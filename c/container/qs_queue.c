/* (c) 2021 @lot_carnage */

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <qs_queue.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 * Macro
 *****************************************************************************/
#define QSQUEUE_LOCAL_FALSE (1 == 0)
#define QSQUEUE_LOCAL_TRUE  (!QSQUEUE_LOCAL_FALSE)

/*****************************************************************************
 * Type Declaration
 *****************************************************************************/

/*****************************************************************************
 * Type Definition
 *****************************************************************************/

/*****************************************************************************
 * Variable Declaration
 *****************************************************************************/

/*****************************************************************************
 * Function Declaration
 *****************************************************************************/

/*****************************************************************************
 * Variable Definition
 *****************************************************************************/

/*****************************************************************************
 * Function Definition
 *****************************************************************************/
/*-------------------------------
 * Private Functions
 *-------------------------------*/
static uint32_t QSQueuePrivate_GetNumElements(
	const QSQueue* qsq)
{
	return (qsq->wp_ - qsq->rp_);
}

static int qsort_compare(const void* plhv, void* prhv)
{
	QSQueueElement lhv = *(const QSQueueElement*)plhv;
	QSQueueElement rhv = *(const QSQueueElement*)prhv;
	if (lhv < rhv) return -1;
	if (rhv < lhv) return  1;
	return 0;
}

static void QSQueuePrivate_UpdateSorted(QSQueue* qsq)
{
	uint32_t i;
	uint32_t num_elements;
	num_elements = QSQueuePrivate_GetNumElements(qsq);
	for (i = 0; i < num_elements; i++) {
		qsq->buffer_for_sort_[i] = qsq->buffer_for_elements_[(qsq->rp_ + i) % qsq->max_elements_count_];
	}
	qsort(qsq->buffer_for_sort_, num_elements, sizeof(QSQueueElement), qsort_compare);
	return;
}

/*-------------------------------
 * Public Functions
 *-------------------------------*/
void QSQueue_Construct(
	QSQueue* qsq_object_memory,
	QSQueueElement* buffer_for_elements,
	QSQueueElement* buffer_for_sort,
	uint32_t max_elements_count)
{
	QSQueue* qsq = qsq_object_memory;
	qsq->buffer_for_elements_ = buffer_for_elements;
	qsq->buffer_for_sort_ = buffer_for_sort;
	qsq->max_elements_count_ = max_elements_count;
	qsq->wp_ = 0U;
	qsq->rp_ = 0U;
	return;
}

void QSQueue_Destruct(QSQueue* qsq)
{
	(void)qsq;
	return;
}


uint32_t QSQueue_GetNumElements(const QSQueue* qsq)
{
	return QSQueuePrivate_GetNumElements(qsq);
}

uint32_t QSQueue_GetNumBlanks(const QSQueue* qsq)
{
	return (qsq->max_elements_count_ - QSQueuePrivate_GetNumElements(qsq));
}

QSQueueElement QSQueue_GetLowerMedian(const QSQueue* qsq)
{
	uint32_t num_elements = QSQueuePrivate_GetNumElements(qsq);
	uint32_t lower_median_index =
		((num_elements % 2U) != 0U)
		? num_elements / 2U
		: num_elements / 2U - 1U;
	return qsq->buffer_for_sort_[lower_median_index];
}

QSQueueElement QSQueue_GetUpperMedian(const QSQueue* qsq)
{
	uint32_t num_elements = QSQueuePrivate_GetNumElements(qsq);
	uint32_t upper_median_index = num_elements / 2U;
	return qsq->buffer_for_sort_[upper_median_index];
}

int QSQueue_IsEnqueueable(const QSQueue* qsq)
{
	return (0U < QSQueue_GetNumBlanks(qsq));
}

int QSQueue_IsDequeueable(const QSQueue* qsq)
{
	return (0U < QSQueuePrivate_GetNumElements(qsq));
}

void QSQueue_Enqueue(
	QSQueue* qsq, QSQueueElement element)
{
	uint32_t const rounded_wp = qsq->wp_ % qsq->max_elements_count_;

	/* 値をキューに入れる */
	qsq->buffer_for_elements_[rounded_wp] = element;
	qsq->wp_++;
	QSQueuePrivate_UpdateSorted(qsq);
	return;
}

QSQueueElement QSQueue_Dequeue(
	QSQueue* qsq)
{
	QSQueueElement element;
	/* キューから値を取り出す */
	element = qsq->buffer_for_elements_[qsq->rp_];
	qsq->rp_++;
	if (qsq->max_elements_count_ <= qsq->rp_) {
		qsq->wp_ -= qsq->max_elements_count_;
		qsq->rp_ -= qsq->max_elements_count_;
	}
	QSQueuePrivate_UpdateSorted(qsq);
	return element;
}
