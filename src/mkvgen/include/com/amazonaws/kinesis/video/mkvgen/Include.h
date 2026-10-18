/**
 * @file
 * @brief MKV generator public include file - packages frames into an MKV stream.
 */
#ifndef __MKV_GEN_INCLUDE__
#define __MKV_GEN_INCLUDE__

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

////////////////////////////////////////////////////
// Status return codes
////////////////////////////////////////////////////
#define STATUS_MKVGEN_BASE                                  0x32000000
#define STATUS_MKV_INVALID_FRAME_DATA                       STATUS_MKVGEN_BASE + 0x00000001
#define STATUS_MKV_INVALID_FRAME_TIMESTAMP                  STATUS_MKVGEN_BASE + 0x00000002
#define STATUS_MKV_INVALID_CLUSTER_DURATION                 STATUS_MKVGEN_BASE + 0x00000003
#define STATUS_MKV_INVALID_CONTENT_TYPE_LENGTH              STATUS_MKVGEN_BASE + 0x00000004
#define STATUS_MKV_NUMBER_TOO_BIG                           STATUS_MKVGEN_BASE + 0x00000005
#define STATUS_MKV_INVALID_CODEC_ID_LENGTH                  STATUS_MKVGEN_BASE + 0x00000006
#define STATUS_MKV_INVALID_TRACK_NAME_LENGTH                STATUS_MKVGEN_BASE + 0x00000007
#define STATUS_MKV_INVALID_CODEC_PRIVATE_LENGTH             STATUS_MKVGEN_BASE + 0x00000008
#define STATUS_MKV_CODEC_PRIVATE_NULL                       STATUS_MKVGEN_BASE + 0x00000009
#define STATUS_MKV_INVALID_TIMECODE_SCALE                   STATUS_MKVGEN_BASE + 0x0000000a
#define STATUS_MKV_MAX_FRAME_TIMECODE                       STATUS_MKVGEN_BASE + 0x0000000b
#define STATUS_MKV_LARGE_FRAME_TIMECODE                     STATUS_MKVGEN_BASE + 0x0000000c
#define STATUS_MKV_INVALID_ANNEXB_NALU_IN_FRAME_DATA        STATUS_MKVGEN_BASE + 0x0000000d
#define STATUS_MKV_INVALID_AVCC_NALU_IN_FRAME_DATA          STATUS_MKVGEN_BASE + 0x0000000e
#define STATUS_MKV_BOTH_ANNEXB_AND_AVCC_SPECIFIED           STATUS_MKVGEN_BASE + 0x0000000f
#define STATUS_MKV_INVALID_ANNEXB_NALU_IN_CPD               STATUS_MKVGEN_BASE + 0x00000010
#define STATUS_MKV_PTS_DTS_ARE_NOT_SAME                     STATUS_MKVGEN_BASE + 0x00000011
#define STATUS_MKV_INVALID_H264_H265_CPD                    STATUS_MKVGEN_BASE + 0x00000012
#define STATUS_MKV_INVALID_H264_H265_SPS_WIDTH              STATUS_MKVGEN_BASE + 0x00000013
#define STATUS_MKV_INVALID_H264_H265_SPS_HEIGHT             STATUS_MKVGEN_BASE + 0x00000014
#define STATUS_MKV_INVALID_H264_H265_SPS_NALU               STATUS_MKVGEN_BASE + 0x00000015
#define STATUS_MKV_INVALID_BIH_CPD                          STATUS_MKVGEN_BASE + 0x00000016
#define STATUS_MKV_INVALID_HEVC_NALU_COUNT                  STATUS_MKVGEN_BASE + 0x00000017
#define STATUS_MKV_INVALID_HEVC_FORMAT                      STATUS_MKVGEN_BASE + 0x00000018
#define STATUS_MKV_HEVC_SPS_NALU_MISSING                    STATUS_MKVGEN_BASE + 0x00000019
#define STATUS_MKV_INVALID_HEVC_SPS_NALU_SIZE               STATUS_MKVGEN_BASE + 0x0000001a
#define STATUS_MKV_INVALID_HEVC_SPS_CHROMA_FORMAT_IDC       STATUS_MKVGEN_BASE + 0x0000001b
#define STATUS_MKV_INVALID_HEVC_SPS_RESERVED                STATUS_MKVGEN_BASE + 0x0000001c
#define STATUS_MKV_MIN_ANNEX_B_CPD_SIZE                     STATUS_MKVGEN_BASE + 0x0000001d
#define STATUS_MKV_ANNEXB_CPD_MISSING_NALUS                 STATUS_MKVGEN_BASE + 0x0000001e
#define STATUS_MKV_INVALID_ANNEXB_CPD_NALUS                 STATUS_MKVGEN_BASE + 0x0000001f
#define STATUS_MKV_INVALID_TAG_NAME_LENGTH                  STATUS_MKVGEN_BASE + 0x00000020
#define STATUS_MKV_INVALID_TAG_VALUE_LENGTH                 STATUS_MKVGEN_BASE + 0x00000021
#define STATUS_MKV_INVALID_GENERATOR_STATE_TAGS             STATUS_MKVGEN_BASE + 0x00000022
#define STATUS_MKV_INVALID_AAC_CPD_SAMPLING_FREQUENCY_INDEX STATUS_MKVGEN_BASE + 0x00000023
#define STATUS_MKV_INVALID_AAC_CPD_CHANNEL_CONFIG           STATUS_MKVGEN_BASE + 0x00000024
#define STATUS_MKV_INVALID_AAC_CPD                          STATUS_MKVGEN_BASE + 0x00000025
#define STATUS_MKV_TRACK_INFO_NOT_FOUND                     STATUS_MKVGEN_BASE + 0x00000026
#define STATUS_MKV_INVALID_SEGMENT_UUID                     STATUS_MKVGEN_BASE + 0x00000027
#define STATUS_MKV_INVALID_TRACK_UID                        STATUS_MKVGEN_BASE + 0x00000028
#define STATUS_MKV_INVALID_CLIENT_ID_LENGTH                 STATUS_MKVGEN_BASE + 0x00000029
#define STATUS_MKV_INVALID_AMS_ACM_CPD                      STATUS_MKVGEN_BASE + 0x0000002a
#define STATUS_MKV_MISSING_SPS_FROM_H264_CPD                STATUS_MKVGEN_BASE + 0x0000002b
#define STATUS_MKV_MISSING_PPS_FROM_H264_CPD                STATUS_MKVGEN_BASE + 0x0000002c
#define STATUS_MKV_INVALID_PARENT_TYPE                      STATUS_MKVGEN_BASE + 0x0000002d

