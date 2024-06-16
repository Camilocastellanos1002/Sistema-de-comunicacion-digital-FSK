#include <math.h>
#include "multiplex_acc.h"
#include "multiplex_acc_private.h"
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
boolean_T multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr ,
int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay ,
real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr , boolean_T
isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr ) { int_T
testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf =
* tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail <
( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] )
&& ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T *
tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024
; if ( newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU
= ( real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if (
tempU == ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if (
istransportdelay ) * xBufPtr = tempX ; } else { * tailPtr = testIdx ; }
return ( true ) ; } real_T multiplex_acc_rt_TDelayInterpolate ( real_T
tMinusDelay , real_T tStart , real_T * tBuf , real_T * uBuf , int_T bufSz ,
int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput ,
boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ;
real_T yout , t1 , t2 , u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } void rt_ssGetBlockPath (
SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * * path ) {
_ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void rt_ssSet_slErrMsg (
SimStruct * S , void * diag ) { if ( ! _ssIsErrorStatusAslErrMsg ( S ) ) {
_ssSet_slErrMsg ( S , diag ) ; } else { _ssDiscardDiagnostic ( S , diag ) ; }
} void rt_ssReportDiagnosticAsWarning ( SimStruct * S , void * diag ) {
_ssReportDiagnosticAsWarning ( S , diag ) ; } void
multiplex_MuestreoyRetencion_Init ( SimStruct * S ,
B_MuestreoyRetencion_multiplex_T * localB , P_MuestreoyRetencion_multiplex_T
* localP ) { localB -> B_0_0_0 = localP -> P_0 ; } void
multiplex_MuestreoyRetencion ( SimStruct * S , real_T rtu_Trigger , real_T
rtu_In , B_MuestreoyRetencion_multiplex_T * localB ,
DW_MuestreoyRetencion_multiplex_T * localDW ,
ZCE_MuestreoyRetencion_multiplex_T * localZCE ) { ZCEventType zcEvent ; if (
ssIsMajorTimeStep ( S ) != 0 ) { zcEvent = rt_ZCFcn ( RISING_ZERO_CROSSING ,
& localZCE -> MuestreoyRetencion_Trig_ZCE , rtu_Trigger ) ; if ( zcEvent !=
NO_ZCEVENT ) { localB -> B_0_0_0 = rtu_In ; localDW ->
MuestreoyRetencion_SubsysRanBC = 4 ; } } } void
multiplex_MuestreoyRetencion_Term ( SimStruct * const S ) { } void
multiplex_SampleandHold_Init ( SimStruct * S , B_SampleandHold_multiplex_T *
localB , P_SampleandHold_multiplex_T * localP ) { localB -> B_3_0_0 = localP
-> P_0 ; } void multiplex_SampleandHold ( SimStruct * S , real_T rtu_Trigger
, boolean_T rtu_In , B_SampleandHold_multiplex_T * localB ,
DW_SampleandHold_multiplex_T * localDW , ZCE_SampleandHold_multiplex_T *
localZCE ) { ZCEventType zcEvent ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & localZCE ->
SampleandHold_Trig_ZCE_b , rtu_Trigger ) ; if ( zcEvent != NO_ZCEVENT ) {
localB -> B_3_0_0 = rtu_In ; localDW -> SampleandHold_SubsysRanBC = 4 ; } } }
void multiplex_SampleandHold_Term ( SimStruct * const S ) { } void
multiplex_TriggeredSubsystem_Init ( SimStruct * S ,
B_TriggeredSubsystem_multiplex_T * localB , P_TriggeredSubsystem_multiplex_T
* localP ) { localB -> B_4_0_0 = localP -> P_0 ; } void
multiplex_TriggeredSubsystem ( SimStruct * S , boolean_T rtu_Trigger , real_T
rtu_In1 , B_TriggeredSubsystem_multiplex_T * localB ,
DW_TriggeredSubsystem_multiplex_T * localDW ,
ZCE_TriggeredSubsystem_multiplex_T * localZCE ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { if ( rtu_Trigger && ( localZCE -> TriggeredSubsystem_Trig_ZCE !=
POS_ZCSIG ) ) { localB -> B_4_0_0 = rtu_In1 ; localDW ->
TriggeredSubsystem_SubsysRanBC = 4 ; } localZCE ->
TriggeredSubsystem_Trig_ZCE = rtu_Trigger ; } } void
multiplex_TriggeredSubsystem_Term ( SimStruct * const S ) { } void
multiplex_NEGATIVEEdge ( SimStruct * S , real_T rtu_Enable , boolean_T rtu_IN
, boolean_T rtu_INprevious , B_NEGATIVEEdge_multiplex_T * localB ,
DW_NEGATIVEEdge_multiplex_T * localDW ) { if ( rtu_Enable > 0.0 ) { localB ->
B_5_0_0 = ( ( int32_T ) rtu_INprevious > ( int32_T ) rtu_IN ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( localDW ->
NEGATIVEEdge_SubsysRanBC ) ; } } } void multiplex_NEGATIVEEdge_Term (
SimStruct * const S ) { } void multiplex_POSITIVEEdge ( SimStruct * S ,
real_T rtu_Enable , boolean_T rtu_IN , boolean_T rtu_INprevious ,
B_POSITIVEEdge_multiplex_T * localB , DW_POSITIVEEdge_multiplex_T * localDW )
{ if ( rtu_Enable > 0.0 ) { localB -> B_6_0_0 = ( ( int32_T ) rtu_INprevious
< ( int32_T ) rtu_IN ) ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC (
localDW -> POSITIVEEdge_SubsysRanBC ) ; } } } void
multiplex_POSITIVEEdge_Term ( SimStruct * const S ) { } void
multiplex_SampleandHold_m_Init ( SimStruct * S ,
B_SampleandHold_multiplex_h_T * localB , P_SampleandHold_multiplex_n_T *
localP ) { localB -> B_13_0_0 = localP -> P_0 ; } void
multiplex_SampleandHold_c ( SimStruct * S , boolean_T rtu_Trigger , real_T
rtu_In , B_SampleandHold_multiplex_h_T * localB ,
DW_SampleandHold_multiplex_n_T * localDW , ZCE_SampleandHold_multiplex_h_T *
localZCE ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( ( ! rtu_Trigger ) &&
( localZCE -> SampleandHold_Trig_ZCE != ZERO_ZCSIG ) ) { localB -> B_13_0_0 =
rtu_In ; localDW -> SampleandHold_SubsysRanBC = 4 ; } localZCE ->
SampleandHold_Trig_ZCE = rtu_Trigger ; } } void
multiplex_SampleandHold_j_Term ( SimStruct * const S ) { } void
multiplex_SampleandHold1_Init ( SimStruct * S , B_SampleandHold1_multiplex_T
* localB , P_SampleandHold1_multiplex_T * localP ) { localB -> B_14_0_0 =
localP -> P_0 ; } void multiplex_SampleandHold1 ( SimStruct * S , real_T
rtu_Trigger , real_T rtu_In , B_SampleandHold1_multiplex_T * localB ,
DW_SampleandHold1_multiplex_T * localDW , ZCE_SampleandHold1_multiplex_T *
localZCE ) { ZCEventType zcEvent ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & localZCE ->
SampleandHold1_Trig_ZCE , rtu_Trigger ) ; if ( zcEvent != NO_ZCEVENT ) {
localB -> B_14_0_0 = rtu_In ; localDW -> SampleandHold1_SubsysRanBC = 4 ; } }
} void multiplex_SampleandHold1_Term ( SimStruct * const S ) { } real_T
rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { uint32_T lo ; uint32_T hi ; lo
= * u % 127773U * 16807U ; hi = * u / 127773U * 2836U ; if ( lo < hi ) { * u
= 2147483647U - ( hi - lo ) ; } else { * u = lo - hi ; } return ( real_T ) *
u * 4.6566128752457969E-10 ; } real_T rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T *
u ) { real_T y ; real_T sr ; real_T si ; do { sr = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = sr * sr + si * si ; } while (
si > 1.0 ) ; y = muDoubleScalarSqrt ( - 2.0 * muDoubleScalarLog ( si ) / si )
* sr ; return y ; } static void mdlOutputs ( SimStruct * S , int_T tid ) {
real_T B_28_37_0 ; real_T B_28_40_0 ; real_T B_28_43_0 ; real_T B_28_51_0 ;
real_T B_28_55_0 ; real_T B_28_57_0 ; real_T B_28_61_0 ; real_T B_28_63_0 ;
real_T B_28_91_0 ; real_T B_28_111_0 ; real_T B_28_113_0 ; real_T B_28_117_0
; real_T B_28_119_0 ; real_T B_28_140_0 ; real_T B_28_147_0 ; real_T
B_28_208_0 ; real_T B_28_236_0 ; real_T B_28_256_0 ; real_T B_28_258_0 ;
real_T B_28_262_0 ; real_T B_28_264_0 ; real_T B_28_285_0 ; real_T B_28_292_0
; boolean_T B_28_7_0 ; boolean_T B_28_17_0 ; boolean_T B_28_97_0 ; boolean_T
B_28_100_0 ; boolean_T B_28_164_0 ; boolean_T B_28_167_0 ; boolean_T
B_28_182_0 ; boolean_T B_28_185_0 ; boolean_T B_28_242_0 ; boolean_T
B_28_245_0 ; boolean_T B_28_309_0 ; boolean_T B_28_312_0 ; boolean_T
B_28_327_0 ; boolean_T B_28_330_0 ; ZCEventType zcEvent ; real_T
rtb_B_28_34_0 ; real_T rtb_B_28_31_0 ; boolean_T rtb_B_28_325_0 ; boolean_T
rtb_B_28_307_0 ; boolean_T rtb_B_28_211_0 ; boolean_T rtb_B_28_180_0 ;
boolean_T rtb_B_28_162_0 ; boolean_T rtb_B_28_66_0 ; real_T rtb_B_28_90_0 ;
real_T rtb_B_28_88_0 ; real_T rtb_B_28_86_0 ; real_T rtb_B_28_84_0 ; real_T
rtb_B_28_82_0 ; real_T rtb_B_28_80_0 ; real_T rtb_B_28_78_0 ; real_T
rtb_B_28_76_0 ; real_T rtb_B_28_74_0 ; uint32_T numCycles ; int32_T isHit ;
B_multiplex_T * _rtB ; P_multiplex_T * _rtP ; X_multiplex_T * _rtX ;
PrevZCX_multiplex_T * _rtZCE ; DW_multiplex_T * _rtDW ; _rtDW = ( (
DW_multiplex_T * ) ssGetRootDWork ( S ) ) ; _rtZCE = ( ( PrevZCX_multiplex_T
* ) _ssGetPrevZCSigState ( S ) ) ; _rtX = ( ( X_multiplex_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_multiplex_T * ) ssGetModelRtp ( S ) )
; _rtB = ( ( B_multiplex_T * ) _ssGetModelBlockIO ( S ) ) ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ]
; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_0 ; _rtB -> B_28_0_0 = multiplex_acc_rt_TDelayInterpolate
( tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK .
CircularBufSize , & _rtDW -> TransportDelay_IWORK . Last , _rtDW ->
TransportDelay_IWORK . Tail , _rtDW -> TransportDelay_IWORK . Head , _rtP ->
P_1 , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput
( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_28_3_0 = muDoubleScalarCos ( _rtX
-> ModuloIntegrator_CSTATE * 6.2831853071795862 ) ; isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( isHit != 0 ) { if ( _rtB -> B_28_3_0 > 0.0 ) { _rtDW ->
Sign_MODE = 1 ; } else if ( _rtB -> B_28_3_0 < 0.0 ) { _rtDW -> Sign_MODE = -
1 ; } else { _rtDW -> Sign_MODE = 0 ; } if ( _rtDW -> Sign_MODE >= _rtP ->
P_5 ) { _rtB -> B_28_5_0 = _rtB -> B_28_39_0_d ; } else { _rtB -> B_28_5_0 =
_rtB -> B_28_40_0 ; } } if ( ssIsMajorTimeStep ( S ) != 0 ) { zcEvent =
rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE -> Integrator_Reset_ZCE , _rtB ->
B_28_5_0 ) ; if ( zcEvent != NO_ZCEVENT ) { _rtX -> Integrator_CSTATE = _rtP
-> P_6 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } } _rtB ->
B_28_6_0 = _rtX -> Integrator_CSTATE ; isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Compare_Mode = ( _rtB -> B_28_6_0 >= _rtB -> B_28_4_0 ) ; } B_28_7_0 = _rtDW
-> Compare_Mode ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_k . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_k . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_7 ; _rtB -> B_28_8_0
= multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK_g . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_g . Last , _rtDW -> TransportDelay_IWORK_g . Tail ,
_rtDW -> TransportDelay_IWORK_g . Head , _rtP -> P_8 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
multiplex_SampleandHold ( S , _rtB -> B_28_8_0 , B_28_7_0 , & _rtB ->
SampleandHold , & _rtDW -> SampleandHold , & _rtZCE -> SampleandHold ) ; }
isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock
( S , 28 , 10 , SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_28_13_0 =
muDoubleScalarCos ( _rtX -> ModuloIntegrator_CSTATE_k * 6.2831853071795862 )
; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( _rtB ->
B_28_13_0 > 0.0 ) { _rtDW -> Sign_MODE_d = 1 ; } else if ( _rtB -> B_28_13_0
< 0.0 ) { _rtDW -> Sign_MODE_d = - 1 ; } else { _rtDW -> Sign_MODE_d = 0 ; }
if ( _rtDW -> Sign_MODE_d >= _rtP -> P_12 ) { _rtB -> B_28_15_0 = _rtB ->
B_28_89_0_j ; } else { _rtB -> B_28_15_0 = _rtB -> B_28_90_0 ; } } if (
ssIsMajorTimeStep ( S ) != 0 ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
_rtZCE -> Integrator_Reset_ZCE_d , _rtB -> B_28_15_0 ) ; if ( zcEvent !=
NO_ZCEVENT ) { _rtX -> Integrator_CSTATE_n = _rtP -> P_13 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } } _rtB -> B_28_16_0 =
_rtX -> Integrator_CSTATE_n ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode_d
= ( _rtB -> B_28_16_0 >= _rtB -> B_28_54_0_l ) ; } B_28_17_0 = _rtDW ->
Compare_Mode_d ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_f . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_f . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_14 ; _rtB ->
B_28_18_0 = multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_d . CircularBufSize , &
_rtDW -> TransportDelay_IWORK_d . Last , _rtDW -> TransportDelay_IWORK_d .
Tail , _rtDW -> TransportDelay_IWORK_d . Head , _rtP -> P_15 , 1 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { multiplex_SampleandHold ( S , _rtB -> B_28_18_0 , B_28_17_0 , & _rtB ->
SampleandHold_j , & _rtDW -> SampleandHold_j , & _rtZCE -> SampleandHold_j )
; } ssCallAccelRunBlock ( S , 28 , 20 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
28 , 21 , SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_28_23_0 = _rtX ->
Integrator_CSTATE_l * _rtB -> B_28_2_0 ; ssCallAccelRunBlock ( S , 28 , 24 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_28_26_0 = _rtX -> Integrator_CSTATE_j *
_rtB -> B_28_3_0_c ; ssCallAccelRunBlock ( S , 28 , 27 , SS_CALL_MDL_OUTPUTS
) ; _rtB -> B_28_28_0 = 0.0 ; _rtB -> B_28_28_0 += _rtP -> P_20 * _rtX ->
AnalogFilterDesign_CSTATE [ 4 ] ; _rtB -> B_28_29_0 = 0.0 ; _rtB -> B_28_29_0
+= _rtP -> P_24 * _rtX -> AnalogFilterDesign2_CSTATE [ 4 ] ; rtb_B_28_31_0 =
muDoubleScalarCos ( _rtX -> ModuloIntegrator_CSTATE_kx * 6.2831853071795862 )
; rtb_B_28_34_0 = muDoubleScalarCos ( _rtX -> ModuloIntegrator_CSTATE_h *
6.2831853071795862 ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_c . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_c . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_32 ; if ( _rtP ->
P_32 == 0.0 ) B_28_37_0 = _rtB -> B_28_21_0 ; else B_28_37_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK_j . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_j . Last , _rtDW -> TransportDelay_IWORK_j . Tail ,
_rtDW -> TransportDelay_IWORK_j . Head , _rtP -> P_33 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_28_39_0 = _rtP -> P_34 * B_28_37_0 + _rtB -> B_28_0_0_m ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_m .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_m . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_35 ; if ( _rtP -> P_35 == 0.0 )
B_28_40_0 = _rtB -> B_28_10_0 ; else B_28_40_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_a . Last , _rtDW -> TransportDelay_IWORK_a . Tail ,
_rtDW -> TransportDelay_IWORK_a . Head , _rtP -> P_36 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_28_42_0 = _rtP -> P_37 * B_28_40_0 + _rtB -> B_28_1_0 ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_cm .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_cm . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S )
; real_T tMinusDelay = simTime - _rtP -> P_38 ; B_28_43_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK_e . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_e . Last , _rtDW -> TransportDelay_IWORK_e . Tail ,
_rtDW -> TransportDelay_IWORK_e . Head , _rtP -> P_39 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_28_47_0 = _rtP -> P_43 * _rtDW -> NextOutput + _rtP -> P_44 ; _rtB ->
B_28_48_0 = _rtB -> B_28_47_0 ; } _rtB -> B_28_49_0 = B_28_43_0 + _rtB ->
B_28_48_0 ; _rtB -> B_28_50_0 = ( rtb_B_28_31_0 + rtb_B_28_34_0 ) * _rtP ->
P_46 ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_kg . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_kg . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_47 ;
B_28_51_0 = multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_o . CircularBufSize , &
_rtDW -> TransportDelay_IWORK_o . Last , _rtDW -> TransportDelay_IWORK_o .
Tail , _rtDW -> TransportDelay_IWORK_o . Head , _rtP -> P_48 , 1 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } _rtB -> B_28_53_0 = ( int8_T ) ( ( int8_T ) (
B_28_51_0 != 0.0 ) ^ ( int8_T ) _rtB -> SampleandHold . B_3_0_0 ) ; isHit =
ssIsSampleHit ( S , 4 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_31_0 =
ssGetTaskTime ( S , 4 ) ; if ( ssGetTNextWasAdjusted ( S , 4 ) != 0 ) { _rtDW
-> nextTime = _ssGetVarNextHitTime ( S , 0 ) ; } if ( _rtDW -> justEnabled !=
0 ) { _rtDW -> justEnabled = 0 ; if ( rtb_B_28_31_0 >= _rtP -> P_52 ) {
rtb_B_28_34_0 = ( rtb_B_28_31_0 - _rtP -> P_52 ) / _rtP -> P_50 ; numCycles =
( uint32_T ) muDoubleScalarFloor ( rtb_B_28_34_0 ) ; if ( muDoubleScalarAbs (
( real_T ) ( numCycles + 1U ) - rtb_B_28_34_0 ) < DBL_EPSILON * rtb_B_28_34_0
) { numCycles ++ ; } _rtDW -> numCompleteCycles = numCycles ; rtb_B_28_34_0 =
( ( real_T ) numCycles * _rtP -> P_50 + _rtP -> P_52 ) + _rtP -> P_51 * _rtP
-> P_50 / 100.0 ; if ( rtb_B_28_31_0 < rtb_B_28_34_0 ) { _rtDW ->
currentValue = 1 ; _rtDW -> nextTime = rtb_B_28_34_0 ; } else { _rtDW ->
currentValue = 0 ; _rtDW -> nextTime = ( real_T ) ( numCycles + 1U ) * _rtP
-> P_50 + _rtP -> P_52 ; } } else { _rtDW -> numCompleteCycles = _rtP -> P_52
!= 0.0 ? - 1 : 0 ; _rtDW -> currentValue = 0 ; _rtDW -> nextTime = _rtP ->
P_52 ; } } else { if ( _rtDW -> nextTime <= rtb_B_28_31_0 ) { if ( _rtDW ->
currentValue == 1 ) { _rtDW -> currentValue = 0 ; _rtDW -> nextTime = (
real_T ) ( _rtDW -> numCompleteCycles + 1LL ) * _rtP -> P_50 + _rtP -> P_52 ;
} else { _rtDW -> numCompleteCycles ++ ; _rtDW -> currentValue = 1 ; _rtDW ->
nextTime = ( _rtP -> P_51 * _rtP -> P_50 * 0.01 + ( real_T ) _rtDW ->
numCompleteCycles * _rtP -> P_50 ) + _rtP -> P_52 ; } } }
_ssSetVarNextHitTime ( S , 0 , _rtDW -> nextTime ) ; if ( _rtDW ->
currentValue == 1 ) { _rtB -> B_28_54_0 = _rtP -> P_49 ; } else { _rtB ->
B_28_54_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ B_28_55_0 = _rtB -> B_28_54_0 ; multiplex_MuestreoyRetencion ( S ,
B_28_55_0 , _rtB -> B_28_53_0 , & _rtB -> MuestreoyRetencion , & _rtDW ->
MuestreoyRetencion , & _rtZCE -> MuestreoyRetencion ) ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_p . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_p .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_53 ; B_28_57_0 = multiplex_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_m .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_m . Last , _rtDW ->
TransportDelay_IWORK_m . Tail , _rtDW -> TransportDelay_IWORK_m . Head , _rtP
-> P_54 , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_28_59_0 = (
int8_T ) ( ( int8_T ) ( B_28_57_0 != 0.0 ) ^ ( int8_T ) _rtB ->
SampleandHold_j . B_3_0_0 ) ; isHit = ssIsSampleHit ( S , 5 , 0 ) ; if (
isHit != 0 ) { rtb_B_28_31_0 = ssGetTaskTime ( S , 5 ) ; if (
ssGetTNextWasAdjusted ( S , 5 ) != 0 ) { _rtDW -> nextTime_i =
_ssGetVarNextHitTime ( S , 1 ) ; } if ( _rtDW -> justEnabled_o != 0 ) { _rtDW
-> justEnabled_o = 0 ; if ( rtb_B_28_31_0 >= _rtP -> P_58 ) { rtb_B_28_34_0 =
( rtb_B_28_31_0 - _rtP -> P_58 ) / _rtP -> P_56 ; numCycles = ( uint32_T )
muDoubleScalarFloor ( rtb_B_28_34_0 ) ; if ( muDoubleScalarAbs ( ( real_T ) (
numCycles + 1U ) - rtb_B_28_34_0 ) < DBL_EPSILON * rtb_B_28_34_0 ) {
numCycles ++ ; } _rtDW -> numCompleteCycles_a = numCycles ; rtb_B_28_34_0 = (
( real_T ) numCycles * _rtP -> P_56 + _rtP -> P_58 ) + _rtP -> P_57 * _rtP ->
P_56 / 100.0 ; if ( rtb_B_28_31_0 < rtb_B_28_34_0 ) { _rtDW -> currentValue_h
= 1 ; _rtDW -> nextTime_i = rtb_B_28_34_0 ; } else { _rtDW -> currentValue_h
= 0 ; _rtDW -> nextTime_i = ( real_T ) ( numCycles + 1U ) * _rtP -> P_56 +
_rtP -> P_58 ; } } else { _rtDW -> numCompleteCycles_a = _rtP -> P_58 != 0.0
? - 1 : 0 ; _rtDW -> currentValue_h = 0 ; _rtDW -> nextTime_i = _rtP -> P_58
; } } else { if ( _rtDW -> nextTime_i <= rtb_B_28_31_0 ) { if ( _rtDW ->
currentValue_h == 1 ) { _rtDW -> currentValue_h = 0 ; _rtDW -> nextTime_i = (
real_T ) ( _rtDW -> numCompleteCycles_a + 1LL ) * _rtP -> P_56 + _rtP -> P_58
; } else { _rtDW -> numCompleteCycles_a ++ ; _rtDW -> currentValue_h = 1 ;
_rtDW -> nextTime_i = ( _rtP -> P_57 * _rtP -> P_56 * 0.01 + ( real_T ) _rtDW
-> numCompleteCycles_a * _rtP -> P_56 ) + _rtP -> P_58 ; } } }
_ssSetVarNextHitTime ( S , 1 , _rtDW -> nextTime_i ) ; if ( _rtDW ->
currentValue_h == 1 ) { _rtB -> B_28_60_0 = _rtP -> P_55 ; } else { _rtB ->
B_28_60_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ B_28_61_0 = _rtB -> B_28_60_0 ; multiplex_MuestreoyRetencion ( S ,
B_28_61_0 , _rtB -> B_28_59_0 , & _rtB -> MuestreoyRetencion_e , & _rtDW ->
MuestreoyRetencion_e , & _rtZCE -> MuestreoyRetencion_e ) ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay12_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay12_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_59 ; if ( _rtP -> P_59 == 0.0 ) B_28_63_0 = _rtB ->
B_28_8_0 ; else B_28_63_0 = multiplex_acc_rt_TDelayInterpolate ( tMinusDelay
, 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay12_IWORK .
CircularBufSize , & _rtDW -> TransportDelay12_IWORK . Last , _rtDW ->
TransportDelay12_IWORK . Tail , _rtDW -> TransportDelay12_IWORK . Head , _rtP
-> P_60 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_28_64_0 =
ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
rtb_B_28_66_0 = ! _rtDW -> Memory_PreviousInput ; if ( _rtB -> SampleandHold
. B_3_0_0 ) { _rtB -> B_28_67_0 = _rtB -> B_28_25_0 ; } else { _rtB ->
B_28_67_0 = _rtB -> B_28_23_0_n ; } _rtB -> B_28_68_0 = _rtB -> B_28_67_0 *
_rtB -> B_28_13_0_c ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_61 ; _rtB ->
B_28_69_0 = multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay2_IWORK . CircularBufSize , &
_rtDW -> TransportDelay2_IWORK . Last , _rtDW -> TransportDelay2_IWORK . Tail
, _rtDW -> TransportDelay2_IWORK . Head , _rtP -> P_62 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_31_0 = _rtB -> B_28_69_0 * _rtB -> B_28_24_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_63 ; _rtB -> B_28_71_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay1_IWORK . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK . Last , _rtDW -> TransportDelay1_IWORK . Tail , _rtDW
-> TransportDelay1_IWORK . Head , _rtP -> P_64 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_34_0 = _rtB -> B_28_71_0 * _rtB -> B_28_26_0_p ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay4_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay4_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_65 ; _rtB -> B_28_73_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay4_IWORK . CircularBufSize , & _rtDW ->
TransportDelay4_IWORK . Last , _rtDW -> TransportDelay4_IWORK . Tail , _rtDW
-> TransportDelay4_IWORK . Head , _rtP -> P_66 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_74_0 = _rtB -> B_28_73_0 * _rtB -> B_28_27_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_67 ; _rtB -> B_28_75_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay3_IWORK . CircularBufSize , & _rtDW ->
TransportDelay3_IWORK . Last , _rtDW -> TransportDelay3_IWORK . Tail , _rtDW
-> TransportDelay3_IWORK . Head , _rtP -> P_68 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_76_0 = _rtB -> B_28_75_0 * _rtB -> B_28_28_0_l ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay6_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay6_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_69 ; _rtB -> B_28_77_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay6_IWORK . CircularBufSize , & _rtDW ->
TransportDelay6_IWORK . Last , _rtDW -> TransportDelay6_IWORK . Tail , _rtDW
-> TransportDelay6_IWORK . Head , _rtP -> P_70 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_78_0 = _rtB -> B_28_77_0 * _rtB -> B_28_29_0_j ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay5_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay5_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_71 ; _rtB -> B_28_79_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay5_IWORK . CircularBufSize , & _rtDW ->
TransportDelay5_IWORK . Last , _rtDW -> TransportDelay5_IWORK . Tail , _rtDW
-> TransportDelay5_IWORK . Head , _rtP -> P_72 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_80_0 = _rtB -> B_28_79_0 * _rtB -> B_28_30_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay8_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay8_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_73 ; _rtB -> B_28_81_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay8_IWORK . CircularBufSize , & _rtDW ->
TransportDelay8_IWORK . Last , _rtDW -> TransportDelay8_IWORK . Tail , _rtDW
-> TransportDelay8_IWORK . Head , _rtP -> P_74 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_82_0 = _rtB -> B_28_81_0 * _rtB -> B_28_31_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay7_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay7_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_75 ; _rtB -> B_28_83_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay7_IWORK . CircularBufSize , & _rtDW ->
TransportDelay7_IWORK . Last , _rtDW -> TransportDelay7_IWORK . Tail , _rtDW
-> TransportDelay7_IWORK . Head , _rtP -> P_76 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_84_0 = _rtB -> B_28_83_0 * _rtB -> B_28_32_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay9_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay9_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_77 ; _rtB -> B_28_85_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay9_IWORK . CircularBufSize , & _rtDW ->
TransportDelay9_IWORK . Last , _rtDW -> TransportDelay9_IWORK . Tail , _rtDW
-> TransportDelay9_IWORK . Head , _rtP -> P_78 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_86_0 = _rtB -> B_28_85_0 * _rtB -> B_28_14_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay11_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay11_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_79 ; _rtB -> B_28_87_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay11_IWORK . CircularBufSize , & _rtDW ->
TransportDelay11_IWORK . Last , _rtDW -> TransportDelay11_IWORK . Tail ,
_rtDW -> TransportDelay11_IWORK . Head , _rtP -> P_80 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_88_0 = _rtB -> B_28_87_0 * _rtB -> B_28_15_0_f ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay10_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay10_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_81 ; _rtB -> B_28_89_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay10_IWORK . CircularBufSize , & _rtDW ->
TransportDelay10_IWORK . Last , _rtDW -> TransportDelay10_IWORK . Tail ,
_rtDW -> TransportDelay10_IWORK . Head , _rtP -> P_82 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_90_0 = _rtB -> B_28_89_0 * _rtB -> B_28_16_0_g ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay13_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay13_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_83 ; B_28_91_0 = multiplex_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay13_IWORK .
CircularBufSize , & _rtDW -> TransportDelay13_IWORK . Last , _rtDW ->
TransportDelay13_IWORK . Tail , _rtDW -> TransportDelay13_IWORK . Head , _rtP
-> P_84 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_28_93_0 = ( (
( ( ( ( ( ( ( ( ( _rtB -> B_28_68_0 + rtb_B_28_31_0 ) + rtb_B_28_34_0 ) +
rtb_B_28_74_0 ) + rtb_B_28_76_0 ) + rtb_B_28_78_0 ) + rtb_B_28_80_0 ) +
rtb_B_28_82_0 ) + rtb_B_28_84_0 ) + rtb_B_28_86_0 ) + rtb_B_28_88_0 ) +
rtb_B_28_90_0 ) + B_28_91_0 * _rtB -> B_28_17_0 ; if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> Switch_Mode = ( _rtB -> B_28_93_0 > _rtP -> P_85 ) ;
_rtDW -> Switch1_Mode = ( _rtB -> B_28_93_0 > _rtP -> P_86 ) ; } if ( _rtDW
-> Switch_Mode ) { rtb_B_28_31_0 = _rtB -> B_28_19_0 ; } else { rtb_B_28_31_0
= _rtB -> B_28_18_0_g ; } if ( _rtDW -> Switch1_Mode ) { rtb_B_28_34_0 = _rtB
-> B_28_22_0 ; } else { rtb_B_28_34_0 = _rtB -> B_28_21_0_m ; } _rtB ->
B_28_96_0 = ( ( rtb_B_28_31_0 != 0.0 ) || ( rtb_B_28_34_0 != 0.0 ) ) ; isHit
= ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { B_28_97_0 = _rtDW ->
Memory_PreviousInput_b ; multiplex_POSITIVEEdge ( S , _rtB -> B_28_38_0 [ 0 ]
, _rtB -> B_28_96_0 , B_28_97_0 , & _rtB -> POSITIVEEdge , & _rtDW ->
POSITIVEEdge ) ; multiplex_NEGATIVEEdge ( S , _rtB -> B_28_38_0 [ 1 ] , _rtB
-> B_28_96_0 , B_28_97_0 , & _rtB -> NEGATIVEEdge , & _rtDW -> NEGATIVEEdge )
; B_28_100_0 = ( _rtB -> POSITIVEEdge . B_6_0_0 || _rtB -> NEGATIVEEdge .
B_5_0_0 ) ; _rtB -> B_28_101_0 = ( rtb_B_28_66_0 && B_28_100_0 ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_103_0 = _rtDW
-> ICic_PreviousInput ; } if ( _rtB -> B_28_101_0 ) { _rtB -> B_28_104_0 =
_rtB -> B_28_64_0 ; } else { _rtB -> B_28_104_0 = _rtB -> B_28_103_0 ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_105_0
= _rtP -> P_88 ; } _rtB -> B_28_106_0 = _rtB -> B_28_104_0 + _rtB ->
B_28_105_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode = ( _rtB ->
B_28_106_0 > _rtB -> B_28_64_0 ) ; } _rtB -> B_28_107_0 = _rtDW ->
RelationalOperator_Mode ; } if ( _rtB -> B_28_107_0 ) { _rtB -> B_28_108_0 =
B_28_63_0 ; } else { _rtB -> B_28_108_0 = _rtB -> B_28_20_0 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S
) != 0 ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE ->
Mensajerecibido_Trig_ZCE , _rtB -> B_28_108_0 ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 2 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Mensajerecibido_SubsysRanBC = 4 ; } } ssCallAccelRunBlock ( S , 28 , 110 ,
SS_CALL_MDL_OUTPUTS ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_h . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_89 ; B_28_111_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK_at . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_at . Last , _rtDW -> TransportDelay_IWORK_at . Tail ,
_rtDW -> TransportDelay_IWORK_at . Head , _rtP -> P_90 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_28_112_0 = _rtP -> P_91 * B_28_111_0 ; { real_T * * uBuffer =
( real_T * * ) & _rtDW -> TransportDelay1_PWORK_m . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_m .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_92 ; B_28_113_0 = multiplex_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay1_IWORK_p
. CircularBufSize , & _rtDW -> TransportDelay1_IWORK_p . Last , _rtDW ->
TransportDelay1_IWORK_p . Tail , _rtDW -> TransportDelay1_IWORK_p . Head ,
_rtP -> P_93 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_28_114_0 =
_rtP -> P_94 * B_28_113_0 ; ssCallAccelRunBlock ( S , 28 , 115 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_28_116_0 = 0.0 ; _rtB -> B_28_116_0 += _rtP
-> P_97 * _rtX -> Filtro_CSTATE [ 5 ] ; { real_T * * uBuffer = ( real_T * * )
& _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 1 ] ;
real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_99 ;
B_28_117_0 = multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_i . CircularBufSize , &
_rtDW -> TransportDelay_IWORK_i . Last , _rtDW -> TransportDelay_IWORK_i .
Tail , _rtDW -> TransportDelay_IWORK_i . Head , _rtP -> P_100 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } rtb_B_28_34_0 = B_28_117_0 + _rtB -> B_28_28_0 ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_b .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK_b . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S )
; real_T tMinusDelay = simTime - _rtP -> P_101 ; B_28_119_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay1_IWORK_h . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_h . Last , _rtDW -> TransportDelay1_IWORK_h . Tail ,
_rtDW -> TransportDelay1_IWORK_h . Head , _rtP -> P_102 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_34_0 *= _rtB -> B_28_5_0_k ; isHit = ssIsSampleHit ( S , 2 , 0
) ; if ( isHit != 0 ) { _rtB -> B_28_126_0 = _rtP -> P_106 * _rtDW ->
NextOutput_k + _rtP -> P_107 ; _rtB -> B_28_127_0 = _rtB -> B_28_126_0 ; }
rtb_B_28_34_0 += _rtB -> B_28_127_0 ; _rtB -> B_28_129_0 = rtb_B_28_34_0 *
_rtB -> B_28_112_0 ; rtb_B_28_31_0 = ( B_28_119_0 + _rtB -> B_28_28_0 ) *
_rtB -> B_28_5_0_k + _rtB -> B_28_127_0 ; _rtB -> B_28_131_0 = _rtB ->
B_28_114_0 * rtb_B_28_31_0 ; _rtB -> B_28_132_0 = _rtB -> B_28_129_0 - _rtB
-> B_28_131_0 ; ssCallAccelRunBlock ( S , 28 , 133 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> B_28_136_0 = muDoubleScalarCos ( _rtX -> ModuloIntegrator_CSTATE_l *
6.2831853071795862 ) ; rtb_B_28_34_0 = rtb_B_28_34_0 * _rtB -> B_28_6_0_c *
_rtB -> B_28_136_0 ; B_28_140_0 = _rtB -> B_28_7_0 * rtb_B_28_34_0 + _rtX ->
Integrator_CSTATE_o ; _rtB -> B_28_143_0 = muDoubleScalarCos ( _rtX ->
ModuloIntegrator_CSTATE_e * 6.2831853071795862 ) ; rtb_B_28_31_0 *= _rtB ->
B_28_143_0 * _rtB -> B_28_6_0_c ; B_28_147_0 = _rtB -> B_28_9_0 *
rtb_B_28_31_0 + _rtX -> Integrator1_CSTATE ; _rtB -> B_28_149_0 = _rtP ->
P_117 * B_28_140_0 + _rtB -> B_28_11_0 ; _rtB -> B_28_151_0 = _rtP -> P_118 *
B_28_147_0 + _rtB -> B_28_12_0 ; _rtB -> B_28_152_0 = rtb_B_28_34_0 * _rtB ->
B_28_8_0_b ; _rtB -> B_28_153_0 = rtb_B_28_31_0 * _rtB -> B_28_10_0_p ; isHit
= ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( _rtB -> B_28_116_0 >
0.0 ) { _rtDW -> Sign3_MODE = 1 ; } else if ( _rtB -> B_28_116_0 < 0.0 ) {
_rtDW -> Sign3_MODE = - 1 ; } else { _rtDW -> Sign3_MODE = 0 ; } _rtB ->
B_28_154_0 = _rtDW -> Sign3_MODE ; } _rtB -> B_28_155_0 = ssGetT ( S ) ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
multiplex_TriggeredSubsystem ( S , B_28_100_0 , _rtB -> B_28_155_0 , & _rtB
-> TriggeredSubsystem , & _rtDW -> TriggeredSubsystem , & _rtZCE ->
TriggeredSubsystem ) ; _rtB -> B_28_157_0 = _rtB -> TriggeredSubsystem .
B_4_0_0 + _rtB -> B_28_33_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode_l = ( _rtB -> B_28_157_0 > _rtB -> B_28_155_0 ) ; } }
if ( ssIsMajorTimeStep ( S ) != 0 ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING
, & _rtZCE -> Integrator_Reset_ZCE_l , _rtB -> B_28_5_0 ) ; if ( zcEvent !=
NO_ZCEVENT ) { _rtX -> Integrator_CSTATE_a = _rtP -> P_119 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } } _rtB -> B_28_159_0 =
_rtX -> Integrator_CSTATE_a ; _rtB -> B_28_160_0 = ssGetT ( S ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_162_0 = ! _rtDW ->
Memory_PreviousInput_k ; } _rtB -> B_28_163_0 = ( _rtB -> B_28_5_0 != 0.0 ) ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { B_28_164_0 = _rtDW
-> Memory_PreviousInput_n ; multiplex_POSITIVEEdge ( S , _rtB -> B_28_47_0_l
[ 0 ] , _rtB -> B_28_163_0 , B_28_164_0 , & _rtB -> POSITIVEEdge_b , & _rtDW
-> POSITIVEEdge_b ) ; multiplex_NEGATIVEEdge ( S , _rtB -> B_28_47_0_l [ 1 ]
, _rtB -> B_28_163_0 , B_28_164_0 , & _rtB -> NEGATIVEEdge_i , & _rtDW ->
NEGATIVEEdge_i ) ; B_28_167_0 = ( _rtB -> POSITIVEEdge_b . B_6_0_0 || _rtB ->
NEGATIVEEdge_i . B_5_0_0 ) ; _rtB -> B_28_168_0 = ( rtb_B_28_162_0 &&
B_28_167_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_28_170_0 = _rtDW -> ICic_PreviousInput_k ; } if ( _rtB ->
B_28_168_0 ) { _rtB -> B_28_171_0 = _rtB -> B_28_160_0 ; } else { _rtB ->
B_28_171_0 = _rtB -> B_28_170_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { _rtB -> B_28_172_0 = _rtP -> P_121 ; } _rtB -> B_28_173_0 =
_rtB -> B_28_171_0 + _rtB -> B_28_172_0 ; isHit = ssIsSampleHit ( S , 1 , 0 )
; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode_o = ( _rtB -> B_28_173_0 > _rtB -> B_28_160_0 ) ; }
_rtB -> B_28_174_0 = _rtDW -> RelationalOperator_Mode_o ; } _rtB ->
B_28_175_0 = _rtB -> B_28_174_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { multiplex_SampleandHold_c ( S , _rtB -> B_28_175_0 , _rtB ->
B_28_159_0 , & _rtB -> SampleandHold_c , & _rtDW -> SampleandHold_c , &
_rtZCE -> SampleandHold_c ) ; _rtB -> B_28_177_0 = muDoubleScalarAbs ( _rtB
-> SampleandHold_c . B_13_0_0 ) ; } _rtB -> B_28_178_0 = ssGetT ( S ) ; isHit
= ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_180_0 = ! _rtDW
-> Memory_PreviousInput_kl ; } _rtB -> B_28_181_0 = ( _rtB -> B_28_5_0 != 0.0
) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { B_28_182_0 =
_rtDW -> Memory_PreviousInput_j ; multiplex_POSITIVEEdge ( S , _rtB ->
B_28_53_0_d [ 0 ] , _rtB -> B_28_181_0 , B_28_182_0 , & _rtB ->
POSITIVEEdge_d , & _rtDW -> POSITIVEEdge_d ) ; multiplex_NEGATIVEEdge ( S ,
_rtB -> B_28_53_0_d [ 1 ] , _rtB -> B_28_181_0 , B_28_182_0 , & _rtB ->
NEGATIVEEdge_k , & _rtDW -> NEGATIVEEdge_k ) ; B_28_185_0 = ( _rtB ->
POSITIVEEdge_d . B_6_0_0 || _rtB -> NEGATIVEEdge_k . B_5_0_0 ) ; _rtB ->
B_28_186_0 = ( rtb_B_28_180_0 && B_28_185_0 ) ; } isHit = ssIsSampleHit ( S ,
1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_188_0 = _rtDW ->
ICic_PreviousInput_p ; } if ( _rtB -> B_28_186_0 ) { _rtB -> B_28_189_0 =
_rtB -> B_28_178_0 ; } else { _rtB -> B_28_189_0 = _rtB -> B_28_188_0 ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_190_0
= _rtP -> P_123 ; } _rtB -> B_28_191_0 = _rtB -> B_28_189_0 + _rtB ->
B_28_190_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode_b = ( _rtB
-> B_28_191_0 > _rtB -> B_28_178_0 ) ; } _rtB -> B_28_192_0 = _rtDW ->
RelationalOperator_Mode_b ; } if ( ssIsMajorTimeStep ( S ) != 0 ) {
rtb_B_28_180_0 = ( ( ! _rtB -> B_28_192_0 ) && ( _rtZCE ->
Integrator1_Reset_ZCE != ZERO_ZCSIG ) ) ; _rtZCE -> Integrator1_Reset_ZCE =
_rtB -> B_28_192_0 ; if ( rtb_B_28_180_0 ) { _rtX -> Integrator1_CSTATE_c =
_rtP -> P_124 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } } _rtB
-> B_28_193_0 = _rtX -> Integrator1_CSTATE_c ; if ( ssIsMajorTimeStep ( S )
!= 0 ) { _rtDW -> Abs1_MODE = ( _rtB -> B_28_193_0 >= 0.0 ) ; } _rtB ->
B_28_195_0 = _rtB -> B_28_177_0 - ( _rtDW -> Abs1_MODE > 0 ? _rtB ->
B_28_193_0 : - _rtB -> B_28_193_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { multiplex_SampleandHold1 ( S , _rtB -> B_28_5_0 , _rtB ->
B_28_195_0 , & _rtB -> SampleandHold1 , & _rtDW -> SampleandHold1 , & _rtZCE
-> SampleandHold1 ) ; ssCallAccelRunBlock ( S , 28 , 197 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_28_199_0 = _rtP -> P_125 * _rtB ->
SampleandHold1 . B_14_0_0 + _rtB -> B_28_41_0 ; } _rtB -> B_28_200_0 = ssGetT
( S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
multiplex_TriggeredSubsystem ( S , B_28_167_0 , _rtB -> B_28_200_0 , & _rtB
-> TriggeredSubsystem_f , & _rtDW -> TriggeredSubsystem_f , & _rtZCE ->
TriggeredSubsystem_f ) ; _rtB -> B_28_202_0 = _rtB -> TriggeredSubsystem_f .
B_4_0_0 + _rtB -> B_28_42_0_g ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW
-> RelationalOperator_Mode_by = ( _rtB -> B_28_202_0 > _rtB -> B_28_200_0 ) ;
} } _rtB -> B_28_204_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { multiplex_TriggeredSubsystem ( S , B_28_185_0 , _rtB ->
B_28_204_0 , & _rtB -> TriggeredSubsystem_p , & _rtDW -> TriggeredSubsystem_p
, & _rtZCE -> TriggeredSubsystem_p ) ; _rtB -> B_28_206_0 = _rtB ->
TriggeredSubsystem_p . B_4_0_0 + _rtB -> B_28_48_0_d ; if ( ssIsMajorTimeStep
( S ) != 0 ) { _rtDW -> RelationalOperator_Mode_n = ( _rtB -> B_28_206_0 >
_rtB -> B_28_204_0 ) ; } } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay12_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay12_PWORK_m . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_126 ; if (
_rtP -> P_126 == 0.0 ) B_28_208_0 = _rtB -> B_28_18_0 ; else B_28_208_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay12_IWORK_f . CircularBufSize , & _rtDW ->
TransportDelay12_IWORK_f . Last , _rtDW -> TransportDelay12_IWORK_f . Tail ,
_rtDW -> TransportDelay12_IWORK_f . Head , _rtP -> P_127 , 0 , ( boolean_T )
( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) )
) ) ; } _rtB -> B_28_209_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 , 0
) ; if ( isHit != 0 ) { rtb_B_28_211_0 = ! _rtDW -> Memory_PreviousInput_h ;
if ( _rtB -> SampleandHold_j . B_3_0_0 ) { _rtB -> B_28_212_0 = _rtB ->
B_28_75_0_e ; } else { _rtB -> B_28_212_0 = _rtB -> B_28_73_0_d ; } _rtB ->
B_28_213_0 = _rtB -> B_28_212_0 * _rtB -> B_28_63_0 ; } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay2_PWORK_m . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay2_PWORK_m .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_128 ; _rtB -> B_28_214_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay2_IWORK_j . CircularBufSize , & _rtDW ->
TransportDelay2_IWORK_j . Last , _rtDW -> TransportDelay2_IWORK_j . Tail ,
_rtDW -> TransportDelay2_IWORK_j . Head , _rtP -> P_129 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_31_0 = _rtB -> B_28_214_0 * _rtB -> B_28_74_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_l . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_l
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_130 ; _rtB -> B_28_216_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay1_IWORK_e . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_e . Last , _rtDW -> TransportDelay1_IWORK_e . Tail ,
_rtDW -> TransportDelay1_IWORK_e . Head , _rtP -> P_131 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_34_0 = _rtB -> B_28_216_0 * _rtB -> B_28_76_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay4_PWORK_b . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay4_PWORK_b
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_132 ; _rtB -> B_28_218_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay4_IWORK_h . CircularBufSize , & _rtDW ->
TransportDelay4_IWORK_h . Last , _rtDW -> TransportDelay4_IWORK_h . Tail ,
_rtDW -> TransportDelay4_IWORK_h . Head , _rtP -> P_133 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_74_0 = _rtB -> B_28_218_0 * _rtB -> B_28_77_0_b ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK_n . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK_n
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_134 ; _rtB -> B_28_220_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay3_IWORK_e . CircularBufSize , & _rtDW ->
TransportDelay3_IWORK_e . Last , _rtDW -> TransportDelay3_IWORK_e . Tail ,
_rtDW -> TransportDelay3_IWORK_e . Head , _rtP -> P_135 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_76_0 = _rtB -> B_28_220_0 * _rtB -> B_28_78_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay6_PWORK_f . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay6_PWORK_f
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_136 ; _rtB -> B_28_222_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay6_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay6_IWORK_a . Last , _rtDW -> TransportDelay6_IWORK_a . Tail ,
_rtDW -> TransportDelay6_IWORK_a . Head , _rtP -> P_137 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_78_0 = _rtB -> B_28_222_0 * _rtB -> B_28_79_0_j ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay5_PWORK_h . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay5_PWORK_h
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_138 ; _rtB -> B_28_224_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay5_IWORK_l . CircularBufSize , & _rtDW ->
TransportDelay5_IWORK_l . Last , _rtDW -> TransportDelay5_IWORK_l . Tail ,
_rtDW -> TransportDelay5_IWORK_l . Head , _rtP -> P_139 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_80_0 = _rtB -> B_28_224_0 * _rtB -> B_28_80_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay8_PWORK_g . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay8_PWORK_g
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_140 ; _rtB -> B_28_226_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay8_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay8_IWORK_a . Last , _rtDW -> TransportDelay8_IWORK_a . Tail ,
_rtDW -> TransportDelay8_IWORK_a . Head , _rtP -> P_141 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_82_0 = _rtB -> B_28_226_0 * _rtB -> B_28_81_0_f ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay7_PWORK_b . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay7_PWORK_b
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_142 ; _rtB -> B_28_228_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay7_IWORK_d . CircularBufSize , & _rtDW ->
TransportDelay7_IWORK_d . Last , _rtDW -> TransportDelay7_IWORK_d . Tail ,
_rtDW -> TransportDelay7_IWORK_d . Head , _rtP -> P_143 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_84_0 = _rtB -> B_28_228_0 * _rtB -> B_28_82_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay9_PWORK_k . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay9_PWORK_k
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_144 ; _rtB -> B_28_230_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay9_IWORK_e . CircularBufSize , & _rtDW ->
TransportDelay9_IWORK_e . Last , _rtDW -> TransportDelay9_IWORK_e . Tail ,
_rtDW -> TransportDelay9_IWORK_e . Head , _rtP -> P_145 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } rtb_B_28_86_0 = _rtB -> B_28_230_0 * _rtB -> B_28_64_0_n ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay11_PWORK_h . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay11_PWORK_h
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_146 ; _rtB -> B_28_232_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay11_IWORK_c . CircularBufSize , & _rtDW ->
TransportDelay11_IWORK_c . Last , _rtDW -> TransportDelay11_IWORK_c . Tail ,
_rtDW -> TransportDelay11_IWORK_c . Head , _rtP -> P_147 , 0 , ( boolean_T )
( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) )
) ) ; } rtb_B_28_88_0 = _rtB -> B_28_232_0 * _rtB -> B_28_65_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay10_PWORK_l . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay10_PWORK_l
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_148 ; _rtB -> B_28_234_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay10_IWORK_o . CircularBufSize , & _rtDW ->
TransportDelay10_IWORK_o . Last , _rtDW -> TransportDelay10_IWORK_o . Tail ,
_rtDW -> TransportDelay10_IWORK_o . Head , _rtP -> P_149 , 0 , ( boolean_T )
( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) )
) ) ; } rtb_B_28_90_0 = _rtB -> B_28_234_0 * _rtB -> B_28_66_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay13_PWORK_j . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay13_PWORK_j
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_150 ; B_28_236_0 = multiplex_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay13_IWORK_m
. CircularBufSize , & _rtDW -> TransportDelay13_IWORK_m . Last , _rtDW ->
TransportDelay13_IWORK_m . Tail , _rtDW -> TransportDelay13_IWORK_m . Head ,
_rtP -> P_151 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_28_238_0 = (
( ( ( ( ( ( ( ( ( ( _rtB -> B_28_213_0 + rtb_B_28_31_0 ) + rtb_B_28_34_0 ) +
rtb_B_28_74_0 ) + rtb_B_28_76_0 ) + rtb_B_28_78_0 ) + rtb_B_28_80_0 ) +
rtb_B_28_82_0 ) + rtb_B_28_84_0 ) + rtb_B_28_86_0 ) + rtb_B_28_88_0 ) +
rtb_B_28_90_0 ) + B_28_236_0 * _rtB -> B_28_67_0_b ; if ( ssIsMajorTimeStep (
S ) != 0 ) { _rtDW -> Switch_Mode_m = ( _rtB -> B_28_238_0 > _rtP -> P_152 )
; _rtDW -> Switch1_Mode_a = ( _rtB -> B_28_238_0 > _rtP -> P_153 ) ; } if (
_rtDW -> Switch_Mode_m ) { rtb_B_28_31_0 = _rtB -> B_28_69_0_h ; } else {
rtb_B_28_31_0 = _rtB -> B_28_68_0_l ; } if ( _rtDW -> Switch1_Mode_a ) {
rtb_B_28_34_0 = _rtB -> B_28_72_0 ; } else { rtb_B_28_34_0 = _rtB ->
B_28_71_0_b ; } _rtB -> B_28_241_0 = ( ( rtb_B_28_31_0 != 0.0 ) || (
rtb_B_28_34_0 != 0.0 ) ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { B_28_242_0 = _rtDW -> Memory_PreviousInput_e ;
multiplex_POSITIVEEdge ( S , _rtB -> B_28_88_0 [ 0 ] , _rtB -> B_28_241_0 ,
B_28_242_0 , & _rtB -> POSITIVEEdge_p , & _rtDW -> POSITIVEEdge_p ) ;
multiplex_NEGATIVEEdge ( S , _rtB -> B_28_88_0 [ 1 ] , _rtB -> B_28_241_0 ,
B_28_242_0 , & _rtB -> NEGATIVEEdge_kl , & _rtDW -> NEGATIVEEdge_kl ) ;
B_28_245_0 = ( _rtB -> POSITIVEEdge_p . B_6_0_0 || _rtB -> NEGATIVEEdge_kl .
B_5_0_0 ) ; _rtB -> B_28_246_0 = ( rtb_B_28_211_0 && B_28_245_0 ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_248_0 = _rtDW
-> ICic_PreviousInput_i ; } if ( _rtB -> B_28_246_0 ) { _rtB -> B_28_249_0 =
_rtB -> B_28_209_0 ; } else { _rtB -> B_28_249_0 = _rtB -> B_28_248_0 ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_250_0
= _rtP -> P_155 ; } _rtB -> B_28_251_0 = _rtB -> B_28_249_0 + _rtB ->
B_28_250_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode_j = ( _rtB
-> B_28_251_0 > _rtB -> B_28_209_0 ) ; } _rtB -> B_28_252_0 = _rtDW ->
RelationalOperator_Mode_j ; } if ( _rtB -> B_28_252_0 ) { _rtB -> B_28_253_0
= B_28_208_0 ; } else { _rtB -> B_28_253_0 = _rtB -> B_28_70_0 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S
) != 0 ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE ->
Mensajerecibido2_Trig_ZCE , _rtB -> B_28_253_0 ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 15 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Mensajerecibido2_SubsysRanBC = 4 ; } } ssCallAccelRunBlock ( S , 28 , 255 ,
SS_CALL_MDL_OUTPUTS ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_cv . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_cv . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_156 ;
B_28_256_0 = multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_k . CircularBufSize , &
_rtDW -> TransportDelay_IWORK_k . Last , _rtDW -> TransportDelay_IWORK_k .
Tail , _rtDW -> TransportDelay_IWORK_k . Head , _rtP -> P_157 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } _rtB -> B_28_257_0 = _rtP -> P_158 * B_28_256_0 ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_i .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK_i . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S )
; real_T tMinusDelay = simTime - _rtP -> P_159 ; B_28_258_0 =
multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay1_IWORK_i . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_i . Last , _rtDW -> TransportDelay1_IWORK_i . Tail ,
_rtDW -> TransportDelay1_IWORK_i . Head , _rtP -> P_160 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_28_259_0 = _rtP -> P_161 * B_28_258_0 ; ssCallAccelRunBlock (
S , 28 , 260 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_28_261_0 = 0.0 ; _rtB ->
B_28_261_0 += _rtP -> P_164 * _rtX -> Filtro_CSTATE_b [ 5 ] ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c5 . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c5
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_166 ; B_28_262_0 = multiplex_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_gq
. CircularBufSize , & _rtDW -> TransportDelay_IWORK_gq . Last , _rtDW ->
TransportDelay_IWORK_gq . Tail , _rtDW -> TransportDelay_IWORK_gq . Head ,
_rtP -> P_167 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } rtb_B_28_34_0 =
B_28_262_0 + _rtB -> B_28_29_0 ; { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay1_PWORK_mk . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> TransportDelay1_PWORK_mk . TUbufferPtrs [ 1 ] ;
real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_168
; B_28_264_0 = multiplex_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay1_IWORK_b . CircularBufSize , &
_rtDW -> TransportDelay1_IWORK_b . Last , _rtDW -> TransportDelay1_IWORK_b .
Tail , _rtDW -> TransportDelay1_IWORK_b . Head , _rtP -> P_169 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } rtb_B_28_34_0 *= _rtB -> B_28_55_0 ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_271_0 = _rtP
-> P_173 * _rtDW -> NextOutput_c + _rtP -> P_174 ; _rtB -> B_28_272_0 = _rtB
-> B_28_271_0 ; } rtb_B_28_34_0 += _rtB -> B_28_272_0 ; _rtB -> B_28_274_0 =
rtb_B_28_34_0 * _rtB -> B_28_257_0 ; rtb_B_28_31_0 = ( B_28_264_0 + _rtB ->
B_28_29_0 ) * _rtB -> B_28_55_0 + _rtB -> B_28_272_0 ; _rtB -> B_28_276_0 =
_rtB -> B_28_259_0 * rtb_B_28_31_0 ; _rtB -> B_28_277_0 = _rtB -> B_28_274_0
- _rtB -> B_28_276_0 ; ssCallAccelRunBlock ( S , 28 , 278 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_28_281_0 = muDoubleScalarCos ( _rtX ->
ModuloIntegrator_CSTATE_c * 6.2831853071795862 ) ; rtb_B_28_34_0 =
rtb_B_28_34_0 * _rtB -> B_28_56_0 * _rtB -> B_28_281_0 ; B_28_285_0 = _rtB ->
B_28_57_0 * rtb_B_28_34_0 + _rtX -> Integrator_CSTATE_jg ; _rtB -> B_28_288_0
= muDoubleScalarCos ( _rtX -> ModuloIntegrator_CSTATE_a * 6.2831853071795862
) ; rtb_B_28_31_0 *= _rtB -> B_28_288_0 * _rtB -> B_28_56_0 ; B_28_292_0 =
_rtB -> B_28_59_0_o * rtb_B_28_31_0 + _rtX -> Integrator1_CSTATE_cy ; _rtB ->
B_28_294_0 = _rtP -> P_184 * B_28_285_0 + _rtB -> B_28_61_0 ; _rtB ->
B_28_296_0 = _rtP -> P_185 * B_28_292_0 + _rtB -> B_28_62_0 ; _rtB ->
B_28_297_0 = rtb_B_28_34_0 * _rtB -> B_28_58_0 ; _rtB -> B_28_298_0 =
rtb_B_28_31_0 * _rtB -> B_28_60_0_b ; isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { if ( _rtB -> B_28_261_0 > 0.0 ) { _rtDW -> Sign3_MODE_e =
1 ; } else if ( _rtB -> B_28_261_0 < 0.0 ) { _rtDW -> Sign3_MODE_e = - 1 ; }
else { _rtDW -> Sign3_MODE_e = 0 ; } _rtB -> B_28_299_0 = _rtDW ->
Sign3_MODE_e ; } _rtB -> B_28_300_0 = ssGetT ( S ) ; isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { multiplex_TriggeredSubsystem ( S ,
B_28_245_0 , _rtB -> B_28_300_0 , & _rtB -> TriggeredSubsystem_m , & _rtDW ->
TriggeredSubsystem_m , & _rtZCE -> TriggeredSubsystem_m ) ; _rtB ->
B_28_302_0 = _rtB -> TriggeredSubsystem_m . B_4_0_0 + _rtB -> B_28_83_0_a ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode_d = (
_rtB -> B_28_302_0 > _rtB -> B_28_300_0 ) ; } } if ( ssIsMajorTimeStep ( S )
!= 0 ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE ->
Integrator_Reset_ZCE_h , _rtB -> B_28_15_0 ) ; if ( zcEvent != NO_ZCEVENT ) {
_rtX -> Integrator_CSTATE_om = _rtP -> P_186 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } } _rtB -> B_28_304_0 =
_rtX -> Integrator_CSTATE_om ; _rtB -> B_28_305_0 = ssGetT ( S ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_307_0 = ! _rtDW ->
Memory_PreviousInput_jr ; } _rtB -> B_28_308_0 = ( _rtB -> B_28_15_0 != 0.0 )
; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { B_28_309_0 =
_rtDW -> Memory_PreviousInput_l ; multiplex_POSITIVEEdge ( S , _rtB ->
B_28_97_0 [ 0 ] , _rtB -> B_28_308_0 , B_28_309_0 , & _rtB -> POSITIVEEdge_m
, & _rtDW -> POSITIVEEdge_m ) ; multiplex_NEGATIVEEdge ( S , _rtB ->
B_28_97_0 [ 1 ] , _rtB -> B_28_308_0 , B_28_309_0 , & _rtB -> NEGATIVEEdge_g
, & _rtDW -> NEGATIVEEdge_g ) ; B_28_312_0 = ( _rtB -> POSITIVEEdge_m .
B_6_0_0 || _rtB -> NEGATIVEEdge_g . B_5_0_0 ) ; _rtB -> B_28_313_0 = (
rtb_B_28_307_0 && B_28_312_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_28_315_0 = _rtDW -> ICic_PreviousInput_c ; } if (
_rtB -> B_28_313_0 ) { _rtB -> B_28_316_0 = _rtB -> B_28_305_0 ; } else {
_rtB -> B_28_316_0 = _rtB -> B_28_315_0 ; } isHit = ssIsSampleHit ( S , 1 , 0
) ; if ( isHit != 0 ) { _rtB -> B_28_317_0 = _rtP -> P_188 ; } _rtB ->
B_28_318_0 = _rtB -> B_28_316_0 + _rtB -> B_28_317_0 ; isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) {
_rtDW -> RelationalOperator_Mode_d2 = ( _rtB -> B_28_318_0 > _rtB ->
B_28_305_0 ) ; } _rtB -> B_28_319_0 = _rtDW -> RelationalOperator_Mode_d2 ; }
_rtB -> B_28_320_0 = _rtB -> B_28_319_0 ; isHit = ssIsSampleHit ( S , 1 , 0 )
; if ( isHit != 0 ) { multiplex_SampleandHold_c ( S , _rtB -> B_28_320_0 ,
_rtB -> B_28_304_0 , & _rtB -> SampleandHold_i , & _rtDW -> SampleandHold_i ,
& _rtZCE -> SampleandHold_i ) ; _rtB -> B_28_322_0 = muDoubleScalarAbs ( _rtB
-> SampleandHold_i . B_13_0_0 ) ; } _rtB -> B_28_323_0 = ssGetT ( S ) ; isHit
= ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_28_325_0 = ! _rtDW
-> Memory_PreviousInput_a ; } _rtB -> B_28_326_0 = ( _rtB -> B_28_15_0 != 0.0
) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { B_28_327_0 =
_rtDW -> Memory_PreviousInput_bb ; multiplex_POSITIVEEdge ( S , _rtB ->
B_28_103_0_j [ 0 ] , _rtB -> B_28_326_0 , B_28_327_0 , & _rtB ->
POSITIVEEdge_o , & _rtDW -> POSITIVEEdge_o ) ; multiplex_NEGATIVEEdge ( S ,
_rtB -> B_28_103_0_j [ 1 ] , _rtB -> B_28_326_0 , B_28_327_0 , & _rtB ->
NEGATIVEEdge_a , & _rtDW -> NEGATIVEEdge_a ) ; B_28_330_0 = ( _rtB ->
POSITIVEEdge_o . B_6_0_0 || _rtB -> NEGATIVEEdge_a . B_5_0_0 ) ; _rtB ->
B_28_331_0 = ( rtb_B_28_325_0 && B_28_330_0 ) ; } isHit = ssIsSampleHit ( S ,
1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_333_0 = _rtDW ->
ICic_PreviousInput_cq ; } if ( _rtB -> B_28_331_0 ) { _rtB -> B_28_334_0 =
_rtB -> B_28_323_0 ; } else { _rtB -> B_28_334_0 = _rtB -> B_28_333_0 ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_28_335_0
= _rtP -> P_190 ; } _rtB -> B_28_336_0 = _rtB -> B_28_334_0 + _rtB ->
B_28_335_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode_k = ( _rtB
-> B_28_336_0 > _rtB -> B_28_323_0 ) ; } _rtB -> B_28_337_0 = _rtDW ->
RelationalOperator_Mode_k ; } if ( ssIsMajorTimeStep ( S ) != 0 ) {
rtb_B_28_180_0 = ( ( ! _rtB -> B_28_337_0 ) && ( _rtZCE ->
Integrator1_Reset_ZCE_i != ZERO_ZCSIG ) ) ; _rtZCE -> Integrator1_Reset_ZCE_i
= _rtB -> B_28_337_0 ; if ( rtb_B_28_180_0 ) { _rtX -> Integrator1_CSTATE_e =
_rtP -> P_191 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } } _rtB
-> B_28_338_0 = _rtX -> Integrator1_CSTATE_e ; if ( ssIsMajorTimeStep ( S )
!= 0 ) { _rtDW -> Abs1_MODE_c = ( _rtB -> B_28_338_0 >= 0.0 ) ; } _rtB ->
B_28_340_0 = _rtB -> B_28_322_0 - ( _rtDW -> Abs1_MODE_c > 0 ? _rtB ->
B_28_338_0 : - _rtB -> B_28_338_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { multiplex_SampleandHold1 ( S , _rtB -> B_28_15_0 , _rtB
-> B_28_340_0 , & _rtB -> SampleandHold1_l , & _rtDW -> SampleandHold1_l , &
_rtZCE -> SampleandHold1_l ) ; ssCallAccelRunBlock ( S , 28 , 342 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_28_344_0 = _rtP -> P_192 * _rtB ->
SampleandHold1_l . B_14_0_0 + _rtB -> B_28_91_0 ; } _rtB -> B_28_345_0 =
ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
multiplex_TriggeredSubsystem ( S , B_28_312_0 , _rtB -> B_28_345_0 , & _rtB
-> TriggeredSubsystem_c , & _rtDW -> TriggeredSubsystem_c , & _rtZCE ->
TriggeredSubsystem_c ) ; _rtB -> B_28_347_0 = _rtB -> TriggeredSubsystem_c .
B_4_0_0 + _rtB -> B_28_92_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode_g = ( _rtB -> B_28_347_0 > _rtB -> B_28_345_0 ) ; } }
_rtB -> B_28_349_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { multiplex_TriggeredSubsystem ( S , B_28_330_0 , _rtB ->
B_28_349_0 , & _rtB -> TriggeredSubsystem_mf , & _rtDW ->
TriggeredSubsystem_mf , & _rtZCE -> TriggeredSubsystem_mf ) ; _rtB ->
B_28_351_0 = _rtB -> TriggeredSubsystem_mf . B_4_0_0 + _rtB -> B_28_98_0 ; if
( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode_du = (
_rtB -> B_28_351_0 > _rtB -> B_28_349_0 ) ; } } UNUSED_PARAMETER ( tid ) ; }
static void mdlOutputsTID6 ( SimStruct * S , int_T tid ) { B_multiplex_T *
_rtB ; P_multiplex_T * _rtP ; _rtP = ( ( P_multiplex_T * ) ssGetModelRtp ( S
) ) ; _rtB = ( ( B_multiplex_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB ->
B_28_0_0_m = _rtP -> P_193 ; _rtB -> B_28_1_0 = _rtP -> P_194 ; _rtB ->
B_28_2_0 = _rtP -> P_195 ; _rtB -> B_28_3_0_c = _rtP -> P_196 ; _rtB ->
B_28_4_0 = _rtP -> P_197 ; _rtB -> B_28_5_0_k = _rtP -> P_198 ; _rtB ->
B_28_6_0_c = _rtP -> P_199 ; _rtB -> B_28_7_0 = _rtP -> P_200 ; _rtB ->
B_28_8_0_b = _rtP -> P_201 ; _rtB -> B_28_9_0 = _rtP -> P_202 ; _rtB ->
B_28_10_0_p = _rtP -> P_203 ; _rtB -> B_28_11_0 = _rtP -> P_204 ; _rtB ->
B_28_12_0 = _rtP -> P_205 ; _rtB -> B_28_13_0_c = _rtP -> P_206 ; _rtB ->
B_28_14_0 = _rtP -> P_207 ; _rtB -> B_28_15_0_f = _rtP -> P_208 ; _rtB ->
B_28_16_0_g = _rtP -> P_209 ; _rtB -> B_28_17_0 = _rtP -> P_210 ; _rtB ->
B_28_18_0_g = _rtP -> P_211 ; _rtB -> B_28_19_0 = _rtP -> P_212 ; _rtB ->
B_28_20_0 = _rtP -> P_213 ; _rtB -> B_28_21_0_m = _rtP -> P_214 ; _rtB ->
B_28_22_0 = _rtP -> P_215 ; _rtB -> B_28_23_0_n = _rtP -> P_216 ; _rtB ->
B_28_24_0 = _rtP -> P_217 ; _rtB -> B_28_25_0 = _rtP -> P_218 ; _rtB ->
B_28_26_0_p = _rtP -> P_219 ; _rtB -> B_28_27_0 = _rtP -> P_220 ; _rtB ->
B_28_28_0_l = _rtP -> P_221 ; _rtB -> B_28_29_0_j = _rtP -> P_222 ; _rtB ->
B_28_30_0 = _rtP -> P_223 ; _rtB -> B_28_31_0 = _rtP -> P_224 ; _rtB ->
B_28_32_0 = _rtP -> P_225 ; _rtB -> B_28_33_0 = _rtP -> P_226 ; switch ( (
int32_T ) _rtP -> P_227 ) { case 1 : _rtB -> B_28_38_0 [ 0 ] = _rtP -> P_228
[ 0 ] ; _rtB -> B_28_38_0 [ 1 ] = _rtP -> P_228 [ 1 ] ; break ; case 2 : _rtB
-> B_28_38_0 [ 0 ] = _rtP -> P_229 [ 0 ] ; _rtB -> B_28_38_0 [ 1 ] = _rtP ->
P_229 [ 1 ] ; break ; default : _rtB -> B_28_38_0 [ 0 ] = _rtP -> P_230 [ 0 ]
; _rtB -> B_28_38_0 [ 1 ] = _rtP -> P_230 [ 1 ] ; break ; } _rtB ->
B_28_39_0_d = _rtP -> P_231 ; _rtB -> B_28_40_0 = _rtP -> P_232 ; _rtB ->
B_28_41_0 = _rtP -> P_233 ; _rtB -> B_28_42_0_g = _rtP -> P_234 ; switch ( (
int32_T ) _rtP -> P_235 ) { case 1 : _rtB -> B_28_47_0_l [ 0 ] = _rtP ->
P_236 [ 0 ] ; _rtB -> B_28_47_0_l [ 1 ] = _rtP -> P_236 [ 1 ] ; break ; case
2 : _rtB -> B_28_47_0_l [ 0 ] = _rtP -> P_237 [ 0 ] ; _rtB -> B_28_47_0_l [ 1
] = _rtP -> P_237 [ 1 ] ; break ; default : _rtB -> B_28_47_0_l [ 0 ] = _rtP
-> P_238 [ 0 ] ; _rtB -> B_28_47_0_l [ 1 ] = _rtP -> P_238 [ 1 ] ; break ; }
_rtB -> B_28_48_0_d = _rtP -> P_239 ; switch ( ( int32_T ) _rtP -> P_240 ) {
case 1 : _rtB -> B_28_53_0_d [ 0 ] = _rtP -> P_241 [ 0 ] ; _rtB ->
B_28_53_0_d [ 1 ] = _rtP -> P_241 [ 1 ] ; break ; case 2 : _rtB ->
B_28_53_0_d [ 0 ] = _rtP -> P_242 [ 0 ] ; _rtB -> B_28_53_0_d [ 1 ] = _rtP ->
P_242 [ 1 ] ; break ; default : _rtB -> B_28_53_0_d [ 0 ] = _rtP -> P_243 [ 0
] ; _rtB -> B_28_53_0_d [ 1 ] = _rtP -> P_243 [ 1 ] ; break ; } _rtB ->
B_28_54_0_l = _rtP -> P_244 ; _rtB -> B_28_55_0 = _rtP -> P_245 ; _rtB ->
B_28_56_0 = _rtP -> P_246 ; _rtB -> B_28_57_0 = _rtP -> P_247 ; _rtB ->
B_28_58_0 = _rtP -> P_248 ; _rtB -> B_28_59_0_o = _rtP -> P_249 ; _rtB ->
B_28_60_0_b = _rtP -> P_250 ; _rtB -> B_28_61_0 = _rtP -> P_251 ; _rtB ->
B_28_62_0 = _rtP -> P_252 ; _rtB -> B_28_63_0 = _rtP -> P_253 ; _rtB ->
B_28_64_0_n = _rtP -> P_254 ; _rtB -> B_28_65_0 = _rtP -> P_255 ; _rtB ->
B_28_66_0 = _rtP -> P_256 ; _rtB -> B_28_67_0_b = _rtP -> P_257 ; _rtB ->
B_28_68_0_l = _rtP -> P_258 ; _rtB -> B_28_69_0_h = _rtP -> P_259 ; _rtB ->
B_28_70_0 = _rtP -> P_260 ; _rtB -> B_28_71_0_b = _rtP -> P_261 ; _rtB ->
B_28_72_0 = _rtP -> P_262 ; _rtB -> B_28_73_0_d = _rtP -> P_263 ; _rtB ->
B_28_74_0 = _rtP -> P_264 ; _rtB -> B_28_75_0_e = _rtP -> P_265 ; _rtB ->
B_28_76_0 = _rtP -> P_266 ; _rtB -> B_28_77_0_b = _rtP -> P_267 ; _rtB ->
B_28_78_0 = _rtP -> P_268 ; _rtB -> B_28_79_0_j = _rtP -> P_269 ; _rtB ->
B_28_80_0 = _rtP -> P_270 ; _rtB -> B_28_81_0_f = _rtP -> P_271 ; _rtB ->
B_28_82_0 = _rtP -> P_272 ; _rtB -> B_28_83_0_a = _rtP -> P_273 ; switch ( (
int32_T ) _rtP -> P_274 ) { case 1 : _rtB -> B_28_88_0 [ 0 ] = _rtP -> P_275
[ 0 ] ; _rtB -> B_28_88_0 [ 1 ] = _rtP -> P_275 [ 1 ] ; break ; case 2 : _rtB
-> B_28_88_0 [ 0 ] = _rtP -> P_276 [ 0 ] ; _rtB -> B_28_88_0 [ 1 ] = _rtP ->
P_276 [ 1 ] ; break ; default : _rtB -> B_28_88_0 [ 0 ] = _rtP -> P_277 [ 0 ]
; _rtB -> B_28_88_0 [ 1 ] = _rtP -> P_277 [ 1 ] ; break ; } _rtB ->
B_28_89_0_j = _rtP -> P_278 ; _rtB -> B_28_90_0 = _rtP -> P_279 ; _rtB ->
B_28_91_0 = _rtP -> P_280 ; _rtB -> B_28_92_0 = _rtP -> P_281 ; switch ( (
int32_T ) _rtP -> P_282 ) { case 1 : _rtB -> B_28_97_0 [ 0 ] = _rtP -> P_283
[ 0 ] ; _rtB -> B_28_97_0 [ 1 ] = _rtP -> P_283 [ 1 ] ; break ; case 2 : _rtB
-> B_28_97_0 [ 0 ] = _rtP -> P_284 [ 0 ] ; _rtB -> B_28_97_0 [ 1 ] = _rtP ->
P_284 [ 1 ] ; break ; default : _rtB -> B_28_97_0 [ 0 ] = _rtP -> P_285 [ 0 ]
; _rtB -> B_28_97_0 [ 1 ] = _rtP -> P_285 [ 1 ] ; break ; } _rtB -> B_28_98_0
= _rtP -> P_286 ; switch ( ( int32_T ) _rtP -> P_287 ) { case 1 : _rtB ->
B_28_103_0_j [ 0 ] = _rtP -> P_288 [ 0 ] ; _rtB -> B_28_103_0_j [ 1 ] = _rtP
-> P_288 [ 1 ] ; break ; case 2 : _rtB -> B_28_103_0_j [ 0 ] = _rtP -> P_289
[ 0 ] ; _rtB -> B_28_103_0_j [ 1 ] = _rtP -> P_289 [ 1 ] ; break ; default :
_rtB -> B_28_103_0_j [ 0 ] = _rtP -> P_290 [ 0 ] ; _rtB -> B_28_103_0_j [ 1 ]
= _rtP -> P_290 [ 1 ] ; break ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { int32_T isHit ;
B_multiplex_T * _rtB ; P_multiplex_T * _rtP ; DW_multiplex_T * _rtDW ; _rtDW
= ( ( DW_multiplex_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( P_multiplex_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_multiplex_T * ) _ssGetModelBlockIO ( S
) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK .
Head < ( _rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay_IWORK
. CircularBufSize , & _rtDW -> TransportDelay_IWORK . Tail , & _rtDW ->
TransportDelay_IWORK . Head , & _rtDW -> TransportDelay_IWORK . Last ,
simTime - _rtP -> P_0 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay_IWORK . Head ] = _rtB -> B_28_21_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_k . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_k .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK_g . Head = ( ( _rtDW -> TransportDelay_IWORK_g . Head <
( _rtDW -> TransportDelay_IWORK_g . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_g . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_g . Head == _rtDW -> TransportDelay_IWORK_g . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_g . CircularBufSize , & _rtDW -> TransportDelay_IWORK_g
. Tail , & _rtDW -> TransportDelay_IWORK_g . Head , & _rtDW ->
TransportDelay_IWORK_g . Last , simTime - _rtP -> P_7 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_g .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_g . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_g . Head ] = _rtB ->
B_28_5_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_f . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_f . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_d . Head = ( ( _rtDW ->
TransportDelay_IWORK_d . Head < ( _rtDW -> TransportDelay_IWORK_d .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_d . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_d . Head == _rtDW ->
TransportDelay_IWORK_d . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_d . CircularBufSize , & _rtDW -> TransportDelay_IWORK_d
. Tail , & _rtDW -> TransportDelay_IWORK_d . Head , & _rtDW ->
TransportDelay_IWORK_d . Last , simTime - _rtP -> P_14 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_d .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_d . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_d . Head ] = _rtB ->
B_28_15_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_c . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_c . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_j . Head = ( ( _rtDW ->
TransportDelay_IWORK_j . Head < ( _rtDW -> TransportDelay_IWORK_j .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_j . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_j . Head == _rtDW ->
TransportDelay_IWORK_j . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_j . CircularBufSize , & _rtDW -> TransportDelay_IWORK_j
. Tail , & _rtDW -> TransportDelay_IWORK_j . Head , & _rtDW ->
TransportDelay_IWORK_j . Last , simTime - _rtP -> P_32 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_j .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] = _rtB ->
B_28_21_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_a . Head = ( ( _rtDW ->
TransportDelay_IWORK_a . Head < ( _rtDW -> TransportDelay_IWORK_a .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_a . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_a . Head == _rtDW ->
TransportDelay_IWORK_a . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_a . CircularBufSize , & _rtDW -> TransportDelay_IWORK_a
. Tail , & _rtDW -> TransportDelay_IWORK_a . Head , & _rtDW ->
TransportDelay_IWORK_a . Last , simTime - _rtP -> P_35 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_a .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] = _rtB ->
B_28_10_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_cm . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_cm . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_e . Head = ( ( _rtDW
-> TransportDelay_IWORK_e . Head < ( _rtDW -> TransportDelay_IWORK_e .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_e . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_e . Head == _rtDW ->
TransportDelay_IWORK_e . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_e . CircularBufSize , & _rtDW -> TransportDelay_IWORK_e
. Tail , & _rtDW -> TransportDelay_IWORK_e . Head , & _rtDW ->
TransportDelay_IWORK_e . Last , simTime - _rtP -> P_38 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_e .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_e . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_e . Head ] = _rtB ->
B_28_50_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> NextOutput = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed ) * _rtP ->
P_41 + _rtP -> P_40 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_kg . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_kg . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_o . Head = ( ( _rtDW
-> TransportDelay_IWORK_o . Head < ( _rtDW -> TransportDelay_IWORK_o .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_o . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_o . Head == _rtDW ->
TransportDelay_IWORK_o . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_o . CircularBufSize , & _rtDW -> TransportDelay_IWORK_o
. Tail , & _rtDW -> TransportDelay_IWORK_o . Head , & _rtDW ->
TransportDelay_IWORK_o . Last , simTime - _rtP -> P_47 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_o .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_o . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_o . Head ] = _rtB ->
B_28_21_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_p . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_p . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_m . Head = ( ( _rtDW ->
TransportDelay_IWORK_m . Head < ( _rtDW -> TransportDelay_IWORK_m .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_m . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_m . Head == _rtDW ->
TransportDelay_IWORK_m . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_m . CircularBufSize , & _rtDW -> TransportDelay_IWORK_m
. Tail , & _rtDW -> TransportDelay_IWORK_m . Head , & _rtDW ->
TransportDelay_IWORK_m . Last , simTime - _rtP -> P_53 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_m .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_m . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_m . Head ] = _rtB ->
B_28_10_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay12_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay12_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay12_IWORK . Head = ( ( _rtDW ->
TransportDelay12_IWORK . Head < ( _rtDW -> TransportDelay12_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay12_IWORK . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay12_IWORK . Head == _rtDW ->
TransportDelay12_IWORK . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay12_IWORK . CircularBufSize , & _rtDW -> TransportDelay12_IWORK
. Tail , & _rtDW -> TransportDelay12_IWORK . Head , & _rtDW ->
TransportDelay12_IWORK . Last , simTime - _rtP -> P_59 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay12_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay12_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay12_IWORK . Head ] = _rtB ->
B_28_8_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> Memory_PreviousInput = _rtB -> B_28_107_0 ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [
1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay2_IWORK . Head =
( ( _rtDW -> TransportDelay2_IWORK . Head < ( _rtDW -> TransportDelay2_IWORK
. CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay2_IWORK . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay2_IWORK . Head == _rtDW ->
TransportDelay2_IWORK . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay2_IWORK
. CircularBufSize , & _rtDW -> TransportDelay2_IWORK . Tail , & _rtDW ->
TransportDelay2_IWORK . Head , & _rtDW -> TransportDelay2_IWORK . Last ,
simTime - _rtP -> P_61 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay2_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay2_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay2_IWORK . Head ] = _rtB -> B_28_67_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay1_IWORK . Head = ( ( _rtDW -> TransportDelay1_IWORK . Head < (
_rtDW -> TransportDelay1_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK . Head == _rtDW -> TransportDelay1_IWORK . Tail ) { if
( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK . CircularBufSize , & _rtDW -> TransportDelay1_IWORK .
Tail , & _rtDW -> TransportDelay1_IWORK . Head , & _rtDW ->
TransportDelay1_IWORK . Last , simTime - _rtP -> P_63 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay1_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] = _rtB ->
B_28_69_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay4_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay4_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay4_IWORK . Head = ( ( _rtDW ->
TransportDelay4_IWORK . Head < ( _rtDW -> TransportDelay4_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay4_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay4_IWORK . Head == _rtDW ->
TransportDelay4_IWORK . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay4_IWORK
. CircularBufSize , & _rtDW -> TransportDelay4_IWORK . Tail , & _rtDW ->
TransportDelay4_IWORK . Head , & _rtDW -> TransportDelay4_IWORK . Last ,
simTime - _rtP -> P_65 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay4_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay4_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay4_IWORK . Head ] = _rtB -> B_28_71_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay3_IWORK . Head = ( ( _rtDW -> TransportDelay3_IWORK . Head < (
_rtDW -> TransportDelay3_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay3_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay3_IWORK . Head == _rtDW -> TransportDelay3_IWORK . Tail ) { if
( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay3_IWORK . CircularBufSize , & _rtDW -> TransportDelay3_IWORK .
Tail , & _rtDW -> TransportDelay3_IWORK . Head , & _rtDW ->
TransportDelay3_IWORK . Last , simTime - _rtP -> P_67 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay3_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay3_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay3_IWORK . Head ] = _rtB ->
B_28_73_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay6_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay6_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay6_IWORK . Head = ( ( _rtDW ->
TransportDelay6_IWORK . Head < ( _rtDW -> TransportDelay6_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay6_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay6_IWORK . Head == _rtDW ->
TransportDelay6_IWORK . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay6_IWORK
. CircularBufSize , & _rtDW -> TransportDelay6_IWORK . Tail , & _rtDW ->
TransportDelay6_IWORK . Head , & _rtDW -> TransportDelay6_IWORK . Last ,
simTime - _rtP -> P_69 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay6_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay6_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay6_IWORK . Head ] = _rtB -> B_28_75_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay5_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay5_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay5_IWORK . Head = ( ( _rtDW -> TransportDelay5_IWORK . Head < (
_rtDW -> TransportDelay5_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay5_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay5_IWORK . Head == _rtDW -> TransportDelay5_IWORK . Tail ) { if
( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay5_IWORK . CircularBufSize , & _rtDW -> TransportDelay5_IWORK .
Tail , & _rtDW -> TransportDelay5_IWORK . Head , & _rtDW ->
TransportDelay5_IWORK . Last , simTime - _rtP -> P_71 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay5_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay5_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay5_IWORK . Head ] = _rtB ->
B_28_77_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay8_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay8_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay8_IWORK . Head = ( ( _rtDW ->
TransportDelay8_IWORK . Head < ( _rtDW -> TransportDelay8_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay8_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay8_IWORK . Head == _rtDW ->
TransportDelay8_IWORK . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay8_IWORK
. CircularBufSize , & _rtDW -> TransportDelay8_IWORK . Tail , & _rtDW ->
TransportDelay8_IWORK . Head , & _rtDW -> TransportDelay8_IWORK . Last ,
simTime - _rtP -> P_73 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay8_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay8_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay8_IWORK . Head ] = _rtB -> B_28_79_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay7_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay7_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay7_IWORK . Head = ( ( _rtDW -> TransportDelay7_IWORK . Head < (
_rtDW -> TransportDelay7_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay7_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay7_IWORK . Head == _rtDW -> TransportDelay7_IWORK . Tail ) { if
( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay7_IWORK . CircularBufSize , & _rtDW -> TransportDelay7_IWORK .
Tail , & _rtDW -> TransportDelay7_IWORK . Head , & _rtDW ->
TransportDelay7_IWORK . Last , simTime - _rtP -> P_75 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay7_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay7_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay7_IWORK . Head ] = _rtB ->
B_28_81_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay9_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay9_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay9_IWORK . Head = ( ( _rtDW ->
TransportDelay9_IWORK . Head < ( _rtDW -> TransportDelay9_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay9_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay9_IWORK . Head == _rtDW ->
TransportDelay9_IWORK . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay9_IWORK
. CircularBufSize , & _rtDW -> TransportDelay9_IWORK . Tail , & _rtDW ->
TransportDelay9_IWORK . Head , & _rtDW -> TransportDelay9_IWORK . Last ,
simTime - _rtP -> P_77 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
false , & _rtDW -> TransportDelay9_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay9_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay9_IWORK . Head ] = _rtB -> B_28_83_0 ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay11_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay11_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay11_IWORK . Head = ( ( _rtDW -> TransportDelay11_IWORK . Head <
( _rtDW -> TransportDelay11_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay11_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay11_IWORK . Head == _rtDW -> TransportDelay11_IWORK . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay11_IWORK . CircularBufSize , & _rtDW -> TransportDelay11_IWORK
. Tail , & _rtDW -> TransportDelay11_IWORK . Head , & _rtDW ->
TransportDelay11_IWORK . Last , simTime - _rtP -> P_79 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay11_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay11_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay11_IWORK . Head ] = _rtB ->
B_28_85_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay10_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay10_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay10_IWORK . Head = ( ( _rtDW ->
TransportDelay10_IWORK . Head < ( _rtDW -> TransportDelay10_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay10_IWORK . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay10_IWORK . Head == _rtDW ->
TransportDelay10_IWORK . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay10_IWORK . CircularBufSize , & _rtDW -> TransportDelay10_IWORK
. Tail , & _rtDW -> TransportDelay10_IWORK . Head , & _rtDW ->
TransportDelay10_IWORK . Last , simTime - _rtP -> P_81 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay10_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay10_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay10_IWORK . Head ] = _rtB ->
B_28_87_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay13_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay13_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay13_IWORK . Head = ( ( _rtDW ->
TransportDelay13_IWORK . Head < ( _rtDW -> TransportDelay13_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay13_IWORK . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay13_IWORK . Head == _rtDW ->
TransportDelay13_IWORK . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay13_IWORK . CircularBufSize , & _rtDW -> TransportDelay13_IWORK
. Tail , & _rtDW -> TransportDelay13_IWORK . Head , & _rtDW ->
TransportDelay13_IWORK . Last , simTime - _rtP -> P_83 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay13_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay13_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay13_IWORK . Head ] = _rtB ->
B_28_89_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> Memory_PreviousInput_b = _rtB -> B_28_96_0 ; _rtDW -> ICic_PreviousInput =
_rtB -> B_28_104_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_h . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_at . Head = ( ( _rtDW ->
TransportDelay_IWORK_at . Head < ( _rtDW -> TransportDelay_IWORK_at .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_at . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_at . Head == _rtDW ->
TransportDelay_IWORK_at . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_at . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_at . Tail , & _rtDW -> TransportDelay_IWORK_at . Head ,
& _rtDW -> TransportDelay_IWORK_at . Last , simTime - _rtP -> P_89 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_at . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_at . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_at . Head ] = _rtB -> B_28_136_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_m . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_m
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay1_IWORK_p . Head = ( ( _rtDW -> TransportDelay1_IWORK_p . Head
< ( _rtDW -> TransportDelay1_IWORK_p . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK_p . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK_p . Head == _rtDW -> TransportDelay1_IWORK_p . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK_p . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_p . Tail , & _rtDW -> TransportDelay1_IWORK_p . Head ,
& _rtDW -> TransportDelay1_IWORK_p . Last , simTime - _rtP -> P_92 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay1_IWORK_p . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay1_IWORK_p . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK_p . Head ] = _rtB -> B_28_143_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_i .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK_i . Head = ( ( _rtDW -> TransportDelay_IWORK_i . Head <
( _rtDW -> TransportDelay_IWORK_i . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_i . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_i . Head == _rtDW -> TransportDelay_IWORK_i . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_i . CircularBufSize , & _rtDW -> TransportDelay_IWORK_i
. Tail , & _rtDW -> TransportDelay_IWORK_i . Head , & _rtDW ->
TransportDelay_IWORK_i . Last , simTime - _rtP -> P_99 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_i .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_i . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_i . Head ] = _rtB ->
B_28_28_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK_b . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay1_PWORK_b . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK_h . Head = ( ( _rtDW
-> TransportDelay1_IWORK_h . Head < ( _rtDW -> TransportDelay1_IWORK_h .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay1_IWORK_h . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay1_IWORK_h . Head == _rtDW ->
TransportDelay1_IWORK_h . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK_h . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_h . Tail , & _rtDW -> TransportDelay1_IWORK_h . Head ,
& _rtDW -> TransportDelay1_IWORK_h . Last , simTime - _rtP -> P_101 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay1_IWORK_h . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay1_IWORK_h . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK_h . Head ] = _rtB -> B_28_28_0 ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> NextOutput_k =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_i ) * _rtP -> P_104 + _rtP
-> P_103 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> Memory_PreviousInput_k = _rtB -> B_28_174_0 ; _rtDW ->
Memory_PreviousInput_n = _rtB -> B_28_163_0 ; _rtDW -> ICic_PreviousInput_k =
_rtB -> B_28_171_0 ; _rtDW -> Memory_PreviousInput_kl = _rtB -> B_28_192_0 ;
_rtDW -> Memory_PreviousInput_j = _rtB -> B_28_181_0 ; _rtDW ->
ICic_PreviousInput_p = _rtB -> B_28_189_0 ; } { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay12_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay12_PWORK_m . TUbufferPtrs [
1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay12_IWORK_f .
Head = ( ( _rtDW -> TransportDelay12_IWORK_f . Head < ( _rtDW ->
TransportDelay12_IWORK_f . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay12_IWORK_f . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay12_IWORK_f . Head == _rtDW -> TransportDelay12_IWORK_f . Tail )
{ if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay12_IWORK_f . CircularBufSize , & _rtDW ->
TransportDelay12_IWORK_f . Tail , & _rtDW -> TransportDelay12_IWORK_f . Head
, & _rtDW -> TransportDelay12_IWORK_f . Last , simTime - _rtP -> P_126 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay12_IWORK_f . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay12_IWORK_f . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay12_IWORK_f . Head ] = _rtB -> B_28_18_0 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Memory_PreviousInput_h = _rtB -> B_28_252_0 ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay2_PWORK_m . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay2_PWORK_m .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay2_IWORK_j . Head = ( ( _rtDW -> TransportDelay2_IWORK_j . Head
< ( _rtDW -> TransportDelay2_IWORK_j . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay2_IWORK_j . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay2_IWORK_j . Head == _rtDW -> TransportDelay2_IWORK_j . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay2_IWORK_j . CircularBufSize , & _rtDW ->
TransportDelay2_IWORK_j . Tail , & _rtDW -> TransportDelay2_IWORK_j . Head ,
& _rtDW -> TransportDelay2_IWORK_j . Last , simTime - _rtP -> P_128 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay2_IWORK_j . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay2_IWORK_j . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay2_IWORK_j . Head ] = _rtB -> B_28_212_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_l . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_l
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay1_IWORK_e . Head = ( ( _rtDW -> TransportDelay1_IWORK_e . Head
< ( _rtDW -> TransportDelay1_IWORK_e . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK_e . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK_e . Head == _rtDW -> TransportDelay1_IWORK_e . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK_e . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_e . Tail , & _rtDW -> TransportDelay1_IWORK_e . Head ,
& _rtDW -> TransportDelay1_IWORK_e . Last , simTime - _rtP -> P_130 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay1_IWORK_e . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay1_IWORK_e . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK_e . Head ] = _rtB -> B_28_214_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay4_PWORK_b . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay4_PWORK_b
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay4_IWORK_h . Head = ( ( _rtDW -> TransportDelay4_IWORK_h . Head
< ( _rtDW -> TransportDelay4_IWORK_h . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay4_IWORK_h . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay4_IWORK_h . Head == _rtDW -> TransportDelay4_IWORK_h . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay4_IWORK_h . CircularBufSize , & _rtDW ->
TransportDelay4_IWORK_h . Tail , & _rtDW -> TransportDelay4_IWORK_h . Head ,
& _rtDW -> TransportDelay4_IWORK_h . Last , simTime - _rtP -> P_132 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay4_IWORK_h . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay4_IWORK_h . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay4_IWORK_h . Head ] = _rtB -> B_28_216_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK_n . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK_n
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay3_IWORK_e . Head = ( ( _rtDW -> TransportDelay3_IWORK_e . Head
< ( _rtDW -> TransportDelay3_IWORK_e . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay3_IWORK_e . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay3_IWORK_e . Head == _rtDW -> TransportDelay3_IWORK_e . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay3_IWORK_e . CircularBufSize , & _rtDW ->
TransportDelay3_IWORK_e . Tail , & _rtDW -> TransportDelay3_IWORK_e . Head ,
& _rtDW -> TransportDelay3_IWORK_e . Last , simTime - _rtP -> P_134 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay3_IWORK_e . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay3_IWORK_e . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay3_IWORK_e . Head ] = _rtB -> B_28_218_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay6_PWORK_f . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay6_PWORK_f
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay6_IWORK_a . Head = ( ( _rtDW -> TransportDelay6_IWORK_a . Head
< ( _rtDW -> TransportDelay6_IWORK_a . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay6_IWORK_a . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay6_IWORK_a . Head == _rtDW -> TransportDelay6_IWORK_a . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay6_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay6_IWORK_a . Tail , & _rtDW -> TransportDelay6_IWORK_a . Head ,
& _rtDW -> TransportDelay6_IWORK_a . Last , simTime - _rtP -> P_136 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay6_IWORK_a . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay6_IWORK_a . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay6_IWORK_a . Head ] = _rtB -> B_28_220_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay5_PWORK_h . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay5_PWORK_h
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay5_IWORK_l . Head = ( ( _rtDW -> TransportDelay5_IWORK_l . Head
< ( _rtDW -> TransportDelay5_IWORK_l . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay5_IWORK_l . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay5_IWORK_l . Head == _rtDW -> TransportDelay5_IWORK_l . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay5_IWORK_l . CircularBufSize , & _rtDW ->
TransportDelay5_IWORK_l . Tail , & _rtDW -> TransportDelay5_IWORK_l . Head ,
& _rtDW -> TransportDelay5_IWORK_l . Last , simTime - _rtP -> P_138 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay5_IWORK_l . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay5_IWORK_l . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay5_IWORK_l . Head ] = _rtB -> B_28_222_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay8_PWORK_g . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay8_PWORK_g
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay8_IWORK_a . Head = ( ( _rtDW -> TransportDelay8_IWORK_a . Head
< ( _rtDW -> TransportDelay8_IWORK_a . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay8_IWORK_a . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay8_IWORK_a . Head == _rtDW -> TransportDelay8_IWORK_a . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay8_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay8_IWORK_a . Tail , & _rtDW -> TransportDelay8_IWORK_a . Head ,
& _rtDW -> TransportDelay8_IWORK_a . Last , simTime - _rtP -> P_140 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay8_IWORK_a . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay8_IWORK_a . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay8_IWORK_a . Head ] = _rtB -> B_28_224_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay7_PWORK_b . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay7_PWORK_b
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay7_IWORK_d . Head = ( ( _rtDW -> TransportDelay7_IWORK_d . Head
< ( _rtDW -> TransportDelay7_IWORK_d . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay7_IWORK_d . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay7_IWORK_d . Head == _rtDW -> TransportDelay7_IWORK_d . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay7_IWORK_d . CircularBufSize , & _rtDW ->
TransportDelay7_IWORK_d . Tail , & _rtDW -> TransportDelay7_IWORK_d . Head ,
& _rtDW -> TransportDelay7_IWORK_d . Last , simTime - _rtP -> P_142 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay7_IWORK_d . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay7_IWORK_d . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay7_IWORK_d . Head ] = _rtB -> B_28_226_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay9_PWORK_k . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay9_PWORK_k
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay9_IWORK_e . Head = ( ( _rtDW -> TransportDelay9_IWORK_e . Head
< ( _rtDW -> TransportDelay9_IWORK_e . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay9_IWORK_e . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay9_IWORK_e . Head == _rtDW -> TransportDelay9_IWORK_e . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay9_IWORK_e . CircularBufSize , & _rtDW ->
TransportDelay9_IWORK_e . Tail , & _rtDW -> TransportDelay9_IWORK_e . Head ,
& _rtDW -> TransportDelay9_IWORK_e . Last , simTime - _rtP -> P_144 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay9_IWORK_e . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay9_IWORK_e . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay9_IWORK_e . Head ] = _rtB -> B_28_228_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay11_PWORK_h . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay11_PWORK_h
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay11_IWORK_c . Head = ( ( _rtDW -> TransportDelay11_IWORK_c .
Head < ( _rtDW -> TransportDelay11_IWORK_c . CircularBufSize - 1 ) ) ? (
_rtDW -> TransportDelay11_IWORK_c . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay11_IWORK_c . Head == _rtDW -> TransportDelay11_IWORK_c . Tail )
{ if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay11_IWORK_c . CircularBufSize , & _rtDW ->
TransportDelay11_IWORK_c . Tail , & _rtDW -> TransportDelay11_IWORK_c . Head
, & _rtDW -> TransportDelay11_IWORK_c . Last , simTime - _rtP -> P_146 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay11_IWORK_c . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay11_IWORK_c . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay11_IWORK_c . Head ] = _rtB -> B_28_230_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay10_PWORK_l . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay10_PWORK_l
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay10_IWORK_o . Head = ( ( _rtDW -> TransportDelay10_IWORK_o .
Head < ( _rtDW -> TransportDelay10_IWORK_o . CircularBufSize - 1 ) ) ? (
_rtDW -> TransportDelay10_IWORK_o . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay10_IWORK_o . Head == _rtDW -> TransportDelay10_IWORK_o . Tail )
{ if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay10_IWORK_o . CircularBufSize , & _rtDW ->
TransportDelay10_IWORK_o . Tail , & _rtDW -> TransportDelay10_IWORK_o . Head
, & _rtDW -> TransportDelay10_IWORK_o . Last , simTime - _rtP -> P_148 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay10_IWORK_o . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay10_IWORK_o . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay10_IWORK_o . Head ] = _rtB -> B_28_232_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay13_PWORK_j . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay13_PWORK_j
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay13_IWORK_m . Head = ( ( _rtDW -> TransportDelay13_IWORK_m .
Head < ( _rtDW -> TransportDelay13_IWORK_m . CircularBufSize - 1 ) ) ? (
_rtDW -> TransportDelay13_IWORK_m . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay13_IWORK_m . Head == _rtDW -> TransportDelay13_IWORK_m . Tail )
{ if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay13_IWORK_m . CircularBufSize , & _rtDW ->
TransportDelay13_IWORK_m . Tail , & _rtDW -> TransportDelay13_IWORK_m . Head
, & _rtDW -> TransportDelay13_IWORK_m . Last , simTime - _rtP -> P_150 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay13_IWORK_m . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay13_IWORK_m . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay13_IWORK_m . Head ] = _rtB -> B_28_234_0 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Memory_PreviousInput_e = _rtB -> B_28_241_0 ; _rtDW -> ICic_PreviousInput_i =
_rtB -> B_28_249_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_cv . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_cv . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_k . Head = ( ( _rtDW
-> TransportDelay_IWORK_k . Head < ( _rtDW -> TransportDelay_IWORK_k .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_k . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_k . Head == _rtDW ->
TransportDelay_IWORK_k . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_k . CircularBufSize , & _rtDW -> TransportDelay_IWORK_k
. Tail , & _rtDW -> TransportDelay_IWORK_k . Head , & _rtDW ->
TransportDelay_IWORK_k . Last , simTime - _rtP -> P_156 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_k .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_k . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_k . Head ] = _rtB ->
B_28_281_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK_i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay1_PWORK_i . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK_i . Head = ( ( _rtDW
-> TransportDelay1_IWORK_i . Head < ( _rtDW -> TransportDelay1_IWORK_i .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay1_IWORK_i . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay1_IWORK_i . Head == _rtDW ->
TransportDelay1_IWORK_i . Tail ) { if ( !
multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK_i . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_i . Tail , & _rtDW -> TransportDelay1_IWORK_i . Head ,
& _rtDW -> TransportDelay1_IWORK_i . Last , simTime - _rtP -> P_159 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay1_IWORK_i . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay1_IWORK_i . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK_i . Head ] = _rtB -> B_28_288_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c5 . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c5
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK_gq . Head = ( ( _rtDW -> TransportDelay_IWORK_gq . Head
< ( _rtDW -> TransportDelay_IWORK_gq . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_gq . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_gq . Head == _rtDW -> TransportDelay_IWORK_gq . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_gq . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_gq . Tail , & _rtDW -> TransportDelay_IWORK_gq . Head ,
& _rtDW -> TransportDelay_IWORK_gq . Last , simTime - _rtP -> P_166 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_gq . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_gq . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_gq . Head ] = _rtB -> B_28_29_0 ; } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_mk . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_mk .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay1_IWORK_b . Head = ( ( _rtDW -> TransportDelay1_IWORK_b . Head
< ( _rtDW -> TransportDelay1_IWORK_b . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK_b . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK_b . Head == _rtDW -> TransportDelay1_IWORK_b . Tail ) {
if ( ! multiplex_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK_b . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_b . Tail , & _rtDW -> TransportDelay1_IWORK_b . Head ,
& _rtDW -> TransportDelay1_IWORK_b . Last , simTime - _rtP -> P_168 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay1_IWORK_b . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay1_IWORK_b . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK_b . Head ] = _rtB -> B_28_29_0 ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> NextOutput_c =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_e ) * _rtP -> P_171 + _rtP
-> P_170 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> Memory_PreviousInput_jr = _rtB -> B_28_319_0 ; _rtDW ->
Memory_PreviousInput_l = _rtB -> B_28_308_0 ; _rtDW -> ICic_PreviousInput_c =
_rtB -> B_28_316_0 ; _rtDW -> Memory_PreviousInput_a = _rtB -> B_28_337_0 ;
_rtDW -> Memory_PreviousInput_bb = _rtB -> B_28_326_0 ; _rtDW ->
ICic_PreviousInput_cq = _rtB -> B_28_334_0 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID6 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { int_T is ; int_T ci ; static
const int8_T ir [ 11 ] = { 0 , 2 , 6 , 8 , 12 , 14 , 15 , 16 , 17 , 18 , 19 }
; static const int8_T ir_0 [ 11 ] = { 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
1 } ; static const int8_T jc [ 19 ] = { 0 , 5 , 0 , 1 , 2 , 6 , 1 , 7 , 2 , 3
, 4 , 8 , 3 , 9 , 0 , 1 , 2 , 3 , 4 } ; static const int8_T ir_1 [ 7 ] = { 0
, 2 , 3 , 6 , 7 , 10 , 11 } ; static const int8_T jc_0 [ 11 ] = { 0 , 1 , 0 ,
1 , 2 , 3 , 2 , 3 , 4 , 5 , 4 } ; static const int8_T ir_2 [ 7 ] = { 0 , 1 ,
1 , 1 , 1 , 1 , 1 } ; B_multiplex_T * _rtB ; P_multiplex_T * _rtP ;
X_multiplex_T * _rtX ; XDot_multiplex_T * _rtXdot ; _rtXdot = ( (
XDot_multiplex_T * ) ssGetdX ( S ) ) ; _rtX = ( ( X_multiplex_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_multiplex_T * ) ssGetModelRtp ( S ) )
; _rtB = ( ( B_multiplex_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
ModuloIntegrator_CSTATE = _rtB -> B_28_199_0 ; _rtXdot -> Integrator_CSTATE =
_rtB -> B_28_154_0 ; _rtXdot -> ModuloIntegrator_CSTATE_k = _rtB ->
B_28_344_0 ; _rtXdot -> Integrator_CSTATE_n = _rtB -> B_28_299_0 ; _rtXdot ->
Integrator_CSTATE_l = _rtB -> MuestreoyRetencion . B_0_0_0 ; _rtXdot ->
Integrator_CSTATE_j = _rtB -> MuestreoyRetencion_e . B_0_0_0 ; for ( is = 0 ;
is < 10 ; is ++ ) { _rtXdot -> AnalogFilterDesign_CSTATE [ is ] = 0.0 ; for (
ci = ir [ is ] ; ci < ir [ is + 1 ] ; ci ++ ) { _rtXdot ->
AnalogFilterDesign_CSTATE [ is ] += _rtP -> P_18 [ ci ] * _rtX ->
AnalogFilterDesign_CSTATE [ jc [ ci ] ] ; } } for ( is = 0 ; is < 10 ; is ++
) { ci = ir_0 [ is ] ; while ( ci < ir_0 [ is + 1 ] ) { _rtXdot ->
AnalogFilterDesign_CSTATE [ is ] += _rtP -> P_19 * _rtB -> B_28_49_0 ; ci = 1
; } _rtXdot -> AnalogFilterDesign2_CSTATE [ is ] = 0.0 ; } for ( is = 0 ; is
< 10 ; is ++ ) { for ( ci = ir [ is ] ; ci < ir [ is + 1 ] ; ci ++ ) {
_rtXdot -> AnalogFilterDesign2_CSTATE [ is ] += _rtP -> P_22 [ ci ] * _rtX ->
AnalogFilterDesign2_CSTATE [ jc [ ci ] ] ; } } for ( is = 0 ; is < 10 ; is ++
) { ci = ir_0 [ is ] ; while ( ci < ir_0 [ is + 1 ] ) { _rtXdot ->
AnalogFilterDesign2_CSTATE [ is ] += _rtP -> P_23 * _rtB -> B_28_49_0 ; ci =
1 ; } } _rtXdot -> ModuloIntegrator_CSTATE_kx = _rtB -> B_28_39_0 ; _rtXdot
-> ModuloIntegrator_CSTATE_h = _rtB -> B_28_42_0 ; for ( is = 0 ; is < 6 ; is
++ ) { _rtXdot -> Filtro_CSTATE [ is ] = 0.0 ; for ( ci = ir_1 [ is ] ; ci <
ir_1 [ is + 1 ] ; ci ++ ) { _rtXdot -> Filtro_CSTATE [ is ] += _rtP -> P_95 [
ci ] * _rtX -> Filtro_CSTATE [ jc_0 [ ci ] ] ; } } _rtXdot ->
ModuloIntegrator_CSTATE_l = _rtB -> B_28_149_0 ; _rtXdot ->
Integrator_CSTATE_o = _rtB -> B_28_152_0 ; _rtXdot ->
ModuloIntegrator_CSTATE_e = _rtB -> B_28_151_0 ; _rtXdot ->
Integrator1_CSTATE = _rtB -> B_28_153_0 ; _rtXdot -> Integrator_CSTATE_a =
_rtB -> B_28_154_0 ; _rtXdot -> Integrator1_CSTATE_c = _rtB -> B_28_154_0 ;
for ( is = 0 ; is < 6 ; is ++ ) { ci = ir_2 [ is ] ; while ( ci < 1 ) {
_rtXdot -> Filtro_CSTATE [ is ] += _rtP -> P_96 * _rtB -> B_28_132_0 ; ci = 1
; } _rtXdot -> Filtro_CSTATE_b [ is ] = 0.0 ; } for ( is = 0 ; is < 6 ; is ++
) { for ( ci = ir_1 [ is ] ; ci < ir_1 [ is + 1 ] ; ci ++ ) { _rtXdot ->
Filtro_CSTATE_b [ is ] += _rtP -> P_162 [ ci ] * _rtX -> Filtro_CSTATE_b [
jc_0 [ ci ] ] ; } } for ( is = 0 ; is < 6 ; is ++ ) { ci = ir_2 [ is ] ;
while ( ci < 1 ) { _rtXdot -> Filtro_CSTATE_b [ is ] += _rtP -> P_163 * _rtB
-> B_28_277_0 ; ci = 1 ; } } _rtXdot -> ModuloIntegrator_CSTATE_c = _rtB ->
B_28_294_0 ; _rtXdot -> Integrator_CSTATE_jg = _rtB -> B_28_297_0 ; _rtXdot
-> ModuloIntegrator_CSTATE_a = _rtB -> B_28_296_0 ; _rtXdot ->
Integrator1_CSTATE_cy = _rtB -> B_28_298_0 ; _rtXdot -> Integrator_CSTATE_om
= _rtB -> B_28_299_0 ; _rtXdot -> Integrator1_CSTATE_e = _rtB -> B_28_299_0 ;
}
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_multiplex_T * _rtB ;
P_multiplex_T * _rtP ; ZCV_multiplex_T * _rtZCSV ; _rtZCSV = ( (
ZCV_multiplex_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtP = ( (
P_multiplex_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_multiplex_T * )
_ssGetModelBlockIO ( S ) ) ; _rtZCSV -> Sign_Input_ZC = _rtB -> B_28_3_0 ;
_rtZCSV -> Compare_RelopInput_ZC = _rtB -> B_28_6_0 - _rtB -> B_28_4_0 ;
_rtZCSV -> Sign_Input_ZC_o = _rtB -> B_28_13_0 ; _rtZCSV ->
Compare_RelopInput_ZC_g = _rtB -> B_28_16_0 - _rtB -> B_28_54_0_l ; _rtZCSV
-> Switch_SwitchCond_ZC = _rtB -> B_28_93_0 - _rtP -> P_85 ; _rtZCSV ->
Switch1_SwitchCond_ZC = _rtB -> B_28_93_0 - _rtP -> P_86 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC = _rtB -> B_28_106_0 - _rtB -> B_28_64_0 ;
_rtZCSV -> Mensajerecibido_Trig_ZC = _rtB -> B_28_108_0 ; _rtZCSV ->
Sign3_Input_ZC = _rtB -> B_28_116_0 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_d = _rtB -> B_28_157_0 - _rtB -> B_28_155_0
; _rtZCSV -> RelationalOperator_RelopInput_ZC_c = _rtB -> B_28_173_0 - _rtB
-> B_28_160_0 ; _rtZCSV -> RelationalOperator_RelopInput_ZC_o = _rtB ->
B_28_191_0 - _rtB -> B_28_178_0 ; _rtZCSV -> Abs1_AbsZc_ZC = _rtB ->
B_28_193_0 ; _rtZCSV -> RelationalOperator_RelopInput_ZC_k = _rtB ->
B_28_202_0 - _rtB -> B_28_200_0 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_j = _rtB -> B_28_206_0 - _rtB -> B_28_204_0
; _rtZCSV -> Switch_SwitchCond_ZC_d = _rtB -> B_28_238_0 - _rtP -> P_152 ;
_rtZCSV -> Switch1_SwitchCond_ZC_b = _rtB -> B_28_238_0 - _rtP -> P_153 ;
_rtZCSV -> RelationalOperator_RelopInput_ZC_p = _rtB -> B_28_251_0 - _rtB ->
B_28_209_0 ; _rtZCSV -> Mensajerecibido2_Trig_ZC = _rtB -> B_28_253_0 ;
_rtZCSV -> Sign3_Input_ZC_d = _rtB -> B_28_261_0 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_pq = _rtB -> B_28_302_0 - _rtB -> B_28_300_0
; _rtZCSV -> RelationalOperator_RelopInput_ZC_b = _rtB -> B_28_318_0 - _rtB
-> B_28_305_0 ; _rtZCSV -> RelationalOperator_RelopInput_ZC_g = _rtB ->
B_28_336_0 - _rtB -> B_28_323_0 ; _rtZCSV -> Abs1_AbsZc_ZC_h = _rtB ->
B_28_338_0 ; _rtZCSV -> RelationalOperator_RelopInput_ZC_jd = _rtB ->
B_28_347_0 - _rtB -> B_28_345_0 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_e = _rtB -> B_28_351_0 - _rtB -> B_28_349_0
; } static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S ,
0 , 830880822U ) ; ssSetChecksumVal ( S , 1 , 3767987685U ) ;
ssSetChecksumVal ( S , 2 , 7383377U ) ; ssSetChecksumVal ( S , 3 , 979551635U
) ; { mxArray * slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString (
"simulink" ) ; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , &
slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray *
slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat ==
NULL ) { status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar ,
10 ) ; } } mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ;
if ( ( status == 1 ) || ( strcmp ( slVerChar , "10.1" ) != 0 ) ) { return ; }
} ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork
( S ) != sizeof ( DW_multiplex_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_multiplex_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_multiplex_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & multiplex_rtDefaultP ) ; } static void mdlInitializeSampleTimes (
SimStruct * S ) { slAccRegPrmChangeFcn ( S , mdlOutputsTID6 ) ; } static void
mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
