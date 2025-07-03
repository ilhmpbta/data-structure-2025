#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct pqueueNode_t {
    int data;
    struct pqueueNode_t *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

void pqueue_init(PriorityQueue *pqueue) {
    pqueue->_size = 0;
    pqueue->_top = NULL;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int value) {
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data = value;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (value > pqueue->_top->data) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while (temp->next != NULL && temp->next->data >= value) temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

int pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data;
    else return 0;
}

int translate(char bjorn) {
    if(bjorn == ')') return 0;
    if(bjorn == '!') return 1;
    if(bjorn == '@') return 2;
    if(bjorn == '#') return 3;
    if(bjorn == '$') return 4;
    if(bjorn == '%') return 5;
    if(bjorn == '^') return 6;
    if(bjorn == '&') return 7;
    if(bjorn == '*') return 8;
    if(bjorn == '(') return 9;
    return -1;
}

int main(){
    PriorityQueue bjorn;
    pqueue_init(&bjorn);

    int n, M; scanf("%d%d", &n, &M);
    for (int i = 0; i < n; i++) {
        char input[7]; 
        scanf("%s", input);
        int temp = 0;
        for (int j = 0; j < strlen(input); j++) {
            temp *= 10;
            temp += translate(input[j]);
        } if (temp <= M) {
            pqueue_push(&bjorn, temp);
        }
    
        while(!pqueue_isEmpty(&bjorn) && pqueue_top(&bjorn) == M){
            printf("%d ", pqueue_top(&bjorn));
            pqueue_pop(&bjorn);
            M--;
        } printf("\n");
    }
}