/**
 * Implementasi ADT Queue (Queue menggunakan Linked List)
 * 
 * Dibuat dan ditulis oleh Bayu Laksana
 * -- tanggal 22 Januari 2019
 * Struktur Data 2020
 * Implementasi untuk bahasa C
 * 
 * !!NOTE!!
 * cara menggunakan lihat pada fungsi main()
 */

 #include <stdlib.h>
 #include <stdbool.h>
 #include <stdio.h>
 
 /* Struktur Node */
 
 typedef struct queueNode_t {
     int data;
     struct queueNode_t *next;
 } QueueNode;
 
 /* Struktur ADT Queue */
 
 typedef struct queue_t {
     QueueNode   *_front, 
                 *_rear;
     unsigned _size;
 } Queue;
 
 /* Function prototype */
 
 void queue_init(Queue *queue);
 bool queue_isEmpty(Queue *queue);
 void queue_push(Queue *queue, int value);
 void queue_pop(Queue *queue);
 int  queue_front(Queue *queue);
 int  queue_size(Queue *queue);
 
 /* Function definition below */
 
 void queue_init(Queue *queue)
 {
     queue->_size = 0;
     queue->_front = NULL;
     queue->_rear = NULL;
 }
 
 bool queue_isEmpty(Queue *queue) {
     return (queue->_front == NULL && queue->_rear == NULL);
 }
 
 void queue_push(Queue *queue, int value)
 {
     QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
     if (newNode) {
         queue->_size++;
         newNode->data = value;
         newNode->next = NULL;
         
         if (queue_isEmpty(queue))                 
             queue->_front = queue->_rear = newNode;
         else {
             queue->_rear->next = newNode;
             queue->_rear = newNode;
         }
     }
 }
 
 void queue_pop(Queue *queue)
 {
     if (!queue_isEmpty(queue)) {
         QueueNode *temp = queue->_front;
         queue->_front = queue->_front->next;
         free(temp);
         
         if (queue->_front == NULL)
             queue->_rear = NULL;
         queue->_size--;
     }
 }
 
 int queue_front(Queue *queue)
 {
     if (!queue_isEmpty(queue)) {
         return (queue->_front->data);
     }
     return (int)0;
 }
 
 int queue_size(Queue *queue) {
     return queue->_size;
 }
 
 int main(int argc, char const *argv[]) {
     Queue burger_line;
     queue_init(&burger_line);

     int X, Y, Z;
     scanf("%d%d%d", &X, &Y, &Z);
     int requeue = 0, me_borgor = 0;
     for (int i = 0; i < X; i++){
        int temp;
        scanf("%d", &temp);
        queue_push(&burger_line, temp);
     }
     
     for (int i = 1; !queue_isEmpty(&burger_line); i++){
        if (Y<=0) break;
        if (!(i%Z)) {
            int temp = queue_front(&burger_line);
            queue_pop(&burger_line);
            queue_push(&burger_line, temp);
            requeue++;
        } else {
            Y -= queue_front(&burger_line);
            queue_pop(&burger_line);
        }
     }
     (queue_isEmpty(&burger_line) && Y >= 0) ? (me_borgor = 1) : (me_borgor = 0);
     printf("%d %s", requeue, ((me_borgor)?"Yes Dapat burger gratis!!!" : "NOO tidak Dapat :("));
     return 0;
 }