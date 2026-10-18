/**
 * @file
 * @brief Content view public include file - the window of buffered items indexed by timestamp.
 */
#ifndef __CONTENT_VIEW_INCLUDE__
#define __CONTENT_VIEW_INCLUDE__

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <com/amazonaws/kinesis/video/common/CommonDefs.h>
#include <com/amazonaws/kinesis/video/common/PlatformUtils.h>

// IMPORTANT! Some of the headers are not tightly packed!
////////////////////////////////////////////////////
// Public headers
////////////////////////////////////////////////////
#include <com/amazonaws/kinesis/video/utils/Include.h>
#include <com/amazonaws/kinesis/video/heap/Include.h>

/**
 * Minimum number of items in the window
 */
#define MIN_CONTENT_VIEW_ITEMS 10

/**
 * Minimum buffer duration value
 */
#define MIN_CONTENT_VIEW_BUFFER_DURATION 0

/**
 * Current version of the content view object
 */
#define CONTENT_VIEW_CURRENT_VERSION 0

////////////////////////////////////////////////////
// Status return codes
////////////////////////////////////////////////////
#define STATUS_VIEW_BASE                      0x30000000
#define STATUS_MIN_CONTENT_VIEW_ITEMS         STATUS_VIEW_BASE + 0x00000001
#define STATUS_INVALID_CONTENT_VIEW_DURATION  STATUS_VIEW_BASE + 0x00000002
#define STATUS_CONTENT_VIEW_NO_MORE_ITEMS     STATUS_VIEW_BASE + 0x00000003
#define STATUS_CONTENT_VIEW_INVALID_INDEX     STATUS_VIEW_BASE + 0x00000004
#define STATUS_CONTENT_VIEW_INVALID_TIMESTAMP STATUS_VIEW_BASE + 0x00000005
#define STATUS_INVALID_CONTENT_VIEW_LENGTH    STATUS_VIEW_BASE + 0x00000006

////////////////////////////////////////////////////
// Main structure declarations
////////////////////////////////////////////////////

/**
 * Flags definitions
 *
 * NOTE: The high order 16 bits will be used to store the data offset
 */
#define ITEM_FLAG_NONE                0
#define ITEM_FLAG_STREAM_START        (0x1 << 0)
#define ITEM_FLAG_FRAGMENT_START      (0x1 << 1)
#define ITEM_FLAG_BUFFERING_ACK       (0x1 << 2)
#define ITEM_FLAG_RECEIVED_ACK        (0x1 << 3)
#define ITEM_FLAG_FRAGMENT_END        (0x1 << 4)
#define ITEM_FLAG_PERSISTED_ACK       (0x1 << 5)
#define ITEM_FLAG_SKIP_ITEM           (0x1 << 6)
// A new timecode base begins at this item: the generator reset its timeline here (initial header, or
// mkvgenResetGenerator), so cluster timecodes restart from zero relative to a new streamStartTimestamp.
//
// Deliberately separate from ITEM_FLAG_STREAM_START, which only means "this item's bytes begin with an EBML
// header". Both a generator reset and streamStartFixupOnReconnect produce a header, but only the generator
// reset restarts timecodes. Unlike ITEM_FLAG_STREAM_START this marker must survive being sent: it is the
// only record that a base change happens at this item, and getStreamData relies on it to terminate any
// session that advances onto it, which is what keeps one timecode base per PutMedia segment.
#define ITEM_FLAG_TIMECODE_BASE_START (0x1 << 7)
#define ITEM_FLAG_STREAM_START_DEBUG  (0x1 << 15)

/**
 * Macros for checking/setting/clearing for various flags
 */
#define CHECK_ITEM_FRAGMENT_START(f)      (((f) &ITEM_FLAG_FRAGMENT_START) != ITEM_FLAG_NONE)
#define CHECK_ITEM_BUFFERING_ACK(f)       (((f) &ITEM_FLAG_BUFFERING_ACK) != ITEM_FLAG_NONE)
#define CHECK_ITEM_RECEIVED_ACK(f)        (((f) &ITEM_FLAG_RECEIVED_ACK) != ITEM_FLAG_NONE)
#define CHECK_ITEM_STREAM_START(f)        (((f) &ITEM_FLAG_STREAM_START) != ITEM_FLAG_NONE)
#define CHECK_ITEM_FRAGMENT_END(f)        (((f) &ITEM_FLAG_FRAGMENT_END) != ITEM_FLAG_NONE)
#define CHECK_ITEM_PERSISTED_ACK(f)       (((f) &ITEM_FLAG_PERSISTED_ACK) != ITEM_FLAG_NONE)
#define CHECK_ITEM_SKIP_ITEM(f)           (((f) &ITEM_FLAG_SKIP_ITEM) != ITEM_FLAG_NONE)
#define CHECK_ITEM_STREAM_START_DEBUG(f)  (((f) &ITEM_FLAG_STREAM_START_DEBUG) != ITEM_FLAG_NONE)
#define CHECK_ITEM_TIMECODE_BASE_START(f) (((f) &ITEM_FLAG_TIMECODE_BASE_START) != ITEM_FLAG_NONE)

