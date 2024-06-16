#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "FSK_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#ifndef SS_INT64
#define SS_INT64  15
#endif
#ifndef SS_UINT64
#define SS_UINT64  16
#endif
#else
#include "builtin_typeid_types.h"
#include "FSK.h"
#include "FSK_capi.h"
#include "FSK_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"FSK/Informacion" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 1 , 0 ,
TARGET_STRING ( "FSK/Filtro" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } ,
{ 2 , 0 , TARGET_STRING ( "FSK/canal /Gain" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 3 , 0 , TARGET_STRING ( "FSK/canal /Add" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 4 , 1 , TARGET_STRING (
"FSK/medidor de error/Muestreo y Retencion " ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 2 } , { 5 , 0 , TARGET_STRING (
"FSK/medidor de error/Data Type Conversion" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 6 , 0 , TARGET_STRING (
"FSK/medidor de error/Pulse Generator" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 3 } , { 7 , 0 , TARGET_STRING ( "FSK/medidor de error/Product" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 8 , 10 , TARGET_STRING (
"FSK/receptor /Sample and Hold" ) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 2
} , { 9 , 0 , TARGET_STRING ( "FSK/receptor /Integrator" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 10 , 0 , TARGET_STRING ( "FSK/receptor /Sign3"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 11 , 0 , TARGET_STRING (
"FSK/receptor /Filtro" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 12
, 0 , TARGET_STRING ( "FSK/Transmisor/Continuous-Time VCO/Sum" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 13 , 0 , TARGET_STRING (
"FSK/canal /Gaussian Noise Generator/Sum" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 5 } , { 14 , 0 , TARGET_STRING (
"FSK/canal /Gaussian Noise Generator/Buffer" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 5 } , { 15 , 1 , TARGET_STRING (
"FSK/medidor de error/Muestreo y Retencion /In" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 2 } , { 16 , 0 , TARGET_STRING (
"FSK/receptor /Gaussian Noise Generator/Sum" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 5 } , { 17 , 0 , TARGET_STRING (
"FSK/receptor /Gaussian Noise Generator/Buffer" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 5 } , { 18 , 8 , TARGET_STRING (
"FSK/receptor /Reloj/Sample and Hold" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 2 } , { 19 , 9 , TARGET_STRING ( "FSK/receptor /Reloj/Sample and Hold1" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 20 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Abs" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , {
21 , 0 , TARGET_STRING ( "FSK/receptor /Reloj/Integrator" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 22 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Integrator1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
1 } , { 23 , 0 , TARGET_STRING ( "FSK/receptor /Reloj/Sum" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 24 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Switch2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 }
, { 25 , 0 , TARGET_STRING ( "FSK/receptor /Reloj/Transport Delay" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 26 , 10 , TARGET_STRING (
"FSK/receptor /Sample and Hold/In" ) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 ,
2 } , { 27 , 0 , TARGET_STRING ( "FSK/receptor /SinPortadora /Product3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 28 , 0 , TARGET_STRING (
"FSK/receptor /SinPortadora /Product6" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 1 } , { 29 , 0 , TARGET_STRING ( "FSK/receptor /SinPortadora /Product7" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 30 , 0 , TARGET_STRING (
"FSK/receptor /SinPortadora /Add1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
1 } , { 31 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Logical Operator" ) , TARGET_STRING ( "" ) , 0 ,
1 , 0 , 0 , 1 } , { 32 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Product4" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 4 } , { 33 , 0 , TARGET_STRING ( "FSK/receptor /Sincronismo /Add" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 34 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Switch2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 1 } , { 35 , 0 , TARGET_STRING ( "FSK/receptor /Sincronismo /Switch3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 36 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay1" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 37 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay10" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 38 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay11" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 39 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay2" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 40 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay3" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 41 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay4" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 42 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay5" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 43 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay6" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 44 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay7" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 45 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay8" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 46 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay9" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 47 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Continuous-Time VCO/Inherit Shape" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 48 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Continuous-Time VCO/Sum" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 4 } , { 49 , 8 , TARGET_STRING (
"FSK/receptor /Reloj/Sample and Hold/In" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 2 } , { 50 , 9 , TARGET_STRING (
"FSK/receptor /Reloj/Sample and Hold1/In" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 2 } , { 51 , 0 , TARGET_STRING (
"FSK/receptor /SinPortadora /Continuous-Time VCO/Inherit Shape" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 52 , 0 , TARGET_STRING (
"FSK/receptor /SinPortadora /Continuous-Time VCO/Sum" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 53 , 0 , TARGET_STRING (
"FSK/receptor /SinPortadora /Continuous-Time VCO1/Inherit Shape" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 54 , 0 , TARGET_STRING (
"FSK/receptor /SinPortadora /Continuous-Time VCO1/Sum" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 55 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Clock" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 56 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/T_monostable" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 4 } , { 57 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Data Type Conversion2" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 58 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Logical Operator1" ) , TARGET_STRING (
"" ) , 0 , 1 , 0 , 0 , 4 } , { 59 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Relational Operator" ) , TARGET_STRING
( "" ) , 0 , 1 , 0 , 0 , 4 } , { 60 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Sum" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 61 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Clock" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 62 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/T_monostable" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 4 } , { 63 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Data Type Conversion2" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 64 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Logical Operator1" ) , TARGET_STRING (
"" ) , 0 , 1 , 0 , 0 , 4 } , { 65 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Relational Operator" ) , TARGET_STRING
( "" ) , 0 , 1 , 0 , 0 , 4 } , { 66 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Sum" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 67 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Monostable1/Model/Clock" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 1 } , { 68 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Monostable1/Model/T_monostable" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 4 } , { 69 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Monostable1/Model/Logical Operator1" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 70 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Monostable1/Model/Relational Operator" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 71 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Monostable1/Model/Sum" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 72 , 3 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/NEGATIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 73 , 4 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/POSITIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 74 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Multiport Switch"
) , TARGET_STRING ( "" ) , 0 , 0 , 1 , 0 , 6 } , { 75 , 6 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/NEGATIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 76 , 7 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/POSITIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 77 , 0 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Multiport Switch"
) , TARGET_STRING ( "" ) , 0 , 0 , 1 , 0 , 6 } , { 78 , 12 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/NEGATIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 79 , 13 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/POSITIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 80 , 0 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Multiport Switch"
) , TARGET_STRING ( "" ) , 0 , 0 , 1 , 0 , 6 } , { 81 , 2 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 82 , 0 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Clock"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 83 , 0 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Sum"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 84 , 3 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/NEGATIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 85 , 4 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/POSITIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 86 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Sample and Hold/Model/IC=ic" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 87 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Sample and Hold/Model/Switch" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 88 , 5 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 89 , 0 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Clock"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 90 , 0 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Sum"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 91 , 6 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/NEGATIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 92 , 7 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/POSITIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 93 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Sample and Hold/Model/IC=ic" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 94 , 0 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Sample and Hold/Model/Switch" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 95 , 11 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 96 , 0 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Clock"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 97 , 0 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Sum"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 98 , 12 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/NEGATIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 99 , 13 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/POSITIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 100 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Monostable1/Model/Sample and Hold/Model/IC=ic" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 101 , 0 , TARGET_STRING (
"FSK/receptor /Sincronismo /Monostable1/Model/Sample and Hold/Model/Switch" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 102 , 2 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/In1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 103 , 5 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/In1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 104 , 11 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/In1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 0 , 0 , ( NULL ) , ( NULL
) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 105 , TARGET_STRING ( "FSK/Informacion" ) ,
TARGET_STRING ( "Data0" ) , 0 , 2 , 0 } , { 106 , TARGET_STRING (
"FSK/Filtro" ) , TARGET_STRING ( "A" ) , 0 , 3 , 0 } , { 107 , TARGET_STRING
( "FSK/Filtro" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0 } , { 108 ,
TARGET_STRING ( "FSK/Filtro" ) , TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 109
, TARGET_STRING ( "FSK/Filtro" ) , TARGET_STRING ( "InitialCondition" ) , 0 ,
0 , 0 } , { 110 , TARGET_STRING ( "FSK/Transmisor/Transport Delay" ) ,
TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0 } , { 111 , TARGET_STRING (
"FSK/Transmisor/Transport Delay" ) , TARGET_STRING ( "InitialOutput" ) , 0 ,
0 , 0 } , { 112 , TARGET_STRING ( "FSK/canal /Gaussian Noise Generator" ) ,
TARGET_STRING ( "m" ) , 0 , 0 , 0 } , { 113 , TARGET_STRING (
"FSK/canal /Gaussian Noise Generator" ) , TARGET_STRING ( "d" ) , 0 , 0 , 0 }
, { 114 , TARGET_STRING ( "FSK/canal /Gaussian Noise Generator" ) ,
TARGET_STRING ( "s" ) , 0 , 0 , 0 } , { 115 , TARGET_STRING (
"FSK/canal /Transport Delay" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 ,
0 } , { 116 , TARGET_STRING ( "FSK/medidor de error/Pulse Generator" ) ,
TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 117 , TARGET_STRING (
"FSK/medidor de error/Pulse Generator" ) , TARGET_STRING ( "PulseWidth" ) , 0
, 0 , 0 } , { 118 , TARGET_STRING ( "FSK/medidor de error/Pulse Generator" )
, TARGET_STRING ( "PhaseDelay" ) , 0 , 0 , 0 } , { 119 , TARGET_STRING (
"FSK/medidor de error/Integrator" ) , TARGET_STRING ( "InitialCondition" ) ,
0 , 0 , 0 } , { 120 , TARGET_STRING ( "FSK/medidor de error/Transport Delay"
) , TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0 } , { 121 , TARGET_STRING (
"FSK/medidor de error/Transport Delay" ) , TARGET_STRING ( "InitialOutput" )
, 0 , 0 , 0 } , { 122 , TARGET_STRING ( "FSK/receptor /Compare To Constant" )
, TARGET_STRING ( "const" ) , 0 , 0 , 0 } , { 123 , TARGET_STRING (
"FSK/receptor /Gaussian Noise Generator" ) , TARGET_STRING ( "m" ) , 0 , 0 ,
0 } , { 124 , TARGET_STRING ( "FSK/receptor /Gaussian Noise Generator" ) ,
TARGET_STRING ( "s" ) , 0 , 0 , 0 } , { 125 , TARGET_STRING (
"FSK/receptor /Integrator" ) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 ,
0 } , { 126 , TARGET_STRING ( "FSK/receptor /Filtro" ) , TARGET_STRING ( "A"
) , 0 , 4 , 0 } , { 127 , TARGET_STRING ( "FSK/receptor /Filtro" ) ,
TARGET_STRING ( "B" ) , 0 , 0 , 0 } , { 128 , TARGET_STRING (
"FSK/receptor /Filtro" ) , TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 129 ,
TARGET_STRING ( "FSK/receptor /Filtro" ) , TARGET_STRING ( "InitialCondition"
) , 0 , 0 , 0 } , { 130 , TARGET_STRING (
"FSK/canal /Gaussian Noise Generator/Random Number" ) , TARGET_STRING (
"Mean" ) , 0 , 0 , 0 } , { 131 , TARGET_STRING (
"FSK/canal /Gaussian Noise Generator/Random Number" ) , TARGET_STRING (
"StdDev" ) , 0 , 0 , 0 } , { 132 , TARGET_STRING (
"FSK/canal /Gaussian Noise Generator/Buffer" ) , TARGET_STRING ( "ic" ) , 0 ,
0 , 0 } , { 133 , TARGET_STRING (
"FSK/medidor de error/Muestreo y Retencion / " ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 134 , TARGET_STRING (
"FSK/receptor /Filtro /Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 }
, { 135 , TARGET_STRING ( "FSK/receptor /Filtro /Transport Delay" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 136 , TARGET_STRING (
"FSK/receptor /Filtro /Transport Delay1" ) , TARGET_STRING ( "InitialOutput"
) , 0 , 0 , 0 } , { 137 , TARGET_STRING (
"FSK/receptor /Gaussian Noise Generator/Matrix Gain" ) , TARGET_STRING (
"Gain" ) , 0 , 0 , 0 } , { 138 , TARGET_STRING (
"FSK/receptor /Gaussian Noise Generator/Random Number" ) , TARGET_STRING (
"Mean" ) , 0 , 0 , 0 } , { 139 , TARGET_STRING (
"FSK/receptor /Gaussian Noise Generator/Random Number" ) , TARGET_STRING (
"StdDev" ) , 0 , 0 , 0 } , { 140 , TARGET_STRING (
"FSK/receptor /Gaussian Noise Generator/Buffer" ) , TARGET_STRING ( "ic" ) ,
0 , 0 , 0 } , { 141 , TARGET_STRING ( "FSK/receptor /Reloj/Monostable" ) ,
TARGET_STRING ( "ic" ) , 1 , 0 , 0 } , { 142 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1" ) , TARGET_STRING ( "ic" ) , 1 , 0 , 0 } ,
{ 143 , TARGET_STRING ( "FSK/receptor /Reloj/Constant5" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 144 , TARGET_STRING (
"FSK/receptor /Reloj/Constant6" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } ,
{ 145 , TARGET_STRING ( "FSK/receptor /Reloj/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 146 , TARGET_STRING (
"FSK/receptor /Reloj/Integrator1" ) , TARGET_STRING ( "InitialCondition" ) ,
0 , 0 , 0 } , { 147 , TARGET_STRING ( "FSK/receptor /Reloj/Switch2" ) ,
TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 148 , TARGET_STRING (
"FSK/receptor /Reloj/Transport Delay" ) , TARGET_STRING ( "InitialOutput" ) ,
0 , 0 , 0 } , { 149 , TARGET_STRING ( "FSK/receptor /Sample and Hold/ " ) ,
TARGET_STRING ( "InitialOutput" ) , 1 , 0 , 0 } , { 150 , TARGET_STRING (
"FSK/receptor /SinPortadora /Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 151 , TARGET_STRING (
"FSK/receptor /SinPortadora /Integrator1" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 152 , TARGET_STRING (
"FSK/receptor /SinPortadora /Transport Delay" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 153 , TARGET_STRING (
"FSK/receptor /SinPortadora /Transport Delay1" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 154 , TARGET_STRING (
"FSK/receptor /Sincronismo /Monostable1" ) , TARGET_STRING ( "ic" ) , 1 , 0 ,
0 } , { 155 , TARGET_STRING ( "FSK/receptor /Sincronismo /Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 156 , TARGET_STRING (
"FSK/receptor /Sincronismo /Constant10" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 157 , TARGET_STRING ( "FSK/receptor /Sincronismo /Constant11" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 158 , TARGET_STRING (
"FSK/receptor /Sincronismo /Constant12" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 159 , TARGET_STRING ( "FSK/receptor /Sincronismo /Constant13" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 160 , TARGET_STRING (
"FSK/receptor /Sincronismo /Constant14" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 161 , TARGET_STRING ( "FSK/receptor /Sincronismo /Constant15" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 162 , TARGET_STRING (
"FSK/receptor /Sincronismo /Constant16" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 163 , TARGET_STRING ( "FSK/receptor /Sincronismo /Constant17" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 164 , TARGET_STRING (
"FSK/receptor /Sincronismo /Constant18" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 165 , TARGET_STRING ( "FSK/receptor /Sincronismo /Constant19" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 166 , TARGET_STRING (
"FSK/receptor /Sincronismo /Constant2" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 167 , TARGET_STRING ( "FSK/receptor /Sincronismo /Constant20" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 168 , TARGET_STRING (
"FSK/receptor /Sincronismo /Constant3" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 169 , TARGET_STRING ( "FSK/receptor /Sincronismo /Constant4" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 170 , TARGET_STRING (
"FSK/receptor /Sincronismo /Constant5" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 171 , TARGET_STRING ( "FSK/receptor /Sincronismo /Constant6" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 172 , TARGET_STRING (
"FSK/receptor /Sincronismo /Constant7" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 173 , TARGET_STRING ( "FSK/receptor /Sincronismo /Constant8" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 174 , TARGET_STRING (
"FSK/receptor /Sincronismo /Constant9" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 175 , TARGET_STRING ( "FSK/receptor /Sincronismo /Switch" ) ,
TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 176 , TARGET_STRING (
"FSK/receptor /Sincronismo /Switch1" ) , TARGET_STRING ( "Threshold" ) , 0 ,
0 , 0 } , { 177 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay1" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 178 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay10" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 179 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay11" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 180 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay12" ) , TARGET_STRING (
"DelayTime" ) , 0 , 0 , 0 } , { 181 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay12" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 182 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay13" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 183 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay2" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 184 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay3" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 185 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay4" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 186 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay5" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 187 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay6" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 188 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay7" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 189 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay8" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 190 , TARGET_STRING (
"FSK/receptor /Sincronismo /Transport Delay9" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 191 , TARGET_STRING (
"FSK/Transmisor/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 192 , TARGET_STRING (
"FSK/Transmisor/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator" ) ,
TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 193 ,
TARGET_STRING (
"FSK/Transmisor/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator" ) ,
TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 194 ,
TARGET_STRING ( "FSK/receptor /Reloj/Sample and Hold/ " ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 195 , TARGET_STRING (
"FSK/receptor /Reloj/Sample and Hold1/ " ) , TARGET_STRING ( "InitialOutput"
) , 0 , 0 , 0 } , { 196 , TARGET_STRING (
"FSK/receptor /Reloj/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 197 ,
TARGET_STRING (
"FSK/receptor /Reloj/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 198 ,
TARGET_STRING (
"FSK/receptor /Reloj/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 199 ,
TARGET_STRING ( "FSK/receptor /Reloj/Monostable/Model/Sample and Hold" ) ,
TARGET_STRING ( "ic" ) , 0 , 0 , 0 } , { 200 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Memory" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 201 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Sample and Hold" ) , TARGET_STRING (
"ic" ) , 0 , 0 , 0 } , { 202 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Memory" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 203 , TARGET_STRING (
 "FSK/receptor /SinPortadora /Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 204 ,
TARGET_STRING (
 "FSK/receptor /SinPortadora /Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 205 ,
TARGET_STRING (
 "FSK/receptor /SinPortadora /Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 206 ,
TARGET_STRING (
 "FSK/receptor /SinPortadora /Continuous-Time VCO1/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 207 ,
TARGET_STRING (
 "FSK/receptor /SinPortadora /Continuous-Time VCO1/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 208 ,
TARGET_STRING (
 "FSK/receptor /SinPortadora /Continuous-Time VCO1/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 209 ,
TARGET_STRING (
"FSK/receptor /Sincronismo /Monostable1/Model/Sample and Hold" ) ,
TARGET_STRING ( "ic" ) , 0 , 0 , 0 } , { 210 , TARGET_STRING (
"FSK/receptor /Sincronismo /Monostable1/Model/Memory" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 211 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 212 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/either edge" )
, TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 213 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/neg. edge" ) ,
TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 214 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/pos. edge" ) ,
TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 215 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Constant1" )
, TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 216 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/either edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 217 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/neg. edge" )
, TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 218 , TARGET_STRING (
"FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/pos. edge" )
, TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 219 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Constant1"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 220 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/either edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 221 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/neg. edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 222 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/pos. edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 223 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 224 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 225 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 226 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/Out1"
) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 227 , TARGET_STRING (
 "FSK/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/Out1"
) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 228 , TARGET_STRING (
 "FSK/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/Out1"
) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL
) , 0 , 0 , 0 } } ; static const rtwCAPI_ModelParameters rtModelParameters [
] = { { 229 , TARGET_STRING ( "Atenuacion_canal" ) , 0 , 0 , 0 } , { 230 ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 231 , TARGET_STRING ( "Datos" ) , 0 ,
0 , 0 } , { 232 , TARGET_STRING ( "Frec1" ) , 0 , 0 , 0 } , { 233 ,
TARGET_STRING ( "Frec2" ) , 0 , 0 , 0 } , { 234 , TARGET_STRING ( "R1" ) , 0
, 0 , 0 } , { 235 , TARGET_STRING ( "R2" ) , 0 , 0 , 0 } , { 236 ,
TARGET_STRING ( "Rb" ) , 0 , 0 , 0 } , { 237 , TARGET_STRING (
"Retraso_canal" ) , 0 , 0 , 0 } , { 238 , TARGET_STRING ( "kv" ) , 0 , 0 , 0
} , { 239 , TARGET_STRING ( "kv2" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , 0 , 0 ,
0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . ghegbffnb0 , & rtB . mr1s0bxcpp ,
& rtB . ibhjdwhj0b , & rtB . brw1yh1ujs , & rtB . jmfd3dtamo , & rtB .
geskkhqdb3 , & rtB . gfobd5zpxv , & rtB . hao2kgiuqu , & rtB . m4lv3kzihg , &
rtB . f5hdbpawyv , & rtB . e15ao1bk3m , & rtB . hs1qpln3nc , & rtB .
echlwz23fd , & rtB . ong5vjnb0y , & rtB . iyoofertyx , & rtB . jmfd3dtamo , &
rtB . cqkmv0ulyy , & rtB . fcjlyowfli , & rtB . lzdd3z4ueb , & rtB .
fmyjxkxyji , & rtB . inulkftw3y , & rtB . ooknyqiljy , & rtB . iuiswtbqno , &
rtB . ctnzwjmcme , & rtB . bui2nj5eby , & rtB . i1k4ywizrv , & rtB .
m4lv3kzihg , & rtB . ftsmahysaw , & rtB . furzsgxei5 , & rtB . jiqtvtg4mt , &
rtB . fwzg1qmdog , & rtB . cbutxn4e51 , & rtB . kwwqn5rlhs , & rtB .
jp5azcgtac , & rtB . hpuvpoamzd , & rtB . jknu1nrhnz , & rtB . dkfpnckao5 , &
rtB . f2wibvryef , & rtB . d2paa5zotr , & rtB . aemhoq5few , & rtB .
lbeln3akc2 , & rtB . fnydnbixk1 , & rtB . n5sbv1oypg , & rtB . jw32jpeck5 , &
rtB . aqj0wixgbx , & rtB . m22qmdpsyj , & rtB . hjpiowuzne , & rtB .
iea4dkyy2w , & rtB . kkn0pryfbs , & rtB . lzdd3z4ueb , & rtB . fmyjxkxyji , &
rtB . kaaziuo5ef , & rtB . ma2rvcr4nq , & rtB . jwmjcxympi , & rtB .
akirm2mhww , & rtB . ijufvlmorm , & rtB . mzfkqi1te1 , & rtB . mdla3lhngq , &
rtB . lisqze2m0v , & rtB . akkrfuecb2 , & rtB . nvde5gnl32 , & rtB .
pdl3oaaxvv , & rtB . ik1ga1yi4x , & rtB . pk0yjglikg , & rtB . hu24p5k4qk , &
rtB . plthkbxpdz , & rtB . mpss00ytce , & rtB . jmi5xid0ph , & rtB .
axx1cycxep , & rtB . n5sddkmaty , & rtB . bnbr20jdr4 , & rtB . dxcynwwxat , &
rtB . fqkin25shtk . ighgnitevw , & rtB . edzbs02xos1 . ddvcjkqoaj , & rtB .
f2kmaedy0v [ 0 ] , & rtB . awkevlz2ww . ighgnitevw , & rtB . cfrh4agkgq .
ddvcjkqoaj , & rtB . btp22atm5y [ 0 ] , & rtB . b5dbwkwsrj . ighgnitevw , &
rtB . cvrfqtrsgv . ddvcjkqoaj , & rtB . hg4tfoauyd [ 0 ] , & rtB .
jgvwez5knrn . jzxmgvajvp , & rtB . oarcyjxd4w , & rtB . h3jkxjjtu0 , & rtB .
fqkin25shtk . ighgnitevw , & rtB . edzbs02xos1 . ddvcjkqoaj , & rtB .
jsr2vw3sph , & rtB . d1ncaq24su , & rtB . dzgncmrria . jzxmgvajvp , & rtB .
lwvzpms5bv , & rtB . oru1g5vkau , & rtB . awkevlz2ww . ighgnitevw , & rtB .
cfrh4agkgq . ddvcjkqoaj , & rtB . bbud2xrwvw , & rtB . nhklduoiog , & rtB .
cc2aoo0nhc . jzxmgvajvp , & rtB . kp4mtdwxq5 , & rtB . bd1h4kdhj0 , & rtB .
b5dbwkwsrj . ighgnitevw , & rtB . cvrfqtrsgv . ddvcjkqoaj , & rtB .
hagpe2nohf , & rtB . kj3rknv443 , & rtB . jgvwez5knrn . jzxmgvajvp , & rtB .
dzgncmrria . jzxmgvajvp , & rtB . cc2aoo0nhc . jzxmgvajvp , & rtP .
Informacion_Data0 [ 0 ] , & rtP . Filtro_A [ 0 ] , & rtP . Filtro_B , & rtP .
Filtro_C , & rtP . Filtro_InitialCondition , & rtP . TransportDelay_Delay , &
rtP . TransportDelay_InitOutput , & rtP . GaussianNoiseGenerator_m , & rtP .
GaussianNoiseGenerator_d , & rtP . GaussianNoiseGenerator_s , & rtP .
TransportDelay_InitOutput_npzkuu2dfa , & rtP . PulseGenerator_Amp , & rtP .
PulseGenerator_Duty , & rtP . PulseGenerator_PhaseDelay , & rtP .
Integrator_IC , & rtP . TransportDelay_Delay_lnyuh05kkd , & rtP .
TransportDelay_InitOutput_g2gukl3g33 , & rtP . CompareToConstant_const , &
rtP . GaussianNoiseGenerator_m_pvxm3ngdo5 , & rtP .
GaussianNoiseGenerator_s_mqeqzkwvys , & rtP . Integrator_IC_nblk03gvyi , &
rtP . Filtro_A_almvbenuye [ 0 ] , & rtP . Filtro_B_cz4ovtnlbh , & rtP .
Filtro_C_l0jcyicm4y , & rtP . Filtro_InitialCondition_ixj5gjnfdp , & rtP .
RandomNumber_Mean , & rtP . RandomNumber_StdDev , & rtP . Buffer_ic , & rtP .
_Y0 , & rtP . Constant_Value , & rtP . TransportDelay_InitOutput_bd4zohbbpk ,
& rtP . TransportDelay1_InitOutput_ge1vnqoztc , & rtP . MatrixGain_Gain , &
rtP . RandomNumber_Mean_n4x5jyjuez , & rtP . RandomNumber_StdDev_ojydngz0lp ,
& rtP . Buffer_ic_lzvqyw2ni2 , & rtP . Monostable_ic , & rtP .
Monostable1_ic_bkmb1fdrhz , & rtP . Constant5_Value , & rtP . Constant6_Value
, & rtP . Integrator_IC_dfzts412q5 , & rtP . Integrator1_IC , & rtP .
Switch2_Threshold , & rtP . TransportDelay_InitOutput_itctaj4ekg , & rtP .
_Y0_dwtojptuc5 , & rtP . Integrator_IC_hiwtnk3vzy , & rtP .
Integrator1_IC_ggm3f24kg1 , & rtP . TransportDelay_InitOutput_ac2nn3i4uy , &
rtP . TransportDelay1_InitOutput_dc05214qlk , & rtP . Monostable1_ic , & rtP
. Constant1_Value_ju0tizjign , & rtP . Constant10_Value , & rtP .
Constant11_Value , & rtP . Constant12_Value , & rtP . Constant13_Value , &
rtP . Constant14_Value , & rtP . Constant15_Value , & rtP . Constant16_Value
, & rtP . Constant17_Value , & rtP . Constant18_Value , & rtP .
Constant19_Value , & rtP . Constant2_Value , & rtP . Constant20_Value , & rtP
. Constant3_Value , & rtP . Constant4_Value , & rtP .
Constant5_Value_ak2ogm0bur , & rtP . Constant6_Value_mfzl25kers , & rtP .
Constant7_Value , & rtP . Constant8_Value , & rtP . Constant9_Value , & rtP .
Switch_Threshold , & rtP . Switch1_Threshold , & rtP .
TransportDelay1_InitOutput , & rtP . TransportDelay10_InitOutput , & rtP .
TransportDelay11_InitOutput , & rtP . TransportDelay12_Delay , & rtP .
TransportDelay12_InitOutput , & rtP . TransportDelay13_InitOutput , & rtP .
TransportDelay2_InitOutput , & rtP . TransportDelay3_InitOutput , & rtP .
TransportDelay4_InitOutput , & rtP . TransportDelay5_InitOutput , & rtP .
TransportDelay6_InitOutput , & rtP . TransportDelay7_InitOutput , & rtP .
TransportDelay8_InitOutput , & rtP . TransportDelay9_InitOutput , & rtP .
ModuloIntegrator_IC_apzvenlzc5 , & rtP .
ModuloIntegrator_WrappedStateUpperValue_o4nt1k5w0o , & rtP .
ModuloIntegrator_WrappedStateLowerValue_ehdhuzchfk , & rtP . _Y0_db5voyihuo ,
& rtP . _Y0_bdpgvrnswx , & rtP . ModuloIntegrator_IC , & rtP .
ModuloIntegrator_WrappedStateUpperValue , & rtP .
ModuloIntegrator_WrappedStateLowerValue , & rtP . SampleandHold_ic_jlfvpcljxw
, & rtP . Memory_InitialCondition_meb2sac0hw , & rtP .
SampleandHold_ic_lzb14dyui4 , & rtP . Memory_InitialCondition_aqwb21zvmj , &
rtP . ModuloIntegrator_IC_mhkqbc55cu , & rtP .
ModuloIntegrator_WrappedStateUpperValue_l42cys1cux , & rtP .
ModuloIntegrator_WrappedStateLowerValue_fozsdgujhv , & rtP .
ModuloIntegrator_IC_pwbk55yuz2 , & rtP .
ModuloIntegrator_WrappedStateUpperValue_cqbjibrf3p , & rtP .
ModuloIntegrator_WrappedStateLowerValue_nzxqkuyo3a , & rtP . SampleandHold_ic
, & rtP . Memory_InitialCondition , & rtP . Constant1_Value , & rtP .
eitheredge_Value [ 0 ] , & rtP . negedge_Value [ 0 ] , & rtP . posedge_Value
[ 0 ] , & rtP . Constant1_Value_bx4tgv4ysd , & rtP .
eitheredge_Value_mhaz3orisj [ 0 ] , & rtP . negedge_Value_kjod1cdk3f [ 0 ] ,
& rtP . posedge_Value_dx0lu3aoqz [ 0 ] , & rtP . Constant1_Value_j11evhb4ur ,
& rtP . eitheredge_Value_nb0pdzkjaa [ 0 ] , & rtP . negedge_Value_abbvesy1jz
[ 0 ] , & rtP . posedge_Value_arvlrnf2hc [ 0 ] , & rtP .
Constant_Value_pgh0qhw5wr , & rtP . Constant_Value_czlel2g4xm , & rtP .
Constant_Value_dufhvts2ca , & rtP . jgvwez5knrn . Out1_Y0 , & rtP .
dzgncmrria . Out1_Y0 , & rtP . cc2aoo0nhc . Out1_Y0 , & rtP .
Atenuacion_canal , & rtP . C , & rtP . Datos , & rtP . Frec1 , & rtP . Frec2
, & rtP . R1 , & rtP . R2 , & rtP . Rb , & rtP . Retraso_canal , & rtP . kv ,
& rtP . kv2 , } ; static int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , SS_DOUBLE , 0 , 0 , 0 } , {
"unsigned char" , "boolean_T" , 0 , 0 , sizeof ( boolean_T ) , SS_BOOLEAN , 0
, 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } , {
rtwCAPI_VECTOR , 8 , 2 , 0 } , { rtwCAPI_VECTOR , 10 , 2 , 0 } } ; static
const uint_T rtDimensionArray [ ] = { 1 , 1 , 2 , 1 , 182 , 1 , 7 , 1 , 11 ,
1 , 1 , 2 } ; static const real_T rtcapiStoredFloats [ ] = { 8.0E-6 , 0.0 , -
2.0 , 1.0 , 1.0E-9 } ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { (
NULL ) , ( NULL ) , rtwCAPI_FIX_RESERVED , 0 , 0 , 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 3 ,
0 } , { ( const void * ) & rtcapiStoredFloats [ 1 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , 0 , 0 } , { ( NULL ) , ( NULL ) , - 1 , 0 } , { (
const void * ) & rtcapiStoredFloats [ 2 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , 4 , 0 } , { ( const void * ) & rtcapiStoredFloats
[ 1 ] , ( const void * ) & rtcapiStoredFloats [ 3 ] , 1 , 0 } , { ( const
void * ) & rtcapiStoredFloats [ 4 ] , ( const void * ) & rtcapiStoredFloats [
1 ] , 2 , 0 } , { ( NULL ) , ( NULL ) , 5 , 0 } } ; static
rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 105 , ( NULL
) , 0 , ( NULL ) , 0 } , { rtBlockParameters , 124 , rtModelParameters , 11 }
, { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap , rtFixPtMap ,
rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float" , { 2351720087U
, 4125363493U , 143698455U , 1469152365U } , ( NULL ) , 0 , 0 } ; const
rtwCAPI_ModelMappingStaticInfo * FSK_GetCAPIStaticMap ( void ) { return &
mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void FSK_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
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
void FSK_host_InitializeDataMapInfo ( FSK_host_DataMapInfo_T * dataMap ,
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
