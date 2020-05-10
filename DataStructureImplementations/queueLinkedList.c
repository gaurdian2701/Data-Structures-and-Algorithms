#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QueueNode {
	int value;
	struct QueueNode* nextNode;
}QueueNode;

typedef struct Queue {
	QueueNode* front;
	QueueNode* rear;
}Queue;

Queue* createQueue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->front = NULL;
	queue->rear  = NULL;
	return queue;
}
QueueNode* createQueueNode(int element) {
	QueueNode* queueNode = (QueueNode*)malloc(sizeof(QueueNode));

	queueNode->value = element;
	queueNode->nextNode = NULL;
	
	return queueNode;
}

void Enqueue(Queue* queue, int element) {
	QueueNode* queueNode = createQueueNode(element);

	if(queueNode == NULL) {
		printf("Error in Node creation.\n");
		return;
	}

	if(queue->rear == NULL) {
		queue->rear = queueNode;
		queue->front = queueNode;
		return;
	}
	(queue->rear)->nextNode = queueNode;
	queue->rear = queueNode;
	return;
}

void Dequeue(Queue* queue) {
	if(queue->front == NULL) {
		printf("Queue is empty. Cannot remove elements.\n");
		return;
	}

	QueueNode* deq = queue->front;
	queue->front = (queue->front)->nextNode;
	
	if(queue->front == NULL) 
		queue->rear = NULL;

	printf("Element %d is removed from queue.\n", deq->value);
	free(deq);
	return;
}

int Front(Queue* queue) {
	if(queue->front == NULL) {
		printf("Queue is empty. No elements.\n");
		return INT_MIN;
	}
	return (queue->front)->value;
}

int Rear(Queue* queue) {
	if(queue->rear == NULL) {
		printf("Queue is empty. No elements.\n");
		return INT_MIN;
	}
	return (queue->rear)->value;
}

int main() {

	int element, front, rear, response;
	Queue* queue = NULL;
	QueueNode* queueNode = NULL;

	queue = createQueue();
	if(queue == NULL) {
		printf("Error in queue creation.\n");
		return 0;
	}
operation:
	printf("\n");
	printf("1. Add elements to Queue.\n");
	printf("2. Remove elements from Queue.\n");
	printf("3. View Front of Queue.\n");
	printf("4. View Rear of Queue.\n");
	printf("5. Quit\n");
	printf("Enter your response :");
	scanf("%d", &response);

	switch(response) {
		case 1:
			printf("Enter element to add : ");
			scanf("%d", &element);
			Enqueue(queue, element);
			break;
		case 2:
			Dequeue(queue);
			break;
		case 3:
			front = Front(queue);
			if(front != INT_MIN)
				printf("Element in front is %d.\n", front);
			break;
		case 4:
			rear = Rear(queue);
			if(rear != INT_MIN)
				printf("Element in rear is %d.\n", rear);
			break;
		case 5:
			while(queue->front != NULL) {
				queueNode = queue->front;
				queue->front = (queue->front)->nextNode;
				printf("Free up node with %d.\n", queueNode->value);
				free(queueNode);
			}
			free(queue);
			return 0;
		default:
			printf("Enter a valid option.\n");
	}
	goto operation;
	return 0;
}
