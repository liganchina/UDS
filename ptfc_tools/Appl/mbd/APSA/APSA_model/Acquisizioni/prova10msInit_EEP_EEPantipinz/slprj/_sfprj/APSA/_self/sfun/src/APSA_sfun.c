/* Include files */

#define IN_SF_MACHINE_SOURCE           1
#include "APSA_sfun.h"
#include "APSA_sfun_debug_macros.h"
#include "c1_APSA.h"
#include "c2_APSA.h"
#include "c4_APSA.h"
#include "c5_APSA.h"
#include "c6_APSA.h"
#include "c7_APSA.h"
#include "c8_APSA.h"
#include "c9_APSA.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _APSAMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void APSA_initializer(void)
{
}

void APSA_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_APSA_method_dispatcher(SimStruct *simstructPtr, unsigned int
  chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_APSA_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_APSA_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_APSA_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_APSA_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_APSA_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==7) {
    c7_APSA_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==8) {
    c8_APSA_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==9) {
    c9_APSA_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

extern void sf_APSA_uses_exported_functions(int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[])
{
  plhs[0] = mxCreateLogicalScalar(0);
}

unsigned int sf_APSA_process_check_sum_call( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2745568101U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(775529877U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3038078439U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2776302878U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4023273488U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3023748103U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2578303454U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1292027650U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_APSA_get_check_sum(mxArray *plhs[]);
          sf_c1_APSA_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_APSA_get_check_sum(mxArray *plhs[]);
          sf_c2_APSA_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_APSA_get_check_sum(mxArray *plhs[]);
          sf_c4_APSA_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_APSA_get_check_sum(mxArray *plhs[]);
          sf_c5_APSA_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_APSA_get_check_sum(mxArray *plhs[]);
          sf_c6_APSA_get_check_sum(plhs);
          break;
        }

       case 7:
        {
          extern void sf_c7_APSA_get_check_sum(mxArray *plhs[]);
          sf_c7_APSA_get_check_sum(plhs);
          break;
        }

       case 8:
        {
          extern void sf_c8_APSA_get_check_sum(mxArray *plhs[]);
          sf_c8_APSA_get_check_sum(plhs);
          break;
        }

       case 9:
        {
          extern void sf_c9_APSA_get_check_sum(mxArray *plhs[]);
          sf_c9_APSA_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1213122363U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2499509803U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(959266273U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3790816109U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1795126090U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1303769368U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(397491954U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3854730674U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_APSA_autoinheritance_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "gfwgYAWE4u08pcS9RoID2F") == 0) {
          extern mxArray *sf_c1_APSA_get_autoinheritance_info(void);
          plhs[0] = sf_c1_APSA_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "YDhojF6BUKMrUJuhmOO8AG") == 0) {
          extern mxArray *sf_c2_APSA_get_autoinheritance_info(void);
          plhs[0] = sf_c2_APSA_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "rmTZBaeNTuyyuv976XplTE") == 0) {
          extern mxArray *sf_c4_APSA_get_autoinheritance_info(void);
          plhs[0] = sf_c4_APSA_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "uL9jcKGA6838zxLgqZ1il") == 0) {
          extern mxArray *sf_c5_APSA_get_autoinheritance_info(void);
          plhs[0] = sf_c5_APSA_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "uL9jcKGA6838zxLgqZ1il") == 0) {
          extern mxArray *sf_c6_APSA_get_autoinheritance_info(void);
          plhs[0] = sf_c6_APSA_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 7:
      {
        if (strcmp(aiChksum, "L2erPxXLmRXvh0K4hNeCLE") == 0) {
          extern mxArray *sf_c7_APSA_get_autoinheritance_info(void);
          plhs[0] = sf_c7_APSA_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 8:
      {
        if (strcmp(aiChksum, "uL9jcKGA6838zxLgqZ1il") == 0) {
          extern mxArray *sf_c8_APSA_get_autoinheritance_info(void);
          plhs[0] = sf_c8_APSA_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 9:
      {
        if (strcmp(aiChksum, "L2erPxXLmRXvh0K4hNeCLE") == 0) {
          extern mxArray *sf_c9_APSA_get_autoinheritance_info(void);
          plhs[0] = sf_c9_APSA_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_APSA_get_eml_resolved_functions_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_APSA_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_APSA_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray *sf_c2_APSA_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_APSA_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_APSA_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_APSA_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_APSA_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_APSA_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray *sf_c6_APSA_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_APSA_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 7:
      {
        extern const mxArray *sf_c7_APSA_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c7_APSA_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 8:
      {
        extern const mxArray *sf_c8_APSA_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c8_APSA_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 9:
      {
        extern const mxArray *sf_c9_APSA_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c9_APSA_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_APSA_third_party_uses_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "W1pLsl8VieHi7tv5i97oaH") == 0) {
          extern mxArray *sf_c1_APSA_third_party_uses_info(void);
          plhs[0] = sf_c1_APSA_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "UCJxgYSedRXhsdcrMQVREB") == 0) {
          extern mxArray *sf_c2_APSA_third_party_uses_info(void);
          plhs[0] = sf_c2_APSA_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "5fYFGqfubUbZ0SLVVG2H8B") == 0) {
          extern mxArray *sf_c4_APSA_third_party_uses_info(void);
          plhs[0] = sf_c4_APSA_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "07vEVLLuwu0mXv45TNSB9F") == 0) {
          extern mxArray *sf_c5_APSA_third_party_uses_info(void);
          plhs[0] = sf_c5_APSA_third_party_uses_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "07vEVLLuwu0mXv45TNSB9F") == 0) {
          extern mxArray *sf_c6_APSA_third_party_uses_info(void);
          plhs[0] = sf_c6_APSA_third_party_uses_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "FGjORsjPTeG2GiCFeZybSH") == 0) {
          extern mxArray *sf_c7_APSA_third_party_uses_info(void);
          plhs[0] = sf_c7_APSA_third_party_uses_info();
          break;
        }
      }

     case 8:
      {
        if (strcmp(tpChksum, "FTHj0kyYTTEcV00KXVem7C") == 0) {
          extern mxArray *sf_c8_APSA_third_party_uses_info(void);
          plhs[0] = sf_c8_APSA_third_party_uses_info();
          break;
        }
      }

     case 9:
      {
        if (strcmp(tpChksum, "BuXj2XzgM05JehrXy2FrnC") == 0) {
          extern mxArray *sf_c9_APSA_third_party_uses_info(void);
          plhs[0] = sf_c9_APSA_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_APSA_jit_fallback_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the jit_fallback_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_jit_fallback_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "W1pLsl8VieHi7tv5i97oaH") == 0) {
          extern mxArray *sf_c1_APSA_jit_fallback_info(void);
          plhs[0] = sf_c1_APSA_jit_fallback_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "UCJxgYSedRXhsdcrMQVREB") == 0) {
          extern mxArray *sf_c2_APSA_jit_fallback_info(void);
          plhs[0] = sf_c2_APSA_jit_fallback_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "5fYFGqfubUbZ0SLVVG2H8B") == 0) {
          extern mxArray *sf_c4_APSA_jit_fallback_info(void);
          plhs[0] = sf_c4_APSA_jit_fallback_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "07vEVLLuwu0mXv45TNSB9F") == 0) {
          extern mxArray *sf_c5_APSA_jit_fallback_info(void);
          plhs[0] = sf_c5_APSA_jit_fallback_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "07vEVLLuwu0mXv45TNSB9F") == 0) {
          extern mxArray *sf_c6_APSA_jit_fallback_info(void);
          plhs[0] = sf_c6_APSA_jit_fallback_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "FGjORsjPTeG2GiCFeZybSH") == 0) {
          extern mxArray *sf_c7_APSA_jit_fallback_info(void);
          plhs[0] = sf_c7_APSA_jit_fallback_info();
          break;
        }
      }

     case 8:
      {
        if (strcmp(tpChksum, "FTHj0kyYTTEcV00KXVem7C") == 0) {
          extern mxArray *sf_c8_APSA_jit_fallback_info(void);
          plhs[0] = sf_c8_APSA_jit_fallback_info();
          break;
        }
      }

     case 9:
      {
        if (strcmp(tpChksum, "BuXj2XzgM05JehrXy2FrnC") == 0) {
          extern mxArray *sf_c9_APSA_jit_fallback_info(void);
          plhs[0] = sf_c9_APSA_jit_fallback_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_APSA_updateBuildInfo_args_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "W1pLsl8VieHi7tv5i97oaH") == 0) {
          extern mxArray *sf_c1_APSA_updateBuildInfo_args_info(void);
          plhs[0] = sf_c1_APSA_updateBuildInfo_args_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "UCJxgYSedRXhsdcrMQVREB") == 0) {
          extern mxArray *sf_c2_APSA_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_APSA_updateBuildInfo_args_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "5fYFGqfubUbZ0SLVVG2H8B") == 0) {
          extern mxArray *sf_c4_APSA_updateBuildInfo_args_info(void);
          plhs[0] = sf_c4_APSA_updateBuildInfo_args_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "07vEVLLuwu0mXv45TNSB9F") == 0) {
          extern mxArray *sf_c5_APSA_updateBuildInfo_args_info(void);
          plhs[0] = sf_c5_APSA_updateBuildInfo_args_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "07vEVLLuwu0mXv45TNSB9F") == 0) {
          extern mxArray *sf_c6_APSA_updateBuildInfo_args_info(void);
          plhs[0] = sf_c6_APSA_updateBuildInfo_args_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "FGjORsjPTeG2GiCFeZybSH") == 0) {
          extern mxArray *sf_c7_APSA_updateBuildInfo_args_info(void);
          plhs[0] = sf_c7_APSA_updateBuildInfo_args_info();
          break;
        }
      }

     case 8:
      {
        if (strcmp(tpChksum, "FTHj0kyYTTEcV00KXVem7C") == 0) {
          extern mxArray *sf_c8_APSA_updateBuildInfo_args_info(void);
          plhs[0] = sf_c8_APSA_updateBuildInfo_args_info();
          break;
        }
      }

     case 9:
      {
        if (strcmp(tpChksum, "BuXj2XzgM05JehrXy2FrnC") == 0) {
          extern mxArray *sf_c9_APSA_updateBuildInfo_args_info(void);
          plhs[0] = sf_c9_APSA_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void sf_APSA_get_post_codegen_info( int nlhs, mxArray * plhs[], int nrhs, const
  mxArray * prhs[] )
{
  unsigned int chartFileNumber = (unsigned int) mxGetScalar(prhs[0]);
  char tpChksum[64];
  mxGetString(prhs[1], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  switch (chartFileNumber) {
   case 1:
    {
      if (strcmp(tpChksum, "W1pLsl8VieHi7tv5i97oaH") == 0) {
        extern mxArray *sf_c1_APSA_get_post_codegen_info(void);
        plhs[0] = sf_c1_APSA_get_post_codegen_info();
        return;
      }
    }
    break;

   case 2:
    {
      if (strcmp(tpChksum, "UCJxgYSedRXhsdcrMQVREB") == 0) {
        extern mxArray *sf_c2_APSA_get_post_codegen_info(void);
        plhs[0] = sf_c2_APSA_get_post_codegen_info();
        return;
      }
    }
    break;

   case 4:
    {
      if (strcmp(tpChksum, "5fYFGqfubUbZ0SLVVG2H8B") == 0) {
        extern mxArray *sf_c4_APSA_get_post_codegen_info(void);
        plhs[0] = sf_c4_APSA_get_post_codegen_info();
        return;
      }
    }
    break;

   case 5:
    {
      if (strcmp(tpChksum, "07vEVLLuwu0mXv45TNSB9F") == 0) {
        extern mxArray *sf_c5_APSA_get_post_codegen_info(void);
        plhs[0] = sf_c5_APSA_get_post_codegen_info();
        return;
      }
    }
    break;

   case 6:
    {
      if (strcmp(tpChksum, "07vEVLLuwu0mXv45TNSB9F") == 0) {
        extern mxArray *sf_c6_APSA_get_post_codegen_info(void);
        plhs[0] = sf_c6_APSA_get_post_codegen_info();
        return;
      }
    }
    break;

   case 7:
    {
      if (strcmp(tpChksum, "FGjORsjPTeG2GiCFeZybSH") == 0) {
        extern mxArray *sf_c7_APSA_get_post_codegen_info(void);
        plhs[0] = sf_c7_APSA_get_post_codegen_info();
        return;
      }
    }
    break;

   case 8:
    {
      if (strcmp(tpChksum, "FTHj0kyYTTEcV00KXVem7C") == 0) {
        extern mxArray *sf_c8_APSA_get_post_codegen_info(void);
        plhs[0] = sf_c8_APSA_get_post_codegen_info();
        return;
      }
    }
    break;

   case 9:
    {
      if (strcmp(tpChksum, "BuXj2XzgM05JehrXy2FrnC") == 0) {
        extern mxArray *sf_c9_APSA_get_post_codegen_info(void);
        plhs[0] = sf_c9_APSA_get_post_codegen_info();
        return;
      }
    }
    break;

   default:
    break;
  }

  plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
}

void APSA_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _APSAMachineNumber_ = sf_debug_initialize_machine(debugInstance,"APSA","sfun",
    0,8,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,_APSAMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,_APSAMachineNumber_,0);
}

void APSA_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_APSA_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("APSA", "APSA");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_APSA_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
