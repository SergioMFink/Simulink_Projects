/*
 * controle_hardware_abs.h
 *
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 *
 * Code generation for model "controle_hardware_abs".
 *
 * Model version              : 1.2
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C source code generated on : Sun Aug 17 17:36:03 2025
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef controle_hardware_abs_h_
#define controle_hardware_abs_h_
#ifndef controle_hardware_abs_COMMON_INCLUDES_
#define controle_hardware_abs_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_AnalogIn.h"
#include "MW_PWM.h"
#endif                              /* controle_hardware_abs_COMMON_INCLUDES_ */

#include "controle_hardware_abs_types.h"
#include <stddef.h>
#include <string.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_inter_T obj; /* '<Root>/Analog Input3' */
  codertarget_arduinobase_inter_T obj_e;/* '<Root>/Analog Input2' */
  codertarget_arduinobase_inter_T obj_l;/* '<Root>/Analog Input1' */
  codertarget_arduinobase_inter_T obj_k;/* '<Root>/Analog Input' */
  codertarget_arduinobase_int_b_T obj_j;/* '<Root>/PWM' */
  boolean_T objisempty;                /* '<Root>/PWM' */
  boolean_T objisempty_b;              /* '<Root>/Analog Input3' */
  boolean_T objisempty_h;              /* '<Root>/Analog Input2' */
  boolean_T objisempty_f;              /* '<Root>/Analog Input1' */
  boolean_T objisempty_n;              /* '<Root>/Analog Input' */
} DW_controle_hardware_abs_T;

/* Parameters (default storage) */
struct P_controle_hardware_abs_T_ {
  real_T Constant2_Value;              /* Expression: 30
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T Constant1_Value;              /* Expression: 90
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T VelocidadeVeculoRef_Value;    /* Expression: 25
                                        * Referenced by: '<Root>/Velocidade Veículo Ref'
                                        */
  real_T Constant_Value;               /* Expression: -0.2
                                        * Referenced by: '<Root>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_controle_hardware_abs_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
extern P_controle_hardware_abs_T controle_hardware_abs_P;

/* Block states (default storage) */
extern DW_controle_hardware_abs_T controle_hardware_abs_DW;

/* Model entry point functions */
extern void controle_hardware_abs_initialize(void);
extern void controle_hardware_abs_step(void);
extern void controle_hardware_abs_terminate(void);

/* Real-time Model object */
extern RT_MODEL_controle_hardware_ab_T *const controle_hardware_abs_M;
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
 * '<Root>' : 'controle_hardware_abs'
 */
#endif                                 /* controle_hardware_abs_h_ */
