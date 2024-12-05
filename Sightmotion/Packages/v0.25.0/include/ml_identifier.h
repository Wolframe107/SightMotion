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

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Device Identifier
  \sharedobject ml_settings
  \brief APIs for accessing Unique Identifiers within the OS.
  \{
*/

/*!
  \brief Represents the max sizes of the C string for the different identifiers.

  \apilevel 9
*/
typedef enum MLIdentifierMaxSize {
  /*! Enum to get App Instance ID max size. */
  MLIdentifierMaxSize_AppInstanceID = 255,
  /*! Ensure enum is represented as 32 bits. */
  MLIdentifierMaxSize_Ensure32Bits = 0x7FFFFFFF
}
MLIdentifierMaxSize;

/*!
  \brief Represents the different Identifiers supported by the API

  \apilevel 9
*/
typedef enum MLIdentifierType {
  /*! Represents no Identifier */
  MLIdentifierType_None = 0,
  /*! enum to get App Instance ID */
  MLIdentifierType_AppInstanceID = 1 << 0,
  /*! Ensure enum is represented as 32 bits. */
  MLIdentifierType_Ensure32Bits = 0x7FFFFFFF
}
MLIdentifierType;

/*!
  \brief Represents the result of an Identifier query

  To get this the API MLIdentifierGetResult needs to be polled

  \apilevel 9
*/
typedef struct MLIdentifierData {
  /*!
    \brief enum representing the type of Identifier
  */
  MLIdentifierType type;
  /*!
    \brief The C string carrying identifier data which is UTF-8 and null terminated.
  */
  char id_string[MLIdentifierMaxSize_AppInstanceID+1];
} MLIdentifierData;

/*!
  \brief Identifier Params

  When requesting the Identifier, this input structure needs to be provided as parameter
  with the type of Identifier requested.
  This structure must be initialized by calling MLIdentifierParamsInit() before use.

  \apilevel 9
*/
typedef struct MLIdentifierParams {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief Type of the Identifier requested.
  */
  MLIdentifierType id_type_req;

} MLIdentifierParams;

/*!
  \brief Initializes default values for MLIdentifierParams.

  \apilevel 9

  \param[in] in_params The object to initialize with default params.

  \retval MLResult_InvalidParam Failed to init settings due to pointer being NULL.
  \retval MLResult_Ok Successfully initialized Identifier allocator params.
*/
ML_STATIC_INLINE MLResult MLIdentifierParamsInit(MLIdentifierParams *inout_params) {
  if (!inout_params) {
    return MLResult_InvalidParam;
  }
  inout_params->version = 1u;
  inout_params->id_type_req = MLIdentifierType_None;
  return MLResult_Ok;
}

/*!
  \brief Create an Identifier instance.

  \apilevel 9

  \param[out] id_handle A pointer to an MLHandle to the newly created Identifier instance.
              If this operation fails, id_handle will be ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam Failed to create Identifier due to invalid out_handle.
  \retval MLResult_Ok Successfully created Identifier instance.
  \retval MLResult_UnspecifiedFailure Failed to create the Identifier due to an internal error.

  \priv none
*/
ML_API MLResult ML_CALL MLIdentifierCreate(MLHandle *id_handle);

/*!
  \brief Destroy an Identifier.

  \apilevel 9

  \param[in] id_handle MLHandle to the Identifier created by MLIdentifierCreate().

  \retval MLResult_Ok Successfully destroyed the Identifier.
  \retval MLResult_UnspecifiedFailure Failed to destroy the Identifier due to an internal error.

  \priv none
*/
ML_API MLResult ML_CALL MLIdentifierDestroy(MLHandle id_handle);

/*!
  \brief Get the results of Identifier requested.

  This function can be used to poll results from the Identifier instance.

  \apilevel 9

  \param[in] id_handle #MLHandle to the Identifier created by MLIdentifierCreate().
  \param[in] in_params The input parameters to the function as needed.
  \param[out] out_data Pointer to MLIdentifierData.
              The content will have to be allocated and released by the user.

  \retval MLResult_InvalidParam Failed to return data due to invalid out_data.
  \retval MLResult_Ok Successfully fetched and returned all data.
  \retval MLResult_UnspecifiedFailure Failed to return data due to an internal error.

  \priv None
*/
ML_API MLResult ML_CALL MLIdentifierGetResult(MLHandle id_handle, MLIdentifierParams *in_params,
                                                  MLIdentifierData *out_data);

/*! \} */

ML_EXTERN_C_END