////////////////////////////////////////////////////
// Main structure declarations
////////////////////////////////////////////////////

/**
 * Max length of the content type in chars
 */
#define MAX_CONTENT_TYPE_LEN 128

/**
 * Max length of the codec ID
 */
#define MKV_MAX_CODEC_ID_LEN 32

/**
 * Max length of the track name
 */
#define MKV_MAX_TRACK_NAME_LEN 32

/**
 * Max codec private data length
 */
#define MKV_MAX_CODEC_PRIVATE_LEN (1 * 1024 * 1024)

/**
 * Max tag name length
 */
#define MKV_MAX_TAG_NAME_LEN 128

/**
 * Max tag string value length
 */
#define MKV_MAX_TAG_VALUE_LEN 256

/**
 * Minimal and Maximal cluster durations sanity values
 */
#define MAX_CLUSTER_DURATION (30 * HUNDREDS_OF_NANOS_IN_A_SECOND)
#define MIN_CLUSTER_DURATION (1 * HUNDREDS_OF_NANOS_IN_A_SECOND)

/**
 * Minimal and Maximal timecode scale values - for sanity reasons
 */
#define MAX_TIMECODE_SCALE (1 * HUNDREDS_OF_NANOS_IN_A_SECOND)
#define MIN_TIMECODE_SCALE 1

