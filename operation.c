/**********************************************************************************************
 * Title       : Operation and Utility Functions
 * Description : This file contains helper functions such as input validation, node creation,
 *               list insertion, list conversion, comparison, printing, zero removal and
 *               memory freeing for the APC (Arbitrary Precision Calculator) project.
 **********************************************************************************************/

#include "apc.h"

/* This function checks if the given number is valid.
   It allows digits and an optional leading + or -. */
Status valid_number(char *nums)
{
    if (nums == NULL || nums[0] == '\0')
        return FAILURE;

    int i = 0;

    /* Allow one leading + or - but not alone */
    if (nums[0] == '+' || nums[0] == '-')
    {
        if (nums[1] == '\0') // only + or - is not valid
            return FAILURE;
        i = 1; // skip the sign
    }

    /* Check the rest should be digits only */
    for (; nums[i] != '\0'; i++)
    {
        if (nums[i] < '0' || nums[i] > '9')
            return FAILURE;
    }
    return SUCCESS;
}

/* This function checks whether the operator is valid.
   Allowed operators: +, -, X/x, /, % */
Status valid_operator(char *op)
{
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 ||
        strcmp(op, "X") == 0 || strcmp(op, "x") == 0 ||
        strcmp(op, "/") == 0 || strcmp(op, "%") == 0)
    {
        return SUCCESS;
    }
    return FAILURE;
}

/* This function checks if the user provided correct arguments in command line */
Status validate_input_arguments(int argc, char *argv[])
{
    if (argc != 4) // expecting exactly 4 arguments
        return FAILURE;

    if (valid_number(argv[1]) == FAILURE)
    {
        printf("Error : Invalid Number -> %s\n", argv[1]);
        return FAILURE;
    }

    if (valid_operator(argv[2]) == FAILURE)
    {
        printf("Error : Invalid Operator -> %s\n", argv[2]);
        return FAILURE;
    }

    if (valid_number(argv[3]) == FAILURE)
    {
        printf("Error : Invalid Number -> %s\n", argv[3]);
        return FAILURE;
    }

    return SUCCESS;
}

/* This function creates a new doubly linked list node */
Dlist *create_new_node(int data)
{
    Dlist *newNode = malloc(sizeof(Dlist));
    if (newNode == NULL)
        return NULL;

    newNode->prev = NULL;
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

/* This function inserts a node at the beginning of the list */
Status insert_at_start(Dlist **head, Dlist **tail, int data)
{
    Dlist *newNode = create_new_node(data);
    if (newNode == NULL)
        return FAILURE;

    /* If list is empty, new node becomes both head and tail */
    if (*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else
    {
        newNode->next = *head;   // link new node to old head
        (*head)->prev = newNode; // set previous pointer
        *head = newNode;         // update head
    }
    return SUCCESS;
}

/* This function converts a number string into a DLL of digits.
   It ignores + or - sign and stores only digits. */
Status string_to_list(Dlist **head, Dlist **tail, char *num)
{
    if (num == NULL)
        return FAILURE;

    int start = 0;

    /* Skip sign if present */
    if (num[0] == '+' || num[0] == '-')
        start = 1;

    /* Insert digits from right to left */
    int len = strlen(num) - 1;
    for (int i = len; i >= start; i--)
    {
        int data = num[i] - '0';
        if (insert_at_start(head, tail, data) == FAILURE)
            return FAILURE;
    }

    /* If list is empty (example: input "0"), insert a zero */
    if (*head == NULL)
    {
        if (insert_at_start(head, tail, 0) == FAILURE)
            return FAILURE;
    }

    return SUCCESS;
}

/* This function prints the number stored in DLL */
void print_list( Dlist *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

/* This function counts how many nodes are in the list */
int length(Dlist *head)
{
    int len = 0;
    while (head)
    {
        len++;
        head = head->next;
    }
    return len;
}

/* This function compares two numbers represented as DLLs.
   Returns SUCCESS if number1 >= number2, otherwise FAILURE. */
Status comparelist(Dlist *head1, Dlist *head2)
{
    int x = length(head1);
    int y = length(head2);

    /* If digit count is more, number is bigger */
    if (x > y)
        return SUCCESS;
    if (x < y)
        return FAILURE;

    /* If same length, compare digit by digit */
    while (head1 && head2)
    {
        if (head1->data > head2->data)
            return SUCCESS;

        if (head1->data < head2->data)
            return FAILURE;

        head1 = head1->next;
        head2 = head2->next;
    }

    return SUCCESS; // both numbers are equal
}

/* This function removes extra zeros at the start (example: 00045 → 45) */
void remove_leading_zero(Dlist **head, Dlist **tail)
{
    if (head == NULL || *head == NULL)
        return;

    /* Remove zeros until we reach a non-zero digit */
    while (*head && (*head)->data == 0 && (*head)->next != NULL)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }

    /* Update tail pointer */
    Dlist *t = *head;
    while (t && t->next)
        t = t->next;
    *tail = t;
}

/* This function frees all nodes of a linked list */
void free_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;

    while (temp)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
    *tail = NULL;
}

/* This function inserts a node at the end of the list */
void insert_at_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
        return;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    /* If list is empty */
    if (!*head && !*tail)
    {
        *head = *tail = new;
    }
    else
    {
        new->prev = *tail;
        (*tail)->next = new;
        *tail = new;
    }
}

/* This function copies one linked list into another */
void copy_list(Dlist **srcH, Dlist **srcT, Dlist **destH, Dlist **destT)
{
    if (srcH == NULL || *srcH == NULL)
    {
        *destH = *destT = NULL;
        return;
    }

    Dlist *temp = *srcH;
    while (temp)
    {
        insert_at_last(destH, destT, temp->data);
        temp = temp->next;
    }
}

/* This function checks if the divisor is zero */
int division_by_zero(Dlist **head, Dlist **tail)
{
    if (head == NULL || *head == NULL)
        return 1; // empty means zero

    /* Skip leading zeros */
    Dlist *t = *head;
    while (t && t->data == 0 && t->next != NULL)
        t = t->next;

    /* If only one zero node remains */
    if (t && t->next == NULL && t->data == 0)
        return 1;

    return 0;
}