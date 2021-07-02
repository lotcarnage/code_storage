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
typedef int (*MedianQueuePrivate_ComparisonOperator)(
	MedianQueueElement lhv, MedianQueueElement rhv);

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

static uint32_t MedianQueuePrivate_GetNumElementsInLeftHandHeap(
	const MedianQueue* mq)
{
	return MedianQueuePrivate_GetNumElements(mq) / 2U;
}

static uint32_t MedianQueuePrivate_GetNumElementsInRightHandHeap(
	const MedianQueue* mq)
{
	return (MedianQueuePrivate_GetNumElements(mq) + 1U) / 2U;
}

static uint32_t MedianQueuePrivate_GetRightHandHeapIndexOffset(
	const MedianQueue* mq)
{
	return (mq->max_elements_count_ + 1U) / 2U;
}

static uint32_t MedianQueuePrivate_GetTailIndexInLeftHandHeap(
	const MedianQueue* mq)
{
	return MedianQueuePrivate_GetNumElements(mq) / 2U - 1U;
}

static uint32_t MedianQueuePrivate_GetTailIndexInRightHandHeap(
	const MedianQueue* mq)
{
	return (MedianQueuePrivate_GetNumElements(mq) + 1U) / 2U - 1U;
}


/* lhvv < rhv */
static int MedianQueuePriavte_IsLhvLtRhv(
	MedianQueueElement lhv, MedianQueueElement rhv)
{
	return (lhv < rhv);
}

/* lhv > rhv */
static int MedianQueuePriavte_IsLhvGtRhv(
	MedianQueueElement lhv, MedianQueueElement rhv)
{
	return (lhv > rhv);
}

