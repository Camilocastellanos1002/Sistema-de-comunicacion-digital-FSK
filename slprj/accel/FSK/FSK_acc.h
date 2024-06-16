#ifndef RTW_HEADER_FSK_acc_h_
#define RTW_HEADER_FSK_acc_h_
#include <stddef.h>
#include <float.h>
#ifndef FSK_acc_COMMON_INCLUDES_
#define FSK_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "FSK_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
typedef struct { real_T B_3_0_0 ; } B_TriggeredSubsystem_FSK_T ; typedef
struct { int32_T TriggeredSubsystem_sysIdxToRun ; int8_T
TriggeredSubsystem_SubsysRanBC ; char_T pad_TriggeredSubsystem_SubsysRanBC [
3 ] ; } DW_TriggeredSubsystem_FSK_T ; typedef struct { real_T
TriggeredSubsystem_Trig_ZC ; } ZCV_TriggeredSubsystem_FSK_T ; typedef struct
{ ZCSigState TriggeredSubsystem_Trig_ZCE ; } ZCE_TriggeredSubsystem_FSK_T ;
typedef struct { boolean_T B_4_0_0 ; char_T pad_B_4_0_0 [ 7 ] ; }
B_NEGATIVEEdge_FSK_T ; typedef struct { int32_T NEGATIVEEdge_sysIdxToRun ;
int8_T NEGATIVEEdge_SubsysRanBC ; char_T pad_NEGATIVEEdge_SubsysRanBC [ 3 ] ;
} DW_NEGATIVEEdge_FSK_T ; typedef struct { boolean_T B_5_0_0 ; char_T
pad_B_5_0_0 [ 7 ] ; } B_POSITIVEEdge_FSK_T ; typedef struct { int32_T
POSITIVEEdge_sysIdxToRun ; int8_T POSITIVEEdge_SubsysRanBC ; char_T
pad_POSITIVEEdge_SubsysRanBC [ 3 ] ; } DW_POSITIVEEdge_FSK_T ; typedef struct
{ real_T B_14_1_0 ; real_T B_14_4_0 ; real_T B_14_6_0 ; real_T B_14_7_0 ;
real_T B_14_9_0 ; real_T B_14_12_0 ; real_T B_14_13_0 ; real_T B_14_19_0 ;
real_T B_14_24_0 ; real_T B_14_25_0 ; real_T B_14_26_0 ; real_T B_14_27_0 ;
real_T B_14_28_0 ; real_T B_14_31_0 ; real_T B_14_32_0 ; real_T B_14_36_0 ;
real_T B_14_39_0 ; real_T B_14_40_0 ; real_T B_14_41_0 ; real_T B_14_43_0 ;
real_T B_14_45_0 ; real_T B_14_47_0 ; real_T B_14_49_0 ; real_T B_14_51_0 ;
real_T B_14_53_0 ; real_T B_14_55_0 ; real_T B_14_57_0 ; real_T B_14_59_0 ;
real_T B_14_61_0 ; real_T B_14_65_0 ; real_T B_14_75_0 ; real_T B_14_76_0 ;
real_T B_14_77_0 ; real_T B_14_78_0 ; real_T B_14_80_0 ; real_T B_14_82_0 ;
real_T B_14_87_0 ; real_T B_14_90_0 ; real_T B_14_92_0 ; real_T B_14_100_0 ;
real_T B_14_101_0 ; real_T B_14_103_0 ; real_T B_14_105_0 ; real_T B_14_106_0
; real_T B_14_110_0 ; real_T B_14_117_0 ; real_T B_14_123_0 ; real_T
B_14_125_0 ; real_T B_14_126_0 ; real_T B_14_127_0 ; real_T B_14_128_0 ;
real_T B_14_129_0 ; real_T B_14_131_0 ; real_T B_14_133_0 ; real_T B_14_134_0
; real_T B_14_144_0 ; real_T B_14_145_0 ; real_T B_14_146_0 ; real_T
B_14_147_0 ; real_T B_14_151_0 ; real_T B_14_152_0 ; real_T B_14_162_0 ;
real_T B_14_163_0 ; real_T B_14_164_0 ; real_T B_14_165_0 ; real_T B_14_167_0
; real_T B_14_169_0 ; real_T B_14_173_0 ; real_T B_14_174_0 ; real_T
B_14_176_0 ; real_T B_14_178_0 ; real_T B_14_180_0 ; real_T B_14_0_0 ; real_T
B_14_1_0_m ; real_T B_14_2_0 ; real_T B_14_3_0 ; real_T B_14_4_0_c ; real_T
B_14_5_0 ; real_T B_14_6_0_k ; real_T B_14_7_0_c ; real_T B_14_8_0 ; real_T
B_14_9_0_b ; real_T B_14_10_0 ; real_T B_14_11_0 ; real_T B_14_12_0_p ;
real_T B_14_13_0_c ; real_T B_14_14_0 ; real_T B_14_15_0 ; real_T B_14_16_0 ;
real_T B_14_17_0 ; real_T B_14_18_0 ; real_T B_14_19_0_f ; real_T B_14_20_0 ;
real_T B_14_21_0 ; real_T B_14_22_0 ; real_T B_14_23_0 ; real_T B_14_24_0_g ;
real_T B_14_25_0_g ; real_T B_14_26_0_m ; real_T B_14_27_0_n ; real_T
B_14_28_0_p ; real_T B_14_29_0 ; real_T B_14_30_0 ; real_T B_14_31_0_l ;
real_T B_14_36_0_j [ 2 ] ; real_T B_14_37_0 ; real_T B_14_38_0 ; real_T
B_14_39_0_d ; real_T B_14_40_0_g ; real_T B_14_45_0_l [ 2 ] ; real_T
B_14_46_0 ; real_T B_14_51_0_d [ 2 ] ; real_T B_13_0_0 ; real_T B_12_0_0 ;
real_T B_0_0_0 ; boolean_T B_14_68_0 ; boolean_T B_14_73_0 ; boolean_T
B_14_79_0 ; boolean_T B_14_137_0 ; boolean_T B_14_142_0 ; boolean_T
B_14_148_0 ; boolean_T B_14_149_0 ; boolean_T B_14_155_0 ; boolean_T
B_14_160_0 ; boolean_T B_14_166_0 ; boolean_T B_2_0_0 ; char_T pad_B_2_0_0 [
5 ] ; B_POSITIVEEdge_FSK_T POSITIVEEdge_a ; B_NEGATIVEEdge_FSK_T
NEGATIVEEdge_o ; B_TriggeredSubsystem_FSK_T TriggeredSubsystem_g ;
B_POSITIVEEdge_FSK_T POSITIVEEdge_e ; B_NEGATIVEEdge_FSK_T NEGATIVEEdge_c ;
B_TriggeredSubsystem_FSK_T TriggeredSubsystem_d ; B_POSITIVEEdge_FSK_T
POSITIVEEdge ; B_NEGATIVEEdge_FSK_T NEGATIVEEdge ; B_TriggeredSubsystem_FSK_T
TriggeredSubsystem ; } B_FSK_T ; typedef struct { real_T NextOutput ; real_T
nextTime ; real_T ICic_PreviousInput ; real_T NextOutput_m ; real_T
ICic_PreviousInput_b ; real_T ICic_PreviousInput_a ; int64_T
numCompleteCycles ; struct { real_T modelTStart ; } TransportDelay_RWORK ;
struct { real_T modelTStart ; } TransportDelay_RWORK_p ; struct { real_T
modelTStart ; } TransportDelay_RWORK_e ; struct { real_T modelTStart ; }
TransportDelay_RWORK_g ; struct { real_T modelTStart ; }
TransportDelay12_RWORK ; struct { real_T modelTStart ; }
TransportDelay2_RWORK ; struct { real_T modelTStart ; } TransportDelay1_RWORK
; struct { real_T modelTStart ; } TransportDelay4_RWORK ; struct { real_T
modelTStart ; } TransportDelay3_RWORK ; struct { real_T modelTStart ; }
TransportDelay6_RWORK ; struct { real_T modelTStart ; } TransportDelay5_RWORK
; struct { real_T modelTStart ; } TransportDelay8_RWORK ; struct { real_T
modelTStart ; } TransportDelay7_RWORK ; struct { real_T modelTStart ; }
TransportDelay9_RWORK ; struct { real_T modelTStart ; }
TransportDelay11_RWORK ; struct { real_T modelTStart ; }
TransportDelay10_RWORK ; struct { real_T modelTStart ; }
TransportDelay13_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK_j ; struct { real_T modelTStart ; }
TransportDelay_RWORK_a ; struct { real_T modelTStart ; }
TransportDelay1_RWORK_d ; struct { real_T modelTStart ; }
TransportDelay1_RWORK_m ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK ; void * Scope_PWORK [ 3 ] ; void * Informacion_PWORK [
3 ] ; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_h ; struct
{ void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_c ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_c4 ; void * Scope_PWORK_e [ 2 ] ;
struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay12_PWORK ; struct { void
* TUbufferPtrs [ 2 ] ; } TransportDelay2_PWORK ; struct { void * TUbufferPtrs
[ 2 ] ; } TransportDelay1_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay4_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay3_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay6_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay5_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay8_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay7_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay9_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay11_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay10_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay13_PWORK ; void * Scope_PWORK_o ; void * Scope1_PWORK [ 2 ] ;
struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_o ; void *
Scope2_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_j
; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay1_PWORK_j ; void *
portadoras_PWORK [ 2 ] ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay1_PWORK_o ; void * Scope_PWORK_e3 [ 3 ] ; void * Scope_PWORK_op
[ 4 ] ; void * ToWorkspace_PWORK ; int32_T justEnabled ; int32_T currentValue
; int32_T SampleandHold1_sysIdxToRun ; int32_T SampleandHold_sysIdxToRun ;
int32_T SampleandHold_sysIdxToRun_m ; int32_T Mensajerecibido_sysIdxToRun ;
int32_T MuestreoyRetencion_sysIdxToRun ; uint32_T RandSeed ; uint32_T
RandSeed_m ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK ; int_T
Informacion_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_i ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_e ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_ic ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay12_IWORK ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay2_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay1_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay4_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay3_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay6_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay5_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay8_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay7_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay9_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay11_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay10_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay13_IWORK ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_g ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_ir ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay1_IWORK_d ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay1_IWORK_g ; int_T Sign_MODE ; int_T
Sign3_MODE ; int_T Abs1_MODE ; int8_T SampleandHold1_SubsysRanBC ; int8_T
SampleandHold_SubsysRanBC ; int8_T SampleandHold_SubsysRanBC_c ; int8_T
Mensajerecibido_SubsysRanBC ; int8_T MuestreoyRetencion_SubsysRanBC ;
boolean_T Compare_Mode ; boolean_T Memory_PreviousInput ; boolean_T
Switch_Mode ; boolean_T Switch1_Mode ; boolean_T Memory_PreviousInput_f ;
boolean_T RelationalOperator_Mode ; boolean_T RelationalOperator_Mode_a ;
boolean_T Memory_PreviousInput_b ; boolean_T Memory_PreviousInput_p ;
boolean_T RelationalOperator_Mode_m ; boolean_T Memory_PreviousInput_k ;
boolean_T Memory_PreviousInput_ke ; boolean_T RelationalOperator_Mode_i ;
boolean_T RelationalOperator_Mode_e ; boolean_T RelationalOperator_Mode_g ;
char_T pad_RelationalOperator_Mode_g [ 4 ] ; DW_POSITIVEEdge_FSK_T
POSITIVEEdge_a ; DW_NEGATIVEEdge_FSK_T NEGATIVEEdge_o ;
DW_TriggeredSubsystem_FSK_T TriggeredSubsystem_g ; DW_POSITIVEEdge_FSK_T
POSITIVEEdge_e ; DW_NEGATIVEEdge_FSK_T NEGATIVEEdge_c ;
DW_TriggeredSubsystem_FSK_T TriggeredSubsystem_d ; DW_POSITIVEEdge_FSK_T
POSITIVEEdge ; DW_NEGATIVEEdge_FSK_T NEGATIVEEdge ;
DW_TriggeredSubsystem_FSK_T TriggeredSubsystem ; } DW_FSK_T ; typedef struct
{ real_T Integrator_CSTATE ; real_T ModuloIntegrator_CSTATE ; real_T
Integrator_CSTATE_d ; real_T Filtro_CSTATE [ 4 ] ; real_T
ModuloIntegrator_CSTATE_j ; real_T Filtro_CSTATE_j [ 6 ] ; real_T
ModuloIntegrator_CSTATE_b ; real_T Integrator_CSTATE_p ; real_T
ModuloIntegrator_CSTATE_j0 ; real_T Integrator1_CSTATE ; real_T
Integrator_CSTATE_p0 ; real_T Integrator1_CSTATE_a ; } X_FSK_T ; typedef
int_T PeriodicIndX_FSK_T [ 4 ] ; typedef real_T PeriodicRngX_FSK_T [ 8 ] ;
typedef struct { real_T Integrator_CSTATE ; real_T ModuloIntegrator_CSTATE ;
real_T Integrator_CSTATE_d ; real_T Filtro_CSTATE [ 4 ] ; real_T
ModuloIntegrator_CSTATE_j ; real_T Filtro_CSTATE_j [ 6 ] ; real_T
ModuloIntegrator_CSTATE_b ; real_T Integrator_CSTATE_p ; real_T
ModuloIntegrator_CSTATE_j0 ; real_T Integrator1_CSTATE ; real_T
Integrator_CSTATE_p0 ; real_T Integrator1_CSTATE_a ; } XDot_FSK_T ; typedef
struct { boolean_T Integrator_CSTATE ; boolean_T ModuloIntegrator_CSTATE ;
boolean_T Integrator_CSTATE_d ; boolean_T Filtro_CSTATE [ 4 ] ; boolean_T
ModuloIntegrator_CSTATE_j ; boolean_T Filtro_CSTATE_j [ 6 ] ; boolean_T
ModuloIntegrator_CSTATE_b ; boolean_T Integrator_CSTATE_p ; boolean_T
ModuloIntegrator_CSTATE_j0 ; boolean_T Integrator1_CSTATE ; boolean_T
Integrator_CSTATE_p0 ; boolean_T Integrator1_CSTATE_a ; } XDis_FSK_T ;
typedef struct { real_T Integrator_CSTATE ; real_T ModuloIntegrator_CSTATE ;
real_T Integrator_CSTATE_d ; real_T Filtro_CSTATE [ 4 ] ; real_T
ModuloIntegrator_CSTATE_j ; real_T Filtro_CSTATE_j [ 6 ] ; real_T
ModuloIntegrator_CSTATE_b ; real_T Integrator_CSTATE_p ; real_T
ModuloIntegrator_CSTATE_j0 ; real_T Integrator1_CSTATE ; real_T
Integrator_CSTATE_p0 ; real_T Integrator1_CSTATE_a ; } CStateAbsTol_FSK_T ;
typedef struct { real_T Integrator_CSTATE ; real_T ModuloIntegrator_CSTATE ;
real_T Integrator_CSTATE_d ; real_T Filtro_CSTATE [ 4 ] ; real_T
ModuloIntegrator_CSTATE_j ; real_T Filtro_CSTATE_j [ 6 ] ; real_T
ModuloIntegrator_CSTATE_b ; real_T Integrator_CSTATE_p ; real_T
ModuloIntegrator_CSTATE_j0 ; real_T Integrator1_CSTATE ; real_T
Integrator_CSTATE_p0 ; real_T Integrator1_CSTATE_a ; } CXPtMin_FSK_T ;
typedef struct { real_T Integrator_CSTATE ; real_T ModuloIntegrator_CSTATE ;
real_T Integrator_CSTATE_d ; real_T Filtro_CSTATE [ 4 ] ; real_T
ModuloIntegrator_CSTATE_j ; real_T Filtro_CSTATE_j [ 6 ] ; real_T
ModuloIntegrator_CSTATE_b ; real_T Integrator_CSTATE_p ; real_T
ModuloIntegrator_CSTATE_j0 ; real_T Integrator1_CSTATE ; real_T
Integrator_CSTATE_p0 ; real_T Integrator1_CSTATE_a ; } CXPtMax_FSK_T ;
typedef struct { real_T Sign_Input_ZC ; real_T Integrator_Reset_ZC ; real_T
Compare_RelopInput_ZC ; real_T Switch_SwitchCond_ZC ; real_T
Switch1_SwitchCond_ZC ; real_T RelationalOperator_RelopInput_ZC ; real_T
Sign3_Input_ZC ; real_T RelationalOperator_RelopInput_ZC_g ; real_T
Integrator_Reset_ZC_e ; real_T RelationalOperator_RelopInput_ZC_c ; real_T
RelationalOperator_RelopInput_ZC_e ; real_T Integrator1_Reset_ZC ; real_T
Abs1_AbsZc_ZC ; real_T RelationalOperator_RelopInput_ZC_et ; real_T
RelationalOperator_RelopInput_ZC_j ; real_T SampleandHold1_Trig_ZC ; real_T
SampleandHold_Trig_ZC ; ZCV_TriggeredSubsystem_FSK_T TriggeredSubsystem_g ;
ZCV_TriggeredSubsystem_FSK_T TriggeredSubsystem_d ;
ZCV_TriggeredSubsystem_FSK_T TriggeredSubsystem ; real_T
SampleandHold_Trig_ZC_k ; real_T Mensajerecibido_Trig_ZC ; real_T
MuestreoyRetencion_Trig_ZC ; } ZCV_FSK_T ; typedef struct { ZCSigState
Sign_Input_ZCE ; ZCSigState Integrator_Reset_ZCE ; ZCSigState
Compare_RelopInput_ZCE ; ZCSigState Switch_SwitchCond_ZCE ; ZCSigState
Switch1_SwitchCond_ZCE ; ZCSigState RelationalOperator_RelopInput_ZCE ;
ZCSigState Sign3_Input_ZCE ; ZCSigState RelationalOperator_RelopInput_ZCE_b ;
ZCSigState Integrator_Reset_ZCE_n ; ZCSigState
RelationalOperator_RelopInput_ZCE_c ; ZCSigState
RelationalOperator_RelopInput_ZCE_j ; ZCSigState Integrator1_Reset_ZCE ;
ZCSigState Abs1_AbsZc_ZCE ; ZCSigState RelationalOperator_RelopInput_ZCE_a ;
ZCSigState RelationalOperator_RelopInput_ZCE_k ; ZCSigState
SampleandHold1_Trig_ZCE ; ZCSigState SampleandHold_Trig_ZCE ;
ZCE_TriggeredSubsystem_FSK_T TriggeredSubsystem_g ;
ZCE_TriggeredSubsystem_FSK_T TriggeredSubsystem_d ;
ZCE_TriggeredSubsystem_FSK_T TriggeredSubsystem ; ZCSigState
SampleandHold_Trig_ZCE_k ; ZCSigState Mensajerecibido_Trig_ZCE ; ZCSigState
MuestreoyRetencion_Trig_ZCE ; } PrevZCX_FSK_T ; struct
P_TriggeredSubsystem_FSK_T_ { real_T P_0 ; } ; struct P_FSK_T_ { real_T P_0 ;
real_T P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ;
real_T P_7 ; real_T P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11 [ 7 ] ;
real_T P_12 ; real_T P_13 ; real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T
P_17 ; real_T P_18 ; real_T P_19 ; real_T P_20 ; real_T P_21 ; real_T P_22 ;
real_T P_23 ; real_T P_24 ; real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T
P_28 ; real_T P_29 ; real_T P_30 ; real_T P_31 ; real_T P_32 ; real_T P_33 ;
real_T P_34 ; real_T P_35 ; real_T P_36 ; real_T P_37 ; real_T P_38 ; real_T
P_39 ; real_T P_40 ; real_T P_41 ; real_T P_42 ; real_T P_43 ; real_T P_44 ;
real_T P_45 ; real_T P_46 ; real_T P_47 ; real_T P_48 ; real_T P_49 ; real_T
P_50 ; real_T P_51 ; real_T P_52 ; real_T P_53 ; real_T P_54 ; real_T P_55 ;
real_T P_56 ; real_T P_57 ; real_T P_58 ; real_T P_59 ; real_T P_60 ; real_T
P_61 ; real_T P_62 ; real_T P_63 ; real_T P_64 ; real_T P_65 ; real_T P_66 [
11 ] ; real_T P_67 ; real_T P_68 ; real_T P_69 ; real_T P_70 ; real_T P_71 ;
real_T P_72 ; real_T P_73 ; real_T P_74 ; real_T P_75 ; real_T P_76 ; real_T
P_77 ; real_T P_78 ; real_T P_79 ; real_T P_80 ; real_T P_81 ; real_T P_82 ;
real_T P_83 ; real_T P_84 ; real_T P_85 ; real_T P_86 ; real_T P_87 ; real_T
P_88 ; real_T P_89 ; real_T P_90 ; real_T P_91 ; real_T P_92 ; real_T P_93 ;
real_T P_94 ; real_T P_95 ; real_T P_96 ; real_T P_97 ; real_T P_98 ; real_T
P_99 ; real_T P_100 ; real_T P_101 ; real_T P_102 ; real_T P_103 ; real_T
P_104 ; real_T P_105 ; real_T P_106 ; real_T P_107 ; real_T P_108 ; real_T
P_109 ; real_T P_110 ; real_T P_111 ; real_T P_112 ; real_T P_113 ; real_T
P_114 ; real_T P_115 ; real_T P_116 ; real_T P_117 ; real_T P_118 ; real_T
P_119 ; real_T P_120 ; real_T P_121 ; real_T P_122 ; real_T P_123 ; real_T
P_124 ; real_T P_125 ; real_T P_126 ; real_T P_127 ; real_T P_128 ; real_T
P_129 ; real_T P_130 ; real_T P_131 ; real_T P_132 ; real_T P_133 ; real_T
P_134 ; real_T P_135 ; real_T P_136 [ 2 ] ; real_T P_137 [ 2 ] ; real_T P_138
[ 2 ] ; real_T P_139 ; real_T P_140 ; real_T P_141 ; real_T P_142 ; real_T
P_143 ; real_T P_144 [ 2 ] ; real_T P_145 [ 2 ] ; real_T P_146 [ 2 ] ; real_T
P_147 ; real_T P_148 ; real_T P_149 [ 2 ] ; real_T P_150 [ 2 ] ; real_T P_151
[ 2 ] ; boolean_T P_152 ; boolean_T P_153 ; boolean_T P_154 ; boolean_T P_155
; boolean_T P_156 ; boolean_T P_157 ; boolean_T P_158 ; char_T pad_P_158 [ 1
] ; P_TriggeredSubsystem_FSK_T TriggeredSubsystem_g ;
P_TriggeredSubsystem_FSK_T TriggeredSubsystem_d ; P_TriggeredSubsystem_FSK_T
TriggeredSubsystem ; } ; extern P_FSK_T FSK_rtDefaultP ;
#endif
