/**********************************************************************************************
 * Title       : Multiplication
 * Description : Multiplies two big numbers stored in doubly linked lists.
 **********************************************************************************************/

#include "apc.h"

Status multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp2 = *tail2; // Start from last digit of number2 (right side)

    int result, carry = 0, data, count = 0;

    /* Loop through each digit of number2 */
    while (temp2 != NULL)
    {
        Dlist *temp1 = *tail1; // Start from last digit of number1
        Dlist *headR1 = NULL;  // Partial multiplication result
        Dlist *tailR1 = NULL;
        carry = 0;

        /* Multiply temp2 digit with all digits of number1 */
        while (temp1 != NULL)
        {
            result = temp1->data * temp2->data + carry; // multiply + carry
            carry = result / 10;                        // new carry
            data = result % 10;                         // digit to store

            insert_at_start(&headR1, &tailR1, data); // store digit
            temp1 = temp1->prev;                     // move left
        }

        /* If some carry remains, store it also */
        if (carry > 0)
        {
            insert_at_start(&headR1, &tailR1, carry);
        }

        /* Add zeros at the end depending on place value */
        for (int i = 0; i < count; i++)
        {
            insert_at_last(&headR1, &tailR1, 0);
        }

        /* If this is the first partial result, store it directly */
        if (*headR == NULL)
        {
            *headR = headR1;
            *tailR = tailR1;
        }
        else
        {
            /* Otherwise, add the partial result with earlier result */
            Dlist *headR2 = NULL;
            Dlist *tailR2 = NULL;

            addition(&headR1, &tailR1, headR, tailR, &headR2, &tailR2);

            free_list(headR, tailR);     // delete old result
            free_list(&headR1, &tailR1); // delete partial result

            *headR = headR2; // update final result
            *tailR = tailR2;
        }

        count++;             // For the next round, shift by one zero
        temp2 = temp2->prev; // Move to previous digit in number2
    }

	remove_leading_zero(headR, tailR);
    
    return SUCCESS; // Multiplication done
}