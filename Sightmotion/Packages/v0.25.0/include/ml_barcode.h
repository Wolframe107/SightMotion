// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2020 Magic Leap, Inc. (COMPANY) All Rights Reserved.
// Magic Leap, Inc. Confidential and Proprietary
//
// NOTICE:  All information contained herein is, and remains the property
// of COMPANY. The intellectual and technical concepts contained herein
// are proprietary to COMPANY and may be covered by U.S. and Foreign
// Patents, patents in process, and are protected by trade secret or
// copyright law.  Dissemination of this information or reproduction of
// this material is strictly forbidden unless prior written permission is
// obtained from COMPANY.  Access to the source code contained herein is
// hereby forbidden to anyone except current COMPANY employees, managers
// or contractors who have executed Confidentiality and Non-disclosure
// agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended
// publication or disclosure  of  this source code, which includes
// information that is confidential and/or proprietary, and is a trade
// secret, of  COMPANY.   ANY REPRODUCTION, MODIFICATION, DISTRIBUTION,
// PUBLIC  PERFORMANCE, OR PUBLIC DISPLAY OF OR THROUGH USE  OF THIS
// SOURCE CODE  WITHOUT THE EXPRESS WRITTEN CONSENT OF COMPANY IS
// STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND
// INTERNATIONAL TREATIES.  THE RECEIPT OR POSSESSION OF  THIS SOURCE
// CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE,
// USE, OR SELL ANYTHING THAT IT  MAY DESCRIBE, IN WHOLE OR IN PART.
//
// %COPYRIGHT_END%
// --------------------------------------------------------------------*/
// %BANNER_END%

#pragma once

#include "ml_api.h"
#include "ml_coordinate_frame_uid.h"


ML_EXTERN_C_BEGIN

/*!
  \defgroup MarkerTracking Fiducial Marker Tracking.
  \addtogroup MarkerTracking
  \sharedobject ml_perception_client
  \brief APIs for the Barcode scanning system.

  This API can be used to scan barcodes. For QR codes it also provides 6DOF poses.
  The scanner supports up to 16 barcodes.
  Identical barcodes will be treated as seperate barcodes and reported individually.

  List of supported barcodes:
  - QR codes of Model 1
  - QR codes of Model 2

  \{
*/

/*!
  \brief Represents the different barcode types supported by the API.

  \apilevel 9
*/
typedef enum MLBarcodeType {
  /*! Represents no barcode. */
  MLBarcodeType_None = 0,
  /*! QR code of Model 1 or 2 */
  MLBarcodeType_QR = 1 << 0,
  /*! All supported barcodes. */
  MLBarcodeType_All = 0x3FFFFFFF,
  MLBarcodeType_Ensure32Bits = 0x7FFFFFFF
}
MLBarcodeType;

/*!
  \brief Represents the decoded data encoded in the barcode.

  Barcodes can encode binary data, strings, URLs and more. This struct represents the
  decoded data read from a barcode.

  \apilevel 9
*/
typedef struct MLBarcodeScannerDecodedData {
  /*!
    \brief Data array decoded from a detected barcode.
  */
  const char* data;

  /*!
    \brief Length of the decoded data.
  */
  uint32_t size;
} MLBarcodeScannerDecodedData;

/*!
  \brief Represents the tracking result for a single barcode.

  A list of these results will be returned by the Barcode Scanner, after processing a video
  frame succesfully.

  \apilevel 9
*/
typedef struct MLBarcodeScannerResult {
  /*!
    \brief The data which was encoded in the barcode.
  */
  MLBarcodeScannerDecodedData decoded_data;

  /*!
    \brief The type of barcode that was detected.
  */
  MLBarcodeType type;

  /*!
    \brief MLCoordinateFrameUID of the QR code.

    This FrameUID is only useful if the barcode is of type #MLBarcodeTypeQR
    This should be passed to the MLSnapshotGetTransform() function to get
    the 6 DOF pose of the QR code.
    Any barcode that isn't a QR code will have an invalid FrameUID here.
  */
  MLCoordinateFrameUID coord_frame_qr_code;

  /*!
    \brief The reprojection error of this QR code detection in degrees.

    The reprojection error is only useful when tracking QR codes.
    A high reprojection error means that the estimated pose of the QR code doesn't match well with
    the 2D detection on the processed video frame and thus the pose might be inaccurate. The error
    is given in degrees, signifying by how much either camera or QR code would have to be moved or
    rotated to create a perfect reprojection. The further away your QR code is, the smaller this
    reprojection error will be for the same displacement error of the code.
  */
  float reprojection_err;
} MLBarcodeScannerResult;

