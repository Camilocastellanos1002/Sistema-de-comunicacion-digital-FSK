#include "rt_logging_mmi.h"
#include "FSK_capi.h"
#include <math.h>
#include "FSK.h"
#include "FSK_private.h"
#include "FSK_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; extern boolean_T
gblExtModeStartPktReceived ; void raccelForceExtModeShutdown ( ) { if ( !
gblExtModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 5 , & stopRequested ) ; }
rtExtModeShutdown ( 5 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 1 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 6 ; const char_T
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
"slprj\\raccel\\FSK\\FSK_Jpattern.mat" ; const int_T gblNumRootInportBlks = 0
; const int_T gblNumModelInputs = 0 ; extern rtInportTUtable *
gblInportTUtables ; extern const char * gblInportFileName ; extern void *
gblAperiodicPartitionHitTimes ; const int_T gblInportDataTypeIdx [ ] = { - 1
} ; const int_T gblInportDims [ ] = { - 1 } ; const int_T gblInportComplex [
] = { - 1 } ; const int_T gblInportInterpoFlag [ ] = { - 1 } ; const int_T
gblInportContinuous [ ] = { - 1 } ; int_T enableFcnCallFlag [ ] = { 1 , 1 , 1
, 1 , 1 , 1 } ; const char * raccelLoadInputsAndAperiodicHitTimes ( const
char * inportFileName , int * matFileFormat ) { return
rt_RapidReadInportsMatFile ( inportFileName , matFileFormat , 1 ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
B rtB ; X rtX ; PeriodicIndX rtPeriodicIndX ; PeriodicRngX rtPeriodicRngX ;
DW rtDW ; PrevZCX rtPrevZCX ; static SimStruct model_S ; SimStruct * const
rtS = & model_S ;
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
void rt_TDelayFreeBuf ( void * buf ) { utFree ( buf ) ; } void gdhiyz4i3p (
cagpp1qjpe * localB , ng5ktuyqvq * localP ) { localB -> jzxmgvajvp = localP
-> Out1_Y0 ; } void jgvwez5knr ( SimStruct * rtS_e , boolean_T lriha2u4es ,
real_T b1ojo4vufy , cagpp1qjpe * localB , cjdwzvmo5b * localDW , bg3mtgiacz *
localZCE ) { if ( ssIsMajorTimeStep ( rtS_e ) ) { if ( lriha2u4es && (
localZCE -> htztm3ejkl != POS_ZCSIG ) ) { localB -> jzxmgvajvp = b1ojo4vufy ;
localDW -> b4uftfd3jt = 4 ; } localZCE -> htztm3ejkl = lriha2u4es ; } } void
fqkin25sht ( SimStruct * rtS_i , real_T eqs2k4ungi , boolean_T bx3jn4fhmp ,
boolean_T fo0hifrbjv , fu5bk3bmay * localB , gmd13fthxk * localDW ) { if (
eqs2k4ungi > 0.0 ) { localB -> ighgnitevw = ( ( int32_T ) fo0hifrbjv > (
int32_T ) bx3jn4fhmp ) ; if ( ssIsMajorTimeStep ( rtS_i ) ) { srUpdateBC (
localDW -> mnrpt53zog ) ; } } } void edzbs02xos ( SimStruct * rtS_m , real_T
eh13uoyrfq , boolean_T kv0s3nitai , boolean_T owf55xoyw2 , impou4x0jn *
localB , nyhc31mepi * localDW ) { if ( eh13uoyrfq > 0.0 ) { localB ->
ddvcjkqoaj = ( ( int32_T ) owf55xoyw2 < ( int32_T ) kv0s3nitai ) ; if (
ssIsMajorTimeStep ( rtS_m ) ) { srUpdateBC ( localDW -> bl2ajkrwzq ) ; } } }
real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { uint32_T lo ; uint32_T
hi ; lo = * u % 127773U * 16807U ; hi = * u / 127773U * 2836U ; if ( lo < hi
) { * u = 2147483647U - ( hi - lo ) ; } else { * u = lo - hi ; } return (
real_T ) * u * 4.6566128752457969E-10 ; } real_T rt_nrand_Upu32_Yd_f_pw_snf (
uint32_T * u ) { real_T y ; real_T sr ; real_T si ; do { sr = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = sr * sr + si * si ; } while (
si > 1.0 ) ; y = muDoubleScalarSqrt ( - 2.0 * muDoubleScalarLog ( si ) / si )
* sr ; return y ; } void MdlInitialize ( void ) { uint32_T tseed ; int32_T r
; int32_T t ; real_T tmp ; rtX . npfxxayysv = rtP . Integrator_IC ; rtX .
nnu2myvywh = rtP . ModuloIntegrator_IC ; rtX . pmpdgrmizb = rtP .
Integrator_IC_nblk03gvyi ; rtX . fdnkcpfqw2 [ 0 ] = rtP .
Filtro_InitialCondition ; rtX . fdnkcpfqw2 [ 1 ] = rtP .
Filtro_InitialCondition ; rtX . fdnkcpfqw2 [ 2 ] = rtP .
Filtro_InitialCondition ; rtX . fdnkcpfqw2 [ 3 ] = rtP .
Filtro_InitialCondition ; rtX . mjardhsaxq = rtP .
ModuloIntegrator_IC_apzvenlzc5 ; tmp = muDoubleScalarFloor ( rtP .
GaussianNoiseGenerator_s ) ; if ( muDoubleScalarIsNaN ( tmp ) ||
muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; } else { tmp = muDoubleScalarRem
( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0 ? ( uint32_T ) - ( int32_T ) (
uint32_T ) - tmp : ( uint32_T ) tmp ; r = ( int32_T ) ( tseed >> 16U ) ; t =
( int32_T ) ( tseed & 32768U ) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r <<
16U ) ) + t ) << 16U ) + t ) + r ; if ( tseed < 1U ) { tseed = 1144108930U ;
} else { if ( tseed > 2147483646U ) { tseed = 2147483646U ; } } rtDW .
dwuhp2thuf = tseed ; rtDW . dzchlxvwf3 = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW
. dwuhp2thuf ) * rtP . RandomNumber_StdDev + rtP . RandomNumber_Mean ; rtDW .
bybwcm2hrx = rtP . Memory_InitialCondition ; rtDW . p0mgrctrnl = rtP .
Monostable1_ic ; rtDW . lzar0ld5iq = rtP . SampleandHold_ic ; tmp =
muDoubleScalarFloor ( rtP . GaussianNoiseGenerator_s_mqeqzkwvys ) ; if (
muDoubleScalarIsNaN ( tmp ) || muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; }
else { tmp = muDoubleScalarRem ( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0
? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp : ( uint32_T ) tmp ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + t ) << 16U ) + t ) + r ; if ( tseed
< 1U ) { tseed = 1144108930U ; } else { if ( tseed > 2147483646U ) { tseed =
2147483646U ; } } rtDW . h4m3xflze4 = tseed ; rtDW . kqtr3qx2r4 =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . h4m3xflze4 ) * rtP .
RandomNumber_StdDev_ojydngz0lp + rtP . RandomNumber_Mean_n4x5jyjuez ; for ( r
= 0 ; r < 6 ; r ++ ) { rtX . iz0hdnziyp [ r ] = rtP .
Filtro_InitialCondition_ixj5gjnfdp ; } rtX . gusjeimfuy = rtP .
Integrator_IC_dfzts412q5 ; rtDW . kwcxzpft0d = rtP .
Memory_InitialCondition_meb2sac0hw ; rtDW . ljvna4i1sk = rtP . Monostable_ic
; rtDW . f2j0l3sxg1 = rtP . SampleandHold_ic_jlfvpcljxw ; rtDW . c22fq5hb2l =
rtP . Memory_InitialCondition_aqwb21zvmj ; rtDW . isfsg2jso1 = rtP .
Monostable1_ic_bkmb1fdrhz ; rtDW . nea0jvgp55 = rtP .
SampleandHold_ic_lzb14dyui4 ; rtX . ocmfulb5j3 = rtP . Integrator1_IC ; rtX .
nk03khymzz = rtP . ModuloIntegrator_IC_mhkqbc55cu ; rtX . hqbabu1dqz = rtP .
Integrator_IC_hiwtnk3vzy ; rtX . lpsjm2psah = rtP .
ModuloIntegrator_IC_pwbk55yuz2 ; rtX . inqcqvaw3b = rtP .
Integrator1_IC_ggm3f24kg1 ; rtB . m4lv3kzihg = rtP . _Y0_dwtojptuc5 ; rtB .
jmfd3dtamo = rtP . _Y0 ; rtB . lzdd3z4ueb = rtP . _Y0_db5voyihuo ; rtB .
fmyjxkxyji = rtP . _Y0_bdpgvrnswx ; gdhiyz4i3p ( & rtB . jgvwez5knrn , & rtP
. jgvwez5knrn ) ; gdhiyz4i3p ( & rtB . dzgncmrria , & rtP . dzgncmrria ) ;
gdhiyz4i3p ( & rtB . cc2aoo0nhc , & rtP . cc2aoo0nhc ) ; { int_T
rootPeriodicContStateIndices [ 4 ] = { 1 , 7 , 16 , 18 } ; real_T
rootPeriodicContStateRanges [ 8 ] = { 0.0 , 1.0 , 0.0 , 1.0 , 0.0 , 1.0 , 0.0
, 1.0 } ; ( void ) memcpy ( ( void * ) rtPeriodicIndX ,
rootPeriodicContStateIndices , 4 * sizeof ( int_T ) ) ; ( void ) memcpy ( (
void * ) rtPeriodicRngX , rootPeriodicContStateRanges , 8 * sizeof ( real_T )
) ; } } void MdlEnable ( void ) { rtDW . n2ufwbrgzx = 1 ; _ssSetSampleHit (
rtS , 4 , 1 ) ; _ssSetTaskTime ( rtS , 4 , ssGetT ( rtS ) ) ;
_ssSetVarNextHitTime ( rtS , 0 , ssGetT ( rtS ) ) ; ; } void MdlStart ( void
) { { void * * slioCatalogueAddr = rt_slioCatalogueAddr ( ) ; void * r2 = (
NULL ) ; void * * pOSigstreamManagerAddr = ( NULL ) ; const int
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
externalInputIsInDatasetFormat ) { } } { int_T dimensions [ 1 ] = { 1 } ;
rtDW . ovsyej354z . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "mensajerx" , SS_BOOLEAN , 0 , 0 , 0 , 1 , 1 , dimensions ,
NO_LOGVALDIMS , ( NULL ) , ( NULL ) , 0 , 1 , - 1.0 , 1 ) ; if ( rtDW .
ovsyej354z . LoggedData == ( NULL ) ) return ; } { FWksInfo * fromwksInfo ;
if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1 , sizeof ( FWksInfo ) ) ) == (
NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "mensaje " ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) rtP . Informacion_Data0 ; fromwksInfo -> nDataPoints =
182 ; fromwksInfo -> time = ( NULL ) ; rtDW . ap5xq1jhre . TimePtr =
fromwksInfo -> time ; rtDW . ap5xq1jhre . DataPtr = fromwksInfo -> data ;
rtDW . ap5xq1jhre . RSimInfoPtr = fromwksInfo ; } rtDW . ob0eo32bes .
PrevIndex = - 1 ; } { { real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf (
2 , 1024 , sizeof ( real_T ) ) ; if ( pBuffer == ( NULL ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } rtDW
. eioayfkhqd . Tail = 0 ; rtDW . eioayfkhqd . Head = 0 ; rtDW . eioayfkhqd .
Last = 0 ; rtDW . eioayfkhqd . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
lv2dzfblr1 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
lv2dzfblr1 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . hpphhvjiqw . Tail = 0
; rtDW . hpphhvjiqw . Head = 0 ; rtDW . hpphhvjiqw . Last = 0 ; rtDW .
hpphhvjiqw . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_npzkuu2dfa ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . ifklj3sbrn . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
ifklj3sbrn . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . pjaubi5g0r . Tail = 0
; rtDW . pjaubi5g0r . Head = 0 ; rtDW . pjaubi5g0r . Last = 0 ; rtDW .
pjaubi5g0r . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_g2gukl3g33 ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . hd1c30tkpp . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
hd1c30tkpp . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . gtgggrpqsb . Tail = 0
; rtDW . gtgggrpqsb . Head = 0 ; rtDW . gtgggrpqsb . Last = 0 ; rtDW .
gtgggrpqsb . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_itctaj4ekg ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . ge2wwzjib2 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
ge2wwzjib2 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . gfgr3iktyl . Tail = 0
; rtDW . gfgr3iktyl . Head = 0 ; rtDW . gfgr3iktyl . Last = 0 ; rtDW .
gfgr3iktyl . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay12_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
jshlet2ssp . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
jshlet2ssp . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . pttsc0t4lz . Tail = 0
; rtDW . pttsc0t4lz . Head = 0 ; rtDW . pttsc0t4lz . Last = 0 ; rtDW .
pttsc0t4lz . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay2_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
pkzvqa1hj0 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
pkzvqa1hj0 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . eppzhodfly . Tail = 0
; rtDW . eppzhodfly . Head = 0 ; rtDW . eppzhodfly . Last = 0 ; rtDW .
eppzhodfly . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay1_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
pviiww4mxm . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
pviiww4mxm . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . josactzshu . Tail = 0
; rtDW . josactzshu . Head = 0 ; rtDW . josactzshu . Last = 0 ; rtDW .
josactzshu . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay4_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
dwlf21fnwg . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
dwlf21fnwg . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . c3xd1ms0us . Tail = 0
; rtDW . c3xd1ms0us . Head = 0 ; rtDW . c3xd1ms0us . Last = 0 ; rtDW .
c3xd1ms0us . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay3_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
bnamprjobf . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
bnamprjobf . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . odb4cbppzt . Tail = 0
; rtDW . odb4cbppzt . Head = 0 ; rtDW . odb4cbppzt . Last = 0 ; rtDW .
odb4cbppzt . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay6_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
lrrduccxok . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
lrrduccxok . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . deeamvwgxv . Tail = 0
; rtDW . deeamvwgxv . Head = 0 ; rtDW . deeamvwgxv . Last = 0 ; rtDW .
deeamvwgxv . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay5_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
fhjti1tiah . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
fhjti1tiah . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . ftsaljquvy . Tail = 0
; rtDW . ftsaljquvy . Head = 0 ; rtDW . ftsaljquvy . Last = 0 ; rtDW .
ftsaljquvy . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay8_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
faivwg4izm . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
faivwg4izm . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . h0kavv2rvj . Tail = 0
; rtDW . h0kavv2rvj . Head = 0 ; rtDW . h0kavv2rvj . Last = 0 ; rtDW .
h0kavv2rvj . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay7_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
lw4b5iw0r0 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
lw4b5iw0r0 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . orr2azrxe5 . Tail = 0
; rtDW . orr2azrxe5 . Head = 0 ; rtDW . orr2azrxe5 . Last = 0 ; rtDW .
orr2azrxe5 . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay9_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
nhj2clh5pd . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
nhj2clh5pd . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . mrknrsmtwp . Tail = 0
; rtDW . mrknrsmtwp . Head = 0 ; rtDW . mrknrsmtwp . Last = 0 ; rtDW .
mrknrsmtwp . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay11_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
d1uhchttm1 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
d1uhchttm1 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . hdikw2z4pb . Tail = 0
; rtDW . hdikw2z4pb . Head = 0 ; rtDW . hdikw2z4pb . Last = 0 ; rtDW .
hdikw2z4pb . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay10_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
egilahlbnt . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
egilahlbnt . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . oqom4bvhu5 . Tail = 0
; rtDW . oqom4bvhu5 . Head = 0 ; rtDW . oqom4bvhu5 . Last = 0 ; rtDW .
oqom4bvhu5 . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay13_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
lxhyqkdxwz . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
lxhyqkdxwz . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . fpoqultkeo . Tail = 0
; rtDW . fpoqultkeo . Head = 0 ; rtDW . fpoqultkeo . Last = 0 ; rtDW .
fpoqultkeo . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay1_InitOutput_ge1vnqoztc ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . a4exivx0tt . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
a4exivx0tt . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . iexysxku45 . Tail = 0
; rtDW . iexysxku45 . Head = 0 ; rtDW . iexysxku45 . Last = 0 ; rtDW .
iexysxku45 . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_bd4zohbbpk ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . idcmakdjdp . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
idcmakdjdp . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . ivfrpj5iet . Tail = 0
; rtDW . ivfrpj5iet . Head = 0 ; rtDW . ivfrpj5iet . Last = 0 ; rtDW .
ivfrpj5iet . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_ac2nn3i4uy ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . btwgfjuhwu . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
btwgfjuhwu . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . hklidk4rmf . Tail = 0
; rtDW . hklidk4rmf . Head = 0 ; rtDW . hklidk4rmf . Last = 0 ; rtDW .
hklidk4rmf . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay1_InitOutput_dc05214qlk ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . mfdffnmnea . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
mfdffnmnea . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } }
MdlInitialize ( ) ; MdlEnable ( ) ; } void MdlOutputs ( int_T tid ) { real_T
m5svzl2d0r ; real_T df2qweyodv ; real_T bt4v1hgfu1 ; real_T nzb3j55cwr ;
real_T dvd0cnpjzo ; real_T cewfnzvlrx ; real_T pejfdcn22k ; real_T a1ii04vsed
; real_T ovvaoy4j4s ; real_T mmjled0acg ; real_T ojxkax2t5t ; boolean_T
ecvqk10vip ; boolean_T bgzgwcdawz ; boolean_T o2hio1ntaz ; boolean_T
alpoam0d0d ; boolean_T eajnxatdeu ; boolean_T lpt5fbfvi2 ; ZCEventType
zcEvent ; boolean_T fdlbiydiib ; boolean_T ldk2pamjug ; boolean_T cq0tju2coi
; real_T taskTimeV ; uint32_T numCycles ; real_T ratio ; srClearBC ( rtDW .
lomcfztmre ) ; srClearBC ( rtDW . jgvwez5knrn . b4uftfd3jt ) ; srClearBC (
rtDW . fqkin25shtk . mnrpt53zog ) ; srClearBC ( rtDW . edzbs02xos1 .
bl2ajkrwzq ) ; srClearBC ( rtDW . nwsijekr51 ) ; srClearBC ( rtDW .
juqugykvvp ) ; srClearBC ( rtDW . jsih34lehs ) ; srClearBC ( rtDW .
og5vligtf5 ) ; rtB . hao2kgiuqu = rtX . npfxxayysv * rtP . Rb ; rtB .
iea4dkyy2w = muDoubleScalarCos ( rtX . nnu2myvywh * 6.2831853071795862 ) ; if
( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB . iea4dkyy2w > 0.0 ) { rtDW .
oib2ggiaac = 1 ; } else if ( rtB . iea4dkyy2w < 0.0 ) { rtDW . oib2ggiaac = -
1 ; } else { rtDW . oib2ggiaac = 0 ; } if ( rtDW . oib2ggiaac >= rtP .
Switch2_Threshold ) { rtB . bui2nj5eby = rtP . Constant5_Value ; } else { rtB
. bui2nj5eby = rtP . Constant6_Value ; } } if ( ssIsMajorTimeStep ( rtS ) ) {
zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & rtPrevZCX . emmu1baj1n , ( rtB .
bui2nj5eby ) ) ; if ( zcEvent != NO_ZCEVENT ) { rtX . pmpdgrmizb = rtP .
Integrator_IC_nblk03gvyi ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; } } rtB . f5hdbpawyv = rtX . pmpdgrmizb ; rtB . mr1s0bxcpp = 0.0 ; rtB .
mr1s0bxcpp += rtP . Filtro_C * rtX . fdnkcpfqw2 [ 1 ] ; if ( ssIsSampleHit (
rtS , 3 , 0 ) ) { { int_T currIndex = rtDW . ob0eo32bes . PrevIndex + 1 ;
real_T * pDataValues = ( real_T * ) rtDW . ap5xq1jhre . DataPtr ; int
numPoints , lastPoint ; FWksInfo * fromwksInfo = ( FWksInfo * ) rtDW .
ap5xq1jhre . RSimInfoPtr ; numPoints = fromwksInfo -> nDataPoints ; lastPoint
= numPoints - 1 ; if ( currIndex < numPoints ) { pDataValues += currIndex ;
rtB . ghegbffnb0 = * pDataValues ; } else { rtB . ghegbffnb0 = 0.0 ; } rtDW .
ob0eo32bes . PrevIndex = currIndex ; } } { real_T * * uBuffer = ( real_T * *
) & rtDW . lv2dzfblr1 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & rtDW . lv2dzfblr1 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS
) ; real_T tMinusDelay = simTime - rtP . TransportDelay_Delay ; if ( rtP .
TransportDelay_Delay == 0.0 ) m5svzl2d0r = rtB . ghegbffnb0 ; else m5svzl2d0r
= rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
eioayfkhqd . CircularBufSize , & rtDW . eioayfkhqd . Last , rtDW . eioayfkhqd
. Tail , rtDW . eioayfkhqd . Head , rtP . TransportDelay_InitOutput , 1 , (
boolean_T ) ( ssIsMinorTimeStep ( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) ==
ssGetT ( rtS ) ) ) ) ; } rtB . echlwz23fd = rtP . Rb / 2.0 * m5svzl2d0r + rtP
. Frec2 ; { real_T * * uBuffer = ( real_T * * ) & rtDW . ifklj3sbrn .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW . ifklj3sbrn
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; real_T tMinusDelay =
simTime - rtP . Retraso_canal ; df2qweyodv = rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW . hpphhvjiqw .
CircularBufSize , & rtDW . hpphhvjiqw . Last , rtDW . hpphhvjiqw . Tail ,
rtDW . hpphhvjiqw . Head , rtP . TransportDelay_InitOutput_npzkuu2dfa , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) ==
ssGetT ( rtS ) ) ) ) ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB .
ong5vjnb0y = rtP . GaussianNoiseGenerator_d * rtDW . dzchlxvwf3 + rtP .
GaussianNoiseGenerator_m ; rtB . iyoofertyx = rtB . ong5vjnb0y ; } rtB .
brw1yh1ujs = df2qweyodv + rtB . iyoofertyx ; rtB . ibhjdwhj0b = 1.0 / rtP .
Atenuacion_canal * muDoubleScalarCos ( rtX . mjardhsaxq * 6.2831853071795862
) ; { real_T * * uBuffer = ( real_T * * ) & rtDW . hd1c30tkpp . TUbufferPtrs
[ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW . hd1c30tkpp .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; real_T tMinusDelay =
simTime - rtP . TransportDelay_Delay_lnyuh05kkd ; bt4v1hgfu1 =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
pjaubi5g0r . CircularBufSize , & rtDW . pjaubi5g0r . Last , rtDW . pjaubi5g0r
. Tail , rtDW . pjaubi5g0r . Head , rtP .
TransportDelay_InitOutput_g2gukl3g33 , 1 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
brpeccm2su = ( rtB . f5hdbpawyv >= rtP . CompareToConstant_const ) ; }
fdlbiydiib = rtDW . brpeccm2su ; } { real_T * * uBuffer = ( real_T * * ) &
rtDW . ge2wwzjib2 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * )
& rtDW . ge2wwzjib2 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ;
real_T tMinusDelay = simTime - ( ( 0.95 / rtP . Rb ) ) ; rtB . i1k4ywizrv =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
gtgggrpqsb . CircularBufSize , & rtDW . gtgggrpqsb . Last , rtDW . gtgggrpqsb
. Tail , rtDW . gtgggrpqsb . Head , rtP .
TransportDelay_InitOutput_itctaj4ekg , 1 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsMajorTimeStep ( rtS ) ) { zcEvent =
rt_ZCFcn ( ANY_ZERO_CROSSING , & rtPrevZCX . fwipwlsvaq , ( rtB . i1k4ywizrv
) ) ; if ( zcEvent != NO_ZCEVENT ) { rtB . m4lv3kzihg = fdlbiydiib ; rtDW .
jsih34lehs = 4 ; } } rtB . geskkhqdb3 = ( int8_T ) ( ( int8_T ) ( bt4v1hgfu1
!= 0.0 ) ^ ( int8_T ) rtB . m4lv3kzihg ) ; if ( ssIsSampleHit ( rtS , 4 , 0 )
) { taskTimeV = ssGetTaskTime ( rtS , 4 ) ; if ( ssGetTNextWasAdjusted ( rtS
, 4 ) ) { rtDW . akzvs10hux = _ssGetVarNextHitTime ( rtS , 0 ) ; } if ( rtDW
. n2ufwbrgzx != 0 ) { rtDW . n2ufwbrgzx = 0 ; if ( taskTimeV >= rtP .
PulseGenerator_PhaseDelay ) { ratio = ( taskTimeV - rtP .
PulseGenerator_PhaseDelay ) / ( 1.0 / rtP . Rb ) ; numCycles = ( uint32_T )
muDoubleScalarFloor ( ratio ) ; if ( muDoubleScalarAbs ( ( real_T ) (
numCycles + 1U ) - ratio ) < DBL_EPSILON * ratio ) { numCycles ++ ; } rtDW .
j5zzyh4rpr = numCycles ; ratio = ( 1.0 / rtP . Rb * ( real_T ) numCycles +
rtP . PulseGenerator_PhaseDelay ) + 1.0 / rtP . Rb * rtP .
PulseGenerator_Duty / 100.0 ; if ( taskTimeV < ratio ) { rtDW . ljyjgojejj =
1 ; rtDW . akzvs10hux = ratio ; } else { rtDW . ljyjgojejj = 0 ; rtDW .
akzvs10hux = ( real_T ) ( numCycles + 1U ) * ( 1.0 / rtP . Rb ) + rtP .
PulseGenerator_PhaseDelay ; } } else { rtDW . j5zzyh4rpr = rtP .
PulseGenerator_PhaseDelay != 0.0 ? - 1 : 0 ; rtDW . ljyjgojejj = 0 ; rtDW .
akzvs10hux = rtP . PulseGenerator_PhaseDelay ; } } else { if ( rtDW .
akzvs10hux <= taskTimeV ) { if ( rtDW . ljyjgojejj == 1 ) { rtDW . ljyjgojejj
= 0 ; rtDW . akzvs10hux = ( real_T ) ( rtDW . j5zzyh4rpr + 1LL ) * ( 1.0 /
rtP . Rb ) + rtP . PulseGenerator_PhaseDelay ; } else { rtDW . j5zzyh4rpr ++
; rtDW . ljyjgojejj = 1 ; rtDW . akzvs10hux = ( 1.0 / rtP . Rb * rtP .
PulseGenerator_Duty * 0.01 + 1.0 / rtP . Rb * ( real_T ) rtDW . j5zzyh4rpr )
+ rtP . PulseGenerator_PhaseDelay ; } } } _ssSetVarNextHitTime ( rtS , 0 ,
rtDW . akzvs10hux ) ; if ( rtDW . ljyjgojejj == 1 ) { rtB . gfobd5zpxv = rtP
. PulseGenerator_Amp ; } else { rtB . gfobd5zpxv = 0.0 ; } } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsMajorTimeStep ( rtS ) ) { zcEvent =
rt_ZCFcn ( RISING_ZERO_CROSSING , & rtPrevZCX . itvz2yalg2 , ( rtB .
gfobd5zpxv ) ) ; if ( zcEvent != NO_ZCEVENT ) { rtB . jmfd3dtamo = rtB .
geskkhqdb3 ; rtDW . lomcfztmre = 4 ; } } { real_T * * uBuffer = ( real_T * *
) & rtDW . jshlet2ssp . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & rtDW . jshlet2ssp . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS
) ; real_T tMinusDelay = simTime - rtP . TransportDelay12_Delay ; if ( rtP .
TransportDelay12_Delay == 0.0 ) nzb3j55cwr = rtB . i1k4ywizrv ; else
nzb3j55cwr = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer
, rtDW . gfgr3iktyl . CircularBufSize , & rtDW . gfgr3iktyl . Last , rtDW .
gfgr3iktyl . Tail , rtDW . gfgr3iktyl . Head , rtP .
TransportDelay12_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB .
jmi5xid0ph = ssGetT ( rtS ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
cq0tju2coi = ! rtDW . bybwcm2hrx ; if ( rtB . m4lv3kzihg ) { rtB . jknu1nrhnz
= rtP . Constant20_Value ; } else { rtB . jknu1nrhnz = rtP . Constant19_Value
; } rtB . kwwqn5rlhs = rtB . jknu1nrhnz * rtP . Constant1_Value_ju0tizjign ;
} { real_T * * uBuffer = ( real_T * * ) & rtDW . pkzvqa1hj0 . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW . pkzvqa1hj0 . TUbufferPtrs
[ 1 ] ; real_T simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - (
1.0 / rtP . Rb ) ; rtB . aemhoq5few = rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , rtDW . pttsc0t4lz . CircularBufSize , & rtDW .
pttsc0t4lz . Last , rtDW . pttsc0t4lz . Tail , rtDW . pttsc0t4lz . Head , rtP
. TransportDelay2_InitOutput , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . pviiww4mxm . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . pviiww4mxm . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . dkfpnckao5 = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . eppzhodfly . CircularBufSize , & rtDW . eppzhodfly . Last ,
rtDW . eppzhodfly . Tail , rtDW . eppzhodfly . Head , rtP .
TransportDelay1_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . dwlf21fnwg . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . dwlf21fnwg . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . fnydnbixk1 = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . josactzshu . CircularBufSize , & rtDW . josactzshu . Last ,
rtDW . josactzshu . Tail , rtDW . josactzshu . Head , rtP .
TransportDelay4_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . bnamprjobf . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . bnamprjobf . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . lbeln3akc2 = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . c3xd1ms0us . CircularBufSize , & rtDW . c3xd1ms0us . Last ,
rtDW . c3xd1ms0us . Tail , rtDW . c3xd1ms0us . Head , rtP .
TransportDelay3_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . lrrduccxok . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . lrrduccxok . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . jw32jpeck5 = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . odb4cbppzt . CircularBufSize , & rtDW . odb4cbppzt . Last ,
rtDW . odb4cbppzt . Tail , rtDW . odb4cbppzt . Head , rtP .
TransportDelay6_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . fhjti1tiah . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . fhjti1tiah . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . n5sbv1oypg = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . deeamvwgxv . CircularBufSize , & rtDW . deeamvwgxv . Last ,
rtDW . deeamvwgxv . Tail , rtDW . deeamvwgxv . Head , rtP .
TransportDelay5_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . faivwg4izm . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . faivwg4izm . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . m22qmdpsyj = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . ftsaljquvy . CircularBufSize , & rtDW . ftsaljquvy . Last ,
rtDW . ftsaljquvy . Tail , rtDW . ftsaljquvy . Head , rtP .
TransportDelay8_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . lw4b5iw0r0 . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . lw4b5iw0r0 . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . aqj0wixgbx = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . h0kavv2rvj . CircularBufSize , & rtDW . h0kavv2rvj . Last ,
rtDW . h0kavv2rvj . Tail , rtDW . h0kavv2rvj . Head , rtP .
TransportDelay7_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . nhj2clh5pd . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . nhj2clh5pd . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . hjpiowuzne = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . orr2azrxe5 . CircularBufSize , & rtDW . orr2azrxe5 . Last ,
rtDW . orr2azrxe5 . Tail , rtDW . orr2azrxe5 . Head , rtP .
TransportDelay9_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . d1uhchttm1 . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . d1uhchttm1 . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . d2paa5zotr = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . mrknrsmtwp . CircularBufSize , & rtDW . mrknrsmtwp . Last ,
rtDW . mrknrsmtwp . Tail , rtDW . mrknrsmtwp . Head , rtP .
TransportDelay11_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . egilahlbnt . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . egilahlbnt . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . f2wibvryef = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . hdikw2z4pb . CircularBufSize , & rtDW . hdikw2z4pb . Last ,
rtDW . hdikw2z4pb . Tail , rtDW . hdikw2z4pb . Head , rtP .
TransportDelay10_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . lxhyqkdxwz . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . lxhyqkdxwz . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; dvd0cnpjzo = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . oqom4bvhu5 . CircularBufSize , & rtDW . oqom4bvhu5 . Last ,
rtDW . oqom4bvhu5 . Tail , rtDW . oqom4bvhu5 . Head , rtP .
TransportDelay13_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB .
jp5azcgtac = ( ( ( ( ( ( ( ( ( ( ( rtB . aemhoq5few * rtP . Constant2_Value +
rtB . kwwqn5rlhs ) + rtB . dkfpnckao5 * rtP . Constant3_Value ) + rtB .
fnydnbixk1 * rtP . Constant4_Value ) + rtB . lbeln3akc2 * rtP .
Constant5_Value_ak2ogm0bur ) + rtB . jw32jpeck5 * rtP .
Constant6_Value_mfzl25kers ) + rtB . n5sbv1oypg * rtP . Constant7_Value ) +
rtB . m22qmdpsyj * rtP . Constant8_Value ) + rtB . aqj0wixgbx * rtP .
Constant9_Value ) + rtB . hjpiowuzne * rtP . Constant10_Value ) + rtB .
d2paa5zotr * rtP . Constant11_Value ) + rtB . f2wibvryef * rtP .
Constant12_Value ) + dvd0cnpjzo * rtP . Constant13_Value ; if (
ssIsMajorTimeStep ( rtS ) ) { rtDW . ltwnscr23j = ( rtB . jp5azcgtac > rtP .
Switch_Threshold ) ; rtDW . f3anteups0 = ( rtB . jp5azcgtac > rtP .
Switch1_Threshold ) ; } if ( rtDW . ltwnscr23j ) { taskTimeV = rtP .
Constant15_Value ; } else { taskTimeV = rtP . Constant14_Value ; } if ( rtDW
. f3anteups0 ) { ratio = rtP . Constant18_Value ; } else { ratio = rtP .
Constant17_Value ; } rtB . cbutxn4e51 = ( ( taskTimeV != 0.0 ) || ( ratio !=
0.0 ) ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { ecvqk10vip = rtDW .
p0mgrctrnl ; edzbs02xos ( rtS , rtB . hg4tfoauyd [ 0 ] , rtB . cbutxn4e51 ,
ecvqk10vip , & rtB . cvrfqtrsgv , & rtDW . cvrfqtrsgv ) ; fqkin25sht ( rtS ,
rtB . hg4tfoauyd [ 1 ] , rtB . cbutxn4e51 , ecvqk10vip , & rtB . b5dbwkwsrj ,
& rtDW . b5dbwkwsrj ) ; bgzgwcdawz = ( rtB . cvrfqtrsgv . ddvcjkqoaj || rtB .
b5dbwkwsrj . ighgnitevw ) ; rtB . n5sddkmaty = ( cq0tju2coi && bgzgwcdawz ) ;
rtB . hagpe2nohf = rtDW . lzar0ld5iq ; rtB . axx1cycxep = rtP . Datos / rtP .
Rb - 2.2204460492503131E-16 ; } if ( rtB . n5sddkmaty ) { rtB . kj3rknv443 =
rtB . jmi5xid0ph ; } else { rtB . kj3rknv443 = rtB . hagpe2nohf ; } rtB .
dxcynwwxat = rtB . kj3rknv443 + rtB . axx1cycxep ; if ( ssIsSampleHit ( rtS ,
1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . i5mfbygyll = ( rtB .
dxcynwwxat > rtB . jmi5xid0ph ) ; } rtB . bnbr20jdr4 = rtDW . i5mfbygyll ; }
if ( rtB . bnbr20jdr4 ) { rtB . hpuvpoamzd = nzb3j55cwr ; } else { rtB .
hpuvpoamzd = rtP . Constant16_Value ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsMajorTimeStep ( rtS ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
rtPrevZCX . aqaejmbsqc , ( rtB . hpuvpoamzd ) ) ; if ( zcEvent != NO_ZCEVENT
) { if ( ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS ,
1 ) ; ; if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar
* ) ( LogVar * ) ( rtDW . ovsyej354z . LoggedData ) , & rtB . m4lv3kzihg , 0
) ; } } } rtDW . og5vligtf5 = 4 ; } } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) {
rtB . cqkmv0ulyy = rtP . MatrixGain_Gain * rtDW . kqtr3qx2r4 + rtP .
GaussianNoiseGenerator_m_pvxm3ngdo5 ; rtB . fcjlyowfli = rtB . cqkmv0ulyy ; }
{ real_T * * uBuffer = ( real_T * * ) & rtDW . a4exivx0tt . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & rtDW . a4exivx0tt . TUbufferPtrs [
1 ] ; real_T simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 0.5
/ rtP . Frec1 ) ; cewfnzvlrx = rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , rtDW . fpoqultkeo . CircularBufSize , & rtDW .
fpoqultkeo . Last , rtDW . fpoqultkeo . Tail , rtDW . fpoqultkeo . Head , rtP
. TransportDelay1_InitOutput_ge1vnqoztc , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS
) ) ) ) ; } taskTimeV = ( cewfnzvlrx + rtB . mr1s0bxcpp ) * rtP .
Constant_Value + rtB . fcjlyowfli ; { real_T * * uBuffer = ( real_T * * ) &
rtDW . idcmakdjdp . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * )
& rtDW . idcmakdjdp . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ;
real_T tMinusDelay = simTime - ( 0.5 / rtP . Frec2 ) ; pejfdcn22k =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
iexysxku45 . CircularBufSize , & rtDW . iexysxku45 . Last , rtDW . iexysxku45
. Tail , rtDW . iexysxku45 . Head , rtP .
TransportDelay_InitOutput_bd4zohbbpk , 0 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } ratio
= ( pejfdcn22k + rtB . mr1s0bxcpp ) * rtP . Constant_Value + rtB . fcjlyowfli
; rtB . hs1qpln3nc = 0.0 ; rtB . hs1qpln3nc += rtP . Filtro_C_l0jcyicm4y *
rtX . iz0hdnziyp [ 5 ] ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB .
hs1qpln3nc > 0.0 ) { rtDW . cb1jfiyqqe = 1 ; } else if ( rtB . hs1qpln3nc <
0.0 ) { rtDW . cb1jfiyqqe = - 1 ; } else { rtDW . cb1jfiyqqe = 0 ; } rtB .
e15ao1bk3m = rtDW . cb1jfiyqqe ; } if ( ssIsMajorTimeStep ( rtS ) ) { zcEvent
= rt_ZCFcn ( ANY_ZERO_CROSSING , & rtPrevZCX . gcwp0symhu , ( rtB .
bui2nj5eby ) ) ; if ( zcEvent != NO_ZCEVENT ) { rtX . gusjeimfuy = rtP .
Integrator_IC_dfzts412q5 ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; } } rtB . ooknyqiljy = rtX . gusjeimfuy ; rtB . ijufvlmorm = ssGetT ( rtS )
; rtB . mdla3lhngq = ( rtB . bui2nj5eby != 0.0 ) ; if ( ssIsSampleHit ( rtS ,
1 , 0 ) ) { fdlbiydiib = ! rtDW . kwcxzpft0d ; o2hio1ntaz = rtDW . ljvna4i1sk
; edzbs02xos ( rtS , rtB . f2kmaedy0v [ 0 ] , rtB . mdla3lhngq , o2hio1ntaz ,
& rtB . edzbs02xos1 , & rtDW . edzbs02xos1 ) ; fqkin25sht ( rtS , rtB .
f2kmaedy0v [ 1 ] , rtB . mdla3lhngq , o2hio1ntaz , & rtB . fqkin25shtk , &
rtDW . fqkin25shtk ) ; alpoam0d0d = ( rtB . edzbs02xos1 . ddvcjkqoaj || rtB .
fqkin25shtk . ighgnitevw ) ; rtB . lisqze2m0v = ( fdlbiydiib && alpoam0d0d )
; rtB . jsr2vw3sph = rtDW . f2j0l3sxg1 ; rtB . mzfkqi1te1 = 0.9 / rtP . Rb -
2.2204460492503131E-16 ; } if ( rtB . lisqze2m0v ) { rtB . d1ncaq24su = rtB .
ijufvlmorm ; } else { rtB . d1ncaq24su = rtB . jsr2vw3sph ; } rtB .
nvde5gnl32 = rtB . d1ncaq24su + rtB . mzfkqi1te1 ; if ( ssIsSampleHit ( rtS ,
1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . en3gkuykg0 = ( rtB .
nvde5gnl32 > rtB . ijufvlmorm ) ; } rtB . akkrfuecb2 = rtDW . en3gkuykg0 ; }
rtB . cpzsxqkvzb = rtB . akkrfuecb2 ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
if ( ssIsMajorTimeStep ( rtS ) ) { if ( ( ! rtB . cpzsxqkvzb ) && ( rtPrevZCX
. osoivfua0c != ZERO_ZCSIG ) ) { rtB . lzdd3z4ueb = rtB . ooknyqiljy ; rtDW .
nwsijekr51 = 4 ; } rtPrevZCX . osoivfua0c = rtB . cpzsxqkvzb ; } rtB .
inulkftw3y = muDoubleScalarAbs ( rtB . lzdd3z4ueb ) ; ldk2pamjug = ! rtDW .
c22fq5hb2l ; } rtB . pdl3oaaxvv = ssGetT ( rtS ) ; rtB . pk0yjglikg = ( rtB .
bui2nj5eby != 0.0 ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { eajnxatdeu =
rtDW . isfsg2jso1 ; edzbs02xos ( rtS , rtB . btp22atm5y [ 0 ] , rtB .
pk0yjglikg , eajnxatdeu , & rtB . cfrh4agkgq , & rtDW . cfrh4agkgq ) ;
fqkin25sht ( rtS , rtB . btp22atm5y [ 1 ] , rtB . pk0yjglikg , eajnxatdeu , &
rtB . awkevlz2ww , & rtDW . awkevlz2ww ) ; lpt5fbfvi2 = ( rtB . cfrh4agkgq .
ddvcjkqoaj || rtB . awkevlz2ww . ighgnitevw ) ; rtB . hu24p5k4qk = (
ldk2pamjug && lpt5fbfvi2 ) ; rtB . bbud2xrwvw = rtDW . nea0jvgp55 ; rtB .
ik1ga1yi4x = 0.1 / rtP . Rb - 2.2204460492503131E-16 ; } if ( rtB .
hu24p5k4qk ) { rtB . nhklduoiog = rtB . pdl3oaaxvv ; } else { rtB .
nhklduoiog = rtB . bbud2xrwvw ; } rtB . mpss00ytce = rtB . nhklduoiog + rtB .
ik1ga1yi4x ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep (
rtS ) ) { rtDW . ht5i5wmo5i = ( rtB . mpss00ytce > rtB . pdl3oaaxvv ) ; } rtB
. plthkbxpdz = rtDW . ht5i5wmo5i ; } if ( ssIsMajorTimeStep ( rtS ) ) {
fdlbiydiib = ( ( ! rtB . plthkbxpdz ) && ( rtPrevZCX . ck5u1lzcvp !=
ZERO_ZCSIG ) ) ; rtPrevZCX . ck5u1lzcvp = rtB . plthkbxpdz ; if ( fdlbiydiib
) { rtX . ocmfulb5j3 = rtP . Integrator1_IC ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } } rtB . iuiswtbqno =
rtX . ocmfulb5j3 ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . jhkfehrm4t = (
rtB . iuiswtbqno >= 0.0 ) ; } rtB . ctnzwjmcme = rtB . inulkftw3y - ( rtDW .
jhkfehrm4t > 0 ? rtB . iuiswtbqno : - rtB . iuiswtbqno ) ; if ( ssIsSampleHit
( rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { zcEvent = rt_ZCFcn (
ANY_ZERO_CROSSING , & rtPrevZCX . jcttspjmiw , ( rtB . bui2nj5eby ) ) ; if (
zcEvent != NO_ZCEVENT ) { rtB . fmyjxkxyji = rtB . ctnzwjmcme ; rtDW .
juqugykvvp = 4 ; } } } rtB . oarcyjxd4w = ssGetT ( rtS ) ; if ( ssIsSampleHit
( rtS , 1 , 0 ) ) { rtB . kkn0pryfbs = rtP . kv2 * rtB . fmyjxkxyji + rtP .
Rb / 2.0 ; jgvwez5knr ( rtS , alpoam0d0d , rtB . oarcyjxd4w , & rtB .
jgvwez5knrn , & rtDW . jgvwez5knrn , & rtPrevZCX . jgvwez5knrn ) ; rtB .
h3jkxjjtu0 = rtB . jgvwez5knrn . jzxmgvajvp + rtP . Constant_Value_pgh0qhw5wr
; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . dmhkjfkzni = ( rtB . h3jkxjjtu0 >
rtB . oarcyjxd4w ) ; } } rtB . lwvzpms5bv = ssGetT ( rtS ) ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { jgvwez5knr ( rtS , lpt5fbfvi2 , rtB .
lwvzpms5bv , & rtB . dzgncmrria , & rtDW . dzgncmrria , & rtPrevZCX .
dzgncmrria ) ; rtB . oru1g5vkau = rtB . dzgncmrria . jzxmgvajvp + rtP .
Constant_Value_czlel2g4xm ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
giqgg3q5tt = ( rtB . oru1g5vkau > rtB . lwvzpms5bv ) ; } } { real_T * *
uBuffer = ( real_T * * ) & rtDW . btwgfjuhwu . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . btwgfjuhwu . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 0.25 / rtP .
Frec1 ) ; a1ii04vsed = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , rtDW . ivfrpj5iet . CircularBufSize , & rtDW . ivfrpj5iet . Last
, rtDW . ivfrpj5iet . Tail , rtDW . ivfrpj5iet . Head , rtP .
TransportDelay_InitOutput_ac2nn3i4uy , 0 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB .
jiqtvtg4mt = 1.0 / rtP . Atenuacion_canal * a1ii04vsed * ratio ; { real_T * *
uBuffer = ( real_T * * ) & rtDW . mfdffnmnea . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . mfdffnmnea . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 0.25 / rtP .
Frec2 ) ; ovvaoy4j4s = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , rtDW . hklidk4rmf . CircularBufSize , & rtDW . hklidk4rmf . Last
, rtDW . hklidk4rmf . Tail , rtDW . hklidk4rmf . Head , rtP .
TransportDelay1_InitOutput_dc05214qlk , 0 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB .
fwzg1qmdog = rtB . jiqtvtg4mt - 1.0 / rtP . Atenuacion_canal * ovvaoy4j4s *
taskTimeV ; rtB . kaaziuo5ef = muDoubleScalarCos ( rtX . nk03khymzz *
6.2831853071795862 ) ; ratio = ratio * rtP . Atenuacion_canal * rtB .
kaaziuo5ef ; mmjled0acg = rtP . R2 / rtP . R1 * ratio + rtX . hqbabu1dqz ;
rtB . jwmjcxympi = muDoubleScalarCos ( rtX . lpsjm2psah * 6.2831853071795862
) ; taskTimeV *= rtB . jwmjcxympi * rtP . Atenuacion_canal ; ojxkax2t5t = rtP
. R2 / rtP . R1 * taskTimeV + rtX . inqcqvaw3b ; rtB . ma2rvcr4nq = rtP . kv
* mmjled0acg + rtP . Frec1 ; rtB . akirm2mhww = rtP . kv * ojxkax2t5t + rtP .
Frec2 ; rtB . ftsmahysaw = 1.0 / ( rtP . R1 * rtP . C ) * ratio ; rtB .
furzsgxei5 = 1.0 / ( rtP . R1 * rtP . C ) * taskTimeV ; rtB . kp4mtdwxq5 =
ssGetT ( rtS ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { jgvwez5knr ( rtS ,
bgzgwcdawz , rtB . kp4mtdwxq5 , & rtB . cc2aoo0nhc , & rtDW . cc2aoo0nhc , &
rtPrevZCX . cc2aoo0nhc ) ; rtB . bd1h4kdhj0 = rtB . cc2aoo0nhc . jzxmgvajvp +
rtP . Constant_Value_dufhvts2ca ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
g31sjopxfu = ( rtB . bd1h4kdhj0 > rtB . kp4mtdwxq5 ) ; } } UNUSED_PARAMETER (
tid ) ; } void MdlOutputsTID5 ( int_T tid ) { switch ( ( int32_T ) rtP .
Constant1_Value ) { case 1 : rtB . f2kmaedy0v [ 0 ] = rtP . posedge_Value [ 0
] ; rtB . f2kmaedy0v [ 1 ] = rtP . posedge_Value [ 1 ] ; break ; case 2 : rtB
. f2kmaedy0v [ 0 ] = rtP . negedge_Value [ 0 ] ; rtB . f2kmaedy0v [ 1 ] = rtP
. negedge_Value [ 1 ] ; break ; default : rtB . f2kmaedy0v [ 0 ] = rtP .
eitheredge_Value [ 0 ] ; rtB . f2kmaedy0v [ 1 ] = rtP . eitheredge_Value [ 1
] ; break ; } switch ( ( int32_T ) rtP . Constant1_Value_bx4tgv4ysd ) { case
1 : rtB . btp22atm5y [ 0 ] = rtP . posedge_Value_dx0lu3aoqz [ 0 ] ; rtB .
btp22atm5y [ 1 ] = rtP . posedge_Value_dx0lu3aoqz [ 1 ] ; break ; case 2 :
rtB . btp22atm5y [ 0 ] = rtP . negedge_Value_kjod1cdk3f [ 0 ] ; rtB .
btp22atm5y [ 1 ] = rtP . negedge_Value_kjod1cdk3f [ 1 ] ; break ; default :
rtB . btp22atm5y [ 0 ] = rtP . eitheredge_Value_mhaz3orisj [ 0 ] ; rtB .
btp22atm5y [ 1 ] = rtP . eitheredge_Value_mhaz3orisj [ 1 ] ; break ; } switch
( ( int32_T ) rtP . Constant1_Value_j11evhb4ur ) { case 1 : rtB . hg4tfoauyd
[ 0 ] = rtP . posedge_Value_arvlrnf2hc [ 0 ] ; rtB . hg4tfoauyd [ 1 ] = rtP .
posedge_Value_arvlrnf2hc [ 1 ] ; break ; case 2 : rtB . hg4tfoauyd [ 0 ] =
rtP . negedge_Value_abbvesy1jz [ 0 ] ; rtB . hg4tfoauyd [ 1 ] = rtP .
negedge_Value_abbvesy1jz [ 1 ] ; break ; default : rtB . hg4tfoauyd [ 0 ] =
rtP . eitheredge_Value_nb0pdzkjaa [ 0 ] ; rtB . hg4tfoauyd [ 1 ] = rtP .
eitheredge_Value_nb0pdzkjaa [ 1 ] ; break ; } UNUSED_PARAMETER ( tid ) ; }
void MdlUpdate ( int_T tid ) { { real_T * * uBuffer = ( real_T * * ) & rtDW .
lv2dzfblr1 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. lv2dzfblr1 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
eioayfkhqd . Head = ( ( rtDW . eioayfkhqd . Head < ( rtDW . eioayfkhqd .
CircularBufSize - 1 ) ) ? ( rtDW . eioayfkhqd . Head + 1 ) : 0 ) ; if ( rtDW
. eioayfkhqd . Head == rtDW . eioayfkhqd . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . eioayfkhqd . CircularBufSize , & rtDW
. eioayfkhqd . Tail , & rtDW . eioayfkhqd . Head , & rtDW . eioayfkhqd . Last
, simTime - rtP . TransportDelay_Delay , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . eioayfkhqd . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . eioayfkhqd . Head ] = simTime ; ( * uBuffer ) [ rtDW .
eioayfkhqd . Head ] = rtB . ghegbffnb0 ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . ifklj3sbrn . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . ifklj3sbrn . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . hpphhvjiqw . Head = ( ( rtDW . hpphhvjiqw . Head < ( rtDW .
hpphhvjiqw . CircularBufSize - 1 ) ) ? ( rtDW . hpphhvjiqw . Head + 1 ) : 0 )
; if ( rtDW . hpphhvjiqw . Head == rtDW . hpphhvjiqw . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . hpphhvjiqw . CircularBufSize , & rtDW
. hpphhvjiqw . Tail , & rtDW . hpphhvjiqw . Head , & rtDW . hpphhvjiqw . Last
, simTime - rtP . Retraso_canal , tBuffer , uBuffer , ( NULL ) , ( boolean_T
) 0 , false , & rtDW . hpphhvjiqw . MaxNewBufSize ) ) { ssSetErrorStatus (
rtS , "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW
. hpphhvjiqw . Head ] = simTime ; ( * uBuffer ) [ rtDW . hpphhvjiqw . Head ]
= rtB . ibhjdwhj0b ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW .
dzchlxvwf3 = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . dwuhp2thuf ) * rtP .
RandomNumber_StdDev + rtP . RandomNumber_Mean ; } { real_T * * uBuffer = (
real_T * * ) & rtDW . hd1c30tkpp . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & rtDW . hd1c30tkpp . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( rtS ) ; rtDW . pjaubi5g0r . Head = ( ( rtDW . pjaubi5g0r . Head < (
rtDW . pjaubi5g0r . CircularBufSize - 1 ) ) ? ( rtDW . pjaubi5g0r . Head + 1
) : 0 ) ; if ( rtDW . pjaubi5g0r . Head == rtDW . pjaubi5g0r . Tail ) { if (
! rt_TDelayUpdateTailOrGrowBuf ( & rtDW . pjaubi5g0r . CircularBufSize , &
rtDW . pjaubi5g0r . Tail , & rtDW . pjaubi5g0r . Head , & rtDW . pjaubi5g0r .
Last , simTime - rtP . TransportDelay_Delay_lnyuh05kkd , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & rtDW . pjaubi5g0r . MaxNewBufSize ) )
{ ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } }
( * tBuffer ) [ rtDW . pjaubi5g0r . Head ] = simTime ; ( * uBuffer ) [ rtDW .
pjaubi5g0r . Head ] = rtB . ghegbffnb0 ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . ge2wwzjib2 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . ge2wwzjib2 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . gtgggrpqsb . Head = ( ( rtDW . gtgggrpqsb . Head < ( rtDW .
gtgggrpqsb . CircularBufSize - 1 ) ) ? ( rtDW . gtgggrpqsb . Head + 1 ) : 0 )
; if ( rtDW . gtgggrpqsb . Head == rtDW . gtgggrpqsb . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . gtgggrpqsb . CircularBufSize , & rtDW
. gtgggrpqsb . Tail , & rtDW . gtgggrpqsb . Head , & rtDW . gtgggrpqsb . Last
, simTime - ( ( 0.95 / rtP . Rb ) ) , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . gtgggrpqsb . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . gtgggrpqsb . Head ] = simTime ; ( * uBuffer ) [ rtDW .
gtgggrpqsb . Head ] = rtB . bui2nj5eby ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . jshlet2ssp . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . jshlet2ssp . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . gfgr3iktyl . Head = ( ( rtDW . gfgr3iktyl . Head < ( rtDW .
gfgr3iktyl . CircularBufSize - 1 ) ) ? ( rtDW . gfgr3iktyl . Head + 1 ) : 0 )
; if ( rtDW . gfgr3iktyl . Head == rtDW . gfgr3iktyl . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . gfgr3iktyl . CircularBufSize , & rtDW
. gfgr3iktyl . Tail , & rtDW . gfgr3iktyl . Head , & rtDW . gfgr3iktyl . Last
, simTime - rtP . TransportDelay12_Delay , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . gfgr3iktyl . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . gfgr3iktyl . Head ] = simTime ; ( * uBuffer ) [ rtDW .
gfgr3iktyl . Head ] = rtB . i1k4ywizrv ; } if ( ssIsSampleHit ( rtS , 1 , 0 )
) { rtDW . bybwcm2hrx = rtB . bnbr20jdr4 ; } { real_T * * uBuffer = ( real_T
* * ) & rtDW . pkzvqa1hj0 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & rtDW . pkzvqa1hj0 . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( rtS ) ; rtDW . pttsc0t4lz . Head = ( ( rtDW . pttsc0t4lz . Head < (
rtDW . pttsc0t4lz . CircularBufSize - 1 ) ) ? ( rtDW . pttsc0t4lz . Head + 1
) : 0 ) ; if ( rtDW . pttsc0t4lz . Head == rtDW . pttsc0t4lz . Tail ) { if (
! rt_TDelayUpdateTailOrGrowBuf ( & rtDW . pttsc0t4lz . CircularBufSize , &
rtDW . pttsc0t4lz . Tail , & rtDW . pttsc0t4lz . Head , & rtDW . pttsc0t4lz .
Last , simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . pttsc0t4lz . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . pttsc0t4lz . Head ] = simTime ; ( * uBuffer ) [ rtDW .
pttsc0t4lz . Head ] = rtB . jknu1nrhnz ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . pviiww4mxm . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . pviiww4mxm . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . eppzhodfly . Head = ( ( rtDW . eppzhodfly . Head < ( rtDW .
eppzhodfly . CircularBufSize - 1 ) ) ? ( rtDW . eppzhodfly . Head + 1 ) : 0 )
; if ( rtDW . eppzhodfly . Head == rtDW . eppzhodfly . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . eppzhodfly . CircularBufSize , & rtDW
. eppzhodfly . Tail , & rtDW . eppzhodfly . Head , & rtDW . eppzhodfly . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . eppzhodfly . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
eppzhodfly . Head ] = simTime ; ( * uBuffer ) [ rtDW . eppzhodfly . Head ] =
rtB . aemhoq5few ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
dwlf21fnwg . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. dwlf21fnwg . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
josactzshu . Head = ( ( rtDW . josactzshu . Head < ( rtDW . josactzshu .
CircularBufSize - 1 ) ) ? ( rtDW . josactzshu . Head + 1 ) : 0 ) ; if ( rtDW
. josactzshu . Head == rtDW . josactzshu . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . josactzshu . CircularBufSize , & rtDW
. josactzshu . Tail , & rtDW . josactzshu . Head , & rtDW . josactzshu . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . josactzshu . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
josactzshu . Head ] = simTime ; ( * uBuffer ) [ rtDW . josactzshu . Head ] =
rtB . dkfpnckao5 ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
bnamprjobf . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. bnamprjobf . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
c3xd1ms0us . Head = ( ( rtDW . c3xd1ms0us . Head < ( rtDW . c3xd1ms0us .
CircularBufSize - 1 ) ) ? ( rtDW . c3xd1ms0us . Head + 1 ) : 0 ) ; if ( rtDW
. c3xd1ms0us . Head == rtDW . c3xd1ms0us . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . c3xd1ms0us . CircularBufSize , & rtDW
. c3xd1ms0us . Tail , & rtDW . c3xd1ms0us . Head , & rtDW . c3xd1ms0us . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . c3xd1ms0us . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
c3xd1ms0us . Head ] = simTime ; ( * uBuffer ) [ rtDW . c3xd1ms0us . Head ] =
rtB . fnydnbixk1 ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
lrrduccxok . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. lrrduccxok . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
odb4cbppzt . Head = ( ( rtDW . odb4cbppzt . Head < ( rtDW . odb4cbppzt .
CircularBufSize - 1 ) ) ? ( rtDW . odb4cbppzt . Head + 1 ) : 0 ) ; if ( rtDW
. odb4cbppzt . Head == rtDW . odb4cbppzt . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . odb4cbppzt . CircularBufSize , & rtDW
. odb4cbppzt . Tail , & rtDW . odb4cbppzt . Head , & rtDW . odb4cbppzt . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . odb4cbppzt . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
odb4cbppzt . Head ] = simTime ; ( * uBuffer ) [ rtDW . odb4cbppzt . Head ] =
rtB . lbeln3akc2 ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
fhjti1tiah . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. fhjti1tiah . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
deeamvwgxv . Head = ( ( rtDW . deeamvwgxv . Head < ( rtDW . deeamvwgxv .
CircularBufSize - 1 ) ) ? ( rtDW . deeamvwgxv . Head + 1 ) : 0 ) ; if ( rtDW
. deeamvwgxv . Head == rtDW . deeamvwgxv . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . deeamvwgxv . CircularBufSize , & rtDW
. deeamvwgxv . Tail , & rtDW . deeamvwgxv . Head , & rtDW . deeamvwgxv . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . deeamvwgxv . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
deeamvwgxv . Head ] = simTime ; ( * uBuffer ) [ rtDW . deeamvwgxv . Head ] =
rtB . jw32jpeck5 ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
faivwg4izm . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. faivwg4izm . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
ftsaljquvy . Head = ( ( rtDW . ftsaljquvy . Head < ( rtDW . ftsaljquvy .
CircularBufSize - 1 ) ) ? ( rtDW . ftsaljquvy . Head + 1 ) : 0 ) ; if ( rtDW
. ftsaljquvy . Head == rtDW . ftsaljquvy . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . ftsaljquvy . CircularBufSize , & rtDW
. ftsaljquvy . Tail , & rtDW . ftsaljquvy . Head , & rtDW . ftsaljquvy . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . ftsaljquvy . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
ftsaljquvy . Head ] = simTime ; ( * uBuffer ) [ rtDW . ftsaljquvy . Head ] =
rtB . n5sbv1oypg ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
lw4b5iw0r0 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. lw4b5iw0r0 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
h0kavv2rvj . Head = ( ( rtDW . h0kavv2rvj . Head < ( rtDW . h0kavv2rvj .
CircularBufSize - 1 ) ) ? ( rtDW . h0kavv2rvj . Head + 1 ) : 0 ) ; if ( rtDW
. h0kavv2rvj . Head == rtDW . h0kavv2rvj . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . h0kavv2rvj . CircularBufSize , & rtDW
. h0kavv2rvj . Tail , & rtDW . h0kavv2rvj . Head , & rtDW . h0kavv2rvj . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . h0kavv2rvj . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
h0kavv2rvj . Head ] = simTime ; ( * uBuffer ) [ rtDW . h0kavv2rvj . Head ] =
rtB . m22qmdpsyj ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
nhj2clh5pd . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. nhj2clh5pd . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
orr2azrxe5 . Head = ( ( rtDW . orr2azrxe5 . Head < ( rtDW . orr2azrxe5 .
CircularBufSize - 1 ) ) ? ( rtDW . orr2azrxe5 . Head + 1 ) : 0 ) ; if ( rtDW
. orr2azrxe5 . Head == rtDW . orr2azrxe5 . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . orr2azrxe5 . CircularBufSize , & rtDW
. orr2azrxe5 . Tail , & rtDW . orr2azrxe5 . Head , & rtDW . orr2azrxe5 . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . orr2azrxe5 . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
orr2azrxe5 . Head ] = simTime ; ( * uBuffer ) [ rtDW . orr2azrxe5 . Head ] =
rtB . aqj0wixgbx ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
d1uhchttm1 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. d1uhchttm1 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
mrknrsmtwp . Head = ( ( rtDW . mrknrsmtwp . Head < ( rtDW . mrknrsmtwp .
CircularBufSize - 1 ) ) ? ( rtDW . mrknrsmtwp . Head + 1 ) : 0 ) ; if ( rtDW
. mrknrsmtwp . Head == rtDW . mrknrsmtwp . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . mrknrsmtwp . CircularBufSize , & rtDW
. mrknrsmtwp . Tail , & rtDW . mrknrsmtwp . Head , & rtDW . mrknrsmtwp . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . mrknrsmtwp . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
mrknrsmtwp . Head ] = simTime ; ( * uBuffer ) [ rtDW . mrknrsmtwp . Head ] =
rtB . hjpiowuzne ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
egilahlbnt . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. egilahlbnt . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
hdikw2z4pb . Head = ( ( rtDW . hdikw2z4pb . Head < ( rtDW . hdikw2z4pb .
CircularBufSize - 1 ) ) ? ( rtDW . hdikw2z4pb . Head + 1 ) : 0 ) ; if ( rtDW
. hdikw2z4pb . Head == rtDW . hdikw2z4pb . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . hdikw2z4pb . CircularBufSize , & rtDW
. hdikw2z4pb . Tail , & rtDW . hdikw2z4pb . Head , & rtDW . hdikw2z4pb . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . hdikw2z4pb . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
hdikw2z4pb . Head ] = simTime ; ( * uBuffer ) [ rtDW . hdikw2z4pb . Head ] =
rtB . d2paa5zotr ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
lxhyqkdxwz . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. lxhyqkdxwz . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
oqom4bvhu5 . Head = ( ( rtDW . oqom4bvhu5 . Head < ( rtDW . oqom4bvhu5 .
CircularBufSize - 1 ) ) ? ( rtDW . oqom4bvhu5 . Head + 1 ) : 0 ) ; if ( rtDW
. oqom4bvhu5 . Head == rtDW . oqom4bvhu5 . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . oqom4bvhu5 . CircularBufSize , & rtDW
. oqom4bvhu5 . Tail , & rtDW . oqom4bvhu5 . Head , & rtDW . oqom4bvhu5 . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . oqom4bvhu5 . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
oqom4bvhu5 . Head ] = simTime ; ( * uBuffer ) [ rtDW . oqom4bvhu5 . Head ] =
rtB . f2wibvryef ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . p0mgrctrnl
= rtB . cbutxn4e51 ; rtDW . lzar0ld5iq = rtB . kj3rknv443 ; } if (
ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW . kqtr3qx2r4 =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . h4m3xflze4 ) * rtP .
RandomNumber_StdDev_ojydngz0lp + rtP . RandomNumber_Mean_n4x5jyjuez ; } {
real_T * * uBuffer = ( real_T * * ) & rtDW . a4exivx0tt . TUbufferPtrs [ 0 ]
; real_T * * tBuffer = ( real_T * * ) & rtDW . a4exivx0tt . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( rtS ) ; rtDW . fpoqultkeo . Head = ( ( rtDW .
fpoqultkeo . Head < ( rtDW . fpoqultkeo . CircularBufSize - 1 ) ) ? ( rtDW .
fpoqultkeo . Head + 1 ) : 0 ) ; if ( rtDW . fpoqultkeo . Head == rtDW .
fpoqultkeo . Tail ) { if ( ! rt_TDelayUpdateTailOrGrowBuf ( & rtDW .
fpoqultkeo . CircularBufSize , & rtDW . fpoqultkeo . Tail , & rtDW .
fpoqultkeo . Head , & rtDW . fpoqultkeo . Last , simTime - ( 0.5 / rtP .
Frec1 ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & rtDW .
fpoqultkeo . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
fpoqultkeo . Head ] = simTime ; ( * uBuffer ) [ rtDW . fpoqultkeo . Head ] =
rtB . mr1s0bxcpp ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
idcmakdjdp . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. idcmakdjdp . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
iexysxku45 . Head = ( ( rtDW . iexysxku45 . Head < ( rtDW . iexysxku45 .
CircularBufSize - 1 ) ) ? ( rtDW . iexysxku45 . Head + 1 ) : 0 ) ; if ( rtDW
. iexysxku45 . Head == rtDW . iexysxku45 . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . iexysxku45 . CircularBufSize , & rtDW
. iexysxku45 . Tail , & rtDW . iexysxku45 . Head , & rtDW . iexysxku45 . Last
, simTime - ( 0.5 / rtP . Frec2 ) , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . iexysxku45 . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . iexysxku45 . Head ] = simTime ; ( * uBuffer ) [ rtDW .
iexysxku45 . Head ] = rtB . mr1s0bxcpp ; } if ( ssIsSampleHit ( rtS , 1 , 0 )
) { rtDW . kwcxzpft0d = rtB . akkrfuecb2 ; rtDW . ljvna4i1sk = rtB .
mdla3lhngq ; rtDW . f2j0l3sxg1 = rtB . d1ncaq24su ; rtDW . c22fq5hb2l = rtB .
plthkbxpdz ; rtDW . isfsg2jso1 = rtB . pk0yjglikg ; rtDW . nea0jvgp55 = rtB .
nhklduoiog ; } { real_T * * uBuffer = ( real_T * * ) & rtDW . btwgfjuhwu .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW . btwgfjuhwu
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW . ivfrpj5iet .
Head = ( ( rtDW . ivfrpj5iet . Head < ( rtDW . ivfrpj5iet . CircularBufSize -
1 ) ) ? ( rtDW . ivfrpj5iet . Head + 1 ) : 0 ) ; if ( rtDW . ivfrpj5iet .
Head == rtDW . ivfrpj5iet . Tail ) { if ( ! rt_TDelayUpdateTailOrGrowBuf ( &
rtDW . ivfrpj5iet . CircularBufSize , & rtDW . ivfrpj5iet . Tail , & rtDW .
ivfrpj5iet . Head , & rtDW . ivfrpj5iet . Last , simTime - ( 0.25 / rtP .
Frec1 ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & rtDW .
ivfrpj5iet . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
ivfrpj5iet . Head ] = simTime ; ( * uBuffer ) [ rtDW . ivfrpj5iet . Head ] =
rtB . kaaziuo5ef ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
mfdffnmnea . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. mfdffnmnea . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
hklidk4rmf . Head = ( ( rtDW . hklidk4rmf . Head < ( rtDW . hklidk4rmf .
CircularBufSize - 1 ) ) ? ( rtDW . hklidk4rmf . Head + 1 ) : 0 ) ; if ( rtDW
. hklidk4rmf . Head == rtDW . hklidk4rmf . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . hklidk4rmf . CircularBufSize , & rtDW
. hklidk4rmf . Tail , & rtDW . hklidk4rmf . Head , & rtDW . hklidk4rmf . Last
, simTime - ( 0.25 / rtP . Frec2 ) , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . hklidk4rmf . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . hklidk4rmf . Head ] = simTime ; ( * uBuffer ) [ rtDW .
hklidk4rmf . Head ] = rtB . jwmjcxympi ; } UNUSED_PARAMETER ( tid ) ; } void
MdlUpdateTID5 ( int_T tid ) { UNUSED_PARAMETER ( tid ) ; } void
MdlDerivatives ( void ) { int_T is ; int_T ci ; static const int8_T ir [ 7 ]
= { 0 , 2 , 3 , 6 , 7 , 10 , 11 } ; static const int8_T ir_p [ 7 ] = { 0 , 1
, 1 , 1 , 1 , 1 , 1 } ; static const int8_T jc [ 11 ] = { 0 , 1 , 0 , 1 , 2 ,
3 , 2 , 3 , 4 , 5 , 4 } ; XDot * _rtXdot ; _rtXdot = ( ( XDot * ) ssGetdX (
rtS ) ) ; _rtXdot -> npfxxayysv = rtB . jmfd3dtamo ; _rtXdot -> nnu2myvywh =
rtB . kkn0pryfbs ; _rtXdot -> pmpdgrmizb = rtB . e15ao1bk3m ; _rtXdot ->
fdnkcpfqw2 [ 0 ] = 0.0 ; _rtXdot -> fdnkcpfqw2 [ 1 ] = 0.0 ; _rtXdot ->
fdnkcpfqw2 [ 2 ] = 0.0 ; _rtXdot -> fdnkcpfqw2 [ 3 ] = 0.0 ; _rtXdot ->
fdnkcpfqw2 [ 0 ] += rtP . Filtro_A [ 0 ] * rtX . fdnkcpfqw2 [ 0 ] ; _rtXdot
-> fdnkcpfqw2 [ 0 ] += rtP . Filtro_A [ 1 ] * rtX . fdnkcpfqw2 [ 1 ] ;
_rtXdot -> fdnkcpfqw2 [ 0 ] += rtP . Filtro_A [ 2 ] * rtX . fdnkcpfqw2 [ 2 ]
; _rtXdot -> fdnkcpfqw2 [ 1 ] += rtP . Filtro_A [ 3 ] * rtX . fdnkcpfqw2 [ 0
] ; _rtXdot -> fdnkcpfqw2 [ 1 ] += rtP . Filtro_A [ 4 ] * rtX . fdnkcpfqw2 [
3 ] ; _rtXdot -> fdnkcpfqw2 [ 2 ] += rtP . Filtro_A [ 5 ] * rtX . fdnkcpfqw2
[ 0 ] ; _rtXdot -> fdnkcpfqw2 [ 3 ] += rtP . Filtro_A [ 6 ] * rtX .
fdnkcpfqw2 [ 1 ] ; _rtXdot -> fdnkcpfqw2 [ 0 ] += rtP . Filtro_B * rtB .
brw1yh1ujs ; _rtXdot -> mjardhsaxq = rtB . echlwz23fd ; for ( is = 0 ; is < 6
; is ++ ) { _rtXdot -> iz0hdnziyp [ is ] = 0.0 ; for ( ci = ir [ is ] ; ci <
ir [ is + 1 ] ; ci ++ ) { _rtXdot -> iz0hdnziyp [ is ] += rtP .
Filtro_A_almvbenuye [ ci ] * rtX . iz0hdnziyp [ jc [ ci ] ] ; } } for ( is =
0 ; is < 6 ; is ++ ) { ci = ir_p [ is ] ; while ( ci < 1 ) { _rtXdot ->
iz0hdnziyp [ is ] += rtP . Filtro_B_cz4ovtnlbh * rtB . fwzg1qmdog ; ci = 1 ;
} } _rtXdot -> gusjeimfuy = rtB . e15ao1bk3m ; _rtXdot -> ocmfulb5j3 = rtB .
e15ao1bk3m ; _rtXdot -> nk03khymzz = rtB . ma2rvcr4nq ; _rtXdot -> hqbabu1dqz
= rtB . ftsmahysaw ; _rtXdot -> lpsjm2psah = rtB . akirm2mhww ; _rtXdot ->
inqcqvaw3b = rtB . furzsgxei5 ; } void MdlProjection ( void ) { } void
MdlZeroCrossings ( void ) { ZCV * _rtZCSV ; _rtZCSV = ( ( ZCV * )
ssGetSolverZcSignalVector ( rtS ) ) ; _rtZCSV -> dbmhpbljhw = rtB .
iea4dkyy2w ; _rtZCSV -> dayf44tptb = rtB . f5hdbpawyv - rtP .
CompareToConstant_const ; _rtZCSV -> a4ovn5qqow = rtB . jp5azcgtac - rtP .
Switch_Threshold ; _rtZCSV -> ng5fhqdavf = rtB . jp5azcgtac - rtP .
Switch1_Threshold ; _rtZCSV -> bz4a51q4zh = rtB . dxcynwwxat - rtB .
jmi5xid0ph ; _rtZCSV -> bulkgwmmam = rtB . hpuvpoamzd ; _rtZCSV -> fzwpwip1bi
= rtB . hs1qpln3nc ; _rtZCSV -> l4ft3tkoae = rtB . nvde5gnl32 - rtB .
ijufvlmorm ; _rtZCSV -> hxle11zvbw = rtB . mpss00ytce - rtB . pdl3oaaxvv ;
_rtZCSV -> aba0ie0tsy = rtB . iuiswtbqno ; _rtZCSV -> ioresh4hqd = rtB .
h3jkxjjtu0 - rtB . oarcyjxd4w ; _rtZCSV -> kond1vggyv = rtB . oru1g5vkau -
rtB . lwvzpms5bv ; _rtZCSV -> iplt3teglz = rtB . bd1h4kdhj0 - rtB .
kp4mtdwxq5 ; } void MdlTerminate ( void ) { rt_FREE ( rtDW . ap5xq1jhre .
RSimInfoPtr ) ; rt_TDelayFreeBuf ( rtDW . lv2dzfblr1 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . ifklj3sbrn . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . hd1c30tkpp . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . ge2wwzjib2 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . jshlet2ssp . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . pkzvqa1hj0 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . pviiww4mxm . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . dwlf21fnwg . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . bnamprjobf . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . lrrduccxok . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . fhjti1tiah . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . faivwg4izm . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . lw4b5iw0r0 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . nhj2clh5pd . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . d1uhchttm1 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . egilahlbnt . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . lxhyqkdxwz . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . a4exivx0tt . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . idcmakdjdp . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . btwgfjuhwu . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . mfdffnmnea . TUbufferPtrs [ 0 ] ) ; if (
rt_slioCatalogue ( ) != ( NULL ) ) { void * * slioCatalogueAddr =
rt_slioCatalogueAddr ( ) ; rtwSaveDatasetsToMatFile (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ,
rt_GetMatSigstreamLoggingFileName ( ) ) ; rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = NULL ; } } void
MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 20 ) ;
ssSetNumPeriodicContStates ( rtS , 4 ) ; ssSetNumY ( rtS , 0 ) ; ssSetNumU (
rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ; ssSetNumSampleTimes ( rtS ,
5 ) ; ssSetNumBlocks ( rtS , 238 ) ; ssSetNumBlockIO ( rtS , 93 ) ;
ssSetNumBlockParams ( rtS , 341 ) ; } void MdlInitializeSampleTimes ( void )
{ ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetSampleTime ( rtS , 1 , 0.0 ) ;
ssSetSampleTime ( rtS , 2 , 1.0E-9 ) ; ssSetSampleTime ( rtS , 3 , 8.0E-6 ) ;
ssSetSampleTime ( rtS , 4 , - 2.0 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ;
ssSetOffsetTime ( rtS , 1 , 1.0 ) ; ssSetOffsetTime ( rtS , 2 , 0.0 ) ;
ssSetOffsetTime ( rtS , 3 , 0.0 ) ; ssSetOffsetTime ( rtS , 4 , 0.0 ) ; }
void raccel_set_checksum ( ) { ssSetChecksumVal ( rtS , 0 , 2351720087U ) ;
ssSetChecksumVal ( rtS , 1 , 4125363493U ) ; ssSetChecksumVal ( rtS , 2 ,
143698455U ) ; ssSetChecksumVal ( rtS , 3 , 1469152365U ) ; }
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
, & dtInfo ) ; dtInfo . numDataTypes = 17 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
FSK_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS , true )
; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 )
; ssSetModelName ( rtS , "FSK" ) ; ssSetPath ( rtS , "FSK" ) ; ssSetTStart (
rtS , 0.0 ) ; ssSetTFinal ( rtS , 0.001496 ) ; { static RTWLogInfo
rt_DataLoggingInfo ; rt_DataLoggingInfo . loggingInterval = NULL ;
ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; } { { static int_T
rt_LoggedStateWidths [ ] = { 1 , 1 , 1 , 4 , 1 , 6 , 1 , 1 , 1 , 1 , 1 , 1 }
; static int_T rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 } ; static int_T rt_LoggedStateDimensions [ ] = { 1 , 1 ,
1 , 4 , 1 , 6 , 1 , 1 , 1 , 1 , 1 , 1 } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
} ; static BuiltInDTypeId rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE } ; static int_T
rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 } ; static RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs [
] = { ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) } ; static
const char_T * rt_LoggedStateLabels [ ] = { "CSTATE" , "CSTATE" , "CSTATE" ,
"CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" ,
"CSTATE" , "CSTATE" } ; static const char_T * rt_LoggedStateBlockNames [ ] =
{ "FSK/medidor de error/Integrator" ,
 "FSK/receptor\n/Reloj/Continuous-Time\nVCO/Modulo \nIntegrator/Modulo\nIntegrator"
, "FSK/receptor\n/Integrator" , "FSK/Filtro" ,
"FSK/Transmisor/Continuous-Time\nVCO/Modulo \nIntegrator/Modulo\nIntegrator"
, "FSK/receptor\n/Filtro" , "FSK/receptor\n/Reloj/Integrator" ,
"FSK/receptor\n/Reloj/Integrator1" ,
 "FSK/receptor\n/SinPortadora\n/Continuous-Time\nVCO/Modulo \nIntegrator/Modulo\nIntegrator"
, "FSK/receptor\n/SinPortadora\n/Integrator" ,
 "FSK/receptor\n/SinPortadora\n/Continuous-Time\nVCO1/Modulo \nIntegrator/Modulo\nIntegrator"
, "FSK/receptor\n/SinPortadora\n/Integrator1" } ; static const char_T *
rt_LoggedStateNames [ ] = { "" , "" , "" , "" , "" , "" , "" , "" , "" , "" ,
"" , "" } ; static boolean_T rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static RTWLogDataTypeConvert
rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 ,
1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } ,
{ 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 12 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert } ; static void *
rt_LoggedStateSignalPtrs [ 12 ] ; rtliSetLogXSignalPtrs ( ssGetRTWLogInfo (
rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . npfxxayysv ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . nnu2myvywh ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtX . pmpdgrmizb ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtX . fdnkcpfqw2 [ 0 ] ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtX . mjardhsaxq ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) & rtX . iz0hdnziyp [ 0 ] ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) & rtX . gusjeimfuy ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) & rtX . ocmfulb5j3 ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) & rtX . nk03khymzz ;
rt_LoggedStateSignalPtrs [ 9 ] = ( void * ) & rtX . hqbabu1dqz ;
rt_LoggedStateSignalPtrs [ 10 ] = ( void * ) & rtX . lpsjm2psah ;
rt_LoggedStateSignalPtrs [ 11 ] = ( void * ) & rtX . inqcqvaw3b ; }
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
void * ) rtPeriodicIndX , 0 , 4 * sizeof ( int_T ) ) ;
ssSetPeriodicContStateRanges ( rtS , rtPeriodicRngX ) ; ( void ) memset ( (
void * ) rtPeriodicRngX , 0 , 8 * sizeof ( real_T ) ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 20 ] ;
static real_T absTol [ 20 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 } ; static
uint8_T absTolControl [ 20 ] = { 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U ,
0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U } ; static real_T
contStateJacPerturbBoundMinVec [ 20 ] ; static real_T
contStateJacPerturbBoundMaxVec [ 20 ] ; static uint8_T zcAttributes [ 23 ] =
{ ( ZC_EVENT_ALL ) , ( 0xc0 | ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
0xc0 | ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( 0xc0 |
ZC_EVENT_ALL_DN ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) ,
( ZC_EVENT_ALL ) , ( 0x80 | ZC_EVENT_ALL ) , ( 0xc0 | ZC_EVENT_ALL_UP ) , (
0xc0 | ZC_EVENT_ALL ) , ( 0xc0 | ZC_EVENT_ALL ) , ( 0xc0 | ZC_EVENT_ALL_DN )
, ( 0xc0 | ZC_EVENT_ALL_UP ) , ( 0xc0 | ZC_EVENT_ALL_UP ) , ( 0xc0 |
ZC_EVENT_ALL_UP ) } ; static ssNonContDerivSigInfo nonContDerivSigInfo [ 6 ]
= { { 1 * sizeof ( real_T ) , ( char * ) ( & rtB . kkn0pryfbs ) , ( NULL ) }
, { 1 * sizeof ( real_T ) , ( char * ) ( & rtB . e15ao1bk3m ) , ( NULL ) } ,
{ 1 * sizeof ( real_T ) , ( char * ) ( & rtB . fcjlyowfli ) , ( NULL ) } , {
1 * sizeof ( real_T ) , ( char * ) ( & rtB . iyoofertyx ) , ( NULL ) } , { 1
* sizeof ( real_T ) , ( char * ) ( & rtB . ghegbffnb0 ) , ( NULL ) } , { 1 *
sizeof ( real_T ) , ( char * ) ( & rtB . jmfd3dtamo ) , ( NULL ) } } ; { int
i ; for ( i = 0 ; i < 20 ; ++ i ) { contStateJacPerturbBoundMinVec [ i ] = 0
; contStateJacPerturbBoundMaxVec [ i ] = rtGetInf ( ) ; } } ssSetSolverRelTol
( rtS , 0.001 ) ; ssSetStepSize ( rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0
) ; ssSetMaxNumMinSteps ( rtS , - 1 ) ; ssSetMinStepViolatedError ( rtS , 0 )
; ssSetMaxStepSize ( rtS , 1.0E-9 ) ; ssSetSolverMaxOrder ( rtS , - 1 ) ;
ssSetSolverRefineFactor ( rtS , 1 ) ; ssSetOutputTimes ( rtS , ( NULL ) ) ;
ssSetNumOutputTimes ( rtS , 0 ) ; ssSetOutputTimesOnly ( rtS , 0 ) ;
ssSetOutputTimesIndex ( rtS , 0 ) ; ssSetZCCacheNeedsReset ( rtS , 1 ) ;
ssSetDerivCacheNeedsReset ( rtS , 0 ) ; ssSetNumNonContDerivSigInfos ( rtS ,
6 ) ; ssSetNonContDerivSigInfos ( rtS , nonContDerivSigInfo ) ;
ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS , "ode45" ) ;
ssSetVariableStepSolver ( rtS , 1 ) ; ssSetSolverConsistencyChecking ( rtS ,
0 ) ; ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ;
ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetAbsTolVector ( rtS , absTol )
; ssSetAbsTolControlVector ( rtS , absTolControl ) ;
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
MdlDerivatives ) ; ssSetSolverZcSignalAttrib ( rtS , zcAttributes ) ;
ssSetSolverNumZcSignals ( rtS , 23 ) ; ssSetModelZeroCrossings ( rtS ,
MdlZeroCrossings ) ; ssSetSolverConsecutiveZCsStepRelTol ( rtS ,
2.8421709430404007E-13 ) ; ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ;
ssSetSolverConsecutiveZCsError ( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic (
rtS , 1 ) ; ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ;
ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 13 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; } {
ZCSigState * zc = ( ZCSigState * ) & rtPrevZCX ; ssSetPrevZCSigState ( rtS ,
zc ) ; } { rtPrevZCX . emmu1baj1n = UNINITIALIZED_ZCSIG ; rtPrevZCX .
gcwp0symhu = UNINITIALIZED_ZCSIG ; rtPrevZCX . ck5u1lzcvp =
UNINITIALIZED_ZCSIG ; rtPrevZCX . itvz2yalg2 = UNINITIALIZED_ZCSIG ;
rtPrevZCX . osoivfua0c = ZERO_ZCSIG ; rtPrevZCX . jcttspjmiw =
UNINITIALIZED_ZCSIG ; rtPrevZCX . fwipwlsvaq = UNINITIALIZED_ZCSIG ;
rtPrevZCX . aqaejmbsqc = UNINITIALIZED_ZCSIG ; rtPrevZCX . cc2aoo0nhc .
htztm3ejkl = POS_ZCSIG ; rtPrevZCX . dzgncmrria . htztm3ejkl = POS_ZCSIG ;
rtPrevZCX . jgvwez5knrn . htztm3ejkl = POS_ZCSIG ; } ssSetChecksumVal ( rtS ,
0 , 2351720087U ) ; ssSetChecksumVal ( rtS , 1 , 4125363493U ) ;
ssSetChecksumVal ( rtS , 2 , 143698455U ) ; ssSetChecksumVal ( rtS , 3 ,
1469152365U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 15 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = ( sysRanDType * ) &
rtDW . lomcfztmre ; systemRan [ 2 ] = ( sysRanDType * ) & rtDW . jgvwez5knrn
. b4uftfd3jt ; systemRan [ 3 ] = ( sysRanDType * ) & rtDW . fqkin25shtk .
mnrpt53zog ; systemRan [ 4 ] = ( sysRanDType * ) & rtDW . edzbs02xos1 .
bl2ajkrwzq ; systemRan [ 5 ] = ( sysRanDType * ) & rtDW . dzgncmrria .
b4uftfd3jt ; systemRan [ 6 ] = ( sysRanDType * ) & rtDW . awkevlz2ww .
mnrpt53zog ; systemRan [ 7 ] = ( sysRanDType * ) & rtDW . cfrh4agkgq .
bl2ajkrwzq ; systemRan [ 8 ] = ( sysRanDType * ) & rtDW . nwsijekr51 ;
systemRan [ 9 ] = ( sysRanDType * ) & rtDW . juqugykvvp ; systemRan [ 10 ] =
( sysRanDType * ) & rtDW . jsih34lehs ; systemRan [ 11 ] = ( sysRanDType * )
& rtDW . cc2aoo0nhc . b4uftfd3jt ; systemRan [ 12 ] = ( sysRanDType * ) &
rtDW . b5dbwkwsrj . mnrpt53zog ; systemRan [ 13 ] = ( sysRanDType * ) & rtDW
. cvrfqtrsgv . bl2ajkrwzq ; systemRan [ 14 ] = ( sysRanDType * ) & rtDW .
og5vligtf5 ; rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) , &
ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo (
rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS )
, ssGetTPtr ( rtS ) ) ; } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 5 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID5 ( tid ) ; }
