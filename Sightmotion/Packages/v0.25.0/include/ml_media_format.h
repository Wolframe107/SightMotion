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
  \sharedobject ml_mediaformat
  \brief APIs for creaitng and retrieving media format information.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

#define MAX_FORMAT_STRING_SIZE 512
#define MAX_KEY_STRING_SIZE    64

/*! Media format type. */
typedef enum MLMediaFormatType {
  /*! Video. */
  MLMediaFormatType_Video,
  /*! Audio. */
  MLMediaFormatType_Audio,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaFormatType_Ensure32Bits = 0x7FFFFFFF
} MLMediaFormatType;

/*! Data type containing byte array buffer and the size. */
typedef struct MLMediaFormatByteArray {
  uint8_t *ptr;
  size_t length;
} MLMediaFormatByteArray;

typedef enum MLMediaFormatAudioEncoding {
  /*! Audio data format: PCM 16 bits per sample. */
  MLMediaFormatAudioEncoding_PCM16Bits = 2,
  /*! Audio data format: PCM 8 bits per sample. */
  MLMediaFormatAudioEncoding_PCM8Bits  = 3,
  /*! Audio data format: single-precision floating-point per sample. */
  MLMediaFormatAudioEncoding_PCMFloat = 4,
  /*! Audio data format: PCM 32 bits per sample. */
  MLMediaFormatAudioEncoding_PCM32Bits = 201,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaFormatAudioEncoding_Ensure32Bits = 0x7FFFFFFF
} MLMediaFormatAudioEncoding;

typedef const char *MLMediaFormatKey;

/*!
  \brief The format of media data (video/audio) is specified as key/value pairs.
  Below is a list of keys used to set/obtain format values.
*/
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_Encoded_Target_Level;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Boost_Factor;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Attenuation_Factor;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Heavy_Compression;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Target_Reference_Level;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_Max_Output_Channel_Count;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_Profile;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_SBR_Mode;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Bit_Rate;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Capture_Rate;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Channel_Count;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Channel_Mask;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Color_Format;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Duration;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_FLAC_Compression_Level;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Frame_Rate;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Height;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_I_Frame_Interval;
/*!
  \brief An optional key describing the period of intra refresh in frames. The associated value is an integer.

  This is an optional parameter that applies only to video encoders.
  If encoder supports it (\ref MLMediaCodecListIsIntraRefreshSupported), the whole frame is completely refreshed after the specified period.
  Also for each frame, a fix subset of macroblocks must be intra coded which leads to more constant bitrate than inserting a key frame.
  This key is recommended for video streaming applications as it provides low-delay and good error-resilience.
  This key is ignored if the video encoder does not support the intra refresh feature.
  Use the output format to verify that this feature was enabled.
*/
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_Period;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Is_ADTS;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Is_Autoselect;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Is_Default;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Is_Forced_Subtitle;
/*! Value type for this key is string. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Language;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_Height;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_Input_Size;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_Width;
/*! Value type for this key is string. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Mime;
/*! Value type for this key is integer with values defined by MLMediaFormatAudioEncoding. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_PCM_Encoding;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Push_Blank_Buffers_On_Stop;
/*! Value type for this key is long. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Repeat_Previous_Frame_After;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Sample_Rate;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Stride;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Temporal_Layering;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Width;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crop_Left;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crop_Right;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crop_Bottom;
/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crop_Top;
/*!
  \brief A key describing the desired bitrate mode to be used by an encoder.

   Value type for this key is integer and it can be one of the \ref MLMediaCodecBitrateMode enumaration.
*/
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Bit_Rate_Mode;

/*!
  \brief A key describing the desired codec priority.

  The associated value can be one of the \ref MLMediaCodecPriority enumaration.
  This is a hint used at codec configuration and resource planning - to understand the realtime requirements of the application;
  however, due to the nature of media components, performance is not guaranteed.
*/
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Priority;

