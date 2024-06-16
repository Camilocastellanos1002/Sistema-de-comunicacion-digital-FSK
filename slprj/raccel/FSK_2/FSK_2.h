#ifndef RTW_HEADER_FSK_2_h_
#define RTW_HEADER_FSK_2_h_
#include <string.h>
#include <stddef.h>
#include <float.h>
#include "rtw_modelmap.h"
#ifndef FSK_2_COMMON_INCLUDES_
#define FSK_2_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "sigstream_rtw.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "FSK_2_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME FSK_2
#define NSAMPLE_TIMES (5) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (10) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (22)   
#elif NCSTATES != 22
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T bdmiwmnwdi ; real_T a2ej4vwwfz ; real_T cydck3mxyr ;
real_T ixhdtyqkuo ; real_T dzdmp2qvuc ; real_T a1nwn30zom ; real_T pxelcov220
; real_T br52h0oi5h ; real_T clkvycwj4m ; real_T o0un153nbh ; } B ; typedef
struct { real_T osax4czyvz ; struct { real_T modelTStart ; } ahatirdp3v ;
struct { real_T modelTStart ; } nkby1sxpuw ; struct { real_T modelTStart ; }
fhwaru4dxv ; struct { void * TimePtr ; void * DataPtr ; void * RSimInfoPtr ;
} i00x1wwgsf ; struct { void * LoggedData [ 2 ] ; } bmmqaeqn53 ; struct {
void * TimePtr ; void * DataPtr ; void * RSimInfoPtr ; } jf1myj4gvp ; struct
{ void * LoggedData [ 2 ] ; } ozc2tf4c2y ; struct { void * TUbufferPtrs [ 2 ]
; } aw2n3f4po1 ; struct { void * TUbufferPtrs [ 2 ] ; } bmxd34jmp4 ; struct {
void * TUbufferPtrs [ 2 ] ; } haguqrracw ; struct { void * LoggedData [ 2 ] ;
} pqkcete42o ; uint32_T ezauhd3tt0 ; struct { int_T PrevIndex ; } h4rggrbxnc
; struct { int_T PrevIndex ; } powianu2bz ; struct { int_T Tail ; int_T Head
; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; } oxfi1zw3ko ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } engssbe05o ; struct { int_T Tail ; int_T Head ; int_T Last
; int_T CircularBufSize ; int_T MaxNewBufSize ; } m0cwy3q4nt ; } DW ; typedef
struct { real_T ay2evnqozi [ 10 ] ; real_T efzaicakgx [ 10 ] ; real_T
hpywvdhwlx ; real_T dmykij4zst ; } X ; typedef int_T PeriodicIndX [ 2 ] ;
typedef real_T PeriodicRngX [ 4 ] ; typedef struct { real_T ay2evnqozi [ 10 ]
; real_T efzaicakgx [ 10 ] ; real_T hpywvdhwlx ; real_T dmykij4zst ; } XDot ;
typedef struct { boolean_T ay2evnqozi [ 10 ] ; boolean_T efzaicakgx [ 10 ] ;
boolean_T hpywvdhwlx ; boolean_T dmykij4zst ; } XDis ; typedef struct {
real_T ay2evnqozi [ 10 ] ; real_T efzaicakgx [ 10 ] ; real_T hpywvdhwlx ;
real_T dmykij4zst ; } CStateAbsTol ; typedef struct { real_T ay2evnqozi [ 10
] ; real_T efzaicakgx [ 10 ] ; real_T hpywvdhwlx ; real_T dmykij4zst ; }
CXPtMin ; typedef struct { real_T ay2evnqozi [ 10 ] ; real_T efzaicakgx [ 10
] ; real_T hpywvdhwlx ; real_T dmykij4zst ; } CXPtMax ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T
Atenuacion_canal ; real_T Frec2 ; real_T Frec4 ; real_T Rb ; real_T
Retraso_canal ; real_T frec ; real_T GaussianNoiseGenerator_d ; real_T
GaussianNoiseGenerator_m ; real_T GaussianNoiseGenerator_s ; real_T
Informacion_Data0 [ 182 ] ; real_T AnalogFilterDesign_A [ 19 ] ; real_T
AnalogFilterDesign_B ; real_T AnalogFilterDesign_C ; real_T
AnalogFilterDesign_InitialCondition ; real_T AnalogFilterDesign2_A [ 19 ] ;
real_T AnalogFilterDesign2_B ; real_T AnalogFilterDesign2_C ; real_T
AnalogFilterDesign2_InitialCondition ; real_T Informacion1_Data0 [ 182 ] ;
real_T ModuloIntegrator_IC ; real_T ModuloIntegrator_WrappedStateUpperValue ;
real_T ModuloIntegrator_WrappedStateLowerValue ; real_T SineWave_Amp ; real_T
SineWave_Bias ; real_T SineWave_Phase ; real_T ModuloIntegrator_IC_p52dz1dzx0
; real_T ModuloIntegrator_WrappedStateUpperValue_kbmmwvx1uc ; real_T
ModuloIntegrator_WrappedStateLowerValue_mg14ul40s3 ; real_T
TransportDelay_Delay ; real_T TransportDelay_InitOutput ; real_T
TransportDelay_Delay_mpjovd0fow ; real_T TransportDelay_InitOutput_erb5xkljw0
; real_T TransportDelay_InitOutput_npzkuu2dfa ; real_T RandomNumber_Mean ;
real_T RandomNumber_StdDev ; real_T Buffer_ic ; } ; extern const char *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX ; extern DW rtDW ;
extern P rtP ; extern const rtwCAPI_ModelMappingStaticInfo *
FSK_2_GetCAPIStaticMap ( void ) ; extern SimStruct * const rtS ; extern const
int_T gblNumToFiles ; extern const int_T gblNumFrFiles ; extern const int_T
gblNumFrWksBlocks ; extern rtInportTUtable * gblInportTUtables ; extern const
char * gblInportFileName ; extern const int_T gblNumRootInportBlks ; extern
const int_T gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ;
extern const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [
] ; extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( void
) ;
#endif
