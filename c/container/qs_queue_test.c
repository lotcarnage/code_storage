/* (c) 2021 @lot_carnage */

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <qs_queue.h>

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
	QSQueue qsq[1];
	QSQueueElement buffer_for_elements[5];
	QSQueueElement buffer_for_sort[5];
	QSQueue_Construct(
		qsq, buffer_for_elements, buffer_for_sort, 5);

	/* Queueu API test */
	QSQueue_Enqueue(qsq, 1);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 1);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 1);
	QSQueue_Enqueue(qsq, 2);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 1);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 2);
	QSQueue_Enqueue(qsq, 3);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 2);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 2);
	QSQueue_Enqueue(qsq, 4);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 2);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 3);
	QSQueue_Enqueue(qsq, 5);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 3);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 3);
	TEST_ASSERT(QSQueue_Dequeue(qsq) == 1);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 3);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 4);
	TEST_ASSERT(QSQueue_Dequeue(qsq) == 2);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 4);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 4);
	TEST_ASSERT(QSQueue_Dequeue(qsq) == 3);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 4);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 5);
	TEST_ASSERT(QSQueue_Dequeue(qsq) == 4);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 5);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 5);
	TEST_ASSERT(QSQueue_Dequeue(qsq) == 5);

	QSQueue_Enqueue(qsq, 1);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 1);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 1);
	QSQueue_Enqueue(qsq, 3);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 1);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 3);
	QSQueue_Enqueue(qsq, 4);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 3);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 3);
	QSQueue_Enqueue(qsq, 5);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 3);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 4);
	QSQueue_Enqueue(qsq, 2);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 3);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 3);

	TEST_ASSERT(QSQueue_Dequeue(qsq) == 1);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 3);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 4);
	TEST_ASSERT(QSQueue_Dequeue(qsq) == 3);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 4);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 4);
	TEST_ASSERT(QSQueue_Dequeue(qsq) == 4);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 2);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 5);
	TEST_ASSERT(QSQueue_Dequeue(qsq) == 5);
	TEST_ASSERT(QSQueue_GetLowerMedian(qsq) == 2);
	TEST_ASSERT(QSQueue_GetUpperMedian(qsq) == 2);
	TEST_ASSERT(QSQueue_Dequeue(qsq) == 2);

	/* Check API test */
	TEST_ASSERT(QSQueue_IsEnqueueable(qsq));
	TEST_ASSERT(!QSQueue_IsDequeueable(qsq));
	QSQueue_Enqueue(qsq, 1);
	TEST_ASSERT(QSQueue_IsEnqueueable(qsq));
	TEST_ASSERT(QSQueue_IsDequeueable(qsq));
	QSQueue_Enqueue(qsq, 2);
	TEST_ASSERT(QSQueue_IsEnqueueable(qsq));
	TEST_ASSERT(QSQueue_IsDequeueable(qsq));
	QSQueue_Enqueue(qsq, 3);
	TEST_ASSERT(QSQueue_IsEnqueueable(qsq));
	TEST_ASSERT(QSQueue_IsDequeueable(qsq));
	QSQueue_Enqueue(qsq, 4);
	TEST_ASSERT(QSQueue_IsEnqueueable(qsq));
	TEST_ASSERT(QSQueue_IsDequeueable(qsq));
	QSQueue_Enqueue(qsq, 5);
	TEST_ASSERT(!QSQueue_IsEnqueueable(qsq));
	TEST_ASSERT(QSQueue_IsDequeueable(qsq));

	QSQueue_Destruct(qsq);

	return s_test_result;
}
