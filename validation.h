#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macros for status */
#define SUCCESS 0
#define FAILURE 1
/* Doubly linked list node structure */
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

/* Function prototypes */

// Validation Functions
int isValidNumber(const char *str,char *s);
int isValidOperator(char op);
int read_validate_arguments(int argc, char *argv[], char *s1, char *s2);

// Linked List Operations
Node *create_node(int data);
void insert_at_front(Node **head, Node **tail, int data);
void insert_at_last(Node **head, Node **tail, int data);
void print_list(Node *head);
void free_list(Node **head, Node **tail);
int compare_lists(Node *head1, Node *head2);
void remove_leading_zeros(Node **head, Node **tail);
int compare_signs(char *s1,char *s2);
// Conversion
int string_to_list(const char *str, Node **head, Node **tail);

// Arithmetic Operations
int addition(Node **head1, Node **tail1, Node **head2, Node **tail2, Node **headR, Node **tailR);
int subtraction(Node **head1, Node **tail1, Node **head2, Node **tail2, Node **headR, Node **tailR,int *sign);
int multiplication(Node **head1, Node **tail1, Node **head2, Node **tail2, Node **headR, Node **tailR);
int division(Node **head1, Node **tail1, Node **head2, Node **tail2, Node **headR, Node **tailR,int *sign);

#endif
