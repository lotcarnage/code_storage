/* (c) 2021 @lot_carnage */

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <fixed_size_ring_buffer.h>

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
	FixedSizeRingBuffer frb[1];
	FixedSizeRingBufferElement buffer_for_elements[4];
	FixedSizeRingBuffer_Construct(frb, buffer_for_elements, 4);

	/* Queueu API test */
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)1U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)2U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)3U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)4U);
	TEST_ASSERT(FixedSizeRingBuffer_Dequeue(frb) == (FixedSizeRingBufferElement)1U);
	TEST_ASSERT(FixedSizeRingBuffer_Dequeue(frb) == (FixedSizeRingBufferElement)2U);
	TEST_ASSERT(FixedSizeRingBuffer_Dequeue(frb) == (FixedSizeRingBufferElement)3U);
	TEST_ASSERT(FixedSizeRingBuffer_Dequeue(frb) == (FixedSizeRingBufferElement)4U);

	/* Stack API test */
	FixedSizeRingBuffer_Push(frb, (FixedSizeRingBufferElement)1U);
	FixedSizeRingBuffer_Push(frb, (FixedSizeRingBufferElement)2U);
	FixedSizeRingBuffer_Push(frb, (FixedSizeRingBufferElement)3U);
	FixedSizeRingBuffer_Push(frb, (FixedSizeRingBufferElement)4U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)4U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)3U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)2U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)1U);

	/* Mix API test */
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)1U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)2U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)3U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)4U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)4U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)3U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)2U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)1U);

	FixedSizeRingBuffer_Push(frb, (FixedSizeRingBufferElement)1U);
	FixedSizeRingBuffer_Push(frb, (FixedSizeRingBufferElement)2U);
	FixedSizeRingBuffer_Push(frb, (FixedSizeRingBufferElement)3U);
	FixedSizeRingBuffer_Push(frb, (FixedSizeRingBufferElement)4U);
	TEST_ASSERT(FixedSizeRingBuffer_Dequeue(frb) == (FixedSizeRingBufferElement)1U);
	TEST_ASSERT(FixedSizeRingBuffer_Dequeue(frb) == (FixedSizeRingBufferElement)2U);
	TEST_ASSERT(FixedSizeRingBuffer_Dequeue(frb) == (FixedSizeRingBufferElement)3U);
	TEST_ASSERT(FixedSizeRingBuffer_Dequeue(frb) == (FixedSizeRingBufferElement)4U);

	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)1U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)2U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)3U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)4U);
	TEST_ASSERT(FixedSizeRingBuffer_Dequeue(frb) == (FixedSizeRingBufferElement)1U);
	TEST_ASSERT(FixedSizeRingBuffer_Dequeue(frb) == (FixedSizeRingBufferElement)2U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)5U);
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)6U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)6U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)5U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)4U);
	TEST_ASSERT(FixedSizeRingBuffer_Pop(frb) == (FixedSizeRingBufferElement)3U);

	/* Check API test */
	TEST_ASSERT(FixedSizeRingBuffer_IsEnqueueable(frb));
	TEST_ASSERT(!FixedSizeRingBuffer_IsDequeueable(frb));
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)1U);
	TEST_ASSERT(FixedSizeRingBuffer_IsEnqueueable(frb));
	TEST_ASSERT(FixedSizeRingBuffer_IsDequeueable(frb));
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)2U);
	TEST_ASSERT(FixedSizeRingBuffer_IsEnqueueable(frb));
	TEST_ASSERT(FixedSizeRingBuffer_IsDequeueable(frb));
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)3U);
	TEST_ASSERT(FixedSizeRingBuffer_IsEnqueueable(frb));
	TEST_ASSERT(FixedSizeRingBuffer_IsDequeueable(frb));
	FixedSizeRingBuffer_Enqueue(frb, (FixedSizeRingBufferElement)4U);
	TEST_ASSERT(!FixedSizeRingBuffer_IsEnqueueable(frb));
	TEST_ASSERT(FixedSizeRingBuffer_IsDequeueable(frb));

	FixedSizeRingBuffer_Destruct(frb);

	return s_test_result;
}
