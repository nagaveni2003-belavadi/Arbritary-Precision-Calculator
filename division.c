/**********************************************************************************************
 * Title       : Division
 * Description : Divides two big numbers stored in doubly linked lists.
 *               Stores only the quotient as the final result.
 **********************************************************************************************/

#include "apc.h"

Status division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	/* Check if divisor is zero */
	if (division_by_zero(head2, tail2))
		return FAILURE; // Cannot divide by zero

	remove_leading_zero(head2, tail2);
	
	/* If number1 < number2, answer is 0 */
	if (comparelist(*head1, *head2) == FAILURE)
	{
		insert_at_last(headR, tailR, 0);
		return SUCCESS;
	}

	Dlist *remH = NULL, *remT = NULL; // Will store remainder part
	Dlist *temp = *head1;			  // Start from leftmost digit of dividend

	/* Go through each digit of the dividend one by one */
	while (temp)
	{
		/* Bring down next digit to remainder */
		insert_at_last(&remH, &remT, temp->data);
		remove_leading_zero(&remH, &remT); // Remove unnecessary zeros

		int qdigit = 0; // This will store the quotient digit for this step

		/* Try subtracting divisor from remainder until it becomes smaller */
		while (remH && comparelist(remH, *head2) != FAILURE)
		{
			Dlist *resH = NULL, *resT = NULL; // To store subtraction result

			/* rem = rem - divisor */
			subtraction(&remH, &remT, head2, tail2, &resH, &resT);
			remove_leading_zero(&resH, &resT);

			/* Free old remainder and update with new remainder */
			free_list(&remH, &remT);
			remH = resH;
			remT = resT;

			qdigit++; // Count how many times divisor fits into remainder
		}

		/* Store this quotient digit in final result */
		insert_at_last(headR, tailR, qdigit);

		temp = temp->next; // Move to the next digit of dividend
	}

	/* Remove leading zeros from final quotient */
	remove_leading_zero(headR, tailR);

	return SUCCESS; // Division complete
}