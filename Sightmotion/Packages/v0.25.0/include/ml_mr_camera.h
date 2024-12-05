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
#include "ml_media_error.h"

ML_EXTERN_C_BEGIN

/*!
  \defgroup MRCamera Mixed Reality Camera Capture
  \addtogroup MRCamera
  \sharedobject ml_mr_camera
  \brief APIs for Mixed Reality Camera Capture.

  When using MLMRCamera API, Any subsequent calls to MLCameraConnect() would fail until MLMRCameraDisconnect() is called.
  Stringify the error codes returned by these APIs, call MLMediaResultGetString.

  \{
*/

/*! Mixed Reality Camera output format. */
typedef enum MLMRCameraOutputFormat {
  MLMRCameraOutputFormat_Unknown = 0,
  /*! RGBA format. */
  MLMRCameraOutputFormat_RGBA_8888 = 1,
  /*! Ensure enum is represented as 32 bits. */
  MLMRCameraOutputFormat_Ensure32Bits = 0x7FFFFFFF
} MLMRCameraOutputFormat;

/*! Per plane info for Mixed Reality Camera output. */
typedef struct MLMRCameraPlaneInfo {
  /*! Width of the output image in pixels. */
  uint32_t width;
  /*! Height of the output image in pixels. */
  uint32_t height;
  /*! Stride of the output image in bytes. */
  uint32_t stride;
  /*! Number of bytes used to represent a pixel. */
  uint32_t bytes_per_pixel;
  /*! Image data. */
  uint8_t  *data;
  /*! Number of bytes in the image output data. */
  uint32_t size;
} MLMRCameraPlaneInfo;

enum {
  /*! Number of planes representing the image color space. */
  MLMRCamera_MaxImagePlanes = 3
};

/*! Mixed Reality Camera output. */
typedef struct MLMRCameraOutput {
  /*! Version contains the version number for this structure. */
  uint32_t version;
  /*! Number of output image planes: 1 for RGB8888; */
  uint8_t plane_count;
  /*! Output image plane info. The number of output planes is specified by plane_count. */
  MLMRCameraPlaneInfo planes[MLMRCamera_MaxImagePlanes];
  /*! Supported output format specified by MLMRCameraOutputFormat. */
  MLMRCameraOutputFormat format;
} MLMRCameraOutput;

/*! Video Quality enumeration */
typedef enum MLMRCameraQuality {
  /*! Quality at 720P.*/
  MLMRCameraQuality_720P = 1,
  /*! Quality at 1080P.*/
  MLMRCameraQuality_1080P = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLMRCameraQuality_Ensure32Bits = 0x7FFFFFFF
} MLMRCameraQuality;

/*! Virtual and real content blending modes. */
typedef enum MLMRCameraBlendType {
  /*! Alpha Blend Type. Standard (1 - srcA) blend where virtual pixels are combined over the background real world pixels.*/
  MLMRCameraBlendType_Alpha = 0,
  /*! Additive Blend Type. It simply adds pixel values of real world and virtual layer.*/
  MLMRCameraBlendType_Additive = 1,
  /*!
      Hybrid Blend Type. A mix between Alpha blending and Additive blending using a power curve.
      In this setting, content with alpha values of 1 is treated as semi opaque, with a fixed amount
      of blending against the world camera. Any other alpha values are treated as additive, allowing
      the apps to choose how they want to composite content in the final captured output.
  */
  MLMRCameraBlendType_Hybrid = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLMRCameraBlendType_Ensure32Bits = 0x7FFFFFFF
} MLMRCameraBlendType;

/*! Mixed Reality Camera context to be used during initialization. */
typedef struct MLMRCameraInputContext {
  /*! Version contains the version number for this structure. */
  uint32_t version;
  /*! Quality of the video frame. */
  MLMRCameraQuality quality;
  /*! Blend Type */
  MLMRCameraBlendType blend_type;
  /*! Stabilization. */
  bool stabilization;
} MLMRCameraInputContext;

/*!
  \brief Initialize the MLMRCameraInputContext structure.

  Shall be called before calling MLMRCameraConnect().

  \apilevel 9

  \param[in, out] MLMRCameraInputContext structure to initialize.

  \priv None
*/
ML_STATIC_INLINE void MLMRCameraContextInit(MLMRCameraInputContext *inout_mrcamera_input_context) {
  if (inout_mrcamera_input_context) {
    inout_mrcamera_input_context->version = 1u;
    inout_mrcamera_input_context->quality = MLMRCameraQuality_1080P;
    inout_mrcamera_input_context->blend_type = MLMRCameraBlendType_Additive;
    inout_mrcamera_input_context->stabilization = false;
  }
}

/*!
  \brief Mixed Reality Camera Frame capture info.

  \apilevel 9
*/
typedef struct MLMRCameraFrameCaptureInfo {
  /*! Mixed Reality Camera frame id number. id might not start from 0. */
  uint64_t id;
  /*! Mixed Reality Camera frame time stamp in nanoseconds (ns). */
  uint64_t timestamp_ns;
  /*! Provides image properties and buffer pointer to image data. */
  const MLMRCameraOutput *output;
  /*! User data as passed to MLMRCameraSetCallbacks(). */
  void *data;
} MLMRCameraFrameCaptureInfo;