/**
 * The size of the Segment UUID in bytes.
 */
#define MKV_SEGMENT_UUID_LEN 16

/**
 * Max possible timestamp - signed value. This is needed so we won't overflow
 * while multiplying by 100ns (default Kinesis Video time scale) and then divide it
 * by the value of the timecode scale before subtracting the cluster timecode
 * as the frame timecodes are relative to the beginning of the cluster.
 */
#define MAX_TIMESTAMP_VALUE (MAX_INT64 / DEFAULT_TIME_UNIT_IN_NANOS)

/**
 * Max frame queue per track definition
 */
#define DEFAULT_MAX_FRAME_QUEUE_SIZE_PER_TRACK 60

/**
 * Max MKV client id length
 */
#define MAX_MKV_CLIENT_ID_STRING_LEN 64

/**
 * Constant definition for some known content types
 */
#define MKV_H264_CONTENT_TYPE             ((PCHAR) "video/h264")
#define MKV_H265_CONTENT_TYPE             ((PCHAR) "video/h265")
#define MKV_X_MKV_VIDEO_CONTENT_TYPE      ((PCHAR) "video/x-matroska")
#define MKV_X_MKV_AUDIO_CONTENT_TYPE      ((PCHAR) "audio/x-matroska")
#define MKV_AAC_CONTENT_TYPE              ((PCHAR) "audio/aac")
#define MKV_ALAW_CONTENT_TYPE             ((PCHAR) "audio/alaw")
#define MKV_MULAW_CONTENT_TYPE            ((PCHAR) "audio/mulaw")
#define MKV_AVC_CONTENT_TYPE              ((PCHAR) "video/avc")
#define MKV_HEVC_CONTENT_TYPE             ((PCHAR) "video/hevc")
#define MKV_H264_AAC_MULTI_CONTENT_TYPE   ((PCHAR) "video/h264,audio/aac")
#define MKV_H264_MULAW_MULTI_CONTENT_TYPE ((PCHAR) "video/h264,audio/mulaw")
/**
 * Constant definitions for some known codec IDs
 */
#define MKV_FOURCC_CODEC_ID               ((PCHAR) "V_MS/VFW/FOURCC")
#define MKV_H264_AVC_CODEC_ID             ((PCHAR) "V_MPEG4/ISO/AVC")
#define MKV_H265_HEVC_CODEC_ID            ((PCHAR) "V_MPEGH/ISO/HEVC")
#define MKV_AAC_MPEG4_MAIN_CODEC_ID       ((PCHAR) "A_AAC/MPEG4/MAIN")
#define MKV_AAC_CODEC_ID                  ((PCHAR) "A_AAC")
#define MKV_PCM_CODEC_ID                  ((PCHAR) "A_MS/ACM")
#define MKV_PCM_INT_LIT_CODEC_ID          ((PCHAR) "A_PCM/INT/LIT")
#define MKV_PCM_INT_BIG_CODEC_ID          ((PCHAR) "A_PCM/INT/BIG")
#define MKV_PCM_FLOAT_IEEE_CODEC_ID       ((PCHAR) "A_PCM/FLOAT/IEEE")

/**
 * Current versions of the public facing structures
 */
#define TRACK_INFO_CURRENT_VERSION 0
#define FRAME_CURRENT_VERSION      0

/**
 * Frame types enum
 */
