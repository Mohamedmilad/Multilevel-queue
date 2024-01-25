#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define MAX_PROCESSES 60
int number_of_processes=0;
typedef struct {
    char name[20];
    int time,finishing_flag;
} Process;

typedef struct {
    Process processes[MAX_PROCESSES];
    int front, rear,time,size;
} Queue;

void initializeQueue(Queue *q,int time,int size) {
    q->front = -1;
    q->rear = -1;
    q->time=time;
    q->size=size;
}

int queueEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

int queueFull(Queue *q) {
    return (q->rear == q->size - 1);
}

void enqueue(Queue *q, Process process) {
    if (queueFull(q)) {
        printf("Queue is full\n");
    } else {
        if (queueEmpty(q)) {
            q->front = 0;
        }
        q->rear++;
        q->processes[q->rear] = process;
    }
}

Process dequeue(Queue *q) {
    Process process;
    if (queueEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        process = q->processes[q->front];
        if (q->front == q->rear) {
            // Last element
            q->front = -1;
            q->rear = -1;
        } else {
            q->front++;
        }
    }
    return process;
}

void displayQueue(Queue *q, char *queueName) {
    printf("%s Queue: ", queueName);
    if (queueEmpty(q)) {
        printf("Empty\n");
    } else {
        for (int i = q->front; i <= q->rear; i++) {
            printf("%s ", q->processes[i].name);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    Queue queue1,queue2,queue3,finishing_queue;
    initializeQueue(&queue1,8,10);
    initializeQueue(&queue2,16,20);
    initializeQueue(&queue3,INT_MAX,30);
    initializeQueue(&finishing_queue,0,MAX_PROCESSES);
    // the number written is the time of each process
    Process processes[MAX_PROCESSES] = {{"Process1",60}, {"Process2",6},{"Process3",1},{"Process4",30},{"Process5",12}};

    while (processes[number_of_processes].name[0] != '\0') {
        number_of_processes++;
    }
    // Enqueue processes to the first queue then second then 50% random in first queue or third queue then all the rest in third queue
    for (int i = 0; i < number_of_processes; i++) {
        enqueue(&queue1, processes[i]);
        if(processes[i].time>queue1.time){
            processes[i].time=processes[i].time-queue1.time;
        }
        else{
            processes[i].time=0;
            processes[i].finishing_flag=1;
            enqueue(&finishing_queue,processes[i]);
        }
        if(processes[i].time>0){
            enqueue(&queue2, processes[i]);
            if(processes[i].time>queue2.time){
            processes[i].time=processes[i].time-queue2.time;
            }
            else{
            processes[i].time=0;
            processes[i].finishing_flag=2;
            enqueue(&finishing_queue,processes[i]);
            }
        }
        if(processes[i].time>0) {
            int randomChoice = rand() % 2;
            if(randomChoice==0){
                enqueue(&queue1, processes[i]);
                if(processes[i].time>queue1.time){
                    processes[i].time=processes[i].time-queue1.time;
                }
                else{
                    processes[i].time=0;
                    processes[i].finishing_flag=3;
                    enqueue(&finishing_queue,processes[i]);
                }
            }
            else{
                enqueue(&queue3, processes[i]);
                processes[i].time=0;
                processes[i].finishing_flag=3;
                enqueue(&finishing_queue,processes[i]);
            }
            if(processes[i].time>0){
                enqueue(&queue3, processes[i]);
                processes[i].time=0;
                processes[i].finishing_flag=4;
                enqueue(&finishing_queue,processes[i]);
            }
        }
    }

    // Display initial queues
    displayQueue(&queue1, "Queue1");
    displayQueue(&queue2, "Queue2");
    displayQueue(&queue3, "Queue3");
    printf("\n");
    // finished in queue1
    for (int i = finishing_queue.front; i <= finishing_queue.rear; i++){
            if(finishing_queue.processes[i].finishing_flag==1){
            printf("%s has finished \n", finishing_queue.processes[i].name);
            }
    }
    // finished in queue2
    for (int i = finishing_queue.front; i <= finishing_queue.rear; i++){
            if(finishing_queue.processes[i].finishing_flag==2){
            printf("%s has finished \n", finishing_queue.processes[i].name);
            }
    }
    // finished in queue1 or 3
    for (int i = finishing_queue.front; i <= finishing_queue.rear; i++){
            if(finishing_queue.processes[i].finishing_flag==3){
            printf("%s has finished \n", finishing_queue.processes[i].name);
            }
    }
    // finished in queue3
    for (int i = finishing_queue.front; i <= finishing_queue.rear; i++){
            if(finishing_queue.processes[i].finishing_flag==4){
            printf("%s has finished \n", finishing_queue.processes[i].name);
            }
    }
    return 0;
}
