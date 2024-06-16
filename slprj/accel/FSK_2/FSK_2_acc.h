#ifndef RTW_HEADER_FSK_2_acc_h_
#define RTW_HEADER_FSK_2_acc_h_
#include <stddef.h>
#include <float.h>
#ifndef FSK_2_acc_COMMON_INCLUDES_
#define FSK_2_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "FSK_2_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
typedef struct { real_T B_0_0_0 ; } B_MuestreoyRetencion_FSK_2_T ; typedef
struct { int32_T MuestreoyRetencion_sysIdxToRun ; int8_T
MuestreoyRetencion_SubsysRanBC ; char_T pad_MuestreoyRetencion_SubsysRanBC [
3 ] ; } DW_MuestreoyRetencion_FSK_2_T ; typedef struct { real_T
MuestreoyRetencion_Trig_ZC ; } ZCV_MuestreoyRetencion_FSK_2_T ; typedef
struct { ZCSigState MuestreoyRetencion_Trig_ZCE ; }
ZCE_MuestreoyRetencion_FSK_2_T ; typedef struct { boolean_T B_3_0_0 ; char_T
pad_B_3_0_0 [ 7 ] ; } B_SampleandHold_FSK_2_T ; typedef struct { int32_T
SampleandHold_sysIdxToRun ; int8_T SampleandHold_SubsysRanBC ; char_T
pad_SampleandHold_SubsysRanBC [ 3 ] ; } DW_SampleandHold_FSK_2_T ; typedef
struct { real_T SampleandHold_Trig_ZC_n ; } ZCV_SampleandHold_FSK_2_T ;
typedef struct { ZCSigState SampleandHold_Trig_ZCE_b ; }
ZCE_SampleandHold_FSK_2_T ; typedef struct { real_T B_4_0_0 ; }
B_TriggeredSubsystem_FSK_2_T ; typedef struct { int32_T
TriggeredSubsystem_sysIdxToRun ; int8_T TriggeredSubsystem_SubsysRanBC ;
char_T pad_TriggeredSubsystem_SubsysRanBC [ 3 ] ; }
DW_TriggeredSubsystem_FSK_2_T ; typedef struct { real_T
TriggeredSubsystem_Trig_ZC ; } ZCV_TriggeredSubsystem_FSK_2_T ; typedef
struct { ZCSigState TriggeredSubsystem_Trig_ZCE ; }
ZCE_TriggeredSubsystem_FSK_2_T ; typedef struct { boolean_T B_5_0_0 ; char_T
pad_B_5_0_0 [ 7 ] ; } B_NEGATIVEEdge_FSK_2_T ; typedef struct { int32_T
NEGATIVEEdge_sysIdxToRun ; int8_T NEGATIVEEdge_SubsysRanBC ; char_T
pad_NEGATIVEEdge_SubsysRanBC [ 3 ] ; } DW_NEGATIVEEdge_FSK_2_T ; typedef
struct { boolean_T B_6_0_0 ; char_T pad_B_6_0_0 [ 7 ] ; }
B_POSITIVEEdge_FSK_2_T ; typedef struct { int32_T POSITIVEEdge_sysIdxToRun ;
int8_T POSITIVEEdge_SubsysRanBC ; char_T pad_POSITIVEEdge_SubsysRanBC [ 3 ] ;
} DW_POSITIVEEdge_FSK_2_T ; typedef struct { real_T B_13_0_0 ; }
B_SampleandHold_FSK_2_h_T ; typedef struct { int32_T
SampleandHold_sysIdxToRun ; int8_T SampleandHold_SubsysRanBC ; char_T
pad_SampleandHold_SubsysRanBC [ 3 ] ; } DW_SampleandHold_FSK_2_n_T ; typedef
struct { real_T SampleandHold_Trig_ZC ; } ZCV_SampleandHold_FSK_2_o_T ;
typedef struct { ZCSigState SampleandHold_Trig_ZCE ; }
ZCE_SampleandHold_FSK_2_h_T ; typedef struct { real_T B_14_0_0 ; }
B_SampleandHold1_FSK_2_T ; typedef struct { int32_T
SampleandHold1_sysIdxToRun ; int8_T SampleandHold1_SubsysRanBC ; char_T
pad_SampleandHold1_SubsysRanBC [ 3 ] ; } DW_SampleandHold1_FSK_2_T ; typedef
struct { real_T SampleandHold1_Trig_ZC ; } ZCV_SampleandHold1_FSK_2_T ;
typedef struct { ZCSigState SampleandHold1_Trig_ZCE ; }
ZCE_SampleandHold1_FSK_2_T ; typedef struct { real_T B_28_0_0 ; real_T
B_28_3_0 ; real_T B_28_5_0 ; real_T B_28_6_0 ; real_T B_28_7_0 ; real_T
B_28_10_0 ; real_T B_28_12_0 ; real_T B_28_13_0 ; real_T B_28_16_0 ; real_T
B_28_19_0 ; real_T B_28_21_0 ; real_T B_28_22_0 ; real_T B_28_32_0 ; real_T
B_28_35_0 ; real_T B_28_40_0 ; real_T B_28_41_0 ; real_T B_28_42_0 ; real_T
B_28_43_0 ; real_T B_28_46_0 ; real_T B_28_49_0 ; real_T B_28_50_0 ; real_T
B_28_55_0 ; real_T B_28_58_0 ; real_T B_28_59_0 ; real_T B_28_63_0 ; real_T
B_28_66_0 ; real_T B_28_67_0 ; real_T B_28_68_0 ; real_T B_28_70_0 ; real_T
B_28_72_0 ; real_T B_28_74_0 ; real_T B_28_76_0 ; real_T B_28_78_0 ; real_T
B_28_80_0 ; real_T B_28_82_0 ; real_T B_28_84_0 ; real_T B_28_86_0 ; real_T
B_28_88_0 ; real_T B_28_92_0 ; real_T B_28_102_0 ; real_T B_28_103_0 ; real_T
B_28_104_0 ; real_T B_28_105_0 ; real_T B_28_107_0 ; real_T B_28_111_0 ;
real_T B_28_113_0 ; real_T B_28_115_0 ; real_T B_28_125_0 ; real_T B_28_126_0
; real_T B_28_128_0 ; real_T B_28_130_0 ; real_T B_28_131_0 ; real_T
B_28_135_0 ; real_T B_28_142_0 ; real_T B_28_148_0 ; real_T B_28_150_0 ;
real_T B_28_151_0 ; real_T B_28_152_0 ; real_T B_28_153_0 ; real_T B_28_154_0
; real_T B_28_156_0 ; real_T B_28_158_0 ; real_T B_28_159_0 ; real_T
B_28_169_0 ; real_T B_28_170_0 ; real_T B_28_171_0 ; real_T B_28_172_0 ;
real_T B_28_176_0 ; real_T B_28_177_0 ; real_T B_28_187_0 ; real_T B_28_188_0
; real_T B_28_189_0 ; real_T B_28_190_0 ; real_T B_28_192_0 ; real_T
B_28_194_0 ; real_T B_28_198_0 ; real_T B_28_199_0 ; real_T B_28_201_0 ;
real_T B_28_203_0 ; real_T B_28_205_0 ; real_T B_28_208_0 ; real_T B_28_211_0
; real_T B_28_212_0 ; real_T B_28_213_0 ; real_T B_28_215_0 ; real_T
B_28_217_0 ; real_T B_28_219_0 ; real_T B_28_221_0 ; real_T B_28_223_0 ;
real_T B_28_225_0 ; real_T B_28_227_0 ; real_T B_28_229_0 ; real_T B_28_231_0
; real_T B_28_233_0 ; real_T B_28_237_0 ; real_T B_28_247_0 ; real_T
B_28_248_0 ; real_T B_28_249_0 ; real_T B_28_250_0 ; real_T B_28_252_0 ;
real_T B_28_256_0 ; real_T B_28_258_0 ; real_T B_28_260_0 ; real_T B_28_270_0
; real_T B_28_271_0 ; real_T B_28_273_0 ; real_T B_28_275_0 ; real_T
B_28_276_0 ; real_T B_28_280_0 ; real_T B_28_287_0 ; real_T B_28_293_0 ;
real_T B_28_295_0 ; real_T B_28_296_0 ; real_T B_28_297_0 ; real_T B_28_298_0
; real_T B_28_299_0 ; real_T B_28_301_0 ; real_T B_28_303_0 ; real_T
B_28_304_0 ; real_T B_28_314_0 ; real_T B_28_315_0 ; real_T B_28_316_0 ;
real_T B_28_317_0 ; real_T B_28_321_0 ; real_T B_28_322_0 ; real_T B_28_332_0
; real_T B_28_333_0 ; real_T B_28_334_0 ; real_T B_28_335_0 ; real_T
B_28_337_0 ; real_T B_28_339_0 ; real_T B_28_343_0 ; real_T B_28_344_0 ;
real_T B_28_346_0 ; real_T B_28_348_0 ; real_T B_28_350_0 ; real_T B_28_0_0_m
; real_T B_28_1_0 ; real_T B_28_2_0 ; real_T B_28_3_0_c ; real_T B_28_4_0 ;
real_T B_28_5_0_k ; real_T B_28_6_0_c ; real_T B_28_7_0_b ; real_T B_28_8_0 ;
real_T B_28_9_0 ; real_T B_28_10_0_p ; real_T B_28_11_0 ; real_T B_28_12_0_c
; real_T B_28_13_0_f ; real_T B_28_14_0 ; real_T B_28_15_0 ; real_T
B_28_16_0_g ; real_T B_28_17_0 ; real_T B_28_18_0 ; real_T B_28_19_0_g ;
real_T B_28_20_0 ; real_T B_28_21_0_m ; real_T B_28_22_0_n ; real_T B_28_23_0
; real_T B_28_24_0 ; real_T B_28_25_0 ; real_T B_28_26_0 ; real_T B_28_27_0 ;
real_T B_28_28_0 ; real_T B_28_29_0 ; real_T B_28_30_0 ; real_T B_28_31_0 ;
real_T B_28_32_0_p ; real_T B_28_33_0 ; real_T B_28_38_0 [ 2 ] ; real_T
B_28_39_0 ; real_T B_28_40_0_l ; real_T B_28_41_0_j ; real_T B_28_42_0_d ;
real_T B_28_47_0 [ 2 ] ; real_T B_28_48_0 ; real_T B_28_53_0 [ 2 ] ; real_T
B_28_54_0 ; real_T B_28_55_0_g ; real_T B_28_56_0 ; real_T B_28_57_0 ; real_T
B_28_58_0_l ; real_T B_28_59_0_d ; real_T B_28_60_0 ; real_T B_28_61_0 ;
real_T B_28_62_0 ; real_T B_28_63_0_d ; real_T B_28_64_0 ; real_T B_28_65_0 ;
real_T B_28_66_0_l ; real_T B_28_67_0_o ; real_T B_28_68_0_b ; real_T
B_28_69_0 ; real_T B_28_70_0_n ; real_T B_28_71_0 ; real_T B_28_72_0_b ;
real_T B_28_73_0 ; real_T B_28_74_0_l ; real_T B_28_75_0 ; real_T B_28_76_0_h
; real_T B_28_77_0 ; real_T B_28_78_0_b ; real_T B_28_79_0 ; real_T
B_28_80_0_d ; real_T B_28_81_0 ; real_T B_28_82_0_e ; real_T B_28_83_0 ;
real_T B_28_88_0_b [ 2 ] ; real_T B_28_89_0 ; real_T B_28_90_0 ; real_T
B_28_91_0 ; real_T B_28_92_0_j ; real_T B_28_97_0 [ 2 ] ; real_T B_28_98_0 ;
real_T B_28_103_0_f [ 2 ] ; boolean_T B_28_95_0 ; boolean_T B_28_100_0 ;
boolean_T B_28_106_0 ; boolean_T B_28_162_0 ; boolean_T B_28_167_0 ;
boolean_T B_28_173_0 ; boolean_T B_28_174_0 ; boolean_T B_28_180_0 ;
boolean_T B_28_185_0 ; boolean_T B_28_191_0 ; boolean_T B_28_240_0 ;
boolean_T B_28_245_0 ; boolean_T B_28_251_0 ; boolean_T B_28_307_0 ;
boolean_T B_28_312_0 ; boolean_T B_28_318_0 ; boolean_T B_28_319_0 ;
boolean_T B_28_325_0 ; boolean_T B_28_330_0 ; boolean_T B_28_336_0 ; char_T
pad_B_28_336_0 [ 4 ] ; B_SampleandHold1_FSK_2_T SampleandHold1_l ;
B_SampleandHold_FSK_2_h_T SampleandHold_i ; B_POSITIVEEdge_FSK_2_T
POSITIVEEdge_o ; B_NEGATIVEEdge_FSK_2_T NEGATIVEEdge_a ;
B_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_mf ; B_POSITIVEEdge_FSK_2_T
POSITIVEEdge_m ; B_NEGATIVEEdge_FSK_2_T NEGATIVEEdge_g ;
B_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_c ; B_POSITIVEEdge_FSK_2_T
POSITIVEEdge_p ; B_NEGATIVEEdge_FSK_2_T NEGATIVEEdge_kl ;
B_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_m ; B_SampleandHold_FSK_2_T
SampleandHold_j ; B_SampleandHold1_FSK_2_T SampleandHold1 ;
B_SampleandHold_FSK_2_h_T SampleandHold_c ; B_POSITIVEEdge_FSK_2_T
POSITIVEEdge_d ; B_NEGATIVEEdge_FSK_2_T NEGATIVEEdge_k ;
B_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_p ; B_POSITIVEEdge_FSK_2_T
POSITIVEEdge_b ; B_NEGATIVEEdge_FSK_2_T NEGATIVEEdge_i ;
B_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_f ; B_POSITIVEEdge_FSK_2_T
POSITIVEEdge ; B_NEGATIVEEdge_FSK_2_T NEGATIVEEdge ;
B_TriggeredSubsystem_FSK_2_T TriggeredSubsystem ; B_SampleandHold_FSK_2_T
SampleandHold ; B_MuestreoyRetencion_FSK_2_T MuestreoyRetencion_e ;
B_MuestreoyRetencion_FSK_2_T MuestreoyRetencion ; } B_FSK_2_T ; typedef
struct { real_T NextOutput ; real_T nextTime ; real_T nextTime_i ; real_T
ICic_PreviousInput ; real_T NextOutput_k ; real_T ICic_PreviousInput_k ;
real_T ICic_PreviousInput_p ; real_T ICic_PreviousInput_i ; real_T
NextOutput_c ; real_T ICic_PreviousInput_c ; real_T ICic_PreviousInput_cq ;
int64_T numCompleteCycles ; int64_T numCompleteCycles_a ; struct { real_T
modelTStart ; } TransportDelay_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK_n ; struct { real_T modelTStart ; }
TransportDelay_RWORK_e ; struct { real_T modelTStart ; }
TransportDelay_RWORK_d ; struct { real_T modelTStart ; }
TransportDelay_RWORK_nj ; struct { real_T modelTStart ; }
TransportDelay_RWORK_b ; struct { real_T modelTStart ; }
TransportDelay_RWORK_h ; struct { real_T modelTStart ; }
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
TransportDelay_RWORK_i ; struct { real_T modelTStart ; }
TransportDelay1_RWORK_m ; struct { real_T modelTStart ; }
TransportDelay_RWORK_j ; struct { real_T modelTStart ; }
TransportDelay1_RWORK_h ; struct { real_T modelTStart ; }
TransportDelay12_RWORK_g ; struct { real_T modelTStart ; }
TransportDelay2_RWORK_p ; struct { real_T modelTStart ; }
TransportDelay1_RWORK_o ; struct { real_T modelTStart ; }
TransportDelay4_RWORK_h ; struct { real_T modelTStart ; }
TransportDelay3_RWORK_o ; struct { real_T modelTStart ; }
TransportDelay6_RWORK_m ; struct { real_T modelTStart ; }
TransportDelay5_RWORK_i ; struct { real_T modelTStart ; }
TransportDelay8_RWORK_n ; struct { real_T modelTStart ; }
TransportDelay7_RWORK_m ; struct { real_T modelTStart ; }
TransportDelay9_RWORK_n ; struct { real_T modelTStart ; }
TransportDelay11_RWORK_c ; struct { real_T modelTStart ; }
TransportDelay10_RWORK_l ; struct { real_T modelTStart ; }
TransportDelay13_RWORK_j ; struct { real_T modelTStart ; }
TransportDelay_RWORK_dp ; struct { real_T modelTStart ; }
TransportDelay1_RWORK_hj ; struct { real_T modelTStart ; }
TransportDelay_RWORK_di ; struct { real_T modelTStart ; }
TransportDelay1_RWORK_i ; void * Informacion_PWORK [ 3 ] ; void *
Informacion1_PWORK [ 3 ] ; void * Comparaciondemensajes_PWORK [ 4 ] ; void *
Tx1yRx1_PWORK [ 3 ] ; void * Tx2yRx2_PWORK [ 3 ] ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void * TUbufferPtrs [
2 ] ; } TransportDelay_PWORK_m ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_c ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_k ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_ky ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_p ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_f ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay12_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay2_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay1_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay4_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay3_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay6_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay5_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay8_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay7_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay9_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay11_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay10_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay13_PWORK ; void * Scope1_PWORK [ 2 ] ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_h ; struct { void * TUbufferPtrs
[ 2 ] ; } TransportDelay1_PWORK_m ; void * portadoras_PWORK [ 2 ] ; struct {
void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_i ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay1_PWORK_b ; void * Scope_PWORK [ 3 ] ;
void * Scope_PWORK_b [ 4 ] ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay12_PWORK_m ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay2_PWORK_m ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay1_PWORK_l ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay4_PWORK_b ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay3_PWORK_n ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay6_PWORK_f ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay5_PWORK_h ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay8_PWORK_g ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay7_PWORK_b ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay9_PWORK_k ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay11_PWORK_h ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay10_PWORK_l ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay13_PWORK_j ; void * Scope1_PWORK_c [ 2 ] ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_cv ; struct { void * TUbufferPtrs
[ 2 ] ; } TransportDelay1_PWORK_i ; void * portadoras_PWORK_c [ 2 ] ; struct
{ void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_c5 ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay1_PWORK_mk ; void * Scope_PWORK_n [ 3 ]
; void * Scope_PWORK_m [ 4 ] ; void * ToWorkspace_PWORK ; void *
ToWorkspace_PWORK_e ; int32_T justEnabled ; int32_T currentValue ; int32_T
justEnabled_o ; int32_T currentValue_h ; int32_T Mensajerecibido_sysIdxToRun
; int32_T Mensajerecibido_sysIdxToRun_i ; uint32_T RandSeed ; uint32_T
RandSeed_i ; uint32_T RandSeed_e ; int_T Informacion_IWORK ; int_T
Informacion1_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_a ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_e ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_o ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_g ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_m ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_d ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay12_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay2_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay1_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay4_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay3_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay6_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay5_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay8_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay7_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay9_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay11_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay10_IWORK ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay13_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_at ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay1_IWORK_p ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_i ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay1_IWORK_h ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay12_IWORK_f ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay2_IWORK_j ; struct { int_T Tail ; int_T Head
; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay1_IWORK_e ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay4_IWORK_h ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay3_IWORK_e ; struct { int_T Tail ; int_T Head
; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay6_IWORK_a ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay5_IWORK_l ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay8_IWORK_a ; struct { int_T Tail ; int_T Head
; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay7_IWORK_d ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay9_IWORK_e ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay11_IWORK_c ; struct { int_T Tail ; int_T Head
; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay10_IWORK_o ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay13_IWORK_m ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_k ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay1_IWORK_i ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_gq ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay1_IWORK_b ; int_T Sign_MODE ; int_T
Sign_MODE_d ; int_T Sign3_MODE ; int_T Abs1_MODE ; int_T Sign3_MODE_e ; int_T
Abs1_MODE_c ; int8_T Mensajerecibido_SubsysRanBC ; int8_T
Mensajerecibido_SubsysRanBC_d ; boolean_T Compare_Mode ; boolean_T
Compare_Mode_d ; boolean_T Memory_PreviousInput ; boolean_T Switch_Mode ;
boolean_T Switch1_Mode ; boolean_T Memory_PreviousInput_b ; boolean_T
RelationalOperator_Mode ; boolean_T RelationalOperator_Mode_l ; boolean_T
Memory_PreviousInput_k ; boolean_T Memory_PreviousInput_n ; boolean_T
RelationalOperator_Mode_o ; boolean_T Memory_PreviousInput_kl ; boolean_T
Memory_PreviousInput_j ; boolean_T RelationalOperator_Mode_b ; boolean_T
RelationalOperator_Mode_by ; boolean_T RelationalOperator_Mode_n ; boolean_T
Memory_PreviousInput_h ; boolean_T Switch_Mode_m ; boolean_T Switch1_Mode_a ;
boolean_T Memory_PreviousInput_e ; boolean_T RelationalOperator_Mode_j ;
boolean_T RelationalOperator_Mode_d ; boolean_T Memory_PreviousInput_jr ;
boolean_T Memory_PreviousInput_l ; boolean_T RelationalOperator_Mode_d2 ;
boolean_T Memory_PreviousInput_a ; boolean_T Memory_PreviousInput_bb ;
boolean_T RelationalOperator_Mode_k ; boolean_T RelationalOperator_Mode_g ;
boolean_T RelationalOperator_Mode_du ; DW_SampleandHold1_FSK_2_T
SampleandHold1_l ; DW_SampleandHold_FSK_2_n_T SampleandHold_i ;
DW_POSITIVEEdge_FSK_2_T POSITIVEEdge_o ; DW_NEGATIVEEdge_FSK_2_T
NEGATIVEEdge_a ; DW_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_mf ;
DW_POSITIVEEdge_FSK_2_T POSITIVEEdge_m ; DW_NEGATIVEEdge_FSK_2_T
NEGATIVEEdge_g ; DW_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_c ;
DW_POSITIVEEdge_FSK_2_T POSITIVEEdge_p ; DW_NEGATIVEEdge_FSK_2_T
NEGATIVEEdge_kl ; DW_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_m ;
DW_SampleandHold_FSK_2_T SampleandHold_j ; DW_SampleandHold1_FSK_2_T
SampleandHold1 ; DW_SampleandHold_FSK_2_n_T SampleandHold_c ;
DW_POSITIVEEdge_FSK_2_T POSITIVEEdge_d ; DW_NEGATIVEEdge_FSK_2_T
NEGATIVEEdge_k ; DW_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_p ;
DW_POSITIVEEdge_FSK_2_T POSITIVEEdge_b ; DW_NEGATIVEEdge_FSK_2_T
NEGATIVEEdge_i ; DW_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_f ;
DW_POSITIVEEdge_FSK_2_T POSITIVEEdge ; DW_NEGATIVEEdge_FSK_2_T NEGATIVEEdge ;
DW_TriggeredSubsystem_FSK_2_T TriggeredSubsystem ; DW_SampleandHold_FSK_2_T
SampleandHold ; DW_MuestreoyRetencion_FSK_2_T MuestreoyRetencion_e ;
DW_MuestreoyRetencion_FSK_2_T MuestreoyRetencion ; } DW_FSK_2_T ; typedef
struct { real_T ModuloIntegrator_CSTATE ; real_T Integrator_CSTATE ; real_T
ModuloIntegrator_CSTATE_k ; real_T Integrator_CSTATE_n ; real_T
Integrator_CSTATE_l ; real_T Integrator_CSTATE_j ; real_T
AnalogFilterDesign_CSTATE [ 10 ] ; real_T AnalogFilterDesign2_CSTATE [ 10 ] ;
real_T ModuloIntegrator_CSTATE_kx ; real_T ModuloIntegrator_CSTATE_h ; real_T
Filtro_CSTATE [ 6 ] ; real_T ModuloIntegrator_CSTATE_l ; real_T
Integrator_CSTATE_o ; real_T ModuloIntegrator_CSTATE_e ; real_T
Integrator1_CSTATE ; real_T Integrator_CSTATE_a ; real_T Integrator1_CSTATE_c
; real_T Filtro_CSTATE_b [ 6 ] ; real_T ModuloIntegrator_CSTATE_c ; real_T
Integrator_CSTATE_jg ; real_T ModuloIntegrator_CSTATE_a ; real_T
Integrator1_CSTATE_cy ; real_T Integrator_CSTATE_om ; real_T
Integrator1_CSTATE_e ; } X_FSK_2_T ; typedef int_T PeriodicIndX_FSK_2_T [ 8 ]
; typedef real_T PeriodicRngX_FSK_2_T [ 16 ] ; typedef struct { real_T
ModuloIntegrator_CSTATE ; real_T Integrator_CSTATE ; real_T
ModuloIntegrator_CSTATE_k ; real_T Integrator_CSTATE_n ; real_T
Integrator_CSTATE_l ; real_T Integrator_CSTATE_j ; real_T
AnalogFilterDesign_CSTATE [ 10 ] ; real_T AnalogFilterDesign2_CSTATE [ 10 ] ;
real_T ModuloIntegrator_CSTATE_kx ; real_T ModuloIntegrator_CSTATE_h ; real_T
Filtro_CSTATE [ 6 ] ; real_T ModuloIntegrator_CSTATE_l ; real_T
Integrator_CSTATE_o ; real_T ModuloIntegrator_CSTATE_e ; real_T
Integrator1_CSTATE ; real_T Integrator_CSTATE_a ; real_T Integrator1_CSTATE_c
; real_T Filtro_CSTATE_b [ 6 ] ; real_T ModuloIntegrator_CSTATE_c ; real_T
Integrator_CSTATE_jg ; real_T ModuloIntegrator_CSTATE_a ; real_T
Integrator1_CSTATE_cy ; real_T Integrator_CSTATE_om ; real_T
Integrator1_CSTATE_e ; } XDot_FSK_2_T ; typedef struct { boolean_T
ModuloIntegrator_CSTATE ; boolean_T Integrator_CSTATE ; boolean_T
ModuloIntegrator_CSTATE_k ; boolean_T Integrator_CSTATE_n ; boolean_T
Integrator_CSTATE_l ; boolean_T Integrator_CSTATE_j ; boolean_T
AnalogFilterDesign_CSTATE [ 10 ] ; boolean_T AnalogFilterDesign2_CSTATE [ 10
] ; boolean_T ModuloIntegrator_CSTATE_kx ; boolean_T
ModuloIntegrator_CSTATE_h ; boolean_T Filtro_CSTATE [ 6 ] ; boolean_T
ModuloIntegrator_CSTATE_l ; boolean_T Integrator_CSTATE_o ; boolean_T
ModuloIntegrator_CSTATE_e ; boolean_T Integrator1_CSTATE ; boolean_T
Integrator_CSTATE_a ; boolean_T Integrator1_CSTATE_c ; boolean_T
Filtro_CSTATE_b [ 6 ] ; boolean_T ModuloIntegrator_CSTATE_c ; boolean_T
Integrator_CSTATE_jg ; boolean_T ModuloIntegrator_CSTATE_a ; boolean_T
Integrator1_CSTATE_cy ; boolean_T Integrator_CSTATE_om ; boolean_T
Integrator1_CSTATE_e ; } XDis_FSK_2_T ; typedef struct { real_T
ModuloIntegrator_CSTATE ; real_T Integrator_CSTATE ; real_T
ModuloIntegrator_CSTATE_k ; real_T Integrator_CSTATE_n ; real_T
Integrator_CSTATE_l ; real_T Integrator_CSTATE_j ; real_T
AnalogFilterDesign_CSTATE [ 10 ] ; real_T AnalogFilterDesign2_CSTATE [ 10 ] ;
real_T ModuloIntegrator_CSTATE_kx ; real_T ModuloIntegrator_CSTATE_h ; real_T
Filtro_CSTATE [ 6 ] ; real_T ModuloIntegrator_CSTATE_l ; real_T
Integrator_CSTATE_o ; real_T ModuloIntegrator_CSTATE_e ; real_T
Integrator1_CSTATE ; real_T Integrator_CSTATE_a ; real_T Integrator1_CSTATE_c
; real_T Filtro_CSTATE_b [ 6 ] ; real_T ModuloIntegrator_CSTATE_c ; real_T
Integrator_CSTATE_jg ; real_T ModuloIntegrator_CSTATE_a ; real_T
Integrator1_CSTATE_cy ; real_T Integrator_CSTATE_om ; real_T
Integrator1_CSTATE_e ; } CStateAbsTol_FSK_2_T ; typedef struct { real_T
ModuloIntegrator_CSTATE ; real_T Integrator_CSTATE ; real_T
ModuloIntegrator_CSTATE_k ; real_T Integrator_CSTATE_n ; real_T
Integrator_CSTATE_l ; real_T Integrator_CSTATE_j ; real_T
AnalogFilterDesign_CSTATE [ 10 ] ; real_T AnalogFilterDesign2_CSTATE [ 10 ] ;
real_T ModuloIntegrator_CSTATE_kx ; real_T ModuloIntegrator_CSTATE_h ; real_T
Filtro_CSTATE [ 6 ] ; real_T ModuloIntegrator_CSTATE_l ; real_T
Integrator_CSTATE_o ; real_T ModuloIntegrator_CSTATE_e ; real_T
Integrator1_CSTATE ; real_T Integrator_CSTATE_a ; real_T Integrator1_CSTATE_c
; real_T Filtro_CSTATE_b [ 6 ] ; real_T ModuloIntegrator_CSTATE_c ; real_T
Integrator_CSTATE_jg ; real_T ModuloIntegrator_CSTATE_a ; real_T
Integrator1_CSTATE_cy ; real_T Integrator_CSTATE_om ; real_T
Integrator1_CSTATE_e ; } CXPtMin_FSK_2_T ; typedef struct { real_T
ModuloIntegrator_CSTATE ; real_T Integrator_CSTATE ; real_T
ModuloIntegrator_CSTATE_k ; real_T Integrator_CSTATE_n ; real_T
Integrator_CSTATE_l ; real_T Integrator_CSTATE_j ; real_T
AnalogFilterDesign_CSTATE [ 10 ] ; real_T AnalogFilterDesign2_CSTATE [ 10 ] ;
real_T ModuloIntegrator_CSTATE_kx ; real_T ModuloIntegrator_CSTATE_h ; real_T
Filtro_CSTATE [ 6 ] ; real_T ModuloIntegrator_CSTATE_l ; real_T
Integrator_CSTATE_o ; real_T ModuloIntegrator_CSTATE_e ; real_T
Integrator1_CSTATE ; real_T Integrator_CSTATE_a ; real_T Integrator1_CSTATE_c
; real_T Filtro_CSTATE_b [ 6 ] ; real_T ModuloIntegrator_CSTATE_c ; real_T
Integrator_CSTATE_jg ; real_T ModuloIntegrator_CSTATE_a ; real_T
Integrator1_CSTATE_cy ; real_T Integrator_CSTATE_om ; real_T
Integrator1_CSTATE_e ; } CXPtMax_FSK_2_T ; typedef struct { real_T
Sign_Input_ZC ; real_T Integrator_Reset_ZC ; real_T Sign_Input_ZC_o ; real_T
Integrator_Reset_ZC_e ; real_T Compare_RelopInput_ZC ; real_T
Compare_RelopInput_ZC_g ; real_T Switch_SwitchCond_ZC ; real_T
Switch1_SwitchCond_ZC ; real_T RelationalOperator_RelopInput_ZC ; real_T
Sign3_Input_ZC ; real_T RelationalOperator_RelopInput_ZC_d ; real_T
Integrator_Reset_ZC_c ; real_T RelationalOperator_RelopInput_ZC_c ; real_T
RelationalOperator_RelopInput_ZC_o ; real_T Integrator1_Reset_ZC ; real_T
Abs1_AbsZc_ZC ; real_T RelationalOperator_RelopInput_ZC_k ; real_T
RelationalOperator_RelopInput_ZC_j ; real_T Switch_SwitchCond_ZC_d ; real_T
Switch1_SwitchCond_ZC_b ; real_T RelationalOperator_RelopInput_ZC_p ; real_T
Sign3_Input_ZC_d ; real_T RelationalOperator_RelopInput_ZC_pq ; real_T
Integrator_Reset_ZC_m ; real_T RelationalOperator_RelopInput_ZC_b ; real_T
RelationalOperator_RelopInput_ZC_g ; real_T Integrator1_Reset_ZC_j ; real_T
Abs1_AbsZc_ZC_h ; real_T RelationalOperator_RelopInput_ZC_jd ; real_T
RelationalOperator_RelopInput_ZC_e ; ZCV_SampleandHold1_FSK_2_T
SampleandHold1_l ; ZCV_SampleandHold_FSK_2_o_T SampleandHold_i ;
ZCV_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_mf ;
ZCV_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_c ;
ZCV_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_m ;
ZCV_SampleandHold_FSK_2_T SampleandHold_j ; real_T Mensajerecibido_Trig_ZC ;
ZCV_SampleandHold1_FSK_2_T SampleandHold1 ; ZCV_SampleandHold_FSK_2_o_T
SampleandHold_c ; ZCV_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_p ;
ZCV_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_f ;
ZCV_TriggeredSubsystem_FSK_2_T TriggeredSubsystem ; ZCV_SampleandHold_FSK_2_T
SampleandHold ; real_T Mensajerecibido_Trig_ZC_l ;
ZCV_MuestreoyRetencion_FSK_2_T MuestreoyRetencion_e ;
ZCV_MuestreoyRetencion_FSK_2_T MuestreoyRetencion ; } ZCV_FSK_2_T ; typedef
struct { ZCSigState Sign_Input_ZCE ; ZCSigState Integrator_Reset_ZCE ;
ZCSigState Sign_Input_ZCE_f ; ZCSigState Integrator_Reset_ZCE_d ; ZCSigState
Compare_RelopInput_ZCE ; ZCSigState Compare_RelopInput_ZCE_b ; ZCSigState
Switch_SwitchCond_ZCE ; ZCSigState Switch1_SwitchCond_ZCE ; ZCSigState
RelationalOperator_RelopInput_ZCE ; ZCSigState Sign3_Input_ZCE ; ZCSigState
RelationalOperator_RelopInput_ZCE_m ; ZCSigState Integrator_Reset_ZCE_l ;
ZCSigState RelationalOperator_RelopInput_ZCE_j ; ZCSigState
RelationalOperator_RelopInput_ZCE_c ; ZCSigState Integrator1_Reset_ZCE ;
ZCSigState Abs1_AbsZc_ZCE ; ZCSigState RelationalOperator_RelopInput_ZCE_h ;
ZCSigState RelationalOperator_RelopInput_ZCE_hn ; ZCSigState
Switch_SwitchCond_ZCE_h ; ZCSigState Switch1_SwitchCond_ZCE_k ; ZCSigState
RelationalOperator_RelopInput_ZCE_p ; ZCSigState Sign3_Input_ZCE_k ;
ZCSigState RelationalOperator_RelopInput_ZCE_e ; ZCSigState
Integrator_Reset_ZCE_h ; ZCSigState RelationalOperator_RelopInput_ZCE_k ;
ZCSigState RelationalOperator_RelopInput_ZCE_kt ; ZCSigState
Integrator1_Reset_ZCE_i ; ZCSigState Abs1_AbsZc_ZCE_k ; ZCSigState
RelationalOperator_RelopInput_ZCE_kw ; ZCSigState
RelationalOperator_RelopInput_ZCE_ey ; ZCE_SampleandHold1_FSK_2_T
SampleandHold1_l ; ZCE_SampleandHold_FSK_2_h_T SampleandHold_i ;
ZCE_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_mf ;
ZCE_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_c ;
ZCE_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_m ;
ZCE_SampleandHold_FSK_2_T SampleandHold_j ; ZCSigState
Mensajerecibido_Trig_ZCE ; ZCE_SampleandHold1_FSK_2_T SampleandHold1 ;
ZCE_SampleandHold_FSK_2_h_T SampleandHold_c ; ZCE_TriggeredSubsystem_FSK_2_T
TriggeredSubsystem_p ; ZCE_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_f ;
ZCE_TriggeredSubsystem_FSK_2_T TriggeredSubsystem ; ZCE_SampleandHold_FSK_2_T
SampleandHold ; ZCSigState Mensajerecibido_Trig_ZCE_p ;
ZCE_MuestreoyRetencion_FSK_2_T MuestreoyRetencion_e ;
ZCE_MuestreoyRetencion_FSK_2_T MuestreoyRetencion ; } PrevZCX_FSK_2_T ;
struct P_MuestreoyRetencion_FSK_2_T_ { real_T P_0 ; } ; struct
P_SampleandHold_FSK_2_T_ { boolean_T P_0 ; char_T pad_P_0 [ 7 ] ; } ; struct
P_TriggeredSubsystem_FSK_2_T_ { real_T P_0 ; } ; struct
P_SampleandHold_FSK_2_n_T_ { real_T P_0 ; } ; struct
P_SampleandHold1_FSK_2_T_ { real_T P_0 ; } ; struct P_FSK_2_T_ { real_T P_0 ;
real_T P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ;
real_T P_7 ; real_T P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T
P_12 [ 19 ] ; real_T P_13 ; real_T P_14 ; real_T P_15 ; real_T P_16 [ 19 ] ;
real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T P_20 ; real_T P_21 ; real_T
P_22 ; real_T P_23 ; real_T P_24 ; real_T P_25 ; real_T P_26 ; real_T P_27 ;
real_T P_28 ; real_T P_29 ; real_T P_30 ; real_T P_31 ; real_T P_32 ; real_T
P_33 ; real_T P_34 ; real_T P_35 ; real_T P_36 ; real_T P_37 ; real_T P_38 ;
real_T P_39 ; real_T P_40 ; real_T P_41 ; real_T P_42 ; real_T P_43 ; real_T
P_44 ; real_T P_45 ; real_T P_46 ; real_T P_47 ; real_T P_48 ; real_T P_49 ;
real_T P_50 ; real_T P_51 ; real_T P_52 ; real_T P_53 ; real_T P_54 ; real_T
P_55 ; real_T P_56 ; real_T P_57 ; real_T P_58 ; real_T P_59 ; real_T P_60 ;
real_T P_61 ; real_T P_62 ; real_T P_63 ; real_T P_64 ; real_T P_65 ; real_T
P_66 ; real_T P_67 ; real_T P_68 ; real_T P_69 ; real_T P_70 ; real_T P_71 ;
real_T P_72 ; real_T P_73 ; real_T P_74 ; real_T P_75 ; real_T P_76 ; real_T
P_77 ; real_T P_78 ; real_T P_79 ; real_T P_80 ; real_T P_81 ; real_T P_82 ;
real_T P_83 ; real_T P_84 ; real_T P_85 ; real_T P_86 ; real_T P_87 ; real_T
P_88 ; real_T P_89 ; real_T P_90 ; real_T P_91 ; real_T P_92 ; real_T P_93 [
11 ] ; real_T P_94 ; real_T P_95 ; real_T P_96 ; real_T P_97 ; real_T P_98 ;
real_T P_99 ; real_T P_100 ; real_T P_101 ; real_T P_102 ; real_T P_103 ;
real_T P_104 ; real_T P_105 ; real_T P_106 ; real_T P_107 ; real_T P_108 ;
real_T P_109 ; real_T P_110 ; real_T P_111 ; real_T P_112 ; real_T P_113 ;
real_T P_114 ; real_T P_115 ; real_T P_116 ; real_T P_117 ; real_T P_118 ;
real_T P_119 ; real_T P_120 ; real_T P_121 ; real_T P_122 ; real_T P_123 ;
real_T P_124 ; real_T P_125 ; real_T P_126 ; real_T P_127 ; real_T P_128 ;
real_T P_129 ; real_T P_130 ; real_T P_131 ; real_T P_132 ; real_T P_133 ;
real_T P_134 ; real_T P_135 ; real_T P_136 ; real_T P_137 ; real_T P_138 ;
real_T P_139 ; real_T P_140 ; real_T P_141 ; real_T P_142 ; real_T P_143 ;
real_T P_144 ; real_T P_145 ; real_T P_146 ; real_T P_147 ; real_T P_148 ;
real_T P_149 ; real_T P_150 ; real_T P_151 ; real_T P_152 ; real_T P_153 ;
real_T P_154 ; real_T P_155 ; real_T P_156 ; real_T P_157 ; real_T P_158 ;
real_T P_159 ; real_T P_160 [ 11 ] ; real_T P_161 ; real_T P_162 ; real_T
P_163 ; real_T P_164 ; real_T P_165 ; real_T P_166 ; real_T P_167 ; real_T
P_168 ; real_T P_169 ; real_T P_170 ; real_T P_171 ; real_T P_172 ; real_T
P_173 ; real_T P_174 ; real_T P_175 ; real_T P_176 ; real_T P_177 ; real_T
P_178 ; real_T P_179 ; real_T P_180 ; real_T P_181 ; real_T P_182 ; real_T
P_183 ; real_T P_184 ; real_T P_185 ; real_T P_186 ; real_T P_187 ; real_T
P_188 ; real_T P_189 ; real_T P_190 ; real_T P_191 ; real_T P_192 ; real_T
P_193 ; real_T P_194 ; real_T P_195 ; real_T P_196 ; real_T P_197 ; real_T
P_198 ; real_T P_199 ; real_T P_200 ; real_T P_201 ; real_T P_202 ; real_T
P_203 ; real_T P_204 ; real_T P_205 ; real_T P_206 ; real_T P_207 ; real_T
P_208 ; real_T P_209 ; real_T P_210 ; real_T P_211 ; real_T P_212 ; real_T
P_213 ; real_T P_214 ; real_T P_215 ; real_T P_216 ; real_T P_217 ; real_T
P_218 ; real_T P_219 ; real_T P_220 ; real_T P_221 ; real_T P_222 ; real_T
P_223 ; real_T P_224 ; real_T P_225 ; real_T P_226 [ 2 ] ; real_T P_227 [ 2 ]
; real_T P_228 [ 2 ] ; real_T P_229 ; real_T P_230 ; real_T P_231 ; real_T
P_232 ; real_T P_233 ; real_T P_234 [ 2 ] ; real_T P_235 [ 2 ] ; real_T P_236
[ 2 ] ; real_T P_237 ; real_T P_238 ; real_T P_239 [ 2 ] ; real_T P_240 [ 2 ]
; real_T P_241 [ 2 ] ; real_T P_242 ; real_T P_243 ; real_T P_244 ; real_T
P_245 ; real_T P_246 ; real_T P_247 ; real_T P_248 ; real_T P_249 ; real_T
P_250 ; real_T P_251 ; real_T P_252 ; real_T P_253 ; real_T P_254 ; real_T
P_255 ; real_T P_256 ; real_T P_257 ; real_T P_258 ; real_T P_259 ; real_T
P_260 ; real_T P_261 ; real_T P_262 ; real_T P_263 ; real_T P_264 ; real_T
P_265 ; real_T P_266 ; real_T P_267 ; real_T P_268 ; real_T P_269 ; real_T
P_270 ; real_T P_271 ; real_T P_272 ; real_T P_273 [ 2 ] ; real_T P_274 [ 2 ]
; real_T P_275 [ 2 ] ; real_T P_276 ; real_T P_277 ; real_T P_278 ; real_T
P_279 ; real_T P_280 ; real_T P_281 [ 2 ] ; real_T P_282 [ 2 ] ; real_T P_283
[ 2 ] ; real_T P_284 ; real_T P_285 ; real_T P_286 [ 2 ] ; real_T P_287 [ 2 ]
; real_T P_288 [ 2 ] ; boolean_T P_289 ; boolean_T P_290 ; boolean_T P_291 ;
boolean_T P_292 ; boolean_T P_293 ; boolean_T P_294 ; boolean_T P_295 ;
boolean_T P_296 ; boolean_T P_297 ; boolean_T P_298 ; boolean_T P_299 ;
boolean_T P_300 ; char_T pad_P_300 [ 4 ] ; P_SampleandHold1_FSK_2_T
SampleandHold1_l ; P_SampleandHold_FSK_2_n_T SampleandHold_i ;
P_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_mf ;
P_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_c ;
P_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_m ; P_SampleandHold_FSK_2_T
SampleandHold_j ; P_SampleandHold1_FSK_2_T SampleandHold1 ;
P_SampleandHold_FSK_2_n_T SampleandHold_c ; P_TriggeredSubsystem_FSK_2_T
TriggeredSubsystem_p ; P_TriggeredSubsystem_FSK_2_T TriggeredSubsystem_f ;
P_TriggeredSubsystem_FSK_2_T TriggeredSubsystem ; P_SampleandHold_FSK_2_T
SampleandHold ; P_MuestreoyRetencion_FSK_2_T MuestreoyRetencion_e ;
P_MuestreoyRetencion_FSK_2_T MuestreoyRetencion ; } ; extern P_FSK_2_T
FSK_2_rtDefaultP ;
#endif