/*!
  \brief An array of all the detection results from the barcode scanning.

  \apilevel 9
*/
typedef struct MLBarcodeScannerResultArray {
  /*! Version of this structure. */
  uint32_t version;

  /*! Pointer to an array of pointers for MLBarcodeResult. */
  MLBarcodeScannerResult** detections;

  /*! Number of barcodes being tracked. */
  uint32_t count;
} MLBarcodeScannerResultArray;

/*!
  \brief Initializes default values for MLBarcodeScannerResultArray.

  \apilevel 9

  \param[in, out] inout_resultarray The object to initialize as default result array.

  \retval MLResult_InvalidParam Failed to init result array due to pointer being NULL.
  \retval MLResult_Ok Successfully initialized Barcode result array.
*/
ML_STATIC_INLINE MLResult MLBarcodeScannerResultArrayInit(MLBarcodeScannerResultArray *inout_resultarray) {
  if (!inout_resultarray) {
    return MLResult_InvalidParam;
  }
  inout_resultarray->version = 1u;
  inout_resultarray->detections = NULL;
  inout_resultarray->count = 0;
  return MLResult_Ok;
}

/*!
  \brief Barcode Scanner Settings

  When creating the Barcode Scanner, this list of settings needs to be passed to configure the scanner
  properly. The estimated poses will only be correct if the barcode length has been set correctly.

  \apilevel 9
*/
typedef struct MLBarcodeScannerSettings {
  /*! Version of this structure. */
  uint32_t version;

  /*!
    \brief The physical size of the QR code that shall be tracked.

    The physical size is important to know, because once a QR code is detected we can only determine
    its 3D position when we know its correct size.
    The size of the QR code is given in meters and represents the length of one side of the square
    code (without the outer margin).
    Min size: As a rule of thumb the size of a QR code should be at least a 10th of the distance you
    intend to scan it with a camera device. Higher version barcodes with higher information density
    might need to be larger than that to be detected reliably.
    Max size: Our camera needs to see the whole barcode at once. If it's too large, we won't detect it.
  */
  float qr_code_size;

  /*!
    \brief If \c true, Barcode Scanner will detect barcodes and track QR codes.

    Barcode Scanner should be disabled when app is paused and enabled when app resumes.
    When enabled, Barcode Scanner will gain access to the camera and start scanning barcodes.
    When disabled Barcode Scanner will release the camera and stop scanning barcodes.
    Internal state of the scanner will be maintained.
  */
  bool enable_barcode_scanning;

  /*!
    \brief The barcode types that are enabled for this scanner.

    Enable barcodes by combining any number of #MLBarcodeType flags using '|' (bitwise 'or').

  */
  uint32_t enabled_barcode_types;
} MLBarcodeScannerSettings;

/*!
  \brief Initializes default values for MLBarcodeScannerSettings.

  \apilevel 9

  \param[in, out] inout_settings The object to initialize with default settings.

  \retval MLResult_InvalidParam Failed to init settings due to pointer being NULL.
  \retval MLResult_Ok Successfully initialized Barcode Scanner settings.
*/
ML_STATIC_INLINE MLResult MLBarcodeScannerSettingsInit(MLBarcodeScannerSettings *inout_settings) {
  if (!inout_settings) {
    return MLResult_InvalidParam;
  }
  inout_settings->version = 1u;
  inout_settings->qr_code_size = 0.1f;
  inout_settings->enable_barcode_scanning = true;
  inout_settings->enabled_barcode_types = MLBarcodeType_None;
  return MLResult_Ok;
}