typedef enum {
    /**
     * No flags are set
     */
    FRAME_FLAG_NONE = 0,

    /**
     * The frame is a key frame - I or IDR
     */
    FRAME_FLAG_KEY_FRAME = (1 << 0),

    /**
     * The frame is discardable - no other frames depend on it
     */
    FRAME_FLAG_DISCARDABLE_FRAME = (1 << 1),

    /**
     * The frame is invisible for rendering
     */
    FRAME_FLAG_INVISIBLE_FRAME = (1 << 2),

    /**
     * The frame is an explicit marker for the end-of-fragment
     */
    FRAME_FLAG_END_OF_FRAGMENT = (1 << 3),
} FRAME_FLAGS;

/**
 * MKV stream states enum
 */
typedef enum {
    MKV_STATE_START_STREAM,
    MKV_STATE_START_CLUSTER,
    MKV_STATE_START_BLOCK,
} MKV_STREAM_STATE,
    *PMKV_STREAM_STATE;

/**
 * Track types taken from the MKV specification
 */
typedef enum {
    MKV_TRACK_INFO_TYPE_VIDEO = (BYTE) 0x01,
    MKV_TRACK_INFO_TYPE_AUDIO = (BYTE) 0x02,
    MKV_TRACK_INFO_TYPE_UNKOWN = (BYTE) 0x03,
} MKV_TRACK_INFO_TYPE,
    *PMKV_TRACK_INFO_TYPE;

typedef enum { MKV_TREE_TAGS = 0, MKV_TREE_TAG, MKV_TREE_SIMPLE, MKV_TREE_LAST } MKV_TREE_TYPE;

#define GET_TRACK_TYPE_STR(st)                                                                                                                       \
    ((st) == MKV_TRACK_INFO_TYPE_VIDEO       ? (PCHAR) "TRACK_INFO_TYPE_VIDEO"                                                                       \
         : (st) == MKV_TRACK_INFO_TYPE_AUDIO ? (PCHAR) "TRACK_INFO_TYPE_AUDIO"                                                                       \
                                             : "TRACK_INFO_TYPE_UNKNOWN")

/**
 * Macros checking for the frame flags
 */
#define CHECK_FRAME_FLAG_KEY_FRAME(f)         (((f) &FRAME_FLAG_KEY_FRAME) != FRAME_FLAG_NONE)
#define CHECK_FRAME_FLAG_DISCARDABLE_FRAME(f) (((f) &FRAME_FLAG_DISCARDABLE_FRAME) != FRAME_FLAG_NONE)
#define CHECK_FRAME_FLAG_INVISIBLE_FRAME(f)   (((f) &FRAME_FLAG_INVISIBLE_FRAME) != FRAME_FLAG_NONE)
#define CHECK_FRAME_FLAG_END_OF_FRAGMENT(f)   (((f) &FRAME_FLAG_END_OF_FRAGMENT) != FRAME_FLAG_NONE)

#define SET_FRAME_FLAG_KEY_FRAME(f)         ((f) = (FRAME_FLAGS) (f | FRAME_FLAG_KEY_FRAME))
#define SET_FRAME_FLAG_DISCARDABLE_FRAME(f) ((f) = (FRAME_FLAGS) (f | FRAME_FLAG_DISCARDABLE_FRAME))
#define SET_FRAME_FLAG_INVISIBLE_FRAME(f)   ((f) = (FRAME_FLAGS) (f | FRAME_FLAG_INVISIBLE_FRAME))
#define SET_FRAME_FLAG_END_OF_FRAGMENT(f)   ((f) = (FRAME_FLAGS) (f | FRAME_FLAG_END_OF_FRAGMENT))

#define CLEAR_FRAME_FLAG_KEY_FRAME(f)         ((f) = (FRAME_FLAGS) (f & ~FRAME_FLAG_KEY_FRAME))
#define CLEAR_FRAME_FLAG_DISCARDABLE_FRAME(f) ((f) = (FRAME_FLAGS) (f & ~FRAME_FLAG_DISCARDABLE_FRAME))
#define CLEAR_FRAME_FLAG_INVISIBLE_FRAME(f)   ((f) = (FRAME_FLAGS) (f & ~FRAME_FLAG_INVISIBLE_FRAME))
#define CLEAR_FRAME_FLAG_END_OF_FRAGMENT(f)   ((f) = (FRAME_FLAGS) (f & ~FRAME_FLAG_END_OF_FRAGMENT))

