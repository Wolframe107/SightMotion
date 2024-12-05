// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2017 Magic Leap, Inc. (COMPANY) All Rights Reserved.
// Magic Leap, Inc. Confidential and Proprietary
//
// NOTICE: All information contained herein is, and remains the property
// of COMPANY. The intellectual and technical concepts contained herein
// are proprietary to COMPANY and may be covered by U.S. and Foreign
// Patents, patents in process, and are protected by trade secret or
// copyright law. Dissemination of this information or reproduction of
// this material is strictly forbidden unless prior written permission is
// obtained from COMPANY. Access to the source code contained herein is
// hereby forbidden to anyone except current COMPANY employees, managers
// or contractors who have executed Confidentiality and Non-disclosure
// agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended
// publication or disclosure of this source code, which includes
// information that is confidential and/or proprietary, and is a trade
// secret, of COMPANY. ANY REPRODUCTION, MODIFICATION, DISTRIBUTION,
// PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR THROUGH USE OF THIS
// SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF COMPANY IS
// STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND
// INTERNATIONAL TREATIES. THE RECEIPT OR POSSESSION OF THIS SOURCE
// CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE,
// USE, OR SELL ANYTHING THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
//
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

#include "ml_api.h"

ML_EXTERN_C_BEGIN

