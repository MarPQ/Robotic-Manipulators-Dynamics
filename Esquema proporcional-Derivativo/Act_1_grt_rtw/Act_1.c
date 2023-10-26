/*
 * Act_1.c
 *
 * Code generation for model "Act_1".
 *
 * Model version              : 1.10
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C source code generated on : Tue Nov 17 18:56:12 2020
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Act_1.h"
#include "Act_1_private.h"

/* Block signals (auto storage) */
B_Act_1_T Act_1_B;

/* Continuous states */
X_Act_1_T Act_1_X;

/* Block states (auto storage) */
DW_Act_1_T Act_1_DW;

/* Real-time model */
RT_MODEL_Act_1_T Act_1_M_;
RT_MODEL_Act_1_T *const Act_1_M = &Act_1_M_;

/*
 * This function updates continuous states using the ODE2 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE2_IntgData *id = (ODE2_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T temp;
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Act_1_derivatives();

  /* f1 = f(t + h, y + h*f0) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f0[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f1);
  Act_1_step();
  Act_1_derivatives();

  /* tnew = t + h
     ynew = y + (h/2)*(f0 + f1) */
  temp = 0.5*h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + f1[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Act_1_step(void)
{
  real_T m12;
  real_T M[4];
  real_T B[2];
  int32_T r1;
  int32_T r2;
  real_T m12_tmp;
  real_T B_tmp;
  if (rtmIsMajorTimeStep(Act_1_M)) {
    /* set solver stop time */
    if (!(Act_1_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Act_1_M->solverInfo, ((Act_1_M->Timing.clockTickH0
        + 1) * Act_1_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Act_1_M->solverInfo, ((Act_1_M->Timing.clockTick0 +
        1) * Act_1_M->Timing.stepSize0 + Act_1_M->Timing.clockTickH0 *
        Act_1_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Act_1_M)) {
    Act_1_M->Timing.t[0] = rtsiGetT(&Act_1_M->solverInfo);
  }

  /* Integrator: '<Root>/Integrator1' */
  Act_1_B.Integrator1[0] = Act_1_X.Integrator1_CSTATE[0];

  /* Integrator: '<Root>/Integrator' */
  Act_1_B.Integrator[0] = Act_1_X.Integrator_CSTATE[0];

  /* Integrator: '<Root>/Integrator1' */
  Act_1_B.Integrator1[1] = Act_1_X.Integrator1_CSTATE[1];

  /* Integrator: '<Root>/Integrator' */
  Act_1_B.Integrator[1] = Act_1_X.Integrator_CSTATE[1];
  if (rtmIsMajorTimeStep(Act_1_M)) {
  }

  /* MATLAB Function: '<Root>/MATLAB Function' */
  m12_tmp = cos(Act_1_B.Integrator1[1]);
  m12 = (0.045 * m12_tmp + 0.0225) * 0.2 + 0.001;
  M[0] = (((0.09 * m12_tmp + 0.126) * 0.2 + 0.0045) + 0.001) + 0.001;
  M[2] = m12;
  M[1] = m12;
  M[3] = 0.0055;
  m12 = -0.009 * sin(Act_1_B.Integrator1[1]);
  m12_tmp = cos(Act_1_B.Integrator1[0]);
  B_tmp = cos(Act_1_B.Integrator1[0] + Act_1_B.Integrator1[1]);
  B[0] = (0.0 - ((2.0 * m12 * Act_1_B.Integrator[1] + m12 * Act_1_B.Integrator[0])
                 * Act_1_B.Integrator[1] + m12 * Act_1_B.Integrator[1] *
                 Act_1_B.Integrator[0])) - ((B_tmp * 0.15 + 0.3 * m12_tmp) *
    1.9620000000000002 + 0.2943 * m12_tmp);
  B[1] = (0.0 - (-m12 * Act_1_B.Integrator[0] * Act_1_B.Integrator[0] + 0.0 *
                 Act_1_B.Integrator[1])) - B_tmp * 0.2943;
  if (fabs(M[1]) > fabs(M[0])) {
    r1 = 1;
    r2 = 0;
  } else {
    r1 = 0;
    r2 = 1;
  }

  m12 = M[r2] / M[r1];
  Act_1_B.q_ddot[1] = (B[r2] - B[r1] * m12) / (M[2 + r2] - M[2 + r1] * m12);
  Act_1_B.q_ddot[0] = (B[r1] - M[2 + r1] * Act_1_B.q_ddot[1]) / M[r1];

  /* End of MATLAB Function: '<Root>/MATLAB Function' */
  if (rtmIsMajorTimeStep(Act_1_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(Act_1_M->rtwLogInfo, (Act_1_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Act_1_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(Act_1_M)!=-1) &&
          !((rtmGetTFinal(Act_1_M)-(((Act_1_M->Timing.clockTick1+
               Act_1_M->Timing.clockTickH1* 4294967296.0)) * 0.001)) >
            (((Act_1_M->Timing.clockTick1+Act_1_M->Timing.clockTickH1*
               4294967296.0)) * 0.001) * (DBL_EPSILON))) {
        rtmSetErrorStatus(Act_1_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&Act_1_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Act_1_M->Timing.clockTick0)) {
      ++Act_1_M->Timing.clockTickH0;
    }

    Act_1_M->Timing.t[0] = rtsiGetSolverStopTime(&Act_1_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      Act_1_M->Timing.clockTick1++;
      if (!Act_1_M->Timing.clockTick1) {
        Act_1_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Act_1_derivatives(void)
{
  XDot_Act_1_T *_rtXdot;
  _rtXdot = ((XDot_Act_1_T *) Act_1_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[0] = Act_1_B.Integrator[0];

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = Act_1_B.q_ddot[0];

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[1] = Act_1_B.Integrator[1];

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE[1] = Act_1_B.q_ddot[1];
}

/* Model initialize function */
void Act_1_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Act_1_M, 0,
                sizeof(RT_MODEL_Act_1_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Act_1_M->solverInfo, &Act_1_M->Timing.simTimeStep);
    rtsiSetTPtr(&Act_1_M->solverInfo, &rtmGetTPtr(Act_1_M));
    rtsiSetStepSizePtr(&Act_1_M->solverInfo, &Act_1_M->Timing.stepSize0);
    rtsiSetdXPtr(&Act_1_M->solverInfo, &Act_1_M->derivs);
    rtsiSetContStatesPtr(&Act_1_M->solverInfo, (real_T **) &Act_1_M->contStates);
    rtsiSetNumContStatesPtr(&Act_1_M->solverInfo, &Act_1_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Act_1_M->solverInfo,
      &Act_1_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Act_1_M->solverInfo,
      &Act_1_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Act_1_M->solverInfo,
      &Act_1_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Act_1_M->solverInfo, (&rtmGetErrorStatus(Act_1_M)));
    rtsiSetRTModelPtr(&Act_1_M->solverInfo, Act_1_M);
  }

  rtsiSetSimTimeStep(&Act_1_M->solverInfo, MAJOR_TIME_STEP);
  Act_1_M->intgData.y = Act_1_M->odeY;
  Act_1_M->intgData.f[0] = Act_1_M->odeF[0];
  Act_1_M->intgData.f[1] = Act_1_M->odeF[1];
  Act_1_M->contStates = ((X_Act_1_T *) &Act_1_X);
  rtsiSetSolverData(&Act_1_M->solverInfo, (void *)&Act_1_M->intgData);
  rtsiSetSolverName(&Act_1_M->solverInfo,"ode2");
  rtmSetTPtr(Act_1_M, &Act_1_M->Timing.tArray[0]);
  rtmSetTFinal(Act_1_M, 60.0);
  Act_1_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    Act_1_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Act_1_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Act_1_M->rtwLogInfo, (NULL));
    rtliSetLogT(Act_1_M->rtwLogInfo, "tout");
    rtliSetLogX(Act_1_M->rtwLogInfo, "");
    rtliSetLogXFinal(Act_1_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Act_1_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Act_1_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Act_1_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Act_1_M->rtwLogInfo, 1);
    rtliSetLogY(Act_1_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Act_1_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Act_1_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &Act_1_B), 0,
                sizeof(B_Act_1_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Act_1_X, 0,
                  sizeof(X_Act_1_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Act_1_DW, 0,
                sizeof(DW_Act_1_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Act_1_M->rtwLogInfo, 0.0, rtmGetTFinal
    (Act_1_M), Act_1_M->Timing.stepSize0, (&rtmGetErrorStatus(Act_1_M)));

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  Act_1_X.Integrator1_CSTATE[0] = Act_1_P.Integrator1_IC[0];

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  Act_1_X.Integrator_CSTATE[0] = Act_1_P.Integrator_IC[0];

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  Act_1_X.Integrator1_CSTATE[1] = Act_1_P.Integrator1_IC[1];

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  Act_1_X.Integrator_CSTATE[1] = Act_1_P.Integrator_IC[1];
}

/* Model terminate function */
void Act_1_terminate(void)
{
  /* (no terminate code required) */
}