/**
 * Frame types enum
 */
typedef enum {
    /**
     * No flags are set
     */
    MKV_GEN_FLAG_NONE = 0,

    /**
     * Always create clusters on the key frame boundary
     */
    MKV_GEN_KEY_FRAME_PROCESSING = (1 << 0),

    /**
     * Whether to use in-stream defined timestamps or call get time
     */
    MKV_GEN_IN_STREAM_TIME = (1 << 1),

    /**
     * Whether to generate absolute cluster timestamps
     */
    MKV_GEN_ABSOLUTE_CLUSTER_TIME = (1 << 2),

    /**
     * Whether to adapt Annex-B NALUs to Avcc NALUs
     */
    MKV_GEN_ADAPT_ANNEXB_NALS = (1 << 3),

    /**
     * Whether to adapt Avcc NALUs to Annex-B NALUs
     */
    MKV_GEN_ADAPT_AVCC_NALS = (1 << 4),

    /**
     * Whether to adapt Annex-B NALUs for the codec private data to Avcc format NALUs
     */
    MKV_GEN_ADAPT_ANNEXB_CPD_NALS = (1 << 5),
} MKV_BEHAVIOR_FLAGS;

/**
 * The representation of the Frame
 */
typedef struct __Frame {
    UINT32 version;

    /// Id of the frame
    UINT32 index;

    /// Flags associated with the frame (ex. IFrame for frames)
    FRAME_FLAGS flags;

    /// The decoding timestamp of the frame in 100ns precision
    UINT64 decodingTs;

    /// The presentation timestamp of the frame in 100ns precision
    UINT64 presentationTs;

    /// The duration of the frame in 100ns precision. Can be 0.
    UINT64 duration;

    /// Size of the frame data in bytes
    UINT32 size;

    /// The frame bits
    PBYTE frameData;

    /// Id of the track this frame belong to
    UINT64 trackId;
} Frame, *PFrame;

/*
 * End-of-Fragment frame initializer. This is used to easily initialize a local variable in a form of
 * Frame eofr = EOFR_FRAME_INITIALIZER;
 * putKinesisVideoFrame(&eofr));
 *
 * The initializer will zero all the fields and set the EoFr flag in flags.
 */
#define EOFR_FRAME_INITIALIZER                                                                                                                       \
    {                                                                                                                                                \
        FRAME_CURRENT_VERSION, 0, FRAME_FLAG_END_OF_FRAGMENT, 0, 0, 0, 0, NULL, 0                                                                    \
    }

/**
 * The representation of mkv video element
 */
typedef struct {
    UINT16 videoWidth;
    UINT16 videoHeight;
} TrackVideoConfig, *PTrackVideoConfig;

/**
 * The representation of mkv audio element
 */
typedef struct {
    DOUBLE samplingFrequency;
    UINT16 channelConfig;
    UINT16 bitDepth;
} TrackAudioConfig, *PTrackAudioConfig;

/**
 * Store custom information depending on whether if track is audio or video
 */
typedef union {
    TrackAudioConfig trackAudioConfig;
    TrackVideoConfig trackVideoConfig;
} TrackCustomData, *PTrackCustomData;

typedef struct {
    UINT32 version;

    /// Unique Identifier for TrackInfo
    UINT64 trackId;

    /// Codec ID of the stream. Null terminated.
    CHAR codecId[MKV_MAX_CODEC_ID_LEN + 1];

    /// Human readable track name. Null terminated.
    CHAR trackName[MKV_MAX_TRACK_NAME_LEN + 1];

    /// Size of the codec private data in bytes. Can be 0 if no CPD is used.
    UINT32 codecPrivateDataSize;

    /// Codec private data. Can be NULL if no CPD is used. Allocated in heap.
    PBYTE codecPrivateData;

    /// Track's content type.
    MKV_TRACK_INFO_TYPE trackType;

    /// Track type specific data.
    TrackCustomData trackCustomData;

    // ------------------------------- V0 compat ----------------------
} TrackInfo, *PTrackInfo;

