/**
 * @page c_pa_ecall Modem eCall Platform Adapter API
 *
 * @ref pa_ecall.h "API Reference"
 *
 * <HR>
 *
 * @section pa_ecall_toc Table of Contents
 *
 *  - @ref pa_ecall_intro
 *  - @ref pa_ecall_rational
 *
 *
 * @section pa_ecall_intro Introduction
 * These APIs are on the top of the platform-dependent adapter layer. They are independent of the
 * implementation. They guarantee the portability on different kind of platform without any changes
 * for the components developped upon these APIs.
 *
 *
 * @section pa_ecall_rational Rational
 * These functions are all blocking functions, so that they return when the modem has answered or
 * when a timeout has occured due to an interrupted communication with the modem.
 *
 * They all verify the validity and the range of the input parameters before performing the modem
 * operation.
 *
 * Some functions are used to get some information with a fixed pattern string,
 * in this case no buffer overflow will occur has they always get a fixed string length.
 *
 * <HR>
 *
 * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
 */


/** @file pa_ecall.h
 *
 * Legato @ref c_pa_ecall include file.
 *
 * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
 */

#ifndef LEGATO_PAECALL_INCLUDE_GUARD
#define LEGATO_PAECALL_INCLUDE_GUARD


#include "legato.h"
#include "interfaces.h"


//--------------------------------------------------------------------------------------------------
// Symbol and Enum definitions.
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
/**
 * System standard.
 *
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    PA_ECALL_PAN_EUROPEAN, ///< PAN-European system.
    PA_ECALL_ERA_GLONASS   ///< ERA-GLONASS system.
}
pa_ecall_SysStd_t;

//--------------------------------------------------------------------------------------------------
/**
 * eCall start Type.
 *
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    PA_ECALL_START_MANUAL   = 0, ///< eCall start manual.
    PA_ECALL_START_AUTO     = 1, ///< eCall start automatic.
    PA_ECALL_START_TEST     = 2, ///< eCall start test.
}
pa_ecall_StartType_t;

//--------------------------------------------------------------------------------------------------
// APIs.
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
/**
 * A handler that is called whenever a eCall event is received by the modem.
 *
 */
//--------------------------------------------------------------------------------------------------
typedef void (*pa_ecall_EventHandlerFunc_t)
(
    le_ecall_State_t*  statePtr  ///< eCall state
);

//--------------------------------------------------------------------------------------------------
/**
 * This function initializes the platform adapter layer for eCall services.
 *
 * @return LE_OK if successful.
 * @return LE_FAULT if unsuccessful.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_Init
(
    pa_ecall_SysStd_t sysStd ///< [IN] Choosen system (PA_ECALL_PAN_EUROPEAN or PA_ECALL_ERA_GLONASS)
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to set the eCall operation mode.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_SetOperationMode
(
    le_ecall_OpMode_t mode ///< [IN] Operation mode
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to retrieve the configured eCall operation mode.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_GetOperationMode
(
    le_ecall_OpMode_t* mode ///< [OUT] Operation mode
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to register a handler for eCall event notifications.
 *
 * @return A handler reference, which is only needed for later removal of the handler.
 *
 * @note Doesn't return on failure, so there's no need to check the return value for errors.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_event_HandlerRef_t pa_ecall_AddEventHandler
(
    pa_ecall_EventHandlerFunc_t   handlerFuncPtr ///< [IN] The event handler function.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to unregister the handler for eCalls handling.
 *
 * @note Doesn't return on failure, so there's no need to check the return value for errors.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED void pa_ecall_RemoveEventHandler
(
    le_event_HandlerRef_t handlerRef
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to set the Public Safely Answering Point number.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OVERFLOW  psap number is too long.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_SetPsapNumber
(
    char psap[LE_MDMDEFS_PHONE_NUM_MAX_BYTES] ///< [IN] Public Safely Answering Point number
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to get the Public Safely Answering Point number.
 *
 * @return LE_FAULT     The function failed.
 * @return LE_OVERFLOW  Retrieved PSAP number is too long for the out parameter.
 * @return LE_OK        The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_GetPsapNumber
(
    char*    psapPtr, ///< [OUT] Public Safely Answering Point number
    size_t   len      ///< [IN] The length of SMSC string.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function can be recalled to indicate the modem to read the number to dial from the FDN/SDN
 * of the U/SIM, depending upon the eCall operating mode.
 *
 * @return
 *  - LE_OK on success
 *  - LE_FAULT for other failures
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_UseUSimNumbers
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to set push/pull transmission mode.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_SetMsdTxMode
(
    le_ecall_MsdTxMode_t mode
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to get push/pull transmission mode.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_GetMsdTxMode
(
    le_ecall_MsdTxMode_t* modePtr
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to start the eCall.
 *
 * @return
 *      LE_OK if successful.
 *      LE_FAULT if unsuccessful.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_Start
(
    pa_ecall_StartType_t callType,
    uint32_t *           callIdPtr
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to stop the eCall.
 *
 * @return
 *      LE_OK if successful.
 *      LE_FAULT if unsuccessful.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_Stop
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to end a eCall.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_End
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * Set the 'NAD Deregistration Time' value in minutes.
 *
 * @return
 *  - LE_OK on success
 *  - LE_FAULT on failure
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_SetNadDeregistrationTime
(
    uint16_t    deregTime  ///< [IN] the 'NAD Deregistration Time' value in minutes.
);

//--------------------------------------------------------------------------------------------------
/**
 * Get the 'NAD Deregistration Time' value in minutes.
 *
 * @return
 *  - LE_OK on success
 *  - LE_FAULT on failure
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_GetNadDeregistrationTime
(
    uint16_t*    deregTimePtr  ///< [OUT] the 'NAD Deregistration Time' value in minutes.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to send the Minimum Set of Data for the eCall.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_ecall_SendMsd
(
    uint8_t  *msdPtr,   ///< [IN] Encoded Msd
    size_t    msdSize   ///< [IN] msd buffer size
);

#endif // LEGATO_PAECALL_INCLUDE_GUARD