#define SET_ITEM_FRAGMENT_START(f)      ((f) |= ITEM_FLAG_FRAGMENT_START)
#define SET_ITEM_BUFFERING_ACK(f)       ((f) |= ITEM_FLAG_BUFFERING_ACK)
#define SET_ITEM_RECEIVED_ACK(f)        ((f) |= ITEM_FLAG_RECEIVED_ACK)
#define SET_ITEM_STREAM_START(f)        ((f) |= ITEM_FLAG_STREAM_START)
#define SET_ITEM_FRAGMENT_END(f)        ((f) |= ITEM_FLAG_FRAGMENT_END)
#define SET_ITEM_PERSISTED_ACK(f)       ((f) |= ITEM_FLAG_PERSISTED_ACK)
#define SET_ITEM_SKIP_ITEM(f)           ((f) |= ITEM_FLAG_SKIP_ITEM)
#define SET_ITEM_STREAM_START_DEBUG(f)  ((f) |= ITEM_FLAG_STREAM_START_DEBUG)
#define SET_ITEM_TIMECODE_BASE_START(f) ((f) |= ITEM_FLAG_TIMECODE_BASE_START)

#define CLEAR_ITEM_FRAGMENT_START(f)      ((f) &= ~ITEM_FLAG_FRAGMENT_START)
#define CLEAR_ITEM_BUFFERING_ACK(f)       ((f) &= ~ITEM_FLAG_BUFFERING_ACK)
#define CLEAR_ITEM_RECEIVED_ACK(f)        ((f) &= ~ITEM_FLAG_RECEIVED_ACK)
#define CLEAR_ITEM_STREAM_START(f)        ((f) &= ~ITEM_FLAG_STREAM_START)
#define CLEAR_ITEM_FRAGMENT_END(f)        ((f) &= ~ITEM_FLAG_FRAGMENT_END)
#define CLEAR_ITEM_PERSISTED_ACK(f)       ((f) &= ~ITEM_FLAG_PERSISTED_ACK)
#define CLEAR_ITEM_SKIP_ITEM(f)           ((f) &= ~ITEM_FLAG_SKIP_ITEM)
#define CLEAR_ITEM_STREAM_START_DEBUG(f)  ((f) &= ~ITEM_FLAG_STREAM_START_DEBUG)
#define CLEAR_ITEM_TIMECODE_BASE_START(f) ((f) &= ~ITEM_FLAG_TIMECODE_BASE_START)

#define GET_ITEM_DATA_OFFSET(f)    ((UINT16) ((f) >> 16))
#define SET_ITEM_DATA_OFFSET(f, o) ((f) = ((f) &0x0000ffff) | (((UINT16) (o)) << 16))

/**
 * This is a sentinel indicating an invalid index value
 */
#define INVALID_VIEW_INDEX_VALUE (0xFFFFFFFFFFFFFFFFULL)

/**
 * Checks for the index validity
 */
#define IS_VALID_VIEW_INDEX(h) ((h) != INVALID_VIEW_INDEX_VALUE)

/**
 * The representation of the item in the cache.
 *
 * IMPORTANT!!! This structure should be tightly packed without explicit compiler directives
 */
typedef struct {
    /// Id of the item
    UINT64 index;

    /// The timestamp of the item
    UINT64 timestamp;

    /// The timestamp used to map acks from backend
    UINT64 ackTimestamp;

    /// The duration of the item
    UINT64 duration;

    /// Length of the data in bytes
    UINT32 length;

    /// Whether this item depends on others (ex. IFrame for frames)
    UINT32 flags;

    /// The data allocation handle
    ALLOCATION_HANDLE handle;
} ViewItem, *PViewItem;

/*
 * Determine how content view drop frames when overflow is detected
 */
