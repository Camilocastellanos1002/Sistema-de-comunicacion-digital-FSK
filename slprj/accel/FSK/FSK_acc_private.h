#ifndef RTW_HEADER_FSK_acc_private_h_
#define RTW_HEADER_FSK_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "FSK_acc.h"
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
#error Code was generated for compiler with different sized uchar/char. \
#endif
#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
#endif
#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
#endif
#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
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
FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T * tailPtr ,
int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * * tBufPtr ,
real_T * * uBufPtr , real_T * * xBufPtr , boolean_T isfixedbuf , boolean_T
istransportdelay , int_T * maxNewBufSzPtr ) ; real_T
FSK_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart , real_T *
tBuf , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx ,
int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) ; void FSK_TriggeredSubsystem_Init (
SimStruct * S , B_TriggeredSubsystem_FSK_T * localB ,
P_TriggeredSubsystem_FSK_T * localP ) ; void FSK_TriggeredSubsystem (
SimStruct * S , boolean_T rtu_Trigger , real_T rtu_In1 ,
B_TriggeredSubsystem_FSK_T * localB , DW_TriggeredSubsystem_FSK_T * localDW ,
ZCE_TriggeredSubsystem_FSK_T * localZCE ) ; void FSK_NEGATIVEEdge ( SimStruct
* S , real_T rtu_Enable , boolean_T rtu_IN , boolean_T rtu_INprevious ,
B_NEGATIVEEdge_FSK_T * localB , DW_NEGATIVEEdge_FSK_T * localDW ) ; void
FSK_POSITIVEEdge ( SimStruct * S , real_T rtu_Enable , boolean_T rtu_IN ,
boolean_T rtu_INprevious , B_POSITIVEEdge_FSK_T * localB ,
DW_POSITIVEEdge_FSK_T * localDW ) ;
#endif