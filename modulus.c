/**********************************************************************************************
 * Title       : Modulus
 * Description : Finds the remainder when two big numbers stored in doubly linked lists
 *               are divided. Stores only the remainder as the final result.
 **********************************************************************************************/
#include "apc.h"

Status modulus(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Check if divisor is zero */
    if (division_by_zero(head2, tail2))
        return FAILURE;

    /* If number1 < number2, remainder is number1 itself */
    if (comparelist(*head1, *head2) == FAILURE)
    {
        free_list(headR, tailR);               // clear old result
        copy_list(head1, tail1, headR, tailR); // copy number1 as remainder
        return SUCCESS;
    }

    Dlist *remH = NULL, *remT = NULL; // remainder list
    Dlist *temp = *head1;             // start from leftmost digit of number1

    /* Long-division style: bring down digits one by one */
    while (temp)
    {
        /* Add next digit into remainder */
        insert_at_last(&remH, &remT, temp->data);
        remove_leading_zero(&remH, &remT); // remove unnecessary zeros

        /* Keep subtracting divisor until remainder becomes smaller */
        while (remH && comparelist(remH, *head2) != FAILURE)
        {
            Dlist *resH = NULL, *resT = NULL;

            /* rem = rem - divisor */
            subtraction(&remH, &remT, head2, tail2, &resH, &resT);
            remove_leading_zero(&resH, &resT);

            /* replace old remainder with new one */
            free_list(&remH, &remT);
            remH = resH;
            remT = resT;
        }

        temp = temp->next; // move to next digit of number1
    }

    /* Prepare final remainder */
    free_list(headR, tailR); // clear old result
    *headR = remH;
    *tailR = remT;

    /* If remainder becomes empty, store zero */
    if (*headR == NULL)
    {
        insert_at_start(headR, tailR, 0);
    }
    else
    {
        remove_leading_zero(headR, tailR); // clean unnecessary zeros
    }

    return SUCCESS; // Modulus operation complete
}