#include "queue.h"

//==============================================================================
//  ��������
//==============================================================================
void Queue_Init(QUEUE_HandleTypeDef * hqueue, unsigned char * buffer, unsigned int len);
void Queue_Clear(QUEUE_HandleTypeDef * hqueue);
unsigned int Queue_Count(QUEUE_HandleTypeDef * hqueue);
QUEUE_StatusTypeDef Queue_Push(QUEUE_HandleTypeDef * hqueue, unsigned char data);
unsigned int Queue_Push_Array(QUEUE_HandleTypeDef * hqueue, unsigned char * pdatas, unsigned int len);

//==============================================================================
//  �������ƣ�
//  �������ܣ�
//  ����������
//  �������أ�
//==============================================================================
void Queue_Init(QUEUE_HandleTypeDef * hqueue, unsigned char * buffer, unsigned int len)
{
    hqueue->buffer = buffer;
    hqueue->buffer_length = len;
    Queue_Clear(hqueue);
}

//==============================================================================
//  �������ƣ�
//  �������ܣ�
//  ����������
//  �������أ�
//==============================================================================
void Queue_Clear(QUEUE_HandleTypeDef * hqueue)
{
    hqueue->head = 0;
    hqueue->tail = 0;
}

//==============================================================================
//  �������ƣ�Queue_Count
//  �������ܣ���ȡ���������ݸ���
//  ����������
//  �������أ�
//==============================================================================
unsigned int Queue_Count(QUEUE_HandleTypeDef * hqueue)
{
    if(hqueue->head <= hqueue->tail)
    {
        return (unsigned int)(hqueue->tail - hqueue->head);
    }
    else
    {
        return (unsigned int)(hqueue->buffer_length + hqueue->tail - hqueue->head);
    }
}

//==============================================================================
//  �������ƣ�Queue_Push
//  �������ܣ�ѹ�����ݵ�������
//  ����������
//  �������أ�
//==============================================================================
QUEUE_StatusTypeDef Queue_Push(QUEUE_HandleTypeDef * hqueue, unsigned char data)
{
    unsigned int tmp = (hqueue->tail + 1) % hqueue->buffer_length;

    if(tmp == hqueue->head)
    {
        return QUEUE_OVERLOAD;
    }
    else
    {
        hqueue->buffer[hqueue->tail] = data;
        hqueue->tail = tmp;
        return QUEUE_OK;
    }
}

//==============================================================================
//  �������ƣ�Queue_Push_Array
//  �������ܣ�ѹ��һ�����ݵ�������
//  ����������
//  �������أ��ɹ�ѹ��������ݵ�����
//==============================================================================
unsigned int Queue_Push_Array(QUEUE_HandleTypeDef * hqueue, unsigned char * pdatas, unsigned int len)
{
    unsigned int i;
    for(i=0; i<len; i++)
    {
        if(Queue_Push(hqueue,pdatas[i]) == QUEUE_OVERLOAD)
        {
            break;
        }
    }
    return i;
}

