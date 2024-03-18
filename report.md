#File Encrypter, Decrypter

This code is an implementation of a Caesar Cipher encryption and decryption program in C, using the ncurses library for terminal-based user interface. Below is an explanation of each part of the code:

1. **Header Inclusions**: The code includes necessary standard C libraries like `stdio.h`, `stdlib.h`, `string.h`, etc., and `ncurses.h` for terminal manipulation.

2. **Function `rotate`**: This function rotates each character by a given key. It handles both lowercase and uppercase characters by shifting them within their respective ASCII ranges. The rotation is performed modulo 26 to handle cases where the key exceeds 26.

3. **Function `encrypt`**: This function reads data from a file, encrypts it using the `rotate` function, and writes the encrypted data to another file named "encrypted_caesar.txt".

4. **Function `decrypt`**: This function reads encrypted data from a file, decrypts it by rotating characters in the opposite direction, and writes the decrypted data to multiple files with names "decrypted_caesar_X.txt", where X represents different rotation values.

5. **Main Function**: 
    - Sets up the ncurses environment.
    - Displays a menu with options for encryption, decryption, and exit.
    - Based on user input, it either encrypts or decrypts a file.
    - It handles input validation for filenames and keys.
    - Uses the `error` function to check if a file exists.

6. **Function `print_menu`**: This function prints the menu on the screen using ncurses, highlighting the currently selected option.

7. **Function `error`**: This function checks if a file exists by attempting to open it. If the file does not exist, it displays an error message indicating the file's absence.

Overall, this code provides a simple command-line interface for encrypting and decrypting files using the Caesar Cipher algorithm. It also incorporates error handling to ensure the smooth execution of operations.
