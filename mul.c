#include "validation.h"
/*
 * head1, tail1 : First number linked list
 * head2, tail2 : Second number linked list
 * headR, tailR : Result (Product) linked list
*/
int multiplication(Node **head1, Node **tail1, Node **head2, Node **tail2, Node **headR, Node **tailR)
{
    //initialising res list as empty
    *headR = *tailR = NULL;

    //start from least sig digit of sec num
    Node *temp2 = *tail2;
    //keeos tract of pos 
    int count = 0,v1,v2;
  
    //loop through each digit of sec num
    while (temp2)
    {
        int carry = 0;

        //temp list to store partial mult rea=s
        Node *headR2 = NULL, *tailR2 = NULL;

        //add zeros at the end based on digit position
        for (int i = 0; i < count; i++)
        {
            insert_at_last(&headR2, &tailR2, 0);
        }
        
        //start from least sigf digit of first num
        Node *temp1 = *tail1;
        //multiplying each digit of first nu with current digit of sec
        while (temp1)
        {
            v1=temp1->data;
            v2=temp2->data;

            //multiply digits and add carry
            int mul = v1 * v2 + carry;

            //update carry
            carry = mul / 10;

            //storing cuurent digit at front of partial res
            insert_at_front(&headR2, &tailR2, mul % 10);
            temp1 = temp1->prev;
        }

        //if carry present insert it
        if (carry > 0)
        {
            insert_at_front(&headR2, &tailR2, carry);
        }

        //add partisl res to final res
        addition(headR, tailR, &headR2, &tailR2, headR, tailR);

        //free temp partial res list
        free_list(&headR2, &tailR2);
        
        //move to next digit of sec num
        count++;
        temp2 = temp2->prev;
    }
    
    //removing unnecessary leading zeroes in res
    remove_leading_zeros(headR, tailR);

    //if res becomes empty insert 0
    if (!*headR)
    {
        insert_at_front(headR, tailR, 0);
    }

    return SUCCESS;
}
