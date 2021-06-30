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
	MedianQueue bhq[1];
	MedianQueueElement buffer_for_elements[5];
	uint32_t heap_indices[5];
	uint32_t heap[5];
	MedianQueue_Construct(
		bhq, buffer_for_elements, heap_indices, heap, 5);

	/* Queueu API test */
	MedianQueue_Enqueue(bhq, 1);
	TEST_ASSERT(MedianQueue_GetLowerMedian(bhq) == 1);
	TEST_ASSERT(MedianQueue_GetUpperMedian(bhq) == 1);
	MedianQueue_Enqueue(bhq, 2);
	TEST_ASSERT(MedianQueue_GetLowerMedian(bhq) == 1);
	TEST_ASSERT(MedianQueue_GetUpperMedian(bhq) == 2);
	MedianQueue_Enqueue(bhq, 3);
	TEST_ASSERT(MedianQueue_GetLowerMedian(bhq) == 2);
	TEST_ASSERT(MedianQueue_GetUpperMedian(bhq) == 2);
	MedianQueue_Enqueue(bhq, 4);
	TEST_ASSERT(MedianQueue_GetLowerMedian(bhq) == 2);
	TEST_ASSERT(MedianQueue_GetUpperMedian(bhq) == 3);
	MedianQueue_Enqueue(bhq, 5);
	TEST_ASSERT(MedianQueue_GetLowerMedian(bhq) == 3);
	TEST_ASSERT(MedianQueue_GetUpperMedian(bhq) == 3);
	TEST_ASSERT(MedianQueue_Dequeue(bhq) == 1);
	TEST_ASSERT(MedianQueue_GetLowerMedian(bhq) == 3);
	TEST_ASSERT(MedianQueue_GetUpperMedian(bhq) == 4);
	TEST_ASSERT(MedianQueue_Dequeue(bhq) == 2);
	TEST_ASSERT(MedianQueue_GetLowerMedian(bhq) == 4);
	TEST_ASSERT(MedianQueue_GetUpperMedian(bhq) == 4);
	TEST_ASSERT(MedianQueue_Dequeue(bhq) == 3);
	TEST_ASSERT(MedianQueue_GetLowerMedian(bhq) == 4);
	TEST_ASSERT(MedianQueue_GetUpperMedian(bhq) == 5);
	TEST_ASSERT(MedianQueue_Dequeue(bhq) == 4);
	TEST_ASSERT(MedianQueue_GetLowerMedian(bhq) == 5);
	TEST_ASSERT(MedianQueue_GetUpperMedian(bhq) == 5);
	TEST_ASSERT(MedianQueue_Dequeue(bhq) == 5);


	/* Check API test */
	TEST_ASSERT(MedianQueue_IsEnqueueable(bhq));
	TEST_ASSERT(!MedianQueue_IsDequeueable(bhq));
	MedianQueue_Enqueue(bhq, 1);
	TEST_ASSERT(MedianQueue_IsEnqueueable(bhq));
	TEST_ASSERT(MedianQueue_IsDequeueable(bhq));
	MedianQueue_Enqueue(bhq, 2);
	TEST_ASSERT(MedianQueue_IsEnqueueable(bhq));
	TEST_ASSERT(MedianQueue_IsDequeueable(bhq));
	MedianQueue_Enqueue(bhq, 3);
	TEST_ASSERT(MedianQueue_IsEnqueueable(bhq));
	TEST_ASSERT(MedianQueue_IsDequeueable(bhq));
	MedianQueue_Enqueue(bhq, 4);
	TEST_ASSERT(MedianQueue_IsEnqueueable(bhq));
	TEST_ASSERT(MedianQueue_IsDequeueable(bhq));
	MedianQueue_Enqueue(bhq, 5);
	TEST_ASSERT(!MedianQueue_IsEnqueueable(bhq));
	TEST_ASSERT(MedianQueue_IsDequeueable(bhq));

	MedianQueue_Destruct(bhq);

	return s_test_result;
}