/**
 * The representation of the packaged frame information
 */
typedef struct {
    /// Stream start timestamp adjusted with the timecode scale and the generator properties.
    UINT64 streamStartTs;

    /// Cluster timestamp adjusted with the timecode scale and the generator properties.
    UINT64 clusterPts;

    /// Frame decoding timestamp of first frame in the cluster adjusted with the timecode scale.
    UINT64 clusterDts;

    /// Frame presentation timestamp adjusted with the timecode scale.
    UINT64 framePts;

    /// Frame decoding timestamp adjusted with the timecode scale.
    UINT64 frameDts;

    /// Frame duration adjusted with the timecode scale.
    UINT64 duration;

    /// The offset where the original/adapted frame data begins
    UINT16 dataOffset;

    /// The state of the MKV stream generator.
    MKV_STREAM_STATE streamState;

} EncodedFrameInfo, *PEncodedFrameInfo;

/**
 * MKV Packager
 */
typedef struct __MkvGenerator MkvGenerator;
struct __MkvGenerator {
    UINT32 version;
    // NOTE: The internal structure follows
};

typedef struct __MkvGenerator* PMkvGenerator;

// https://wiki.multimedia.cx/index.php/MPEG-4_Audio
// should cover most of aac object types. we can always expand this list if needed.
typedef enum {
    AAC_MAIN = 1,
    AAC_LC = 2,
    AAC_SSR = 3,
    AAC_LTP = 4,
    SBR = 5,
    AAC_SCALABLE = 6,
} KVS_MPEG4_AUDIO_OBJECT_TYPES;

// 5 bits (Audio Object Type) | 4 bits (frequency index) | 4 bits (channel configuration) | 3 bits (not used)
#define KVS_AAC_CPD_SIZE_BYTE 2

/*
 * http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 * cpd structure (little endian):
 * - 2 bytes format code (0x06 0x00 for pcm alaw)
 * - 2 bytes number of channels
 * - 4 bytes sampling rate
 * - 4 bytes average bytes per second
 * - 2 bytes block align
 * - 2 bytes bit depth
 * - 2 bytes extra data (usually 0)
 */
#define KVS_PCM_CPD_SIZE_BYTE 18

typedef enum {
    KVS_PCM_FORMAT_CODE_ALAW = (UINT16) 0x0006,
    KVS_PCM_FORMAT_CODE_MULAW = (UINT16) 0x0007,
} KVS_PCM_FORMAT_CODE;

// Min/Max sampling rate for PCM alaw and mulaw. Referred pad template of gstreamer alawenc plugin
#define MIN_PCM_SAMPLING_RATE 8000
#define MAX_PCM_SAMPLING_RATE 192000

////////////////////////////////////////////////////
// Callbacks definitions
////////////////////////////////////////////////////
/**
 * Gets the current time in 100ns from some timestamp.
 *
 * @param customData Custom handle passed by the caller.
 *
 * @return Current time value in 100ns
 */
typedef UINT64 (*GetCurrentTimeFunc)(UINT64 customData);

////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////

