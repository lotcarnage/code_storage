/* (c) 2021 @lot_carnage */

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <median_queue.h>

#include <stdint.h>

/*****************************************************************************
 * Macro
 *****************************************************************************/
#define MEDIANQUEUE_LOCAL_FALSE (1 == 0)
#define MEDIANQUEUE_LOCAL_TRUE  (!MEDIANQUEUE_LOCAL_FALSE)

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
static uint32_t MedianQueuePrivate_GetNumElements(
	const MedianQueue* mq)
{
	return (mq->wp_ - mq->rp_);
}

static void MedianQueuePriavte_LHUpHeap(
	MedianQueue* mq, uint32_t starting_index_in_heap)
{
	MedianQueueElement parent_value;
	MedianQueueElement current_value;
	uint32_t parent_index_in_queue;
	uint32_t current_index_in_queue;
	uint32_t parent_index_in_heap;
	uint32_t current_index_in_heap = starting_index_in_heap;
	MedianQueueElement* elements_queue = mq->buffer_for_elements_;
	uint32_t* heap = mq->lh_heap_;
	uint32_t* indices_queue = mq->buffer_for_heap_indices_;
	for (;;) {
		if (current_index_in_heap == 0U) {
			break;
		}
		current_index_in_queue = heap[current_index_in_heap];
		current_value = elements_queue[current_index_in_queue];
		parent_index_in_heap = (current_index_in_heap - 1U) / 2U;
		parent_index_in_queue = heap[parent_index_in_heap];
		parent_value = elements_queue[parent_index_in_queue];
		if (parent_value < current_value) {
			/* swap */
			heap[parent_index_in_heap] = current_index_in_queue;
			heap[current_index_in_heap] = parent_index_in_queue;
			indices_queue[parent_index_in_queue] = current_index_in_heap;
			indices_queue[current_index_in_queue] = parent_index_in_heap;
			current_index_in_heap = parent_index_in_heap;
		} else {
			break;
		}
	}
	return;
}

static int MedianQueuePriavte_LHDownHeap(
	MedianQueue* mq, uint32_t starting_index_in_heap)
{
	MedianQueueElement child_value;
	MedianQueueElement current_value;
	uint32_t child_index_in_queue;
	uint32_t current_index_in_queue;
	uint32_t child_index_in_heap;
	uint32_t current_index_in_heap = starting_index_in_heap;
	uint32_t num_elements = MedianQueuePrivate_GetNumElements(mq) / 2U;
	MedianQueueElement* elements_queue = mq->buffer_for_elements_;
	uint32_t* heap = mq->lh_heap_;
	uint32_t* indices_queue = mq->buffer_for_heap_indices_;
	int is_updated = MEDIANQUEUE_LOCAL_FALSE;

	for (;;) {
		/* Left hand child */
		child_index_in_heap = (current_index_in_heap + 1U) * 2U - 1U;
		if (num_elements <= child_index_in_heap) {
			break;
		}
		current_index_in_queue = heap[current_index_in_heap];
		current_value = elements_queue[current_index_in_queue];
		child_index_in_queue = heap[child_index_in_heap];
		child_value = elements_queue[child_index_in_queue];
		if (current_value < child_value) {
			/* swap */
			heap[child_index_in_heap] = current_index_in_queue;
			heap[current_index_in_heap] = child_index_in_queue;
			indices_queue[child_index_in_queue] = current_index_in_heap;
			indices_queue[current_index_in_queue] = child_index_in_heap;
			current_index_in_heap = child_index_in_heap;
			is_updated = MEDIANQUEUE_LOCAL_TRUE;
			continue;
		}

		/* Right hand child */
		child_index_in_heap = child_index_in_heap + 1U;
		if (num_elements <= child_index_in_heap) {
			break;
		}
		current_index_in_queue = heap[current_index_in_heap];
		current_value = elements_queue[current_index_in_queue];
		child_index_in_queue = heap[child_index_in_heap];
		child_value = elements_queue[child_index_in_queue];
		if (current_value < child_value) {
			/* swap */
			heap[child_index_in_heap] = current_index_in_queue;
			heap[current_index_in_heap] = child_index_in_queue;
			indices_queue[child_index_in_queue] = current_index_in_heap;
			indices_queue[current_index_in_queue] = child_index_in_heap;
			current_index_in_heap = child_index_in_heap;
			is_updated = MEDIANQUEUE_LOCAL_TRUE;
			continue;
		}
		break;
	}
	return is_updated;
}

