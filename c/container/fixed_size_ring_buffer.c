/* (c) 2021 @lot_carnage */

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <fixed_size_ring_buffer.h>

#include <stddef.h>
#include <stdint.h>

/*****************************************************************************
 * Macro
 *****************************************************************************/
#define FIXEDSIZERINGBUFFER_LOCAL_FALSE	(1 == 0)
#define FIXEDSIZERINGBUFFER_LOCAL_TRUE		(!FIXEDSIZERINGBUFFER_LOCAL_FALSE)

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
/* インスタンスを構築する */
void FixedSizeRingBuffer_Construct(
	FixedSizeRingBuffer* frb_object_memory,
	FixedSizeRingBufferElement buffer_for_elements[],
	uint32_t max_elements_count)
{
	FixedSizeRingBuffer* frb = frb_object_memory;
	frb->buffer_for_elements_ = buffer_for_elements;
	frb->max_elements_count_ = max_elements_count;
	frb->wp_ = 0U;
	frb->rp_ = 0U;
	return;
}

/* インスタンスを破棄する */
void FixedSizeRingBuffer_Destruct(FixedSizeRingBuffer* frb)
{
	return;
}

/* 積荷の数を取得する */
uint32_t FixedSizeRingBuffer_GetNumElements(const FixedSizeRingBuffer* frb)
{
	return (frb->wp_ - frb->rp_);
}

/* 空き領域の数を取得する */
uint32_t FixedSizeRingBuffer_GetNumBlanks(const FixedSizeRingBuffer* frb)
{
	return (frb->max_elements_count_ - FixedSizeRingBuffer_GetNumElements(frb));
}

/* Enqueue可能か */
int FixedSizeRingBuffer_IsEnqueueable(const FixedSizeRingBuffer* frb)
{
	return (0UL < FixedSizeRingBuffer_GetNumBlanks(frb));
}

/* Dequeue可能か */
int FixedSizeRingBuffer_IsDequeueable(const FixedSizeRingBuffer* frb)
{
	return (0UL < FixedSizeRingBuffer_GetNumElements(frb));
}

/* Push可能か */
int FixedSizeRingBuffer_IsPushable(const FixedSizeRingBuffer* frb)
{
	return FixedSizeRingBuffer_IsEnqueueable(frb);
}

/* Pop可能か */
int FixedSizeRingBuffer_IsPoppable(const FixedSizeRingBuffer* frb)
{
	return FixedSizeRingBuffer_IsDequeueable(frb);
}

/* Enqueue
 * 容量オーバ時の結果は未定義
 */
void FixedSizeRingBuffer_Enqueue(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement element)
{
	uint32_t rounded_wp = frb->wp_ % frb->max_elements_count_;
	frb->buffer_for_elements_[rounded_wp] = element;
	frb->wp_++;
	return;
}

/* Push
 * 容量オーバ時の結果は未定義
 */
void FixedSizeRingBuffer_Push(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement element)
{
	FixedSizeRingBuffer_Enqueue(frb, element);
	return;
}

/* Dequeue
 * 積荷が無い場合の結果は未定義
 */
FixedSizeRingBufferElement FixedSizeRingBuffer_Dequeue(FixedSizeRingBuffer* frb)
{
	FixedSizeRingBufferElement element;
	element = frb->buffer_for_elements_[frb->rp_];
	frb->rp_++;
	if (frb->max_elements_count_ <= frb->rp_) {
		frb->rp_ -= frb->max_elements_count_;
		frb->wp_ -= frb->max_elements_count_;
	}
	return element;
}

/* Pop
 * 積荷が無い場合の結果は未定義
 */
FixedSizeRingBufferElement FixedSizeRingBuffer_Pop(FixedSizeRingBuffer* frb)
{
	uint32_t rounded_wp;
	frb->wp_--;
	rounded_wp = frb->wp_ % frb->max_elements_count_;
	return frb->buffer_for_elements_[rounded_wp];
}

/* チェックありEnqueue
 * 成功時は0以外、失敗時は0を返す
 */
int FixedSizeRingBuffer_EnqueueWithCheck(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement element)
{
	if (!FixedSizeRingBuffer_IsEnqueueable(frb)) {
		return FIXEDSIZERINGBUFFER_LOCAL_FALSE;
	}
	FixedSizeRingBuffer_Enqueue(frb, element);
	return FIXEDSIZERINGBUFFER_LOCAL_TRUE;
}

/* チェックありPush
 * 成功時は0以外、失敗時は0を返す
 */
int FixedSizeRingBuffer_PushWithCheck(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement element)
{
	if (!FixedSizeRingBuffer_IsPushable(frb)) {
		return FIXEDSIZERINGBUFFER_LOCAL_FALSE;
	}
	FixedSizeRingBuffer_Push(frb, element);
	return FIXEDSIZERINGBUFFER_LOCAL_TRUE;
}

/* チェックありDequeue
 * 成功時は0以外、失敗時は0を返す
 */
int FixedSizeRingBuffer_DequeueWithCheck(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement* dequeued_element)
{
	if (!FixedSizeRingBuffer_IsDequeueable(frb)) {
		return FIXEDSIZERINGBUFFER_LOCAL_FALSE;
	}
	*dequeued_element = FixedSizeRingBuffer_Dequeue(frb);
	return FIXEDSIZERINGBUFFER_LOCAL_TRUE;
}

/* チェックありPop
 * 成功時は0以外、失敗時は0を返す
 */
int FixedSizeRingBuffer_PopWithCheck(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement* popped_element)
{
	if (!FixedSizeRingBuffer_IsPoppable(frb)) {
		return FIXEDSIZERINGBUFFER_LOCAL_FALSE;
	}
	*popped_element = FixedSizeRingBuffer_Pop(frb);
	return FIXEDSIZERINGBUFFER_LOCAL_TRUE;
}
