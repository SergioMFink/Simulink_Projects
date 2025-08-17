/*
 * ECU_ABS_Model.h
 *
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 *
 * Code generation for model "ECU_ABS_Model".
 *
 * Model version              : 3.5
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C source code generated on : Sun Aug 17 19:41:58 2025
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef ECU_ABS_Model_h_
#define ECU_ABS_Model_h_
#ifndef ECU_ABS_Model_COMMON_INCLUDES_
#define ECU_ABS_Model_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_mode.h"
#include "MW_PWM.h"
#endif                                 /* ECU_ABS_Model_COMMON_INCLUDES_ */

#include "ECU_ABS_Model_types.h"
#include <math.h>
#include <string.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Velocidade_Roda_Diant_Esq;    /* '<S1>/fromWS_Signal 1' */
  real_T Velocidade_Roda_Diant_Dir;    /* '<S1>/From Workspace' */
  real_T Velocidade_Roda_Tras_Esq;     /* '<S1>/From Workspace1' */
  real_T Velocidade_Roda_Tras_Dir;     /* '<S1>/From Workspace2' */
  boolean_T Ativar_ABS;                /* '<Root>/Logical Operator' */
} B_ECU_ABS_Model_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_inter_T obj; /* '<Root>/PWM' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } fromWS_Signal1_PWORK;              /* '<S1>/fromWS_Signal 1' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace_PWORK;               /* '<S1>/From Workspace' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace1_PWORK;              /* '<S1>/From Workspace1' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace2_PWORK;              /* '<S1>/From Workspace2' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    void *LoggedData[4];
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    int_T PrevIndex;
  } fromWS_Signal1_IWORK;              /* '<S1>/fromWS_Signal 1' */

  struct {
    int_T PrevIndex;
  } FromWorkspace_IWORK;               /* '<S1>/From Workspace' */

  struct {
    int_T PrevIndex;
  } FromWorkspace1_IWORK;              /* '<S1>/From Workspace1' */

  struct {
    int_T PrevIndex;
  } FromWorkspace2_IWORK;              /* '<S1>/From Workspace2' */

  boolean_T objisempty;                /* '<Root>/PWM' */
} DW_ECU_ABS_Model_T;

/* Parameters (default storage) */
struct P_ECU_ABS_Model_T_ {
  real_T Constant1_Value;              /* Expression: 77
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T VelocidadeVeculoRef_Value;    /* Expression: 25
                                        * Referenced by: '<Root>/Velocidade Veículo Ref'
                                        */
  real_T Constant_Value;               /* Expression: -0.2
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Constant2_Value;              /* Expression: 230
                                        * Referenced by: '<Root>/Constant2'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_ECU_ABS_Model_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_ECU_ABS_Model_T ECU_ABS_Model_P;

/* Block signals (default storage) */
extern B_ECU_ABS_Model_T ECU_ABS_Model_B;

/* Block states (default storage) */
extern DW_ECU_ABS_Model_T ECU_ABS_Model_DW;

/* Model entry point functions */
extern void ECU_ABS_Model_initialize(void);
extern void ECU_ABS_Model_step(void);
extern void ECU_ABS_Model_terminate(void);

/* Real-time Model object */
extern RT_MODEL_ECU_ABS_Model_T *const ECU_ABS_Model_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ECU_ABS_Model'
 * '<S1>'   : 'ECU_ABS_Model/Sinais das rodas'
 */
#endif                                 /* ECU_ABS_Model_h_ */