/*!
  \brief A key describing the maximum number of B frames between I or P frames, to be used by a video encoder.

  The associated value is an integer. The default value is 0, which means that no B frames are allowed.
  Note that non-zero value does not guarantee B frames; it's up to the encoder to decide.
*/
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_B_Frames;

/*!
  \brief An optional key describing the mode of intra refresh in frames. The associated value is an integer.

  This is an optional parameter that applies only to video encoders.
  If encoder supports it (\ref MLMediaCodecListIsIntraRefreshSupported), the whole frame is completely refreshed after the specified period.
  Also for each frame, a fix subset of macroblocks must be intra coded which leads to more constant bitrate than inserting a key frame.
  This key is recommended for video streaming applications as it provides low-delay and good error-resilience.
  This key is ignored if the video encoder does not support the intra refresh feature.
  Use the output format to verify that this feature was enabled.
  The possible values are defined in \ref MLMediaCodecIntraRefreshMode.
*/
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_Mode;

/*! Number of consecutive macroblocks to be coded as intra when CIR is enabled. The associated value is an integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_CIR_Num;

/*! Number of intra macroblocks to refresh in a frame when AIR is enabled. The associated value is an integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_AIR_Num;

/*! Number of times a motion marked macroblock has to be intra coded. The associated value is an integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_AIR_Ref;

/*!
  \brief A key describing the desired profile to be used by an encoder. The associated value is an integer.

  The supported profiles can be queries through \ref MLMediaCodecListGetSupportedProfileLevels.
  The values are defined in \ref MLMediaCodecProfileType enumaration.
  This key is used as a further hint when specifying a desired profile, and is only supported for codecs that specify a level.
  This key is ignored if the profile is not specified.
*/
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Profile;

/*!
  \brief A key describing the desired level to be used by an encoder. The associated value is an integer.

  The supported profiles can be queries through \ref MLMediaCodecListGetSupportedProfileLevels.
  The values are defined in \ref MLMediaCodecLevelType enumaration.
  This key is used as a further hint when specifying a desired profile, and is only supported for codecs that specify a level.
  This key is ignored if the level is not specified.
*/
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Level;

/*!
  \brief An optional key describing whether encoders prepend headers to sync frames (e.g. SPS and PPS to IDR frames for H.264).

  This is an optional parameter that applies only to video encoders.
  A video encoder may not support this feature; the component will fail to configure in that case.
  For other components, this key is ignored.
  The value is an integer, with 1 indicating to prepend headers to every sync frames, or 0 otherwise.
  The default value is 0.
*/
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Prepend_Header_To_Sync_Frames;

/*! Value type for this key is integer. */
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Parameter_Video_Bitrate;

/*!
  \brief Create a video format object.

  \param[in] mime_type Mime type of the content.
  \param[in] width Width of the content in pixels.
  \param[in] height Height of the content in pixels.
  \param[out] out_handle A handle to the created video format object.
              If there is an error during creation, it will
              return #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed If handle cannot be allocated.
  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatCreateVideo(const char *mime_type, int width, int height, MLHandle *out_handle);

/*!
  \brief Create a audio format object.

  \param[in] mime_type Mime type of the content.
  \param[in] sample_rate Sample rate of the content.
  \param[in] channel_count Number of audio channels.
  \param[out] out_handle A handle to the created audio format object.
              If there is an error during creation, it will
              return #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed If handle cannot be allocated.
  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatCreateAudio(const char *mime_type, int sample_rate, int channel_count, MLHandle *out_handle);

/*!
  \brief Create a subtitle format object.

  \param[in] mime_type Mime type of the content.
  \param[in] language Language of the content, using either ISO 639-1 or
             639-2/T codes. Specify null or "und" if language information
             is only included in the content. (This will also work if there
             are multiple language tracks in the content.)
  \param[out] out_handle A handle to the created subtitle format object.
              If there is an error during creation, it will
              return #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed If handle cannot be allocated.
  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatCreateSubtitle(const char *mime_type, const char *language, MLHandle *out_handle);

/*!
  \brief Create an empty format object.

  \apilevel 9

  \param[out] out_handle A handle to the created empty format object.
              If there is an error during creation, it will
              return #ML_INVALID_HANDLE.

  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_AllocFailed If handle cannot be allocated.
  \retval MLResult_InvalidParam If one of parameters is invalid.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatCreate(MLHandle *out_handle);

/*!
  \brief Destroy a \ref MLMediaFormat object.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.

  \retval MLResult_InvalidParam If handle is invalid.
  \retval MLResult_Ok If \ref MLMediaCodec object was successfully destroyed.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
 */
