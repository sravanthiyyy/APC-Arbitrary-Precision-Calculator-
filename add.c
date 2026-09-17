#include "validation.h"
/*
 * head1, tail1 : First number linked list
 * head2, tail2 : Second number linked list
 * headR, tailR : Result (Sum) linked list
*/
int addition(Node **head1, Node **tail1, Node **head2, Node **tail2, Node **headR, Node **tailR)
{
    //start from least sigf digit of both numbers
    Node *temp1 = *tail1;
    Node *temp2 = *tail2;
    int carry = 0;

    //initialise result list as empty
    *headR = NULL;
    *tailR = NULL;

    //loop till all digits in both list reach null and carry 0 
    while (temp1 != NULL || temp2 != NULL || carry != 0)
    {
        int sum = carry;

        //add digit from first num if present
        if (temp1)
        {
            //adding num1 digit to sum
            sum += temp1->data;
            temp1 = temp1->prev;
        }

        //add digit from sec num if present
        if (temp2)
        {
            //adding num2 digit to sum
            sum += temp2->data;
            temp2 = temp2->prev;
        }
        
        //carry for next iteration 
        if(sum > 9 )
        {
            carry =1 ;
            //to keep the single digit
            sum = sum - 10;
        }
        else
        {
            carry = 0;
        }

        //or other way if we have carry 
        // carry = sum / 10;
        // int digit = sum % 10;   

        //digit stored in res list
        int digit = sum;

        //creating node to store resultant sum of those digits
        Node *new_node = create_node(digit);
        if (!new_node)
            return FAILURE;

            //insert the digit at the front of res list
        if (*headR == NULL)
        {
            *headR = *tailR = new_node;
        }
        else
        {
            new_node->next = *headR;
            (*headR)->prev = new_node;
            *headR = new_node;
        }
    }

    return SUCCESS;
}
