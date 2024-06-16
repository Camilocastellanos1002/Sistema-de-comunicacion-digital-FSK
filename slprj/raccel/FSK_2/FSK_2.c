#include "rt_logging_mmi.h"
#include "FSK_2_capi.h"
#include <math.h>
#include "FSK_2.h"
#include "FSK_2_private.h"
#include "FSK_2_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; extern boolean_T
gblExtModeStartPktReceived ; void raccelForceExtModeShutdown ( ) { if ( !
gblExtModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 4 , & stopRequested ) ; }
rtExtModeShutdown ( 4 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 2 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 5 ; const char_T
* gbl_raccel_Version = "10.1 (R2020a) 18-Nov-2019" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const char * gblSlvrJacPatternFileName =
"slprj\\raccel\\FSK_2\\FSK_2_Jpattern.mat" ; const int_T gblNumRootInportBlks
= 0 ; const int_T gblNumModelInputs = 0 ; extern rtInportTUtable *
gblInportTUtables ; extern const char * gblInportFileName ; extern void *
gblAperiodicPartitionHitTimes ; const int_T gblInportDataTypeIdx [ ] = { - 1
} ; const int_T gblInportDims [ ] = { - 1 } ; const int_T gblInportComplex [
] = { - 1 } ; const int_T gblInportInterpoFlag [ ] = { - 1 } ; const int_T
gblInportContinuous [ ] = { - 1 } ; int_T enableFcnCallFlag [ ] = { 1 , 1 , 1
, 1 , 1 } ; const char * raccelLoadInputsAndAperiodicHitTimes ( const char *
inportFileName , int * matFileFormat ) { return rt_RapidReadInportsMatFile (
inportFileName , matFileFormat , 1 ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
B rtB ; X rtX ; PeriodicIndX rtPeriodicIndX ; PeriodicRngX rtPeriodicRngX ;
DW rtDW ; static SimStruct model_S ; SimStruct * const rtS = & model_S ;
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ;
#endif
void * rt_TDelayCreateBuf ( int_T numBuffer , int_T bufSz , int_T elemSz ) {
return ( ( void * ) utMalloc ( numBuffer * bufSz * elemSz ) ) ; }
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T * tailPtr ,
int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * * tBufPtr ,
real_T * * uBufPtr , real_T * * xBufPtr , boolean_T isfixedbuf , boolean_T
istransportdelay , int_T * maxNewBufSzPtr ) { int_T testIdx ; int_T tail = *
tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf = * tBufPtr ; real_T *
xBuf = ( NULL ) ; int_T numBuffer = 2 ; if ( istransportdelay ) { numBuffer =
3 ; xBuf = * xBufPtr ; } testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 ) :
0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ;
real_T * tempT ; real_T * tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf =
* uBufPtr ; int_T newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr
) { * maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer
* newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false
) ; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
tBufPtr = tempT ; * uBufPtr = tempU ; if ( istransportdelay ) * xBufPtr =
tempX ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart , real_T * tBuf ,
real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx , int_T
newIdx , real_T initOutput , boolean_T discrete , boolean_T
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
#ifndef __RTW_UTFREE__  
extern void utFree ( void * ) ;
#endif
void rt_TDelayFreeBuf ( void * buf ) { utFree ( buf ) ; } real_T
rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { uint32_T lo ; uint32_T hi ; lo
= * u % 127773U * 16807U ; hi = * u / 127773U * 2836U ; if ( lo < hi ) { * u
= 2147483647U - ( hi - lo ) ; } else { * u = lo - hi ; } return ( real_T ) *
u * 4.6566128752457969E-10 ; } real_T rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T *
u ) { real_T y ; real_T sr ; real_T si ; do { sr = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = sr * sr + si * si ; } while (
si > 1.0 ) ; y = muDoubleScalarSqrt ( - 2.0 * muDoubleScalarLog ( si ) / si )
* sr ; return y ; } void MdlInitialize ( void ) { int_T is ; uint32_T tseed ;
int32_T t ; real_T tmp ; for ( is = 0 ; is < 10 ; is ++ ) { rtX . ay2evnqozi
[ is ] = rtP . AnalogFilterDesign_InitialCondition ; rtX . efzaicakgx [ is ]
= rtP . AnalogFilterDesign2_InitialCondition ; } rtX . hpywvdhwlx = rtP .
ModuloIntegrator_IC ; rtX . dmykij4zst = rtP . ModuloIntegrator_IC_p52dz1dzx0
; tmp = muDoubleScalarFloor ( rtP . GaussianNoiseGenerator_s ) ; if (
muDoubleScalarIsNaN ( tmp ) || muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; }
else { tmp = muDoubleScalarRem ( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0
? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp : ( uint32_T ) tmp ; is = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) is << 16U ) ) + t ) << 16U ) + t ) + is ; if (
tseed < 1U ) { tseed = 1144108930U ; } else { if ( tseed > 2147483646U ) {
tseed = 2147483646U ; } } rtDW . ezauhd3tt0 = tseed ; rtDW . osax4czyvz =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . ezauhd3tt0 ) * rtP .
RandomNumber_StdDev + rtP . RandomNumber_Mean ; { int_T
rootPeriodicContStateIndices [ 2 ] = { 20 , 21 } ; real_T
rootPeriodicContStateRanges [ 4 ] = { 0.0 , 1.0 , 0.0 , 1.0 } ; ( void )
memcpy ( ( void * ) rtPeriodicIndX , rootPeriodicContStateIndices , 2 *
sizeof ( int_T ) ) ; ( void ) memcpy ( ( void * ) rtPeriodicRngX ,
rootPeriodicContStateRanges , 4 * sizeof ( real_T ) ) ; } } void MdlStart (
void ) { { void * * slioCatalogueAddr = rt_slioCatalogueAddr ( ) ; void * r2
= ( NULL ) ; void * * pOSigstreamManagerAddr = ( NULL ) ; const int
maxErrorBufferSize = 16384 ; char errMsgCreatingOSigstreamManager [ 16384 ] ;
bool errorCreatingOSigstreamManager = false ; const char *
errorAddingR2SharedResource = ( NULL ) ; * slioCatalogueAddr =
rtwGetNewSlioCatalogue ( rt_GetMatSigLogSelectorFileName ( ) ) ;
errorAddingR2SharedResource = rtwAddR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) , 1 ) ; if (
errorAddingR2SharedResource != ( NULL ) ) { rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = ( NULL ) ; ssSetErrorStatus ( rtS
, errorAddingR2SharedResource ) ; return ; } r2 = rtwGetR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ) ;
pOSigstreamManagerAddr = rt_GetOSigstreamManagerAddr ( ) ;
errorCreatingOSigstreamManager = rtwOSigstreamManagerCreateInstance (
rt_GetMatSigLogSelectorFileName ( ) , r2 , pOSigstreamManagerAddr ,
errMsgCreatingOSigstreamManager , maxErrorBufferSize ) ; if (
errorCreatingOSigstreamManager ) { * pOSigstreamManagerAddr = ( NULL ) ;
ssSetErrorStatus ( rtS , errMsgCreatingOSigstreamManager ) ; return ; } } {
bool externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( ) ; rtwISigstreamManagerGetInputIsInDatasetFormat (
pISigstreamManager , & externalInputIsInDatasetFormat ) ; if (
externalInputIsInDatasetFormat ) { } } { FWksInfo * fromwksInfo ; if ( (
fromwksInfo = ( FWksInfo * ) calloc ( 1 , sizeof ( FWksInfo ) ) ) == ( NULL )
) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "mensaje " ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) rtP . Informacion_Data0 ; fromwksInfo -> nDataPoints =
182 ; fromwksInfo -> time = ( NULL ) ; rtDW . i00x1wwgsf . TimePtr =
fromwksInfo -> time ; rtDW . i00x1wwgsf . DataPtr = fromwksInfo -> data ;
rtDW . i00x1wwgsf . RSimInfoPtr = fromwksInfo ; } rtDW . h4rggrbxnc .
PrevIndex = - 1 ; } { FWksInfo * fromwksInfo ; if ( ( fromwksInfo = (
FWksInfo * ) calloc ( 1 , sizeof ( FWksInfo ) ) ) == ( NULL ) ) {
ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "mensaje " ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) rtP . Informacion1_Data0 ; fromwksInfo -> nDataPoints =
182 ; fromwksInfo -> time = ( NULL ) ; rtDW . jf1myj4gvp . TimePtr =
fromwksInfo -> time ; rtDW . jf1myj4gvp . DataPtr = fromwksInfo -> data ;
rtDW . jf1myj4gvp . RSimInfoPtr = fromwksInfo ; } rtDW . powianu2bz .
PrevIndex = - 1 ; } { { real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf (
2 , 1024 , sizeof ( real_T ) ) ; if ( pBuffer == ( NULL ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } rtDW
. oxfi1zw3ko . Tail = 0 ; rtDW . oxfi1zw3ko . Head = 0 ; rtDW . oxfi1zw3ko .
Last = 0 ; rtDW . oxfi1zw3ko . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
aw2n3f4po1 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
aw2n3f4po1 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . engssbe05o . Tail = 0
; rtDW . engssbe05o . Head = 0 ; rtDW . engssbe05o . Last = 0 ; rtDW .
engssbe05o . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_erb5xkljw0 ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . bmxd34jmp4 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
bmxd34jmp4 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . m0cwy3q4nt . Tail = 0
; rtDW . m0cwy3q4nt . Head = 0 ; rtDW . m0cwy3q4nt . Last = 0 ; rtDW .
m0cwy3q4nt . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_npzkuu2dfa ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . haguqrracw . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
haguqrracw . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } }
MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) { real_T gqcuvhxllf ;
real_T ofccwugglf ; real_T b5fmrjv30p ; if ( ssIsSampleHit ( rtS , 3 , 0 ) )
{ { int_T currIndex = rtDW . h4rggrbxnc . PrevIndex + 1 ; real_T *
pDataValues = ( real_T * ) rtDW . i00x1wwgsf . DataPtr ; int numPoints ,
lastPoint ; FWksInfo * fromwksInfo = ( FWksInfo * ) rtDW . i00x1wwgsf .
RSimInfoPtr ; numPoints = fromwksInfo -> nDataPoints ; lastPoint = numPoints
- 1 ; if ( currIndex < numPoints ) { pDataValues += currIndex ; rtB .
bdmiwmnwdi = * pDataValues ; } else { rtB . bdmiwmnwdi = 0.0 ; } rtDW .
h4rggrbxnc . PrevIndex = currIndex ; } } rtB . a2ej4vwwfz = 0.0 ; rtB .
a2ej4vwwfz += rtP . AnalogFilterDesign_C * rtX . ay2evnqozi [ 4 ] ; rtB .
cydck3mxyr = 0.0 ; rtB . cydck3mxyr += rtP . AnalogFilterDesign2_C * rtX .
efzaicakgx [ 4 ] ; if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { { int_T currIndex =
rtDW . powianu2bz . PrevIndex + 1 ; real_T * pDataValues = ( real_T * ) rtDW
. jf1myj4gvp . DataPtr ; int numPoints , lastPoint ; FWksInfo * fromwksInfo =
( FWksInfo * ) rtDW . jf1myj4gvp . RSimInfoPtr ; numPoints = fromwksInfo ->
nDataPoints ; lastPoint = numPoints - 1 ; if ( currIndex < numPoints ) {
pDataValues += currIndex ; rtB . ixhdtyqkuo = * pDataValues ; } else { rtB .
ixhdtyqkuo = 0.0 ; } rtDW . powianu2bz . PrevIndex = currIndex ; } } { real_T
* * uBuffer = ( real_T * * ) & rtDW . aw2n3f4po1 . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & rtDW . aw2n3f4po1 . TUbufferPtrs [ 1 ]
; real_T simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - rtP .
TransportDelay_Delay ; if ( rtP . TransportDelay_Delay == 0.0 ) gqcuvhxllf =
rtB . bdmiwmnwdi ; else gqcuvhxllf = rt_TDelayInterpolate ( tMinusDelay , 0.0
, * tBuffer , * uBuffer , rtDW . oxfi1zw3ko . CircularBufSize , & rtDW .
oxfi1zw3ko . Last , rtDW . oxfi1zw3ko . Tail , rtDW . oxfi1zw3ko . Head , rtP
. TransportDelay_InitOutput , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB .
dzdmp2qvuc = rtP . Rb / 2.0 * gqcuvhxllf + rtP . Frec2 ; { real_T * * uBuffer
= ( real_T * * ) & rtDW . bmxd34jmp4 . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & rtDW . bmxd34jmp4 . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - rtP .
TransportDelay_Delay_mpjovd0fow ; if ( rtP . TransportDelay_Delay_mpjovd0fow
== 0.0 ) ofccwugglf = rtB . ixhdtyqkuo ; else ofccwugglf =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
engssbe05o . CircularBufSize , & rtDW . engssbe05o . Last , rtDW . engssbe05o
. Tail , rtDW . engssbe05o . Head , rtP .
TransportDelay_InitOutput_erb5xkljw0 , 1 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB .
a1nwn30zom = rtP . Rb / 2.0 * ofccwugglf + rtP . Frec4 ; { real_T * * uBuffer
= ( real_T * * ) & rtDW . haguqrracw . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & rtDW . haguqrracw . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - rtP . Retraso_canal
; b5fmrjv30p = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . m0cwy3q4nt . CircularBufSize , & rtDW . m0cwy3q4nt . Last ,
rtDW . m0cwy3q4nt . Tail , rtDW . m0cwy3q4nt . Head , rtP .
TransportDelay_InitOutput_npzkuu2dfa , 0 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } if (
ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB . pxelcov220 = rtP .
GaussianNoiseGenerator_d * rtDW . osax4czyvz + rtP . GaussianNoiseGenerator_m
; rtB . br52h0oi5h = rtB . pxelcov220 ; } rtB . clkvycwj4m = b5fmrjv30p + rtB
. br52h0oi5h ; rtB . o0un153nbh = ( ( muDoubleScalarSin ( 6.2831853071795862
* rtP . frec * ssGetTaskTime ( rtS , 0 ) + rtP . SineWave_Phase ) * rtP .
SineWave_Amp + rtP . SineWave_Bias ) * muDoubleScalarCos ( rtX . hpywvdhwlx *
6.2831853071795862 ) + muDoubleScalarCos ( rtX . dmykij4zst *
6.2831853071795862 ) ) * ( 1.0 / rtP . Atenuacion_canal ) ; UNUSED_PARAMETER
( tid ) ; } void MdlUpdate ( int_T tid ) { { real_T * * uBuffer = ( real_T *
* ) & rtDW . aw2n3f4po1 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . aw2n3f4po1 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . oxfi1zw3ko . Head = ( ( rtDW . oxfi1zw3ko . Head < ( rtDW .
oxfi1zw3ko . CircularBufSize - 1 ) ) ? ( rtDW . oxfi1zw3ko . Head + 1 ) : 0 )
; if ( rtDW . oxfi1zw3ko . Head == rtDW . oxfi1zw3ko . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . oxfi1zw3ko . CircularBufSize , & rtDW
. oxfi1zw3ko . Tail , & rtDW . oxfi1zw3ko . Head , & rtDW . oxfi1zw3ko . Last
, simTime - rtP . TransportDelay_Delay , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . oxfi1zw3ko . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . oxfi1zw3ko . Head ] = simTime ; ( * uBuffer ) [ rtDW .
oxfi1zw3ko . Head ] = rtB . bdmiwmnwdi ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . bmxd34jmp4 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . bmxd34jmp4 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . engssbe05o . Head = ( ( rtDW . engssbe05o . Head < ( rtDW .
engssbe05o . CircularBufSize - 1 ) ) ? ( rtDW . engssbe05o . Head + 1 ) : 0 )
; if ( rtDW . engssbe05o . Head == rtDW . engssbe05o . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . engssbe05o . CircularBufSize , & rtDW
. engssbe05o . Tail , & rtDW . engssbe05o . Head , & rtDW . engssbe05o . Last
, simTime - rtP . TransportDelay_Delay_mpjovd0fow , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & rtDW . engssbe05o . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . engssbe05o . Head ] = simTime ; ( * uBuffer ) [ rtDW .
engssbe05o . Head ] = rtB . ixhdtyqkuo ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . haguqrracw . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . haguqrracw . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . m0cwy3q4nt . Head = ( ( rtDW . m0cwy3q4nt . Head < ( rtDW .
m0cwy3q4nt . CircularBufSize - 1 ) ) ? ( rtDW . m0cwy3q4nt . Head + 1 ) : 0 )
; if ( rtDW . m0cwy3q4nt . Head == rtDW . m0cwy3q4nt . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . m0cwy3q4nt . CircularBufSize , & rtDW
. m0cwy3q4nt . Tail , & rtDW . m0cwy3q4nt . Head , & rtDW . m0cwy3q4nt . Last
, simTime - rtP . Retraso_canal , tBuffer , uBuffer , ( NULL ) , ( boolean_T
) 0 , false , & rtDW . m0cwy3q4nt . MaxNewBufSize ) ) { ssSetErrorStatus (
rtS , "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW
. m0cwy3q4nt . Head ] = simTime ; ( * uBuffer ) [ rtDW . m0cwy3q4nt . Head ]
= rtB . o0un153nbh ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW .
osax4czyvz = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . ezauhd3tt0 ) * rtP .
RandomNumber_StdDev + rtP . RandomNumber_Mean ; } UNUSED_PARAMETER ( tid ) ;
} void MdlUpdateTID4 ( int_T tid ) { UNUSED_PARAMETER ( tid ) ; } void
MdlDerivatives ( void ) { int_T is ; int_T ci ; static const int8_T ir [ 11 ]
= { 0 , 2 , 6 , 8 , 12 , 14 , 15 , 16 , 17 , 18 , 19 } ; static const int8_T
ir_p [ 11 ] = { 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static const
int8_T jc [ 19 ] = { 0 , 5 , 0 , 1 , 2 , 6 , 1 , 7 , 2 , 3 , 4 , 8 , 3 , 9 ,
0 , 1 , 2 , 3 , 4 } ; XDot * _rtXdot ; _rtXdot = ( ( XDot * ) ssGetdX ( rtS )
) ; for ( is = 0 ; is < 10 ; is ++ ) { _rtXdot -> ay2evnqozi [ is ] = 0.0 ;
for ( ci = ir [ is ] ; ci < ir [ is + 1 ] ; ci ++ ) { _rtXdot -> ay2evnqozi [
is ] += rtP . AnalogFilterDesign_A [ ci ] * rtX . ay2evnqozi [ jc [ ci ] ] ;
} } for ( is = 0 ; is < 10 ; is ++ ) { ci = ir_p [ is ] ; while ( ci < ir_p [
is + 1 ] ) { _rtXdot -> ay2evnqozi [ is ] += rtP . AnalogFilterDesign_B * rtB
. clkvycwj4m ; ci = 1 ; } _rtXdot -> efzaicakgx [ is ] = 0.0 ; } for ( is = 0
; is < 10 ; is ++ ) { for ( ci = ir [ is ] ; ci < ir [ is + 1 ] ; ci ++ ) {
_rtXdot -> efzaicakgx [ is ] += rtP . AnalogFilterDesign2_A [ ci ] * rtX .
efzaicakgx [ jc [ ci ] ] ; } } for ( is = 0 ; is < 10 ; is ++ ) { ci = ir_p [
is ] ; while ( ci < ir_p [ is + 1 ] ) { _rtXdot -> efzaicakgx [ is ] += rtP .
AnalogFilterDesign2_B * rtB . clkvycwj4m ; ci = 1 ; } } _rtXdot -> hpywvdhwlx
= rtB . dzdmp2qvuc ; _rtXdot -> dmykij4zst = rtB . a1nwn30zom ; } void
MdlProjection ( void ) { } void MdlTerminate ( void ) { rt_FREE ( rtDW .
i00x1wwgsf . RSimInfoPtr ) ; rt_FREE ( rtDW . jf1myj4gvp . RSimInfoPtr ) ;
rt_TDelayFreeBuf ( rtDW . aw2n3f4po1 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . bmxd34jmp4 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . haguqrracw . TUbufferPtrs [ 0 ] ) ; if (
rt_slioCatalogue ( ) != ( NULL ) ) { void * * slioCatalogueAddr =
rt_slioCatalogueAddr ( ) ; rtwSaveDatasetsToMatFile (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ,
rt_GetMatSigstreamLoggingFileName ( ) ) ; rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = NULL ; } } void
MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 22 ) ;
ssSetNumPeriodicContStates ( rtS , 2 ) ; ssSetNumY ( rtS , 0 ) ; ssSetNumU (
rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ; ssSetNumSampleTimes ( rtS ,
4 ) ; ssSetNumBlocks ( rtS , 32 ) ; ssSetNumBlockIO ( rtS , 10 ) ;
ssSetNumBlockParams ( rtS , 434 ) ; } void MdlInitializeSampleTimes ( void )
{ ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetSampleTime ( rtS , 1 , 0.0 ) ;
ssSetSampleTime ( rtS , 2 , 1.0E-9 ) ; ssSetSampleTime ( rtS , 3 , 8.0E-6 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 1.0 ) ;
ssSetOffsetTime ( rtS , 2 , 0.0 ) ; ssSetOffsetTime ( rtS , 3 , 0.0 ) ; }
void raccel_set_checksum ( ) { ssSetChecksumVal ( rtS , 0 , 4193358515U ) ;
ssSetChecksumVal ( rtS , 1 , 617856143U ) ; ssSetChecksumVal ( rtS , 2 ,
3689207024U ) ; ssSetChecksumVal ( rtS , 3 , 1471515770U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( void ) { static struct _ssMdlInfo mdlInfo
; ( void ) memset ( ( char * ) rtS , 0 , sizeof ( SimStruct ) ) ; ( void )
memset ( ( char * ) & mdlInfo , 0 , sizeof ( struct _ssMdlInfo ) ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ;
( void ) memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = (
void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork ,
0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset (
( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS
, & dtInfo ) ; dtInfo . numDataTypes = 14 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
FSK_2_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS , true
) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2
) ; ssSetModelName ( rtS , "FSK_2" ) ; ssSetPath ( rtS , "FSK_2" ) ;
ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal ( rtS , 0.001496 ) ; { static
RTWLogInfo rt_DataLoggingInfo ; rt_DataLoggingInfo . loggingInterval = NULL ;
ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; } { { static int_T
rt_LoggedStateWidths [ ] = { 10 , 10 , 1 , 1 } ; static int_T
rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 } ; static int_T
rt_LoggedStateDimensions [ ] = { 10 , 10 , 1 , 1 } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE } ; static int_T rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0
} ; static RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs [ ] = {
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) } ; static const char_T *
rt_LoggedStateLabels [ ] = { "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" } ;
static const char_T * rt_LoggedStateBlockNames [ ] = {
"FSK_2/Demux/Analog\nFilter Design" , "FSK_2/Demux/Analog\nFilter Design2" ,
"FSK_2/Transmisor1/Continuous-Time\nVCO/Modulo \nIntegrator/Modulo\nIntegrator"
,
"FSK_2/Transmisor2/Continuous-Time\nVCO/Modulo \nIntegrator/Modulo\nIntegrator"
} ; static const char_T * rt_LoggedStateNames [ ] = { "" , "" , "" , "" } ;
static boolean_T rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0 } ; static
RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 4 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert } ; static void *
rt_LoggedStateSignalPtrs [ 4 ] ; rtliSetLogXSignalPtrs ( ssGetRTWLogInfo (
rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . ay2evnqozi [ 0 ] ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . efzaicakgx [ 0 ] ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtX . hpywvdhwlx ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtX . dmykij4zst ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "tmp_raccel_xout" ) ; rtliSetLogXFinal (
ssGetRTWLogInfo ( rtS ) , "xFinal" ) ; rtliSetLogVarNameModifier (
ssGetRTWLogInfo ( rtS ) , "none" ) ; rtliSetLogFormat ( ssGetRTWLogInfo ( rtS
) , 2 ) ; rtliSetLogMaxRows ( ssGetRTWLogInfo ( rtS ) , 1000 ) ;
rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS ) , 1 ) ; rtliSetLogY (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogYSignalInfo ( ssGetRTWLogInfo (
rtS ) , ( NULL ) ) ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL
) ) ; } { static struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS ,
& statesInfo2 ) ; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ;
ssSetPeriodicContStateIndices ( rtS , rtPeriodicIndX ) ; ( void ) memset ( (
void * ) rtPeriodicIndX , 0 , 2 * sizeof ( int_T ) ) ;
ssSetPeriodicContStateRanges ( rtS , rtPeriodicRngX ) ; ( void ) memset ( (
void * ) rtPeriodicRngX , 0 , 4 * sizeof ( real_T ) ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 22 ] ;
static real_T absTol [ 22 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 } ; static uint8_T absTolControl [ 22 ] = { 0U , 0U , 0U , 0U , 0U ,
0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U
, 0U } ; static real_T contStateJacPerturbBoundMinVec [ 22 ] ; static real_T
contStateJacPerturbBoundMaxVec [ 22 ] ; static ssNonContDerivSigInfo
nonContDerivSigInfo [ 3 ] = { { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
br52h0oi5h ) , ( NULL ) } , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
ixhdtyqkuo ) , ( NULL ) } , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
bdmiwmnwdi ) , ( NULL ) } } ; { int i ; for ( i = 0 ; i < 22 ; ++ i ) {
contStateJacPerturbBoundMinVec [ i ] = 0 ; contStateJacPerturbBoundMaxVec [ i
] = rtGetInf ( ) ; } } ssSetSolverRelTol ( rtS , 0.001 ) ; ssSetStepSize (
rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 ) ; ssSetMaxNumMinSteps ( rtS , -
1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ; ssSetMaxStepSize ( rtS , 1.0E-9
) ; ssSetSolverMaxOrder ( rtS , - 1 ) ; ssSetSolverRefineFactor ( rtS , 1 ) ;
ssSetOutputTimes ( rtS , ( NULL ) ) ; ssSetNumOutputTimes ( rtS , 0 ) ;
ssSetOutputTimesOnly ( rtS , 0 ) ; ssSetOutputTimesIndex ( rtS , 0 ) ;
ssSetZCCacheNeedsReset ( rtS , 0 ) ; ssSetDerivCacheNeedsReset ( rtS , 0 ) ;
ssSetNumNonContDerivSigInfos ( rtS , 3 ) ; ssSetNonContDerivSigInfos ( rtS ,
nonContDerivSigInfo ) ; ssSetSolverInfo ( rtS , & slvrInfo ) ;
ssSetSolverName ( rtS , "ode45" ) ; ssSetVariableStepSolver ( rtS , 1 ) ;
ssSetSolverConsistencyChecking ( rtS , 0 ) ; ssSetSolverAdaptiveZcDetection (
rtS , 0 ) ; ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetAbsTolVector (
rtS , absTol ) ; ssSetAbsTolControlVector ( rtS , absTolControl ) ;
ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetJacobianPerturbationBoundsMinVec ( rtS , contStateJacPerturbBoundMinVec
) ; ssSetJacobianPerturbationBoundsMaxVec ( rtS ,
contStateJacPerturbBoundMaxVec ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ;
ssSetModelLogDataIfInInterval ( rtS , rt_UpdateTXXFYLogVars ) ;
ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 0 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 4193358515U ) ; ssSetChecksumVal ( rtS , 1 ,
617856143U ) ; ssSetChecksumVal ( rtS , 2 , 3689207024U ) ; ssSetChecksumVal
( rtS , 3 , 1471515770U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 1 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; } return
rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 4 ; void MdlOutputsParameterSampleTime (
int_T tid ) { UNUSED_PARAMETER ( tid ) ; }
