#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
    Beginner Image Processing Project in C
    Works with ASCII PGM (P2) grayscale images.
*/

/* Structure to store image information */
typedef struct {
    int width;
    int height;
    int maxValue;
    int *pixel;
} Image;


/* Keep a value inside the valid grayscale range */
int clamp(int value, int maxValue) {

    if (value < 0)
        return 0;

    if (value > maxValue)
        return maxValue;

    return value;
}


/* Convert row and column into 1-D array position */
int indexOf(const Image *img, int row, int col) {

    return row * img->width + col;
}


/*
    Read the next useful word from a PGM file.

    PGM files can contain comments beginning with #.
    This function skips whitespace and comments.
*/
int nextToken(FILE *fp, char *token, int size) {

    int ch;

    while ((ch = fgetc(fp)) != EOF) {

        /* Ignore spaces, tabs and new lines */
        if (isspace(ch))
            continue;

        /* Ignore comments */
        if (ch == '#') {

            while ((ch = fgetc(fp)) != EOF && ch != '\n') {
                /* Skip comment */
            }

            continue;
        }

        break;
    }

    /* End of file */
    if (ch == EOF)
        return 0;

    int i = 0;

    token[i++] = (char)ch;

    while (i < size - 1 && (ch = fgetc(fp)) != EOF) {

        if (isspace(ch))
            break;

        /*
            If a comment starts after a token,
            stop reading this token.
        */
        if (ch == '#') {

            while ((ch = fgetc(fp)) != EOF && ch != '\n') {
                /* Skip comment */
            }

            break;
        }

        token[i++] = (char)ch;
    }

    token[i] = '\0';

    return 1;
}


/* Read a P2 PGM image */
int readPGM(const char *fileName, Image *img) {

    FILE *fp = fopen(fileName, "r");

    char token[100];

    if (fp == NULL) {

        printf("Error: Could not open %s\n", fileName);

        return 0;
    }


    /* Check PGM type */
    if (!nextToken(fp, token, sizeof(token)) ||
        strcmp(token, "P2") != 0) {

        printf("Error: This program needs an ASCII PGM (P2) file.\n");

        fclose(fp);

        return 0;
    }


    /* Read width */
    if (!nextToken(fp, token, sizeof(token))) {

        fclose(fp);

        return 0;
    }

    img->width = atoi(token);


    /* Read height */
    if (!nextToken(fp, token, sizeof(token))) {

        fclose(fp);

        return 0;
    }

    img->height = atoi(token);


    /* Read maximum grayscale value */
    if (!nextToken(fp, token, sizeof(token))) {

        fclose(fp);

        return 0;
    }

    img->maxValue = atoi(token);


    /* Validate image header */
    if (img->width <= 0 ||
        img->height <= 0 ||
        img->maxValue <= 0 ||
        img->maxValue > 65535) {

        printf("Error: Invalid PGM header.\n");

        fclose(fp);

        return 0;
    }


    /* Calculate number of pixels */
    long totalPixels =
        (long)img->width * img->height;


    /* Allocate memory */
    img->pixel =
        (int *)malloc(totalPixels * sizeof(int));


    if (img->pixel == NULL) {

        printf("Error: Not enough memory.\n");

        fclose(fp);

        return 0;
    }


    /* Read every pixel */
    for (long i = 0; i < totalPixels; i++) {

        if (!nextToken(fp, token, sizeof(token))) {

            printf(
                "Error: Image contains fewer pixels than expected.\n"
            );

            free(img->pixel);

            img->pixel = NULL;

            fclose(fp);

            return 0;
        }


        img->pixel[i] =
            clamp(atoi(token), img->maxValue);
    }


    fclose(fp);

    return 1;
}


/* Write an image as P2 PGM */
int writePGM(const char *fileName, const Image *img) {

    FILE *fp = fopen(fileName, "w");

    if (fp == NULL) {

        printf("Error: Could not create %s\n", fileName);

        return 0;
    }


    /* PGM header */
    fprintf(fp, "P2\n");

    fprintf(
        fp,
        "# Created by beginner C image processing project\n"
    );

    fprintf(
        fp,
        "%d %d\n",
        img->width,
        img->height
    );

    fprintf(
        fp,
        "%d\n",
        img->maxValue
    );


    /* Write pixel values */
    for (int row = 0; row < img->height; row++) {

        for (int col = 0; col < img->width; col++) {

            fprintf(
                fp,
                "%d ",
                img->pixel[indexOf(img, row, col)]
            );
        }

        fprintf(fp, "\n");
    }


    fclose(fp);

    return 1;
}


