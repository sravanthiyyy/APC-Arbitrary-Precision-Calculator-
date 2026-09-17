#include "validation.h"

/*
 * head1, tail1 : First number linked list
 * head2, tail2 : Second number linked list
 * headR, tailR : Result (Difference) linked list
 * sign         : 0 → positive result, 1 → negative result
*/
int subtraction(Node **head1, Node **tail1, Node **head2, Node **tail2,Node **headR, Node **tailR, int *sign)
{
    //assume res is positive initially
    *sign = 0; 

    Node *temp1 = NULL;
    Node *temp2 = NULL;

    //cmp given two numbers to do sub order
    int cmp = compare_lists(*head1, *head2);

    //if furst num >= sec num
    if (cmp == 2)
    {
        temp1 = *tail1;
        temp2 = *tail2;
    }
    //if first num < sec num
    else if (cmp == 1)
    {
        temp1 = *tail2;//larger 
        temp2 = *tail1;//smaller
        *sign = 1; //res be neg
    }
    //if both nums are equal
    else
    {
        Node *res = create_node(0);
        if (!res)
            return FAILURE;
        *headR = *tailR = res;
        return SUCCESS;
    }

    //initialize res list
    *headR = NULL;
    *tailR = NULL;

    int borrow = 0;

    //doing digit by digit sub from lsb to msb 
    while (temp1 != NULL || temp2 != NULL)
    {
        int v1 = (temp1) ? temp1->data : 0;
        int v2 = (temp2) ? temp2->data : 0;

        //sub digits along with borrow
        int diff = v1 - v2 + borrow;

        //store borrow fro next num/iteration
        if (diff < 0)
        {
            diff += 10;
            borrow = -1;
        }
        else
        {
            borrow = 0;
        }

        //create node for current digit of res
        Node *new_node = create_node(diff);
        if (!new_node)
            return FAILURE;

        //insert digit at front of res list
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

        //move to prev digits
        if (temp1)
            temp1 = temp1->prev;
        if (temp2)
            temp2 = temp2->prev;
    }

    //remove zeros from res
    remove_leading_zeros(headR, tailR);

    return SUCCESS;
}
