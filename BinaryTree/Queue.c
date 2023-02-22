//
// Created by 蒋兴宇 on 13/2/2023.
//

#include "Queue.h"

void QueueInit(Queue* pq)
{
    assert(pq);
    pq->head = NULL;
    pq->tail = NULL;
}
void QueueDestroy(Queue* pq)
{
    assert(pq);
    QNode* cur = pq->head;
    while (cur != NULL)
    {
        QNode* next = cur->next;
        free(cur);
        cur = next;
    }
    pq->head = pq->tail = NULL;
}

void QueuePUsh(Queue* pq, QDataType x)
{
    QNode* newnode = (QNode*)malloc(sizeof(QNode));
    newnode->next = NULL;
    newnode->data = x;

    if (pq->head == NULL)
    {
        pq->head = pq->tail = newnode;
    }
    else
    {
        pq->tail->next = newnode;
        pq->tail = newnode;
    }
}
void QueuePop(Queue* pq)
{
    assert(pq);
    assert(!QueueIsEmpty(pq));

    QNode* next = pq->head->next;
    free(pq->head);
    pq->head = next;
    //防止pop到队列为空时，tail成为野指针
    if (pq->head == NULL)
    {
        pq->tail = NULL;
    }
}
QDataType QUeueBegin(Queue* pq)
{
    assert(pq);
    assert(!QueueIsEmpty(pq));
    return pq->head->data;
}
QDataType QUeueLast(Queue* pq)
{
    assert(pq);
    assert(!QueueIsEmpty(pq));
    return pq->tail->data;
}


int QueueSize(Queue* pq)
{
    assert(pq);
    int size = 0;
    QNode* cur = pq->head;
    while (cur != NULL)
    {
        cur = cur->next;
        size++;
    }
    return size;
}
bool QueueIsEmpty(Queue* pq)
{
    assert(pq);
    return pq->head == NULL;
}