/*
    Create an empty image having
    the same size as the source image.
*/
int createLike(const Image *source, Image *result) {

    result->width = source->width;

    result->height = source->height;

    result->maxValue = source->maxValue;


    long totalPixels =
        (long)source->width * source->height;


    result->pixel =
        (int *)malloc(totalPixels * sizeof(int));


    if (result->pixel == NULL) {

        printf(
            "Error: Not enough memory for output image.\n"
        );

        return 0;
    }


    return 1;
}


/*
    Operation 1:
    Negative Image

    Formula:

    newPixel = maxValue - oldPixel
*/
void makeNegative(
    const Image *input,
    Image *output
) {

    long totalPixels =
        (long)input->width * input->height;


    for (long i = 0; i < totalPixels; i++) {

        output->pixel[i] =
            input->maxValue - input->pixel[i];
    }
}


/*
    Operation 2:
    Change Brightness

    Positive amount  -> brighter
    Negative amount  -> darker
*/
void changeBrightness(
    const Image *input,
    Image *output,
    int amount
) {

    long totalPixels =
        (long)input->width * input->height;


    for (long i = 0; i < totalPixels; i++) {

        output->pixel[i] =
            clamp(
                input->pixel[i] + amount,
                input->maxValue
            );
    }
}


/*
    Operation 3:
    Threshold

    Pixel >= threshold -> white
    Pixel < threshold  -> black
*/
void applyThreshold(
    const Image *input,
    Image *output,
    int threshold
) {

    long totalPixels =
        (long)input->width * input->height;


    for (long i = 0; i < totalPixels; i++) {

        if (input->pixel[i] >= threshold)

            output->pixel[i] =
                input->maxValue;

        else

            output->pixel[i] = 0;
    }
}


/*
    Operation 4:
    Horizontal Flip
*/
void flipHorizontal(
    const Image *input,
    Image *output
) {

    for (int row = 0;
         row < input->height;
         row++) {

        for (int col = 0;
             col < input->width;
             col++) {

            int newCol =
                input->width - 1 - col;


            output->pixel[
                indexOf(output, row, newCol)
            ] =
                input->pixel[
                    indexOf(input, row, col)
                ];
        }
    }
}


/*
    Operation 5:
    Simple 3 x 3 Average Blur
*/
void blurImage(
    const Image *input,
    Image *output
) {

    for (int row = 0;
         row < input->height;
         row++) {

        for (int col = 0;
             col < input->width;
             col++) {

            int sum = 0;

            int count = 0;


            /*
                Visit the 3 x 3 neighbourhood
            */
            for (int dr = -1;
                 dr <= 1;
                 dr++) {

                for (int dc = -1;
                     dc <= 1;
                     dc++) {

                    int r = row + dr;

                    int c = col + dc;


                    /*
                        Check image boundaries
                    */
                    if (r >= 0 &&
                        r < input->height &&
                        c >= 0 &&
                        c < input->width) {

                        sum +=
                            input->pixel[
                                indexOf(input, r, c)
                            ];

                        count++;
                    }
                }
            }


            /* Average of neighbouring pixels */
            output->pixel[
                indexOf(output, row, col)
            ] = sum / count;
        }
    }
}


/*
    Operation 6:
    Edge Detection using Sobel idea
*/
void detectEdges(
    const Image *input,
    Image *output
) {

    /*
        Horizontal gradient kernel
    */
    int gxKernel[3][3] = {

        {-1, 0, 1},

        {-2, 0, 2},

        {-1, 0, 1}
    };


    /*
        Vertical gradient kernel
    */
    int gyKernel[3][3] = {

        {-1, -2, -1},

        { 0,  0,  0},

        { 1,  2,  1}
    };


    for (int row = 0;
         row < input->height;
         row++) {

        for (int col = 0;
             col < input->width;
             col++) {


            /*
                Border pixels do not have
                a complete 3 x 3 neighbourhood.
            */
            if (row == 0 ||
                col == 0 ||
                row == input->height - 1 ||
                col == input->width - 1) {

                output->pixel[
                    indexOf(output, row, col)
                ] = 0;

                continue;
            }


            int gx = 0;

            int gy = 0;


            /*
                Apply the two Sobel kernels
            */
            for (int kr = -1;
                 kr <= 1;
                 kr++) {

                for (int kc = -1;
                     kc <= 1;
                     kc++) {

                    int value =
                        input->pixel[
                            indexOf(
                                input,
                                row + kr,
                                col + kc
                            )
                        ];


                    gx +=
                        value *
                        gxKernel[kr + 1][kc + 1];


                    gy +=
                        value *
                        gyKernel[kr + 1][kc + 1];
                }
            }


            /*
                Calculate edge strength
            */
            int edgeStrength =
                abs(gx) + abs(gy);


            output->pixel[
                indexOf(output, row, col)
            ] =
                clamp(
                    edgeStrength,
                    input->maxValue
                );
        }
    }
}


