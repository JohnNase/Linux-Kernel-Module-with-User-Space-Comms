# Linux Kernel Module with User-Space Interaction

This project demonstrates the development of a simple Linux kernel module that interacts with a user-space application. The kernel module creates a virtual device (`/dev/my_device`) that allows reading and writing data. The user-space application communicates with the kernel module via the device file, showcasing basic kernel programming, system calls, and debugging.

## Features
- **Kernel Module**: A simple Linux kernel module that creates a virtual device.
- **User-Space Application**: A C program that interacts with the kernel module via the device file.
- **Makefile**: Automates the compilation of the kernel module and user-space application.

## Technologies Used
- **C Programming**: For kernel module and user-space application development.
- **Linux Kernel APIs**: `file_operations`, `copy_to_user`, `copy_from_user`, etc.
- **Make**: For automating the build process.
- **Ubuntu/WSL**: Development environment.

## Project Structure