/*!
  \brief Create an Barcode Scanner.

  \apilevel 9

  \param[in]  settings List of settings of type MLBarcodeScannerSettings that configure the scanner.
  \param[out] out_handle A pointer to an MLHandle to the newly created Barcode Scanner.
              If this operation fails, out_handle will be ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam Failed to create Barcode Scanner due to invalid out_handle.
  \retval MLResult_Ok Successfully created Barcode Scanner.
  \retval MLResult_PrivilegeDenied Failed to create scanner due to lack of privilege(s).
  \retval MLResult_UnspecifiedFailure Failed to create the Barcode Scanner due to an internal error.

  \priv CameraCapture, LowLatencyLightwear
*/
ML_API MLResult ML_CALL MLBarcodeScannerCreate(const MLBarcodeScannerSettings *settings, MLHandle *out_handle);

/*!
  \brief Update the Barcode Scanner with new settings.

  \apilevel 9

  \param[in] scanner_handle MLHandle to the Barcode Scanner created by MLArucoScannerCreate().
  \param[in] scanner_settings List of new Barcode Scanner settings.

  \retval MLResult_InvalidParam Failed to update the settings due to invalid scanner_settings.
  \retval MLResult_Ok Successfully updated the Barcode Scanner settings.
  \retval MLResult_PrivilegeDenied Failed to update the settings due to lack of privilege(s).
  \retval MLResult_UnspecifiedFailure Failed to update the settings due to an internal error.

  \priv CameraCapture, LowLatencyLightwear
*/
ML_API MLResult ML_CALL MLBarcodeScannerUpdateSettings(MLHandle scanner_handle,
                                                     const MLBarcodeScannerSettings *scanner_settings);

/*!
  \brief Destroy a Barcode Scanner.

  \apilevel 9

  \param[in] scanner_handle MLHandle to the Barcode Scanner created by MLBarcodeScannerCreate().

  \retval MLResult_Ok Successfully destroyed the Barcode Scanner.
  \retval MLResult_UnspecifiedFailure Failed to destroy the scanner due to an internal error.

  \priv CameraCapture, LowLatencyLightwear
*/
ML_API MLResult ML_CALL MLBarcodeScannerDestroy(MLHandle scanner_handle);

/*!
  \brief Get the results for Barcode Scanning.

  This function can be used to poll results from the scanner. Before calling
  this API, initialize MLBarcodeScannerResultArray by calling
  MLBarcodeScannerResultArrayInit. The memory allocated by this API should be
  freed using MLBarcodeScannerReleaseResult before making another call to this
  API.

  \apilevel 9

  \param[in]    scanner_handle #MLHandle to the Barcode Scanner created by MLBarcodeScannerCreate().
  \param[inout] inout_data Pointer to an array of pointers to MLBarcodeScannerResult.
                The content will have to be freed by calling MLBarcodeScannerReleaseResult.

  \retval MLResult_InvalidParam Failed to return detection data due to invalid inout_data.
  \retval MLResult_Ok Successfully fetched and returned all detections.
  \retval MLResult_UnspecifiedFailure Failed to return detections due to an internal error.

  \priv None
*/
ML_API MLResult ML_CALL MLBarcodeScannerGetResult(MLHandle scanner_handle,
                                                  MLBarcodeScannerResultArray *inout_data);

/*!
  \brief Release the resources for the results array.

  \apilevel 9

  \param[in] data The list of detections to be freed.

  \retval MLResult_InvalidParam Failed to free structure due to invalid data.
  \retval MLResult_Ok Successfully freed data structure.
  \retval MLResult_UnspecifiedFailure Failed to free data due to an internal error.

  \priv None
*/
ML_API MLResult ML_CALL MLBarcodeScannerReleaseResult(MLBarcodeScannerResultArray *data);

/*! \} */

ML_EXTERN_C_END