/*
    Operation 7:
    Display Image Information
*/
void showImageInfo(const Image *img) {

    printf("\n");

    printf("Image information\n");

    printf(
        "Width       : %d pixels\n",
        img->width
    );

    printf(
        "Height      : %d pixels\n",
        img->height
    );

    printf(
        "Maximum gray: %d\n",
        img->maxValue
    );

    printf(
        "Total pixels: %ld\n",
        (long)img->width * img->height
    );

    printf("\n");
}


/*
    MAIN FUNCTION
*/
int main(void) {

    Image input = {
        0,
        0,
        0,
        NULL
    };


    Image output = {
        0,
        0,
        0,
        NULL
    };


    char fileName[200];

    int choice;


    printf("\n");
    printf("========================================\n");
    printf("     BEGINNER IMAGE PROCESSING IN C\n");
    printf("========================================\n");
    printf("\n");


    /*
        Ask user for input image
    */
    printf("Enter the input PGM file name: ");

    scanf("%199s", fileName);


    /*
        Read input image
    */
    if (!readPGM(fileName, &input)) {

        return 1;
    }


    printf("\nImage loaded successfully!\n");


    showImageInfo(&input);


    /*
        Menu loop
    */
    do {

        printf("========================================\n");
        printf("Choose an operation:\n");
        printf("========================================\n");

        printf("1. Create negative image\n");

        printf("2. Change brightness\n");

        printf("3. Convert to black and white (threshold)\n");

        printf("4. Flip horizontally\n");

        printf("5. Blur image\n");

        printf("6. Detect edges\n");

        printf("7. Show image information\n");

        printf("0. Exit\n");

        printf("========================================\n");

        printf("Enter choice: ");

        scanf("%d", &choice);


        /*
            Exit
        */
        if (choice == 0) {

            break;
        }


        /*
            Show image information
        */
        if (choice == 7) {

            showImageInfo(&input);

            continue;
        }


        /*
            Validate menu choice
        */
        if (choice < 1 || choice > 6) {

            printf(
                "Invalid choice. Please try again.\n\n"
            );

            continue;
        }


        /*
            Create output image
        */
        if (!createLike(&input, &output)) {

            free(input.pixel);

            return 1;
        }


        /*
            Operation 1: Negative
        */
        if (choice == 1) {

            makeNegative(
                &input,
                &output
            );


            if (writePGM(
                    "negative.pgm",
                    &output)) {

                printf(
                    "Done! Output saved as negative.pgm\n\n"
                );
            }
        }


        /*
            Operation 2: Brightness
        */
        else if (choice == 2) {

            int amount;


            printf(
                "Enter brightness amount (-255 to 255): "
            );

            scanf("%d", &amount);


            changeBrightness(
                &input,
                &output,
                amount
            );


            if (writePGM(
                    "brightness.pgm",
                    &output)) {

                printf(
                    "Done! Output saved as brightness.pgm\n\n"
                );
            }
        }


        /*
            Operation 3: Threshold
        */
        else if (choice == 3) {

            int threshold;


            printf(
                "Enter threshold (0 to %d): ",
                input.maxValue
            );

            scanf("%d", &threshold);


            threshold =
                clamp(
                    threshold,
                    input.maxValue
                );


            applyThreshold(
                &input,
                &output,
                threshold
            );


            if (writePGM(
                    "threshold.pgm",
                    &output)) {

                printf(
                    "Done! Output saved as threshold.pgm\n\n"
                );
            }
        }


        /*
            Operation 4: Horizontal Flip
        */
        else if (choice == 4) {

            flipHorizontal(
                &input,
                &output
            );


            if (writePGM(
                    "horizontal_flip.pgm",
                    &output)) {

                printf(
                    "Done! Output saved as horizontal_flip.pgm\n\n"
                );
            }
        }


        /*
            Operation 5: Blur
        */
        else if (choice == 5) {

            blurImage(
                &input,
                &output
            );


            if (writePGM(
                    "blur.pgm",
                    &output)) {

                printf(
                    "Done! Output saved as blur.pgm\n\n"
                );
            }
        }


        /*
            Operation 6: Edge Detection
        */
        else if (choice == 6) {

            detectEdges(
                &input,
                &output
            );


            if (writePGM(
                    "edge.pgm",
                    &output)) {

                printf(
                    "Done! Output saved as edge.pgm\n\n"
                );
            }
        }


        /*
            Free output image memory
        */
        free(output.pixel);

        output.pixel = NULL;

    } while (1);


    /*
        Free input image memory
    */
    free(input.pixel);


    printf("\n");
    printf("Program closed. Goodbye!\n");

    return 0;
}