ML_API MLResult ML_CALL MLMediaFormatDestroy(MLHandle handle);

/*!
  \brief Obtain the human readable representation of the format.

  User shall allocate at least #MAX_FORMAT_STRING_SIZE bytes of memory for
  storing the output format string. The format string contains
  a list of key-value pairs, which can be extracted individually
  via the suitable "GetKeyValue" APIs.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[out] out_string Pointer to the user-maintained buffer for storing.
              the output C-style format string.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatObjectToString(MLHandle handle, char *out_string);

/*!
  \brief Obtain the value of an integer key.

  For example, use #MLMediaFormat_Key_Frame_Rate key to get
  the framerate of a video track.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_key Value of the key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatGetKeyValueInt32(MLHandle handle, MLMediaFormatKey name, int32_t *out_key);

/*!
  \brief Obtain the value of an long key.
  For example, use MLMediaFormat_Key_Duration key to get
  duration of a track.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_key Value of the key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatGetKeyValueInt64(MLHandle handle, MLMediaFormatKey name, int64_t *out_key);

/*!
  \brief Obtain the value of an float key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_key Value of the key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatGetKeyValueFloat(MLHandle handle, MLMediaFormatKey name, float *out_key);

/*!
  \brief Obtain the size of a key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_size Size of the key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatGetKeySize(MLHandle handle, MLMediaFormatKey name, size_t *out_size);

/*!
  \brief Obtain the value of a string key.

  User shall allocate at least #MAX_KEY_STRING_SIZE bytes of memory for
  storing the output key string.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_string Pointer to the C-string representation of the string key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatGetKeyString(MLHandle handle, MLMediaFormatKey name, char *out_string);

/*!
  \brief Obtain the value of a ByteBuffer key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_buffer Pointer to byte buffer that needs to be allocated and copied to.
              To free/release, call MLMediaFormatKeyByteBufferRelease().

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatGetKeyByteBuffer(MLHandle handle, MLMediaFormatKey name, MLMediaFormatByteArray *out_buffer);

/*!
  \brief Release the ByteBuffer acquired by MLMediaFormatGetKeyByteBuffer.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] buffer Byte buffer that needs to be released.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatKeyByteBufferRelease(MLHandle handle, MLMediaFormatByteArray *buffer);

/*!
  \brief Set the value of an integer key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value Key value.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatSetKeyInt32(MLHandle handle, MLMediaFormatKey name, int32_t key_value);

/*!
  \brief Set the value of a long key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value Key value.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatSetKeyInt64(MLHandle handle, MLMediaFormatKey name, int64_t key_value);

/*!
  \brief Set the value of a float key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value Key value.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatSetKeyFloat(MLHandle handle, MLMediaFormatKey name, float key_value);

/*!
  \brief Set the size of a key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_size Key size.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatSetKeySize(MLHandle handle, MLMediaFormatKey name, size_t key_size);

/*!
  \brief Set the value of a string key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value C-string representation of key value.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
 */
ML_API MLResult ML_CALL MLMediaFormatSetKeyString(MLHandle handle, MLMediaFormatKey name, const char *key_value);

/*!
  \brief Set the value of a ByteBuffer key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] buffer Pointer to the data buffer for the corresponding key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \priv None
*/
ML_API MLResult ML_CALL MLMediaFormatSetKeyByteBuffer(MLHandle handle, MLMediaFormatKey name, MLMediaFormatByteArray *buffer);

/*! \} */

ML_EXTERN_C_END
