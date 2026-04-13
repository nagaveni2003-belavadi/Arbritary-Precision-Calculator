/**********************************************************************************************
 * Title       : APC Header File
 * Description : Contains all function declarations, structures, and definitions used in the
 *               Arbitrary Precision Calculator (APC) project.
 **********************************************************************************************/

#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int data_t;

/* This structure represents one node of the Doubly Linked List.
   Each node stores one digit of the number. */
typedef struct node
{
    struct node *prev;
    data_t data;
    struct node *next;
} Dlist;

/* Return status used by functions */
typedef enum
{
    FAILURE = 0,
    SUCCESS
} Status;

/* ---------------------- Input Validation Functions ----------------------- */

/* Check if user entered correct number of arguments and valid values */
Status validate_input_arguments(int argc, char *argv[]);

/* Check if operator is valid (+, -, X, /, %) */
Status valid_operator(char *op);

/* Check if a number string contains only digits (with optional + or -) */
Status valid_number(char *nums);

/* ----------------- Functions to Create and Convert DLL ------------------- */

/* Convert a string (number) into a doubly linked list of digits */
Status string_to_list(Dlist **head, Dlist **tail, char *num);

/* Insert a digit at the beginning of the list */
Status insert_at_start(Dlist **head, Dlist **tail, int data);

/* Create a new DLL node */
Dlist *create_new_node(int data);

/* -------------------------- Display Function ----------------------------- */

/* Print the number stored in doubly linked list */
void print_list(Dlist *head);

/* ------------------------ Arithmetic Operations -------------------------- */

/* Big number addition */
Status addition(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **headR, Dlist **tailR);

/* Big number subtraction */
Status subtraction(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   Dlist **headR, Dlist **tailR);

/* Big number multiplication */
Status multiplication(Dlist **head1, Dlist **tail1,
                      Dlist **head2, Dlist **tail2,
                      Dlist **headR, Dlist **tailR);

/* Big number division (quotient only) */
Status division(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **headR, Dlist **tailR);

/* Big number modulus (remainder only) */
Status modulus(Dlist **head1, Dlist **tail1,
               Dlist **head2, Dlist **tail2,
               Dlist **headR, Dlist **tailR);

/* ---------------------- Helper / Utility Functions ----------------------- */

/* Remove extra zeros at the beginning (example 00045 -> 45) */
void remove_leading_zero(Dlist **head, Dlist **tail);

/* Compare two big numbers (returns SUCCESS if num1 >= num2) */
Status comparelist(Dlist *head1, Dlist *head2);

/* Count number of digits (nodes) in a list */
int length(Dlist *head);

/* Free all nodes of the list */
void free_list(Dlist **head, Dlist **tail);

/* Insert a digit at the end of the list */
void insert_at_last(Dlist **head, Dlist **tail, int data);

/* Check if divisor is zero */
int division_by_zero(Dlist **head, Dlist **tail);

/* Copy one list into another */
void copy_list(Dlist **srcH, Dlist **srcT, Dlist **destH, Dlist **destT);

#endif