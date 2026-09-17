#include "validation.h"
/*
  perform division using subtraction
 * head1, tail1 : Dividend linked list
 * head2, tail2 : Divisor linked list
 * headR, tailR : Result (Quotient) linked list
 * */
int division(Node **head1, Node **tail1, Node **head2, Node **tail2, Node **headR, Node **tailR,int *sign) 
{
    //to store original sign
    int sign1=*sign;
    //divisor list null or divisor has one node ans its value 0 
    if (*head2 == NULL || ((*head2==*tail2) && (*head2)->data==0) )
    {
        *sign=1;
        return FAILURE;
    }
    //temp list to store current dividend
    Node *dividend_head = NULL, *dividend_tail = NULL;
    //temp list to store subtraction res
    Node *temp_result_head = NULL, *temp_result_tail = NULL;

    //copying org dividend into a temp list to not loose org
    Node *temp = *head1;
    while (temp) 
    {
        insert_at_last(&dividend_head, &dividend_tail, temp->data);
        temp = temp->next;
    }
    //initialising
    Node *one_head = NULL, *one_tail = NULL;
    Node *quotient_head = NULL, *quotient_tail = NULL;

    insert_at_last(&one_head, &one_tail, 1);
    insert_at_last(&quotient_head, &quotient_tail, 0);

    int cmp;
    //division loop
    while (compare_lists(dividend_head, *head2) != 1) 
    {
         //sub divisior from current dividend
        if (subtraction(&dividend_head, &dividend_tail, head2, tail2, &temp_result_head, &temp_result_tail, &sign1) == FAILURE) 
        {
            //free allocated memory before returning
            free_list(&dividend_head, &dividend_tail);
            free_list(&one_head, &one_tail);
            free_list(&quotient_head, &quotient_tail);
            return FAILURE;
        }
        
        //update dividend with sub res
        free_list(&dividend_head, &dividend_tail);
        dividend_head = temp_result_head;
        dividend_tail = temp_result_tail;

        temp_result_head = NULL;
        temp_result_tail = NULL;
        Node *temp_quot_head = NULL, *temp_quot_tail = NULL;
        if (addition(&quotient_head, &quotient_tail, &one_head, &one_tail, &temp_quot_head, &temp_quot_tail) == FAILURE) 
        {
            free_list(&dividend_head, &dividend_tail);
            free_list(&one_head, &one_tail);
            free_list(&quotient_head, &quotient_tail);
            return FAILURE;
        }

        //update quotient
        free_list(&quotient_head, &quotient_tail);
        quotient_head = temp_quot_head;
        quotient_tail = temp_quot_tail;
    }

    //assign quotient to result list
    *headR = quotient_head;
    *tailR = quotient_tail;

    //free temp list
    free_list(&dividend_head, &dividend_tail);
    free_list(&one_head, &one_tail);

    //remove leading zeros from result
    remove_leading_zeros(headR, tailR);

    //if res becomes empty insert 0
    if (*headR == NULL) 
    {
        insert_at_front(headR, tailR, 0);
    }

    return SUCCESS;
}
