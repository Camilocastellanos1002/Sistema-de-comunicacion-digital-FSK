#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "FSK_2_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#else
#include "builtin_typeid_types.h"
#include "FSK_2.h"
#include "FSK_2_capi.h"
#include "FSK_2_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"FSK_2/Informacion" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 1 , 0
, TARGET_STRING ( "FSK_2/Informacion1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 0 } , { 2 , 0 , TARGET_STRING ( "FSK_2/Demux/Analog Filter Design" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 3 , 0 , TARGET_STRING (
"FSK_2/Demux/Analog Filter Design2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 1 } , { 4 , 0 , TARGET_STRING ( "FSK_2/canal /Gain" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 5 , 0 , TARGET_STRING ( "FSK_2/canal /Add" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 6 , 0 , TARGET_STRING (
"FSK_2/Transmisor1/Continuous-Time VCO/Sum" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 7 , 0 , TARGET_STRING (
"FSK_2/Transmisor2/Continuous-Time VCO/Sum" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 8 , 0 , TARGET_STRING (
"FSK_2/canal /Gaussian Noise Generator/Sum" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 2 } , { 9 , 0 , TARGET_STRING (
"FSK_2/canal /Gaussian Noise Generator/Buffer" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 2 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ;
static const rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 10 ,
TARGET_STRING ( "FSK_2/Informacion" ) , TARGET_STRING ( "Data0" ) , 0 , 1 , 0
} , { 11 , TARGET_STRING ( "FSK_2/Informacion1" ) , TARGET_STRING ( "Data0" )
, 0 , 1 , 0 } , { 12 , TARGET_STRING ( "FSK_2/Demux/Analog Filter Design" ) ,
TARGET_STRING ( "A" ) , 0 , 2 , 0 } , { 13 , TARGET_STRING (
"FSK_2/Demux/Analog Filter Design" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0 } ,
{ 14 , TARGET_STRING ( "FSK_2/Demux/Analog Filter Design" ) , TARGET_STRING (
"C" ) , 0 , 0 , 0 } , { 15 , TARGET_STRING (
"FSK_2/Demux/Analog Filter Design" ) , TARGET_STRING ( "InitialCondition" ) ,
0 , 0 , 0 } , { 16 , TARGET_STRING ( "FSK_2/Demux/Analog Filter Design2" ) ,
TARGET_STRING ( "A" ) , 0 , 2 , 0 } , { 17 , TARGET_STRING (
"FSK_2/Demux/Analog Filter Design2" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0 } ,
{ 18 , TARGET_STRING ( "FSK_2/Demux/Analog Filter Design2" ) , TARGET_STRING
( "C" ) , 0 , 0 , 0 } , { 19 , TARGET_STRING (
"FSK_2/Demux/Analog Filter Design2" ) , TARGET_STRING ( "InitialCondition" )
, 0 , 0 , 0 } , { 20 , TARGET_STRING ( "FSK_2/Mux/Sine Wave" ) ,
TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 21 , TARGET_STRING (
"FSK_2/Mux/Sine Wave" ) , TARGET_STRING ( "Bias" ) , 0 , 0 , 0 } , { 22 ,
TARGET_STRING ( "FSK_2/Mux/Sine Wave" ) , TARGET_STRING ( "Phase" ) , 0 , 0 ,
0 } , { 23 , TARGET_STRING ( "FSK_2/Transmisor1/Transport Delay" ) ,
TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0 } , { 24 , TARGET_STRING (
"FSK_2/Transmisor1/Transport Delay" ) , TARGET_STRING ( "InitialOutput" ) , 0
, 0 , 0 } , { 25 , TARGET_STRING ( "FSK_2/Transmisor2/Transport Delay" ) ,
TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0 } , { 26 , TARGET_STRING (
"FSK_2/Transmisor2/Transport Delay" ) , TARGET_STRING ( "InitialOutput" ) , 0
, 0 , 0 } , { 27 , TARGET_STRING ( "FSK_2/canal /Gaussian Noise Generator" )
, TARGET_STRING ( "m" ) , 0 , 0 , 0 } , { 28 , TARGET_STRING (
"FSK_2/canal /Gaussian Noise Generator" ) , TARGET_STRING ( "d" ) , 0 , 0 , 0
} , { 29 , TARGET_STRING ( "FSK_2/canal /Gaussian Noise Generator" ) ,
TARGET_STRING ( "s" ) , 0 , 0 , 0 } , { 30 , TARGET_STRING (
"FSK_2/canal /Transport Delay" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0
, 0 } , { 31 , TARGET_STRING (
"FSK_2/canal /Gaussian Noise Generator/Random Number" ) , TARGET_STRING (
"Mean" ) , 0 , 0 , 0 } , { 32 , TARGET_STRING (
"FSK_2/canal /Gaussian Noise Generator/Random Number" ) , TARGET_STRING (
"StdDev" ) , 0 , 0 , 0 } , { 33 , TARGET_STRING (
"FSK_2/canal /Gaussian Noise Generator/Buffer" ) , TARGET_STRING ( "ic" ) , 0
, 0 , 0 } , { 34 , TARGET_STRING (
"FSK_2/Transmisor1/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 35 , TARGET_STRING
(
"FSK_2/Transmisor1/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 36 ,
TARGET_STRING (
"FSK_2/Transmisor1/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 37 ,
TARGET_STRING (
"FSK_2/Transmisor2/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 38 , TARGET_STRING
(
"FSK_2/Transmisor2/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 39 ,
TARGET_STRING (
"FSK_2/Transmisor2/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 0 , ( NULL )
, ( NULL ) , 0 , 0 , 0 } } ; static const rtwCAPI_ModelParameters
rtModelParameters [ ] = { { 40 , TARGET_STRING ( "Atenuacion_canal" ) , 0 , 0
, 0 } , { 41 , TARGET_STRING ( "Frec2" ) , 0 , 0 , 0 } , { 42 , TARGET_STRING
( "Frec4" ) , 0 , 0 , 0 } , { 43 , TARGET_STRING ( "Rb" ) , 0 , 0 , 0 } , {
44 , TARGET_STRING ( "Retraso_canal" ) , 0 , 0 , 0 } , { 45 , TARGET_STRING (
"frec" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . bdmiwmnwdi , & rtB . ixhdtyqkuo ,
& rtB . a2ej4vwwfz , & rtB . cydck3mxyr , & rtB . o0un153nbh , & rtB .
clkvycwj4m , & rtB . dzdmp2qvuc , & rtB . a1nwn30zom , & rtB . pxelcov220 , &
rtB . br52h0oi5h , & rtP . Informacion_Data0 [ 0 ] , & rtP .
Informacion1_Data0 [ 0 ] , & rtP . AnalogFilterDesign_A [ 0 ] , & rtP .
AnalogFilterDesign_B , & rtP . AnalogFilterDesign_C , & rtP .
AnalogFilterDesign_InitialCondition , & rtP . AnalogFilterDesign2_A [ 0 ] , &
rtP . AnalogFilterDesign2_B , & rtP . AnalogFilterDesign2_C , & rtP .
AnalogFilterDesign2_InitialCondition , & rtP . SineWave_Amp , & rtP .
SineWave_Bias , & rtP . SineWave_Phase , & rtP . TransportDelay_Delay , & rtP
. TransportDelay_InitOutput , & rtP . TransportDelay_Delay_mpjovd0fow , & rtP
. TransportDelay_InitOutput_erb5xkljw0 , & rtP . GaussianNoiseGenerator_m , &
rtP . GaussianNoiseGenerator_d , & rtP . GaussianNoiseGenerator_s , & rtP .
TransportDelay_InitOutput_npzkuu2dfa , & rtP . RandomNumber_Mean , & rtP .
RandomNumber_StdDev , & rtP . Buffer_ic , & rtP . ModuloIntegrator_IC , & rtP
. ModuloIntegrator_WrappedStateUpperValue , & rtP .
ModuloIntegrator_WrappedStateLowerValue , & rtP .
ModuloIntegrator_IC_p52dz1dzx0 , & rtP .
ModuloIntegrator_WrappedStateUpperValue_kbmmwvx1uc , & rtP .
ModuloIntegrator_WrappedStateLowerValue_mg14ul40s3 , & rtP . Atenuacion_canal
, & rtP . Frec2 , & rtP . Frec4 , & rtP . Rb , & rtP . Retraso_canal , & rtP
. frec , } ; static int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , SS_DOUBLE , 0 , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } } ; static const uint_T rtDimensionArray [ ] = {
1 , 1 , 182 , 1 , 19 , 1 } ; static const real_T rtcapiStoredFloats [ ] = {
8.0E-6 , 0.0 , 1.0E-9 } ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { {
( NULL ) , ( NULL ) , rtwCAPI_FIX_RESERVED , 0 , 0 , 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 3 ,
0 } , { ( const void * ) & rtcapiStoredFloats [ 1 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , 0 , 0 } , { ( const void * ) & rtcapiStoredFloats
[ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 2 , 0 } } ; static
rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 10 , ( NULL )
, 0 , ( NULL ) , 0 } , { rtBlockParameters , 30 , rtModelParameters , 6 } , {
( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap , rtFixPtMap , rtElementMap
, rtSampleTimeMap , rtDimensionArray } , "float" , { 4193358515U , 617856143U
, 3689207024U , 1471515770U } , ( NULL ) , 0 , 0 } ; const
rtwCAPI_ModelMappingStaticInfo * FSK_2_GetCAPIStaticMap ( void ) { return &
mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void FSK_2_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void FSK_2_host_InitializeDataMapInfo ( FSK_2_host_DataMapInfo_T * dataMap ,
const char * path ) { rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ;
rtwCAPI_SetStaticMap ( dataMap -> mmi , & mmiStatic ) ;
rtwCAPI_SetDataAddressMap ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , NULL ) ; rtwCAPI_SetPath (
dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
