/*
 * ECU_ABS_Model.c
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

#include "ECU_ABS_Model.h"
#include "ECU_ABS_Model_types.h"
#include "rtwtypes.h"
#include "ECU_ABS_Model_private.h"
#include <string.h>

/* Block signals (default storage) */
B_ECU_ABS_Model_T ECU_ABS_Model_B;

/* Block states (default storage) */
DW_ECU_ABS_Model_T ECU_ABS_Model_DW;

/* Real-time model */
static RT_MODEL_ECU_ABS_Model_T ECU_ABS_Model_M_;
RT_MODEL_ECU_ABS_Model_T *const ECU_ABS_Model_M = &ECU_ABS_Model_M_;

/* Forward declaration for local functions */
static void ECU_ABS_Mode_SystemCore_release(codertarget_arduinobase_inter_T *obj);
static void ECU_ABS_Mode_SystemCore_release(codertarget_arduinobase_inter_T *obj)
{
  /* Start for MATLABSystem: '<Root>/PWM' */
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(9UL);
    MW_PWM_SetDutyCycle(obj->PWMDriverObj.MW_PWM_HANDLE, -0.0);
    obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(9UL);
    MW_PWM_Close(obj->PWMDriverObj.MW_PWM_HANDLE);
  }

  /* End of Start for MATLABSystem: '<Root>/PWM' */
}

