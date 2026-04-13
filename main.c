/*
===============================================================================
Project Title : Arbitrary Precision Calculator (APC)
Author        : Nagaveni Belavadi
Batch ID      : 25031B_178
Date          : 20/11/2025
Language      : C Programming & Data Structures And Algorithms
===============================================================================

Project Overview
----------------
This project implements an Arbitrary Precision Calculator (APC) using the 
Doubly Linked List (DLL) data structure. The primary objective is to perform 
arithmetic operations on integers of arbitrary size, overcoming the limitations 
of standard data types such as int, long, or long long in C.

Each digit of the number is represented as a node in a doubly linked list.  
This approach enables efficient traversal from both ends (MSB and LSB), making 
it suitable for arithmetic operations that mimic manual calculation.

Key Features
------------
• Supports large integer operations with no size limit.  
• Handles positive and negative numbers.  
• Implements the following operations:
    - Addition
    - Subtraction
    - Multiplication
    - Division (Quotient)
    - Modulus (Remainder)
• Modular and readable code structure.  
• Efficient digit-by-digit computation using DLL nodes.  

Working Principle
-----------------
1. Input numbers are read as strings and converted into doubly linked lists.
2. Each digit is stored in a separate node for flexibility and dynamic growth.
3. Operations are performed using classical arithmetic logic:
   - Addition uses carry propagation.
   - Subtraction uses borrow handling.
   - Multiplication uses partial product accumulation.
   - Division and modulus use repeated subtraction (long division method).
4. The final result is stored in a separate linked list and printed accordingly.

Error Handling
--------------
• Invalid operator or incorrect number format.  
• Division by zero detection.  
• Incorrect command-line arguments.  

Usage Format
------------
    ./a.out <number1> <operator> <number2>

Example Commands:
    ./a.out 123456789 + 987654321
    ./a.out -50000 - 1250
    ./a.out 99999 X 99999
    ./a.out 1000000000 / 25
    ./a.out 123456789 % 97

Future Enhancements
-------------------
• Addition of exponentiation and factorial operations.  
• Support for decimal arithmetic (floating-point big numbers).  
• GUI-based calculator interface.  
• Logging and history tracking.

===============================================================================
*/

/**************************************************************************************************************************************************************
 *Title         : main function(Driver function)
 *Description   : This is the main function where all the operations are called
 ***************************************************************************************************************************************************************/

 #include "apc.h"

int main(int argc, char *argv[])
{
	/* Print the heading of the calculator */
	printf("==============================================================\n");
	printf("             APC - Arbitrary Precision Calculator\n");
	printf("==============================================================\n");

	/* Check if user has entered correct inputs in command line */
	if (validate_input_arguments(argc, argv) == FAILURE)
	{
		printf("\nError      : Invalid input arguments.\n");
		printf("Usage      : ./a.out <number1> <operator> <number2>\n");
		printf("Example    : ./a.out 25000 + 12345\n");
		printf("Operators  : +  -  X  /  %%\n");
		printf("\n==============================================================\n");
		return FAILURE;
	}

	/* Find if number1 is positive or negative */
	int sign1 = (argv[1][0] == '-') ? -1 : 1;

	/* Find if number2 is positive or negative */
	int sign2 = (argv[3][0] == '-') ? -1 : 1;

	/* Create pointers for both numbers and result */
	Dlist *head1 = NULL, *tail1 = NULL; // First number
	Dlist *head2 = NULL, *tail2 = NULL; // Second number
	Dlist *headR = NULL, *tailR = NULL; // Result number

	/* Convert the given strings into linked lists (ignore sign) */
	if (string_to_list(&head1, &tail1, argv[1]) == FAILURE ||
		string_to_list(&head2, &tail2, argv[3]) == FAILURE)
	{
		printf("Error : Conversion to list failed!\n");
		return FAILURE;
	}

	/* Read the operator (+, -, X, /, %) */
	char op = argv[2][0];

	/* This will store sign of final answer */
	int result_sign = 1;

	/* Perform the operation based on operator */
	switch (op)
	{
	/* ----------------- ADDITION ----------------- */
	case '+':
		/* If both numbers have same sign, simple addition */
		if (sign1 == sign2)
		{
			addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
			result_sign = sign1; // Final sign same as inputs
		}
		else
		{
			/* If signs are different, subtract smaller number from bigger one */
			if (comparelist(head1, head2) == SUCCESS)
			{
				subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
				result_sign = sign1;
			}
			else
			{
				subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);
				result_sign = sign2;
			}
		}
		break;

	/* ----------------- SUBTRACTION ----------------- */
	case '-':
		/* Remove unwanted leading zeros before comparing */
		remove_leading_zero(&head1, &tail1);
		remove_leading_zero(&head2, &tail2);

		/* If signs differ, subtraction becomes addition */
		if (sign1 != sign2)
		{
			addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
			result_sign = sign1;
		}
		else
		{
			/* If both have same sign, subtract smaller from bigger */
			if (comparelist(head1, head2) == SUCCESS)
			{
				subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
				result_sign = sign1; // Sign stays same
			}
			else
			{
				subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);
				result_sign = -sign1; // Opposite sign
			}
		}
		break;

	/* ----------------- MULTIPLICATION ----------------- */
	case 'X':
	case 'x':
		/* Multiply both numbers using linked list */
		multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);

		/* Final sign = multiplication of signs */
		result_sign = sign1 * sign2;
		break;

	/* ----------------- DIVISION ----------------- */
	case '/':
		/* Check if second number is zero */
		if (division(&head1, &tail1, &head2, &tail2, &headR, &tailR) == FAILURE)
		{
			printf("\nERROR: Not Divisible by 0. Operand 2 must be non zero value.\n");
			printf("\n==============================================================\n");

			return FAILURE;
		}

		/* Sign logic for division */
		result_sign = sign1 * sign2;
		break;

	/* ----------------- MODULUS ----------------- */
	case '%':
		/* Find remainder of both numbers */
		modulus(&head1, &tail1, &head2, &tail2, &headR, &tailR);

		/* Modulus keeps sign of first number */
		result_sign = sign1;
		break;

	default:
		/* Operator is wrong */
		printf("Invalid Input! Try again...\n");
		return FAILURE;
	}

	/* ----------------- Print Final Output ----------------- */

	/* Print Number 1 */
	printf(" Number 1 : %s", (sign1 == -1 ? "-" : ""));
	print_list(head1);

	/* Print Operator */
	printf(" Operator : %c\n", op);

	/* Print Number 2 */
	printf(" Number 2 : %s", (sign2 == -1 ? "-" : ""));
	print_list(head2);

	printf("--------------------------------------------------------------\n");

	/* Print final result */
	printf(" Result   : ");
	if (result_sign == -1) // Print minus sign if result is negative
		printf("-");
	
	print_list(headR);

	printf("==============================================================\n");

	return SUCCESS;
}