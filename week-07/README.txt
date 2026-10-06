BEGINNER FACE RECOGNITION USING C
===================================

Files:
- face_recognition.c : main C program
- arun.pgm           : synthetic teaching image
- beena.pgm          : synthetic teaching image
- charan.pgm         : synthetic teaching image
- test_arun.pgm      : test image
- faces.db           : created automatically after registration

Requirements:
- GCC
- ASCII PGM (P2) images

Ubuntu:
    gcc -std=c11 -Wall -Wextra -pedantic face_recognition.c -o face_recognition

Run:
    ./face_recognition

Suggested test:
1. Choose 1 and register Arun using arun.pgm
2. Choose 1 and register Beena using beena.pgm
3. Choose 1 and register Charan using charan.pgm
4. Choose 3 to list registered people
5. Choose 2 and use test_arun.pgm
6. Choose 4 only if you want to delete faces.db

Important:
This is the educational pixel-template project described in the supplied
Student Project Guide. It works best with already-cropped, front-facing,
grayscale images. It is not a security-grade biometric system.

The included PGM files are simple synthetic teaching images created as
starter test data; they are not real people's biometric images.