static void MedianQueuePriavte_RHUpHeap(
	MedianQueue* mq, uint32_t starting_index_in_heap)
{
	MedianQueueElement parent_value;
	MedianQueueElement current_value;
	uint32_t parent_index_in_queue;
	uint32_t current_index_in_queue;
	uint32_t parent_index_in_heap;
	uint32_t current_index_in_heap = starting_index_in_heap;
	MedianQueueElement* elements_queue = mq->buffer_for_elements_;
	uint32_t* heap = mq->rh_heap_;
	uint32_t* indices_queue = mq->buffer_for_heap_indices_;
	uint32_t heap_index_offset = (mq->max_elements_count_ + 1U) / 2U;

	for (;;) {
		if (current_index_in_heap == 0U) {
			break;
		}
		current_index_in_queue = heap[current_index_in_heap];
		current_value = elements_queue[current_index_in_queue];
		parent_index_in_heap = (current_index_in_heap - 1U) / 2U;
		parent_index_in_queue = heap[parent_index_in_heap];
		parent_value = elements_queue[parent_index_in_queue];
		if (current_value < parent_value) {
			/* swap */
			heap[parent_index_in_heap] = current_index_in_queue;
			heap[current_index_in_heap] = parent_index_in_queue;
			indices_queue[parent_index_in_queue] = current_index_in_heap + heap_index_offset;
			indices_queue[current_index_in_queue] = parent_index_in_heap + heap_index_offset;
			current_index_in_heap = parent_index_in_heap;
		} else {
			break;
		}
	}
	return;
}

static int MedianQueuePriavte_RHDownHeap(
	MedianQueue* mq, uint32_t starting_index_in_heap)
{
	MedianQueueElement child_value;
	MedianQueueElement current_value;
	uint32_t child_index_in_queue;
	uint32_t current_index_in_queue;
	uint32_t child_index_in_heap;
	uint32_t current_index_in_heap = starting_index_in_heap;
	uint32_t num_elements = (MedianQueuePrivate_GetNumElements(mq) + 1U) / 2U;
	MedianQueueElement* elements_queue = mq->buffer_for_elements_;
	uint32_t* heap = mq->rh_heap_;
	uint32_t* indices_queue = mq->buffer_for_heap_indices_;
	int is_updated = MEDIANQUEUE_LOCAL_FALSE;
	uint32_t heap_index_offset = (mq->max_elements_count_ + 1U) / 2U;

	for (;;) {
		/* Left hand child */
		child_index_in_heap = (current_index_in_heap + 1U) * 2U - 1U;
		if (num_elements <= child_index_in_heap) {
			break;
		}
		current_index_in_queue = heap[current_index_in_heap];
		current_value = elements_queue[current_index_in_queue];
		child_index_in_queue = heap[child_index_in_heap];
		child_value = elements_queue[child_index_in_queue];
		if (child_value < current_value) {
			/* swap */
			heap[child_index_in_heap] = current_index_in_queue;
			heap[current_index_in_heap] = child_index_in_queue;
			indices_queue[child_index_in_queue] = current_index_in_heap + heap_index_offset;
			indices_queue[current_index_in_queue] = child_index_in_heap + heap_index_offset;
			current_index_in_heap = child_index_in_heap;
			is_updated = MEDIANQUEUE_LOCAL_TRUE;
			continue;
		}

		/* Right hand child */
		child_index_in_heap = child_index_in_heap + 1U;
		if (num_elements <= child_index_in_heap) {
			break;
		}
		current_index_in_queue = heap[current_index_in_heap];
		current_value = elements_queue[current_index_in_queue];
		child_index_in_queue = heap[child_index_in_heap];
		child_value = elements_queue[child_index_in_queue];
		if (current_value < child_value) {
			/* swap */
			heap[child_index_in_heap] = current_index_in_queue;
			heap[current_index_in_heap] = child_index_in_queue;
			indices_queue[child_index_in_queue] = current_index_in_heap + heap_index_offset;
			indices_queue[current_index_in_queue] = child_index_in_heap + heap_index_offset;
			current_index_in_heap = child_index_in_heap;
			is_updated = MEDIANQUEUE_LOCAL_TRUE;
			continue;
		}
		break;
	}
	return is_updated;
}

/*-------------------------------
 * Public Functions
 *-------------------------------*/
