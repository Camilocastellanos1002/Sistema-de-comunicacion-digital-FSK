#include "rt_logging_mmi.h"
#include "Multuplexacion_FDM_capi.h"
#include <math.h>
#include "Multuplexacion_FDM.h"
#include "Multuplexacion_FDM_private.h"
#include "Multuplexacion_FDM_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; extern boolean_T
gblExtModeStartPktReceived ; void raccelForceExtModeShutdown ( ) { if ( !
gblExtModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 5 , & stopRequested ) ; }
rtExtModeShutdown ( 5 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 2 ;
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
"slprj\\raccel\\Multuplexacion_FDM\\Multuplexacion_FDM_Jpattern.mat" ; const
int_T gblNumRootInportBlks = 0 ; const int_T gblNumModelInputs = 0 ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
extern void * gblAperiodicPartitionHitTimes ; const int_T
gblInportDataTypeIdx [ ] = { - 1 } ; const int_T gblInportDims [ ] = { - 1 }
; const int_T gblInportComplex [ ] = { - 1 } ; const int_T
gblInportInterpoFlag [ ] = { - 1 } ; const int_T gblInportContinuous [ ] = {
- 1 } ; int_T enableFcnCallFlag [ ] = { 1 , 1 , 1 , 1 , 1 , 1 } ; const char
* raccelLoadInputsAndAperiodicHitTimes ( const char * inportFileName , int *
matFileFormat ) { return rt_RapidReadInportsMatFile ( inportFileName ,
matFileFormat , 1 ) ; }
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
void rt_TDelayFreeBuf ( void * buf ) { utFree ( buf ) ; } void e0icchg21v (
mtjjwddujs * localB , b2hegj220n * localP ) { localB -> hml4vbrazh = localP
-> Out1_Y0 ; } void mivhx1fvuu ( SimStruct * rtS_e , boolean_T crtwcnm5c4 ,
real_T anmx2ilkvf , mtjjwddujs * localB , bpumykcckk * localDW , hixkhuf4px *
localZCE ) { if ( ssIsMajorTimeStep ( rtS_e ) ) { if ( crtwcnm5c4 && (
localZCE -> aw5lle212o != POS_ZCSIG ) ) { localB -> hml4vbrazh = anmx2ilkvf ;
localDW -> fmzbbk3ukv = 4 ; } localZCE -> aw5lle212o = crtwcnm5c4 ; } } void
pjvzgcabzc ( fikkek4bti * localB , knxgvh15og * localP ) { localB ->
hmpzhh3n3o = localP -> OUT_Y0 ; } void dnioykk3w1 ( SimStruct * rtS_m ,
real_T eg4ley0b2m , boolean_T bjlu3mfbh2 , boolean_T oeuo3vtrpy , fikkek4bti
* localB , f3nkengjqz * localDW ) { if ( eg4ley0b2m > 0.0 ) { localB ->
hmpzhh3n3o = ( ( int32_T ) oeuo3vtrpy > ( int32_T ) bjlu3mfbh2 ) ; if (
ssIsMajorTimeStep ( rtS_m ) ) { srUpdateBC ( localDW -> k2unbokluf ) ; } } }
void fjikzgt1f0 ( atopmxixl1 * localB , pgxloeq2x1 * localP ) { localB ->
ltgb5gkcbo = localP -> OUT_Y0 ; } void d5zlt11l1p ( SimStruct * rtS_e ,
real_T eniebo42kv , boolean_T nflxpebid4 , boolean_T jyuyvgcqvk , atopmxixl1
* localB , p0p5r3rifc * localDW ) { if ( eniebo42kv > 0.0 ) { localB ->
ltgb5gkcbo = ( ( int32_T ) jyuyvgcqvk < ( int32_T ) nflxpebid4 ) ; if (
ssIsMajorTimeStep ( rtS_e ) ) { srUpdateBC ( localDW -> faxymqm3qy ) ; } } }
real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { uint32_T lo ; uint32_T
hi ; lo = * u % 127773U * 16807U ; hi = * u / 127773U * 2836U ; if ( lo < hi
) { * u = 2147483647U - ( hi - lo ) ; } else { * u = lo - hi ; } return (
real_T ) * u * 4.6566128752457969E-10 ; } real_T rt_nrand_Upu32_Yd_f_pw_snf (
uint32_T * u ) { real_T y ; real_T sr ; real_T si ; do { sr = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = sr * sr + si * si ; } while (
si > 1.0 ) ; y = muDoubleScalarSqrt ( - 2.0 * muDoubleScalarLog ( si ) / si )
* sr ; return y ; } void MdlInitialize ( void ) { int_T is ; uint32_T tseed ;
int32_T t ; real_T tmp ; rtX . cgdhzp3x0l = rtP . Integrator_IC ; rtX .
imuz3fx4o3 = rtP . ModuloIntegrator_IC ; rtX . cfrslgfjyu = rtP .
Integrator_IC_moexjyifg4 ; for ( is = 0 ; is < 10 ; is ++ ) { rtX .
ccwzf3tws3 [ is ] = rtP . AnalogFilterDesign2_InitialCondition ; rtX .
ids2w4qbzk [ is ] = rtP . AnalogFilterDesign_InitialCondition ; } rtX .
nc3vmkovco = rtP . ModuloIntegrator_IC_esfyns1sy5 ; rtX . psx2ki4ws3 = rtP .
ModuloIntegrator_IC_i5n3se5kvp ; tmp = muDoubleScalarFloor ( rtP .
GaussianNoiseGenerator_s ) ; if ( muDoubleScalarIsNaN ( tmp ) ||
muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; } else { tmp = muDoubleScalarRem
( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0 ? ( uint32_T ) - ( int32_T ) (
uint32_T ) - tmp : ( uint32_T ) tmp ; is = ( int32_T ) ( tseed >> 16U ) ; t =
( int32_T ) ( tseed & 32768U ) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) is <<
16U ) ) + t ) << 16U ) + t ) + is ; if ( tseed < 1U ) { tseed = 1144108930U ;
} else { if ( tseed > 2147483646U ) { tseed = 2147483646U ; } } rtDW .
imgdcg24fm = tseed ; rtDW . ou0ychata3 = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW
. imgdcg24fm ) * rtP . RandomNumber_StdDev + rtP . RandomNumber_Mean ; rtDW .
oz50sdopcp = rtP . Memory_InitialCondition ; rtDW . by0zcdyxc4 = rtP .
Monostable1_ic ; rtDW . bwkxnxzhy1 = rtP . SampleandHold_ic ; tmp =
muDoubleScalarFloor ( rtP . GaussianNoiseGenerator_s_natqquq25k ) ; if (
muDoubleScalarIsNaN ( tmp ) || muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; }
else { tmp = muDoubleScalarRem ( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0
? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp : ( uint32_T ) tmp ; is = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) is << 16U ) ) + t ) << 16U ) + t ) + is ; if (
tseed < 1U ) { tseed = 1144108930U ; } else { if ( tseed > 2147483646U ) {
tseed = 2147483646U ; } } rtDW . kzibzv5iwi = tseed ; rtDW . kikmlfmksm =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kzibzv5iwi ) * rtP .
RandomNumber_StdDev_iveng2gmn4 + rtP . RandomNumber_Mean_pbcszkatmd ; for (
is = 0 ; is < 6 ; is ++ ) { rtX . hrccq1fi0z [ is ] = rtP .
Filtro_InitialCondition ; } rtX . gxe5sdikfw = rtP . Integrator_IC_ptowdeldtu
; rtDW . kmeshewsao = rtP . Memory_InitialCondition_jlkxne1qro ; rtDW .
cbjfpdjiyu = rtP . Monostable_ic ; rtDW . livmyfqsgc = rtP .
SampleandHold_ic_j2rdwmu3tc ; rtDW . alglspiynp = rtP .
Memory_InitialCondition_cdrhhgyi4a ; rtDW . koquxjpxpa = rtP .
Monostable1_ic_biaz4juxj0 ; rtDW . nfditlbohk = rtP .
SampleandHold_ic_iltoiaeoee ; rtX . cc5042ocv2 = rtP . Integrator1_IC ; rtX .
husvwrmjnn = rtP . ModuloIntegrator_IC_nahsh2vkhw ; rtX . g01iry0rqn = rtP .
Integrator_IC_nfolmlihr0 ; rtX . iquu4mgvfb = rtP .
ModuloIntegrator_IC_cw2uxsyp5l ; rtX . lnhetubiv2 = rtP .
Integrator1_IC_dcpkt2betd ; rtB . e1nhqxjvjn = rtP . _Y0_ld4ghr3opr ; rtB .
lufwcivalw = rtP . _Y0 ; fjikzgt1f0 ( & rtB . abmuy5rnsq , & rtP . abmuy5rnsq
) ; pjvzgcabzc ( & rtB . mpycb0evfp , & rtP . mpycb0evfp ) ; fjikzgt1f0 ( &
rtB . d5zlt11l1pl , & rtP . d5zlt11l1pl ) ; pjvzgcabzc ( & rtB . dnioykk3w1k
, & rtP . dnioykk3w1k ) ; rtB . munnuokh3b = rtP . _Y0_matapuynvo ;
fjikzgt1f0 ( & rtB . gggqmave4q , & rtP . gggqmave4q ) ; pjvzgcabzc ( & rtB .
fkhi333c1w , & rtP . fkhi333c1w ) ; rtB . dduxw540hu = rtP . _Y0_ghe40wtwbh ;
e0icchg21v ( & rtB . mivhx1fvuuy , & rtP . mivhx1fvuuy ) ; e0icchg21v ( & rtB
. dyorcglstw , & rtP . dyorcglstw ) ; e0icchg21v ( & rtB . jiixgvrfhd , & rtP
. jiixgvrfhd ) ; { int_T rootPeriodicContStateIndices [ 5 ] = { 11 , 23 , 24
, 33 , 35 } ; real_T rootPeriodicContStateRanges [ 10 ] = { 0.0 , 1.0 , 0.0 ,
1.0 , 0.0 , 1.0 , 0.0 , 1.0 , 0.0 , 1.0 } ; ( void ) memcpy ( ( void * )
rtPeriodicIndX , rootPeriodicContStateIndices , 5 * sizeof ( int_T ) ) ; (
void ) memcpy ( ( void * ) rtPeriodicRngX , rootPeriodicContStateRanges , 10
* sizeof ( real_T ) ) ; } } void MdlEnable ( void ) { rtDW . nnzogj4mrn = 1 ;
_ssSetSampleHit ( rtS , 4 , 1 ) ; _ssSetTaskTime ( rtS , 4 , ssGetT ( rtS ) )
; _ssSetVarNextHitTime ( rtS , 0 , ssGetT ( rtS ) ) ; ; } void MdlStart (
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
externalInputIsInDatasetFormat ) { } } { int_T dimensions [ 1 ] = { 1 } ;
rtDW . lp4l4cdghx . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "mensajerx" , SS_BOOLEAN , 0 , 0 , 0 , 1 , 1 , dimensions ,
NO_LOGVALDIMS , ( NULL ) , ( NULL ) , 0 , 1 , - 1.0 , 1 ) ; if ( rtDW .
lp4l4cdghx . LoggedData == ( NULL ) ) return ; } { FWksInfo * fromwksInfo ;
if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1 , sizeof ( FWksInfo ) ) ) == (
NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "mensaje " ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) rtP . Informacion2_Data0 ; fromwksInfo -> nDataPoints =
182 ; fromwksInfo -> time = ( NULL ) ; rtDW . d0yoqq0s2u . TimePtr =
fromwksInfo -> time ; rtDW . d0yoqq0s2u . DataPtr = fromwksInfo -> data ;
rtDW . d0yoqq0s2u . RSimInfoPtr = fromwksInfo ; } rtDW . fxbkkikmgg .
PrevIndex = - 1 ; } { FWksInfo * fromwksInfo ; if ( ( fromwksInfo = (
FWksInfo * ) calloc ( 1 , sizeof ( FWksInfo ) ) ) == ( NULL ) ) {
ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "mensaje " ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) rtP . informacion1_Data0 ; fromwksInfo -> nDataPoints =
182 ; fromwksInfo -> time = ( NULL ) ; rtDW . gtget4fvsy . TimePtr =
fromwksInfo -> time ; rtDW . gtget4fvsy . DataPtr = fromwksInfo -> data ;
rtDW . gtget4fvsy . RSimInfoPtr = fromwksInfo ; } rtDW . j4hthgivby .
PrevIndex = - 1 ; } { { real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf (
2 , 1024 , sizeof ( real_T ) ) ; if ( pBuffer == ( NULL ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } rtDW
. actgbahxga . Tail = 0 ; rtDW . actgbahxga . Head = 0 ; rtDW . actgbahxga .
Last = 0 ; rtDW . actgbahxga . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
j0ojopv3o4 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
j0ojopv3o4 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . cc05czrsze . Tail = 0
; rtDW . cc05czrsze . Head = 0 ; rtDW . cc05czrsze . Last = 0 ; rtDW .
cc05czrsze . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_a54zvzwmak ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . odiqda1u1t . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
odiqda1u1t . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . ikxgblv1zv . Tail = 0
; rtDW . ikxgblv1zv . Head = 0 ; rtDW . ikxgblv1zv . Last = 0 ; rtDW .
ikxgblv1zv . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_nb5s3gjuh0 ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . mx1qnjpwkr . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
mx1qnjpwkr . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . c0ewitmagq . Tail = 0
; rtDW . c0ewitmagq . Head = 0 ; rtDW . c0ewitmagq . Last = 0 ; rtDW .
c0ewitmagq . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_bfobvi0kzf ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . c1abig5l5b . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
c1abig5l5b . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . mw4jmqmb5m . Tail = 0
; rtDW . mw4jmqmb5m . Head = 0 ; rtDW . mw4jmqmb5m . Last = 0 ; rtDW .
mw4jmqmb5m . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_pz2dgrhemk ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . l3olmqutvm . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
l3olmqutvm . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . mbpoqz0vfq . Tail = 0
; rtDW . mbpoqz0vfq . Head = 0 ; rtDW . mbpoqz0vfq . Last = 0 ; rtDW .
mbpoqz0vfq . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay1_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
laigziygdt . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
laigziygdt . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . jqyvcdfdil . Tail = 0
; rtDW . jqyvcdfdil . Head = 0 ; rtDW . jqyvcdfdil . Last = 0 ; rtDW .
jqyvcdfdil . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay12_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
duyhxp3i2o . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
duyhxp3i2o . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . b5jqmouq00 . Tail = 0
; rtDW . b5jqmouq00 . Head = 0 ; rtDW . b5jqmouq00 . Last = 0 ; rtDW .
b5jqmouq00 . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay2_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
pfzlxqtttd . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
pfzlxqtttd . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . dsos1nl3ug . Tail = 0
; rtDW . dsos1nl3ug . Head = 0 ; rtDW . dsos1nl3ug . Last = 0 ; rtDW .
dsos1nl3ug . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay1_InitOutput_km2up0labu ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . kpyzd0zppl . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
kpyzd0zppl . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . miosm0kvi1 . Tail = 0
; rtDW . miosm0kvi1 . Head = 0 ; rtDW . miosm0kvi1 . Last = 0 ; rtDW .
miosm0kvi1 . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay4_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
anw4lh3mkt . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
anw4lh3mkt . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . daastispqd . Tail = 0
; rtDW . daastispqd . Head = 0 ; rtDW . daastispqd . Last = 0 ; rtDW .
daastispqd . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay3_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
hth3y5boa4 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
hth3y5boa4 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . ga03tvlrh0 . Tail = 0
; rtDW . ga03tvlrh0 . Head = 0 ; rtDW . ga03tvlrh0 . Last = 0 ; rtDW .
ga03tvlrh0 . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay6_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
jkfvz1vsm1 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
jkfvz1vsm1 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . d2cdydaqvh . Tail = 0
; rtDW . d2cdydaqvh . Head = 0 ; rtDW . d2cdydaqvh . Last = 0 ; rtDW .
d2cdydaqvh . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay5_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
axitmt5w4i . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
axitmt5w4i . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . lo3fy120pk . Tail = 0
; rtDW . lo3fy120pk . Head = 0 ; rtDW . lo3fy120pk . Last = 0 ; rtDW .
lo3fy120pk . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay8_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
bz4cstgndq . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
bz4cstgndq . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . i5j0s3drdy . Tail = 0
; rtDW . i5j0s3drdy . Head = 0 ; rtDW . i5j0s3drdy . Last = 0 ; rtDW .
i5j0s3drdy . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay7_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
ifxwkbjtsf . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
ifxwkbjtsf . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . naehoe5c24 . Tail = 0
; rtDW . naehoe5c24 . Head = 0 ; rtDW . naehoe5c24 . Last = 0 ; rtDW .
naehoe5c24 . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay9_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
oydq1getqe . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
oydq1getqe . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . atsr3zriuy . Tail = 0
; rtDW . atsr3zriuy . Head = 0 ; rtDW . atsr3zriuy . Last = 0 ; rtDW .
atsr3zriuy . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay11_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
nzhehebsh0 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
nzhehebsh0 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . ogdeiw34cz . Tail = 0
; rtDW . ogdeiw34cz . Head = 0 ; rtDW . ogdeiw34cz . Last = 0 ; rtDW .
ogdeiw34cz . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay10_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
erisf50gfz . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
erisf50gfz . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . nan1e3l5p0 . Tail = 0
; rtDW . nan1e3l5p0 . Head = 0 ; rtDW . nan1e3l5p0 . Last = 0 ; rtDW .
nan1e3l5p0 . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay13_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
jszhk4b0c2 . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
jszhk4b0c2 . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . oivjundpbe . Tail = 0
; rtDW . oivjundpbe . Head = 0 ; rtDW . oivjundpbe . Last = 0 ; rtDW .
oivjundpbe . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay1_InitOutput_cz0jjsby1m ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . emliqyd1hi . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
emliqyd1hi . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } } { {
real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . os1vqq3jgt . Tail = 0
; rtDW . os1vqq3jgt . Head = 0 ; rtDW . os1vqq3jgt . Last = 0 ; rtDW .
os1vqq3jgt . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput_nwut2o4lpm ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . j0z4zsdtwg . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; rtDW .
j0z4zsdtwg . TUbufferPtrs [ 1 ] = ( void * ) & pBuffer [ 1024 ] ; } }
MdlInitialize ( ) ; MdlEnable ( ) ; } void MdlOutputs ( int_T tid ) { real_T
fsify3ne4r ; real_T lvfklq2cvb ; real_T paeaglgzht ; boolean_T h4ky5h1grf ;
boolean_T heolw2ozxt ; boolean_T e540n3jc21 ; boolean_T jfm1h1sfgj ;
boolean_T awcqntc1jt ; boolean_T mfqlwvbvy4 ; ZCEventType zcEvent ; boolean_T
avljzyfwyu ; boolean_T iyu3pyojoi ; boolean_T auvdmsssjz ; real_T taskTimeV ;
uint32_T numCycles ; real_T ratio ; srClearBC ( rtDW . hbnvwgns2u ) ;
srClearBC ( rtDW . mivhx1fvuuy . fmzbbk3ukv ) ; srClearBC ( rtDW .
dnioykk3w1k . k2unbokluf ) ; srClearBC ( rtDW . d5zlt11l1pl . faxymqm3qy ) ;
srClearBC ( rtDW . loneq0nrmu ) ; srClearBC ( rtDW . moelhnb1d2 ) ; srClearBC
( rtDW . cjvs3g4hfh ) ; srClearBC ( rtDW . lekdfle5yl ) ; rtB . gzkvmusrdv =
0.0 ; rtB . gzkvmusrdv += rtP . AnalogFilterDesign2_C * rtX . ccwzf3tws3 [ 4
] ; if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { { int_T currIndex = rtDW .
fxbkkikmgg . PrevIndex + 1 ; real_T * pDataValues = ( real_T * ) rtDW .
d0yoqq0s2u . DataPtr ; int numPoints , lastPoint ; FWksInfo * fromwksInfo = (
FWksInfo * ) rtDW . d0yoqq0s2u . RSimInfoPtr ; numPoints = fromwksInfo ->
nDataPoints ; lastPoint = numPoints - 1 ; if ( currIndex < numPoints ) {
pDataValues += currIndex ; rtB . l2slq2pxao = * pDataValues ; } else { rtB .
l2slq2pxao = 0.0 ; } rtDW . fxbkkikmgg . PrevIndex = currIndex ; } } rtB .
hqvlr0c1t3 = rtX . cgdhzp3x0l ; rtB . l3viz5m5kx = rtB . hqvlr0c1t3 * rtP .
Rb ; rtB . ifswdaywbt = rtX . imuz3fx4o3 ; rtB . ph3uie01yv =
muDoubleScalarCos ( rtB . ifswdaywbt * 6.2831853071795862 ) ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB . ph3uie01yv > 0.0 ) { rtDW .
nfgd4hmkks = 1 ; } else if ( rtB . ph3uie01yv < 0.0 ) { rtDW . nfgd4hmkks = -
1 ; } else { rtDW . nfgd4hmkks = 0 ; } if ( rtDW . nfgd4hmkks >= rtP .
Switch2_Threshold ) { rtB . cwrlg5uwpe = rtP . Constant5_Value ; } else { rtB
. cwrlg5uwpe = rtP . Constant6_Value ; } } if ( ssIsMajorTimeStep ( rtS ) ) {
zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & rtPrevZCX . mqbxqqegfa , ( rtB .
cwrlg5uwpe ) ) ; if ( zcEvent != NO_ZCEVENT ) { rtX . cfrslgfjyu = rtP .
Integrator_IC_moexjyifg4 ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; } } rtB . m1xi1b0n5m = rtX . cfrslgfjyu ; if ( ssIsSampleHit ( rtS , 3 , 0
) ) { { int_T currIndex = rtDW . j4hthgivby . PrevIndex + 1 ; real_T *
pDataValues = ( real_T * ) rtDW . gtget4fvsy . DataPtr ; int numPoints ,
lastPoint ; FWksInfo * fromwksInfo = ( FWksInfo * ) rtDW . gtget4fvsy .
RSimInfoPtr ; numPoints = fromwksInfo -> nDataPoints ; lastPoint = numPoints
- 1 ; if ( currIndex < numPoints ) { pDataValues += currIndex ; rtB .
omyffgmxzc = * pDataValues ; } else { rtB . omyffgmxzc = 0.0 ; } rtDW .
j4hthgivby . PrevIndex = currIndex ; } } rtB . otfd1hdnf4 = 0.0 ; rtB .
otfd1hdnf4 += rtP . AnalogFilterDesign_C * rtX . ids2w4qbzk [ 4 ] ; rtB .
dwygygnfyu = rtX . nc3vmkovco ; rtB . kvdiwfhjmc = ( muDoubleScalarSin (
6.2831853071795862 * rtP . frecport1 * ssGetTaskTime ( rtS , 0 ) + rtP .
SineWave_Phase ) * rtP . SineWave_Amp + rtP . SineWave_Bias ) * rtB .
omyffgmxzc ; { real_T * * uBuffer = ( real_T * * ) & rtDW . j0ojopv3o4 .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW . j0ojopv3o4
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; real_T tMinusDelay =
simTime - rtP . TransportDelay_Delay ; if ( rtP . TransportDelay_Delay == 0.0
) rtB . oddjfmdyew = rtB . kvdiwfhjmc ; else rtB . oddjfmdyew =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
actgbahxga . CircularBufSize , & rtDW . actgbahxga . Last , rtDW . actgbahxga
. Tail , rtDW . actgbahxga . Head , rtP . TransportDelay_InitOutput , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) ==
ssGetT ( rtS ) ) ) ) ; } rtB . ftbsaajysf = rtP . Rb / 2.0 * rtB . oddjfmdyew
; rtB . i3olz0n0gi = rtB . ftbsaajysf + rtP . Frec2 ; rtB . d4sffuf0wj = rtX
. psx2ki4ws3 ; if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . ckmrjxysf3 = (
2.15E+6 - 0.25 * rtP . Rb ) * 6.2831853071795862 + rtP . Rb / 2.0 * rtB .
l2slq2pxao ; } rtB . jaf1or2u2g = muDoubleScalarCos ( rtB . dwygygnfyu *
6.2831853071795862 ) + muDoubleScalarCos ( rtB . d4sffuf0wj *
6.2831853071795862 ) ; { real_T * * uBuffer = ( real_T * * ) & rtDW .
odiqda1u1t . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. odiqda1u1t . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; real_T
tMinusDelay = simTime - rtP . Retraso_canal ; rtB . lisu5vhdeu =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
cc05czrsze . CircularBufSize , & rtDW . cc05czrsze . Last , rtDW . cc05czrsze
. Tail , rtDW . cc05czrsze . Head , rtP .
TransportDelay_InitOutput_a54zvzwmak , 0 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } if (
ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB . czpmrjwdbw = rtP .
GaussianNoiseGenerator_d * rtDW . ou0ychata3 + rtP . GaussianNoiseGenerator_m
; rtB . eqpfzakwij = rtB . czpmrjwdbw ; } rtB . cuyzwij0cy = rtB . lisu5vhdeu
+ rtB . eqpfzakwij ; rtB . dc0ixgrh4v = 1.0 / rtP . Atenuacion_canal * rtB .
jaf1or2u2g ; { real_T * * uBuffer = ( real_T * * ) & rtDW . mx1qnjpwkr .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW . mx1qnjpwkr
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; real_T tMinusDelay =
simTime - rtP . TransportDelay_Delay_dget2i1x1r ; fsify3ne4r =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
ikxgblv1zv . CircularBufSize , & rtDW . ikxgblv1zv . Last , rtDW . ikxgblv1zv
. Tail , rtDW . ikxgblv1zv . Head , rtP .
TransportDelay_InitOutput_nb5s3gjuh0 , 1 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
ita0atad5a = ( rtB . m1xi1b0n5m >= rtP . CompareToConstant_const ) ; }
avljzyfwyu = rtDW . ita0atad5a ; } { real_T * * uBuffer = ( real_T * * ) &
rtDW . c1abig5l5b . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * )
& rtDW . c1abig5l5b . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ;
real_T tMinusDelay = simTime - ( ( 0.95 / rtP . Rb ) ) ; rtB . bonunno3da =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
c0ewitmagq . CircularBufSize , & rtDW . c0ewitmagq . Last , rtDW . c0ewitmagq
. Tail , rtDW . c0ewitmagq . Head , rtP .
TransportDelay_InitOutput_bfobvi0kzf , 1 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsMajorTimeStep ( rtS ) ) { zcEvent =
rt_ZCFcn ( ANY_ZERO_CROSSING , & rtPrevZCX . otkgxfzkeh , ( rtB . bonunno3da
) ) ; if ( zcEvent != NO_ZCEVENT ) { rtB . e1nhqxjvjn = avljzyfwyu ; rtDW .
cjvs3g4hfh = 4 ; } } rtB . p5sg0ao2sd = ( int8_T ) ( ( int8_T ) ( fsify3ne4r
!= 0.0 ) ^ ( int8_T ) rtB . e1nhqxjvjn ) ; if ( ssIsSampleHit ( rtS , 4 , 0 )
) { taskTimeV = ssGetTaskTime ( rtS , 4 ) ; if ( ssGetTNextWasAdjusted ( rtS
, 4 ) ) { rtDW . dbk2xqyp1n = _ssGetVarNextHitTime ( rtS , 0 ) ; } if ( rtDW
. nnzogj4mrn != 0 ) { rtDW . nnzogj4mrn = 0 ; if ( taskTimeV >= rtP .
PulseGenerator_PhaseDelay ) { ratio = ( taskTimeV - rtP .
PulseGenerator_PhaseDelay ) / ( 1.0 / rtP . Rb ) ; numCycles = ( uint32_T )
muDoubleScalarFloor ( ratio ) ; if ( muDoubleScalarAbs ( ( real_T ) (
numCycles + 1U ) - ratio ) < DBL_EPSILON * ratio ) { numCycles ++ ; } rtDW .
kklmtkqxdm = numCycles ; ratio = ( 1.0 / rtP . Rb * ( real_T ) numCycles +
rtP . PulseGenerator_PhaseDelay ) + 1.0 / rtP . Rb * rtP .
PulseGenerator_Duty / 100.0 ; if ( taskTimeV < ratio ) { rtDW . dvmb0i40bs =
1 ; rtDW . dbk2xqyp1n = ratio ; } else { rtDW . dvmb0i40bs = 0 ; rtDW .
dbk2xqyp1n = ( real_T ) ( numCycles + 1U ) * ( 1.0 / rtP . Rb ) + rtP .
PulseGenerator_PhaseDelay ; } } else { rtDW . kklmtkqxdm = rtP .
PulseGenerator_PhaseDelay != 0.0 ? - 1 : 0 ; rtDW . dvmb0i40bs = 0 ; rtDW .
dbk2xqyp1n = rtP . PulseGenerator_PhaseDelay ; } } else { if ( rtDW .
dbk2xqyp1n <= taskTimeV ) { if ( rtDW . dvmb0i40bs == 1 ) { rtDW . dvmb0i40bs
= 0 ; rtDW . dbk2xqyp1n = ( real_T ) ( rtDW . kklmtkqxdm + 1LL ) * ( 1.0 /
rtP . Rb ) + rtP . PulseGenerator_PhaseDelay ; } else { rtDW . kklmtkqxdm ++
; rtDW . dvmb0i40bs = 1 ; rtDW . dbk2xqyp1n = ( 1.0 / rtP . Rb * rtP .
PulseGenerator_Duty * 0.01 + 1.0 / rtP . Rb * ( real_T ) rtDW . kklmtkqxdm )
+ rtP . PulseGenerator_PhaseDelay ; } } } _ssSetVarNextHitTime ( rtS , 0 ,
rtDW . dbk2xqyp1n ) ; if ( rtDW . dvmb0i40bs == 1 ) { rtB . hnghqt15hm = rtP
. PulseGenerator_Amp ; } else { rtB . hnghqt15hm = 0.0 ; } } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsMajorTimeStep ( rtS ) ) { zcEvent =
rt_ZCFcn ( RISING_ZERO_CROSSING , & rtPrevZCX . p1xn3fs3d3 , ( rtB .
hnghqt15hm ) ) ; if ( zcEvent != NO_ZCEVENT ) { rtB . lufwcivalw = rtB .
p5sg0ao2sd ; rtDW . hbnvwgns2u = 4 ; } } { real_T * * uBuffer = ( real_T * *
) & rtDW . l3olmqutvm . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & rtDW . l3olmqutvm . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS
) ; real_T tMinusDelay = simTime - ( 0.25 / rtP . Frec1 ) ; rtB . pbihxnhzkv
= rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
mw4jmqmb5m . CircularBufSize , & rtDW . mw4jmqmb5m . Last , rtDW . mw4jmqmb5m
. Tail , rtDW . mw4jmqmb5m . Head , rtP .
TransportDelay_InitOutput_pz2dgrhemk , 0 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB .
ehk41k1jvu = 1.0 / rtP . Atenuacion_canal * rtB . pbihxnhzkv ; { real_T * *
uBuffer = ( real_T * * ) & rtDW . laigziygdt . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . laigziygdt . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 0.25 / rtP .
Frec2 ) ; rtB . jdmdbzovgb = rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , rtDW . mbpoqz0vfq . CircularBufSize , & rtDW .
mbpoqz0vfq . Last , rtDW . mbpoqz0vfq . Tail , rtDW . mbpoqz0vfq . Head , rtP
. TransportDelay1_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB .
dl2z1kzk4x = 1.0 / rtP . Atenuacion_canal * rtB . jdmdbzovgb ; { real_T * *
uBuffer = ( real_T * * ) & rtDW . duyhxp3i2o . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . duyhxp3i2o . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - rtP .
TransportDelay12_Delay ; if ( rtP . TransportDelay12_Delay == 0.0 )
lvfklq2cvb = rtB . bonunno3da ; else lvfklq2cvb = rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW . jqyvcdfdil .
CircularBufSize , & rtDW . jqyvcdfdil . Last , rtDW . jqyvcdfdil . Tail ,
rtDW . jqyvcdfdil . Head , rtP . TransportDelay12_InitOutput , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) ==
ssGetT ( rtS ) ) ) ) ; } rtB . drqnxkzet4 = ssGetT ( rtS ) ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { auvdmsssjz = ! rtDW . oz50sdopcp ; if ( rtB
. e1nhqxjvjn ) { rtB . hduwbah451 = rtP . Constant20_Value ; } else { rtB .
hduwbah451 = rtP . Constant19_Value ; } rtB . osh4e3wkbx = rtB . hduwbah451 *
rtP . Constant1_Value_obqa0ysasv ; } { real_T * * uBuffer = ( real_T * * ) &
rtDW . pfzlxqtttd . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * )
& rtDW . pfzlxqtttd . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ;
real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb ) ; rtB . jkosinqwcz =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
b5jqmouq00 . CircularBufSize , & rtDW . b5jqmouq00 . Last , rtDW . b5jqmouq00
. Tail , rtDW . b5jqmouq00 . Head , rtP . TransportDelay2_InitOutput , 1 , (
boolean_T ) ( ssIsMinorTimeStep ( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) ==
ssGetT ( rtS ) ) ) ) ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
kpyzd0zppl . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. kpyzd0zppl . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; real_T
tMinusDelay = simTime - ( 1.0 / rtP . Rb ) ; rtB . mhvwbma2wc =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
dsos1nl3ug . CircularBufSize , & rtDW . dsos1nl3ug . Last , rtDW . dsos1nl3ug
. Tail , rtDW . dsos1nl3ug . Head , rtP .
TransportDelay1_InitOutput_km2up0labu , 0 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } {
real_T * * uBuffer = ( real_T * * ) & rtDW . anw4lh3mkt . TUbufferPtrs [ 0 ]
; real_T * * tBuffer = ( real_T * * ) & rtDW . anw4lh3mkt . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 /
rtP . Rb ) ; rtB . hoboqemidv = rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , rtDW . miosm0kvi1 . CircularBufSize , & rtDW .
miosm0kvi1 . Last , rtDW . miosm0kvi1 . Tail , rtDW . miosm0kvi1 . Head , rtP
. TransportDelay4_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . hth3y5boa4 . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . hth3y5boa4 . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . pw3nmstdx1 = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . daastispqd . CircularBufSize , & rtDW . daastispqd . Last ,
rtDW . daastispqd . Tail , rtDW . daastispqd . Head , rtP .
TransportDelay3_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . jkfvz1vsm1 . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . jkfvz1vsm1 . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . aekkmo2dza = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . ga03tvlrh0 . CircularBufSize , & rtDW . ga03tvlrh0 . Last ,
rtDW . ga03tvlrh0 . Tail , rtDW . ga03tvlrh0 . Head , rtP .
TransportDelay6_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . axitmt5w4i . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . axitmt5w4i . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . leuwvo5bd0 = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . d2cdydaqvh . CircularBufSize , & rtDW . d2cdydaqvh . Last ,
rtDW . d2cdydaqvh . Tail , rtDW . d2cdydaqvh . Head , rtP .
TransportDelay5_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . bz4cstgndq . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . bz4cstgndq . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . kzkfn1s2js = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . lo3fy120pk . CircularBufSize , & rtDW . lo3fy120pk . Last ,
rtDW . lo3fy120pk . Tail , rtDW . lo3fy120pk . Head , rtP .
TransportDelay8_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . ifxwkbjtsf . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . ifxwkbjtsf . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . hdfbddrmbc = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . i5j0s3drdy . CircularBufSize , & rtDW . i5j0s3drdy . Last ,
rtDW . i5j0s3drdy . Tail , rtDW . i5j0s3drdy . Head , rtP .
TransportDelay7_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . oydq1getqe . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . oydq1getqe . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . fetl3awrl2 = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . naehoe5c24 . CircularBufSize , & rtDW . naehoe5c24 . Last ,
rtDW . naehoe5c24 . Tail , rtDW . naehoe5c24 . Head , rtP .
TransportDelay9_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . nzhehebsh0 . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . nzhehebsh0 . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . hd11xynwm2 = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . atsr3zriuy . CircularBufSize , & rtDW . atsr3zriuy . Last ,
rtDW . atsr3zriuy . Tail , rtDW . atsr3zriuy . Head , rtP .
TransportDelay11_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . erisf50gfz . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . erisf50gfz . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; rtB . nuzxbadudr = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . ogdeiw34cz . CircularBufSize , & rtDW . ogdeiw34cz . Last ,
rtDW . ogdeiw34cz . Tail , rtDW . ogdeiw34cz . Head , rtP .
TransportDelay10_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } { real_T * *
uBuffer = ( real_T * * ) & rtDW . jszhk4b0c2 . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & rtDW . jszhk4b0c2 . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 1.0 / rtP . Rb )
; paeaglgzht = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , rtDW . nan1e3l5p0 . CircularBufSize , & rtDW . nan1e3l5p0 . Last ,
rtDW . nan1e3l5p0 . Tail , rtDW . nan1e3l5p0 . Head , rtP .
TransportDelay13_InitOutput , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS )
&& ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB .
dfyucx0pjs = ( ( ( ( ( ( ( ( ( ( ( rtB . jkosinqwcz * rtP . Constant2_Value +
rtB . osh4e3wkbx ) + rtB . mhvwbma2wc * rtP . Constant3_Value ) + rtB .
hoboqemidv * rtP . Constant4_Value ) + rtB . pw3nmstdx1 * rtP .
Constant5_Value_pqkhorznoi ) + rtB . aekkmo2dza * rtP .
Constant6_Value_oth1tjvwv0 ) + rtB . leuwvo5bd0 * rtP . Constant7_Value ) +
rtB . kzkfn1s2js * rtP . Constant8_Value ) + rtB . hdfbddrmbc * rtP .
Constant9_Value ) + rtB . fetl3awrl2 * rtP . Constant10_Value ) + rtB .
hd11xynwm2 * rtP . Constant11_Value ) + rtB . nuzxbadudr * rtP .
Constant12_Value ) + paeaglgzht * rtP . Constant13_Value ; if (
ssIsMajorTimeStep ( rtS ) ) { rtDW . pejw2pyiiz = ( rtB . dfyucx0pjs > rtP .
Switch_Threshold ) ; rtDW . j2llbcud4w = ( rtB . dfyucx0pjs > rtP .
Switch1_Threshold ) ; } if ( rtDW . pejw2pyiiz ) { taskTimeV = rtP .
Constant15_Value ; } else { taskTimeV = rtP . Constant14_Value ; } if ( rtDW
. j2llbcud4w ) { ratio = rtP . Constant18_Value ; } else { ratio = rtP .
Constant17_Value ; } rtB . o2g3bsob40 = ( ( taskTimeV != 0.0 ) || ( ratio !=
0.0 ) ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { h4ky5h1grf = rtDW .
by0zcdyxc4 ; d5zlt11l1p ( rtS , rtB . i4cllywuc1 [ 0 ] , rtB . o2g3bsob40 ,
h4ky5h1grf , & rtB . abmuy5rnsq , & rtDW . abmuy5rnsq ) ; dnioykk3w1 ( rtS ,
rtB . i4cllywuc1 [ 1 ] , rtB . o2g3bsob40 , h4ky5h1grf , & rtB . mpycb0evfp ,
& rtDW . mpycb0evfp ) ; heolw2ozxt = ( rtB . abmuy5rnsq . ltgb5gkcbo || rtB .
mpycb0evfp . hmpzhh3n3o ) ; rtB . f0xjphnymz = ( auvdmsssjz && heolw2ozxt ) ;
rtB . owlyu5iz4l = rtDW . bwkxnxzhy1 ; rtB . loxkzong0h = rtP . Datos / rtP .
Rb - 2.2204460492503131E-16 ; } if ( rtB . f0xjphnymz ) { rtB . dwfqmte2n3 =
rtB . drqnxkzet4 ; } else { rtB . dwfqmte2n3 = rtB . owlyu5iz4l ; } rtB .
gx1uxu4kds = rtB . dwfqmte2n3 + rtB . loxkzong0h ; if ( ssIsSampleHit ( rtS ,
1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . alduujhq0a = ( rtB .
gx1uxu4kds > rtB . drqnxkzet4 ) ; } rtB . nekkkm0p0a = rtDW . alduujhq0a ; }
if ( rtB . nekkkm0p0a ) { rtB . co4tajx3jh = lvfklq2cvb ; } else { rtB .
co4tajx3jh = rtP . Constant16_Value ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsMajorTimeStep ( rtS ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
rtPrevZCX . ctjn34sghg , ( rtB . co4tajx3jh ) ) ; if ( zcEvent != NO_ZCEVENT
) { if ( ssGetLogOutput ( rtS ) ) { { double locTime = ssGetTaskTime ( rtS ,
1 ) ; ; if ( rtwTimeInLoggingInterval ( rtliGetLoggingInterval ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) , locTime ) ) { rt_UpdateLogVar ( ( LogVar
* ) ( LogVar * ) ( rtDW . lp4l4cdghx . LoggedData ) , & rtB . e1nhqxjvjn , 0
) ; } } } rtDW . lekdfle5yl = 4 ; } } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) {
rtB . hd0ccnz5kj = rtP . MatrixGain_Gain * rtDW . kikmlfmksm + rtP .
GaussianNoiseGenerator_m_feibr5czzb ; rtB . kmsebnmjbu = rtB . hd0ccnz5kj ; }
{ real_T * * uBuffer = ( real_T * * ) & rtDW . emliqyd1hi . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & rtDW . emliqyd1hi . TUbufferPtrs [
1 ] ; real_T simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( 0.5
/ rtP . Frec1 ) ; rtB . ay4kbspa2f = rt_TDelayInterpolate ( tMinusDelay , 0.0
, * tBuffer , * uBuffer , rtDW . oivjundpbe . CircularBufSize , & rtDW .
oivjundpbe . Last , rtDW . oivjundpbe . Tail , rtDW . oivjundpbe . Head , rtP
. TransportDelay1_InitOutput_cz0jjsby1m , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS
) ) ) ) ; } rtB . dwuvmlamlj = rtB . ay4kbspa2f + rtB . otfd1hdnf4 ; rtB .
iup0qas13y = rtP . Constant_Value * rtB . dwuvmlamlj ; rtB . pbk3xyooxn = rtB
. kmsebnmjbu + rtB . iup0qas13y ; { real_T * * uBuffer = ( real_T * * ) &
rtDW . j0z4zsdtwg . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * )
& rtDW . j0z4zsdtwg . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ;
real_T tMinusDelay = simTime - ( 0.5 / rtP . Frec2 ) ; rtB . jj2crb3wdo =
rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer , rtDW .
os1vqq3jgt . CircularBufSize , & rtDW . os1vqq3jgt . Last , rtDW . os1vqq3jgt
. Tail , rtDW . os1vqq3jgt . Head , rtP .
TransportDelay_InitOutput_nwut2o4lpm , 0 , ( boolean_T ) ( ssIsMinorTimeStep
( rtS ) && ( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB .
flwwemz4a3 = rtB . jj2crb3wdo + rtB . otfd1hdnf4 ; rtB . pskl4q2wwt = rtB .
flwwemz4a3 * rtP . Constant_Value ; rtB . exdbaattar = rtB . pskl4q2wwt + rtB
. kmsebnmjbu ; rtB . izg2hxr1hm = 0.0 ; rtB . izg2hxr1hm += rtP . Filtro_C *
rtX . hrccq1fi0z [ 5 ] ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB .
izg2hxr1hm > 0.0 ) { rtDW . hhfaeeexeg = 1 ; } else if ( rtB . izg2hxr1hm <
0.0 ) { rtDW . hhfaeeexeg = - 1 ; } else { rtDW . hhfaeeexeg = 0 ; } rtB .
f1l5jsixgw = rtDW . hhfaeeexeg ; } if ( ssIsMajorTimeStep ( rtS ) ) { zcEvent
= rt_ZCFcn ( ANY_ZERO_CROSSING , & rtPrevZCX . mj4uwtxvw4 , ( rtB .
cwrlg5uwpe ) ) ; if ( zcEvent != NO_ZCEVENT ) { rtX . gxe5sdikfw = rtP .
Integrator_IC_ptowdeldtu ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; } } rtB . fosqwahuok = rtX . gxe5sdikfw ; rtB . orkfi0mp2e = ssGetT ( rtS )
; rtB . eaief2hsbj = ( rtB . cwrlg5uwpe != 0.0 ) ; if ( ssIsSampleHit ( rtS ,
1 , 0 ) ) { avljzyfwyu = ! rtDW . kmeshewsao ; e540n3jc21 = rtDW . cbjfpdjiyu
; d5zlt11l1p ( rtS , rtB . fto4cglprz [ 0 ] , rtB . eaief2hsbj , e540n3jc21 ,
& rtB . d5zlt11l1pl , & rtDW . d5zlt11l1pl ) ; dnioykk3w1 ( rtS , rtB .
fto4cglprz [ 1 ] , rtB . eaief2hsbj , e540n3jc21 , & rtB . dnioykk3w1k , &
rtDW . dnioykk3w1k ) ; jfm1h1sfgj = ( rtB . d5zlt11l1pl . ltgb5gkcbo || rtB .
dnioykk3w1k . hmpzhh3n3o ) ; rtB . dumyggkchi = ( avljzyfwyu && jfm1h1sfgj )
; rtB . izpbcjjrig = rtDW . livmyfqsgc ; rtB . pgvargzqvr = 0.9 / rtP . Rb -
2.2204460492503131E-16 ; } if ( rtB . dumyggkchi ) { rtB . gwu42iz5ys = rtB .
orkfi0mp2e ; } else { rtB . gwu42iz5ys = rtB . izpbcjjrig ; } rtB .
ityop505e4 = rtB . gwu42iz5ys + rtB . pgvargzqvr ; if ( ssIsSampleHit ( rtS ,
1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . bctphvd2sv = ( rtB .
ityop505e4 > rtB . orkfi0mp2e ) ; } rtB . hgcnrsrftd = rtDW . bctphvd2sv ; }
rtB . ghaifzgd35 = rtB . hgcnrsrftd ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
if ( ssIsMajorTimeStep ( rtS ) ) { if ( ( ! rtB . ghaifzgd35 ) && ( rtPrevZCX
. cvp0g55jmi != ZERO_ZCSIG ) ) { rtB . munnuokh3b = rtB . fosqwahuok ; rtDW .
loneq0nrmu = 4 ; } rtPrevZCX . cvp0g55jmi = rtB . ghaifzgd35 ; } rtB .
hrs0mectw5 = muDoubleScalarAbs ( rtB . munnuokh3b ) ; iyu3pyojoi = ! rtDW .
alglspiynp ; } rtB . fgrkiz4z0n = ssGetT ( rtS ) ; rtB . bnhnntm3f4 = ( rtB .
cwrlg5uwpe != 0.0 ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { awcqntc1jt =
rtDW . koquxjpxpa ; d5zlt11l1p ( rtS , rtB . nj0vsa0aao [ 0 ] , rtB .
bnhnntm3f4 , awcqntc1jt , & rtB . gggqmave4q , & rtDW . gggqmave4q ) ;
dnioykk3w1 ( rtS , rtB . nj0vsa0aao [ 1 ] , rtB . bnhnntm3f4 , awcqntc1jt , &
rtB . fkhi333c1w , & rtDW . fkhi333c1w ) ; mfqlwvbvy4 = ( rtB . gggqmave4q .
ltgb5gkcbo || rtB . fkhi333c1w . hmpzhh3n3o ) ; rtB . ajbeq5hpnj = (
iyu3pyojoi && mfqlwvbvy4 ) ; rtB . cswpv2o1kk = rtDW . nfditlbohk ; rtB .
hx1rf2yrz2 = 0.1 / rtP . Rb - 2.2204460492503131E-16 ; } if ( rtB .
ajbeq5hpnj ) { rtB . de2xsxb24p = rtB . fgrkiz4z0n ; } else { rtB .
de2xsxb24p = rtB . cswpv2o1kk ; } rtB . cviwvtwqhc = rtB . de2xsxb24p + rtB .
hx1rf2yrz2 ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep (
rtS ) ) { rtDW . bqhe24xuds = ( rtB . cviwvtwqhc > rtB . fgrkiz4z0n ) ; } rtB
. eizf1ealtw = rtDW . bqhe24xuds ; } if ( ssIsMajorTimeStep ( rtS ) ) {
avljzyfwyu = ( ( ! rtB . eizf1ealtw ) && ( rtPrevZCX . kci0nfmn3i !=
ZERO_ZCSIG ) ) ; rtPrevZCX . kci0nfmn3i = rtB . eizf1ealtw ; if ( avljzyfwyu
) { rtX . cc5042ocv2 = rtP . Integrator1_IC ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } } rtB . l5nwaj4e3i =
rtX . cc5042ocv2 ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . oxgn4zxxpe = (
rtB . l5nwaj4e3i >= 0.0 ) ; } rtB . looejrxoki = rtB . hrs0mectw5 - ( rtDW .
oxgn4zxxpe > 0 ? rtB . l5nwaj4e3i : - rtB . l5nwaj4e3i ) ; if ( ssIsSampleHit
( rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { zcEvent = rt_ZCFcn (
ANY_ZERO_CROSSING , & rtPrevZCX . coh1zb2qmc , ( rtB . cwrlg5uwpe ) ) ; if (
zcEvent != NO_ZCEVENT ) { rtB . dduxw540hu = rtB . looejrxoki ; rtDW .
moelhnb1d2 = 4 ; } } } rtB . axof5reva4 = ssGetT ( rtS ) ; if ( ssIsSampleHit
( rtS , 1 , 0 ) ) { rtB . awasz3p2hm = rtP . kv2 * rtB . dduxw540hu + rtP .
Rb / 2.0 ; mivhx1fvuu ( rtS , jfm1h1sfgj , rtB . axof5reva4 , & rtB .
mivhx1fvuuy , & rtDW . mivhx1fvuuy , & rtPrevZCX . mivhx1fvuuy ) ; rtB .
m3xclbw4n1 = rtB . mivhx1fvuuy . hml4vbrazh + rtP . Constant_Value_mvnfzatsby
; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . ox1bxr2hww = ( rtB . m3xclbw4n1 >
rtB . axof5reva4 ) ; } } rtB . jka1elz4sz = ssGetT ( rtS ) ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { mivhx1fvuu ( rtS , mfqlwvbvy4 , rtB .
jka1elz4sz , & rtB . dyorcglstw , & rtDW . dyorcglstw , & rtPrevZCX .
dyorcglstw ) ; rtB . ikxyn0xytc = rtB . dyorcglstw . hml4vbrazh + rtP .
Constant_Value_izjuzrtanz ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
kltylslzkb = ( rtB . ikxyn0xytc > rtB . jka1elz4sz ) ; } } rtB . h32dvvdjsr =
rtB . exdbaattar * rtB . ehk41k1jvu ; rtB . cfvwyihfgi = rtB . dl2z1kzk4x *
rtB . pbk3xyooxn ; rtB . bbdybg5bbo = rtB . h32dvvdjsr - rtB . cfvwyihfgi ;
rtB . nb4mlfbe25 = rtX . husvwrmjnn ; rtB . nrzgv2asbm = muDoubleScalarCos (
rtB . nb4mlfbe25 * 6.2831853071795862 ) ; rtB . kb3qoydtul = rtB . exdbaattar
* rtP . Atenuacion_canal * rtB . nrzgv2asbm ; rtB . emzymu3s4t = rtP . R2 /
rtP . R1 * rtB . kb3qoydtul ; rtB . dhvezilxca = rtX . g01iry0rqn ; rtB .
fy1jpymzvl = rtB . emzymu3s4t + rtB . dhvezilxca ; rtB . gwfkgabvtm = rtX .
iquu4mgvfb ; rtB . ijhgy4lexb = muDoubleScalarCos ( rtB . gwfkgabvtm *
6.2831853071795862 ) ; rtB . csu05jokxd = rtB . ijhgy4lexb * rtP .
Atenuacion_canal * rtB . pbk3xyooxn ; rtB . eg0uqlyrw2 = rtP . R2 / rtP . R1
* rtB . csu05jokxd ; rtB . dhxzfrd1ut = rtX . lnhetubiv2 ; rtB . ihg3emy0vs =
rtB . eg0uqlyrw2 + rtB . dhxzfrd1ut ; rtB . l1ylzo5bhw = rtP . kv * rtB .
fy1jpymzvl ; rtB . cj3eokpnbs = rtB . l1ylzo5bhw + rtP . Frec1 ; rtB .
i14aygkcoq = rtP . kv * rtB . ihg3emy0vs ; rtB . a4wt4ee5p1 = rtB .
i14aygkcoq + rtP . Frec2 ; rtB . fz1wrzhdaa = 1.0 / ( rtP . R1 * rtP . C ) *
rtB . kb3qoydtul ; rtB . kp3wrgz5sh = 1.0 / ( rtP . R1 * rtP . C ) * rtB .
csu05jokxd ; rtB . fuwgkaabcp = ssGetT ( rtS ) ; if ( ssIsSampleHit ( rtS , 1
, 0 ) ) { mivhx1fvuu ( rtS , heolw2ozxt , rtB . fuwgkaabcp , & rtB .
jiixgvrfhd , & rtDW . jiixgvrfhd , & rtPrevZCX . jiixgvrfhd ) ; rtB .
d2vdhfxwnv = rtB . jiixgvrfhd . hml4vbrazh + rtP . Constant_Value_pmuy4epl2c
; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . luhachiin3 = ( rtB . d2vdhfxwnv >
rtB . fuwgkaabcp ) ; } } UNUSED_PARAMETER ( tid ) ; } void MdlOutputsTID5 (
int_T tid ) { switch ( ( int32_T ) rtP . Constant1_Value ) { case 1 : rtB .
fto4cglprz [ 0 ] = rtP . posedge_Value [ 0 ] ; rtB . fto4cglprz [ 1 ] = rtP .
posedge_Value [ 1 ] ; break ; case 2 : rtB . fto4cglprz [ 0 ] = rtP .
negedge_Value [ 0 ] ; rtB . fto4cglprz [ 1 ] = rtP . negedge_Value [ 1 ] ;
break ; default : rtB . fto4cglprz [ 0 ] = rtP . eitheredge_Value [ 0 ] ; rtB
. fto4cglprz [ 1 ] = rtP . eitheredge_Value [ 1 ] ; break ; } switch ( (
int32_T ) rtP . Constant1_Value_lpebpexhqd ) { case 1 : rtB . nj0vsa0aao [ 0
] = rtP . posedge_Value_iryngzqrd1 [ 0 ] ; rtB . nj0vsa0aao [ 1 ] = rtP .
posedge_Value_iryngzqrd1 [ 1 ] ; break ; case 2 : rtB . nj0vsa0aao [ 0 ] =
rtP . negedge_Value_a22nqhbklc [ 0 ] ; rtB . nj0vsa0aao [ 1 ] = rtP .
negedge_Value_a22nqhbklc [ 1 ] ; break ; default : rtB . nj0vsa0aao [ 0 ] =
rtP . eitheredge_Value_a1qgi2i0lx [ 0 ] ; rtB . nj0vsa0aao [ 1 ] = rtP .
eitheredge_Value_a1qgi2i0lx [ 1 ] ; break ; } switch ( ( int32_T ) rtP .
Constant1_Value_bsax1tsxxz ) { case 1 : rtB . i4cllywuc1 [ 0 ] = rtP .
posedge_Value_fsgb0grkvo [ 0 ] ; rtB . i4cllywuc1 [ 1 ] = rtP .
posedge_Value_fsgb0grkvo [ 1 ] ; break ; case 2 : rtB . i4cllywuc1 [ 0 ] =
rtP . negedge_Value_ackdjcny40 [ 0 ] ; rtB . i4cllywuc1 [ 1 ] = rtP .
negedge_Value_ackdjcny40 [ 1 ] ; break ; default : rtB . i4cllywuc1 [ 0 ] =
rtP . eitheredge_Value_lzvwtrli1x [ 0 ] ; rtB . i4cllywuc1 [ 1 ] = rtP .
eitheredge_Value_lzvwtrli1x [ 1 ] ; break ; } UNUSED_PARAMETER ( tid ) ; }
void MdlUpdate ( int_T tid ) { { real_T * * uBuffer = ( real_T * * ) & rtDW .
j0ojopv3o4 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. j0ojopv3o4 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
actgbahxga . Head = ( ( rtDW . actgbahxga . Head < ( rtDW . actgbahxga .
CircularBufSize - 1 ) ) ? ( rtDW . actgbahxga . Head + 1 ) : 0 ) ; if ( rtDW
. actgbahxga . Head == rtDW . actgbahxga . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . actgbahxga . CircularBufSize , & rtDW
. actgbahxga . Tail , & rtDW . actgbahxga . Head , & rtDW . actgbahxga . Last
, simTime - rtP . TransportDelay_Delay , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . actgbahxga . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . actgbahxga . Head ] = simTime ; ( * uBuffer ) [ rtDW .
actgbahxga . Head ] = rtB . kvdiwfhjmc ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . odiqda1u1t . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . odiqda1u1t . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . cc05czrsze . Head = ( ( rtDW . cc05czrsze . Head < ( rtDW .
cc05czrsze . CircularBufSize - 1 ) ) ? ( rtDW . cc05czrsze . Head + 1 ) : 0 )
; if ( rtDW . cc05czrsze . Head == rtDW . cc05czrsze . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . cc05czrsze . CircularBufSize , & rtDW
. cc05czrsze . Tail , & rtDW . cc05czrsze . Head , & rtDW . cc05czrsze . Last
, simTime - rtP . Retraso_canal , tBuffer , uBuffer , ( NULL ) , ( boolean_T
) 0 , false , & rtDW . cc05czrsze . MaxNewBufSize ) ) { ssSetErrorStatus (
rtS , "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW
. cc05czrsze . Head ] = simTime ; ( * uBuffer ) [ rtDW . cc05czrsze . Head ]
= rtB . dc0ixgrh4v ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW .
ou0ychata3 = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . imgdcg24fm ) * rtP .
RandomNumber_StdDev + rtP . RandomNumber_Mean ; } { real_T * * uBuffer = (
real_T * * ) & rtDW . mx1qnjpwkr . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & rtDW . mx1qnjpwkr . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( rtS ) ; rtDW . ikxgblv1zv . Head = ( ( rtDW . ikxgblv1zv . Head < (
rtDW . ikxgblv1zv . CircularBufSize - 1 ) ) ? ( rtDW . ikxgblv1zv . Head + 1
) : 0 ) ; if ( rtDW . ikxgblv1zv . Head == rtDW . ikxgblv1zv . Tail ) { if (
! rt_TDelayUpdateTailOrGrowBuf ( & rtDW . ikxgblv1zv . CircularBufSize , &
rtDW . ikxgblv1zv . Tail , & rtDW . ikxgblv1zv . Head , & rtDW . ikxgblv1zv .
Last , simTime - rtP . TransportDelay_Delay_dget2i1x1r , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & rtDW . ikxgblv1zv . MaxNewBufSize ) )
{ ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } }
( * tBuffer ) [ rtDW . ikxgblv1zv . Head ] = simTime ; ( * uBuffer ) [ rtDW .
ikxgblv1zv . Head ] = rtB . omyffgmxzc ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . c1abig5l5b . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . c1abig5l5b . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . c0ewitmagq . Head = ( ( rtDW . c0ewitmagq . Head < ( rtDW .
c0ewitmagq . CircularBufSize - 1 ) ) ? ( rtDW . c0ewitmagq . Head + 1 ) : 0 )
; if ( rtDW . c0ewitmagq . Head == rtDW . c0ewitmagq . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . c0ewitmagq . CircularBufSize , & rtDW
. c0ewitmagq . Tail , & rtDW . c0ewitmagq . Head , & rtDW . c0ewitmagq . Last
, simTime - ( ( 0.95 / rtP . Rb ) ) , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . c0ewitmagq . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . c0ewitmagq . Head ] = simTime ; ( * uBuffer ) [ rtDW .
c0ewitmagq . Head ] = rtB . cwrlg5uwpe ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . l3olmqutvm . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . l3olmqutvm . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . mw4jmqmb5m . Head = ( ( rtDW . mw4jmqmb5m . Head < ( rtDW .
mw4jmqmb5m . CircularBufSize - 1 ) ) ? ( rtDW . mw4jmqmb5m . Head + 1 ) : 0 )
; if ( rtDW . mw4jmqmb5m . Head == rtDW . mw4jmqmb5m . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . mw4jmqmb5m . CircularBufSize , & rtDW
. mw4jmqmb5m . Tail , & rtDW . mw4jmqmb5m . Head , & rtDW . mw4jmqmb5m . Last
, simTime - ( 0.25 / rtP . Frec1 ) , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . mw4jmqmb5m . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . mw4jmqmb5m . Head ] = simTime ; ( * uBuffer ) [ rtDW .
mw4jmqmb5m . Head ] = rtB . nrzgv2asbm ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . laigziygdt . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . laigziygdt . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . mbpoqz0vfq . Head = ( ( rtDW . mbpoqz0vfq . Head < ( rtDW .
mbpoqz0vfq . CircularBufSize - 1 ) ) ? ( rtDW . mbpoqz0vfq . Head + 1 ) : 0 )
; if ( rtDW . mbpoqz0vfq . Head == rtDW . mbpoqz0vfq . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . mbpoqz0vfq . CircularBufSize , & rtDW
. mbpoqz0vfq . Tail , & rtDW . mbpoqz0vfq . Head , & rtDW . mbpoqz0vfq . Last
, simTime - ( 0.25 / rtP . Frec2 ) , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . mbpoqz0vfq . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . mbpoqz0vfq . Head ] = simTime ; ( * uBuffer ) [ rtDW .
mbpoqz0vfq . Head ] = rtB . ijhgy4lexb ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . duyhxp3i2o . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . duyhxp3i2o . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . jqyvcdfdil . Head = ( ( rtDW . jqyvcdfdil . Head < ( rtDW .
jqyvcdfdil . CircularBufSize - 1 ) ) ? ( rtDW . jqyvcdfdil . Head + 1 ) : 0 )
; if ( rtDW . jqyvcdfdil . Head == rtDW . jqyvcdfdil . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . jqyvcdfdil . CircularBufSize , & rtDW
. jqyvcdfdil . Tail , & rtDW . jqyvcdfdil . Head , & rtDW . jqyvcdfdil . Last
, simTime - rtP . TransportDelay12_Delay , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . jqyvcdfdil . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . jqyvcdfdil . Head ] = simTime ; ( * uBuffer ) [ rtDW .
jqyvcdfdil . Head ] = rtB . bonunno3da ; } if ( ssIsSampleHit ( rtS , 1 , 0 )
) { rtDW . oz50sdopcp = rtB . nekkkm0p0a ; } { real_T * * uBuffer = ( real_T
* * ) & rtDW . pfzlxqtttd . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & rtDW . pfzlxqtttd . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( rtS ) ; rtDW . b5jqmouq00 . Head = ( ( rtDW . b5jqmouq00 . Head < (
rtDW . b5jqmouq00 . CircularBufSize - 1 ) ) ? ( rtDW . b5jqmouq00 . Head + 1
) : 0 ) ; if ( rtDW . b5jqmouq00 . Head == rtDW . b5jqmouq00 . Tail ) { if (
! rt_TDelayUpdateTailOrGrowBuf ( & rtDW . b5jqmouq00 . CircularBufSize , &
rtDW . b5jqmouq00 . Tail , & rtDW . b5jqmouq00 . Head , & rtDW . b5jqmouq00 .
Last , simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . b5jqmouq00 . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . b5jqmouq00 . Head ] = simTime ; ( * uBuffer ) [ rtDW .
b5jqmouq00 . Head ] = rtB . hduwbah451 ; } { real_T * * uBuffer = ( real_T *
* ) & rtDW . kpyzd0zppl . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & rtDW . kpyzd0zppl . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT (
rtS ) ; rtDW . dsos1nl3ug . Head = ( ( rtDW . dsos1nl3ug . Head < ( rtDW .
dsos1nl3ug . CircularBufSize - 1 ) ) ? ( rtDW . dsos1nl3ug . Head + 1 ) : 0 )
; if ( rtDW . dsos1nl3ug . Head == rtDW . dsos1nl3ug . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . dsos1nl3ug . CircularBufSize , & rtDW
. dsos1nl3ug . Tail , & rtDW . dsos1nl3ug . Head , & rtDW . dsos1nl3ug . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . dsos1nl3ug . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
dsos1nl3ug . Head ] = simTime ; ( * uBuffer ) [ rtDW . dsos1nl3ug . Head ] =
rtB . jkosinqwcz ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
anw4lh3mkt . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. anw4lh3mkt . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
miosm0kvi1 . Head = ( ( rtDW . miosm0kvi1 . Head < ( rtDW . miosm0kvi1 .
CircularBufSize - 1 ) ) ? ( rtDW . miosm0kvi1 . Head + 1 ) : 0 ) ; if ( rtDW
. miosm0kvi1 . Head == rtDW . miosm0kvi1 . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . miosm0kvi1 . CircularBufSize , & rtDW
. miosm0kvi1 . Tail , & rtDW . miosm0kvi1 . Head , & rtDW . miosm0kvi1 . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . miosm0kvi1 . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
miosm0kvi1 . Head ] = simTime ; ( * uBuffer ) [ rtDW . miosm0kvi1 . Head ] =
rtB . mhvwbma2wc ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
hth3y5boa4 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. hth3y5boa4 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
daastispqd . Head = ( ( rtDW . daastispqd . Head < ( rtDW . daastispqd .
CircularBufSize - 1 ) ) ? ( rtDW . daastispqd . Head + 1 ) : 0 ) ; if ( rtDW
. daastispqd . Head == rtDW . daastispqd . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . daastispqd . CircularBufSize , & rtDW
. daastispqd . Tail , & rtDW . daastispqd . Head , & rtDW . daastispqd . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . daastispqd . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
daastispqd . Head ] = simTime ; ( * uBuffer ) [ rtDW . daastispqd . Head ] =
rtB . hoboqemidv ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
jkfvz1vsm1 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. jkfvz1vsm1 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
ga03tvlrh0 . Head = ( ( rtDW . ga03tvlrh0 . Head < ( rtDW . ga03tvlrh0 .
CircularBufSize - 1 ) ) ? ( rtDW . ga03tvlrh0 . Head + 1 ) : 0 ) ; if ( rtDW
. ga03tvlrh0 . Head == rtDW . ga03tvlrh0 . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . ga03tvlrh0 . CircularBufSize , & rtDW
. ga03tvlrh0 . Tail , & rtDW . ga03tvlrh0 . Head , & rtDW . ga03tvlrh0 . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . ga03tvlrh0 . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
ga03tvlrh0 . Head ] = simTime ; ( * uBuffer ) [ rtDW . ga03tvlrh0 . Head ] =
rtB . pw3nmstdx1 ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
axitmt5w4i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. axitmt5w4i . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
d2cdydaqvh . Head = ( ( rtDW . d2cdydaqvh . Head < ( rtDW . d2cdydaqvh .
CircularBufSize - 1 ) ) ? ( rtDW . d2cdydaqvh . Head + 1 ) : 0 ) ; if ( rtDW
. d2cdydaqvh . Head == rtDW . d2cdydaqvh . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . d2cdydaqvh . CircularBufSize , & rtDW
. d2cdydaqvh . Tail , & rtDW . d2cdydaqvh . Head , & rtDW . d2cdydaqvh . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . d2cdydaqvh . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
d2cdydaqvh . Head ] = simTime ; ( * uBuffer ) [ rtDW . d2cdydaqvh . Head ] =
rtB . aekkmo2dza ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
bz4cstgndq . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. bz4cstgndq . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
lo3fy120pk . Head = ( ( rtDW . lo3fy120pk . Head < ( rtDW . lo3fy120pk .
CircularBufSize - 1 ) ) ? ( rtDW . lo3fy120pk . Head + 1 ) : 0 ) ; if ( rtDW
. lo3fy120pk . Head == rtDW . lo3fy120pk . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . lo3fy120pk . CircularBufSize , & rtDW
. lo3fy120pk . Tail , & rtDW . lo3fy120pk . Head , & rtDW . lo3fy120pk . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . lo3fy120pk . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
lo3fy120pk . Head ] = simTime ; ( * uBuffer ) [ rtDW . lo3fy120pk . Head ] =
rtB . leuwvo5bd0 ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
ifxwkbjtsf . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. ifxwkbjtsf . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
i5j0s3drdy . Head = ( ( rtDW . i5j0s3drdy . Head < ( rtDW . i5j0s3drdy .
CircularBufSize - 1 ) ) ? ( rtDW . i5j0s3drdy . Head + 1 ) : 0 ) ; if ( rtDW
. i5j0s3drdy . Head == rtDW . i5j0s3drdy . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . i5j0s3drdy . CircularBufSize , & rtDW
. i5j0s3drdy . Tail , & rtDW . i5j0s3drdy . Head , & rtDW . i5j0s3drdy . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . i5j0s3drdy . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
i5j0s3drdy . Head ] = simTime ; ( * uBuffer ) [ rtDW . i5j0s3drdy . Head ] =
rtB . kzkfn1s2js ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
oydq1getqe . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. oydq1getqe . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
naehoe5c24 . Head = ( ( rtDW . naehoe5c24 . Head < ( rtDW . naehoe5c24 .
CircularBufSize - 1 ) ) ? ( rtDW . naehoe5c24 . Head + 1 ) : 0 ) ; if ( rtDW
. naehoe5c24 . Head == rtDW . naehoe5c24 . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . naehoe5c24 . CircularBufSize , & rtDW
. naehoe5c24 . Tail , & rtDW . naehoe5c24 . Head , & rtDW . naehoe5c24 . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . naehoe5c24 . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
naehoe5c24 . Head ] = simTime ; ( * uBuffer ) [ rtDW . naehoe5c24 . Head ] =
rtB . hdfbddrmbc ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
nzhehebsh0 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. nzhehebsh0 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
atsr3zriuy . Head = ( ( rtDW . atsr3zriuy . Head < ( rtDW . atsr3zriuy .
CircularBufSize - 1 ) ) ? ( rtDW . atsr3zriuy . Head + 1 ) : 0 ) ; if ( rtDW
. atsr3zriuy . Head == rtDW . atsr3zriuy . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . atsr3zriuy . CircularBufSize , & rtDW
. atsr3zriuy . Tail , & rtDW . atsr3zriuy . Head , & rtDW . atsr3zriuy . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . atsr3zriuy . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
atsr3zriuy . Head ] = simTime ; ( * uBuffer ) [ rtDW . atsr3zriuy . Head ] =
rtB . fetl3awrl2 ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
erisf50gfz . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. erisf50gfz . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
ogdeiw34cz . Head = ( ( rtDW . ogdeiw34cz . Head < ( rtDW . ogdeiw34cz .
CircularBufSize - 1 ) ) ? ( rtDW . ogdeiw34cz . Head + 1 ) : 0 ) ; if ( rtDW
. ogdeiw34cz . Head == rtDW . ogdeiw34cz . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . ogdeiw34cz . CircularBufSize , & rtDW
. ogdeiw34cz . Tail , & rtDW . ogdeiw34cz . Head , & rtDW . ogdeiw34cz . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . ogdeiw34cz . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
ogdeiw34cz . Head ] = simTime ; ( * uBuffer ) [ rtDW . ogdeiw34cz . Head ] =
rtB . hd11xynwm2 ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
jszhk4b0c2 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. jszhk4b0c2 . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
nan1e3l5p0 . Head = ( ( rtDW . nan1e3l5p0 . Head < ( rtDW . nan1e3l5p0 .
CircularBufSize - 1 ) ) ? ( rtDW . nan1e3l5p0 . Head + 1 ) : 0 ) ; if ( rtDW
. nan1e3l5p0 . Head == rtDW . nan1e3l5p0 . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . nan1e3l5p0 . CircularBufSize , & rtDW
. nan1e3l5p0 . Tail , & rtDW . nan1e3l5p0 . Head , & rtDW . nan1e3l5p0 . Last
, simTime - ( 1.0 / rtP . Rb ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , false , & rtDW . nan1e3l5p0 . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS
, "tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
nan1e3l5p0 . Head ] = simTime ; ( * uBuffer ) [ rtDW . nan1e3l5p0 . Head ] =
rtB . nuzxbadudr ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . by0zcdyxc4
= rtB . o2g3bsob40 ; rtDW . bwkxnxzhy1 = rtB . dwfqmte2n3 ; } if (
ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW . kikmlfmksm =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . kzibzv5iwi ) * rtP .
RandomNumber_StdDev_iveng2gmn4 + rtP . RandomNumber_Mean_pbcszkatmd ; } {
real_T * * uBuffer = ( real_T * * ) & rtDW . emliqyd1hi . TUbufferPtrs [ 0 ]
; real_T * * tBuffer = ( real_T * * ) & rtDW . emliqyd1hi . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( rtS ) ; rtDW . oivjundpbe . Head = ( ( rtDW .
oivjundpbe . Head < ( rtDW . oivjundpbe . CircularBufSize - 1 ) ) ? ( rtDW .
oivjundpbe . Head + 1 ) : 0 ) ; if ( rtDW . oivjundpbe . Head == rtDW .
oivjundpbe . Tail ) { if ( ! rt_TDelayUpdateTailOrGrowBuf ( & rtDW .
oivjundpbe . CircularBufSize , & rtDW . oivjundpbe . Tail , & rtDW .
oivjundpbe . Head , & rtDW . oivjundpbe . Last , simTime - ( 0.5 / rtP .
Frec1 ) , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & rtDW .
oivjundpbe . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ rtDW .
oivjundpbe . Head ] = simTime ; ( * uBuffer ) [ rtDW . oivjundpbe . Head ] =
rtB . otfd1hdnf4 ; } { real_T * * uBuffer = ( real_T * * ) & rtDW .
j0z4zsdtwg . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & rtDW
. j0z4zsdtwg . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( rtS ) ; rtDW .
os1vqq3jgt . Head = ( ( rtDW . os1vqq3jgt . Head < ( rtDW . os1vqq3jgt .
CircularBufSize - 1 ) ) ? ( rtDW . os1vqq3jgt . Head + 1 ) : 0 ) ; if ( rtDW
. os1vqq3jgt . Head == rtDW . os1vqq3jgt . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . os1vqq3jgt . CircularBufSize , & rtDW
. os1vqq3jgt . Tail , & rtDW . os1vqq3jgt . Head , & rtDW . os1vqq3jgt . Last
, simTime - ( 0.5 / rtP . Frec2 ) , tBuffer , uBuffer , ( NULL ) , (
boolean_T ) 0 , false , & rtDW . os1vqq3jgt . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; } } (
* tBuffer ) [ rtDW . os1vqq3jgt . Head ] = simTime ; ( * uBuffer ) [ rtDW .
os1vqq3jgt . Head ] = rtB . otfd1hdnf4 ; } if ( ssIsSampleHit ( rtS , 1 , 0 )
) { rtDW . kmeshewsao = rtB . hgcnrsrftd ; rtDW . cbjfpdjiyu = rtB .
eaief2hsbj ; rtDW . livmyfqsgc = rtB . gwu42iz5ys ; rtDW . alglspiynp = rtB .
eizf1ealtw ; rtDW . koquxjpxpa = rtB . bnhnntm3f4 ; rtDW . nfditlbohk = rtB .
de2xsxb24p ; } UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID5 ( int_T tid )
{ UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) { int_T is ;
int_T ci ; static const int8_T ir [ 11 ] = { 0 , 2 , 6 , 8 , 12 , 14 , 15 ,
16 , 17 , 18 , 19 } ; static const int8_T jc [ 19 ] = { 0 , 5 , 0 , 1 , 2 , 6
, 1 , 7 , 2 , 3 , 4 , 8 , 3 , 9 , 0 , 1 , 2 , 3 , 4 } ; static const int8_T
ir_p [ 11 ] = { 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static const
int8_T ir_e [ 7 ] = { 0 , 2 , 3 , 6 , 7 , 10 , 11 } ; static const int8_T
ir_i [ 7 ] = { 0 , 1 , 1 , 1 , 1 , 1 , 1 } ; static const int8_T jc_p [ 11 ]
= { 0 , 1 , 0 , 1 , 2 , 3 , 2 , 3 , 4 , 5 , 4 } ; XDot * _rtXdot ; _rtXdot =
( ( XDot * ) ssGetdX ( rtS ) ) ; for ( is = 0 ; is < 10 ; is ++ ) { _rtXdot
-> ccwzf3tws3 [ is ] = 0.0 ; for ( ci = ir [ is ] ; ci < ir [ is + 1 ] ; ci
++ ) { _rtXdot -> ccwzf3tws3 [ is ] += rtP . AnalogFilterDesign2_A [ ci ] *
rtX . ccwzf3tws3 [ jc [ ci ] ] ; } } _rtXdot -> cgdhzp3x0l = rtB . lufwcivalw
; _rtXdot -> imuz3fx4o3 = rtB . awasz3p2hm ; _rtXdot -> cfrslgfjyu = rtB .
f1l5jsixgw ; for ( is = 0 ; is < 10 ; is ++ ) { ci = ir_p [ is ] ; while ( ci
< ir_p [ is + 1 ] ) { _rtXdot -> ccwzf3tws3 [ is ] += rtP .
AnalogFilterDesign2_B * rtB . cuyzwij0cy ; ci = 1 ; } _rtXdot -> ids2w4qbzk [
is ] = 0.0 ; } for ( is = 0 ; is < 10 ; is ++ ) { for ( ci = ir [ is ] ; ci <
ir [ is + 1 ] ; ci ++ ) { _rtXdot -> ids2w4qbzk [ is ] += rtP .
AnalogFilterDesign_A [ ci ] * rtX . ids2w4qbzk [ jc [ ci ] ] ; } } for ( is =
0 ; is < 10 ; is ++ ) { ci = ir_p [ is ] ; while ( ci < ir_p [ is + 1 ] ) {
_rtXdot -> ids2w4qbzk [ is ] += rtP . AnalogFilterDesign_B * rtB . cuyzwij0cy
; ci = 1 ; } } _rtXdot -> nc3vmkovco = rtB . i3olz0n0gi ; _rtXdot ->
psx2ki4ws3 = rtB . ckmrjxysf3 ; for ( is = 0 ; is < 6 ; is ++ ) { _rtXdot ->
hrccq1fi0z [ is ] = 0.0 ; for ( ci = ir_e [ is ] ; ci < ir_e [ is + 1 ] ; ci
++ ) { _rtXdot -> hrccq1fi0z [ is ] += rtP . Filtro_A [ ci ] * rtX .
hrccq1fi0z [ jc_p [ ci ] ] ; } } for ( is = 0 ; is < 6 ; is ++ ) { ci = ir_i
[ is ] ; while ( ci < 1 ) { _rtXdot -> hrccq1fi0z [ is ] += rtP . Filtro_B *
rtB . bbdybg5bbo ; ci = 1 ; } } _rtXdot -> gxe5sdikfw = rtB . f1l5jsixgw ;
_rtXdot -> cc5042ocv2 = rtB . f1l5jsixgw ; _rtXdot -> husvwrmjnn = rtB .
cj3eokpnbs ; _rtXdot -> g01iry0rqn = rtB . fz1wrzhdaa ; _rtXdot -> iquu4mgvfb
= rtB . a4wt4ee5p1 ; _rtXdot -> lnhetubiv2 = rtB . kp3wrgz5sh ; } void
MdlProjection ( void ) { } void MdlZeroCrossings ( void ) { ZCV * _rtZCSV ;
_rtZCSV = ( ( ZCV * ) ssGetSolverZcSignalVector ( rtS ) ) ; _rtZCSV ->
dnmjo5cczs = rtB . ph3uie01yv ; _rtZCSV -> g3zy3hubrz = rtB . m1xi1b0n5m -
rtP . CompareToConstant_const ; _rtZCSV -> oyjjegcjyy = rtB . dfyucx0pjs -
rtP . Switch_Threshold ; _rtZCSV -> djgwmqbkch = rtB . dfyucx0pjs - rtP .
Switch1_Threshold ; _rtZCSV -> ocfvj3cewj = rtB . gx1uxu4kds - rtB .
drqnxkzet4 ; _rtZCSV -> f2wbwiipfc = rtB . co4tajx3jh ; _rtZCSV -> nheeorwalf
= rtB . izg2hxr1hm ; _rtZCSV -> k3coiq1vdz = rtB . ityop505e4 - rtB .
orkfi0mp2e ; _rtZCSV -> lywec2rsyi = rtB . cviwvtwqhc - rtB . fgrkiz4z0n ;
_rtZCSV -> oul53rl51h = rtB . l5nwaj4e3i ; _rtZCSV -> mmgl4pfrpz = rtB .
m3xclbw4n1 - rtB . axof5reva4 ; _rtZCSV -> dreagcpm3h = rtB . ikxyn0xytc -
rtB . jka1elz4sz ; _rtZCSV -> p1gxley4ws = rtB . d2vdhfxwnv - rtB .
fuwgkaabcp ; } void MdlTerminate ( void ) { rt_FREE ( rtDW . d0yoqq0s2u .
RSimInfoPtr ) ; rt_FREE ( rtDW . gtget4fvsy . RSimInfoPtr ) ;
rt_TDelayFreeBuf ( rtDW . j0ojopv3o4 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . odiqda1u1t . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . mx1qnjpwkr . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . c1abig5l5b . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . l3olmqutvm . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . laigziygdt . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . duyhxp3i2o . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . pfzlxqtttd . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . kpyzd0zppl . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . anw4lh3mkt . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . hth3y5boa4 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . jkfvz1vsm1 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . axitmt5w4i . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . bz4cstgndq . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . ifxwkbjtsf . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . oydq1getqe . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . nzhehebsh0 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . erisf50gfz . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . jszhk4b0c2 . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . emliqyd1hi . TUbufferPtrs [ 0 ] ) ;
rt_TDelayFreeBuf ( rtDW . j0z4zsdtwg . TUbufferPtrs [ 0 ] ) ; if (
rt_slioCatalogue ( ) != ( NULL ) ) { void * * slioCatalogueAddr =
rt_slioCatalogueAddr ( ) ; rtwSaveDatasetsToMatFile (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ,
rt_GetMatSigstreamLoggingFileName ( ) ) ; rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = NULL ; } } void
MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 37 ) ;
ssSetNumPeriodicContStates ( rtS , 5 ) ; ssSetNumY ( rtS , 0 ) ; ssSetNumU (
rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ; ssSetNumSampleTimes ( rtS ,
5 ) ; ssSetNumBlocks ( rtS , 251 ) ; ssSetNumBlockIO ( rtS , 130 ) ;
ssSetNumBlockParams ( rtS , 570 ) ; } void MdlInitializeSampleTimes ( void )
{ ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetSampleTime ( rtS , 1 , 0.0 ) ;
ssSetSampleTime ( rtS , 2 , 1.0E-9 ) ; ssSetSampleTime ( rtS , 3 , 8.0E-6 ) ;
ssSetSampleTime ( rtS , 4 , - 2.0 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ;
ssSetOffsetTime ( rtS , 1 , 1.0 ) ; ssSetOffsetTime ( rtS , 2 , 0.0 ) ;
ssSetOffsetTime ( rtS , 3 , 0.0 ) ; ssSetOffsetTime ( rtS , 4 , 0.0 ) ; }
void raccel_set_checksum ( ) { ssSetChecksumVal ( rtS , 0 , 3625068466U ) ;
ssSetChecksumVal ( rtS , 1 , 1078413989U ) ; ssSetChecksumVal ( rtS , 2 ,
1015600188U ) ; ssSetChecksumVal ( rtS , 3 , 1100843694U ) ; }
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
Multuplexacion_FDM_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive
( rtS , true ) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS ,
SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS , "Multuplexacion_FDM" ) ;
ssSetPath ( rtS , "Multuplexacion_FDM" ) ; ssSetTStart ( rtS , 0.0 ) ;
ssSetTFinal ( rtS , 0.06 ) ; { static RTWLogInfo rt_DataLoggingInfo ;
rt_DataLoggingInfo . loggingInterval = NULL ; ssSetRTWLogInfo ( rtS , &
rt_DataLoggingInfo ) ; } { { static int_T rt_LoggedStateWidths [ ] = { 10 , 1
, 1 , 1 , 10 , 1 , 1 , 6 , 1 , 1 , 1 , 1 , 1 , 1 } ; static int_T
rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 } ; static int_T rt_LoggedStateDimensions [ ] = { 10 , 1 , 1 , 1
, 10 , 1 , 1 , 6 , 1 , 1 , 1 , 1 , 1 , 1 } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 } ; static BuiltInDTypeId rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE
, SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE } ; static int_T rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static RTWPreprocessingFcnPtr
rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) } ; static const char_T *
rt_LoggedStateLabels [ ] = { "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" ,
"CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" ,
"CSTATE" , "CSTATE" , "CSTATE" } ; static const char_T *
rt_LoggedStateBlockNames [ ] = {
"Multuplexacion_FDM/Demux/Analog\nFilter Design2" ,
"Multuplexacion_FDM/medidor de error1/Integrator" ,
 "Multuplexacion_FDM/receptor\n/Reloj/Continuous-Time\nVCO/Modulo \nIntegrator/Modulo\nIntegrator"
, "Multuplexacion_FDM/receptor\n/Integrator" ,
"Multuplexacion_FDM/Demux/Analog\nFilter Design" ,
 "Multuplexacion_FDM/Mod1/Continuous-Time\nVCO/Modulo \nIntegrator/Modulo\nIntegrator"
,
 "Multuplexacion_FDM/Mod2/Continuous-Time\nVCO/Modulo \nIntegrator/Modulo\nIntegrator"
, "Multuplexacion_FDM/receptor\n/Filtro" ,
"Multuplexacion_FDM/receptor\n/Reloj/Integrator" ,
"Multuplexacion_FDM/receptor\n/Reloj/Integrator1" ,
 "Multuplexacion_FDM/receptor\n/SinPortadora\n/Continuous-Time\nVCO/Modulo \nIntegrator/Modulo\nIntegrator"
, "Multuplexacion_FDM/receptor\n/SinPortadora\n/Integrator" ,
 "Multuplexacion_FDM/receptor\n/SinPortadora\n/Continuous-Time\nVCO1/Modulo \nIntegrator/Modulo\nIntegrator"
, "Multuplexacion_FDM/receptor\n/SinPortadora\n/Integrator1" } ; static const
char_T * rt_LoggedStateNames [ ] = { "" , "" , "" , "" , "" , "" , "" , "" ,
"" , "" , "" , "" , "" , "" } ; static boolean_T rt_LoggedStateCrossMdlRef [
] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static
RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 14 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert } ; static void *
rt_LoggedStateSignalPtrs [ 14 ] ; rtliSetLogXSignalPtrs ( ssGetRTWLogInfo (
rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . ccwzf3tws3 [ 0 ] ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . cgdhzp3x0l ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtX . imuz3fx4o3 ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtX . cfrslgfjyu ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtX . ids2w4qbzk [ 0 ] ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) & rtX . nc3vmkovco ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) & rtX . psx2ki4ws3 ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) & rtX . hrccq1fi0z [ 0 ] ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) & rtX . gxe5sdikfw ;
rt_LoggedStateSignalPtrs [ 9 ] = ( void * ) & rtX . cc5042ocv2 ;
rt_LoggedStateSignalPtrs [ 10 ] = ( void * ) & rtX . husvwrmjnn ;
rt_LoggedStateSignalPtrs [ 11 ] = ( void * ) & rtX . g01iry0rqn ;
rt_LoggedStateSignalPtrs [ 12 ] = ( void * ) & rtX . iquu4mgvfb ;
rt_LoggedStateSignalPtrs [ 13 ] = ( void * ) & rtX . lnhetubiv2 ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) ,
"" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 4 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 )
; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ;
ssSetPeriodicContStateIndices ( rtS , rtPeriodicIndX ) ; ( void ) memset ( (
void * ) rtPeriodicIndX , 0 , 5 * sizeof ( int_T ) ) ;
ssSetPeriodicContStateRanges ( rtS , rtPeriodicRngX ) ; ( void ) memset ( (
void * ) rtPeriodicRngX , 0 , 10 * sizeof ( real_T ) ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 37 ] ;
static real_T absTol [ 37 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 } ;
static uint8_T absTolControl [ 37 ] = { 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U
, 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U ,
0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U } ;
static real_T contStateJacPerturbBoundMinVec [ 37 ] ; static real_T
contStateJacPerturbBoundMaxVec [ 37 ] ; static uint8_T zcAttributes [ 23 ] =
{ ( ZC_EVENT_ALL ) , ( 0xc0 | ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
0xc0 | ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( 0xc0 |
ZC_EVENT_ALL_DN ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) ,
( ZC_EVENT_ALL ) , ( 0x80 | ZC_EVENT_ALL ) , ( 0xc0 | ZC_EVENT_ALL_UP ) , (
0xc0 | ZC_EVENT_ALL ) , ( 0xc0 | ZC_EVENT_ALL ) , ( 0xc0 | ZC_EVENT_ALL_DN )
, ( 0xc0 | ZC_EVENT_ALL_UP ) , ( 0xc0 | ZC_EVENT_ALL_UP ) , ( 0xc0 |
ZC_EVENT_ALL_UP ) } ; static ssNonContDerivSigInfo nonContDerivSigInfo [ 8 ]
= { { 1 * sizeof ( real_T ) , ( char * ) ( & rtB . awasz3p2hm ) , ( NULL ) }
, { 1 * sizeof ( real_T ) , ( char * ) ( & rtB . f1l5jsixgw ) , ( NULL ) } ,
{ 1 * sizeof ( real_T ) , ( char * ) ( & rtB . kmsebnmjbu ) , ( NULL ) } , {
1 * sizeof ( real_T ) , ( char * ) ( & rtB . eqpfzakwij ) , ( NULL ) } , { 1
* sizeof ( real_T ) , ( char * ) ( & rtB . ckmrjxysf3 ) , ( NULL ) } , { 1 *
sizeof ( real_T ) , ( char * ) ( & rtB . omyffgmxzc ) , ( NULL ) } , { 1 *
sizeof ( real_T ) , ( char * ) ( & rtB . l2slq2pxao ) , ( NULL ) } , { 1 *
sizeof ( real_T ) , ( char * ) ( & rtB . lufwcivalw ) , ( NULL ) } } ; { int
i ; for ( i = 0 ; i < 37 ; ++ i ) { contStateJacPerturbBoundMinVec [ i ] = 0
; contStateJacPerturbBoundMaxVec [ i ] = rtGetInf ( ) ; } } ssSetSolverRelTol
( rtS , 0.001 ) ; ssSetStepSize ( rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0
) ; ssSetMaxNumMinSteps ( rtS , - 1 ) ; ssSetMinStepViolatedError ( rtS , 0 )
; ssSetMaxStepSize ( rtS , 1.0E-9 ) ; ssSetSolverMaxOrder ( rtS , - 1 ) ;
ssSetSolverRefineFactor ( rtS , 1 ) ; ssSetOutputTimes ( rtS , ( NULL ) ) ;
ssSetNumOutputTimes ( rtS , 0 ) ; ssSetOutputTimesOnly ( rtS , 0 ) ;
ssSetOutputTimesIndex ( rtS , 0 ) ; ssSetZCCacheNeedsReset ( rtS , 1 ) ;
ssSetDerivCacheNeedsReset ( rtS , 0 ) ; ssSetNumNonContDerivSigInfos ( rtS ,
8 ) ; ssSetNonContDerivSigInfos ( rtS , nonContDerivSigInfo ) ;
ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS ,
"VariableStepAuto" ) ; ssSetVariableStepSolver ( rtS , 1 ) ;
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
zc ) ; } { rtPrevZCX . mqbxqqegfa = UNINITIALIZED_ZCSIG ; rtPrevZCX .
mj4uwtxvw4 = UNINITIALIZED_ZCSIG ; rtPrevZCX . kci0nfmn3i =
UNINITIALIZED_ZCSIG ; rtPrevZCX . p1xn3fs3d3 = UNINITIALIZED_ZCSIG ;
rtPrevZCX . cvp0g55jmi = ZERO_ZCSIG ; rtPrevZCX . coh1zb2qmc =
UNINITIALIZED_ZCSIG ; rtPrevZCX . otkgxfzkeh = UNINITIALIZED_ZCSIG ;
rtPrevZCX . ctjn34sghg = UNINITIALIZED_ZCSIG ; rtPrevZCX . jiixgvrfhd .
aw5lle212o = POS_ZCSIG ; rtPrevZCX . dyorcglstw . aw5lle212o = POS_ZCSIG ;
rtPrevZCX . mivhx1fvuuy . aw5lle212o = POS_ZCSIG ; } ssSetChecksumVal ( rtS ,
0 , 3625068466U ) ; ssSetChecksumVal ( rtS , 1 , 1078413989U ) ;
ssSetChecksumVal ( rtS , 2 , 1015600188U ) ; ssSetChecksumVal ( rtS , 3 ,
1100843694U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 15 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = ( sysRanDType * ) &
rtDW . hbnvwgns2u ; systemRan [ 2 ] = ( sysRanDType * ) & rtDW . mivhx1fvuuy
. fmzbbk3ukv ; systemRan [ 3 ] = ( sysRanDType * ) & rtDW . dnioykk3w1k .
k2unbokluf ; systemRan [ 4 ] = ( sysRanDType * ) & rtDW . d5zlt11l1pl .
faxymqm3qy ; systemRan [ 5 ] = ( sysRanDType * ) & rtDW . dyorcglstw .
fmzbbk3ukv ; systemRan [ 6 ] = ( sysRanDType * ) & rtDW . fkhi333c1w .
k2unbokluf ; systemRan [ 7 ] = ( sysRanDType * ) & rtDW . gggqmave4q .
faxymqm3qy ; systemRan [ 8 ] = ( sysRanDType * ) & rtDW . loneq0nrmu ;
systemRan [ 9 ] = ( sysRanDType * ) & rtDW . moelhnb1d2 ; systemRan [ 10 ] =
( sysRanDType * ) & rtDW . cjvs3g4hfh ; systemRan [ 11 ] = ( sysRanDType * )
& rtDW . jiixgvrfhd . fmzbbk3ukv ; systemRan [ 12 ] = ( sysRanDType * ) &
rtDW . mpycb0evfp . k2unbokluf ; systemRan [ 13 ] = ( sysRanDType * ) & rtDW
. abmuy5rnsq . faxymqm3qy ; systemRan [ 14 ] = ( sysRanDType * ) & rtDW .
lekdfle5yl ; rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) , &
ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo (
rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS )
, ssGetTPtr ( rtS ) ) ; } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 5 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID5 ( tid ) ; }