/*!
  \brief Mixed Reality Camera callbacks to be implemented by client to receive Mixed Reality Camera status

  This structure must be initialized by calling MLMRCameraCallbacksInit() before use.

  \apilevel 9
*/
typedef struct MLMRCameraCallbacks {
  /*! Version contains the version number for this structure. */
  uint32_t version;

  /*!
    \brief Callback is invoked when an individual video frame is captured.

    Application should do minimal processing in this callback. Any extensive processing should be done
    in a separate thread.

    \param[in] info - Mixed Reality Camera Frame capture info as \MLMRCameraFrameCaptureInfo.
  */
  void (*on_frame_captured)(const MLMRCameraFrameCaptureInfo *info);

  /*!
    \brief Callback is invoked when a capture is complete

    \param[in] data - User data as passed to MLMRCameraSetCallbacks().
  */
  void (*on_capture_complete)(void* data);

  /*!
    \brief Callback is invoked when Mixed Reality Camera error happens.
          The app should call MLMRCameraStopCapture() and MLMRCameraDisconnect()

    \param[in] what Error type
    \param[in] data - User data as passed to MLMRCameraSetCallbacks().
  */
  void (*on_error)(MLMediaGenericResult what, void* data);

} MLMRCameraCallbacks;

/*!
  \brief Initialize the MLMRCameraCallbacks structure.

  Shall be called before calling MLMRCameraSetCallbacks().

  \apilevel 9

  \param[in, out] Mixed Reality Camera status callbacks structure to initialize.

  \priv None
*/
ML_STATIC_INLINE void MLMRCameraCallbacksInit(MLMRCameraCallbacks *inout_mrcamera_callbacks) {
  if (inout_mrcamera_callbacks) {
    inout_mrcamera_callbacks->version = 1;
    inout_mrcamera_callbacks->on_frame_captured = NULL;
    inout_mrcamera_callbacks->on_capture_complete = NULL;
    inout_mrcamera_callbacks->on_error = NULL;
  }
}

/*!
  \brief Initialize Mixed Reality Camera.

  \apilevel 9

  \param[in] context Mixed Reality Camera Input context

  \retval MLResult_InvalidParam \c context was invalid.
  \retval MLResult_Ok Mixed Reality Camera intialized succesfully.
  \retval MLMediaGenericResult_AlreadyExists Mixed Reality Camera was already initialized.
  \retval MLMediaGenericResult_NoInit Mixed Reality Camera was not properly initialized.

  \priv CameraCapture
*/
ML_API MLResult MLMRCameraConnect(const MLMRCameraInputContext *context);

/*!
  \brief De-initialize Mixed Reality Camera.

  \apilevel 9

  \retval MLResult_Ok Mixed Reality Camera de-intialized succesfully.

  \priv CameraCapture
*/
ML_API MLResult MLMRCameraDisconnect();

/*!
  \brief Set callbacks to receive Mixed Reality Camera notifications

  \apilevel 9

  \param[in] callbacks Mixed Reality Camera callbacks. passing a null pointer will reset
             previous callback pointers.
  \param[in] data Custom data to be returned when any callback is fired.

  \retval MLResult_Ok Mixed Reality Camera callbacks changed succesfully.

  \priv CameraCapture
*/
ML_API MLResult MLMRCameraSetCallbacks(const MLMRCameraCallbacks *callbacks, void *data);

/*!
  \brief Get capture output size based on quality.

  \apilevel 9

  \param[out] width Width of captured Mixed Reality Camera frame
  \param[out] height Height of captured Mixed Reality Camera frame

  \retval MLResult_InvalidParam \c width or \c height was invalid.
  \retval MLResult_Ok Mixed Reality Camera Current resolution returned successfully.
  \retval MLMediaGenericResult_NoInit Mixed Reality Camera was not properly initialized.

  \priv CameraCapture
*/
ML_API MLResult MLMRCameraGetCaptureSize(uint32_t *width, uint32_t *height);

/*!
  \brief Prepare to capture Mixed Reality Camera frame.

  If the handle is ML_INVALID_HANDLE, the frame buffers will be passed to the application via on_frame_captured callback.

  If the handle is a valid surface handle, then the frame buffers will be directly delivered to the surface. In this case,
  on_frame_captured will only contain frame metdata such as frame id and timestamp.

  Shall be called after MLMRCameraConnect().

  \apilevel 9

  \param[in] handle Handle to Hardware Surface Or ML_INVALID_HANDLE.

  \retval MLResult_Ok Mixed Reality Camera prepared successfully.
  \retval MLMediaGenericResult_NoInit Mixed Reality Camera was not properly initialized.

  \priv CameraCapture
*/
ML_API MLResult MLMRCameraPrepareCapture(MLHandle handle);

/*!
  \brief Start capture of Mixed Reality Camera frames.

  \apilevel 9

  \param[in] frame_count Number of frames to capture. 0 will capture indefinitely.
             Caller needs to call MLMRCameraStopCapture to stop capturing.
  \param[in] wait_for_ae_awb_lock Wait for AE and AWB lock.
             true = wait, false = no wait.

  \retval MLResult_Ok Mixed Reality Camera capture started successfully.
  \retval MLMediaGenericResult_InvalidOperation Mixed Reality Camera was not properly started.

  \priv CameraCapture
*/
ML_API MLResult MLMRCameraStartCapture(uint64_t frame_count, bool wait_for_ae_awb_lock);

/*!
  \brief Stop capturing Mixed Reality Camera frames if still capturing.

  \apilevel 9

  \retval MLResult_Ok Mixed Reality Camera capture started successfully.
  \retval MLMediaGenericResult_InvalidOperation Mixed Reality Camera was not properly stopped.

  \priv CameraCapture
*/
ML_API MLResult MLMRCameraStopCapture();

/*! \} */

ML_EXTERN_C_END