typedef enum {
    /// drop single view item from the buffer
    CONTENT_VIEW_OVERFLOW_POLICY_DROP_TAIL_VIEW_ITEM,

    /// drop entire fragment
    CONTENT_VIEW_OVERFLOW_POLICY_DROP_UNTIL_FRAGMENT_START,
} CONTENT_VIEW_OVERFLOW_POLICY;

/**
 * ContentView structure
 */
typedef struct __ContentView ContentView;
struct __ContentView {
    UINT32 version;
    // NOTE: The internal structure follows
};

typedef struct __ContentView* PContentView;

/*
 * Callback functions definitions
 */

/**
 * Callback to notify about an item falling out of the window
 *
 * @param pContentView Content view which notifies the caller - this pointer
 * @param customData Custom pass-through value
 * @param pViewItem item that's about to fall off from the window
 * @param currentRemoved whether the item was current - i.e. it wasn't consumed
 *
 * @return VOID
 */
typedef VOID (*ContentViewItemRemoveNotificationCallbackFunc)(PContentView pContentView, UINT64 customData, PViewItem pViewItem, BOOL currentRemoved);

////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////

/**
 * Create the ContentView object
 *
 * @param maxItemCount Max number of items in the window
 * @param bufferDuration Duration of items to keep in the window
 * @param removeCallbackFunc Optional - Callback function
 * @param customData Custom data to pass to the callback
 * @param overflowStrategy how content view will drop frame when overflow happens
 * @param ppContentView returns the newly created object
 *
 * @return STATUS code of the execution
 **/
PUBLIC_API STATUS createContentView(UINT32 maxItemCount, UINT64 bufferDuration, ContentViewItemRemoveNotificationCallbackFunc removeCallbackFunc, UINT64 customData, CONTENT_VIEW_OVERFLOW_POLICY overflowStrategy, PContentView* ppContentView);

/**
 * Frees and de-allocates the memory of the ContentView and it's sub-objects
 *
 * NOTE: This function is idempotent - can be called at various stages of construction.
 *
 * @param pContentView the object to free
 */
PUBLIC_API STATUS freeContentView(PContentView pContentView);

/**
 * Checks whether an item with a given index exists
 *
 * @param pContentView Content view
 * @param itemIndex item index
 * @param pExists whether the item exists
 *
 */
PUBLIC_API STATUS contentViewItemExists(PContentView pContentView, UINT64 itemIndex, PBOOL pExists);

/**
 * Checks whether an item with a given timestamp is in the range
 *
 * @param pContentView Content view
 * @param timestamp item timestamp
 * @param checkAckTimeStamp whether check against ackTimestamp or contentView timestamp
 * @param pInRange whether the item exists
 *
 */
PUBLIC_API STATUS contentViewTimestampInRange(PContentView pContentView, UINT64 timestamp, BOOL checkAckTimeStamp, PBOOL pInRange);

/**
 * Gets an item from the current index and advances the index. Iterates to the next item.
 *
 * @param pContentView Content view
 * @param ppItem The current item pointer
 *
 */
PUBLIC_API STATUS contentViewGetNext(PContentView pContentView, PViewItem* ppItem);

/**
 * Gets an item from the given index. Current remains untouched.
 *
 * @param pContentView Content view
 * @param itemIndex the index of the item
 * @param ppItem The current item pointer
 *
 */
PUBLIC_API STATUS contentViewGetItemAt(PContentView pContentView, UINT64 itemIndex, PViewItem* ppItem);

/**
 * Finds an item corresponding to the timestamp. Current remains untouched.
 *
 * @param pContentView Content view
 * @param timestamp the index of the item
 * @param checkAckTimeStamp whether check against ackTimestamp or contentView timestamp
 * @param ppItem The current item pointer
 *
 */
PUBLIC_API STATUS contentViewGetItemWithTimestamp(PContentView pContentView, UINT64 timestamp, BOOL checkAckTimeStamp, PViewItem* ppItem);

/**
 * Gets the current index
 *
 * @param pContentView Content view
 * @param pIndex current item index
 *
 */
PUBLIC_API STATUS contentViewGetCurrentIndex(PContentView pContentView, PUINT64 pIndex);

/**
 * Sets the current item at a given index
 *
 * @param pContentView Content view
 * @param index new current item index
 *
 */
PUBLIC_API STATUS contentViewSetCurrentIndex(PContentView pContentView, UINT64 index);

/**
 * Rolls back the current item by a specified duration or as far as the tail.
 * Optionally looks for a key-framed item.
 *
 * @param pContentView Content view.
 * @param duration Timestamp to set the current to. NOTE: the timestamp will be inclusive.
 * @param keyFrame Whether to look for a key framed item.
 * @param lastReceivedAck Whether to stop at the last buffering ACK.
 *
 */
