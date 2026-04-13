# Arbitrary Precision Calculator

## Overview
The Arbitrary Precision Calculator is a command-line application developed in C that performs mathematical operations on very large numbers with high precision. Unlike standard data types that have size limitations, this calculator is capable of handling numbers with an arbitrary number of digits by implementing custom data structures and algorithms.

This project demonstrates advanced concepts such as big number arithmetic, dynamic memory management, and efficient data representation.

## Features
- Perform addition, subtraction, multiplication, and division on large numbers  
- Supports numbers beyond standard data type limits  
- High precision arithmetic operations  
- Handles positive and negative numbers  
- Command-line based user interaction  

## Technologies Used
- Programming Language: C  
- Concepts:  
  - Arbitrary Precision Arithmetic  
  - Linked Lists / Arrays for large number representation  
  - Dynamic Memory Allocation  
  - Modular Programming  
  - String Manipulation  

## Project Structure
Arbitrary-Precision-Calculator/  
│── main.c  
│── addition.c  
│── subtraction.c  
│── multiplication.c  
│── division.c  
│── common.h  
│── Makefile (optional)  

## How to Run
Compile the program:
gcc main.c addition.c subtraction.c multiplication.c division.c -o calculator  

Run the program:
./calculator  

## Sample Functionality
The program allows users to input very large numbers and perform arithmetic operations with high precision, ensuring accurate results even for values exceeding standard integer limits.

## Learning Outcomes
- Understanding of arbitrary precision arithmetic  
- Implementation of large number operations using custom logic  
- Improved knowledge of memory management in C  
- Experience in designing modular and scalable programs  

## Future Enhancements
- Support for floating-point arbitrary precision  
- Advanced mathematical functions (power, factorial, etc.)  
- GUI-based interface  
- Performance optimization for very large inputs  

## Author
Nagaveni Belavadi  

## License
This project is intended for educational and learning purposes.
