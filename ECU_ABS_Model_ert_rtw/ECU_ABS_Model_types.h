/*
 * ECU_ABS_Model_types.h
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

#ifndef ECU_ABS_Model_types_h_
#define ECU_ABS_Model_types_h_
#include "MW_SVD.h"
#include "rtwtypes.h"

/* Custom Type definition for MATLABSystem: '<Root>/PWM' */
#include "MW_SVD.h"
#ifndef struct_tag_7VFuPw0vSNrn5pRgG8Mc4C
#define struct_tag_7VFuPw0vSNrn5pRgG8Mc4C

struct tag_7VFuPw0vSNrn5pRgG8Mc4C
{
  MW_Handle_Type MW_PWM_HANDLE;
};

#endif                                 /* struct_tag_7VFuPw0vSNrn5pRgG8Mc4C */

#ifndef typedef_e_matlabshared_ioclient_perip_T
#define typedef_e_matlabshared_ioclient_perip_T

typedef struct tag_7VFuPw0vSNrn5pRgG8Mc4C e_matlabshared_ioclient_perip_T;

#endif                             /* typedef_e_matlabshared_ioclient_perip_T */

#ifndef struct_tag_RWocY1aAVmuibq0rYX5t0G
#define struct_tag_RWocY1aAVmuibq0rYX5t0G

struct tag_RWocY1aAVmuibq0rYX5t0G
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  e_matlabshared_ioclient_perip_T PWMDriverObj;
};

#endif                                 /* struct_tag_RWocY1aAVmuibq0rYX5t0G */

#ifndef typedef_codertarget_arduinobase_inter_T
#define typedef_codertarget_arduinobase_inter_T

typedef struct tag_RWocY1aAVmuibq0rYX5t0G codertarget_arduinobase_inter_T;

#endif                             /* typedef_codertarget_arduinobase_inter_T */

/* Parameters (default storage) */
typedef struct P_ECU_ABS_Model_T_ P_ECU_ABS_Model_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_ECU_ABS_Model_T RT_MODEL_ECU_ABS_Model_T;

#endif                                 /* ECU_ABS_Model_types_h_ */
