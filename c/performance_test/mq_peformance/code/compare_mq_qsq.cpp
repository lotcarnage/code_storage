/* (c) 2021 @lot_carnage */

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <median_queue.h>
#include <qs_queue.h>

#include <chrono>

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <random_numbers.h>

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

#define MAX_WINDOW_SIZE	(200)

void execute_median_queue_sequence(uint32_t n, int32_t (*output_median_buffer)[NUMBER_OF_random_numbers_ELEMENTS])
{
	MedianQueue mq[1];
	MedianQueueElement buffer_for_elements[MAX_WINDOW_SIZE];
	uint32_t heap_indices[MAX_WINDOW_SIZE];
	uint32_t heap[MAX_WINDOW_SIZE];
	uint32_t i;

	MedianQueue_Construct(
		mq, buffer_for_elements, heap_indices, heap, n);
	for (i = 0; i < NUMBER_OF_random_numbers_ELEMENTS; i++) {
		if (!MedianQueue_IsEnqueueable(mq)) {
			(void)MedianQueue_Dequeue(mq);
		}
		MedianQueue_Enqueue(mq, random_numbers[i]);
		(*output_median_buffer)[i] = MedianQueue_GetUpperMedian(mq);
	}
	MedianQueue_Destruct(mq);
	return;
}

void execute_qs_queue_sequence(uint32_t n, int32_t (*output_median_buffer)[NUMBER_OF_random_numbers_ELEMENTS])
{
	QSQueue qsq[1];
	QSQueueElement buffer_for_elements[MAX_WINDOW_SIZE];
	QSQueueElement buffer_for_sort[MAX_WINDOW_SIZE];
	uint32_t i;

	QSQueue_Construct(
		qsq, buffer_for_elements, buffer_for_sort, n);
	for (i = 0; i < NUMBER_OF_random_numbers_ELEMENTS; i++) {
		if (!QSQueue_IsEnqueueable(qsq)) {
			(void)QSQueue_Dequeue(qsq);
		}
		QSQueue_Enqueue(qsq, random_numbers[i]);
		(*output_median_buffer)[i] = QSQueue_GetUpperMedian(qsq);
	}
	QSQueue_Destruct(qsq);
	return;
}

typedef void (*ProcessFunction)(uint32_t n, int32_t (*output_median_buffer)[NUMBER_OF_random_numbers_ELEMENTS]);

uint64_t record_time_millisecond(
	ProcessFunction process,
	uint32_t n, int32_t (*output_median_buffer)[NUMBER_OF_random_numbers_ELEMENTS])
{
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point finish;
	start = std::chrono::system_clock::now();
	process(n, output_median_buffer);
	finish = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
}


int32_t output_median_buffer_for_mq[NUMBER_OF_random_numbers_ELEMENTS];
int32_t output_median_buffer_for_qsq[NUMBER_OF_random_numbers_ELEMENTS];

int main(int argc, char* argv[])
{
	uint64_t mq_time[MAX_WINDOW_SIZE];
	uint64_t qsq_time[MAX_WINDOW_SIZE];
	uint32_t n;

	for (n = 1; n < MAX_WINDOW_SIZE; n++) {
		mq_time[n - 1] = record_time_millisecond(execute_median_queue_sequence, n, &output_median_buffer_for_mq);
		qsq_time[n - 1] = record_time_millisecond(execute_qs_queue_sequence, n, &output_median_buffer_for_qsq);
#if 0
		{
			uint32_t i;
			for (i = 0; i < NUMBER_OF_random_numbers_ELEMENTS; i++) {
				if (output_median_buffer_for_mq[i] != output_median_buffer_for_qsq[i]) {
					TEST_ASSERT(0);
				}
			}
		}
#endif
		printf("N=%3u, MQ:%8llu, QS:%8llu\n", n, mq_time[n - 1], qsq_time[n - 1]);
	}

	return s_test_result;
}