PUBLIC_API STATUS contentViewRollbackCurrent(PContentView pContentView, UINT64 duration, BOOL keyFrame, BOOL lastReceivedAck);

/**
 * Resets the current item to the tail position
 *
 * @param pContentView Content view
 *
 */
PUBLIC_API STATUS contentViewResetCurrent(PContentView pContentView);

/**
 * Gets the tail item
 *
 * PContentView - Content view
 * PViewItem - The tail item
 *
 */
PUBLIC_API STATUS contentViewGetTail(PContentView pContentView, PViewItem* ppItem);

/**
 * Gets the head item
 *
 * PContentView - Content view
 * PViewItem - The head item
 *
 */
PUBLIC_API STATUS contentViewGetHead(PContentView pContentView, PViewItem* ppItem);

/**
 * Gets the overall allocation size
 *
 * @param pContentView Content view
 * @param[out] pAllocationSize The overall allocation size
 *
 */
PUBLIC_API STATUS contentViewGetAllocationSize(PContentView pContentView, PUINT32 pAllocationSize);

/**
 * Adds an item to the head of the view
 *
 * @param pContentView Content view
 * @param timestamp item timestamp (decoding timestamp)
 * @param ackTimeStamp item timestamp used to map acks from the backend
 * @param duration item duration
 * @param allocHandle Allocation handle
 * @param offset Byte offset of the data from the beginning of the allocation
 * @param length Size of the data in bytes
 * @param flags Item flags.
 *
 */
PUBLIC_API STATUS contentViewAddItem(PContentView pContentView, UINT64 timestamp, UINT64 ackTimeStamp, UINT64 duration, ALLOCATION_HANDLE allocHandle, UINT32 offset, UINT32 length, UINT32 flags);

/**
 * Gets the view's temporal window duration
 *
 * @param pContentView Content view
 * @param pCurrentDuration current window duration - from the head timestamp to the current timestamp
 * @param pWindowDuration Optional - entire window duration - from the head timestamp to the tail timestamp
 *
 */
PUBLIC_API STATUS contentViewGetWindowDuration(PContentView pContentView, PUINT64 pCurrentDuration, PUINT64 pWindowDuration);

/**
 * Gets the view's window item count and entire window item count (optionally)
 *
 * @param pContentView Content view
 * @param pCurrentItemCount current window item count - the number of elements from the current to the head
 * @param pWindowItemCount Optional - entire window item count - the number of elements in the entire window
 *
 */
PUBLIC_API STATUS contentViewGetWindowItemCount(PContentView pContentView, PUINT64 pCurrentItemCount, PUINT64 pWindowItemCount);

/**
 * Gets the view's window allocation size and entire window allocation size (optionally)
 *
 * @param pContentView Content view
 * @param pCurrentAllocationSize current window allocation size - the size of all allocations from the current to the head
 * @param pWindowAllocationSize Optional - entire window size - the size of all allocations in the entire window
 *
 */
PUBLIC_API STATUS contentViewGetWindowAllocationSize(PContentView pContentView, PUINT64 pCurrentAllocationSize, PUINT64 pWindowAllocationSize);

/**
 * Trims the tail till the given item. The remove callbacks will be fired and the current shifted if needed.
 *
 * @param pContentView Content view
 * @param itemIndex Trim the tail to this item
 *
 */
PUBLIC_API STATUS contentViewTrimTail(PContentView pContentView, UINT64 itemIndex);

/**
 * Trims the tail based on CONTENT_VIEW_OVERFLOW_POLICY
 *
 * @param pContentView Content view
 *
 */
PUBLIC_API STATUS contentViewTrimTailItems(PContentView pContentView);

/**
 * Removes all items in the content view. Calls the remove callback if specified.
 *
 * @param pContentView Content view
 */
PUBLIC_API STATUS contentViewRemoveAll(PContentView pContentView);

/**
 * Checks whether there is an available slot both temporary and depth-wise
 * in the content view without evicting a tail item.
 *
 * @param pContentView Content view
 * @param[out] pWindowAvailability Optional. Whether there is available space to put an item without tail eviction.
 */
PUBLIC_API STATUS contentViewCheckAvailability(PContentView pContentView, PBOOL pWindowAvailability);

#ifdef __cplusplus
}
#endif
#endif /* __CONTENT_VIEW_INCLUDE__ */
