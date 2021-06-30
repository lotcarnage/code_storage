/* (c) 2021 @lot_carnage */

/* Include guard */
#ifndef MEDIAN_QUEUE_H_INCLUDED
#define MEDIAN_QUEUE_H_INCLUDED

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
typedef int32_t MedianQueueElement;

typedef struct MedianQueue_ {
	uint32_t max_elements_count_;
	MedianQueueElement* buffer_for_elements_;
	uint32_t* buffer_for_heap_indices_;
	uint32_t* lh_heap_;
	uint32_t* rh_heap_;
	uint32_t wp_;
	uint32_t rp_;
} MedianQueue;

/*****************************************************************************
 * Variable Declaration
 *****************************************************************************/

/*****************************************************************************
 * Function Declaration
 *****************************************************************************/
void MedianQueue_Construct(
	MedianQueue* mq_object_memory,
	MedianQueueElement* buffer_for_elements,
	uint32_t* buffer_for_heap_indices,
	uint32_t* buffer_for_heap,
	uint32_t max_elements_count);

void MedianQueue_Destruct(MedianQueue* mq);

uint32_t MedianQueue_GetNumElements(const MedianQueue* mq);

uint32_t MedianQueue_GetNumBlanks(const MedianQueue* mq);

MedianQueueElement MedianQueue_GetLowerMedian(
	const MedianQueue* mq);

MedianQueueElement MedianQueue_GetUpperMedian(
	const MedianQueue* mq);

int MedianQueue_IsEnqueueable(
	const MedianQueue* mq);

int MedianQueue_IsDequeueable(
	const MedianQueue* mq);

void MedianQueue_Enqueue(
	MedianQueue* mq, MedianQueueElement element);

MedianQueueElement MedianQueue_Dequeue(
	MedianQueue* mq);

#endif /* MEDIAN_QUEUE_H_INCLUDED */