PUBLIC_API STATUS mkvgenHasStreamStarted(PMkvGenerator, PBOOL);
/**
 * Create the MkvGenerator object
 *
 * @param contentType The content type of the stream
 * @param behaviorFlags The behavior flags
 * @param timecodeScale Default timecode scale which will be applied to the generated MKV in 100ns
 * @param clusterDuration Duration of the cluster in 100ns
 * @param[in] segmentUuid Optional Segment UUID to use with size MKV_SEGMENT_UUID_LEN. Otherwise random UUID is generated
 * @param[in] trackInfoList List of TrackInfo structures
 * @param trackInfoCount Number of the TrackInfo elements in the list
 * @param[in] clientId Optional client id string. Null terminated if specified.
 * @param getTimeFn the time function callback
 * @param customData custom data to be passed to the callback
 * @param ppMkvGenerator returns the newly created object
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS createMkvGenerator(PCHAR contentType, UINT32 behaviorFlags, UINT64 timecodeScale, UINT64 clusterDuration, PBYTE segmentUuid, PTrackInfo trackInfoList, UINT32 trackInfoCount, PCHAR clientId, GetCurrentTimeFunc getTimeFn, UINT64 customData, PMkvGenerator* ppMkvGenerator);

/**
 * Frees and de-allocates the memory of the MkvGenerator and it's sub-objects
 *
 * NOTE: This function is idempotent - can be called at various stages of construction.
 *
 * @param pMkvGenerator the object to free
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS freeMkvGenerator(PMkvGenerator pMkvGenerator);

/**
 * Resets the generator to the initial state
 *
 * @param pMkvGenerator the object to reset
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS mkvgenResetGenerator(PMkvGenerator pMkvGenerator);

/**
 * Generates the MKV header
 *
 * @param pMkvGenerator The generator object
 * @param pBuffer Buffer to hold the packaged bits
 * @param[in,out] pSize Size of the produced packaged bits
 * @param[out] pStreamStartTs Stream start timestamp
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS mkvgenGenerateHeader(PMkvGenerator pMkvGenerator, PBYTE pBuffer, PUINT32 pSize, PUINT64 pStreamStartTs);

/**
 * Generates the MKV Tags/Tag/SimpleTag/<TagName, TagString> element
 *
 * @param pMkvGenerator The generator object
 * @param pBuffer Buffer to hold the packaged bits
 * @param tagName Name of the tag
 * @param tagValue Value of the tag as a string
 * @param[in,out] pSize Size of the produced packaged bits
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS mkvgenGenerateTag(PMkvGenerator pMkvGenerator, PBYTE pBuffer, PCHAR tagName, PCHAR tagValue, PUINT32 pSize);

/**
 * Generates the MKV Tags/Tag/SimpleTag/<TagName, TagString> element
 * and allows you to select to start at Tags, Tag, or Simple
 *
 * @param pBuffer Buffer to hold the packaged bits
 * @param tagName Name of the tag
 * @param tagValue Value of the tag as a string
 * @param[in,out] pSize Size of the produced packaged bits
 * @param parent top parent in series of prefix tags to generate
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS mkvgenGenerateTagsChain(PBYTE pBuffer, PCHAR tagName, PCHAR tagValue, PUINT32 pSize, MKV_TREE_TYPE parent);

/**
 * Edits the sizes of an existings TAGS and TAG element in a buffer.
 *
 * @param pBuffer Buffer to hold the packaged bits
 * @param sizeIncrease Number of bytes to add to the size
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS mkvgenIncreaseTagsTagSize(PBYTE pBuffer, UINT32 sizeIncrease);

/**
 * Packages a frame into an MKV fragment
 *
 * @param pMkvGenerator The generator object
 * @param pFrame Frame to package
 * @param[in] pTrackInfo The track info object the frame belongs to
 * @param pBuffer Buffer to hold the packaged bits
 * @param[in,out] pSize Size of the produced packaged bits
 * @param[out] pEncodedFrameInfo Optional. Information about the encoded frame - optional.
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS mkvgenPackageFrame(PMkvGenerator pMkvGenerator, PFrame pFrame, PTrackInfo pTrackInfo, PBYTE pBuffer, PUINT32 pSize, PEncodedFrameInfo pEncodedFrameInfo);

/**
 * Converts an MKV timecode to a timestamp
 *
 * @param pMkvGenerator The generator object
 * @param timecode MKV timecode to convert
 * @param[out] pTimestamp The converted timestamp
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS mkvgenTimecodeToTimestamp(PMkvGenerator pMkvGenerator, UINT64 timecode, PUINT64 pTimestamp);

/**
 * Gets the MKV overhead in bytes for a specified type of frame
 *
 * @param pMkvGenerator The generator object
 * @param mkvStreamState Type of frame to get the overhead for
 * @param[out] pOverhead The overhead in bytes
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS mkvgenGetMkvOverheadSize(PMkvGenerator pMkvGenerator, MKV_STREAM_STATE mkvStreamState, PUINT32 pOverhead);

/**
 * Gets the current generator timestamps
 *
 * @param pMkvGenerator The generator object
 * @param[out] pStreamStartTs MKV stream start timestamp
 * @param[out] pClusterStartTs MKV cluster start timestamp
 * @param[out] pClusterStartDts Decoding timestamp of the first frame of the cluster
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS mkvgenGetCurrentTimestamps(PMkvGenerator pMkvGenerator, PUINT64 pStreamStartTs, PUINT64 pClusterStartTs, PUINT64 pClusterStartDts);

/**
 * Sets the Codec Private Data for a particular track
 *
 * @param pMkvGenerator The generator object
 * @param[in] trackId Track ID to set the Codec Private Data for
 * @param[in] codecPrivateDataSize Codec Private Data size
 * @param[in] codecPrivateData Codec private Data bytes
 *
 * @return STATUS code of the execution
 */
