#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SListNode {
    char data;
    struct SListNode *next;
} SListNode;

typedef struct SinglyList {
    SListNode *_head;
    size_t _size;
} SinglyList;

void slist_pushFront(SinglyList *list, char value) {
    SListNode *newNode = malloc(sizeof(SListNode));
    newNode->data = value;
    newNode->next = list->_head;
    list->_head = newNode;
    list->_size++;
}

void slist_pushBack(SinglyList *list, char value) {
    SListNode *newNode = malloc(sizeof(SListNode));
    newNode->data = value;
    newNode->next = NULL;

    if (list->_head == NULL) {
        list->_head = newNode;
    } else {
        SListNode *temp = list->_head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
    list->_size++;
}

void slist_deleteFront(SinglyList *list) {
    if (list->_head == NULL) return;
    SListNode *temp = list->_head;
    list->_head = temp->next;
    free(temp);
    list->_size--;
}

void slist_deleteBack(SinglyList *list) {
    if (list->_head == NULL) return;
    if (list->_head->next == NULL) {
        free(list->_head);
        list->_head = NULL;
    } else {
        SListNode *temp = list->_head;
        while (temp->next && temp->next->next) temp = temp->next;
        free(temp->next);
        temp->next = NULL;
    }
    list->_size--;
}

int slist_isEmpty(SinglyList *list) {
    return list->_head == NULL;
}

void slist_init(SinglyList *list){
    list->_head = NULL;
    list->_size = 0;
}

int main(){
    SinglyList bbc_note;
    slist_init(&bbc_note);

    while (1){
        char perintah[10];
        scanf("%s ", perintah);

        if (strcmp("PRINT", perintah)==0) break;
        else if (strcmp("WRITE", perintah)==0){
            char temp;
            scanf("%c", &temp);
            slist_pushBack(&bbc_note, temp);
        } else if (strcmp("BACKSPACE", perintah)==0){
            slist_deleteBack(&bbc_note);
        }
    }

    while(!(slist_isEmpty(&bbc_note))){
        printf("%c", bbc_note._head->data);
        slist_deleteFront(&bbc_note);
    }
    
    return 0;
}
