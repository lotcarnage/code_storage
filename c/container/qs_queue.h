/* (c) 2021 @lot_carnage */

/* Include guard */
#ifndef QS_QUEUE_H_INCLUDED
#define QS_QUEUE_H_INCLUDED

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <stdint.h>

/*****************************************************************************
 * Macro
 *****************************************************************************/

/*****************************************************************************
 * Type Declaration
 *****************************************************************************/

/*****************************************************************************
 * Type Definition
 *****************************************************************************/
typedef int32_t QSQueueElement;

typedef struct QSQueue_ {
	uint32_t max_elements_count_;
	QSQueueElement* buffer_for_elements_;
	QSQueueElement* buffer_for_sort_;
	uint32_t wp_;
	uint32_t rp_;
} QSQueue;

/*****************************************************************************
 * Variable Declaration
 *****************************************************************************/

/*****************************************************************************
 * Function Declaration
 *****************************************************************************/
void QSQueue_Construct(
	QSQueue* qsq_object_memory,
	QSQueueElement* buffer_for_elements,
	QSQueueElement* buffer_for_sort,
	uint32_t max_elements_count);

void QSQueue_Destruct(QSQueue* qsq);

uint32_t QSQueue_GetNumElements(const QSQueue* qsq);

uint32_t QSQueue_GetNumBlanks(const QSQueue* qsq);

QSQueueElement QSQueue_GetLowerMedian(
	const QSQueue* qsq);

QSQueueElement QSQueue_GetUpperMedian(
	const QSQueue* qsq);

int QSQueue_IsEnqueueable(
	const QSQueue* qsq);

int QSQueue_IsDequeueable(
	const QSQueue* qsq);

void QSQueue_Enqueue(
	QSQueue* qsq, QSQueueElement element);

QSQueueElement QSQueue_Dequeue(
	QSQueue* qsq);

#endif /* QS_QUEUE_H_INCLUDED */
