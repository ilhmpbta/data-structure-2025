#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    PQueueNode *newNode = (PQueueNode*) malloc(sizeof(PQueueNode));
    newNode->data = value;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        pqueue->_size++;
        return;
    }

    PQueueNode *temp = pqueue->_top;

    // Ascending order (default)
    if (value > pqueue->_top->data) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
        pqueue->_size++;
    } else {
        while (temp->next != NULL && temp->next->data >= value) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        pqueue->_size++;
    }
}

void pqueue_pop(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        pqueue->_size--;
        free(temp);
    }
}

int pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue)) {
        return pqueue->_top->data;
    }
    return 0;
}

unsigned pqueue_size(PriorityQueue *pqueue) {
    return pqueue->_size;
}

int main(){
    PriorityQueue varesa;
    pqueue_init(&varesa);
    int N; scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int x; scanf("%d", &x);
        pqueue_push(&varesa, x);
    }

    while (!pqueue_isEmpty(&varesa)) {
        if(pqueue_size(&varesa) <= 1) break;
        else {
            int temp1 = pqueue_top(&varesa);
            pqueue_pop(&varesa);
            int temp2 = pqueue_top(&varesa);
            pqueue_pop(&varesa);
            if(temp1 > temp2) pqueue_push(&varesa, temp1 - temp2);
            }
     } if(!pqueue_isEmpty(&varesa))printf("%d\n", pqueue_top(&varesa));
     else printf("0\n");
}