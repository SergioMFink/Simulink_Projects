/*
 * controle_hardware_abs.c
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

#include "controle_hardware_abs.h"
#include "rtwtypes.h"
#include <string.h>

/* Block states (default storage) */
DW_controle_hardware_abs_T controle_hardware_abs_DW;

/* Real-time model */
static RT_MODEL_controle_hardware_ab_T controle_hardware_abs_M_;
RT_MODEL_controle_hardware_ab_T *const controle_hardware_abs_M =
  &controle_hardware_abs_M_;

/* Model step function */
void controle_hardware_abs_step(void)
{
  real_T u0;
  uint16_T b_varargout_1;
  uint16_T b_varargout_1_0;
  uint16_T b_varargout_1_1;
  uint16_T b_varargout_1_2;

  /* MATLABSystem: '<Root>/Analog Input' */
  controle_hardware_abs_DW.obj_k.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogIn_GetHandle(14UL);
  MW_AnalogInSingle_ReadResult
    (controle_hardware_abs_DW.obj_k.AnalogInDriverObj.MW_ANALOGIN_HANDLE,
     &b_varargout_1, MW_ANALOGIN_UINT16);

  /* MATLABSystem: '<Root>/Analog Input1' */
  controle_hardware_abs_DW.obj_l.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogIn_GetHandle(15UL);
  MW_AnalogInSingle_ReadResult
    (controle_hardware_abs_DW.obj_l.AnalogInDriverObj.MW_ANALOGIN_HANDLE,
     &b_varargout_1_0, MW_ANALOGIN_UINT16);

  /* MATLABSystem: '<Root>/Analog Input2' */
  controle_hardware_abs_DW.obj_e.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogIn_GetHandle(16UL);
  MW_AnalogInSingle_ReadResult
    (controle_hardware_abs_DW.obj_e.AnalogInDriverObj.MW_ANALOGIN_HANDLE,
     &b_varargout_1_1, MW_ANALOGIN_UINT16);

  /* MATLABSystem: '<Root>/Analog Input3' */
  controle_hardware_abs_DW.obj.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogIn_GetHandle(17UL);
  MW_AnalogInSingle_ReadResult
    (controle_hardware_abs_DW.obj.AnalogInDriverObj.MW_ANALOGIN_HANDLE,
     &b_varargout_1_2, MW_ANALOGIN_UINT16);

  /* MATLABSystem: '<Root>/PWM' */
  controle_hardware_abs_DW.obj_j.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
    (5UL);

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Velocidade Veículo Ref'
   *  Logic: '<Root>/Logical Operator'
   *  MATLABSystem: '<Root>/Analog Input'
   *  MATLABSystem: '<Root>/Analog Input1'
   *  MATLABSystem: '<Root>/Analog Input2'
   *  MATLABSystem: '<Root>/Analog Input3'
   *  Product: '<Root>/Slip Roda Diant. Dir'
   *  Product: '<Root>/Slip Roda Diant. Esq'
   *  Product: '<Root>/Slip Roda Tras. Dir'
   *  Product: '<Root>/Slip Roda Tras. Esq'
   *  RelationalOperator: '<Root>/Relational Operator'
   *  RelationalOperator: '<Root>/Relational Operator1'
   *  RelationalOperator: '<Root>/Relational Operator2'
   *  RelationalOperator: '<Root>/Relational Operator3'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<Root>/Sum2'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<Root>/Sum4'
   * */
  if ((((real_T)b_varargout_1 -
        controle_hardware_abs_P.VelocidadeVeculoRef_Value) /
       controle_hardware_abs_P.VelocidadeVeculoRef_Value <
       controle_hardware_abs_P.Constant_Value) || (((real_T)b_varargout_1_0 -
        controle_hardware_abs_P.VelocidadeVeculoRef_Value) /
       controle_hardware_abs_P.VelocidadeVeculoRef_Value <
       controle_hardware_abs_P.Constant_Value) || (((real_T)b_varargout_1_1 -
        controle_hardware_abs_P.VelocidadeVeculoRef_Value) /
       controle_hardware_abs_P.VelocidadeVeculoRef_Value <
       controle_hardware_abs_P.Constant_Value) || (((real_T)b_varargout_1_2 -
        controle_hardware_abs_P.VelocidadeVeculoRef_Value) /
       controle_hardware_abs_P.VelocidadeVeculoRef_Value <
       controle_hardware_abs_P.Constant_Value)) {
    u0 = controle_hardware_abs_P.Constant2_Value;
  } else {
    u0 = controle_hardware_abs_P.Constant1_Value;
  }

  /* Start for MATLABSystem: '<Root>/PWM' incorporates:
   *  Switch: '<Root>/Switch'
   */
  if (!(u0 <= 255.0)) {
    u0 = 255.0;
  }

  if (!(u0 >= 0.0)) {
    u0 = 0.0;
  }

  /* MATLABSystem: '<Root>/PWM' */
  MW_PWM_SetDutyCycle(controle_hardware_abs_DW.obj_j.PWMDriverObj.MW_PWM_HANDLE,
                      u0);
}