static void MedianQueuePrivate_UpHeapCore(
	MedianQueuePrivate_ComparisonOperator comparison_operator,
	MedianQueueElement const * elements_queue,
	uint32_t* heap,
	uint32_t* indices_queue,
	uint32_t current_index_in_heap,
	uint32_t heap_index_offset)
{
	MedianQueueElement parent_value;
	MedianQueueElement current_value;
	uint32_t parent_index_in_queue;
	uint32_t current_index_in_queue;
	uint32_t parent_index_in_heap;
	for (;;) {
		if (current_index_in_heap == 0U) {
			break;
		}
		current_index_in_queue = heap[current_index_in_heap];
		current_value = elements_queue[current_index_in_queue];
		parent_index_in_heap = (current_index_in_heap - 1U) / 2U;
		parent_index_in_queue = heap[parent_index_in_heap];
		parent_value = elements_queue[parent_index_in_queue];
		if (comparison_operator(current_value, parent_value)) {
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

static int MedianQueuePriavte_DownHeapCore(
	MedianQueuePrivate_ComparisonOperator comparison_operator,
	MedianQueueElement const * elements_queue,
	uint32_t* heap,
	uint32_t num_elements_in_heap,
	uint32_t* indices_queue,
	uint32_t current_index_in_heap,
	uint32_t heap_index_offset)
{
	MedianQueueElement child_value;
	MedianQueueElement current_value;
	uint32_t child_index_in_queue;
	uint32_t current_index_in_queue;
	uint32_t child_index_in_heap;
	int is_updated = MEDIANQUEUE_LOCAL_FALSE;

	for (;;) {
		/* Left hand child */
		child_index_in_heap = (current_index_in_heap + 1U) * 2U - 1U;
		if (num_elements_in_heap <= child_index_in_heap) {
			break;
		}
		current_index_in_queue = heap[current_index_in_heap];
		current_value = elements_queue[current_index_in_queue];
		child_index_in_queue = heap[child_index_in_heap];
		child_value = elements_queue[child_index_in_queue];
		if (comparison_operator(current_value, child_value)) {
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
		if (num_elements_in_heap <= child_index_in_heap) {
			break;
		}
		current_index_in_queue = heap[current_index_in_heap];
		current_value = elements_queue[current_index_in_queue];
		child_index_in_queue = heap[child_index_in_heap];
		child_value = elements_queue[child_index_in_queue];
		if (comparison_operator(current_value, child_value)) {
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


static void MedianQueuePriavte_LHUpHeap(
	MedianQueue* mq, uint32_t starting_index_in_heap)
{
	MedianQueuePrivate_UpHeapCore(
		MedianQueuePriavte_IsLhvGtRhv,
		mq->buffer_for_elements_,
		mq->lh_heap_,
		mq->buffer_for_heap_indices_,
		starting_index_in_heap,
		0U);
	return;
}

static int MedianQueuePriavte_LHDownHeap(
	MedianQueue* mq, uint32_t starting_index_in_heap)
{
	uint32_t num_elements = MedianQueuePrivate_GetNumElementsInLeftHandHeap(mq);
	int is_updated = MedianQueuePriavte_DownHeapCore(
		MedianQueuePriavte_IsLhvLtRhv,
		mq->buffer_for_elements_,
		mq->lh_heap_,
		num_elements,
		mq->buffer_for_heap_indices_,
		starting_index_in_heap,
		0U);
	return is_updated;
}

static void MedianQueuePriavte_RHUpHeap(
	MedianQueue* mq, uint32_t starting_index_in_heap)
{
	uint32_t heap_index_offset = MedianQueuePrivate_GetRightHandHeapIndexOffset(mq);
	MedianQueuePrivate_UpHeapCore(
		MedianQueuePriavte_IsLhvLtRhv,
		mq->buffer_for_elements_,
		mq->rh_heap_,
		mq->buffer_for_heap_indices_,
		starting_index_in_heap,
		heap_index_offset);
	return;
}

static int MedianQueuePriavte_RHDownHeap(
	MedianQueue* mq, uint32_t starting_index_in_heap)
{
	uint32_t num_elements = MedianQueuePrivate_GetNumElementsInRightHandHeap(mq);
	uint32_t heap_index_offset = MedianQueuePrivate_GetRightHandHeapIndexOffset(mq);
	int is_updated = MedianQueuePriavte_DownHeapCore(
		MedianQueuePriavte_IsLhvGtRhv,
		mq->buffer_for_elements_,
		mq->rh_heap_,
		num_elements,
		mq->buffer_for_heap_indices_,
		starting_index_in_heap,
		heap_index_offset);
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

MedianQueueElement MedianQueue_GetLowerMedian(const MedianQueue* mq)
{
	uint32_t num_elements = MedianQueuePrivate_GetNumElements(mq);
	uint32_t queue_index =
		((num_elements % 2U) != 0U)
		? mq->rh_heap_[0]
		: mq->lh_heap_[0];
	return mq->buffer_for_elements_[queue_index];
}

MedianQueueElement MedianQueue_GetUpperMedian(const MedianQueue* mq)
{
	return mq->buffer_for_elements_[mq->rh_heap_[0]];
}

int MedianQueue_IsEnqueueable(const MedianQueue* mq)
{
	return (0U < MedianQueue_GetNumBlanks(mq));
}

int MedianQueue_IsDequeueable(const MedianQueue* mq)
{
	return (0U < MedianQueuePrivate_GetNumElements(mq));
}

void MedianQueue_Enqueue(
	MedianQueue* mq, MedianQueueElement element)
{
	uint32_t const num_elements = MedianQueuePrivate_GetNumElements(mq);
	uint32_t const new_leaf_index_in_lh_heap = num_elements / 2U;
	uint32_t const new_leaf_index_in_rh_heap = (num_elements + 1U) / 2U;
	uint32_t const heap_index_offset = MedianQueuePrivate_GetRightHandHeapIndexOffset(mq);
	uint32_t const rounded_wp = mq->wp_ % mq->max_elements_count_;

	/* 値をキューに入れる */
	mq->buffer_for_elements_[rounded_wp] = element;

	/* 内部ヒープ木の操作 */
	if (num_elements == 0U) {
		/* 最初の一つ目の要素追加は右側ヒープ木に追加して終了 */
		mq->buffer_for_heap_indices_[rounded_wp] = new_leaf_index_in_rh_heap + heap_index_offset;
		mq->rh_heap_[new_leaf_index_in_rh_heap] = rounded_wp;
		MedianQueuePriavte_RHUpHeap(mq, new_leaf_index_in_rh_heap);
	} else if ((num_elements % 2U) != 0U) {
		/* 要素数が奇数=右側ヒープ木が大きい */
		MedianQueueElement upper_median = MedianQueue_GetUpperMedian(mq);
		if (upper_median < element) {
			uint32_t index_in_queue = mq->rh_heap_[0U];

			/* RHのルートを取り出してLHの末尾へ追加してUpHeap */
			mq->lh_heap_[new_leaf_index_in_lh_heap] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = new_leaf_index_in_lh_heap;
			MedianQueuePriavte_LHUpHeap(mq, new_leaf_index_in_lh_heap);

			/* 新しい要素をRHのルートに入れてDownHeap */
			mq->buffer_for_heap_indices_[rounded_wp] = 0U + heap_index_offset;
			mq->rh_heap_[0U] = rounded_wp;
			MedianQueuePriavte_RHDownHeap(mq, 0U);
		} else {
			/* 新しい要素をLHの末尾に追加してUpHeap */
			mq->lh_heap_[new_leaf_index_in_lh_heap] = rounded_wp;
			mq->buffer_for_heap_indices_[rounded_wp] = new_leaf_index_in_lh_heap;
			MedianQueuePriavte_LHUpHeap(mq, new_leaf_index_in_lh_heap);
		}
	} else {
		/* 要素数が偶数=左右ヒープ木の要素数が同じ */
		MedianQueueElement lower_median = MedianQueue_GetLowerMedian(mq);
		if (element < lower_median) {
			uint32_t index_in_queue = mq->lh_heap_[0U];
			/* LHのルートを取り出してRHの末尾へ追加してUpHeap */
			mq->rh_heap_[new_leaf_index_in_rh_heap] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = new_leaf_index_in_rh_heap + heap_index_offset;
			MedianQueuePriavte_RHUpHeap(mq, new_leaf_index_in_rh_heap);

			/* 新しい要素をLHのルートに入れてDownHeap */
			mq->lh_heap_[0U] = rounded_wp;
			mq->buffer_for_heap_indices_[rounded_wp] = 0U;
			MedianQueuePriavte_LHDownHeap(mq, 0U);
		} else {
			/* 新しい要素をRHの末尾に追加してUpHeap */
			mq->rh_heap_[new_leaf_index_in_rh_heap] = rounded_wp;
			mq->buffer_for_heap_indices_[rounded_wp] = new_leaf_index_in_rh_heap + heap_index_offset;
			MedianQueuePriavte_RHUpHeap(mq, new_leaf_index_in_rh_heap);
		}
	}
	/* 処理の途中で要素数が変化しないように最後に要素数を更新する */
	mq->wp_++;
	return;
}

MedianQueueElement MedianQueue_Dequeue(
	MedianQueue* mq)
{
	MedianQueueElement element;
	uint32_t num_elements = MedianQueuePrivate_GetNumElements(mq);
	uint32_t heap_index_offset = MedianQueuePrivate_GetRightHandHeapIndexOffset(mq);
	uint32_t index_in_heap = mq->buffer_for_heap_indices_[mq->rp_];

	/* キューから値を取り出す */
	element = mq->buffer_for_elements_[mq->rp_];

	/* 内部ヒープ木の操作 */
	if ((num_elements % 2U) != 0U) {
		/* 要素数が奇数=右側ヒープ木が大きい */
		uint32_t tail_index_in_rh_heap = MedianQueuePrivate_GetTailIndexInRightHandHeap(mq);
		if (heap_index_offset <= index_in_heap) {
			/* RHから要素を取り出したので取り出した箇所にRHの末尾を移動する */
			index_in_heap -= heap_index_offset;
			if (index_in_heap != tail_index_in_rh_heap) {
				uint32_t index_in_queue;
				index_in_queue = mq->rh_heap_[tail_index_in_rh_heap];
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

			/* RHの末尾をRHのルートに移動してDownHeap */
			index_in_queue = mq->rh_heap_[tail_index_in_rh_heap];
			mq->rh_heap_[0] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = 0U + heap_index_offset;
			MedianQueuePriavte_RHDownHeap(mq, 0U);
		}
	} else {
		/* 要素数が偶数=左右ヒープ木の要素数が同じ */
		uint32_t tail_index_in_lh_heap = MedianQueuePrivate_GetTailIndexInLeftHandHeap(mq);
		if (heap_index_offset <= index_in_heap) {
			uint32_t index_in_queue;
			/* RHから要素を取り出した */
			/* 取り出した箇所にLHのルートを移動する */
			/* LHの要素はRHの全ての要素以下なので、DownHeapで木が変化しない事は自明 */
			index_in_heap -= heap_index_offset;
			index_in_queue = mq->lh_heap_[0];
			mq->rh_heap_[index_in_heap] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = index_in_heap + heap_index_offset;
			/* 埋めた箇所を起点にRHをUpHeap */
			MedianQueuePriavte_RHUpHeap(mq, index_in_heap);

			/* LHの末尾をLHのルートに移動してDownHeap */
			index_in_queue = mq->lh_heap_[tail_index_in_lh_heap];
			mq->lh_heap_[0] = index_in_queue;
			mq->buffer_for_heap_indices_[index_in_queue] = 0U;
			MedianQueuePriavte_LHDownHeap(mq, 0U);
		} else {
			/* LHから要素を取り出した */
			/* 取り出した箇所にLHの末尾を移動する */
			uint32_t index_in_queue;
			if (index_in_heap != tail_index_in_lh_heap) {
				index_in_queue = mq->lh_heap_[tail_index_in_lh_heap];
				mq->lh_heap_[index_in_heap] = index_in_queue;
				mq->buffer_for_heap_indices_[index_in_queue] = index_in_heap;
				/* 埋めた箇所を起点にLHをDownHeap */
				if (!MedianQueuePriavte_LHDownHeap(mq, index_in_heap)) {
					/* DownHeapで変化がなかったら埋めた箇所を起点にRHをUpHeap */
					MedianQueuePriavte_LHUpHeap(mq, index_in_heap);
				}
			}
		}
	}

	/* 処理の途中で要素数が変化しないように最後に要素数を更新する */
	mq->rp_++;
	if (mq->max_elements_count_ <= mq->rp_) {
		mq->wp_ -= mq->max_elements_count_;
		mq->rp_ -= mq->max_elements_count_;
	}

	return element;
}
