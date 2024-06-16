#include <math.h>
#include "FSK_acc.h"
#include "FSK_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T *
tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * *
tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr , boolean_T isfixedbuf ,
boolean_T istransportdelay , int_T * maxNewBufSzPtr ) { int_T testIdx ; int_T
tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf = * tBufPtr ;
real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if ( istransportdelay ) {
numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail < ( bufSz - 1 ) ) ? (
tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && ! isfixedbuf ) {
int_T j ; real_T * tempT ; real_T * tempU ; real_T * tempX = ( NULL ) ;
real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024 ; if ( newBufSz > *
maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * )
utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL
) ) { return ( false ) ; } tempT = tempU + newBufSz ; if ( istransportdelay )
tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j -
tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay
) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT
[ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ;
if ( istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( *
lastPtr > tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail )
; } * tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr =
newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if ( istransportdelay ) *
xBufPtr = tempX ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
FSK_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart , real_T *
tBuf , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx ,
int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2 , u1 , u2
; if ( ( newIdx == 0 ) && ( oldestIdx == 0 ) && ( tMinusDelay > tStart ) )
return initOutput ; if ( tMinusDelay <= tStart ) return initOutput ; if ( (
tMinusDelay <= tBuf [ oldestIdx ] ) ) { if ( discrete ) { return ( uBuf [
oldestIdx ] ) ; } else { int_T tempIdx = oldestIdx + 1 ; if ( oldestIdx ==
bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [ oldestIdx ] ; t2 = tBuf [ tempIdx ] ;
u1 = uBuf [ oldestIdx ] ; u2 = uBuf [ tempIdx ] ; if ( t2 == t1 ) { if (
tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else { real_T f1 =
( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout = f1 * u1 +
f2 * u2 ; } return yout ; } } if ( minorStepAndTAtLastMajorOutput ) { if (
newIdx != 0 ) { if ( * lastIdx == newIdx ) { ( * lastIdx ) -- ; } newIdx -- ;
} else { if ( * lastIdx == newIdx ) { * lastIdx = bufSz - 1 ; } newIdx =
bufSz - 1 ; } } i = * lastIdx ; if ( tBuf [ i ] < tMinusDelay ) { while (
tBuf [ i ] < tMinusDelay ) { if ( i == newIdx ) break ; i = ( i < ( bufSz - 1
) ) ? ( i + 1 ) : 0 ; } } else { while ( tBuf [ i ] >= tMinusDelay ) { i = (
i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0
; } * lastIdx = i ; if ( discrete ) { double tempEps = ( DBL_EPSILON ) *
128.0 ; double localEps = tempEps * muDoubleScalarAbs ( tBuf [ i ] ) ; if (
tempEps > localEps ) { localEps = tempEps ; } localEps = localEps / 2.0 ; if
( tMinusDelay >= ( tBuf [ i ] - localEps ) ) { yout = uBuf [ i ] ; } else {
if ( i == 0 ) { yout = uBuf [ bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ;
} } } else { if ( i == 0 ) { t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1
] ; } else { t1 = tBuf [ i - 1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ;
u2 = uBuf [ i ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; }
else { yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 )
; real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } } return ( yout ) ; }
void rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T blkIdx , char_T
* * path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void
rt_ssSet_slErrMsg ( SimStruct * S , void * diag ) { if ( !
_ssIsErrorStatusAslErrMsg ( S ) ) { _ssSet_slErrMsg ( S , diag ) ; } else {
_ssDiscardDiagnostic ( S , diag ) ; } } void rt_ssReportDiagnosticAsWarning (
SimStruct * S , void * diag ) { _ssReportDiagnosticAsWarning ( S , diag ) ; }
void FSK_TriggeredSubsystem_Init ( SimStruct * S , B_TriggeredSubsystem_FSK_T
* localB , P_TriggeredSubsystem_FSK_T * localP ) { localB -> B_3_0_0 = localP
-> P_0 ; } void FSK_TriggeredSubsystem ( SimStruct * S , boolean_T
rtu_Trigger , real_T rtu_In1 , B_TriggeredSubsystem_FSK_T * localB ,
DW_TriggeredSubsystem_FSK_T * localDW , ZCE_TriggeredSubsystem_FSK_T *
localZCE ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( rtu_Trigger && (
localZCE -> TriggeredSubsystem_Trig_ZCE != POS_ZCSIG ) ) { localB -> B_3_0_0
= rtu_In1 ; localDW -> TriggeredSubsystem_SubsysRanBC = 4 ; } localZCE ->
TriggeredSubsystem_Trig_ZCE = rtu_Trigger ; } } void
FSK_TriggeredSubsystem_Term ( SimStruct * const S ) { } void FSK_NEGATIVEEdge
( SimStruct * S , real_T rtu_Enable , boolean_T rtu_IN , boolean_T
rtu_INprevious , B_NEGATIVEEdge_FSK_T * localB , DW_NEGATIVEEdge_FSK_T *
localDW ) { if ( rtu_Enable > 0.0 ) { localB -> B_4_0_0 = ( ( int32_T )
rtu_INprevious > ( int32_T ) rtu_IN ) ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
srUpdateBC ( localDW -> NEGATIVEEdge_SubsysRanBC ) ; } } } void
FSK_NEGATIVEEdge_Term ( SimStruct * const S ) { } void FSK_POSITIVEEdge (
SimStruct * S , real_T rtu_Enable , boolean_T rtu_IN , boolean_T
rtu_INprevious , B_POSITIVEEdge_FSK_T * localB , DW_POSITIVEEdge_FSK_T *
localDW ) { if ( rtu_Enable > 0.0 ) { localB -> B_5_0_0 = ( ( int32_T )
rtu_INprevious < ( int32_T ) rtu_IN ) ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
srUpdateBC ( localDW -> POSITIVEEdge_SubsysRanBC ) ; } } } void
FSK_POSITIVEEdge_Term ( SimStruct * const S ) { } real_T
rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { uint32_T lo ; uint32_T hi ; lo
= * u % 127773U * 16807U ; hi = * u / 127773U * 2836U ; if ( lo < hi ) { * u
= 2147483647U - ( hi - lo ) ; } else { * u = lo - hi ; } return ( real_T ) *
u * 4.6566128752457969E-10 ; } real_T rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T *
u ) { real_T y ; real_T sr ; real_T si ; do { sr = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = sr * sr + si * si ; } while (
si > 1.0 ) ; y = muDoubleScalarSqrt ( - 2.0 * muDoubleScalarLog ( si ) / si )
* sr ; return y ; } static void mdlOutputs ( SimStruct * S , int_T tid ) {
real_T B_14_17_0 ; real_T B_14_20_0 ; real_T B_14_35_0 ; real_T B_14_63_0 ;
real_T B_14_85_0 ; real_T B_14_89_0 ; real_T B_14_91_0 ; real_T B_14_94_0 ;
real_T B_14_114_0 ; real_T B_14_121_0 ; boolean_T B_14_69_0 ; boolean_T
B_14_72_0 ; boolean_T B_14_138_0 ; boolean_T B_14_141_0 ; boolean_T
B_14_156_0 ; boolean_T B_14_159_0 ; ZCEventType zcEvent ; real_T
rtb_B_14_15_0 ; boolean_T rtb_B_14_8_0 ; boolean_T rtb_B_14_154_0 ; boolean_T
rtb_B_14_136_0 ; boolean_T rtb_B_14_38_0 ; real_T rtb_B_14_62_0 ; real_T
rtb_B_14_60_0 ; real_T rtb_B_14_58_0 ; real_T rtb_B_14_56_0 ; real_T
rtb_B_14_54_0 ; real_T rtb_B_14_52_0 ; real_T rtb_B_14_50_0 ; real_T
rtb_B_14_48_0 ; real_T rtb_B_14_46_0 ; uint32_T numCycles ; real_T ratio ;
int32_T isHit ; B_FSK_T * _rtB ; P_FSK_T * _rtP ; X_FSK_T * _rtX ;
PrevZCX_FSK_T * _rtZCE ; DW_FSK_T * _rtDW ; _rtDW = ( ( DW_FSK_T * )
ssGetRootDWork ( S ) ) ; _rtZCE = ( ( PrevZCX_FSK_T * ) _ssGetPrevZCSigState
( S ) ) ; _rtX = ( ( X_FSK_T * ) ssGetContStates ( S ) ) ; _rtP = ( ( P_FSK_T
* ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_FSK_T * ) _ssGetModelBlockIO ( S ) )
; _rtB -> B_14_1_0 = _rtX -> Integrator_CSTATE * _rtB -> B_14_1_0_m ; _rtB ->
B_14_4_0 = muDoubleScalarCos ( _rtX -> ModuloIntegrator_CSTATE *
6.2831853071795862 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { if ( _rtB -> B_14_4_0 > 0.0 ) { _rtDW -> Sign_MODE = 1 ; } else if ( _rtB
-> B_14_4_0 < 0.0 ) { _rtDW -> Sign_MODE = - 1 ; } else { _rtDW -> Sign_MODE
= 0 ; } if ( _rtDW -> Sign_MODE >= _rtP -> P_7 ) { _rtB -> B_14_6_0 = _rtB ->
B_14_37_0 ; } else { _rtB -> B_14_6_0 = _rtB -> B_14_38_0 ; } } if (
ssIsMajorTimeStep ( S ) != 0 ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
_rtZCE -> Integrator_Reset_ZCE , _rtB -> B_14_6_0 ) ; if ( zcEvent !=
NO_ZCEVENT ) { _rtX -> Integrator_CSTATE_d = _rtP -> P_8 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } } _rtB -> B_14_7_0 =
_rtX -> Integrator_CSTATE_d ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode =
( _rtB -> B_14_7_0 >= _rtB -> B_14_2_0 ) ; } rtb_B_14_8_0 = _rtDW ->
Compare_Mode ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_9 ; _rtB -> B_14_9_0
= FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer ,
_rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW ->
TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail , _rtDW ->
TransportDelay_IWORK . Head , _rtP -> P_10 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && (
ssIsMajorTimeStep ( S ) != 0 ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
_rtZCE -> SampleandHold_Trig_ZCE_k , _rtB -> B_14_9_0 ) ; if ( zcEvent !=
NO_ZCEVENT ) { _rtB -> B_2_0_0 = rtb_B_14_8_0 ; _rtDW ->
SampleandHold_SubsysRanBC_c = 4 ; } } ssCallAccelRunBlock ( S , 14 , 11 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_14_12_0 = 0.0 ; _rtB -> B_14_12_0 += _rtP
-> P_13 * _rtX -> Filtro_CSTATE [ 1 ] ; isHit = ssIsSampleHit ( S , 3 , 0 ) ;
if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 14 , 13 , SS_CALL_MDL_OUTPUTS )
; } rtb_B_14_15_0 = muDoubleScalarCos ( _rtX -> ModuloIntegrator_CSTATE_j *
6.2831853071795862 ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_h . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_18 ; if ( _rtP ->
P_18 == 0.0 ) B_14_17_0 = _rtB -> B_14_13_0 ; else B_14_17_0 =
FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer ,
_rtDW -> TransportDelay_IWORK_i . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_i . Last , _rtDW -> TransportDelay_IWORK_i . Tail ,
_rtDW -> TransportDelay_IWORK_i . Head , _rtP -> P_19 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_14_19_0 = _rtP -> P_20 * B_14_17_0 + _rtB -> B_14_0_0 ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_c . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_21 ; B_14_20_0 =
FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer ,
_rtDW -> TransportDelay_IWORK_e . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_e . Last , _rtDW -> TransportDelay_IWORK_e . Tail ,
_rtDW -> TransportDelay_IWORK_e . Head , _rtP -> P_22 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_14_24_0 = _rtP -> P_26 * _rtDW -> NextOutput + _rtP -> P_27 ; _rtB ->
B_14_25_0 = _rtB -> B_14_24_0 ; } _rtB -> B_14_26_0 = B_14_20_0 + _rtB ->
B_14_25_0 ; _rtB -> B_14_27_0 = _rtP -> P_29 * rtb_B_14_15_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c4 . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c4
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_30 ; _rtB -> B_14_28_0 = FSK_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_ic
. CircularBufSize , & _rtDW -> TransportDelay_IWORK_ic . Last , _rtDW ->
TransportDelay_IWORK_ic . Tail , _rtDW -> TransportDelay_IWORK_ic . Head ,
_rtP -> P_31 , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } ssCallAccelRunBlock ( S
, 14 , 29 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_14_31_0 = ( int8_T ) ( ( int8_T
) ( _rtB -> B_14_28_0 != 0.0 ) ^ ( int8_T ) _rtB -> B_2_0_0 ) ; isHit =
ssIsSampleHit ( S , 4 , 0 ) ; if ( isHit != 0 ) { rtb_B_14_15_0 =
ssGetTaskTime ( S , 4 ) ; if ( ssGetTNextWasAdjusted ( S , 4 ) != 0 ) { _rtDW
-> nextTime = _ssGetVarNextHitTime ( S , 0 ) ; } if ( _rtDW -> justEnabled !=
0 ) { _rtDW -> justEnabled = 0 ; if ( rtb_B_14_15_0 >= _rtP -> P_35 ) { ratio
= ( rtb_B_14_15_0 - _rtP -> P_35 ) / _rtP -> P_33 ; numCycles = ( uint32_T )
muDoubleScalarFloor ( ratio ) ; if ( muDoubleScalarAbs ( ( real_T ) (
numCycles + 1U ) - ratio ) < DBL_EPSILON * ratio ) { numCycles ++ ; } _rtDW
-> numCompleteCycles = numCycles ; ratio = ( ( real_T ) numCycles * _rtP ->
P_33 + _rtP -> P_35 ) + _rtP -> P_34 * _rtP -> P_33 / 100.0 ; if (
rtb_B_14_15_0 < ratio ) { _rtDW -> currentValue = 1 ; _rtDW -> nextTime =
ratio ; } else { _rtDW -> currentValue = 0 ; _rtDW -> nextTime = ( real_T ) (
numCycles + 1U ) * _rtP -> P_33 + _rtP -> P_35 ; } } else { _rtDW ->
numCompleteCycles = _rtP -> P_35 != 0.0 ? - 1 : 0 ; _rtDW -> currentValue = 0
; _rtDW -> nextTime = _rtP -> P_35 ; } } else { if ( _rtDW -> nextTime <=
rtb_B_14_15_0 ) { if ( _rtDW -> currentValue == 1 ) { _rtDW -> currentValue =
0 ; _rtDW -> nextTime = ( real_T ) ( _rtDW -> numCompleteCycles + 1LL ) *
_rtP -> P_33 + _rtP -> P_35 ; } else { _rtDW -> numCompleteCycles ++ ; _rtDW
-> currentValue = 1 ; _rtDW -> nextTime = ( _rtP -> P_34 * _rtP -> P_33 *
0.01 + ( real_T ) _rtDW -> numCompleteCycles * _rtP -> P_33 ) + _rtP -> P_35
; } } } _ssSetVarNextHitTime ( S , 0 , _rtDW -> nextTime ) ; if ( _rtDW ->
currentValue == 1 ) { _rtB -> B_14_32_0 = _rtP -> P_32 ; } else { _rtB ->
B_14_32_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0
) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { zcEvent = rt_ZCFcn (
RISING_ZERO_CROSSING , & _rtZCE -> MuestreoyRetencion_Trig_ZCE , _rtB ->
B_14_32_0 ) ; if ( zcEvent != NO_ZCEVENT ) { _rtB -> B_0_0_0 = _rtB ->
B_14_31_0 ; _rtDW -> MuestreoyRetencion_SubsysRanBC = 4 ; } } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay12_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay12_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_36 ; if ( _rtP -> P_36 == 0.0 ) B_14_35_0 = _rtB ->
B_14_9_0 ; else B_14_35_0 = FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0
, * tBuffer , * uBuffer , _rtDW -> TransportDelay12_IWORK . CircularBufSize ,
& _rtDW -> TransportDelay12_IWORK . Last , _rtDW -> TransportDelay12_IWORK .
Tail , _rtDW -> TransportDelay12_IWORK . Head , _rtP -> P_37 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } _rtB -> B_14_36_0 = ssGetT ( S ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_14_38_0 = ! _rtDW ->
Memory_PreviousInput ; if ( _rtB -> B_2_0_0 ) { _rtB -> B_14_39_0 = _rtB ->
B_14_23_0 ; } else { _rtB -> B_14_39_0 = _rtB -> B_14_21_0 ; } _rtB ->
B_14_40_0 = _rtB -> B_14_39_0 * _rtB -> B_14_11_0 ; } { real_T * * uBuffer =
( real_T * * ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs
[ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP
-> P_38 ; _rtB -> B_14_41_0 = FSK_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay2_IWORK .
CircularBufSize , & _rtDW -> TransportDelay2_IWORK . Last , _rtDW ->
TransportDelay2_IWORK . Tail , _rtDW -> TransportDelay2_IWORK . Head , _rtP
-> P_39 , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } rtb_B_14_15_0 = _rtB ->
B_14_41_0 * _rtB -> B_14_22_0 ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime
= ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_40 ; _rtB ->
B_14_43_0 = FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay1_IWORK . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK . Last , _rtDW -> TransportDelay1_IWORK . Tail , _rtDW
-> TransportDelay1_IWORK . Head , _rtP -> P_41 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } ratio = _rtB -> B_14_43_0 * _rtB -> B_14_24_0_g ; { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay4_PWORK . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay4_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_42 ; _rtB -> B_14_45_0 = FSK_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay4_IWORK .
CircularBufSize , & _rtDW -> TransportDelay4_IWORK . Last , _rtDW ->
TransportDelay4_IWORK . Tail , _rtDW -> TransportDelay4_IWORK . Head , _rtP
-> P_43 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } rtb_B_14_46_0 = _rtB ->
B_14_45_0 * _rtB -> B_14_25_0_g ; { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay3_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay3_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_44 ; _rtB
-> B_14_47_0 = FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , _rtDW -> TransportDelay3_IWORK . CircularBufSize , & _rtDW ->
TransportDelay3_IWORK . Last , _rtDW -> TransportDelay3_IWORK . Tail , _rtDW
-> TransportDelay3_IWORK . Head , _rtP -> P_45 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_14_48_0 = _rtB -> B_14_47_0 * _rtB -> B_14_26_0_m ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay6_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay6_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_46 ; _rtB -> B_14_49_0 = FSK_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay6_IWORK .
CircularBufSize , & _rtDW -> TransportDelay6_IWORK . Last , _rtDW ->
TransportDelay6_IWORK . Tail , _rtDW -> TransportDelay6_IWORK . Head , _rtP
-> P_47 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } rtb_B_14_50_0 = _rtB ->
B_14_49_0 * _rtB -> B_14_27_0_n ; { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay5_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay5_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_48 ; _rtB
-> B_14_51_0 = FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , _rtDW -> TransportDelay5_IWORK . CircularBufSize , & _rtDW ->
TransportDelay5_IWORK . Last , _rtDW -> TransportDelay5_IWORK . Tail , _rtDW
-> TransportDelay5_IWORK . Head , _rtP -> P_49 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_14_52_0 = _rtB -> B_14_51_0 * _rtB -> B_14_28_0_p ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay8_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay8_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_50 ; _rtB -> B_14_53_0 = FSK_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay8_IWORK .
CircularBufSize , & _rtDW -> TransportDelay8_IWORK . Last , _rtDW ->
TransportDelay8_IWORK . Tail , _rtDW -> TransportDelay8_IWORK . Head , _rtP
-> P_51 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } rtb_B_14_54_0 = _rtB ->
B_14_53_0 * _rtB -> B_14_29_0 ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay7_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay7_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime
= ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_52 ; _rtB ->
B_14_55_0 = FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay7_IWORK . CircularBufSize , & _rtDW ->
TransportDelay7_IWORK . Last , _rtDW -> TransportDelay7_IWORK . Tail , _rtDW
-> TransportDelay7_IWORK . Head , _rtP -> P_53 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_14_56_0 = _rtB -> B_14_55_0 * _rtB -> B_14_30_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay9_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay9_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_54 ; _rtB -> B_14_57_0 = FSK_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay9_IWORK .
CircularBufSize , & _rtDW -> TransportDelay9_IWORK . Last , _rtDW ->
TransportDelay9_IWORK . Tail , _rtDW -> TransportDelay9_IWORK . Head , _rtP
-> P_55 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } rtb_B_14_58_0 = _rtB ->
B_14_57_0 * _rtB -> B_14_12_0_p ; { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay11_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay11_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_56 ; _rtB
-> B_14_59_0 = FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , _rtDW -> TransportDelay11_IWORK . CircularBufSize , & _rtDW ->
TransportDelay11_IWORK . Last , _rtDW -> TransportDelay11_IWORK . Tail ,
_rtDW -> TransportDelay11_IWORK . Head , _rtP -> P_57 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_14_60_0 = _rtB -> B_14_59_0 * _rtB -> B_14_13_0_c ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay10_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay10_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_58 ; _rtB -> B_14_61_0 = FSK_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay10_IWORK .
CircularBufSize , & _rtDW -> TransportDelay10_IWORK . Last , _rtDW ->
TransportDelay10_IWORK . Tail , _rtDW -> TransportDelay10_IWORK . Head , _rtP
-> P_59 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } rtb_B_14_62_0 = _rtB ->
B_14_61_0 * _rtB -> B_14_14_0 ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay13_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay13_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_60 ;
B_14_63_0 = FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay13_IWORK . CircularBufSize , & _rtDW ->
TransportDelay13_IWORK . Last , _rtDW -> TransportDelay13_IWORK . Tail ,
_rtDW -> TransportDelay13_IWORK . Head , _rtP -> P_61 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_14_65_0 = ( ( ( ( ( ( ( ( ( ( ( _rtB -> B_14_40_0 +
rtb_B_14_15_0 ) + ratio ) + rtb_B_14_46_0 ) + rtb_B_14_48_0 ) + rtb_B_14_50_0
) + rtb_B_14_52_0 ) + rtb_B_14_54_0 ) + rtb_B_14_56_0 ) + rtb_B_14_58_0 ) +
rtb_B_14_60_0 ) + rtb_B_14_62_0 ) + B_14_63_0 * _rtB -> B_14_15_0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Switch_Mode = ( _rtB -> B_14_65_0 >
_rtP -> P_62 ) ; _rtDW -> Switch1_Mode = ( _rtB -> B_14_65_0 > _rtP -> P_63 )
; } if ( _rtDW -> Switch_Mode ) { rtb_B_14_15_0 = _rtB -> B_14_17_0 ; } else
{ rtb_B_14_15_0 = _rtB -> B_14_16_0 ; } if ( _rtDW -> Switch1_Mode ) { ratio
= _rtB -> B_14_20_0 ; } else { ratio = _rtB -> B_14_19_0_f ; } _rtB ->
B_14_68_0 = ( ( rtb_B_14_15_0 != 0.0 ) || ( ratio != 0.0 ) ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { B_14_69_0 = _rtDW ->
Memory_PreviousInput_f ; FSK_POSITIVEEdge ( S , _rtB -> B_14_36_0_j [ 0 ] ,
_rtB -> B_14_68_0 , B_14_69_0 , & _rtB -> POSITIVEEdge , & _rtDW ->
POSITIVEEdge ) ; FSK_NEGATIVEEdge ( S , _rtB -> B_14_36_0_j [ 1 ] , _rtB ->
B_14_68_0 , B_14_69_0 , & _rtB -> NEGATIVEEdge , & _rtDW -> NEGATIVEEdge ) ;
B_14_72_0 = ( _rtB -> POSITIVEEdge . B_5_0_0 || _rtB -> NEGATIVEEdge .
B_4_0_0 ) ; _rtB -> B_14_73_0 = ( rtb_B_14_38_0 && B_14_72_0 ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_14_75_0 = _rtDW
-> ICic_PreviousInput ; } if ( _rtB -> B_14_73_0 ) { _rtB -> B_14_76_0 = _rtB
-> B_14_36_0 ; } else { _rtB -> B_14_76_0 = _rtB -> B_14_75_0 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_14_77_0 = _rtP ->
P_65 ; } _rtB -> B_14_78_0 = _rtB -> B_14_76_0 + _rtB -> B_14_77_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> RelationalOperator_Mode = ( _rtB -> B_14_78_0 > _rtB ->
B_14_36_0 ) ; } _rtB -> B_14_79_0 = _rtDW -> RelationalOperator_Mode ; } if (
_rtB -> B_14_79_0 ) { _rtB -> B_14_80_0 = B_14_35_0 ; } else { _rtB ->
B_14_80_0 = _rtB -> B_14_18_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
( isHit != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { zcEvent = rt_ZCFcn (
ANY_ZERO_CROSSING , & _rtZCE -> Mensajerecibido_Trig_ZCE , _rtB -> B_14_80_0
) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 1 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Mensajerecibido_SubsysRanBC = 4 ; } } _rtB
-> B_14_82_0 = 0.0 ; _rtB -> B_14_82_0 += _rtP -> P_68 * _rtX ->
Filtro_CSTATE_j [ 5 ] ; ssCallAccelRunBlock ( S , 14 , 83 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 14 , 84 ,
SS_CALL_MDL_OUTPUTS ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_o . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_o . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_70 ; B_14_85_0 =
FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer ,
_rtDW -> TransportDelay_IWORK_g . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_g . Last , _rtDW -> TransportDelay_IWORK_g . Tail ,
_rtDW -> TransportDelay_IWORK_g . Head , _rtP -> P_71 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_14_87_0 = ( B_14_85_0 + _rtB -> B_14_12_0 ) * _rtB ->
B_14_3_0 ; ssCallAccelRunBlock ( S , 14 , 88 , SS_CALL_MDL_OUTPUTS ) ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_j .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_j . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_72 ; B_14_89_0 =
FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer ,
_rtDW -> TransportDelay_IWORK_ir . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_ir . Last , _rtDW -> TransportDelay_IWORK_ir . Tail ,
_rtDW -> TransportDelay_IWORK_ir . Head , _rtP -> P_73 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_14_90_0 = _rtP -> P_74 * B_14_89_0 ; { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay1_PWORK_j . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_j .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_75 ; B_14_91_0 = FSK_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay1_IWORK_d
. CircularBufSize , & _rtDW -> TransportDelay1_IWORK_d . Last , _rtDW ->
TransportDelay1_IWORK_d . Tail , _rtDW -> TransportDelay1_IWORK_d . Head ,
_rtP -> P_76 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_14_92_0 =
_rtP -> P_77 * B_14_91_0 ; ssCallAccelRunBlock ( S , 14 , 93 ,
SS_CALL_MDL_OUTPUTS ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK_o . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay1_PWORK_o . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_78 ;
B_14_94_0 = FSK_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay1_IWORK_g . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_g . Last , _rtDW -> TransportDelay1_IWORK_g . Tail ,
_rtDW -> TransportDelay1_IWORK_g . Head , _rtP -> P_79 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_14_100_0 = _rtP -> P_83 * _rtDW -> NextOutput_m + _rtP -> P_84 ; _rtB ->
B_14_101_0 = _rtB -> B_14_100_0 ; } rtb_B_14_15_0 = _rtB -> B_14_87_0 + _rtB
-> B_14_101_0 ; _rtB -> B_14_103_0 = rtb_B_14_15_0 * _rtB -> B_14_90_0 ;
ratio = ( B_14_94_0 + _rtB -> B_14_12_0 ) * _rtB -> B_14_3_0 + _rtB ->
B_14_101_0 ; _rtB -> B_14_105_0 = _rtB -> B_14_92_0 * ratio ; _rtB ->
B_14_106_0 = _rtB -> B_14_103_0 - _rtB -> B_14_105_0 ; ssCallAccelRunBlock (
S , 14 , 107 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_14_110_0 = muDoubleScalarCos
( _rtX -> ModuloIntegrator_CSTATE_b * 6.2831853071795862 ) ; rtb_B_14_15_0 =
rtb_B_14_15_0 * _rtB -> B_14_4_0_c * _rtB -> B_14_110_0 ; B_14_114_0 = _rtB
-> B_14_5_0 * rtb_B_14_15_0 + _rtX -> Integrator_CSTATE_p ; _rtB ->
B_14_117_0 = muDoubleScalarCos ( _rtX -> ModuloIntegrator_CSTATE_j0 *
6.2831853071795862 ) ; ratio *= _rtB -> B_14_117_0 * _rtB -> B_14_4_0_c ;
B_14_121_0 = _rtB -> B_14_7_0_c * ratio + _rtX -> Integrator1_CSTATE ; _rtB
-> B_14_123_0 = _rtP -> P_94 * B_14_114_0 + _rtB -> B_14_9_0_b ; _rtB ->
B_14_125_0 = _rtP -> P_95 * B_14_121_0 + _rtB -> B_14_10_0 ; _rtB ->
B_14_126_0 = rtb_B_14_15_0 * _rtB -> B_14_6_0_k ; _rtB -> B_14_127_0 = ratio
* _rtB -> B_14_8_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ if ( _rtB -> B_14_82_0 > 0.0 ) { _rtDW -> Sign3_MODE = 1 ; } else if ( _rtB
-> B_14_82_0 < 0.0 ) { _rtDW -> Sign3_MODE = - 1 ; } else { _rtDW ->
Sign3_MODE = 0 ; } _rtB -> B_14_128_0 = _rtDW -> Sign3_MODE ; } _rtB ->
B_14_129_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { FSK_TriggeredSubsystem ( S , B_14_72_0 , _rtB -> B_14_129_0 , & _rtB
-> TriggeredSubsystem , & _rtDW -> TriggeredSubsystem , & _rtZCE ->
TriggeredSubsystem ) ; _rtB -> B_14_131_0 = _rtB -> TriggeredSubsystem .
B_3_0_0 + _rtB -> B_14_31_0_l ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW
-> RelationalOperator_Mode_a = ( _rtB -> B_14_131_0 > _rtB -> B_14_129_0 ) ;
} } if ( ssIsMajorTimeStep ( S ) != 0 ) { zcEvent = rt_ZCFcn (
ANY_ZERO_CROSSING , & _rtZCE -> Integrator_Reset_ZCE_n , _rtB -> B_14_6_0 ) ;
if ( zcEvent != NO_ZCEVENT ) { _rtX -> Integrator_CSTATE_p0 = _rtP -> P_96 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } } _rtB -> B_14_133_0 =
_rtX -> Integrator_CSTATE_p0 ; _rtB -> B_14_134_0 = ssGetT ( S ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_14_136_0 = ! _rtDW ->
Memory_PreviousInput_b ; } _rtB -> B_14_137_0 = ( _rtB -> B_14_6_0 != 0.0 ) ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { B_14_138_0 = _rtDW
-> Memory_PreviousInput_p ; FSK_POSITIVEEdge ( S , _rtB -> B_14_45_0_l [ 0 ]
, _rtB -> B_14_137_0 , B_14_138_0 , & _rtB -> POSITIVEEdge_e , & _rtDW ->
POSITIVEEdge_e ) ; FSK_NEGATIVEEdge ( S , _rtB -> B_14_45_0_l [ 1 ] , _rtB ->
B_14_137_0 , B_14_138_0 , & _rtB -> NEGATIVEEdge_c , & _rtDW ->
NEGATIVEEdge_c ) ; B_14_141_0 = ( _rtB -> POSITIVEEdge_e . B_5_0_0 || _rtB ->
NEGATIVEEdge_c . B_4_0_0 ) ; _rtB -> B_14_142_0 = ( rtb_B_14_136_0 &&
B_14_141_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_14_144_0 = _rtDW -> ICic_PreviousInput_b ; } if ( _rtB ->
B_14_142_0 ) { _rtB -> B_14_145_0 = _rtB -> B_14_134_0 ; } else { _rtB ->
B_14_145_0 = _rtB -> B_14_144_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { _rtB -> B_14_146_0 = _rtP -> P_98 ; } _rtB -> B_14_147_0 =
_rtB -> B_14_145_0 + _rtB -> B_14_146_0 ; isHit = ssIsSampleHit ( S , 1 , 0 )
; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode_m = ( _rtB -> B_14_147_0 > _rtB -> B_14_134_0 ) ; }
_rtB -> B_14_148_0 = _rtDW -> RelationalOperator_Mode_m ; } _rtB ->
B_14_149_0 = _rtB -> B_14_148_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( ( ! _rtB ->
B_14_149_0 ) && ( _rtZCE -> SampleandHold_Trig_ZCE != ZERO_ZCSIG ) ) { _rtB
-> B_12_0_0 = _rtB -> B_14_133_0 ; _rtDW -> SampleandHold_SubsysRanBC = 4 ; }
_rtZCE -> SampleandHold_Trig_ZCE = _rtB -> B_14_149_0 ; } _rtB -> B_14_151_0
= muDoubleScalarAbs ( _rtB -> B_12_0_0 ) ; } _rtB -> B_14_152_0 = ssGetT ( S
) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_14_154_0
= ! _rtDW -> Memory_PreviousInput_k ; } _rtB -> B_14_155_0 = ( _rtB ->
B_14_6_0 != 0.0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
B_14_156_0 = _rtDW -> Memory_PreviousInput_ke ; FSK_POSITIVEEdge ( S , _rtB
-> B_14_51_0_d [ 0 ] , _rtB -> B_14_155_0 , B_14_156_0 , & _rtB ->
POSITIVEEdge_a , & _rtDW -> POSITIVEEdge_a ) ; FSK_NEGATIVEEdge ( S , _rtB ->
B_14_51_0_d [ 1 ] , _rtB -> B_14_155_0 , B_14_156_0 , & _rtB ->
NEGATIVEEdge_o , & _rtDW -> NEGATIVEEdge_o ) ; B_14_159_0 = ( _rtB ->
POSITIVEEdge_a . B_5_0_0 || _rtB -> NEGATIVEEdge_o . B_4_0_0 ) ; _rtB ->
B_14_160_0 = ( rtb_B_14_154_0 && B_14_159_0 ) ; } isHit = ssIsSampleHit ( S ,
1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_14_162_0 = _rtDW ->
ICic_PreviousInput_a ; } if ( _rtB -> B_14_160_0 ) { _rtB -> B_14_163_0 =
_rtB -> B_14_152_0 ; } else { _rtB -> B_14_163_0 = _rtB -> B_14_162_0 ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_14_164_0
= _rtP -> P_100 ; } _rtB -> B_14_165_0 = _rtB -> B_14_163_0 + _rtB ->
B_14_164_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode_i = ( _rtB
-> B_14_165_0 > _rtB -> B_14_152_0 ) ; } _rtB -> B_14_166_0 = _rtDW ->
RelationalOperator_Mode_i ; } if ( ssIsMajorTimeStep ( S ) != 0 ) {
rtb_B_14_154_0 = ( ( ! _rtB -> B_14_166_0 ) && ( _rtZCE ->
Integrator1_Reset_ZCE != ZERO_ZCSIG ) ) ; _rtZCE -> Integrator1_Reset_ZCE =
_rtB -> B_14_166_0 ; if ( rtb_B_14_154_0 ) { _rtX -> Integrator1_CSTATE_a =
_rtP -> P_101 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } } _rtB
-> B_14_167_0 = _rtX -> Integrator1_CSTATE_a ; if ( ssIsMajorTimeStep ( S )
!= 0 ) { _rtDW -> Abs1_MODE = ( _rtB -> B_14_167_0 >= 0.0 ) ; } _rtB ->
B_14_169_0 = _rtB -> B_14_151_0 - ( _rtDW -> Abs1_MODE > 0 ? _rtB ->
B_14_167_0 : - _rtB -> B_14_167_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { zcEvent = rt_ZCFcn
( ANY_ZERO_CROSSING , & _rtZCE -> SampleandHold1_Trig_ZCE , _rtB -> B_14_6_0
) ; if ( zcEvent != NO_ZCEVENT ) { _rtB -> B_13_0_0 = _rtB -> B_14_169_0 ;
_rtDW -> SampleandHold1_SubsysRanBC = 4 ; } } ssCallAccelRunBlock ( S , 14 ,
171 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_14_173_0 = _rtP -> P_102 * _rtB ->
B_13_0_0 + _rtB -> B_14_39_0_d ; } _rtB -> B_14_174_0 = ssGetT ( S ) ; isHit
= ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { FSK_TriggeredSubsystem (
S , B_14_141_0 , _rtB -> B_14_174_0 , & _rtB -> TriggeredSubsystem_d , &
_rtDW -> TriggeredSubsystem_d , & _rtZCE -> TriggeredSubsystem_d ) ; _rtB ->
B_14_176_0 = _rtB -> TriggeredSubsystem_d . B_3_0_0 + _rtB -> B_14_40_0_g ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode_e = (
_rtB -> B_14_176_0 > _rtB -> B_14_174_0 ) ; } } _rtB -> B_14_178_0 = ssGetT (
S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
FSK_TriggeredSubsystem ( S , B_14_159_0 , _rtB -> B_14_178_0 , & _rtB ->
TriggeredSubsystem_g , & _rtDW -> TriggeredSubsystem_g , & _rtZCE ->
TriggeredSubsystem_g ) ; _rtB -> B_14_180_0 = _rtB -> TriggeredSubsystem_g .
B_3_0_0 + _rtB -> B_14_46_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode_g = ( _rtB -> B_14_180_0 > _rtB -> B_14_178_0 ) ; } }
UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID5 ( SimStruct * S ,
int_T tid ) { B_FSK_T * _rtB ; P_FSK_T * _rtP ; _rtP = ( ( P_FSK_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_FSK_T * ) _ssGetModelBlockIO ( S ) ) ;
_rtB -> B_14_0_0 = _rtP -> P_103 ; _rtB -> B_14_1_0_m = _rtP -> P_104 ; _rtB
-> B_14_2_0 = _rtP -> P_105 ; _rtB -> B_14_3_0 = _rtP -> P_106 ; _rtB ->
B_14_4_0_c = _rtP -> P_107 ; _rtB -> B_14_5_0 = _rtP -> P_108 ; _rtB ->
B_14_6_0_k = _rtP -> P_109 ; _rtB -> B_14_7_0_c = _rtP -> P_110 ; _rtB ->
B_14_8_0 = _rtP -> P_111 ; _rtB -> B_14_9_0_b = _rtP -> P_112 ; _rtB ->
B_14_10_0 = _rtP -> P_113 ; _rtB -> B_14_11_0 = _rtP -> P_114 ; _rtB ->
B_14_12_0_p = _rtP -> P_115 ; _rtB -> B_14_13_0_c = _rtP -> P_116 ; _rtB ->
B_14_14_0 = _rtP -> P_117 ; _rtB -> B_14_15_0 = _rtP -> P_118 ; _rtB ->
B_14_16_0 = _rtP -> P_119 ; _rtB -> B_14_17_0 = _rtP -> P_120 ; _rtB ->
B_14_18_0 = _rtP -> P_121 ; _rtB -> B_14_19_0_f = _rtP -> P_122 ; _rtB ->
B_14_20_0 = _rtP -> P_123 ; _rtB -> B_14_21_0 = _rtP -> P_124 ; _rtB ->
B_14_22_0 = _rtP -> P_125 ; _rtB -> B_14_23_0 = _rtP -> P_126 ; _rtB ->
B_14_24_0_g = _rtP -> P_127 ; _rtB -> B_14_25_0_g = _rtP -> P_128 ; _rtB ->
B_14_26_0_m = _rtP -> P_129 ; _rtB -> B_14_27_0_n = _rtP -> P_130 ; _rtB ->
B_14_28_0_p = _rtP -> P_131 ; _rtB -> B_14_29_0 = _rtP -> P_132 ; _rtB ->
B_14_30_0 = _rtP -> P_133 ; _rtB -> B_14_31_0_l = _rtP -> P_134 ; switch ( (
int32_T ) _rtP -> P_135 ) { case 1 : _rtB -> B_14_36_0_j [ 0 ] = _rtP ->
P_136 [ 0 ] ; _rtB -> B_14_36_0_j [ 1 ] = _rtP -> P_136 [ 1 ] ; break ; case
2 : _rtB -> B_14_36_0_j [ 0 ] = _rtP -> P_137 [ 0 ] ; _rtB -> B_14_36_0_j [ 1
] = _rtP -> P_137 [ 1 ] ; break ; default : _rtB -> B_14_36_0_j [ 0 ] = _rtP
-> P_138 [ 0 ] ; _rtB -> B_14_36_0_j [ 1 ] = _rtP -> P_138 [ 1 ] ; break ; }
_rtB -> B_14_37_0 = _rtP -> P_139 ; _rtB -> B_14_38_0 = _rtP -> P_140 ; _rtB
-> B_14_39_0_d = _rtP -> P_141 ; _rtB -> B_14_40_0_g = _rtP -> P_142 ; switch
( ( int32_T ) _rtP -> P_143 ) { case 1 : _rtB -> B_14_45_0_l [ 0 ] = _rtP ->
P_144 [ 0 ] ; _rtB -> B_14_45_0_l [ 1 ] = _rtP -> P_144 [ 1 ] ; break ; case
2 : _rtB -> B_14_45_0_l [ 0 ] = _rtP -> P_145 [ 0 ] ; _rtB -> B_14_45_0_l [ 1
] = _rtP -> P_145 [ 1 ] ; break ; default : _rtB -> B_14_45_0_l [ 0 ] = _rtP
-> P_146 [ 0 ] ; _rtB -> B_14_45_0_l [ 1 ] = _rtP -> P_146 [ 1 ] ; break ; }
_rtB -> B_14_46_0 = _rtP -> P_147 ; switch ( ( int32_T ) _rtP -> P_148 ) {
case 1 : _rtB -> B_14_51_0_d [ 0 ] = _rtP -> P_149 [ 0 ] ; _rtB ->
B_14_51_0_d [ 1 ] = _rtP -> P_149 [ 1 ] ; break ; case 2 : _rtB ->
B_14_51_0_d [ 0 ] = _rtP -> P_150 [ 0 ] ; _rtB -> B_14_51_0_d [ 1 ] = _rtP ->
P_150 [ 1 ] ; break ; default : _rtB -> B_14_51_0_d [ 0 ] = _rtP -> P_151 [ 0
] ; _rtB -> B_14_51_0_d [ 1 ] = _rtP -> P_151 [ 1 ] ; break ; }
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { int32_T isHit ; B_FSK_T
* _rtB ; P_FSK_T * _rtP ; DW_FSK_T * _rtDW ; _rtDW = ( ( DW_FSK_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_FSK_T * ) ssGetModelRtp ( S ) ) ; _rtB
= ( ( B_FSK_T * ) _ssGetModelBlockIO ( S ) ) ; { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = (
( _rtDW -> TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_9 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_14_6_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_h . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_i . Head = ( ( _rtDW ->
TransportDelay_IWORK_i . Head < ( _rtDW -> TransportDelay_IWORK_i .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_i . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_i . Head == _rtDW ->
TransportDelay_IWORK_i . Tail ) { if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf
( & _rtDW -> TransportDelay_IWORK_i . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_i . Tail , & _rtDW -> TransportDelay_IWORK_i . Head , &
_rtDW -> TransportDelay_IWORK_i . Last , simTime - _rtP -> P_18 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_i . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_i . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_i . Head ] = _rtB -> B_14_13_0 ; } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK_e . Head = ( ( _rtDW -> TransportDelay_IWORK_e . Head <
( _rtDW -> TransportDelay_IWORK_e . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_e . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_e . Head == _rtDW -> TransportDelay_IWORK_e . Tail ) {
if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_e . CircularBufSize , & _rtDW -> TransportDelay_IWORK_e
. Tail , & _rtDW -> TransportDelay_IWORK_e . Head , & _rtDW ->
TransportDelay_IWORK_e . Last , simTime - _rtP -> P_21 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_e .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_e . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_e . Head ] = _rtB ->
B_14_27_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> NextOutput = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed ) * _rtP ->
P_24 + _rtP -> P_23 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_c4 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_c4 . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_ic . Head = ( ( _rtDW
-> TransportDelay_IWORK_ic . Head < ( _rtDW -> TransportDelay_IWORK_ic .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_ic . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_ic . Head == _rtDW ->
TransportDelay_IWORK_ic . Tail ) { if ( !
FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay_IWORK_ic .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_ic . Tail , & _rtDW ->
TransportDelay_IWORK_ic . Head , & _rtDW -> TransportDelay_IWORK_ic . Last ,
simTime - _rtP -> P_30 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay_IWORK_ic . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay_IWORK_ic . Head ] = simTime ; ( * uBuffer
) [ _rtDW -> TransportDelay_IWORK_ic . Head ] = _rtB -> B_14_13_0 ; } {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay12_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay12_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay12_IWORK . Head = ( ( _rtDW -> TransportDelay12_IWORK
. Head < ( _rtDW -> TransportDelay12_IWORK . CircularBufSize - 1 ) ) ? (
_rtDW -> TransportDelay12_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay12_IWORK . Head == _rtDW -> TransportDelay12_IWORK . Tail ) {
if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay12_IWORK . CircularBufSize , & _rtDW -> TransportDelay12_IWORK
. Tail , & _rtDW -> TransportDelay12_IWORK . Head , & _rtDW ->
TransportDelay12_IWORK . Last , simTime - _rtP -> P_36 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay12_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay12_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay12_IWORK . Head ] = _rtB ->
B_14_9_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> Memory_PreviousInput = _rtB -> B_14_79_0 ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [
1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay2_IWORK . Head =
( ( _rtDW -> TransportDelay2_IWORK . Head < ( _rtDW -> TransportDelay2_IWORK
. CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay2_IWORK . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay2_IWORK . Head == _rtDW ->
TransportDelay2_IWORK . Tail ) { if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf
( & _rtDW -> TransportDelay2_IWORK . CircularBufSize , & _rtDW ->
TransportDelay2_IWORK . Tail , & _rtDW -> TransportDelay2_IWORK . Head , &
_rtDW -> TransportDelay2_IWORK . Last , simTime - _rtP -> P_38 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay2_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay2_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay2_IWORK . Head ] = _rtB -> B_14_39_0 ; } { real_T * * uBuffer =
( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs
[ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK . Head
= ( ( _rtDW -> TransportDelay1_IWORK . Head < ( _rtDW ->
TransportDelay1_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK . Head == _rtDW -> TransportDelay1_IWORK . Tail ) { if
( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay1_IWORK .
CircularBufSize , & _rtDW -> TransportDelay1_IWORK . Tail , & _rtDW ->
TransportDelay1_IWORK . Head , & _rtDW -> TransportDelay1_IWORK . Last ,
simTime - _rtP -> P_40 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay1_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay1_IWORK . Head ] = _rtB -> B_14_41_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay4_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay4_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay4_IWORK . Head = ( ( _rtDW -> TransportDelay4_IWORK . Head < (
_rtDW -> TransportDelay4_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay4_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay4_IWORK . Head == _rtDW -> TransportDelay4_IWORK . Tail ) { if
( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay4_IWORK .
CircularBufSize , & _rtDW -> TransportDelay4_IWORK . Tail , & _rtDW ->
TransportDelay4_IWORK . Head , & _rtDW -> TransportDelay4_IWORK . Last ,
simTime - _rtP -> P_42 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay4_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay4_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay4_IWORK . Head ] = _rtB -> B_14_43_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay3_IWORK . Head = ( ( _rtDW -> TransportDelay3_IWORK . Head < (
_rtDW -> TransportDelay3_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay3_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay3_IWORK . Head == _rtDW -> TransportDelay3_IWORK . Tail ) { if
( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay3_IWORK .
CircularBufSize , & _rtDW -> TransportDelay3_IWORK . Tail , & _rtDW ->
TransportDelay3_IWORK . Head , & _rtDW -> TransportDelay3_IWORK . Last ,
simTime - _rtP -> P_44 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay3_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay3_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay3_IWORK . Head ] = _rtB -> B_14_45_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay6_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay6_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay6_IWORK . Head = ( ( _rtDW -> TransportDelay6_IWORK . Head < (
_rtDW -> TransportDelay6_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay6_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay6_IWORK . Head == _rtDW -> TransportDelay6_IWORK . Tail ) { if
( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay6_IWORK .
CircularBufSize , & _rtDW -> TransportDelay6_IWORK . Tail , & _rtDW ->
TransportDelay6_IWORK . Head , & _rtDW -> TransportDelay6_IWORK . Last ,
simTime - _rtP -> P_46 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay6_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay6_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay6_IWORK . Head ] = _rtB -> B_14_47_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay5_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay5_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay5_IWORK . Head = ( ( _rtDW -> TransportDelay5_IWORK . Head < (
_rtDW -> TransportDelay5_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay5_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay5_IWORK . Head == _rtDW -> TransportDelay5_IWORK . Tail ) { if
( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay5_IWORK .
CircularBufSize , & _rtDW -> TransportDelay5_IWORK . Tail , & _rtDW ->
TransportDelay5_IWORK . Head , & _rtDW -> TransportDelay5_IWORK . Last ,
simTime - _rtP -> P_48 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay5_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay5_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay5_IWORK . Head ] = _rtB -> B_14_49_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay8_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay8_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay8_IWORK . Head = ( ( _rtDW -> TransportDelay8_IWORK . Head < (
_rtDW -> TransportDelay8_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay8_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay8_IWORK . Head == _rtDW -> TransportDelay8_IWORK . Tail ) { if
( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay8_IWORK .
CircularBufSize , & _rtDW -> TransportDelay8_IWORK . Tail , & _rtDW ->
TransportDelay8_IWORK . Head , & _rtDW -> TransportDelay8_IWORK . Last ,
simTime - _rtP -> P_50 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay8_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay8_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay8_IWORK . Head ] = _rtB -> B_14_51_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay7_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay7_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay7_IWORK . Head = ( ( _rtDW -> TransportDelay7_IWORK . Head < (
_rtDW -> TransportDelay7_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay7_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay7_IWORK . Head == _rtDW -> TransportDelay7_IWORK . Tail ) { if
( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay7_IWORK .
CircularBufSize , & _rtDW -> TransportDelay7_IWORK . Tail , & _rtDW ->
TransportDelay7_IWORK . Head , & _rtDW -> TransportDelay7_IWORK . Last ,
simTime - _rtP -> P_52 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay7_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay7_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay7_IWORK . Head ] = _rtB -> B_14_53_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay9_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay9_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay9_IWORK . Head = ( ( _rtDW -> TransportDelay9_IWORK . Head < (
_rtDW -> TransportDelay9_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay9_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay9_IWORK . Head == _rtDW -> TransportDelay9_IWORK . Tail ) { if
( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay9_IWORK .
CircularBufSize , & _rtDW -> TransportDelay9_IWORK . Tail , & _rtDW ->
TransportDelay9_IWORK . Head , & _rtDW -> TransportDelay9_IWORK . Last ,
simTime - _rtP -> P_54 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay9_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay9_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay9_IWORK . Head ] = _rtB -> B_14_55_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay11_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay11_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay11_IWORK . Head = ( ( _rtDW -> TransportDelay11_IWORK . Head <
( _rtDW -> TransportDelay11_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay11_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay11_IWORK . Head == _rtDW -> TransportDelay11_IWORK . Tail ) {
if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay11_IWORK . CircularBufSize , & _rtDW -> TransportDelay11_IWORK
. Tail , & _rtDW -> TransportDelay11_IWORK . Head , & _rtDW ->
TransportDelay11_IWORK . Last , simTime - _rtP -> P_56 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay11_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay11_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay11_IWORK . Head ] = _rtB ->
B_14_57_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay10_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay10_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay10_IWORK . Head = ( ( _rtDW ->
TransportDelay10_IWORK . Head < ( _rtDW -> TransportDelay10_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay10_IWORK . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay10_IWORK . Head == _rtDW ->
TransportDelay10_IWORK . Tail ) { if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf
( & _rtDW -> TransportDelay10_IWORK . CircularBufSize , & _rtDW ->
TransportDelay10_IWORK . Tail , & _rtDW -> TransportDelay10_IWORK . Head , &
_rtDW -> TransportDelay10_IWORK . Last , simTime - _rtP -> P_58 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay10_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay10_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay10_IWORK . Head ] = _rtB -> B_14_59_0 ; } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay13_PWORK . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay13_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay13_IWORK . Head = ( ( _rtDW -> TransportDelay13_IWORK . Head <
( _rtDW -> TransportDelay13_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay13_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay13_IWORK . Head == _rtDW -> TransportDelay13_IWORK . Tail ) {
if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay13_IWORK . CircularBufSize , & _rtDW -> TransportDelay13_IWORK
. Tail , & _rtDW -> TransportDelay13_IWORK . Head , & _rtDW ->
TransportDelay13_IWORK . Last , simTime - _rtP -> P_60 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay13_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay13_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay13_IWORK . Head ] = _rtB ->
B_14_61_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> Memory_PreviousInput_f = _rtB -> B_14_68_0 ; _rtDW -> ICic_PreviousInput =
_rtB -> B_14_76_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_o . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_o . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_g . Head = ( ( _rtDW ->
TransportDelay_IWORK_g . Head < ( _rtDW -> TransportDelay_IWORK_g .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_g . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_g . Head == _rtDW ->
TransportDelay_IWORK_g . Tail ) { if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf
( & _rtDW -> TransportDelay_IWORK_g . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_g . Tail , & _rtDW -> TransportDelay_IWORK_g . Head , &
_rtDW -> TransportDelay_IWORK_g . Last , simTime - _rtP -> P_70 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_g . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_g . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_g . Head ] = _rtB -> B_14_12_0 ; } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK_j . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_j .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK_ir . Head = ( ( _rtDW -> TransportDelay_IWORK_ir . Head
< ( _rtDW -> TransportDelay_IWORK_ir . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_ir . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_ir . Head == _rtDW -> TransportDelay_IWORK_ir . Tail ) {
if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_ir . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_ir . Tail , & _rtDW -> TransportDelay_IWORK_ir . Head ,
& _rtDW -> TransportDelay_IWORK_ir . Last , simTime - _rtP -> P_72 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_ir . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_ir . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_ir . Head ] = _rtB -> B_14_110_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_j . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_j
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay1_IWORK_d . Head = ( ( _rtDW -> TransportDelay1_IWORK_d . Head
< ( _rtDW -> TransportDelay1_IWORK_d . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK_d . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK_d . Head == _rtDW -> TransportDelay1_IWORK_d . Tail ) {
if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK_d . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_d . Tail , & _rtDW -> TransportDelay1_IWORK_d . Head ,
& _rtDW -> TransportDelay1_IWORK_d . Last , simTime - _rtP -> P_75 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay1_IWORK_d . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay1_IWORK_d . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK_d . Head ] = _rtB -> B_14_117_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_o . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_o
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay1_IWORK_g . Head = ( ( _rtDW -> TransportDelay1_IWORK_g . Head
< ( _rtDW -> TransportDelay1_IWORK_g . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK_g . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK_g . Head == _rtDW -> TransportDelay1_IWORK_g . Tail ) {
if ( ! FSK_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK_g . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_g . Tail , & _rtDW -> TransportDelay1_IWORK_g . Head ,
& _rtDW -> TransportDelay1_IWORK_g . Last , simTime - _rtP -> P_78 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay1_IWORK_g . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay1_IWORK_g . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK_g . Head ] = _rtB -> B_14_12_0 ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> NextOutput_m =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_m ) * _rtP -> P_81 + _rtP ->
P_80 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Memory_PreviousInput_b = _rtB -> B_14_148_0 ; _rtDW -> Memory_PreviousInput_p
= _rtB -> B_14_137_0 ; _rtDW -> ICic_PreviousInput_b = _rtB -> B_14_145_0 ;
_rtDW -> Memory_PreviousInput_k = _rtB -> B_14_166_0 ; _rtDW ->
Memory_PreviousInput_ke = _rtB -> B_14_155_0 ; _rtDW -> ICic_PreviousInput_a
= _rtB -> B_14_163_0 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID5 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { int_T is ; int_T ci ; static
const int8_T ir [ 7 ] = { 0 , 2 , 3 , 6 , 7 , 10 , 11 } ; static const int8_T
ir_0 [ 7 ] = { 0 , 1 , 1 , 1 , 1 , 1 , 1 } ; static const int8_T jc [ 11 ] =
{ 0 , 1 , 0 , 1 , 2 , 3 , 2 , 3 , 4 , 5 , 4 } ; B_FSK_T * _rtB ; P_FSK_T *
_rtP ; X_FSK_T * _rtX ; XDot_FSK_T * _rtXdot ; _rtXdot = ( ( XDot_FSK_T * )
ssGetdX ( S ) ) ; _rtX = ( ( X_FSK_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_FSK_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_FSK_T * ) _ssGetModelBlockIO
( S ) ) ; _rtXdot -> Integrator_CSTATE = _rtB -> B_0_0_0 ; _rtXdot ->
ModuloIntegrator_CSTATE = _rtB -> B_14_173_0 ; _rtXdot -> Integrator_CSTATE_d
= _rtB -> B_14_128_0 ; _rtXdot -> Filtro_CSTATE [ 0 ] = 0.0 ; _rtXdot ->
Filtro_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Filtro_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Filtro_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Filtro_CSTATE [ 0 ] += _rtP -> P_11 [
0 ] * _rtX -> Filtro_CSTATE [ 0 ] ; _rtXdot -> Filtro_CSTATE [ 0 ] += _rtP ->
P_11 [ 1 ] * _rtX -> Filtro_CSTATE [ 1 ] ; _rtXdot -> Filtro_CSTATE [ 0 ] +=
_rtP -> P_11 [ 2 ] * _rtX -> Filtro_CSTATE [ 2 ] ; _rtXdot -> Filtro_CSTATE [
1 ] += _rtP -> P_11 [ 3 ] * _rtX -> Filtro_CSTATE [ 0 ] ; _rtXdot ->
Filtro_CSTATE [ 1 ] += _rtP -> P_11 [ 4 ] * _rtX -> Filtro_CSTATE [ 3 ] ;
_rtXdot -> Filtro_CSTATE [ 2 ] += _rtP -> P_11 [ 5 ] * _rtX -> Filtro_CSTATE
[ 0 ] ; _rtXdot -> Filtro_CSTATE [ 3 ] += _rtP -> P_11 [ 6 ] * _rtX ->
Filtro_CSTATE [ 1 ] ; _rtXdot -> Filtro_CSTATE [ 0 ] += _rtP -> P_12 * _rtB
-> B_14_26_0 ; _rtXdot -> ModuloIntegrator_CSTATE_j = _rtB -> B_14_19_0 ; for
( is = 0 ; is < 6 ; is ++ ) { _rtXdot -> Filtro_CSTATE_j [ is ] = 0.0 ; for (
ci = ir [ is ] ; ci < ir [ is + 1 ] ; ci ++ ) { _rtXdot -> Filtro_CSTATE_j [
is ] += _rtP -> P_66 [ ci ] * _rtX -> Filtro_CSTATE_j [ jc [ ci ] ] ; } } for
( is = 0 ; is < 6 ; is ++ ) { ci = ir_0 [ is ] ; while ( ci < 1 ) { _rtXdot
-> Filtro_CSTATE_j [ is ] += _rtP -> P_67 * _rtB -> B_14_106_0 ; ci = 1 ; } }
_rtXdot -> ModuloIntegrator_CSTATE_b = _rtB -> B_14_123_0 ; _rtXdot ->
Integrator_CSTATE_p = _rtB -> B_14_126_0 ; _rtXdot ->
ModuloIntegrator_CSTATE_j0 = _rtB -> B_14_125_0 ; _rtXdot ->
Integrator1_CSTATE = _rtB -> B_14_127_0 ; _rtXdot -> Integrator_CSTATE_p0 =
_rtB -> B_14_128_0 ; _rtXdot -> Integrator1_CSTATE_a = _rtB -> B_14_128_0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_FSK_T * _rtB ; P_FSK_T *
_rtP ; ZCV_FSK_T * _rtZCSV ; _rtZCSV = ( ( ZCV_FSK_T * )
ssGetSolverZcSignalVector ( S ) ) ; _rtP = ( ( P_FSK_T * ) ssGetModelRtp ( S
) ) ; _rtB = ( ( B_FSK_T * ) _ssGetModelBlockIO ( S ) ) ; _rtZCSV ->
Sign_Input_ZC = _rtB -> B_14_4_0 ; _rtZCSV -> Compare_RelopInput_ZC = _rtB ->
B_14_7_0 - _rtB -> B_14_2_0 ; _rtZCSV -> Switch_SwitchCond_ZC = _rtB ->
B_14_65_0 - _rtP -> P_62 ; _rtZCSV -> Switch1_SwitchCond_ZC = _rtB ->
B_14_65_0 - _rtP -> P_63 ; _rtZCSV -> RelationalOperator_RelopInput_ZC = _rtB
-> B_14_78_0 - _rtB -> B_14_36_0 ; _rtZCSV -> Mensajerecibido_Trig_ZC = _rtB
-> B_14_80_0 ; _rtZCSV -> Sign3_Input_ZC = _rtB -> B_14_82_0 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_g = _rtB -> B_14_131_0 - _rtB -> B_14_129_0
; _rtZCSV -> RelationalOperator_RelopInput_ZC_c = _rtB -> B_14_147_0 - _rtB
-> B_14_134_0 ; _rtZCSV -> RelationalOperator_RelopInput_ZC_e = _rtB ->
B_14_165_0 - _rtB -> B_14_152_0 ; _rtZCSV -> Abs1_AbsZc_ZC = _rtB ->
B_14_167_0 ; _rtZCSV -> RelationalOperator_RelopInput_ZC_et = _rtB ->
B_14_176_0 - _rtB -> B_14_174_0 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_j = _rtB -> B_14_180_0 - _rtB -> B_14_178_0
; } static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S ,
0 , 4104048424U ) ; ssSetChecksumVal ( S , 1 , 1608778103U ) ;
ssSetChecksumVal ( S , 2 , 572647230U ) ; ssSetChecksumVal ( S , 3 ,
617132021U ) ; { mxArray * slVerStructMat = NULL ; mxArray * slStrMat =
mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status =
mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status
== 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ;
if ( slVerMat == NULL ) { status = 1 ; } else { status = mxGetString (
slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "10.1" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
DW_FSK_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_FSK_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_FSK_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & FSK_rtDefaultP ) ; } static void mdlInitializeSampleTimes ( SimStruct * S
) { slAccRegPrmChangeFcn ( S , mdlOutputsTID5 ) ; } static void mdlTerminate
( SimStruct * S ) { }
#include "simulink.c"
