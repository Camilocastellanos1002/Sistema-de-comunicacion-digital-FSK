#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "Multuplexacion_FDM_capi_host.h"
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
#include "Multuplexacion_FDM.h"
#include "Multuplexacion_FDM_capi.h"
#include "Multuplexacion_FDM_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"Multuplexacion_FDM/ informacion 1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 0 } , { 1 , 0 , TARGET_STRING ( "Multuplexacion_FDM/Informacion 2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 2 , 0 , TARGET_STRING (
"Multuplexacion_FDM/Multiplex" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 }
, { 3 , 0 , TARGET_STRING ( "Multuplexacion_FDM/Demux/Analog Filter Design" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 4 , 0 , TARGET_STRING (
"Multuplexacion_FDM/Demux/Analog Filter Design2" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 5 , 0 , TARGET_STRING (
"Multuplexacion_FDM/Mod1/Product" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
1 } , { 6 , 0 , TARGET_STRING ( "Multuplexacion_FDM/Mod1/Transport Delay" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 7 , 0 , TARGET_STRING (
"Multuplexacion_FDM/canal /Gain" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1
} , { 8 , 0 , TARGET_STRING ( "Multuplexacion_FDM/canal /Add" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 9 , 0 , TARGET_STRING (
"Multuplexacion_FDM/canal /Transport Delay" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 10 , 1 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Muestreo y Retencion " ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 11 , 0 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Data Type Conversion" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 12 , 0 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Pulse Generator" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 3 } , { 13 , 0 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Integrator" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 14 , 0 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Product" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 15 , 10 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sample and Hold" ) , TARGET_STRING ( "" ) , 0 ,
1 , 0 , 0 , 2 } , { 16 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Integrator" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 17 , 0 , TARGET_STRING ( "Multuplexacion_FDM/receptor /Sign3"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 18 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 1 } , { 19 , 0 , TARGET_STRING ( "Multuplexacion_FDM/receptor /Add" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 20 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Add1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 1 } , { 21 , 0 , TARGET_STRING (
"Multuplexacion_FDM/Mod1/Continuous-Time VCO/Sensitivity" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 22 , 0 , TARGET_STRING (
"Multuplexacion_FDM/Mod1/Continuous-Time VCO/Sum" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 23 , 0 , TARGET_STRING (
"Multuplexacion_FDM/Mod2/Continuous-Time VCO/Sum" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 24 , 0 , TARGET_STRING (
"Multuplexacion_FDM/canal /Gaussian Noise Generator/Sum" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 5 } , { 25 , 0 , TARGET_STRING (
"Multuplexacion_FDM/canal /Gaussian Noise Generator/Buffer" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 5 } , { 26 , 1 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Muestreo y Retencion /In" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 27 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro /Product" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 28 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro /Product1" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 29 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro /Add" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 30 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro /Add1" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 31 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro /Transport Delay" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 32 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro /Transport Delay1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 33 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Gaussian Noise Generator/Sum" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 5 } , { 34 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Gaussian Noise Generator/Buffer" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 5 } , { 35 , 8 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Sample and Hold" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 2 } , { 36 , 9 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Sample and Hold1" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 2 } , { 37 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Abs" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 4 } , { 38 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Integrator" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 39 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Integrator1" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 40 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Sum" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 1 } , { 41 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Switch2" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 4 } , { 42 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Transport Delay" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 1 } , { 43 , 10 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sample and Hold/In" ) , TARGET_STRING ( "" ) ,
0 , 1 , 0 , 0 , 2 } , { 44 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Gain" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 45 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Gain1" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 46 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Integrator" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 47 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Integrator1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 48 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Product1" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 49 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Product2" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 50 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Product3" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 51 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Product4" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 52 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Product5" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 53 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Product6" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 54 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Product7" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 55 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Product8" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 56 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Add" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 57 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Add1" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 58 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Add2" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 59 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Transport Delay" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 60 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Transport Delay1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 61 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Logical Operator" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 62 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Product4" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 4 } , { 63 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Add" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 64 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Switch2" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 1 } , { 65 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Switch3" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 4 } , { 66 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 67 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay10" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 68 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay11" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 69 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 70 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 71 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay4" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 72 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay5" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 73 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay6" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 74 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay7" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 75 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay8" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 76 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay9" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 77 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/Mod1/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 78 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/Mod2/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 79 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Continuous-Time VCO/Inherit Shape" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 80 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Continuous-Time VCO/Sum" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 81 , 8 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Sample and Hold/In" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 2 } , { 82 , 9 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Sample and Hold1/In" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 2 } , { 83 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO/Sensitivity"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 84 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO/Inherit Shape"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 85 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO/Sum" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 86 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO1/Sensitivity"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 87 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO1/Inherit Shape"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 88 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO1/Sum" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 89 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 90 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Clock" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 91 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable/Model/T_monostable" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 92 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Data Type Conversion2" )
, TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 93 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Logical Operator1" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 94 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Relational Operator" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 95 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Sum" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 96 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Clock" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 97 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/T_monostable" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 98 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Data Type Conversion2"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 99 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Logical Operator1" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 100 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Relational Operator" )
, TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 101 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Sum" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 102 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 103 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO1/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 104 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Clock" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 105 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/T_monostable" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 106 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Logical Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 107 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 108 , 0 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Sum" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 109 , 3 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/NEGATIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 110 , 4 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/POSITIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 111 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Multiport Switch"
) , TARGET_STRING ( "" ) , 0 , 0 , 1 , 0 , 6 } , { 112 , 6 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/NEGATIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 113 , 7 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/POSITIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 114 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Multiport Switch"
) , TARGET_STRING ( "" ) , 0 , 0 , 1 , 0 , 6 } , { 115 , 12 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/NEGATIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 116 , 13 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/POSITIVE Edge"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 117 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Multiport Switch"
) , TARGET_STRING ( "" ) , 0 , 0 , 1 , 0 , 6 } , { 118 , 2 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 119 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Clock"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 120 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Sum"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 121 , 3 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/NEGATIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 122 , 4 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/POSITIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 123 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Sample and Hold/Model/IC=ic"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 124 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Sample and Hold/Model/Switch"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 125 , 5 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 126 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Clock"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 127 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Sum"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 128 , 6 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/NEGATIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 129 , 7 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/POSITIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 130 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Sample and Hold/Model/IC=ic"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 131 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Sample and Hold/Model/Switch"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 132 , 11 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 133 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Clock"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 134 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Sum"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 135 , 12 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/NEGATIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 136 , 13 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/POSITIVE Edge/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 4 } , { 137 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Sample and Hold/Model/IC=ic"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 138 , 0 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Sample and Hold/Model/Switch"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 139 , 2 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/In1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 140 , 5 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/In1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 141 , 11 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/In1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 0 , 0 , ( NULL ) , ( NULL
) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 142 , TARGET_STRING (
"Multuplexacion_FDM/ informacion 1" ) , TARGET_STRING ( "Data0" ) , 0 , 2 , 0
} , { 143 , TARGET_STRING ( "Multuplexacion_FDM/Informacion 2" ) ,
TARGET_STRING ( "Data0" ) , 0 , 2 , 0 } , { 144 , TARGET_STRING (
"Multuplexacion_FDM/Demux/Analog Filter Design" ) , TARGET_STRING ( "A" ) , 0
, 3 , 0 } , { 145 , TARGET_STRING (
"Multuplexacion_FDM/Demux/Analog Filter Design" ) , TARGET_STRING ( "B" ) , 0
, 0 , 0 } , { 146 , TARGET_STRING (
"Multuplexacion_FDM/Demux/Analog Filter Design" ) , TARGET_STRING ( "C" ) , 0
, 0 , 0 } , { 147 , TARGET_STRING (
"Multuplexacion_FDM/Demux/Analog Filter Design" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 148 , TARGET_STRING (
"Multuplexacion_FDM/Demux/Analog Filter Design2" ) , TARGET_STRING ( "A" ) ,
0 , 3 , 0 } , { 149 , TARGET_STRING (
"Multuplexacion_FDM/Demux/Analog Filter Design2" ) , TARGET_STRING ( "B" ) ,
0 , 0 , 0 } , { 150 , TARGET_STRING (
"Multuplexacion_FDM/Demux/Analog Filter Design2" ) , TARGET_STRING ( "C" ) ,
0 , 0 , 0 } , { 151 , TARGET_STRING (
"Multuplexacion_FDM/Demux/Analog Filter Design2" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 152 , TARGET_STRING (
"Multuplexacion_FDM/Mod1/Sine Wave" ) , TARGET_STRING ( "Amplitude" ) , 0 , 0
, 0 } , { 153 , TARGET_STRING ( "Multuplexacion_FDM/Mod1/Sine Wave" ) ,
TARGET_STRING ( "Bias" ) , 0 , 0 , 0 } , { 154 , TARGET_STRING (
"Multuplexacion_FDM/Mod1/Sine Wave" ) , TARGET_STRING ( "Phase" ) , 0 , 0 , 0
} , { 155 , TARGET_STRING ( "Multuplexacion_FDM/Mod1/Transport Delay" ) ,
TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0 } , { 156 , TARGET_STRING (
"Multuplexacion_FDM/Mod1/Transport Delay" ) , TARGET_STRING ( "InitialOutput"
) , 0 , 0 , 0 } , { 157 , TARGET_STRING (
"Multuplexacion_FDM/canal /Gaussian Noise Generator" ) , TARGET_STRING ( "m"
) , 0 , 0 , 0 } , { 158 , TARGET_STRING (
"Multuplexacion_FDM/canal /Gaussian Noise Generator" ) , TARGET_STRING ( "d"
) , 0 , 0 , 0 } , { 159 , TARGET_STRING (
"Multuplexacion_FDM/canal /Gaussian Noise Generator" ) , TARGET_STRING ( "s"
) , 0 , 0 , 0 } , { 160 , TARGET_STRING (
"Multuplexacion_FDM/canal /Transport Delay" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 161 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Pulse Generator" ) , TARGET_STRING (
"Amplitude" ) , 0 , 0 , 0 } , { 162 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Pulse Generator" ) , TARGET_STRING (
"PulseWidth" ) , 0 , 0 , 0 } , { 163 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Pulse Generator" ) , TARGET_STRING (
"PhaseDelay" ) , 0 , 0 , 0 } , { 164 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 165 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Transport Delay" ) , TARGET_STRING (
"DelayTime" ) , 0 , 0 , 0 } , { 166 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Transport Delay" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 167 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Compare To Constant" ) , TARGET_STRING (
"const" ) , 0 , 0 , 0 } , { 168 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Gaussian Noise Generator" ) , TARGET_STRING (
"m" ) , 0 , 0 , 0 } , { 169 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Gaussian Noise Generator" ) , TARGET_STRING (
"s" ) , 0 , 0 , 0 } , { 170 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 171 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro" ) , TARGET_STRING ( "A" ) , 0 , 4 , 0 }
, { 172 , TARGET_STRING ( "Multuplexacion_FDM/receptor /Filtro" ) ,
TARGET_STRING ( "B" ) , 0 , 0 , 0 } , { 173 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro" ) , TARGET_STRING ( "C" ) , 0 , 0 , 0 }
, { 174 , TARGET_STRING ( "Multuplexacion_FDM/receptor /Filtro" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 175 , TARGET_STRING (
"Multuplexacion_FDM/canal /Gaussian Noise Generator/Random Number" ) ,
TARGET_STRING ( "Mean" ) , 0 , 0 , 0 } , { 176 , TARGET_STRING (
"Multuplexacion_FDM/canal /Gaussian Noise Generator/Random Number" ) ,
TARGET_STRING ( "StdDev" ) , 0 , 0 , 0 } , { 177 , TARGET_STRING (
"Multuplexacion_FDM/canal /Gaussian Noise Generator/Buffer" ) , TARGET_STRING
( "ic" ) , 0 , 0 , 0 } , { 178 , TARGET_STRING (
"Multuplexacion_FDM/medidor de error1/Muestreo y Retencion / " ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 179 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro /Constant" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 180 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro /Transport Delay" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 181 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Filtro /Transport Delay1" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 182 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Gaussian Noise Generator/Matrix Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 183 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Gaussian Noise Generator/Random Number" ) ,
TARGET_STRING ( "Mean" ) , 0 , 0 , 0 } , { 184 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Gaussian Noise Generator/Random Number" ) ,
TARGET_STRING ( "StdDev" ) , 0 , 0 , 0 } , { 185 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Gaussian Noise Generator/Buffer" ) ,
TARGET_STRING ( "ic" ) , 0 , 0 , 0 } , { 186 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable" ) , TARGET_STRING ( "ic" ) ,
1 , 0 , 0 } , { 187 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable1" ) , TARGET_STRING ( "ic" ) ,
1 , 0 , 0 } , { 188 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Constant5" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 189 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Constant6" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 190 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 191 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Integrator1" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 192 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Switch2" ) , TARGET_STRING ( "Threshold"
) , 0 , 0 , 0 } , { 193 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Transport Delay" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 194 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sample and Hold/ " ) , TARGET_STRING (
"InitialOutput" ) , 1 , 0 , 0 } , { 195 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 196 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Integrator1" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 197 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Transport Delay" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 198 , TARGET_STRING (
"Multuplexacion_FDM/receptor /SinPortadora /Transport Delay1" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 199 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Monostable1" ) , TARGET_STRING (
"ic" ) , 1 , 0 , 0 } , { 200 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant1" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 201 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant10" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 202 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant11" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 203 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant12" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 204 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant13" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 205 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant14" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 206 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant15" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 207 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant16" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 208 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant17" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 209 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant18" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 210 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant19" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 211 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant2" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 212 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant20" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 213 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant3" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 214 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant4" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 215 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant5" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 216 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant6" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 217 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant7" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 218 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant8" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 219 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Constant9" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 220 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Switch" ) , TARGET_STRING (
"Threshold" ) , 0 , 0 , 0 } , { 221 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Switch1" ) , TARGET_STRING (
"Threshold" ) , 0 , 0 , 0 } , { 222 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay1" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 223 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay10" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 224 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay11" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 225 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay12" ) ,
TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0 } , { 226 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay12" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 227 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay13" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 228 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay2" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 229 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay3" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 230 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay4" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 231 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay5" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 232 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay6" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 233 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay7" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 234 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay8" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 235 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Transport Delay9" ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 236 , TARGET_STRING (
 "Multuplexacion_FDM/Mod1/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 237 ,
TARGET_STRING (
 "Multuplexacion_FDM/Mod1/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 238 ,
TARGET_STRING (
 "Multuplexacion_FDM/Mod1/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 239 ,
TARGET_STRING (
 "Multuplexacion_FDM/Mod2/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 240 ,
TARGET_STRING (
 "Multuplexacion_FDM/Mod2/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 241 ,
TARGET_STRING (
 "Multuplexacion_FDM/Mod2/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 242 ,
TARGET_STRING ( "Multuplexacion_FDM/receptor /Reloj/Sample and Hold/ " ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 243 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Sample and Hold1/ " ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 244 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 245 ,
TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 246 ,
TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 247 ,
TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Sample and Hold" ) ,
TARGET_STRING ( "ic" ) , 0 , 0 , 0 } , { 248 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Memory" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 249 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Sample and Hold" ) ,
TARGET_STRING ( "ic" ) , 0 , 0 , 0 } , { 250 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Memory" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 251 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 252 ,
TARGET_STRING (
 "Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 253 ,
TARGET_STRING (
 "Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 254 ,
TARGET_STRING (
 "Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO1/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 255 ,
TARGET_STRING (
 "Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO1/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateUpperValue" ) , 0 , 0 , 0 } , { 256 ,
TARGET_STRING (
 "Multuplexacion_FDM/receptor /SinPortadora /Continuous-Time VCO1/Modulo  Integrator/Modulo Integrator"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 257 ,
TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Sample and Hold"
) , TARGET_STRING ( "ic" ) , 0 , 0 , 0 } , { 258 , TARGET_STRING (
"Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Memory" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 259 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Constant1"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 260 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/either edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 261 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/neg. edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 262 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/pos. edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 263 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Constant1"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 264 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/either edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 265 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/neg. edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 266 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/pos. edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 267 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Constant1"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 268 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/either edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 269 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/neg. edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 270 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/pos. edge"
) , TARGET_STRING ( "Value" ) , 0 , 5 , 0 } , { 271 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 272 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/NEGATIVE Edge/OUT"
) , TARGET_STRING ( "InitialOutput" ) , 1 , 0 , 0 } , { 273 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/POSITIVE Edge/OUT"
) , TARGET_STRING ( "InitialOutput" ) , 1 , 0 , 0 } , { 274 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 275 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/NEGATIVE Edge/OUT"
) , TARGET_STRING ( "InitialOutput" ) , 1 , 0 , 0 } , { 276 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/POSITIVE Edge/OUT"
) , TARGET_STRING ( "InitialOutput" ) , 1 , 0 , 0 } , { 277 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 278 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/NEGATIVE Edge/OUT"
) , TARGET_STRING ( "InitialOutput" ) , 1 , 0 , 0 } , { 279 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/POSITIVE Edge/OUT"
) , TARGET_STRING ( "InitialOutput" ) , 1 , 0 , 0 } , { 280 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/Out1"
) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 281 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Reloj/Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/Out1"
) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 282 , TARGET_STRING (
 "Multuplexacion_FDM/receptor /Sincronismo /Monostable1/Model/Continuous Edge Detector/Internal dirac generator/Triggered Subsystem/Out1"
) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL
) , 0 , 0 , 0 } } ; static const rtwCAPI_ModelParameters rtModelParameters [
] = { { 283 , TARGET_STRING ( "Atenuacion_canal" ) , 0 , 0 , 0 } , { 284 ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 285 , TARGET_STRING ( "Datos" ) , 0 ,
0 , 0 } , { 286 , TARGET_STRING ( "Frec1" ) , 0 , 0 , 0 } , { 287 ,
TARGET_STRING ( "Frec2" ) , 0 , 0 , 0 } , { 288 , TARGET_STRING ( "R1" ) , 0
, 0 , 0 } , { 289 , TARGET_STRING ( "R2" ) , 0 , 0 , 0 } , { 290 ,
TARGET_STRING ( "Rb" ) , 0 , 0 , 0 } , { 291 , TARGET_STRING (
"Retraso_canal" ) , 0 , 0 , 0 } , { 292 , TARGET_STRING ( "frecport1" ) , 0 ,
0 , 0 } , { 293 , TARGET_STRING ( "kv" ) , 0 , 0 , 0 } , { 294 ,
TARGET_STRING ( "kv2" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . omyffgmxzc , & rtB . l2slq2pxao ,
& rtB . jaf1or2u2g , & rtB . otfd1hdnf4 , & rtB . gzkvmusrdv , & rtB .
kvdiwfhjmc , & rtB . oddjfmdyew , & rtB . dc0ixgrh4v , & rtB . cuyzwij0cy , &
rtB . lisu5vhdeu , & rtB . lufwcivalw , & rtB . p5sg0ao2sd , & rtB .
hnghqt15hm , & rtB . hqvlr0c1t3 , & rtB . l3viz5m5kx , & rtB . e1nhqxjvjn , &
rtB . m1xi1b0n5m , & rtB . f1l5jsixgw , & rtB . izg2hxr1hm , & rtB .
pbk3xyooxn , & rtB . exdbaattar , & rtB . ftbsaajysf , & rtB . i3olz0n0gi , &
rtB . ckmrjxysf3 , & rtB . czpmrjwdbw , & rtB . eqpfzakwij , & rtB .
lufwcivalw , & rtB . iup0qas13y , & rtB . pskl4q2wwt , & rtB . flwwemz4a3 , &
rtB . dwuvmlamlj , & rtB . jj2crb3wdo , & rtB . ay4kbspa2f , & rtB .
hd0ccnz5kj , & rtB . kmsebnmjbu , & rtB . munnuokh3b , & rtB . dduxw540hu , &
rtB . hrs0mectw5 , & rtB . fosqwahuok , & rtB . l5nwaj4e3i , & rtB .
looejrxoki , & rtB . cwrlg5uwpe , & rtB . bonunno3da , & rtB . e1nhqxjvjn , &
rtB . ehk41k1jvu , & rtB . dl2z1kzk4x , & rtB . dhvezilxca , & rtB .
dhxzfrd1ut , & rtB . kb3qoydtul , & rtB . emzymu3s4t , & rtB . fz1wrzhdaa , &
rtB . csu05jokxd , & rtB . eg0uqlyrw2 , & rtB . kp3wrgz5sh , & rtB .
h32dvvdjsr , & rtB . cfvwyihfgi , & rtB . fy1jpymzvl , & rtB . bbdybg5bbo , &
rtB . ihg3emy0vs , & rtB . pbihxnhzkv , & rtB . jdmdbzovgb , & rtB .
o2g3bsob40 , & rtB . osh4e3wkbx , & rtB . dfyucx0pjs , & rtB . co4tajx3jh , &
rtB . hduwbah451 , & rtB . mhvwbma2wc , & rtB . nuzxbadudr , & rtB .
hd11xynwm2 , & rtB . jkosinqwcz , & rtB . pw3nmstdx1 , & rtB . hoboqemidv , &
rtB . leuwvo5bd0 , & rtB . aekkmo2dza , & rtB . hdfbddrmbc , & rtB .
kzkfn1s2js , & rtB . fetl3awrl2 , & rtB . dwygygnfyu , & rtB . d4sffuf0wj , &
rtB . ph3uie01yv , & rtB . awasz3p2hm , & rtB . munnuokh3b , & rtB .
dduxw540hu , & rtB . l1ylzo5bhw , & rtB . nrzgv2asbm , & rtB . cj3eokpnbs , &
rtB . i14aygkcoq , & rtB . ijhgy4lexb , & rtB . a4wt4ee5p1 , & rtB .
ifswdaywbt , & rtB . orkfi0mp2e , & rtB . pgvargzqvr , & rtB . eaief2hsbj , &
rtB . dumyggkchi , & rtB . hgcnrsrftd , & rtB . ityop505e4 , & rtB .
fgrkiz4z0n , & rtB . hx1rf2yrz2 , & rtB . bnhnntm3f4 , & rtB . ajbeq5hpnj , &
rtB . eizf1ealtw , & rtB . cviwvtwqhc , & rtB . nb4mlfbe25 , & rtB .
gwfkgabvtm , & rtB . drqnxkzet4 , & rtB . loxkzong0h , & rtB . f0xjphnymz , &
rtB . nekkkm0p0a , & rtB . gx1uxu4kds , & rtB . dnioykk3w1k . hmpzhh3n3o , &
rtB . d5zlt11l1pl . ltgb5gkcbo , & rtB . fto4cglprz [ 0 ] , & rtB .
fkhi333c1w . hmpzhh3n3o , & rtB . gggqmave4q . ltgb5gkcbo , & rtB .
nj0vsa0aao [ 0 ] , & rtB . mpycb0evfp . hmpzhh3n3o , & rtB . abmuy5rnsq .
ltgb5gkcbo , & rtB . i4cllywuc1 [ 0 ] , & rtB . mivhx1fvuuy . hml4vbrazh , &
rtB . axof5reva4 , & rtB . m3xclbw4n1 , & rtB . dnioykk3w1k . hmpzhh3n3o , &
rtB . d5zlt11l1pl . ltgb5gkcbo , & rtB . izpbcjjrig , & rtB . gwu42iz5ys , &
rtB . dyorcglstw . hml4vbrazh , & rtB . jka1elz4sz , & rtB . ikxyn0xytc , &
rtB . fkhi333c1w . hmpzhh3n3o , & rtB . gggqmave4q . ltgb5gkcbo , & rtB .
cswpv2o1kk , & rtB . de2xsxb24p , & rtB . jiixgvrfhd . hml4vbrazh , & rtB .
fuwgkaabcp , & rtB . d2vdhfxwnv , & rtB . mpycb0evfp . hmpzhh3n3o , & rtB .
abmuy5rnsq . ltgb5gkcbo , & rtB . owlyu5iz4l , & rtB . dwfqmte2n3 , & rtB .
mivhx1fvuuy . hml4vbrazh , & rtB . dyorcglstw . hml4vbrazh , & rtB .
jiixgvrfhd . hml4vbrazh , & rtP . informacion1_Data0 [ 0 ] , & rtP .
Informacion2_Data0 [ 0 ] , & rtP . AnalogFilterDesign_A [ 0 ] , & rtP .
AnalogFilterDesign_B , & rtP . AnalogFilterDesign_C , & rtP .
AnalogFilterDesign_InitialCondition , & rtP . AnalogFilterDesign2_A [ 0 ] , &
rtP . AnalogFilterDesign2_B , & rtP . AnalogFilterDesign2_C , & rtP .
AnalogFilterDesign2_InitialCondition , & rtP . SineWave_Amp , & rtP .
SineWave_Bias , & rtP . SineWave_Phase , & rtP . TransportDelay_Delay , & rtP
. TransportDelay_InitOutput , & rtP . GaussianNoiseGenerator_m , & rtP .
GaussianNoiseGenerator_d , & rtP . GaussianNoiseGenerator_s , & rtP .
TransportDelay_InitOutput_a54zvzwmak , & rtP . PulseGenerator_Amp , & rtP .
PulseGenerator_Duty , & rtP . PulseGenerator_PhaseDelay , & rtP .
Integrator_IC , & rtP . TransportDelay_Delay_dget2i1x1r , & rtP .
TransportDelay_InitOutput_nb5s3gjuh0 , & rtP . CompareToConstant_const , &
rtP . GaussianNoiseGenerator_m_feibr5czzb , & rtP .
GaussianNoiseGenerator_s_natqquq25k , & rtP . Integrator_IC_moexjyifg4 , &
rtP . Filtro_A [ 0 ] , & rtP . Filtro_B , & rtP . Filtro_C , & rtP .
Filtro_InitialCondition , & rtP . RandomNumber_Mean , & rtP .
RandomNumber_StdDev , & rtP . Buffer_ic , & rtP . _Y0 , & rtP .
Constant_Value , & rtP . TransportDelay_InitOutput_nwut2o4lpm , & rtP .
TransportDelay1_InitOutput_cz0jjsby1m , & rtP . MatrixGain_Gain , & rtP .
RandomNumber_Mean_pbcszkatmd , & rtP . RandomNumber_StdDev_iveng2gmn4 , & rtP
. Buffer_ic_b4vk0qmtfp , & rtP . Monostable_ic , & rtP .
Monostable1_ic_biaz4juxj0 , & rtP . Constant5_Value , & rtP . Constant6_Value
, & rtP . Integrator_IC_ptowdeldtu , & rtP . Integrator1_IC , & rtP .
Switch2_Threshold , & rtP . TransportDelay_InitOutput_bfobvi0kzf , & rtP .
_Y0_ld4ghr3opr , & rtP . Integrator_IC_nfolmlihr0 , & rtP .
Integrator1_IC_dcpkt2betd , & rtP . TransportDelay_InitOutput_pz2dgrhemk , &
rtP . TransportDelay1_InitOutput , & rtP . Monostable1_ic , & rtP .
Constant1_Value_obqa0ysasv , & rtP . Constant10_Value , & rtP .
Constant11_Value , & rtP . Constant12_Value , & rtP . Constant13_Value , &
rtP . Constant14_Value , & rtP . Constant15_Value , & rtP . Constant16_Value
, & rtP . Constant17_Value , & rtP . Constant18_Value , & rtP .
Constant19_Value , & rtP . Constant2_Value , & rtP . Constant20_Value , & rtP
. Constant3_Value , & rtP . Constant4_Value , & rtP .
Constant5_Value_pqkhorznoi , & rtP . Constant6_Value_oth1tjvwv0 , & rtP .
Constant7_Value , & rtP . Constant8_Value , & rtP . Constant9_Value , & rtP .
Switch_Threshold , & rtP . Switch1_Threshold , & rtP .
TransportDelay1_InitOutput_km2up0labu , & rtP . TransportDelay10_InitOutput ,
& rtP . TransportDelay11_InitOutput , & rtP . TransportDelay12_Delay , & rtP
. TransportDelay12_InitOutput , & rtP . TransportDelay13_InitOutput , & rtP .
TransportDelay2_InitOutput , & rtP . TransportDelay3_InitOutput , & rtP .
TransportDelay4_InitOutput , & rtP . TransportDelay5_InitOutput , & rtP .
TransportDelay6_InitOutput , & rtP . TransportDelay7_InitOutput , & rtP .
TransportDelay8_InitOutput , & rtP . TransportDelay9_InitOutput , & rtP .
ModuloIntegrator_IC_esfyns1sy5 , & rtP .
ModuloIntegrator_WrappedStateUpperValue_inwk4jds10 , & rtP .
ModuloIntegrator_WrappedStateLowerValue_efd0rfjvev , & rtP .
ModuloIntegrator_IC_i5n3se5kvp , & rtP .
ModuloIntegrator_WrappedStateUpperValue_dcyqcfnaqw , & rtP .
ModuloIntegrator_WrappedStateLowerValue_i1zhdl4bre , & rtP . _Y0_matapuynvo ,
& rtP . _Y0_ghe40wtwbh , & rtP . ModuloIntegrator_IC , & rtP .
ModuloIntegrator_WrappedStateUpperValue , & rtP .
ModuloIntegrator_WrappedStateLowerValue , & rtP . SampleandHold_ic_j2rdwmu3tc
, & rtP . Memory_InitialCondition_jlkxne1qro , & rtP .
SampleandHold_ic_iltoiaeoee , & rtP . Memory_InitialCondition_cdrhhgyi4a , &
rtP . ModuloIntegrator_IC_nahsh2vkhw , & rtP .
ModuloIntegrator_WrappedStateUpperValue_h455it4xzm , & rtP .
ModuloIntegrator_WrappedStateLowerValue_bslhwjjmfb , & rtP .
ModuloIntegrator_IC_cw2uxsyp5l , & rtP .
ModuloIntegrator_WrappedStateUpperValue_hgarqjv2uf , & rtP .
ModuloIntegrator_WrappedStateLowerValue_mxtqs3uocj , & rtP . SampleandHold_ic
, & rtP . Memory_InitialCondition , & rtP . Constant1_Value , & rtP .
eitheredge_Value [ 0 ] , & rtP . negedge_Value [ 0 ] , & rtP . posedge_Value
[ 0 ] , & rtP . Constant1_Value_lpebpexhqd , & rtP .
eitheredge_Value_a1qgi2i0lx [ 0 ] , & rtP . negedge_Value_a22nqhbklc [ 0 ] ,
& rtP . posedge_Value_iryngzqrd1 [ 0 ] , & rtP . Constant1_Value_bsax1tsxxz ,
& rtP . eitheredge_Value_lzvwtrli1x [ 0 ] , & rtP . negedge_Value_ackdjcny40
[ 0 ] , & rtP . posedge_Value_fsgb0grkvo [ 0 ] , & rtP .
Constant_Value_mvnfzatsby , & rtP . dnioykk3w1k . OUT_Y0 , & rtP .
d5zlt11l1pl . OUT_Y0 , & rtP . Constant_Value_izjuzrtanz , & rtP . fkhi333c1w
. OUT_Y0 , & rtP . gggqmave4q . OUT_Y0 , & rtP . Constant_Value_pmuy4epl2c ,
& rtP . mpycb0evfp . OUT_Y0 , & rtP . abmuy5rnsq . OUT_Y0 , & rtP .
mivhx1fvuuy . Out1_Y0 , & rtP . dyorcglstw . Out1_Y0 , & rtP . jiixgvrfhd .
Out1_Y0 , & rtP . Atenuacion_canal , & rtP . C , & rtP . Datos , & rtP .
Frec1 , & rtP . Frec2 , & rtP . R1 , & rtP . R2 , & rtP . Rb , & rtP .
Retraso_canal , & rtP . frecport1 , & rtP . kv , & rtP . kv2 , } ; static
int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
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
const uint_T rtDimensionArray [ ] = { 1 , 1 , 2 , 1 , 182 , 1 , 19 , 1 , 11 ,
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
rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 142 , ( NULL
) , 0 , ( NULL ) , 0 } , { rtBlockParameters , 141 , rtModelParameters , 12 }
, { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap , rtFixPtMap ,
rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float" , { 3625068466U
, 1078413989U , 1015600188U , 1100843694U } , ( NULL ) , 0 , 0 } ; const
rtwCAPI_ModelMappingStaticInfo * Multuplexacion_FDM_GetCAPIStaticMap ( void )
{ return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void Multuplexacion_FDM_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion (
( * rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
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
void Multuplexacion_FDM_host_InitializeDataMapInfo (
Multuplexacion_FDM_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , NULL ) ; rtwCAPI_SetPath (
dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
