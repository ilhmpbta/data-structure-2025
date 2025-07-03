#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
    unsigned size;
} Stack;

void stack_init(Stack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

int stack_is_empty(Stack *stack) {
    return stack->top == NULL;
}

void stack_push(Stack *stack, char value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) return;

    new_node->data = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

void print_stack_pop(Stack *stack) {
    if (!stack_is_empty(stack)) {
        Node *temp = stack->top;
        printf("%c", temp->data);
        stack->top = temp->next;
        free(temp);
        stack->size--;
    }
}

int cek_vokal(char c) {
    return strchr("aiueoAIUEO", c) != NULL;
}

int main() {
    char input_str[101];
    scanf("%s", input_str);

    Stack stack;
    stack_init(&stack);

    for (int i = 0; input_str[i] != '\0'; i++) {
        stack_push(&stack, input_str[i]);
        if (cek_vokal(input_str[i])) {
            stack_push(&stack, input_str[i]);
        }
    }

    while (!stack_is_empty(&stack)) print_stack_pop(&stack);
    printf("\n");

    return 0;
}
