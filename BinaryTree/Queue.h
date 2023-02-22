//#pragma once
//
// Created by ΩØ–À”Ó on 13/2/2023.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//«∞÷√…˘√˜
struct BinaryTree;

typedef struct BinaryTree* QDataType;
typedef struct QNode
{
    QDataType data;
    struct QNode* next;
}QNode;

typedef struct Queue
{
    QNode* head;
    QNode* tail;
}Queue;

void QueueInit(Queue* pq);
void QueueDestroy(Queue* pq);

void QueuePUsh(Queue* pq, QDataType x);
void QueuePop(Queue* pq);
QDataType QUeueBegin(Queue* pq);
QDataType QUeueLast(Queue* pq);


int QueueSize(Queue* pq);
bool QueueIsEmpty(Queue* pq);



















#endif //QUEUE_QUEUE_H
















//#endif //QUEUE_QUEUE_H