# Image Processing with C

This project is a C program designed for image processing and applying filters to bitmap (.bmp) images. The application provides a terminal-based interface for users to interact with the program and apply transformations or filters to images.

---

## Features
- Load and process .bmp images.
- Apply various image filters (customizable).
- Save processed images under a new filename.

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

4. Add the option in the choice in menu()
   ```c
   		printf("What image to you want to use between: \n(1) TIGER (but not Woods) \n(2) Landscape \n(3) A really cool painting \n(4) People (with a great sunset) \nPlease enter the number related to your choice\n");
   ```
6. To see the changement enter 'make' in your terminal and execute './prog'

---

## Screenshots
Negatif of the tiger picture
![image](https://github.com/user-attachments/assets/4905305a-d5ce-4771-a199-45c4dadd6216)

Binary of the landscape
![image](https://github.com/user-attachments/assets/185c681b-55b4-4284-9f07-be3bf34ea856)

Sepia Filter
![image](https://github.com/user-attachments/assets/dafc4303-d117-438b-9153-e9150a4b1b7f)

Blur
![image](https://github.com/user-attachments/assets/22822018-7397-40a5-86df-22d56018cd81)

All of the options
![image](https://github.com/user-attachments/assets/a788568d-df07-486e-97fd-dc06b426dfd7)


---

## Notes
- The program currently supports .bmp files only. Ensure your images are in the correct format.
- Any modifications to the code (e.g., adding filters) can be done in `functions_traitement.c`.

---

Have a good day :)

