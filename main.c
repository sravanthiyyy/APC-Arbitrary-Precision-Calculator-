#include <stdio.h>
#include "validation.h"

//arc : argument count 
//argv : argument vector 
int main(int argc, char *argv[])
{
    //initialising lists for operands and result
    Node *head1 = NULL, *tail1 = NULL;
    Node *head2 = NULL, *tail2 = NULL;
    Node *headR = NULL, *tailR = NULL;
    //used to store result sign
    int sign = 0;
    //used to store sign of operands
    char s1, s2;
     
    //argc validation fun 
    if (read_validate_arguments(argc, argv, &s1, &s2) == FAILURE)
    {
        return FAILURE;
    }

    //operand1 validation fun
    if (string_to_list(argv[1], &head1, &tail1) == FAILURE)
    {
        return FAILURE;
    }
    
    //operand2 validation fun
    if (string_to_list(argv[3], &head2, &tail2) == FAILURE)
    {
        return FAILURE;
    }

    //print to check conversion successful or not
    printf("Conversion successfull\n");
    printf("-----------------------\n");
    printf("First operand : ");
    print_list(head1);
    printf("Second operand : ");
    print_list(head2);
    printf("-----------------------\n");

    //extract operaor
    char operator = argv[2][0];

    //compare value and sign of operands
    int result = compare_lists(head1, head2);
    int sign_result = compare_signs(&s1, &s2);

    //performing operation based on operator
    switch (operator)
    {
        //for addition operator
        case '+':
            printf("Performing the addition operation\n");
            printf("Result : ");

            //if both positive
            if (sign_result == 3)
            {
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                 printf("+");
                print_list(headR);
            }
            //if first positive and sec negitive
            else if (sign_result == 2)
            {
                subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR, &sign);
                if (result == 2)
                {
                   
                    printf("%c", s1);
                    print_list(headR);
                }
                else if (result == 1)
                {
                   
                    printf("%c", s2);
                    print_list(headR);
                }
            }
            //first neg and sec positive
            else if (sign_result == 1)
            {
                subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR, &sign);
                if (result == 2)
                {
                  
                    printf("%c", s1);
                    print_list(headR);
                }
                else if (result == 1)
                {
                    
                    printf("%c", s2);
                    print_list(headR);
                }
            }
            //both operands negative
            else
            {
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
               
                printf("-");
                print_list(headR);
            }
            break;
        //for subtraction operator
        case '-':
            printf("Performing Subraction operation\n");
            printf("Result : ");
            //both positive
            if (sign_result == 3)
            {
                subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR, &sign);
                
                if (sign == 1)
                {
                    printf("-");
                }
                else
                {
                     printf("+");
                }
                print_list(headR);
            }
            //first pos and sec neg
            else if (sign_result == 2)
            {
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
               
                printf("%c", s1);
                print_list(headR);
            }
            //first neg and sec pos
            else if (sign_result == 1)
            {
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                
                printf("%c", s1);
                print_list(headR);
            }
            //both neg
            else
            {
                subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR, &sign);
               
                if (sign == 1)
                {
                    printf("-");
                }
                else
                {
                    printf("+");
                }
                print_list(headR);
            }
            break;
        /* In cammand line * is used for  other operation so insted 
         we use x or X for multiplication operator
        */
        case 'x':
        case 'X':
            printf("Performing the multiplication operation\n");
            multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            printf("Result : ");
            //determine sign of result
            if (sign_result == 3 || sign_result == 0)
            {
                printf("+");
                print_list(headR);
            }
            else
            {
                printf("-");
                print_list(headR);
            }
            break;
        //for division operator
        case '/':
            printf("performing Division operation\n");
            division(&head1, &tail1, &head2, &tail2, &headR, &tailR, &sign);
            printf("Result : ");
    
            //if divisior is zero
            if (sign == 1)
            {
                printf("Divisor should not be Zero\n");
            }
            else
            {
                //determine sign of result
                
                if (sign_result == 3 || sign_result == 0)
                {
                    printf("+");
                    print_list(headR);
                }
                else
                {
                    printf("-");
                    print_list(headR);
                }
            }
            break;

        default:
            printf("Invalid operation\n");
            return FAILURE;
    }

    //free all allocated linked lists
    free_list(&head1, &tail1);
    free_list(&head2, &tail2);
    free_list(&headR, &tailR);

    return SUCCESS;
}
