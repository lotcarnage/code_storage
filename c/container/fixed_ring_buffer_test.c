/* (c) 2021 @lot_carnage */

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <fixed_ring_buffer.h>

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
	FixedRingBuffer frb[1];
	FixedRingBufferPayload payload_buffer[4];
	FixedRingBufferPayload actual_payload;
	FixedRingBuffer_Construct(frb, payload_buffer, 4);

	/* Queueu API test */
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)1U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)2U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)3U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)4U);
	TEST_ASSERT(FixedRingBuffer_Dequeue(frb) == (FixedRingBufferPayload)1U);
	TEST_ASSERT(FixedRingBuffer_Dequeue(frb) == (FixedRingBufferPayload)2U);
	TEST_ASSERT(FixedRingBuffer_Dequeue(frb) == (FixedRingBufferPayload)3U);
	TEST_ASSERT(FixedRingBuffer_Dequeue(frb) == (FixedRingBufferPayload)4U);

	/* Stack API test */
	FixedRingBuffer_Push(frb, (FixedRingBufferPayload)1U);
	FixedRingBuffer_Push(frb, (FixedRingBufferPayload)2U);
	FixedRingBuffer_Push(frb, (FixedRingBufferPayload)3U);
	FixedRingBuffer_Push(frb, (FixedRingBufferPayload)4U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)4U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)3U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)2U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)1U);

	/* Mix API test */
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)1U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)2U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)3U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)4U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)4U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)3U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)2U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)1U);

	FixedRingBuffer_Push(frb, (FixedRingBufferPayload)1U);
	FixedRingBuffer_Push(frb, (FixedRingBufferPayload)2U);
	FixedRingBuffer_Push(frb, (FixedRingBufferPayload)3U);
	FixedRingBuffer_Push(frb, (FixedRingBufferPayload)4U);
	TEST_ASSERT(FixedRingBuffer_Dequeue(frb) == (FixedRingBufferPayload)1U);
	TEST_ASSERT(FixedRingBuffer_Dequeue(frb) == (FixedRingBufferPayload)2U);
	TEST_ASSERT(FixedRingBuffer_Dequeue(frb) == (FixedRingBufferPayload)3U);
	TEST_ASSERT(FixedRingBuffer_Dequeue(frb) == (FixedRingBufferPayload)4U);

	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)1U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)2U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)3U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)4U);
	TEST_ASSERT(FixedRingBuffer_Dequeue(frb) == (FixedRingBufferPayload)1U);
	TEST_ASSERT(FixedRingBuffer_Dequeue(frb) == (FixedRingBufferPayload)2U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)5U);
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)6U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)6U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)5U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)4U);
	TEST_ASSERT(FixedRingBuffer_Pop(frb) == (FixedRingBufferPayload)3U);

	/* Check API test */
	TEST_ASSERT(FixedRingBuffer_IsEnqueueable(frb));
	TEST_ASSERT(!FixedRingBuffer_IsDequeueable(frb));
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)1U);
	TEST_ASSERT(FixedRingBuffer_IsEnqueueable(frb));
	TEST_ASSERT(FixedRingBuffer_IsDequeueable(frb));
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)2U);
	TEST_ASSERT(FixedRingBuffer_IsEnqueueable(frb));
	TEST_ASSERT(FixedRingBuffer_IsDequeueable(frb));
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)3U);
	TEST_ASSERT(FixedRingBuffer_IsEnqueueable(frb));
	TEST_ASSERT(FixedRingBuffer_IsDequeueable(frb));
	FixedRingBuffer_Enqueue(frb, (FixedRingBufferPayload)4U);
	TEST_ASSERT(!FixedRingBuffer_IsEnqueueable(frb));
	TEST_ASSERT(FixedRingBuffer_IsDequeueable(frb));

	FixedRingBuffer_Destruct(frb);

	return s_test_result;
}
