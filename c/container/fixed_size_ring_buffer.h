/* (c) 2021 @lot_carnage */

/* Include guard */
#ifndef FIXED_SIZE_RING_BUFFER_H_INCLUDED
#define FIXED_SIZE_RING_BUFFER_H_INCLUDED

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
typedef void* FixedSizeRingBufferElement;

typedef struct FixedSizeRingBuffer_ {
	FixedSizeRingBufferElement* buffer_for_elements_;
	uint32_t max_elements_count_;
	uint32_t wp_;
	uint32_t rp_;
} FixedSizeRingBuffer;

/*****************************************************************************
 * Variable Declaration
 *****************************************************************************/

/*****************************************************************************
 * Function Declaration
 *****************************************************************************/
/* インスタンスを構築する */
void FixedSizeRingBuffer_Construct(
	FixedSizeRingBuffer* frb_object_memory,
	FixedSizeRingBufferElement buffer_for_elements[],
	uint32_t max_elements_count);

/* インスタンスを破棄する */
void FixedSizeRingBuffer_Destruct(FixedSizeRingBuffer* frb);

/* 積荷の数を取得する */
uint32_t FixedSizeRingBuffer_GetNumElements(const FixedSizeRingBuffer* frb);

/* 空き領域の数を取得する */
uint32_t FixedSizeRingBuffer_GetNumBlanks(const FixedSizeRingBuffer* frb);

/* Enqueue可能か */
int FixedSizeRingBuffer_IsEnqueueable(const FixedSizeRingBuffer* frb);

/* Dequeue可能か */
int FixedSizeRingBuffer_IsDequeueable(const FixedSizeRingBuffer* frb);

/* Push可能か */
int FixedSizeRingBuffer_IsPushable(const FixedSizeRingBuffer* frb);

/* Pop可能か */
int FixedSizeRingBuffer_IsPoppable(const FixedSizeRingBuffer* frb);

/* Enqueue
 * 容量オーバ時の結果は未定義
 */
void FixedSizeRingBuffer_Enqueue(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement element);

/* Push
 * 容量オーバ時の結果は未定義
 */
void FixedSizeRingBuffer_Push(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement element);

/* Dequeue
 * 積荷が無い場合の結果は未定義
 */
FixedSizeRingBufferElement FixedSizeRingBuffer_Dequeue(
	FixedSizeRingBuffer* frb);

/* Pop
 * 積荷が無い場合の結果は未定義
 */
FixedSizeRingBufferElement FixedSizeRingBuffer_Pop(FixedSizeRingBuffer* frb);

/* チェックありEnqueue
 * 成功時は0以外、失敗時は0を返す
 */
int FixedSizeRingBuffer_EnqueueWithCheck(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement element);

/* チェックありPush
 * 成功時は0以外、失敗時は0を返す
 */
int FixedSizeRingBuffer_PushWithCheck(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement element);

/* チェックありDequeue
 * 成功時は0以外、失敗時は0を返す
 */
int FixedSizeRingBuffer_DequeueWithCheck(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement* dequeued_element);

/* チェックありPop
 * 成功時は0以外、失敗時は0を返す
 */
int FixedSizeRingBuffer_PopWithCheck(
	FixedSizeRingBuffer* frb,
	FixedSizeRingBufferElement* popped_element);

#endif /* FIXED_SIZE_RING_BUFFER_H_INCLUDED */