void MedianQueue_Construct(
	MedianQueue* mq_object_memory,
	MedianQueueElement* buffer_for_elements,
	uint32_t* buffer_for_heap_indices,
	uint32_t* buffer_for_heap,
	uint32_t max_elements_count)
{
	MedianQueue* mq = mq_object_memory;
	mq->buffer_for_elements_ = buffer_for_elements;
	mq->buffer_for_heap_indices_ = buffer_for_heap_indices;
	mq->lh_heap_ = buffer_for_heap;
	mq->rh_heap_ = buffer_for_heap + (max_elements_count / 2U);
	mq->max_elements_count_ = max_elements_count;
	mq->wp_ = 0U;
	mq->rp_ = 0U;
	return;
}

void MedianQueue_Destruct(MedianQueue* mq)
{
	(void)mq;
	return;
}


uint32_t MedianQueue_GetNumElements(const MedianQueue* mq)
{
	return MedianQueuePrivate_GetNumElements(mq);
}

uint32_t MedianQueue_GetNumBlanks(const MedianQueue* mq)
{
	return (mq->max_elements_count_ - MedianQueuePrivate_GetNumElements(mq));
}

MedianQueueElement MedianQueue_GetLowerMedian(
	const MedianQueue* mq)
{
	uint32_t num_elements = MedianQueuePrivate_GetNumElements(mq);
	uint32_t queue_index =
		((num_elements % 2U) != 0U)
		? mq->rh_heap_[0]
		: mq->lh_heap_[0];
	return mq->buffer_for_elements_[queue_index];
}

MedianQueueElement MedianQueue_GetUpperMedian(
	const MedianQueue* mq)
{
	return mq->buffer_for_elements_[mq->rh_heap_[0]];
}

int MedianQueue_IsEnqueueable(
	const MedianQueue* mq)
{
	return (0U < MedianQueue_GetNumBlanks(mq));
}

int MedianQueue_IsDequeueable(
	const MedianQueue* mq)
{
	return (0U < MedianQueuePrivate_GetNumElements(mq));
}

void MedianQueue_Enqueue(
	MedianQueue* mq, MedianQueueElement element)
{
	uint32_t num_elements = MedianQueuePrivate_GetNumElements(mq);
	/* 要素数が奇数か偶数か */
	if ((num_elements % 2U) != 0U) {
		MedianQueueElement upper_median =
			MedianQueue_GetUpperMedian(mq);
		if (upper_median < element) {
			/* RH中央値を取り出してLHへ入れる */
			uint32_t index_in_queue = mq->rh_heap_[0U];
			uint32_t last_index_in_lh_heap = num_elements / 2U;
			uint32_t rounded_wp = mq->wp_ % mq->max_elements_count_;
			uint32_t heap_index_offset = (mq->max_elements_count_ + 1U) / 2U;
			mq->lh_heap_[last_index_in_lh_heap] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = last_index_in_lh_heap;

			/* elementをRHのルートに入れる */
			mq->buffer_for_elements_[rounded_wp] = element;
			mq->buffer_for_heap_indices_[rounded_wp] = 0U + heap_index_offset;
			mq->rh_heap_[0U] = rounded_wp;
			mq->wp_++;

			/* LHの末尾を起点にUpHeap */
			MedianQueuePriavte_LHUpHeap(mq, last_index_in_lh_heap);

			/* RHのルートを起点にDownHeap */
			MedianQueuePriavte_RHDownHeap(mq, 0U);
		} else {
			uint32_t rounded_wp = mq->wp_ % mq->max_elements_count_;
			uint32_t last_index_in_lh_heap = num_elements / 2U;
			mq->buffer_for_elements_[rounded_wp] = element;
			mq->buffer_for_heap_indices_[rounded_wp] = last_index_in_lh_heap;
			/* elementをLHの末尾に入れる */
			mq->lh_heap_[last_index_in_lh_heap] = rounded_wp;
			mq->wp_++;
			/* LHの末尾を起点にUpHeap */
			MedianQueuePriavte_LHUpHeap(mq, last_index_in_lh_heap);
		}
	} else {
		uint32_t heap_index_offset = (mq->max_elements_count_ + 1U) / 2U;
		uint32_t rounded_wp = mq->wp_ % mq->max_elements_count_;
		uint32_t last_index_in_rh_heap = (num_elements + 1U) / 2U;
		mq->buffer_for_elements_[rounded_wp] = element;
		/* elementをRHの末尾に入れる */
		mq->rh_heap_[last_index_in_rh_heap] = rounded_wp;
		mq->buffer_for_heap_indices_[rounded_wp] = last_index_in_rh_heap + heap_index_offset;
		mq->wp_++;

		/* RHの末尾を起点にUpHeap */
		MedianQueuePriavte_RHUpHeap(mq, last_index_in_rh_heap);
	}
	return;
}

