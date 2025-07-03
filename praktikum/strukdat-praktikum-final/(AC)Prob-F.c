#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct stackNode_t {
    int data;
    struct stackNode_t *next;
} StackNode;

typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;

void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int value);
void stack_pop(Stack *stack);
int stack_top(Stack *stack);
unsigned stack_size(Stack *stack);

void stack_init(Stack *stack) 
{
    stack->_size = 0;
    stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, int value) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
        
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack) 
{
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

int strtoi(char *string) {
    int number = 0;
    if (string[0] != '-') {
        for (int i = 0; string[i] != '\0'; i++) {
            number = number * 10 + (string[i] - '0');
        }
    } else {
        for (int i = 1; string[i] != '\0'; i++) {
            number = number * 10 + (string[i] - '0');
        } number *= -1;
    } return number;
}

int stack_top(Stack *stack) 
{
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack->_size;
}

int main(int argc, char const *argv[])
{
    Stack charles;
    stack_init(&charles);

    char operand[1001];
    if (fgets(operand, sizeof(operand), stdin)) {
     char *token = strtok(operand, " \n");
        while (token != NULL) {
            if (strcmp(token, "+") == 0) {
                if (stack_size(&charles) >= 2) {
                    stack_push(&charles, charles._top->data + charles._top->next->data);
                }
            } else if (strcmp(token, "C") == 0) {
                stack_pop(&charles);
            } else if (strcmp(token, "D") == 0) {
                if (stack_size(&charles) >= 1) {
                    stack_push(&charles, stack_top(&charles) * 2);
                }
            } else {
                stack_push(&charles, strtoi(token));
            }
            token = strtok(NULL, " \n");
        }
    }

    int total = 0;
    while(!stack_isEmpty(&charles)){
        total += charles._top->data;
        stack_pop(&charles);
    } 
    printf("%d", total);
    return 0;
}
