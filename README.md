# Image Processing with C

This project is a C program designed for image processing and applying filters to bitmap (.bmp) images. The application provides a terminal-based interface for users to interact with the program and apply transformations or filters to images.

---

## Features
- Load and process .bmp images.
- Apply various image filters (customizable).
- Save processed images under a new filename.
- Lightweight and dependency-minimal.

---

## Prerequisites
To use this program, ensure you have the following:
- A Linux-based system.
- GCC (GNU Compiler Collection).
- ImageMagick (for viewing processed images).

Install ImageMagick if not already installed:
```bash
sudo apt install imagemagick
```

---

## Setup and Compilation
Follow these steps to compile and run the program:

1. Compile the necessary object file:
   ```bash
   gcc -c structures.c -o fichier_o/structures.o
   ```

2. Use the provided Makefile to compile the program:
   ```bash
   make
   ```

3. Run the program:
   ```bash
   ./prog
   ```

---

## How to Use
1. Launch the program by running `./prog` in your terminal.
2. Follow the on-screen prompts to select and process an image.
3. The processed image will be saved as `new.bmp` (default name). You can modify this name directly in the source code if needed.
4. To view the processed image, use the following command:
   ```bash
   display new.bmp
   ```

### Adding New Image Cases
To add a new image for processing:
1. Open `functions_traitement.c`.
2. Add a new `case` block with the following template:
   ```c
   case (your_case_number):
       openbmpfile("your_image_filename.bmp");
       break;
   ```
3. Update the line:
   ```c
   while ((pic < 1) && (pic > 4));
   ```
   Replace `4` with the total number of cases you now have.

4. (Optional) Add a description of your new image to the on-screen prompts for better clarity.

---

## Screenshots


---

## Notes
- The program currently supports .bmp files only. Ensure your images are in the correct format.
- Any modifications to the code (e.g., adding filters) can be done in `functions_traitement.c`.

---

Have a good day :)

