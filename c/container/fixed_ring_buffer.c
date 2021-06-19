/* (c) 2021 @lot_carnage */

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <fixed_ring_buffer.h>

#include <stddef.h>
#include <stdint.h>

/*****************************************************************************
 * Macro
 *****************************************************************************/
#define FIXEDRINGBUFFER_LOCAL_FALSE	(1 == 0)
#define FIXEDRINGBUFFER_LOCAL_TRUE		(!FIXEDRINGBUFFER_LOCAL_FALSE)

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
void FixedRingBuffer_Construct(
	FixedRingBuffer* frb_object_memory,
	FixedRingBufferPayload payload_buffer[],
	uint32_t payload_buffer_size)
{
	FixedRingBuffer* frb = frb_object_memory;
	frb->payload_buffer_ = payload_buffer;
	frb->payload_buffer_size_ = payload_buffer_size;
	frb->wp_ = 0UL;
	frb->rp_ = 0UL;
	return;
}

/* インスタンスを破棄する */
void FixedRingBuffer_Destruct(FixedRingBuffer* frb)
{
	return;
}

/* 積荷の数を取得する */
uint32_t FixedRingBuffer_GetNumPayloads(const FixedRingBuffer* frb)
{
	return (frb->wp_ - frb->rp_);
}

/* 空き領域の数を取得する */
uint32_t FixedRingBuffer_GetNumBlanks(const FixedRingBuffer* frb)
{
	return (frb->payload_buffer_size_ - FixedRingBuffer_GetNumPayloads(frb));
}

/* Enqueue可能か */
int FixedRingBuffer_IsEnqueueable(const FixedRingBuffer* frb)
{
	return (0UL < FixedRingBuffer_GetNumBlanks(frb));
}

/* Dequeue可能か */
int FixedRingBuffer_IsDequeueable(const FixedRingBuffer* frb)
{
	return (0UL < FixedRingBuffer_GetNumPayloads(frb));
}

/* Push可能か */
int FixedRingBuffer_IsPushable(const FixedRingBuffer* frb)
{
	return FixedRingBuffer_IsEnqueueable(frb);
}

/* Pop可能か */
int FixedRingBuffer_IsPoppable(const FixedRingBuffer* frb)
{
	return FixedRingBuffer_IsDequeueable(frb);
}

/* Enqueue
 * 容量オーバ時の結果は未定義
 */
void FixedRingBuffer_Enqueue(
	FixedRingBuffer* frb,
	FixedRingBufferPayload payload)
{
	uint32_t rounded_wp = frb->wp_ % frb->payload_buffer_size_;
	frb->payload_buffer_[rounded_wp] = payload;
	frb->wp_++;
	return;
}

/* Push
 * 容量オーバ時の結果は未定義
 */
void FixedRingBuffer_Push(
	FixedRingBuffer* frb,
	FixedRingBufferPayload payload)
{
	FixedRingBuffer_Enqueue(frb, payload);
	return;
}

/* Dequeue
 * 積荷が無い場合の結果は未定義
 */
FixedRingBufferPayload FixedRingBuffer_Dequeue(FixedRingBuffer* frb)
{
	FixedRingBufferPayload payload;
	payload = frb->payload_buffer_[frb->rp_];
	frb->rp_++;
	if (frb->payload_buffer_size_ <= frb->rp_) {
		frb->rp_ -= frb->payload_buffer_size_;
		frb->wp_ -= frb->payload_buffer_size_;
	}
	return payload;
}

/* Pop
 * 積荷が無い場合の結果は未定義
 */
FixedRingBufferPayload FixedRingBuffer_Pop(FixedRingBuffer* frb)
{
	uint32_t rounded_wp;
	frb->wp_--;
	rounded_wp = frb->wp_ % frb->payload_buffer_size_;
	return frb->payload_buffer_[rounded_wp];
}

/* チェックありEnqueue
 * 成功時は0以外、失敗時は0を返す
 */
int FixedRingBuffer_EnqueueWithCheck(
	FixedRingBuffer* frb,
	FixedRingBufferPayload payload)
{
	if (!FixedRingBuffer_IsEnqueueable(frb)) {
		return FIXEDRINGBUFFER_LOCAL_FALSE;
	}
	FixedRingBuffer_Enqueue(frb, payload);
	return FIXEDRINGBUFFER_LOCAL_TRUE;
}

/* チェックありPush
 * 成功時は0以外、失敗時は0を返す
 */
int FixedRingBuffer_PushWithCheck(
	FixedRingBuffer* frb,
	FixedRingBufferPayload payload)
{
	if (!FixedRingBuffer_IsPushable(frb)) {
		return FIXEDRINGBUFFER_LOCAL_FALSE;
	}
	FixedRingBuffer_Push(frb, payload);
	return FIXEDRINGBUFFER_LOCAL_TRUE;
}

/* チェックありDequeue
 * 成功時は0以外、失敗時は0を返す
 */
int FixedRingBuffer_DequeueWithCheck(
	FixedRingBuffer* frb,
	FixedRingBufferPayload* dequeued_payload)
{
	if (!FixedRingBuffer_IsDequeueable(frb)) {
		return FIXEDRINGBUFFER_LOCAL_FALSE;
	}
	*dequeued_payload = FixedRingBuffer_Dequeue(frb);
	return FIXEDRINGBUFFER_LOCAL_TRUE;
}

/* チェックありPop
 * 成功時は0以外、失敗時は0を返す
 */
int FixedRingBuffer_PopWithCheck(
	FixedRingBuffer* frb,
	FixedRingBufferPayload* popped_payload)
{
	if (!FixedRingBuffer_IsPoppable(frb)) {
		return FIXEDRINGBUFFER_LOCAL_FALSE;
	}
	*popped_payload = FixedRingBuffer_Pop(frb);
	return FIXEDRINGBUFFER_LOCAL_TRUE;
}
