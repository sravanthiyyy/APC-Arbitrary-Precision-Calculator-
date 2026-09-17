#include "validation.h"

/*
 * str : Input string to validate
 * s   : Pointer to store the sign of the number
*/
int isValidNumber(const char* str, char *s)
{
    //check for null string
    if (str == NULL)
    {
        return FAILURE;
    }
    if (str[0] == '+' || str[0] == '-')
    {
        //storing sign in a pointer
        *s = str[0];

        //and then validate remaining
        for (int i = 1; str[i] != '\0'; i++)
        {
            if (str[i] < '0' || str[i] > '9')
            {
                return FAILURE;
            }
        }
        //string cannot be only a sign
        if (str[1] == '\0')
        {
            return FAILURE;
        }
    }
    else
    {
        //default sign is positive
        *s = '+';
        //validating all chars as digits
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] < '0' || str[i] > '9')
            {
                return FAILURE;
            }
        }
    }
    return SUCCESS;
}

//validation for operation
int isValidOperator(char op)
{
    if (op == '+' || op == '-' || op == 'x' || op == 'X' || op == '/')
    {
        return SUCCESS;
    }
    return FAILURE;
}

/*
 * argc : Argument count
 * argv : Argument vector
 * s1   : Pointer to store sign of first operand
 * s2   : Pointer to store sign of second operand
*/
int read_validate_arguments(int argc, char *argv[],char *s1,char *s2)
{
    
    //check for valid no of arguments
    if (argc != 4)
    {
        printf("Usage: %s Operand1 Operator Operand2\n", argv[0]);
        printf("------------- Menu ------------\n");
        printf("Add:        Operand1 + Operand2\n");
        printf("Subtract:   Operand1 - Operand2\n");
        printf("Multiply:   Operand1 x Operand2\n");
        printf("Divide:     Operand1 / Operand2\n");
        printf("-------------------------------\n");

        return FAILURE;
    }

    //opr must be a single char
    if (argv[2][1] != '\0')
    {
        printf("Enter a single character only for operator\n");
        return FAILURE;
    }

    //validation for first operand
    if (isValidNumber(argv[1],s1) == FAILURE)
    {
        printf("Error: First argument '%s' is not a valid number.\n", argv[1]);
        return FAILURE;
    }

    //validation for operator
    if (isValidOperator(argv[2][0]) == FAILURE)
    {
        printf("Error: Invalid operator '%c'. Use +, -, x, or /.\n", argv[2][0]);
        return FAILURE;
    }

    //validation fro sec operand
    if (isValidNumber(argv[3],s2) == FAILURE)
    {
        printf("Error: Third argument '%s' is not a valid number.\n", argv[3]);
        return FAILURE;
    }
    return SUCCESS;
}

/*
 * str  : Input numeric string
 * head : Pointer to head of linked list
 * tail : Pointer to tail of linked list
*/
int string_to_list(const char *str, Node **head, Node **tail)
{
    if (str == NULL)
    {
        return FAILURE;
    }

    *head = NULL;
    *tail = NULL;

    //skip sign char if present
    if(str[0]=='+' || str[0]=='-')
    {
        for (int i = 1; str[i] != '\0'; i++)
        {
            int digit = str[i] - '0';
            insert_at_last(head, tail, digit);
        }
    }
    //convert char to digit and store
    else
    {
        for (int i = 0; str[i] != '\0'; i++)
        {
            int digit = str[i] - '0';
            insert_at_last(head, tail, digit);
        }
    }
    return SUCCESS;
}

//fun to print numbers stored in list
void print_list(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}

/*
compare list fun
* Returns:
 *  2 → first number is greater
 *  1 → second number is greater
 *  0 → both numbers are equal
*/
int compare_lists(Node *head1, Node *head2)
{
    int count1 = 0, count2 = 0;
    Node *temp1 = head1;
    Node *temp2 = head2;

    //count no of digits in both lists
    while (temp1 != NULL)
    {
        count1++;
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }

    //compare lengths
    if (count1 > count2)
    {
        //first num len is high
        return 2;
    }
    if (count2 > count1)
    {
        //sec num len is high
        return 1;
    }

    //compare digit by digit
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data > head2->data)
        {
            return 2;
        }
        else if (head1->data < head2->data)
        {
            return 1;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    return 0;
}

//free all nodes in a doubly linked list
void free_list(Node **head, Node **tail)
{
    Node *current = *head;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
    *tail = NULL;
}

//fun to creat anode
Node* create_node(int data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

//fun to insert a node at the begining of list
void insert_at_front(Node **head, Node **tail, int data)
{
    Node* newNode = create_node(data);
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->next = *head;
    newNode->prev = NULL;

    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }
    else
        *tail = newNode;

    *head = newNode;
}

//fun to insert a node at the end of the list
void insert_at_last(Node **head, Node **tail, int data)
{
    Node* newNode = create_node(data);
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->next = NULL;
    newNode->prev = *tail;

    if (*tail != NULL)
        (*tail)->next = newNode;
    else
        *head = newNode;

    *tail = newNode;
}

//remove unnecessary leading zeros from a number list
void remove_leading_zeros(Node **head, Node **tail)
{
    while (*head != NULL && (*head)->data == 0 && (*head)->next != NULL)
    {
        Node *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
    if (*head == NULL)
    {
        *tail = NULL;
    }
}

/*
 * Returns:
 *  3 → both positive
 *  2 → first positive, second negative
 *  1 → first negative, second positive
 *  0 → both negative
*/
int compare_signs(char *s1, char *s2)
{
    if (*s1 == '+' && *s2 == '+') 
    {
        //if both are positive
        return 3; 
    }
    else if (*s1 == '+' && *s2 == '-')
    {
        //first positive and sec negative
        return 2;
    }
    else if(*s1 == '-' && *s2 == '+')
    {
        //first negative sec positive
        return 1;
    }
    else
    {
        //if both are negative
        return 0;
    }
}
