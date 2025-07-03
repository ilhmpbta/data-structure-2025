#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct queueNode_t {
    int data;
    struct queueNode_t *next;
} QueueNode;

typedef struct queue_t {
    QueueNode *_front;
    QueueNode *_rear;
    unsigned _size;
} Queue;

void queue_init(Queue *queue) {
    queue->_size = 0;
    queue->_front = queue->_rear = NULL;
}

bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL);
}

void enqueue(Queue *queue, int value) {
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode->data = value;
    newNode->next = NULL;

    if (queue_isEmpty(queue)) {
        queue->_front = queue->_rear = newNode;
    } else {
        queue->_rear->next = newNode;
        queue->_rear = newNode;
    }

    queue->_size++;
}

void dequeue(Queue *queue) {
    if (!queue_isEmpty(queue)) {
        QueueNode *temp = queue->_front;
        queue->_front = queue->_front->next;
        if (queue->_front == NULL) {
            queue->_rear = NULL;
        }
        free(temp);
        queue->_size--;
    }
}

int queue_front(Queue *queue) {
    if (!queue_isEmpty(queue)) {
        return queue->_front->data;
    }
    return 0;
}

unsigned queue_size(Queue *queue) {
    return queue->_size;
}

int main(){
    Queue antrean;
    queue_init(&antrean);
    int N; 
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        int temp;
        scanf("%d", &temp);
        enqueue(&antrean, temp);
    }

    int S;
    scanf("%d", &S);
    for (int i = 0; i < S; i++){
        char temp[9];
        scanf("%s", temp);
        if (strcmp("BERHASIL", temp) == 0) {
            dequeue(&antrean);
        } else if (strcmp("GAGAL", temp) == 0) {
            int temp = queue_front(&antrean);
            dequeue(&antrean);
            enqueue(&antrean, temp);
        }
    }
    if(queue_isEmpty(&antrean)) printf("KOSONG");
    else {
        while (!queue_isEmpty(&antrean)){
            printf("%d ", queue_front(&antrean));
            dequeue(&antrean);
        }
    } printf("\n");

    return 0;
}