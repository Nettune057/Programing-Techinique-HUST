#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUESTS 100

// Request struct to represent a single request
typedef struct {
    char name[50];
    char ip_address[20];
    char content[100];
    int execution_time;
} Request;

// Queue struct to represent the queue
typedef struct {
    Request requests[MAX_REQUESTS];
    int front, rear;
} Queue;

// Function prototypes
void initQueue(Queue *queue);
int isQueueEmpty(Queue *queue);
int isQueueFull(Queue *queue);
void enqueue(Queue *queue, Request request);
Request dequeue(Queue *queue);
void displayQueue(Queue *queue);

int main() {
    Queue queue;
    initQueue(&queue);

    int choice;
    Request request;

    do {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue Request\n");
        printf("2. Dequeue Request\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter Request Details:\n");
                printf("Request Name: ");
                scanf("%s", request.name);
                printf("IP Address: ");
                scanf("%s", request.ip_address);
                printf("Content: ");
                scanf("%s", request.content);
                printf("Execution Time: ");
                scanf("%d", &request.execution_time);
                enqueue(&queue, request);
                break;
            case 2:
                request = dequeue(&queue);
                if (strcmp(request.name, "") != 0) {
                    printf("\nDequeued Request:\n");
                    printf("Request Name: %s\n", request.name);
                    printf("IP Address: %s\n", request.ip_address);
                    printf("Content: %s\n", request.content);
                    printf("Execution Time: %d\n", request.execution_time);
                }
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to initialize the queue
void initQueue(Queue *queue) {
    queue->front = 0;
    queue->rear = -1;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue *queue) {
    return (queue->front > queue->rear);
}

// Function to check if the queue is full
int isQueueFull(Queue *queue) {
    return (queue->rear == MAX_REQUESTS - 1);
}

// Function to enqueue a request
void enqueue(Queue *queue, Request request) {
    if (isQueueFull(queue)) {
        printf("Queue is full. Cannot enqueue request.\n");
        return;
    }

    queue->rear++;
    queue->requests[queue->rear] = request;
}

// Function to dequeue a request
Request dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue request.\n");
        Request emptyRequest = {"", "", "", 0};
        return emptyRequest;
    }

    Request dequeuedRequest = queue->requests[queue->front];
    queue->front++;
    return dequeuedRequest;
}

// Function to display the requests in the queue
void displayQueue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Requests in the queue:\n");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("Request Name: %s\n", queue->requests[i].name);
        printf("IP Address: %s\n", queue->requests[i].ip_address);
        printf("Content: %s\n", queue->requests[i].content);
        printf("Execution Time: %d\n\n", queue->requests[i].execution_time);
    }
}