/* Model step function */
void ECU_ABS_Model_step(void)
{
  real_T u0;

  /* FromWorkspace: '<S1>/fromWS_Signal 1' */
  {
    real_T t = ECU_ABS_Model_M->Timing.t[0];
    real_T *pTimeValues = (real_T *)
      ECU_ABS_Model_DW.fromWS_Signal1_PWORK.TimePtr;
    real_T *pDataValues = (real_T *)
      ECU_ABS_Model_DW.fromWS_Signal1_PWORK.DataPtr;
    const real_T inputTimeTolerance = 0;
    if (t < pTimeValues[0]) {
      ECU_ABS_Model_B.Velocidade_Roda_Diant_Esq = 0.0;
    } else if (fabs(t - pTimeValues[5]) <= inputTimeTolerance) {
      ECU_ABS_Model_B.Velocidade_Roda_Diant_Esq = pDataValues[5];
    } else if (t > pTimeValues[5] &&
               fabs(t - pTimeValues[5]) > inputTimeTolerance) {
      ECU_ABS_Model_B.Velocidade_Roda_Diant_Esq = 0.0;
    } else {
      int_T currTimeIndex = ECU_ABS_Model_DW.fromWS_Signal1_IWORK.PrevIndex;
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t > pTimeValues[currTimeIndex + 1] ||
               fabs(t - pTimeValues[currTimeIndex + 1]) <= inputTimeTolerance) {
          currTimeIndex++;
        }
      }

      ECU_ABS_Model_B.Velocidade_Roda_Diant_Esq = pDataValues[currTimeIndex];
      ECU_ABS_Model_DW.fromWS_Signal1_IWORK.PrevIndex = currTimeIndex;
    }
  }

  /* FromWorkspace: '<S1>/From Workspace' */
  {
    real_T t = ECU_ABS_Model_M->Timing.t[0];
    real_T *pTimeValues = (real_T *)
      ECU_ABS_Model_DW.FromWorkspace_PWORK.TimePtr;
    real_T *pDataValues = (real_T *)
      ECU_ABS_Model_DW.FromWorkspace_PWORK.DataPtr;
    const real_T inputTimeTolerance = 0;
    if (t < pTimeValues[0]) {
      ECU_ABS_Model_B.Velocidade_Roda_Diant_Dir = 0.0;
    } else if (fabs(t - pTimeValues[5]) <= inputTimeTolerance) {
      ECU_ABS_Model_B.Velocidade_Roda_Diant_Dir = pDataValues[5];
    } else if (t > pTimeValues[5] &&
               fabs(t - pTimeValues[5]) > inputTimeTolerance) {
      ECU_ABS_Model_B.Velocidade_Roda_Diant_Dir = 0.0;
    } else {
      int_T currTimeIndex = ECU_ABS_Model_DW.FromWorkspace_IWORK.PrevIndex;
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t > pTimeValues[currTimeIndex + 1] ||
               fabs(t - pTimeValues[currTimeIndex + 1]) <= inputTimeTolerance) {
          currTimeIndex++;
        }
      }

      ECU_ABS_Model_B.Velocidade_Roda_Diant_Dir = pDataValues[currTimeIndex];
      ECU_ABS_Model_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;
    }
  }

  /* FromWorkspace: '<S1>/From Workspace1' */
  {
    real_T t = ECU_ABS_Model_M->Timing.t[0];
    real_T *pTimeValues = (real_T *)
      ECU_ABS_Model_DW.FromWorkspace1_PWORK.TimePtr;
    real_T *pDataValues = (real_T *)
      ECU_ABS_Model_DW.FromWorkspace1_PWORK.DataPtr;
    const real_T inputTimeTolerance = 0;
    if (t < pTimeValues[0]) {
      ECU_ABS_Model_B.Velocidade_Roda_Tras_Esq = 0.0;
    } else if (fabs(t - pTimeValues[5]) <= inputTimeTolerance) {
      ECU_ABS_Model_B.Velocidade_Roda_Tras_Esq = pDataValues[5];
    } else if (t > pTimeValues[5] &&
               fabs(t - pTimeValues[5]) > inputTimeTolerance) {
      ECU_ABS_Model_B.Velocidade_Roda_Tras_Esq = 0.0;
    } else {
      int_T currTimeIndex = ECU_ABS_Model_DW.FromWorkspace1_IWORK.PrevIndex;
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t > pTimeValues[currTimeIndex + 1] ||
               fabs(t - pTimeValues[currTimeIndex + 1]) <= inputTimeTolerance) {
          currTimeIndex++;
        }
      }

      ECU_ABS_Model_B.Velocidade_Roda_Tras_Esq = pDataValues[currTimeIndex];
      ECU_ABS_Model_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;
    }
  }

  /* FromWorkspace: '<S1>/From Workspace2' */
  {
    real_T t = ECU_ABS_Model_M->Timing.t[0];
    real_T *pTimeValues = (real_T *)
      ECU_ABS_Model_DW.FromWorkspace2_PWORK.TimePtr;
    real_T *pDataValues = (real_T *)
      ECU_ABS_Model_DW.FromWorkspace2_PWORK.DataPtr;
    const real_T inputTimeTolerance = 0;
    if (t < pTimeValues[0]) {
      ECU_ABS_Model_B.Velocidade_Roda_Tras_Dir = 0.0;
    } else if (fabs(t - pTimeValues[5]) <= inputTimeTolerance) {
      ECU_ABS_Model_B.Velocidade_Roda_Tras_Dir = pDataValues[5];
    } else if (t > pTimeValues[5] &&
               fabs(t - pTimeValues[5]) > inputTimeTolerance) {
      ECU_ABS_Model_B.Velocidade_Roda_Tras_Dir = 0.0;
    } else {
      int_T currTimeIndex = ECU_ABS_Model_DW.FromWorkspace2_IWORK.PrevIndex;
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t > pTimeValues[currTimeIndex + 1] ||
               fabs(t - pTimeValues[currTimeIndex + 1]) <= inputTimeTolerance) {
          currTimeIndex++;
        }
      }

      ECU_ABS_Model_B.Velocidade_Roda_Tras_Dir = pDataValues[currTimeIndex];
      ECU_ABS_Model_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;
    }
  }

  /* Logic: '<Root>/Logical Operator' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Velocidade Veículo Ref'
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
   */
  ECU_ABS_Model_B.Ativar_ABS = (((ECU_ABS_Model_B.Velocidade_Roda_Diant_Esq -
    ECU_ABS_Model_P.VelocidadeVeculoRef_Value) /
    ECU_ABS_Model_P.VelocidadeVeculoRef_Value < ECU_ABS_Model_P.Constant_Value) ||
    ((ECU_ABS_Model_B.Velocidade_Roda_Diant_Dir -
      ECU_ABS_Model_P.VelocidadeVeculoRef_Value) /
     ECU_ABS_Model_P.VelocidadeVeculoRef_Value < ECU_ABS_Model_P.Constant_Value)
    || ((ECU_ABS_Model_B.Velocidade_Roda_Tras_Esq -
         ECU_ABS_Model_P.VelocidadeVeculoRef_Value) /
        ECU_ABS_Model_P.VelocidadeVeculoRef_Value <
        ECU_ABS_Model_P.Constant_Value) ||
    ((ECU_ABS_Model_B.Velocidade_Roda_Tras_Dir -
      ECU_ABS_Model_P.VelocidadeVeculoRef_Value) /
     ECU_ABS_Model_P.VelocidadeVeculoRef_Value < ECU_ABS_Model_P.Constant_Value));

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   */
  if (ECU_ABS_Model_B.Ativar_ABS) {
    u0 = ECU_ABS_Model_P.Constant1_Value;
  } else {
    u0 = ECU_ABS_Model_P.Constant2_Value;
  }

  /* Start for MATLABSystem: '<Root>/PWM' incorporates:
   *  Switch: '<Root>/Switch'
   */
  if (!(u0 <= 255.0)) {
    u0 = 255.0;
  }

  /* MATLABSystem: '<Root>/PWM' */
  ECU_ABS_Model_DW.obj.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(9UL);

  /* Start for MATLABSystem: '<Root>/PWM' */
  if (!(u0 >= 0.0)) {
    u0 = 0.0;
  }

  /* MATLABSystem: '<Root>/PWM' */
  MW_PWM_SetDutyCycle(ECU_ABS_Model_DW.obj.PWMDriverObj.MW_PWM_HANDLE, -(u0 *
    20000.0 / 255.0));

  {                                    /* Sample time: [0.0001s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
      (((ECU_ABS_Model_M->Timing.clockTick1+ECU_ABS_Model_M->Timing.clockTickH1*
         4294967296.0) * 1) + 0);

    /* Trigger External Mode event */
    errorCode = extmodeEvent(1, extmodeTime);
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode event errors
         may be added here */
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ECU_ABS_Model_M->Timing.clockTick0)) {
    ++ECU_ABS_Model_M->Timing.clockTickH0;
  }

  ECU_ABS_Model_M->Timing.t[0] = ECU_ABS_Model_M->Timing.clockTick0 *
    ECU_ABS_Model_M->Timing.stepSize0 + ECU_ABS_Model_M->Timing.clockTickH0 *
    ECU_ABS_Model_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.0001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.0001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    ECU_ABS_Model_M->Timing.clockTick1++;
    if (!ECU_ABS_Model_M->Timing.clockTick1) {
      ECU_ABS_Model_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void ECU_ABS_Model_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)ECU_ABS_Model_M, 0,
                sizeof(RT_MODEL_ECU_ABS_Model_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&ECU_ABS_Model_M->solverInfo,
                          &ECU_ABS_Model_M->Timing.simTimeStep);
    rtsiSetTPtr(&ECU_ABS_Model_M->solverInfo, &rtmGetTPtr(ECU_ABS_Model_M));
    rtsiSetStepSizePtr(&ECU_ABS_Model_M->solverInfo,
                       &ECU_ABS_Model_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&ECU_ABS_Model_M->solverInfo, (&rtmGetErrorStatus
      (ECU_ABS_Model_M)));
    rtsiSetRTModelPtr(&ECU_ABS_Model_M->solverInfo, ECU_ABS_Model_M);
  }

  rtsiSetSimTimeStep(&ECU_ABS_Model_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&ECU_ABS_Model_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&ECU_ABS_Model_M->solverInfo, false);
  rtsiSetSolverName(&ECU_ABS_Model_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(ECU_ABS_Model_M, &ECU_ABS_Model_M->Timing.tArray[0]);
  rtmSetTFinal(ECU_ABS_Model_M, 26.0);
  ECU_ABS_Model_M->Timing.stepSize0 = 0.0001;

  /* External mode info */
  ECU_ABS_Model_M->Sizes.checksums[0] = (900865387U);
  ECU_ABS_Model_M->Sizes.checksums[1] = (2674195505U);
  ECU_ABS_Model_M->Sizes.checksums[2] = (3665418308U);
  ECU_ABS_Model_M->Sizes.checksums[3] = (253043832U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    ECU_ABS_Model_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(ECU_ABS_Model_M->extModeInfo,
      &ECU_ABS_Model_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(ECU_ABS_Model_M->extModeInfo,
                        ECU_ABS_Model_M->Sizes.checksums);
    rteiSetTFinalTicks(ECU_ABS_Model_M->extModeInfo, 260000);
  }

  /* block I/O */
  (void) memset(((void *) &ECU_ABS_Model_B), 0,
                sizeof(B_ECU_ABS_Model_T));

  /* states (dwork) */
  (void) memset((void *)&ECU_ABS_Model_DW, 0,
                sizeof(DW_ECU_ABS_Model_T));

  /* Start for FromWorkspace: '<S1>/fromWS_Signal 1' */
  {
    static real_T pTimeValues0[] = { 0.0, 1.0, 2.0, 4.0, 5.0, 25.0 } ;

    static real_T pDataValues0[] = { 20.0, 20.0, 10.0, 10.0, 20.0, 20.0 } ;

    ECU_ABS_Model_DW.fromWS_Signal1_PWORK.TimePtr = (void *) pTimeValues0;
    ECU_ABS_Model_DW.fromWS_Signal1_PWORK.DataPtr = (void *) pDataValues0;
    ECU_ABS_Model_DW.fromWS_Signal1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<S1>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 7.0, 8.0, 10.0, 11.0, 25.0 } ;

    static real_T pDataValues0[] = { 20.0, 20.0, 10.0, 10.0, 20.0, 20.0 } ;

    ECU_ABS_Model_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    ECU_ABS_Model_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    ECU_ABS_Model_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<S1>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 13.0, 14.0, 16.0, 17.0, 25.0 } ;

    static real_T pDataValues0[] = { 20.0, 20.0, 10.0, 10.0, 20.0, 20.0 } ;

    ECU_ABS_Model_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    ECU_ABS_Model_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    ECU_ABS_Model_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<S1>/From Workspace2' */
  {
    static real_T pTimeValues0[] = { 0.0, 19.0, 20.0, 22.0, 23.0, 25.0 } ;

    static real_T pDataValues0[] = { 20.0, 20.0, 10.0, 10.0, 20.0, 20.0 } ;

    ECU_ABS_Model_DW.FromWorkspace2_PWORK.TimePtr = (void *) pTimeValues0;
    ECU_ABS_Model_DW.FromWorkspace2_PWORK.DataPtr = (void *) pDataValues0;
    ECU_ABS_Model_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* Start for MATLABSystem: '<Root>/PWM' */
  ECU_ABS_Model_DW.obj.matlabCodegenIsDeleted = false;
  ECU_ABS_Model_DW.objisempty = true;
  ECU_ABS_Model_DW.obj.isInitialized = 1L;
  ECU_ABS_Model_DW.obj.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(9UL, 2.0,
    20000.0);
  ECU_ABS_Model_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void ECU_ABS_Model_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/PWM' */
  if (!ECU_ABS_Model_DW.obj.matlabCodegenIsDeleted) {
    ECU_ABS_Model_DW.obj.matlabCodegenIsDeleted = true;
    ECU_ABS_Mode_SystemCore_release(&ECU_ABS_Model_DW.obj);
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM' */
}