PUBLIC_API STATUS mkvgenSetCodecPrivateData(PMkvGenerator pMkvGenerator, UINT64 trackId, UINT32 codecPrivateDataSize, PBYTE codecPrivateData);

/**
 * Gets the track info for a specified track id
 *
 * @param[in] pTrackInfos Track info array
 * @param[in] trackInfoCount Track info count
 * @param[in] trackId Track ID
 * @param[out] ppTrackInfo Optional. Track info object matching the track id
 * @param[out] pIndex Optional. Track index
 *
 * @return Status of the operation
 */
PUBLIC_API STATUS mkvgenGetTrackInfo(PTrackInfo pTrackInfos, UINT32 trackInfoCount, UINT64 trackId, PTrackInfo* ppTrackInfo, PUINT32 pIndex);

/**
 * Generate AAC audio cpd
 *
 * @param[in] objectType MPEG4 object type
 * @param[in] samplingFrequency Sampling Frequency
 * @param[in] channelConfig Channel Count
 * @param[out] pBuffer Buffer for cpd, should have at least KVS_AAC_CPD_SIZE_BYTE (2 bytes)
 * @param[in] bufferLen size of buffer
 *
 * @return Status of the operation
 */
PUBLIC_API STATUS mkvgenGenerateAacCpd(KVS_MPEG4_AUDIO_OBJECT_TYPES objectType, UINT32 samplingFrequency, UINT16 channelConfig, PBYTE pBuffer, UINT32 bufferLen);

/**
 * Generate PCM audio cpd
 *
 * @param[in] format pcm format code. Either KVS_PCM_FORMAT_CODE_ALAW or KVS_PCM_FORMAT_CODE_MUALAW
 * @param[in] samplingRate Sampling Frequency
 * @param[in] channels Channel Count
 * @param[out] buffer Buffer for cpd, should have at least KVS_PCM_CPD_SIZE_BYTE (18 bytes)
 * @param[in] bufferLen size of buffer
 *
 * @return Status of the operation
 */
PUBLIC_API STATUS mkvgenGeneratePcmCpd(KVS_PCM_FORMAT_CODE format, UINT32 samplingRate, UINT16 channels, PBYTE buffer, UINT32 bufferLen);

#ifdef __cplusplus
}
#endif
#endif /* __MKV_GEN_INCLUDE__ */
