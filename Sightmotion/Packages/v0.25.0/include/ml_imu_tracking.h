// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2020 Magic Leap, Inc. (COMPANY) All Rights Reserved.
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

#include <stdbool.h>
#include <stdint.h>
#include "ml_api.h"
#include "ml_types.h"

ML_EXTERN_C_BEGIN

/*!
  \defgroup IMU Tracking
  \addtogroup ImuTracking
  \sharedobject ml_perception_client
  \brief APIs for the IMU(Inertial Measurement Unit) Tracking system.

  \{
*/

/*!
  \brief Represents IMU locations.

  The various locations of the IMU on the lightwear and lightpack.

  \apilevel 9
*/
typedef enum MLImuSampleType {
  /*! Lightpack IMU type. */
  MLImuSampleType_Lightpack=0,
    /*! Left Lightwear IMU type. */
  MLImuSampleType_LightwearLeft=1,
  /*! Ensure enum is represented as 32 bits. */
  MLImuSampleType_Ensure32Bits = 0x7FFFFFFF

} MLImuSampleType;

/*!
  \brief Represents IMU sampling rates.

  The various sampling rates supported by the API.

  \apilevel 9
*/
typedef enum MLImuSamplingRate {
  /*! 100Hz */
  MLImuSamplingRate_100Hz = 100,
  /*! 200Hz */
  MLImuSamplingRate_200Hz = 200,
  /*! 250Hz */
  MLImuSamplingRate_250Hz = 250,
  /*! 500Hz */
  MLImuSamplingRate_500Hz = 500,
  /*! 1000Hz */
  MLImuSamplingRate_1000Hz = 1000,
  /*! Ensure enum is represented as 32 bits. */
  MLImuSamplingRate_Ensure32Bits = 0x7FFFFFFF
} MLImuSamplingRate;

/*!
  \brief Miscellaneous constants.

  \apilevel 9
*/
enum {
  /*!
    \brief IMU internal buffer size, in number of samples.
    The internal buffer is a circular buffer that is implemented most
    efficiently with a size that is a power-of-2. Any buffer passed to
    MLImuTrackingGetSamples() need not have a greater capacity.
  */
  MLImuBufferSize = 1024
};

/*!
  \brief IMU sample.

  The sample is calibration-corrected if calibration data is available.
  The sample is not corrected for gravity.

  \apilevel 9
*/
typedef struct MLImuSample {
  /*! Linear acceleration timestamp, in microseconds. */
  uint64_t linear_acceleration_timestamp_in_microseconds;
  /*! Rotational velocity timestamp, in microseconds. */
  uint64_t rotational_velocity_timestamp_in_microseconds;
  /*! Linear acceleration, in m/s^2. Gravity is included. */
  MLVec3f linear_acceleration_in_meters_per_second_per_second;
  /*! Rotational velocity, in rad/s. */
  MLVec3f rotational_velocity_in_radians_per_second;
  /*! Temperature of the IMU device, in degrees C. */
  float temperature_in_celsius;
  /*! The location of the IMU that generated the sample. */
  MLImuSampleType sample_type;
} MLImuSample;

/*!
  \brief IMU samples retrieval parameters.

  \apilevel 9
*/
typedef struct MLImuQueryFilter {
  /*! Version of this structure. */
  uint32_t version;
  /*! Desired type of the IMU samples. */
  MLImuSampleType sample_type;
  /*! The size of the out_samples buffer, in number of samples of type MLImuSample.
      The number of samples copied will be the lesser of sample_count and MLImuBufferSize.*/
  uint32_t sample_count;
} MLImuQueryFilter;

/*!
  \brief Create an IMU Tracker.

  \apilevel 9

  \param[out] out_handle A pointer to an MLHandle which will contain the handle of the IMU tracker.
              If this operation fails, out_handle will be #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam The out_handle parameter was NULL.
  \retval MLResult_Ok The tracker was created successfully.
  \retval MLResult_PrivilegeDenied The application lacks privilege.
  \retval MLResult_UnspecifiedFailure The tracker failed to create successfully.

  \priv ImuCapture, LowLatencyLightwear
*/
ML_API MLResult ML_CALL MLImuTrackingCreate(MLHandle *out_handle);

/*!
  \brief Destroy an IMU Tracker.

  \apilevel 9

  \param[in] handle A handle to an IMU Tracker created by MLImuTrackingCreate().

  \retval MLResult_InvalidParam The handle parameter was not a valid and active IMU tracking handle.
  \retval MLResult_Ok If the tracker was successfully destroyed.
  \retval MLResult_PrivilegeDenied The application lacks privilege.
  \retval MLResult_UnspecifiedFailure The tracker was not successfully destroyed.

  \priv ImuCapture, LowLatencyLightwear
*/
ML_API MLResult ML_CALL MLImuTrackingDestroy(MLHandle handle);

