#include "apc.h"

Status addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int sum = 0, carry = 0, data = 0;

    Dlist *temp1 = *tail1;   // Start from last digit of number1
    Dlist *temp2 = *tail2;   // Start from last digit of number2

    /* Keep adding until all digits are done or carry is left */
    while (temp1 != NULL || temp2 != NULL || carry != 0)
    {
        int x = (temp1) ? temp1->data : 0;   // digit from number1
        int y = (temp2) ? temp2->data : 0;   // digit from number2

        sum = x + y + carry;                 // add both digits + carry
        carry = sum / 10;                    // new carry
        data  = sum % 10;                    // single digit to store

        insert_at_start(headR, tailR, data); // insert digit at beginning of result

        if (temp1) temp1 = temp1->prev;      // move left in number1
        if (temp2) temp2 = temp2->prev;      // move left in number2
    }

    return SUCCESS;   // Addition completed
}