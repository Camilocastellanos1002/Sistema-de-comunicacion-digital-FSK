#ifndef RTW_HEADER_FSK_2_acc_private_h_
#define RTW_HEADER_FSK_2_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "FSK_2_acc.h"
#if !defined(ss_VALIDATE_MEMORY)
#define ss_VALIDATE_MEMORY(S, ptr)   if(!(ptr)) {\
  ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
  }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((ptr));\
  (ptr) = (NULL);\
  }
#else
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((void *)(ptr));\
  (ptr) = (NULL);\
  }
#endif
#endif
#ifndef UCHAR_MAX
#include <limits.h>
#endif
#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#ifndef rtInterpolate
#define rtInterpolate(v1,v2,f1,f2)   (((v1)==(v2))?((double)(v1)):  (((f1)*((double)(v1)))+((f2)*((double)(v2)))))
#endif
#ifndef rtRound
#define rtRound(v) ( ((v) >= 0) ?   muDoubleScalarFloor((v) + 0.5) :   muDoubleScalarCeil((v) - 0.5) )
#endif
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
extern real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) ; extern real_T
rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T * u ) ; boolean_T
FSK_2_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T * tailPtr ,
int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * * tBufPtr ,
real_T * * uBufPtr , real_T * * xBufPtr , boolean_T isfixedbuf , boolean_T
istransportdelay , int_T * maxNewBufSzPtr ) ; real_T
FSK_2_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart , real_T
* tBuf , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx ,
int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) ; void FSK_2_MuestreoyRetencion_Init (
SimStruct * S , B_MuestreoyRetencion_FSK_2_T * localB ,
P_MuestreoyRetencion_FSK_2_T * localP ) ; void FSK_2_MuestreoyRetencion (
SimStruct * S , real_T rtu_Trigger , real_T rtu_In ,
B_MuestreoyRetencion_FSK_2_T * localB , DW_MuestreoyRetencion_FSK_2_T *
localDW , ZCE_MuestreoyRetencion_FSK_2_T * localZCE ) ; void
FSK_2_SampleandHold_Init ( SimStruct * S , B_SampleandHold_FSK_2_T * localB ,
P_SampleandHold_FSK_2_T * localP ) ; void FSK_2_SampleandHold ( SimStruct * S
, real_T rtu_Trigger , boolean_T rtu_In , B_SampleandHold_FSK_2_T * localB ,
DW_SampleandHold_FSK_2_T * localDW , ZCE_SampleandHold_FSK_2_T * localZCE ) ;
void FSK_2_TriggeredSubsystem_Init ( SimStruct * S ,
B_TriggeredSubsystem_FSK_2_T * localB , P_TriggeredSubsystem_FSK_2_T * localP
) ; void FSK_2_TriggeredSubsystem ( SimStruct * S , boolean_T rtu_Trigger ,
real_T rtu_In1 , B_TriggeredSubsystem_FSK_2_T * localB ,
DW_TriggeredSubsystem_FSK_2_T * localDW , ZCE_TriggeredSubsystem_FSK_2_T *
localZCE ) ; void FSK_2_NEGATIVEEdge ( SimStruct * S , real_T rtu_Enable ,
boolean_T rtu_IN , boolean_T rtu_INprevious , B_NEGATIVEEdge_FSK_2_T * localB
, DW_NEGATIVEEdge_FSK_2_T * localDW ) ; void FSK_2_POSITIVEEdge ( SimStruct *
S , real_T rtu_Enable , boolean_T rtu_IN , boolean_T rtu_INprevious ,
B_POSITIVEEdge_FSK_2_T * localB , DW_POSITIVEEdge_FSK_2_T * localDW ) ; void
FSK_2_SampleandHold_k_Init ( SimStruct * S , B_SampleandHold_FSK_2_h_T *
localB , P_SampleandHold_FSK_2_n_T * localP ) ; void FSK_2_SampleandHold_c (
SimStruct * S , boolean_T rtu_Trigger , real_T rtu_In ,
B_SampleandHold_FSK_2_h_T * localB , DW_SampleandHold_FSK_2_n_T * localDW ,
ZCE_SampleandHold_FSK_2_h_T * localZCE ) ; void FSK_2_SampleandHold1_Init (
SimStruct * S , B_SampleandHold1_FSK_2_T * localB , P_SampleandHold1_FSK_2_T
* localP ) ; void FSK_2_SampleandHold1 ( SimStruct * S , real_T rtu_Trigger ,
real_T rtu_In , B_SampleandHold1_FSK_2_T * localB , DW_SampleandHold1_FSK_2_T
* localDW , ZCE_SampleandHold1_FSK_2_T * localZCE ) ;
#endif