/*!
  \brief Check for calibration of samples

  Return whether the samples from a specified IMU type are calibration-corrected or not.

  \apilevel 9

  \param[in] handle A handle to an IMU Tracker created by MLImuTrackingCreate().
  \param[in] sample_type Specifies the type of the IMU samples for which calibration-correction is being queried.
  \param[out] out_samples_are_calibration_corrected \true if IMU
              samples supplied by MLImuTrackingGetSamples() will be calibration-corrected.
              The value is platform-specific and will not change for a given platform.

  \retval MLResult_InvalidParam The handle was not a valid and active IMU tracking handle
          and/or the out_samples_are_calibration_corrected parameterwas NULL.
  \retval MLResult_NotImplemented The specified sample_type is not supported by the device.
  \retval MLResult_Ok The function executed succesfully.
  \retval MLResult_PrivilegeDenied The application lacks privilege.
  \retval MLResult_UnspecifiedFailure The function failed for an unspecified reason.

  \priv ImuCapture, LowLatencyLightwear
*/
ML_API MLResult ML_CALL MLImuTrackingAreSamplesCalibrationCorrected(
  MLHandle handle, MLImuSampleType sample_type, bool *out_samples_are_calibration_corrected);

/*!
  \brief Return the next batch of IMU samples from a specified IMU type.

  The samples are not corrected for gravity. The samples are calibration-corrected if the specified
  IMU has been calibrated.

  \apilevel 9

  \param[in] handle A handle to an IMU Tracker created by MLImuTrackingCreate().
  \param[in] query_filter Parameters specifying the type and version of the samples, and the
             size of the out_samples buffer.
  \param[out] out_samples Pointer to buffer to be filled with the next batch of IMU samples.
              The caller owns the buffer and is responsible for allocating and deleting it.
  \param[out] out_sample_count The number of samples written to out_samples.
  \param[out] out_missed_sample_count Pointer to an integer to be filled with the # of missed
              samples, due to a full buffer, since the most recent call. May be NULL.

  \retval MLResult_InvalidParam The handle was not a valid and active IMU
          tracking handle and/or the out_samples or out_samples_count parameter was NULL or
          the version specified in query_filter is invalid.
  \retval MLResult_NotImplemented The specified sample_type is not supported by the device.
  \retval MLResult_Ok The samples were successfully received.
  \retval MLResult_PrivilegeDenied The application lacks privilege.
  \retval MLResult_UnspecifiedFailure Failed to receive the IMU samples.

  \priv ImuCapture, LowLatencyLightwear
*/
ML_API MLResult ML_CALL MLImuTrackingGetSamples(MLHandle handle,
                                                MLImuQueryFilter query_filter,
                                                MLImuSample *out_samples,
                                                uint32_t *out_sample_count,
                                                uint64_t *out_missed_sample_count);

/*!
  \brief Clear the pipeline of current IMU samples for all IMU types.

  \apilevel 9

  \param[in] handle A handle to an IMU Tracker created by MLImuTrackingCreate().

  \retval MLResult_InvalidParam The handle was not a valid and active IMU tracking handle.
  \retval MLResult_Ok The samples were successfully cleared.
  \retval MLResult_PrivilegeDenied The application lacks privilege.
  \retval MLResult_UnspecifiedFailure Failed to clear the IMU samples.

  \priv ImuCapture, LowLatencyLightwear
*/
ML_API MLResult ML_CALL MLImuTrackingClearSamples(MLHandle handle);

/*!
  \brief Enable the collection of Lightpack IMU samples.

  Collect and set the rate of production of samples to a specified value.
  If the Lightpack IMU is not curently enabled, it will be enabled.
  If the Lightpack IMU is currently enabled, it will remain enabled.
  In either case, it will be set to generate IMU samples at the specified rate.

  \apilevel 9

  \param[in] handle A handle to an IMU Tracker created by MLImuTrackingCreate().
  \param[in] sampling_rate An enumerator that specifies the sampling rate rate in Hz.

  \retval MLResult_InvalidParam The handle parameter was NULL or sampling_rate
          was not a valid enumerator.
  \retval MLResult_Ok The Lightpack IMU was successfully enabled and the
          specified samplng rate set.
  \retval MLResult_PrivilegeDenied The application lacks privilege.
  \retval MLResult_UnspecifiedFailure Failed to enable the Lightpack IMU.

  \priv ImuCapture, LowLatencyLightwear
*/
ML_API MLResult ML_CALL MLImuTrackingLightpackEnable(MLHandle handle,
                                                    MLImuSamplingRate sampling_rate);

/*!
  \brief Disable the collection of Lightpack IMU samples.

  \apilevel 9

  \param[in] handle A handle to an IMU Tracker created by MLImuTrackingCreate().

  \retval MLResult_InvalidParam The handle parameter was NULL.
  \retval MLResult_Ok Sample collection from the Lightpack IMU was successfully disabled.
  \retval MLResult_PrivilegeDenied The application lacks privilege.
  \retval MLResult_UnspecifiedFailure Failed to disable the Lightpack IMU.

  \priv ImuCapture, LowLatencyLightwear
*/
ML_API MLResult ML_CALL MLImuTrackingLightpackDisable(MLHandle handle);

/*! \} */

ML_EXTERN_C_END