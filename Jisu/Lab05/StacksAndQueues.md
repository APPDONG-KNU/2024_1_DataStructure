# Stacks and Queues
## Stack
Last-In-First-Out(LIFO)
* insertion: push
* deletion: pop(```return stack[top--];```)
* end: top

top을 처음에 -1로 하여 top<0이면 비어 있음.

```stack[++top] = item```

## Queues
Fitst-In-First-Out(FIFO)
* front
* rear

front == rear -> empty
rear == MAX_QUEUE_SIZE - 1 -> full

## A Mazing Problem