MedianQueueElement MedianQueue_Dequeue(
	MedianQueue* mq)
{
	MedianQueueElement element;
	uint32_t num_elements = MedianQueuePrivate_GetNumElements(mq);
	uint32_t heap_index_offset = (mq->max_elements_count_ + 1U) / 2U;
	uint32_t index_in_heap = mq->buffer_for_heap_indices_[mq->rp_];

	/* キューから値を取り出す */
	element = mq->buffer_for_elements_[mq->rp_];
	mq->rp_++;
	if (mq->max_elements_count_ <= mq->rp_) {
		mq->wp_ -= mq->max_elements_count_;
		mq->rp_ -= mq->max_elements_count_;
	}

	/* 要素数が奇数か偶数か */
	if ((num_elements % 2U) != 0U) {
		if (heap_index_offset <= index_in_heap) {
			/* RHから要素を取り出したので取り出した箇所にRHの末尾を移動する */
			uint32_t tail_index_in_heap = (num_elements + 1U) / 2U - 1U;
			index_in_heap -= heap_index_offset;
			if (index_in_heap != tail_index_in_heap) {
				uint32_t index_in_queue;
				index_in_queue = mq->rh_heap_[tail_index_in_heap];
				mq->rh_heap_[index_in_heap] = index_in_queue;
				mq->buffer_for_heap_indices_[index_in_queue] = index_in_heap + heap_index_offset;
				/* 埋めた箇所を起点にRHをDownHeap */
				if (!MedianQueuePriavte_RHDownHeap(mq, index_in_heap)) {
					/* DownHeapで変化がなかったら埋めた箇所を起点にRHをUpHeap */
					MedianQueuePriavte_RHUpHeap(mq, index_in_heap);
				}
			}
		} else {
			/* LHから要素を取り出した */
			/* 左右バランスのためにLHの取り出した箇所にRHのルートを移動する */
			uint32_t index_in_queue;
			index_in_queue = mq->rh_heap_[0];
			mq->lh_heap_[index_in_heap] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = index_in_heap;

			/* RHの要素はLHの全ての要素より大きいので、DownHeapで木が変化しない事は自明 */
			/* 埋めた箇所を起点にLHをUpHeap */
			MedianQueuePriavte_LHUpHeap(mq, index_in_heap);

			/* RHのルートに末尾を移動する。 */
			uint32_t last_index_in_rh_heap = (num_elements + 1U) / 2U - 1U;
			index_in_queue = mq->rh_heap_[last_index_in_rh_heap];
			mq->rh_heap_[0] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = 0U + heap_index_offset;
			/* RHのルートを起点にRHをDownHeap */
			MedianQueuePriavte_RHDownHeap(mq, 0U);
		}
	} else {
		if (heap_index_offset <= index_in_heap) {
			/* RHから要素を取り出した */
			/* 取り出した箇所にLHのルートを移動する */
			/* LHの要素はRHの全ての要素以下なので、DownHeapで木が変化しない事は自明 */
			index_in_heap -= heap_index_offset;
			uint32_t index_in_queue;
			index_in_queue = mq->lh_heap_[0];
			mq->rh_heap_[index_in_heap] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = index_in_heap + heap_index_offset;
			/* 埋めた箇所を起点にRHをUpHeap */
			MedianQueuePriavte_RHUpHeap(mq, index_in_heap);
			/* LHのルートにLHの末尾を移動する */
			uint32_t lh_num_elements = num_elements / 2U;
			index_in_queue = mq->lh_heap_[lh_num_elements];
			mq->lh_heap_[0] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = 0;
			/* LHのルートを起点にDownHeap */
			MedianQueuePriavte_LHDownHeap(mq, 0U);
		} else {
			/* LHから要素を取り出した */
			/* 取り出した箇所にLHの末尾を移動する */
			uint32_t index_in_queue;
			uint32_t lh_num_elements = num_elements / 2U;
			index_in_queue = mq->lh_heap_[lh_num_elements];
			mq->lh_heap_[index_in_heap] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = index_in_heap;
			/* 埋めた箇所を起点にLHをDownHeap */
			if (!MedianQueuePriavte_LHDownHeap(mq, index_in_heap)) {
				/* DownHeapで変化がなかったら埋めた箇所を起点にRHをUpHeap */
				MedianQueuePriavte_LHUpHeap(mq, index_in_heap);
			}
		}
	}
	return element;
}