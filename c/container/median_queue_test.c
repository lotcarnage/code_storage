/* (c) 2021 @lot_carnage */

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <median_queue.h>

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*****************************************************************************
 * Macro
 *****************************************************************************/
#define TEST_ASSERT(condition)	{test_assert(condition, __LINE__);}

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
static int s_test_result = EXIT_SUCCESS;

static void test_assert(int condition, int line)
{
	if (!condition) {
		printf("Line:%5d, FAILED\n", line);
		s_test_result = EXIT_FAILURE;
	}
	return;
}

int main(int argc, char* argv[])
{
	MedianQueue mq[1];
	MedianQueueElement buffer_for_elements[5];
	uint32_t heap_indices[5];
	uint32_t heap[5];
	MedianQueue_Construct(
		mq, buffer_for_elements, heap_indices, heap, 5);

	/* Queueu API test */
	MedianQueue_Enqueue(mq, 1);
	TEST_ASSERT(MedianQueue_GetLowerMedian(mq) == 1);
	TEST_ASSERT(MedianQueue_GetUpperMedian(mq) == 1);
	MedianQueue_Enqueue(mq, 2);
	TEST_ASSERT(MedianQueue_GetLowerMedian(mq) == 1);
	TEST_ASSERT(MedianQueue_GetUpperMedian(mq) == 2);
	MedianQueue_Enqueue(mq, 3);
	TEST_ASSERT(MedianQueue_GetLowerMedian(mq) == 2);
	TEST_ASSERT(MedianQueue_GetUpperMedian(mq) == 2);
	MedianQueue_Enqueue(mq, 4);
	TEST_ASSERT(MedianQueue_GetLowerMedian(mq) == 2);
	TEST_ASSERT(MedianQueue_GetUpperMedian(mq) == 3);
	MedianQueue_Enqueue(mq, 5);
	TEST_ASSERT(MedianQueue_GetLowerMedian(mq) == 3);
	TEST_ASSERT(MedianQueue_GetUpperMedian(mq) == 3);
	TEST_ASSERT(MedianQueue_Dequeue(mq) == 1);
	TEST_ASSERT(MedianQueue_GetLowerMedian(mq) == 3);
	TEST_ASSERT(MedianQueue_GetUpperMedian(mq) == 4);
	TEST_ASSERT(MedianQueue_Dequeue(mq) == 2);
	TEST_ASSERT(MedianQueue_GetLowerMedian(mq) == 4);
	TEST_ASSERT(MedianQueue_GetUpperMedian(mq) == 4);
	TEST_ASSERT(MedianQueue_Dequeue(mq) == 3);
	TEST_ASSERT(MedianQueue_GetLowerMedian(mq) == 4);
	TEST_ASSERT(MedianQueue_GetUpperMedian(mq) == 5);
	TEST_ASSERT(MedianQueue_Dequeue(mq) == 4);
	TEST_ASSERT(MedianQueue_GetLowerMedian(mq) == 5);
	TEST_ASSERT(MedianQueue_GetUpperMedian(mq) == 5);
	TEST_ASSERT(MedianQueue_Dequeue(mq) == 5);


	/* Check API test */
	TEST_ASSERT(MedianQueue_IsEnqueueable(mq));
	TEST_ASSERT(!MedianQueue_IsDequeueable(mq));
	MedianQueue_Enqueue(mq, 1);
	TEST_ASSERT(MedianQueue_IsEnqueueable(mq));
	TEST_ASSERT(MedianQueue_IsDequeueable(mq));
	MedianQueue_Enqueue(mq, 2);
	TEST_ASSERT(MedianQueue_IsEnqueueable(mq));
	TEST_ASSERT(MedianQueue_IsDequeueable(mq));
	MedianQueue_Enqueue(mq, 3);
	TEST_ASSERT(MedianQueue_IsEnqueueable(mq));
	TEST_ASSERT(MedianQueue_IsDequeueable(mq));
	MedianQueue_Enqueue(mq, 4);
	TEST_ASSERT(MedianQueue_IsEnqueueable(mq));
	TEST_ASSERT(MedianQueue_IsDequeueable(mq));
	MedianQueue_Enqueue(mq, 5);
	TEST_ASSERT(!MedianQueue_IsEnqueueable(mq));
	TEST_ASSERT(MedianQueue_IsDequeueable(mq));

	MedianQueue_Destruct(mq);

	return s_test_result;
}