/* Model initialize function */
void controle_hardware_abs_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(controle_hardware_abs_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&controle_hardware_abs_DW, 0,
                sizeof(DW_controle_hardware_abs_T));

  /* Start for MATLABSystem: '<Root>/Analog Input' */
  controle_hardware_abs_DW.obj_k.matlabCodegenIsDeleted = false;
  controle_hardware_abs_DW.objisempty_n = true;
  controle_hardware_abs_DW.obj_k.isInitialized = 1L;
  controle_hardware_abs_DW.obj_k.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogInSingle_Open(14UL);
  controle_hardware_abs_DW.obj_k.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Analog Input1' */
  controle_hardware_abs_DW.obj_l.matlabCodegenIsDeleted = false;
  controle_hardware_abs_DW.objisempty_f = true;
  controle_hardware_abs_DW.obj_l.isInitialized = 1L;
  controle_hardware_abs_DW.obj_l.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogInSingle_Open(15UL);
  controle_hardware_abs_DW.obj_l.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Analog Input2' */
  controle_hardware_abs_DW.obj_e.matlabCodegenIsDeleted = false;
  controle_hardware_abs_DW.objisempty_h = true;
  controle_hardware_abs_DW.obj_e.isInitialized = 1L;
  controle_hardware_abs_DW.obj_e.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogInSingle_Open(16UL);
  controle_hardware_abs_DW.obj_e.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Analog Input3' */
  controle_hardware_abs_DW.obj.matlabCodegenIsDeleted = false;
  controle_hardware_abs_DW.objisempty_b = true;
  controle_hardware_abs_DW.obj.isInitialized = 1L;
  controle_hardware_abs_DW.obj.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogInSingle_Open(17UL);
  controle_hardware_abs_DW.obj.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/PWM' */
  controle_hardware_abs_DW.obj_j.matlabCodegenIsDeleted = false;
  controle_hardware_abs_DW.objisempty = true;
  controle_hardware_abs_DW.obj_j.isInitialized = 1L;
  controle_hardware_abs_DW.obj_j.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(5UL,
    0.0, 0.0);
  controle_hardware_abs_DW.obj_j.isSetupComplete = true;
}

/* Model terminate function */
void controle_hardware_abs_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Analog Input' */
  if (!controle_hardware_abs_DW.obj_k.matlabCodegenIsDeleted) {
    controle_hardware_abs_DW.obj_k.matlabCodegenIsDeleted = true;
    if ((controle_hardware_abs_DW.obj_k.isInitialized == 1L) &&
        controle_hardware_abs_DW.obj_k.isSetupComplete) {
      controle_hardware_abs_DW.obj_k.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
        MW_AnalogIn_GetHandle(14UL);
      MW_AnalogIn_Close
        (controle_hardware_abs_DW.obj_k.AnalogInDriverObj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Analog Input' */

  /* Terminate for MATLABSystem: '<Root>/Analog Input1' */
  if (!controle_hardware_abs_DW.obj_l.matlabCodegenIsDeleted) {
    controle_hardware_abs_DW.obj_l.matlabCodegenIsDeleted = true;
    if ((controle_hardware_abs_DW.obj_l.isInitialized == 1L) &&
        controle_hardware_abs_DW.obj_l.isSetupComplete) {
      controle_hardware_abs_DW.obj_l.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
        MW_AnalogIn_GetHandle(15UL);
      MW_AnalogIn_Close
        (controle_hardware_abs_DW.obj_l.AnalogInDriverObj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Analog Input1' */

  /* Terminate for MATLABSystem: '<Root>/Analog Input2' */
  if (!controle_hardware_abs_DW.obj_e.matlabCodegenIsDeleted) {
    controle_hardware_abs_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((controle_hardware_abs_DW.obj_e.isInitialized == 1L) &&
        controle_hardware_abs_DW.obj_e.isSetupComplete) {
      controle_hardware_abs_DW.obj_e.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
        MW_AnalogIn_GetHandle(16UL);
      MW_AnalogIn_Close
        (controle_hardware_abs_DW.obj_e.AnalogInDriverObj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Analog Input2' */

  /* Terminate for MATLABSystem: '<Root>/Analog Input3' */
  if (!controle_hardware_abs_DW.obj.matlabCodegenIsDeleted) {
    controle_hardware_abs_DW.obj.matlabCodegenIsDeleted = true;
    if ((controle_hardware_abs_DW.obj.isInitialized == 1L) &&
        controle_hardware_abs_DW.obj.isSetupComplete) {
      controle_hardware_abs_DW.obj.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
        MW_AnalogIn_GetHandle(17UL);
      MW_AnalogIn_Close
        (controle_hardware_abs_DW.obj.AnalogInDriverObj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Analog Input3' */

  /* Terminate for MATLABSystem: '<Root>/PWM' */
  if (!controle_hardware_abs_DW.obj_j.matlabCodegenIsDeleted) {
    controle_hardware_abs_DW.obj_j.matlabCodegenIsDeleted = true;
    if ((controle_hardware_abs_DW.obj_j.isInitialized == 1L) &&
        controle_hardware_abs_DW.obj_j.isSetupComplete) {
      controle_hardware_abs_DW.obj_j.PWMDriverObj.MW_PWM_HANDLE =
        MW_PWM_GetHandle(5UL);
      MW_PWM_SetDutyCycle
        (controle_hardware_abs_DW.obj_j.PWMDriverObj.MW_PWM_HANDLE, 0.0);
      controle_hardware_abs_DW.obj_j.PWMDriverObj.MW_PWM_HANDLE =
        MW_PWM_GetHandle(5UL);
      MW_PWM_Close(controle_hardware_abs_DW.obj_j.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM' */
}
