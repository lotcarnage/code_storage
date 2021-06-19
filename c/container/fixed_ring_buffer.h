/* (c) 2021 @lot_carnage */

/* Include guard */
#ifndef FIXED_RING_BUFFER_H_INCLUDED
#define FIXED_RING_BUFFER_H_INCLUDED

/*****************************************************************************
 * Header Include
 *****************************************************************************/
#include <stddef.h>
#include <stdint.h>

/*****************************************************************************
 * Macro
 *****************************************************************************/

/*****************************************************************************
 * Type Declaration
 *****************************************************************************/

/*****************************************************************************
 * Type Definition
 *****************************************************************************/
typedef void* FixedRingBufferPayload;

typedef struct FixedRingBuffer_ {
	FixedRingBufferPayload* payload_buffer_;
	uint32_t payload_buffer_size_;
	uint32_t wp_;
	uint32_t rp_;
} FixedRingBuffer;

/*****************************************************************************
 * Variable Declaration
 *****************************************************************************/

/*****************************************************************************
 * Function Declaration
 *****************************************************************************/
/* インスタンスを構築する */
void FixedRingBuffer_Construct(
	FixedRingBuffer* frb_object_memory,
	FixedRingBufferPayload payload_buffer[],
	uint32_t payload_buffer_size);

/* インスタンスを破棄する */
void FixedRingBuffer_Destruct(FixedRingBuffer* frb);

/* 積荷の数を取得する */
uint32_t FixedRingBuffer_GetNumPayloads(const FixedRingBuffer* frb);

/* 空き領域の数を取得する */
uint32_t FixedRingBuffer_GetNumBlanks(const FixedRingBuffer* frb);

/* Enqueue可能か */
int FixedRingBuffer_IsEnqueueable(const FixedRingBuffer* frb);

/* Dequeue可能か */
int FixedRingBuffer_IsDequeueable(const FixedRingBuffer* frb);

/* Push可能か */
int FixedRingBuffer_IsPushable(const FixedRingBuffer* frb);

/* Pop可能か */
int FixedRingBuffer_IsPoppable(const FixedRingBuffer* frb);

/* Enqueue
 * 容量オーバ時の結果は未定義
 */
void FixedRingBuffer_Enqueue(
	FixedRingBuffer* frb,
	FixedRingBufferPayload payload);

/* Push
 * 容量オーバ時の結果は未定義
 */
void FixedRingBuffer_Push(
	FixedRingBuffer* frb,
	FixedRingBufferPayload payload);

/* Dequeue
 * 積荷が無い場合の結果は未定義
 */
FixedRingBufferPayload FixedRingBuffer_Dequeue(FixedRingBuffer* frb);

/* Pop
 * 積荷が無い場合の結果は未定義
 */
FixedRingBufferPayload FixedRingBuffer_Pop(FixedRingBuffer* frb);

/* チェックありEnqueue
 * 成功時は0以外、失敗時は0を返す
 */
int FixedRingBuffer_EnqueueWithCheck(
	FixedRingBuffer* frb,
	FixedRingBufferPayload payload);

/* チェックありPush
 * 成功時は0以外、失敗時は0を返す
 */
int FixedRingBuffer_PushWithCheck(
	FixedRingBuffer* frb,
	FixedRingBufferPayload payload);

/* チェックありDequeue
 * 成功時は0以外、失敗時は0を返す
 */
int FixedRingBuffer_DequeueWithCheck(
	FixedRingBuffer* frb,
	FixedRingBufferPayload* dequeued_payload);

/* チェックありPop
 * 成功時は0以外、失敗時は0を返す
 */
int FixedRingBuffer_PopWithCheck(
	FixedRingBuffer* frb,
	FixedRingBufferPayload* popped_payload);

#endif /* FIXED_RING_BUFFER_H_INCLUDED */
