#include <stdio.h>
#include <stdlib.h>

typedef struct snode_t {
    int data;
    struct snode_t *next;
} SListNode;

typedef struct slist_t {
    unsigned _size;
    int front;
    SListNode *_head;
} SinglyList;

void slist_init(SinglyList *list){
    list->_head = NULL;
    list->_size = 0;
    list->front = 0;
}

int slist_isEmpty(SinglyList *list) {
    return (list->_head == NULL);
}

void slist_pushBack(SinglyList *list, int value) {
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        newNode->data = value;
        newNode->next = NULL;
        
        if (slist_isEmpty(list)) {
            list->_head = newNode;
            list->front = value;
        } else {
            SListNode *temp = list->_head;
            while (temp->next != NULL) 
                temp = temp->next;
            temp->next = newNode;
        }
    }
}

void slist_popFront(SinglyList *list) {
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        list->_head = list->_head->next;
        free(temp);
        list->_size--;

        if (list->_head)
            list->front = list->_head->data;
        else
            list->front = -1;
    } 
}

int main(){
    int N; 
    scanf("%d", &N);
    SinglyList original, tukaran;
    slist_init(&original); slist_init(&tukaran);

    for (int i = 0; i < N; i++){
        int temp; scanf("%d", &temp);
        slist_pushBack(&original, temp);
    }

    for (int i = 0; i < N / 2; i++) {
        int temp = original.front;
        slist_popFront(&original);
        int temp2 = original.front;
        slist_popFront(&original);
    
        slist_pushBack(&tukaran, temp2);
        slist_pushBack(&tukaran, temp);
    } if ((N%2)) {
        slist_pushBack(&tukaran, original.front);
        slist_popFront(&original);
    }

    while(!slist_isEmpty(&tukaran)){
        printf("%d ", tukaran.front);
        slist_popFront(&tukaran);
    } printf("\n");
}