/*!
  \defgroup MediaPlayer Media Player
  \addtogroup MediaPlayer
  \sharedobject ml_mediacodeclist
  \brief APIs for retrieving all supported encoders and decoders.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

#define MAX_CODEC_NAME_LENGTH 64

/*! Bit mask for specifying the type of codec being queried using MLMediaCodecListGetMatchingCodecs(). */
typedef enum MLMediaCodecListCodecTypeFlag {
  /*! Software. */
  MLMediaCodecListCodecTypeFlag_Software     = 1 << 0,
  /*! Hardware. */
  MLMediaCodecListCodecTypeFlag_Hardware     = 1 << 1,
  /*! Ensure enum is represented as 32 Bits. */
  MLMediaCodecListCodecTypeFlag_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecListCodecTypeFlag;

/*! Bit mask for checking the capability of a codec after queried via #MLMediaCodecListGetCapabilityFlag. */
typedef enum MLMediaCodecListCapabilityFlag {
  /*! Adaptive playback. */
  MLMediaCodecListCapabilityFlag_AdaptivePlayback = 1 << 0,
  /*! Secure playback. */
  MLMediaCodecListCapabilityFlag_SecurePlayback   = 1 << 1,
  /*! Tunneled playback. */
  MLMediaCodecListCapabilityFlag_TunneledPlayback = 1 << 2,
  /*! Ensure enum is represented as 32 Bits. */
  MLMediaCodecListCapabilityFlag_Ensure32Bits     = 0x7FFFFFFF
} MLMediaCodecListCapabilityFlag;

/*!
  \brief Enumeration defining possible uncompressed image/video formats.

  \apilevel 9
*/
typedef enum MLMediaCodecColorFormat {
  /*! Unused: Placeholder value when format is N/A. */
  MLMediaCodecColorFormat_Unused = 0,
  /*! Monochrome: black and white. */
  MLMediaCodecColorFormat_Monochrome = 1,
  /*! 8BitRGB332: Red 7:5, Green 4:2, Blue 1:0. */
  MLMediaCodecColorFormat_8BitRGB332 = 2,
  /*! 12BitRGB444: Red 11:8, Green 7:4, Blue 3:0. */
  MLMediaCodecColorFormat_12BitRGB444 = 3,
  /*! 16BitARGB4444: Alpha 15:12, Red 11:8, Green 7:4, Blue 3:0. */
  MLMediaCodecColorFormat_16BitARGB4444 = 4,
  /*! 16BitARGB1555: Alpha 15, Red 14:10, Green 9:5, Blue 4:0. */
  MLMediaCodecColorFormat_16BitARGB1555 = 5,
  /*! 16BitRGB565: Red 15:11, Green 10:5, Blue 4:0. */
  MLMediaCodecColorFormat_16BitRGB565 = 6,
  /*! 16BitBGR565: Blue 15:11, Green 10:5, Red 4:0. */
  MLMediaCodecColorFormat_16BitBGR565 = 7,
  /*! 18BitRGB666: Red 17:12, Green 11:6, Blue 5:0. */
  MLMediaCodecColorFormat_18BitRGB666 = 8,
  /*! 18BitARGB1665: Alpha 17, Red 16:11, Green 10:5, Blue 4:0. */
  MLMediaCodecColorFormat_18BitARGB1665 = 9,
  /*! 19BitARGB1666: Alpha 18, Red 17:12, Green 11:6, Blue 5:0. */
  MLMediaCodecColorFormat_19BitARGB1666 = 10,
  /*! 24BitRGB888: Red 24:16, Green 15:8, Blue 7:0. */
  MLMediaCodecColorFormat_24BitRGB888 = 11,
  /*! 24BitBGR888: Blue 24:16, Green 15:8, Red 7:0. */
  MLMediaCodecColorFormat_24BitBGR888 = 12,
  /*! 24BitARGB1887: Alpha 23, Red 22:15, Green 14:7, Blue 6:0. */
  MLMediaCodecColorFormat_24BitARGB1887 = 13,
  /*! 25BitARGB1888: Alpha 24, Red 23:16, Green 15:8, Blue 7:0. */
  MLMediaCodecColorFormat_25BitARGB1888 = 14,
  /*! 32BitBGRA8888: Blue 31:24, Green 23:16, Red 15:8, Alpha 7:0. */
  MLMediaCodecColorFormat_32BitBGRA8888 = 15,
  /*! 32BitARGB8888: Alpha 31:24, Red 23:16, Green 15:8, Blue 7:0. */
  MLMediaCodecColorFormat_32BitARGB8888 = 16,
  /*! YUV411Planar: U,Y are subsampled by a factor of 4 horizontally. */
  MLMediaCodecColorFormat_YUV411Planar = 17,
  /*! YUV411PackedPlanar: packed per payload in planar slices. */
  MLMediaCodecColorFormat_YUV411PackedPlanar = 18,
  /*! YUV420Planar: Three arrays Y,U,V. */
  MLMediaCodecColorFormat_YUV420Planar = 19,
  /*! YUV420PackedPlanar: packed per payload in planar slices. */
  MLMediaCodecColorFormat_YUV420PackedPlanar = 20,
  /*! YUV420SemiPlanar: Two arrays, one is all Y, the other is U and V. */
  MLMediaCodecColorFormat_YUV420SemiPlanar = 21,
  /*! YUV422Planar: Three arrays Y,U,V. */
  MLMediaCodecColorFormat_YUV422Planar = 22,
  /*! YUV422PackedPlanar: packed per payload in planar slices. */
  MLMediaCodecColorFormat_YUV422PackedPlanar = 23,
  /*! YUV422SemiPlanar: Two arrays, one is all Y, the other is U and V. */
  MLMediaCodecColorFormat_YUV422SemiPlanar = 24,
  /*! YCbYCr: Organized as 16Bit YUYV (i.e. YCbYCr). */
  MLMediaCodecColorFormat_YCbYCr = 25,
  /*! YCrYCb: Organized as 16Bit YVYU (i.e. YCrYCb). */
  MLMediaCodecColorFormat_YCrYCb = 26,
  /*! CbYCrY: Organized as 16Bit UYVY (i.e. CbYCrY). */
  MLMediaCodecColorFormat_CbYCrY = 27,
  /*! CrYCbY: Organized as 16Bit VYUY (i.e. CrYCbY). */
  MLMediaCodecColorFormat_CrYCbY = 28,
  /*! YUV444Interleaved: Each pixel contains equal parts YUV. */
  MLMediaCodecColorFormat_YUV444Interleaved = 29,
  /*! RawBayer8Bit: SMIA camera output format. */
  MLMediaCodecColorFormat_RawBayer8Bit = 30,
  /*! RawBayer10Bit: SMIA camera output format. */
  MLMediaCodecColorFormat_RawBayer10Bit = 31,
  /*! RawBayer8Bitcompressed: SMIA camera output format. */
  MLMediaCodecColorFormat_RawBayer8Bitcompressed = 32,
  /*! Deprecated. Use MLMediaCodecColorFormat_L8. */
  MLMediaCodecColorFormat_L2 = 33,
  /*! Deprecated. Use MLMediaCodecColorFormat_L8. */
  MLMediaCodecColorFormat_L4 = 34,
  /*! 8 Bits per pixel Y color format. */
  MLMediaCodecColorFormat_L8 = 35,
  /*! 16 Bits per pixel, little-endian Y color format. */
  MLMediaCodecColorFormat_L16 = 36,
  /*! Deprecated. Use MLMediaCodecColorFormat_L16. */
  MLMediaCodecColorFormat_L24 = 37,
  /*! Deprecated. Use MLMediaCodecColorFormat_L16. */
  MLMediaCodecColorFormat_L32 = 38,
  /*! YUV420PackedSemiPlanar. */
  MLMediaCodecColorFormat_YUV420PackedSemiPlanar,
  /*! YUV422PackedSemiPlanar. */
  MLMediaCodecColorFormat_YUV422PackedSemiPlanar,
  /*! 18BitBGR666. */
  MLMediaCodecColorFormat_18BitBGR666,
  /*! 24BitARGB6666. */
  MLMediaCodecColorFormat_24BitARGB6666,
  /*! 24BitABGR6666. */
  MLMediaCodecColorFormat_24BitABGR6666,
  /*! Reserved region for introducing Khronos Standard Extensions. */
  MLMediaCodecColorFormat_KhronosExtensions = 0x6F000000,
  /*! Reserved region for introducing Vendor Extensions. */
  MLMediaCodecColorFormat_VendorStartUnused = 0x7F000000,
  /*!
    \brief Reserved android opaque color format.
     Tells the encoder that the actual color format will be relayed by the
     Graphics memory allocator Buffers.
  */
  MLMediaCodecColorFormat_AndroidOpaque = 0x7F000789,
  /*! 32BitRGBA8888. */
  MLMediaCodecColorFormat_32BitRGBA8888 = 0x7F00A000,
  /*!
    \brief Flexible 8-bit YUV format.
     Codec should report this format as being supported if it supports any YUV420 packed planar or semiplanar formats.
     When port is set to use this format, codec can substitute any YUV420 packed planar or semiplanar format for it.
  */
  MLMediaCodecColorFormat_YUV420Flexible = 0x7F420888,
  /*! 10-bit or 12-bit YUV format, LSB-justified (0's on higher bits). */
  MLMediaCodecColorFormat_YUV420Planar16 = 0x7F42016B,
  /*!
    \brief Packed 10-bit YUV444 representation that includes 2 bits of alpha.
     Each pixel is 32-bit. Bits 0-9 contain the U sample, bits 10-19 contain the Y sample,
     bits 20-29 contain the V sample, and bits 30-31 contain the alpha value.
  */
  MLMediaCodecColorFormat_YUV444Y410 = 0x7F444AAA,

  /*! TI's YUV420PackedSemiPlanar. */
  MLMediaCodecColorFormat_TIYUV420PackedSemiPlanar = 0x7F000100,
  /*! QCOM's YVU420SemiPlanar. */
  MLMediaCodecColorFormat_QCOMYVU420SemiPlanar = 0x7FA30C00,
  /*! QCOM's YUV420PackedSemiPlanar64x32Tile2m8ka. */
  MLMediaCodecColorFormat_QCOMYUV420PackedSemiPlanar64x32Tile2m8ka = 0x7FA30C03,
  /*! QCOM's YUV420PackedSemiPlanar32m. */
  MLMediaCodecColorFormat_QCOMYUV420PackedSemiPlanar32m = 0x7FA30C04,
  /*! SEC's NV12Tiled. */
  MLMediaCodecColorFormat_SECNV12Tiled = 0x7FC00002,

  /*! Ensure enum is represented as 32 Bits. */
  MLMediaCodecColorFormat_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecColorFormat;

/*!
  \brief Enumeration defining the Codec priority.

  \apilevel 9
*/
typedef enum MLMediaCodecPriority {
  /*!
    \brief realtime priority - meaning that the codec shall support the given performance configuration (e.g. framerate) at realtime.
    This should only be used by media playback, capture, and possibly by realtime communication scenarios if best effort performance is not suitable.
  */
  MLMediaCodecPriority_RealTime = 0,
  /*! non-realtime priority (best effort). */
  MLMediaCodecPriority_NonRealTime = 1,
  /*! Ensure enum is represented as 32 Bits. */
  MLMediaCodecPriority_Ensure32Bits = 0x7FFFFFFF,
} MLMediaCodecPriority;

/*!
  \brief Enumeration of possible methods to use for Intra Refresh.

  \apilevel 9
*/
typedef enum MLMediaCodecIntraRefreshMode {
  /*! Cyclic. */
  MLMediaCodecIntraRefreshMode_Cyclic = 0,
  /*! Adaptive. */
  MLMediaCodecIntraRefreshMode_Adaptive = 1,
  /*! Both. */
  MLMediaCodecIntraRefreshMode_Both = 2,
  MLMediaCodecIntraRefreshMode_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecIntraRefreshMode;

/*!
  \brief Enumeration defining Codec Bitrate modes.

  \apilevel 9
*/
typedef enum MLMediaCodecBitrateMode {
  /*! Constant quality mode. */
  MLMediaCodecBitrateMode_CQ = 0,
  /*! Variable bitrate mode. */
  MLMediaCodecBitrateMode_VBR = 1,
  /*! Constant bitrate mode. */
  MLMediaCodecBitrateMode_CBR = 2,
  /*! Ensure enum is represented as 32 Bits. */
  MLMediaCodecBitrateMode_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecBitrateMode;

/*!
  \brief Enumeration defining Codec profile types.

  This is a consolidated list for all the codecs that support profiles.
  Each profile indicates support for various performance bounds and different annexes.

  \note A codec may not support all the profiles and levels listed below. For any given codec,
  the supported profiles and levels can be queried using \ref MLMediaCodecListGetSupportedProfileLevels.

  \apilevel 9
*/
typedef enum MLMediaCodecProfileType {
  /*! H263 Baseline Profile: H.263 (V1), no optional modes. */
  MLMediaCodecProfileType_H263Baseline            = 0x01,
  /*! H263 H.320 Coding Efficiency Backward Compatibility Profile: H.263+ (V2), includes annexes I, J, L.4 and T. */
  MLMediaCodecProfileType_H263H320Coding          = 0x02,
  /*! H263 Backward Compatibility Profile: H.263 (V1), includes annex F. */
  MLMediaCodecProfileType_H263BackwardCompatible  = 0x04,
  /*! H263 Interactive Streaming Wireless Profile: H.263+ (V2), includes annexes I, J, K and T. */
  MLMediaCodecProfileType_H263ISWV2               = 0x08,
  /*! H263 Interactive Streaming Wireless Profile: H.263++ (V3), includes profile 3 and annexes V and W.6.3.8. */
  MLMediaCodecProfileType_H263ISWV3               = 0x10,
  /*! H263 Conversational High Compression Profile: H.263++ (V3), includes profiles 1 & 2 and annexes D and U. */
  MLMediaCodecProfileType_H263HighCompression     = 0x20,
  /*! H263 Conversational Internet Profile: H.263++ (V3), includes profile 5 and annex K. */
  MLMediaCodecProfileType_H263Internet            = 0x40,
  /*! H263 Conversational Interlace Profile: H.263++ (V3), includes profile 5 and annex W.6.3.11. */
  MLMediaCodecProfileType_H263Interlace           = 0x80,
  /*! H263 High Latency Profile: H.263++ (V3), includes profile 6 and annexes O.1 and P.5. */
  MLMediaCodecProfileType_H263HighLatency         = 0x100,

  /*! MPEG-2 Simple Profile. */
  MLMediaCodecProfileType_MPEG2Simple = 0,
  /*! MPEG-2 Main Profile. */
  MLMediaCodecProfileType_MPEG2Main = 1,
  /*! MPEG-2 4:2:2 Profile. */
  MLMediaCodecProfileType_MPEG2422 = 2,
  /*! MPEG-2 SNR Profile. */
  MLMediaCodecProfileType_MPEG2SNR = 3,
  /*! MPEG-2 Spatial Profile. */
  MLMediaCodecProfileType_MPEG2Spatial = 4,
  /*! MPEG-2 High Profile. */
  MLMediaCodecProfileType_MPEG2High = 5,

  /*! MPEG-4 Simple Profile, Levels 1-3. */
  MLMediaCodecProfileType_MPEG4Simple = 0x01,
  /*! MPEG-4 Simple Scalable Profile, Levels 1-2. */
  MLMediaCodecProfileType_MPEG4SimpleScalable = 0x02,
  /*! MPEG-4 Core Profile, Levels 1-2. */
  MLMediaCodecProfileType_MPEG4Core = 0x04,
  /*! MPEG-4 Main Profile, Levels 2-4. */
  MLMediaCodecProfileType_MPEG4Main = 0x08,
  /*! MPEG-4 N-bit Profile, Level 2. */
  MLMediaCodecProfileType_MPEG4Nbit = 0x10,
  /*! MPEG-4 Scalable Texture Profile, Level 1. */
  MLMediaCodecProfileType_MPEG4ScalableTexture = 0x20,
  /*! MPEG-4 Simple Face Animation Profile, Levels 1-2. */
  MLMediaCodecProfileType_MPEG4SimpleFace = 0x40,
  /*! MPEG-4 Simple Face and Body Animation (FBA) Profile, Levels 1-2. */
  MLMediaCodecProfileType_MPEG4SimpleFBA = 0x80,
  /*! MPEG-4 Basic Animated Texture Profile, Levels 1-2. */
  MLMediaCodecProfileType_MPEG4BasicAnimated = 0x100,
  /*! MPEG-4 Hybrid Profile, Levels 1-2. */
  MLMediaCodecProfileType_MPEG4Hybrid = 0x200,
  /*! MPEG-4 Advanced Real Time Simple Profiles, Levels 1-4. */
  MLMediaCodecProfileType_MPEG4AdvancedRealTime = 0x400,
  /*! MPEG-4 Core Scalable Profile, Levels 1-3. */
  MLMediaCodecProfileType_MPEG4CoreScalable = 0x800,
  /*! MPEG-4 Advanced Coding Efficiency Profile, Levels 1-4. */
  MLMediaCodecProfileType_MPEG4AdvancedCoding = 0x1000,
  /*! MPEG-4 Advanced Core Profile, Levels 1-2. */
  MLMediaCodecProfileType_MPEG4AdvancedCore = 0x2000,
  /*! MPEG-4 Advanced Scalable Texture, Levels 2-3. */
  MLMediaCodecProfileType_MPEG4AdvancedScalable = 0x4000,
  /*! MPEG-4 Advanced Simple. */
  MLMediaCodecProfileType_MPEG4AdvancedSimple = 0x8000,

  /*! AVC Baseline profile. */
  MLMediaCodecProfileType_AVCBaseline = 0x01,
  /*! AVC Main profile. */
  MLMediaCodecProfileType_AVCMain     = 0x02,
  /*! AVC Extended profile. */
  MLMediaCodecProfileType_AVCExtended = 0x04,
  /*! AVC High profile. */
  MLMediaCodecProfileType_AVCHigh     = 0x08,
  /*! AVC High 10 profile. */
  MLMediaCodecProfileType_AVCHigh10   = 0x10,
  /*! AVC High 4:2:2 profile. */
  MLMediaCodecProfileType_AVCHigh422  = 0x20,
  /*! AVC High 4:4:4 profile. */
  MLMediaCodecProfileType_AVCHigh444  = 0x40,

  /*! VP8 Main profile. */
  MLMediaCodecProfileType_VP8Main = 0x01,

  /*! VP9 Profile 0 4:2:0 8-bit. */
  MLMediaCodecProfileType_VP90 = 0x01,
  /*! VP9 Profile 1 4:2:2 8-bit. */
  MLMediaCodecProfileType_VP91 = 0x02,
  /*! VP9 Profile 2 4:2:0 10-bit. */
  MLMediaCodecProfileType_VP92 = 0x04,
  /*! VP9 Profile 3 4:2:2 10-bit. */
  MLMediaCodecProfileType_VP93 = 0x08,
  /*! VP9 Profile 2 4:2:0 10-bit HDR. */
  MLMediaCodecProfileType_VP92HDR = 0x1000,
  /*! VP9 Profile 3 4:2:2 10-bit HDR. */
  MLMediaCodecProfileType_VP93HDR = 0x2000,
  /*! VP9 Profile 2 4:2:0 10-bit HDR10Plus. */
  MLMediaCodecProfileType_VP92HDR10Plus = 0x4000,
  /*! VP9 Profile 3 4:2:2 10-bit HDR10Plus. */
  MLMediaCodecProfileType_VP93HDR10Plus = 0x8000,

  /*! HEVC Main profile. */
  MLMediaCodecProfileType_HEVCMain        = 0x01,
  /*! HEVC Main 1.0 profile. */
  MLMediaCodecProfileType_HEVCMain10      = 0x02,
  /*! HEVC Main Still profile. */
  MLMediaCodecProfileType_HEVCMainStill   = 0x04,
  /*! HEVC Main HDR profile. */
  MLMediaCodecProfileType_HEVCMain10HDR10 = 0x1000,
  /*! HEVC Main HDR+ profile. */
  MLMediaCodecProfileType_HEVCMain10HDR10Plus = 0x2000,

  /*! AAC Null, not used. */
  MLMediaCodecProfileType_AACObjectNull = 0,
  /*! AAC Main object. */
  MLMediaCodecProfileType_AACObjectMain = 1,
  /*! AAC Low Complexity object (AAC profile). */
  MLMediaCodecProfileType_AACObjectLC = 2,
  /*! AAC Scalable Sample Rate object. */
  MLMediaCodecProfileType_AACObjectSS = 3,
  /*! AAC Long Term Prediction object. */
  MLMediaCodecProfileType_AACObjectLTP = 4,
  /*! AAC High Efficiency (object type SBR, HE-AAC profile). */
  MLMediaCodecProfileType_AACObjectHE = 5,
  /*! AAC Scalable object. */
  MLMediaCodecProfileType_AACObjectScalable = 6,
  /*! ER AAC Low Complexity object (Error Resilient AAC-LC). */
  MLMediaCodecProfileType_AACObjectERLC = 17,
  /*! AAC Low Delay object (Error Resilient). */
  MLMediaCodecProfileType_AACObjectLD = 23,
  /*! AAC High Efficiency with Parametric Stereo coding (HE-AAC v2, object type PS). */
  MLMediaCodecProfileType_AACObjectHE_PS = 29,

  /*! WMA profile unused or unknown . */
  MLMediaCodecProfileType_WMAProfileUnused = 0,
  /*! WMA version 9 profile L1. */
  MLMediaCodecProfileType_WMAProfileL1 = 1,
  /*! WMA version 9 profile L2. */
  MLMediaCodecProfileType_WMAProfileL2 = 2,
  /*! WMA version 9 profile L3. */
  MLMediaCodecProfileType_WMAProfileL3 = 3,

  /*! Ensure enum is represented as 32 Bits. */
  MLMediaCodecProfileType_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecProfileType;

/*!
  \brief Enumeration defining Codec Level types.

  This is a consolidated list for all the codecs that support profiles.
  Each level indicates support for various frame sizes, bit rates, decoder frame rates.

  \note A codec may not support all the profiles and levels listed below. For any given codec,
  the supported profiles and levels can be queried using \ref MLMediaCodecListGetSupportedProfileLevels.

  \apilevel 9
*/
typedef enum MLMediaCodecLevelType {
  /*! H263 Level 1.0. */
  MLMediaCodecLevelType_H263Level10  = 0x01,
  /*! H263 Level 2.0. */
  MLMediaCodecLevelType_H263Level20  = 0x02,
  /*! H263 Level 3.0. */
  MLMediaCodecLevelType_H263Level30  = 0x04,
  /*! H263 Level 4.0. */
  MLMediaCodecLevelType_H263Level40  = 0x08,
  /*! H263 Level 4.5. */
  MLMediaCodecLevelType_H263Level45  = 0x10,
  /*! H263 Level 5.0. */
  MLMediaCodecLevelType_H263Level50  = 0x20,
  /*! H263 Level 6.0. */
  MLMediaCodecLevelType_H263Level60  = 0x40,
  /*! H263 Level 7.0. */
  MLMediaCodecLevelType_H263Level70  = 0x80,

  /*! MPEG-2 Low Level. */
  MLMediaCodecLevelType_MPEG2LevelLL = 0,
  /*! MPEG-2 Main Level. */
  MLMediaCodecLevelType_MPEG2LevelML = 1,
  /*! MPEG-2 High 1440. */
  MLMediaCodecLevelType_MPEG2LevelH14 = 2,
  /*! MPEG-2 High Level. */
  MLMediaCodecLevelType_MPEG2LevelHL = 3,

  /*! MPEG-4 Level 0. */
  MLMediaCodecLevelType_MPEG4Level0 = 0x01,
  /*! MPEG-4 Level 0b. */
  MLMediaCodecLevelType_MPEG4Level0b = 0x02,
  /*! MPEG-4 Level 1. */
  MLMediaCodecLevelType_MPEG4Level1 = 0x04,
  /*! MPEG-4 Level 2. */
  MLMediaCodecLevelType_MPEG4Level2 = 0x08,
  /*! MPEG-4 Level 3. */
  MLMediaCodecLevelType_MPEG4Level3 = 0x10,
  /*! MPEG-4 Level 4. */
  MLMediaCodecLevelType_MPEG4Level4 = 0x20,
  /*! MPEG-4 Level 4a. */
  MLMediaCodecLevelType_MPEG4Level4a = 0x40,
  /*! MPEG-4 Level 5. */
  MLMediaCodecLevelType_MPEG4Level5 = 0x80,

  /*! AVC Level 1. */
  MLMediaCodecLevelType_AVCLevel1       = 0x01,
  /*! AVC Level 1.b */
  MLMediaCodecLevelType_AVCLevel1b      = 0x02,
  /*! AVC Level 1.1 */
  MLMediaCodecLevelType_AVCLevel11      = 0x04,
  /*! AVC Level 1.2. */
  MLMediaCodecLevelType_AVCLevel12      = 0x08,
  /*! AVC Level 1.3. */
  MLMediaCodecLevelType_AVCLevel13      = 0x10,
  /*! AVC Level 2. */
  MLMediaCodecLevelType_AVCLevel2       = 0x20,
  /*! AVC Level 2.1. */
  MLMediaCodecLevelType_AVCLevel21      = 0x40,
  /*! AVC Level 2.2. */
  MLMediaCodecLevelType_AVCLevel22      = 0x80,
  /*! AVC Level 3. */
  MLMediaCodecLevelType_AVCLevel3       = 0x100,
  /*! AVC Level 3.1. */
  MLMediaCodecLevelType_AVCLevel31      = 0x200,
  /*! AVC Level 3.2. */
  MLMediaCodecLevelType_AVCLevel32      = 0x400,
  /*! AVC Level 4. */
  MLMediaCodecLevelType_AVCLevel4       = 0x800,
  /*! AVC Level 4.1. */
  MLMediaCodecLevelType_AVCLevel41      = 0x1000,
  /*! AVC Level 4.2. */
  MLMediaCodecLevelType_AVCLevel42      = 0x2000,
  /*! AVC Level 5. */
  MLMediaCodecLevelType_AVCLevel5       = 0x4000,
  /*! AVC Level 5.1. */
  MLMediaCodecLevelType_AVCLevel51      = 0x8000,

  /*! VP8 Level version 0. */
  MLMediaCodecLevelType_VP8LevelVersion0 = 0x01,
  /*! VP8 Level version 1. */
  MLMediaCodecLevelType_VP8LevelVersion1 = 0x02,
  /*! VP8 Level version 2. */
  MLMediaCodecLevelType_VP8LevelVersion2 = 0x04,
  /*! VP8 Level version 3. */
  MLMediaCodecLevelType_VP8LevelVersion3 = 0x08,

  /*! VP9 Level 5.1. */
  MLMediaCodecLevelType_VP9Level1  = 0x1,
  /*! VP9 Level 1.1. */
  MLMediaCodecLevelType_VP9Level11 = 0x2,
  /*! VP9 Level 2. */
  MLMediaCodecLevelType_VP9Level2  = 0x4,
  /*! VP9 Level 2.1. */
  MLMediaCodecLevelType_VP9Level21 = 0x8,
  /*! VP9 Level 3. */
  MLMediaCodecLevelType_VP9Level3  = 0x10,
  /*! VP9 Level 3.1. */
  MLMediaCodecLevelType_VP9Level31 = 0x20,
  /*! VP9 Level 4. */
  MLMediaCodecLevelType_VP9Level4  = 0x40,
  /*! VP9 Level 4.1. */
  MLMediaCodecLevelType_VP9Level41 = 0x80,
  /*! VP9 Level 5. */
  MLMediaCodecLevelType_VP9Level5  = 0x100,
  /*! VP9 Level 5.1. */
  MLMediaCodecLevelType_VP9Level51 = 0x200,
  /*! VP9 Level 5.2. */
  MLMediaCodecLevelType_VP9Level52 = 0x400,
  /*! VP9 Level 6. */
  MLMediaCodecLevelType_VP9Level6  = 0x800,
  /*! VP9 Level 6.1. */
  MLMediaCodecLevelType_VP9Level61 = 0x1000,
  /*! VP9 Level 6.2. */
  MLMediaCodecLevelType_VP9Level62 = 0x2000,

  /*! HEVC Main Level 1. */
  MLMediaCodecLevelType_HEVCMainTierLevel1  = 0x1,
  /*! HEVC High Level 1. */
  MLMediaCodecLevelType_HEVCHighTierLevel1  = 0x2,
  /*! HEVC Main Level 2. */
  MLMediaCodecLevelType_HEVCMainTierLevel2  = 0x4,
  /*! HEVC High Level 2. */
  MLMediaCodecLevelType_HEVCHighTierLevel2  = 0x8,
  /*! HEVC Main Level 2.1. */
  MLMediaCodecLevelType_HEVCMainTierLevel21 = 0x10,
  /*! HEVC High Level 2.1. */
  MLMediaCodecLevelType_HEVCHighTierLevel21 = 0x20,
  /*! HEVC Main Level 3. */
  MLMediaCodecLevelType_HEVCMainTierLevel3  = 0x40,
  /*! HEVC High Level 3. */
  MLMediaCodecLevelType_HEVCHighTierLevel3  = 0x80,
  /*! HEVC Main Level 3.1. */
  MLMediaCodecLevelType_HEVCMainTierLevel31 = 0x100,
  /*! HEVC High Level 3.1. */
  MLMediaCodecLevelType_HEVCHighTierLevel31 = 0x200,
  /*! HEVC Main Level 4. */
  MLMediaCodecLevelType_HEVCMainTierLevel4  = 0x400,
  /*! HEVC High Level 4. */
  MLMediaCodecLevelType_HEVCHighTierLevel4  = 0x800,
  /*! HEVC Main Level 4.1. */
  MLMediaCodecLevelType_HEVCMainTierLevel41 = 0x1000,
  /*! HEVC High Level 4.1. */
  MLMediaCodecLevelType_HEVCHighTierLevel41 = 0x2000,
  /*! HEVC Main Level 5. */
  MLMediaCodecLevelType_HEVCMainTierLevel5  = 0x4000,
  /*! HEVC High Level 5. */
  MLMediaCodecLevelType_HEVCHighTierLevel5  = 0x8000,
  /*! HEVC Main Level 5.1. */
  MLMediaCodecLevelType_HEVCMainTierLevel51 = 0x10000,
  /*! HEVC High Level 5.1. */
  MLMediaCodecLevelType_HEVCHighTierLevel51 = 0x20000,
  /*! HEVC Main Level 5.2. */
  MLMediaCodecLevelType_HEVCMainTierLevel52 = 0x40000,
  /*! HEVC High Level 5.2. */
  MLMediaCodecLevelType_HEVCHighTierLevel52 = 0x80000,
  /*! HEVC Main Level 6. */
  MLMediaCodecLevelType_HEVCMainTierLevel6  = 0x100000,
  /*! HEVC High Level 6. */
  MLMediaCodecLevelType_HEVCHighTierLevel6  = 0x200000,
  /*! HEVC Main Level 6.1. */
  MLMediaCodecLevelType_HEVCMainTierLevel61 = 0x400000,
  /*! HEVC High Level 6.1. */
  MLMediaCodecLevelType_HEVCHighTierLevel61 = 0x800000,
  /*! HEVC Main Level 6.2. */
  MLMediaCodecLevelType_HEVCMainTierLevel62 = 0x1000000,
  /*! HEVC High Level 6.2. */
  MLMediaCodecLevelType_HEVCHighTierLevel62 = 0x2000000,

  /*! Ensure enum is represented as 32 Bits. */
  MLMediaCodecLevelType_Ensure32Bits = 0x7FFFFFFF,
} MLMediaCodecLevelType;

/*! Used to store the list of available codec names or the list of supported mime types. */
typedef struct MLMediaCodecListQueryResults {
  size_t  count;
  char    **data;
} MLMediaCodecListQueryResults;

/*!
  \brief Used to store the list of codec profile levels.
  \apilevel 6
*/
typedef struct MLMediaCodecListProfileLevel {
  /*! Codec profile as defined by MLMediaCodecProfileType. */
  uint32_t profile;
  /*! Codec level as defined by MLMediaCodecLevelType. */
  uint32_t level;
} MLMediaCodecListProfileLevel;

/*!
  \brief Obtain the number of available codecs.

  \param[out] out_codec_count Number of available codecs.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListCountCodecs(uint64_t *out_codec_count);

/*!
  \brief Determine whether a codec is a software codec.

  \param[in] codec_name Name of the codec.
  \param[out] out_val \c true if the codec is a software codec and \c false otherwise.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListIsSoftwareCodec(const char *codec_name, bool *out_val);

/*!
  \brief Obtain a list of matching codecs for a given codec mime.

  The memory used to store the list is maintained by the library.
  User shall call MLMediaCodecListQueryResultsRelease() to release it.

  \param[in] mime Codec mime.
  \param[in] is_encoder \c true if querying for encoder and false otherwise.
  \param[in] flag Whether querying for software-only or hardware-only,
             defined by #MLMediaCodecListCodecTypeFlag.
  \param[out] out_matching_codecs List of codecs supporting the given mime.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListGetMatchingCodecs(const char *mime, bool is_encoder, MLMediaCodecListCodecTypeFlag flag, MLMediaCodecListQueryResults *out_matching_codecs);

/*!
  \brief Obtain the codec matching the given codec type from the codec list.

  \param[in] type Codec mime.
  \param[in] is_encoder \c true if querying for encoder and \c false otherwise.
  \param[in] start_index Index from which to search in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[out] out_index Index of the matching codec or -2.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListGetCodecByType(const char *type, bool is_encoder, uint64_t start_index, int64_t *out_index);

/*!
  \brief Obtain the codec from the codec matching the given codec name from the codec list.

  \param[in] name Codec name.
  \param[out] out_index Index of the matching codec or -2.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListGetCodecByName(const char *name, int64_t *out_index);

/*!
  \brief Confirm whether a component is an Encoder or Decoder.

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[out] out_val \c true if the codec is an encoder and \c false otherwise.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListIsEncoder(uint64_t index, bool *out_val);

/*!
  \brief Obtain a codec name.

  User shall allocate at least #MAX_CODEC_NAME_LENGTH bytes of memory for
  storing the output name string.

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[out] out_name Pointer to the user-maintained buffer for storing
              the output C-style name string.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListGetCodecName(uint64_t index, char *out_name);

/*!
  \brief Obtain the list of mime types supported by a codec.

  The memory used to store the list is maintained by the library.
  User shall call MLMediaCodecListQueryResultsRelease() to
  release it.

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[out] out_supported_mimes List of supported mimes.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListGetSupportedMimes(uint64_t index, MLMediaCodecListQueryResults *out_supported_mimes);

/*!
  \brief Obtain the capability flag for a codec.

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[in] mime Mime type of the codec being queried.
  \param[out] out_capability_flag Codec capability flag defined by #MLMediaCodecListCapabilityFlag.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListGetCapabilityFlag(uint64_t index, const char *mime, MLMediaCodecListCapabilityFlag *out_capability_flag);

/*!
  \brief Obtain the name of a secure codec for the given mime type.

  User shall allocate at least #MAX_CODEC_NAME_LENGTH bytes of memory for
  storing the output name string.

  \param[in] mime Mime type of the codec.
  \param[in] is_decoder \c true if querying for decoder and \c false otherwise.
  \param[out] out_name Pointer to the user-maintained buffer for storing
              the output C-style name string.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListGetSecureCodecName(const char *mime, bool is_decoder, char *out_name);

/*!
  \brief Release the query results.

  \param[in] query_results Query results such as the list of codecs acquired by
             MLMediaCodecListGetMatchingCodecs() or the list of supported mime types
             acquired by MLMediaCodecListGetSupportedMimes().

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListQueryResultsRelease(MLMediaCodecListQueryResults *query_results);

/*!
  \brief Obtain the supported profile levels for a codec.

  User shall call MLMediaCodecListProfileLevelsRelease() to release it.

  \apilevel 6

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[in] mime Mime type of the codec being queried.
  \param[out] out_profile_levels Codec supported profile levels defined by #MLMediaCodecListProfileLevel.
  \param[out] out_profile_levels_size Number of profile levels.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListGetSupportedProfileLevels(uint64_t index, const char *mime,
    MLMediaCodecListProfileLevel **out_profile_levels, size_t *out_profile_levels_size);

/*!
  \brief Release profile levels.

  \apilevel 6

  \param[in] profile_levels The return value of MLMediaCodecListGetSupportedProfileLevels().

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListProfileLevelsRelease(MLMediaCodecListProfileLevel *profile_levels);

/*!
  \brief Obtain the supported color formats for a codec.
   All the supported color formats are defined by MLMediaCodecColorFormat.

  User shall call MLMediaCodecListColorFormatsRelease() to release it.

  \apilevel 6

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[in] mime Mime type of the codec being queried.
  \param[out] out_color_formats Codec supported color formats of type MLMediaCodecColorFormat.
  \param[out] out_color_formats Number of color formats.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListGetSupportedColorFormats(uint64_t index, const char *mime,
    uint32_t **out_color_formats, size_t *out_color_formats_size);

/*!
  \brief Release color formats.

  \apilevel 6

  \param[in] color_formats the return value of MLMediaCodecListGetSupportedColorFormats().

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListColorFormatsRelease(uint32_t *color_formats);

/*!
  \brief Obtain the supported bitrate modes for a codec.

  User shall call MLMediaCodecBitrateModesRelease() to release it.

  \apilevel 9

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[in] mime Mime type of the codec being queried.
  \param[out] out_bitrate_modes Codec supported Bitrate modes defined by #MLMediaCodecBitrateMode.
  \param[out] out_bitrate_modes_size Number of Bitrate modes.

  \retval MLResult_Ok If operation was successful.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListGetSupportedBitrateModes(uint64_t index, const char *mime,
    MLMediaCodecBitrateMode **out_bitrate_modes, size_t *out_bitrate_modes_size);

/*!
  \brief Release Bitrate modes.

  \apilevel 9

  \param[in] bitrate_modes The return value of MLMediaCodecListGetSupportedBitrateModes().

  \retval MLResult_Ok If operation was successful.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecBitrateModesRelease(MLMediaCodecBitrateMode *bitrate_modes);

/*!
  \brief Check whether Adaptive playback is supported.

  This function is used to query a video decoder to see whether it supports seamless resolution changes through Adaptive streaming.
  If the component is an audio decoder or encoder, it will always return false.

  \apilevel 9

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[in] mime Mime type of the codec being queried.
  \param[out] out_supported \c true if supported, \c false otherwise.

  \retval MLResult_Ok If operation was successful.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListIsAdaptivePlaybackSupported(uint64_t index, const char *mime, bool *out_supported);

/*!
  \brief Check whether Secure playback is supported.

  If the component is an encoder, it will always return false.

  \apilevel 9

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[in] mime Mime type of the codec being queried.
  \param[out] out_supported \c true if supported, \c false otherwise.

  \retval MLResult_Ok If operation was successful.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListIsSecurePlaybackSupported(uint64_t index, const char *mime, bool *out_supported);

/*!
  \brief Check whether Intra Refresh is supported.

  If the component is Decoder, it will always return false.

  \apilevel 9

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[in] mime Mime type of the codec being queried.
  \param[out] out_supported \c true if supported, \c false otherwise.

  \retval MLResult_Ok If operation was successful.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaCodecListIsIntraRefreshSupported(uint64_t index, const char *mime, bool *out_supported);

/*! \} */

ML_EXTERN_C_END
