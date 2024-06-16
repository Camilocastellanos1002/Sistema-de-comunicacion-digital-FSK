#ifndef RTW_HEADER_FSK_h_
#define RTW_HEADER_FSK_h_
#include <string.h>
#include <stddef.h>
#include <float.h>
#include "rtw_modelmap.h"
#ifndef FSK_COMMON_INCLUDES_
#define FSK_COMMON_INCLUDES_
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
#include "FSK_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_zcfcn.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME FSK
#define NSAMPLE_TIMES (6) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (93) 
#define NUM_ZC_EVENTS (11) 
#ifndef NCSTATES
#define NCSTATES (20)   
#elif NCSTATES != 20
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
typedef struct { real_T jzxmgvajvp ; } cagpp1qjpe ; typedef struct { int8_T
b4uftfd3jt ; } cjdwzvmo5b ; typedef struct { real_T iulwoctycu ; } fdijpttqf5
; typedef struct { ZCSigState htztm3ejkl ; } bg3mtgiacz ; typedef struct {
boolean_T ighgnitevw ; } fu5bk3bmay ; typedef struct { int8_T mnrpt53zog ; }
gmd13fthxk ; typedef struct { boolean_T ddvcjkqoaj ; } impou4x0jn ; typedef
struct { int8_T bl2ajkrwzq ; } nyhc31mepi ; typedef struct { real_T
hao2kgiuqu ; real_T iea4dkyy2w ; real_T bui2nj5eby ; real_T f5hdbpawyv ;
real_T mr1s0bxcpp ; real_T ghegbffnb0 ; real_T echlwz23fd ; real_T ong5vjnb0y
; real_T iyoofertyx ; real_T brw1yh1ujs ; real_T ibhjdwhj0b ; real_T
i1k4ywizrv ; real_T geskkhqdb3 ; real_T gfobd5zpxv ; real_T jmi5xid0ph ;
real_T jknu1nrhnz ; real_T kwwqn5rlhs ; real_T aemhoq5few ; real_T dkfpnckao5
; real_T fnydnbixk1 ; real_T lbeln3akc2 ; real_T jw32jpeck5 ; real_T
n5sbv1oypg ; real_T m22qmdpsyj ; real_T aqj0wixgbx ; real_T hjpiowuzne ;
real_T d2paa5zotr ; real_T f2wibvryef ; real_T jp5azcgtac ; real_T hagpe2nohf
; real_T kj3rknv443 ; real_T axx1cycxep ; real_T dxcynwwxat ; real_T
hpuvpoamzd ; real_T cqkmv0ulyy ; real_T fcjlyowfli ; real_T hs1qpln3nc ;
real_T e15ao1bk3m ; real_T ooknyqiljy ; real_T ijufvlmorm ; real_T jsr2vw3sph
; real_T d1ncaq24su ; real_T mzfkqi1te1 ; real_T nvde5gnl32 ; real_T
inulkftw3y ; real_T pdl3oaaxvv ; real_T bbud2xrwvw ; real_T nhklduoiog ;
real_T ik1ga1yi4x ; real_T mpss00ytce ; real_T iuiswtbqno ; real_T ctnzwjmcme
; real_T kkn0pryfbs ; real_T oarcyjxd4w ; real_T h3jkxjjtu0 ; real_T
lwvzpms5bv ; real_T oru1g5vkau ; real_T jiqtvtg4mt ; real_T fwzg1qmdog ;
real_T kaaziuo5ef ; real_T jwmjcxympi ; real_T ma2rvcr4nq ; real_T akirm2mhww
; real_T ftsmahysaw ; real_T furzsgxei5 ; real_T kp4mtdwxq5 ; real_T
bd1h4kdhj0 ; real_T f2kmaedy0v [ 2 ] ; real_T btp22atm5y [ 2 ] ; real_T
hg4tfoauyd [ 2 ] ; real_T fmyjxkxyji ; real_T lzdd3z4ueb ; real_T jmfd3dtamo
; boolean_T cbutxn4e51 ; boolean_T n5sddkmaty ; boolean_T bnbr20jdr4 ;
boolean_T mdla3lhngq ; boolean_T lisqze2m0v ; boolean_T akkrfuecb2 ;
boolean_T cpzsxqkvzb ; boolean_T pk0yjglikg ; boolean_T hu24p5k4qk ;
boolean_T plthkbxpdz ; boolean_T m4lv3kzihg ; impou4x0jn cvrfqtrsgv ;
fu5bk3bmay b5dbwkwsrj ; cagpp1qjpe cc2aoo0nhc ; impou4x0jn cfrh4agkgq ;
fu5bk3bmay awkevlz2ww ; cagpp1qjpe dzgncmrria ; impou4x0jn edzbs02xos1 ;
fu5bk3bmay fqkin25shtk ; cagpp1qjpe jgvwez5knrn ; } B ; typedef struct {
real_T dzchlxvwf3 ; real_T akzvs10hux ; real_T lzar0ld5iq ; real_T kqtr3qx2r4
; real_T f2j0l3sxg1 ; real_T nea0jvgp55 ; int64_T j5zzyh4rpr ; struct {
real_T modelTStart ; } pjddaatqz2 ; struct { real_T modelTStart ; }
hnsh4hlcjf ; struct { real_T modelTStart ; } aodjfyn1vf ; struct { real_T
modelTStart ; } glkz222vzv ; struct { real_T modelTStart ; } ncjovmrbg0 ;
struct { real_T modelTStart ; } klfxndpfsg ; struct { real_T modelTStart ; }
d14s1qzuzq ; struct { real_T modelTStart ; } mxv0osx2ez ; struct { real_T
modelTStart ; } ppmbxq52ac ; struct { real_T modelTStart ; } f0yw54erky ;
struct { real_T modelTStart ; } gpmkh0kcin ; struct { real_T modelTStart ; }
bdb0yzd0st ; struct { real_T modelTStart ; } btck01pmwp ; struct { real_T
modelTStart ; } balgznqrxg ; struct { real_T modelTStart ; } phjdmexj3l ;
struct { real_T modelTStart ; } la2whjw243 ; struct { real_T modelTStart ; }
nqs2szczzo ; struct { real_T modelTStart ; } nxgqhfx5gi ; struct { real_T
modelTStart ; } jszw02sccm ; struct { real_T modelTStart ; } c3s5d5tdbo ;
struct { real_T modelTStart ; } pvm13mlbpg ; struct { void * LoggedData [ 2 ]
; } m12hjeojxl ; struct { void * TimePtr ; void * DataPtr ; void *
RSimInfoPtr ; } ap5xq1jhre ; struct { void * TUbufferPtrs [ 2 ] ; }
lv2dzfblr1 ; struct { void * TUbufferPtrs [ 2 ] ; } ifklj3sbrn ; struct {
void * TUbufferPtrs [ 2 ] ; } hd1c30tkpp ; struct { void * TUbufferPtrs [ 2 ]
; } ge2wwzjib2 ; struct { void * TUbufferPtrs [ 2 ] ; } jshlet2ssp ; struct {
void * TUbufferPtrs [ 2 ] ; } pkzvqa1hj0 ; struct { void * TUbufferPtrs [ 2 ]
; } pviiww4mxm ; struct { void * TUbufferPtrs [ 2 ] ; } dwlf21fnwg ; struct {
void * TUbufferPtrs [ 2 ] ; } bnamprjobf ; struct { void * TUbufferPtrs [ 2 ]
; } lrrduccxok ; struct { void * TUbufferPtrs [ 2 ] ; } fhjti1tiah ; struct {
void * TUbufferPtrs [ 2 ] ; } faivwg4izm ; struct { void * TUbufferPtrs [ 2 ]
; } lw4b5iw0r0 ; struct { void * TUbufferPtrs [ 2 ] ; } nhj2clh5pd ; struct {
void * TUbufferPtrs [ 2 ] ; } d1uhchttm1 ; struct { void * TUbufferPtrs [ 2 ]
; } egilahlbnt ; struct { void * TUbufferPtrs [ 2 ] ; } lxhyqkdxwz ; struct {
void * TUbufferPtrs [ 2 ] ; } a4exivx0tt ; struct { void * TUbufferPtrs [ 2 ]
; } idcmakdjdp ; struct { void * LoggedData [ 4 ] ; } j12ztdudf4 ; struct {
void * LoggedData [ 4 ] ; } nyj02hk5rd ; struct { void * TUbufferPtrs [ 2 ] ;
} btwgfjuhwu ; struct { void * TUbufferPtrs [ 2 ] ; } mfdffnmnea ; struct {
void * LoggedData [ 2 ] ; } e10ua2pcif ; struct { void * LoggedData ; }
ovsyej354z ; int32_T n2ufwbrgzx ; int32_T ljyjgojejj ; uint32_T dwuhp2thuf ;
uint32_T h4m3xflze4 ; struct { int_T PrevIndex ; } ob0eo32bes ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } eioayfkhqd ; struct { int_T Tail ; int_T Head ; int_T Last
; int_T CircularBufSize ; int_T MaxNewBufSize ; } hpphhvjiqw ; struct { int_T
Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize
; } pjaubi5g0r ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } gtgggrpqsb ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
gfgr3iktyl ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } pttsc0t4lz ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
eppzhodfly ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } josactzshu ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
c3xd1ms0us ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } odb4cbppzt ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
deeamvwgxv ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } ftsaljquvy ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
h0kavv2rvj ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } orr2azrxe5 ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
mrknrsmtwp ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } hdikw2z4pb ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
oqom4bvhu5 ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } fpoqultkeo ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
iexysxku45 ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } ivfrpj5iet ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
hklidk4rmf ; int_T oib2ggiaac ; int_T cb1jfiyqqe ; int_T jhkfehrm4t ; int8_T
og5vligtf5 ; int8_T jsih34lehs ; int8_T juqugykvvp ; int8_T nwsijekr51 ;
int8_T lomcfztmre ; boolean_T brpeccm2su ; boolean_T bybwcm2hrx ; boolean_T
ltwnscr23j ; boolean_T f3anteups0 ; boolean_T p0mgrctrnl ; boolean_T
i5mfbygyll ; boolean_T kwcxzpft0d ; boolean_T ljvna4i1sk ; boolean_T
en3gkuykg0 ; boolean_T c22fq5hb2l ; boolean_T isfsg2jso1 ; boolean_T
ht5i5wmo5i ; boolean_T dmhkjfkzni ; boolean_T giqgg3q5tt ; boolean_T
g31sjopxfu ; nyhc31mepi cvrfqtrsgv ; gmd13fthxk b5dbwkwsrj ; cjdwzvmo5b
cc2aoo0nhc ; nyhc31mepi cfrh4agkgq ; gmd13fthxk awkevlz2ww ; cjdwzvmo5b
dzgncmrria ; nyhc31mepi edzbs02xos1 ; gmd13fthxk fqkin25shtk ; cjdwzvmo5b
jgvwez5knrn ; } DW ; typedef struct { real_T npfxxayysv ; real_T nnu2myvywh ;
real_T pmpdgrmizb ; real_T fdnkcpfqw2 [ 4 ] ; real_T mjardhsaxq ; real_T
iz0hdnziyp [ 6 ] ; real_T gusjeimfuy ; real_T ocmfulb5j3 ; real_T nk03khymzz
; real_T hqbabu1dqz ; real_T lpsjm2psah ; real_T inqcqvaw3b ; } X ; typedef
int_T PeriodicIndX [ 4 ] ; typedef real_T PeriodicRngX [ 8 ] ; typedef struct
{ real_T npfxxayysv ; real_T nnu2myvywh ; real_T pmpdgrmizb ; real_T
fdnkcpfqw2 [ 4 ] ; real_T mjardhsaxq ; real_T iz0hdnziyp [ 6 ] ; real_T
gusjeimfuy ; real_T ocmfulb5j3 ; real_T nk03khymzz ; real_T hqbabu1dqz ;
real_T lpsjm2psah ; real_T inqcqvaw3b ; } XDot ; typedef struct { boolean_T
npfxxayysv ; boolean_T nnu2myvywh ; boolean_T pmpdgrmizb ; boolean_T
fdnkcpfqw2 [ 4 ] ; boolean_T mjardhsaxq ; boolean_T iz0hdnziyp [ 6 ] ;
boolean_T gusjeimfuy ; boolean_T ocmfulb5j3 ; boolean_T nk03khymzz ;
boolean_T hqbabu1dqz ; boolean_T lpsjm2psah ; boolean_T inqcqvaw3b ; } XDis ;
typedef struct { real_T npfxxayysv ; real_T nnu2myvywh ; real_T pmpdgrmizb ;
real_T fdnkcpfqw2 [ 4 ] ; real_T mjardhsaxq ; real_T iz0hdnziyp [ 6 ] ;
real_T gusjeimfuy ; real_T ocmfulb5j3 ; real_T nk03khymzz ; real_T hqbabu1dqz
; real_T lpsjm2psah ; real_T inqcqvaw3b ; } CStateAbsTol ; typedef struct {
real_T npfxxayysv ; real_T nnu2myvywh ; real_T pmpdgrmizb ; real_T fdnkcpfqw2
[ 4 ] ; real_T mjardhsaxq ; real_T iz0hdnziyp [ 6 ] ; real_T gusjeimfuy ;
real_T ocmfulb5j3 ; real_T nk03khymzz ; real_T hqbabu1dqz ; real_T lpsjm2psah
; real_T inqcqvaw3b ; } CXPtMin ; typedef struct { real_T npfxxayysv ; real_T
nnu2myvywh ; real_T pmpdgrmizb ; real_T fdnkcpfqw2 [ 4 ] ; real_T mjardhsaxq
; real_T iz0hdnziyp [ 6 ] ; real_T gusjeimfuy ; real_T ocmfulb5j3 ; real_T
nk03khymzz ; real_T hqbabu1dqz ; real_T lpsjm2psah ; real_T inqcqvaw3b ; }
CXPtMax ; typedef struct { real_T dbmhpbljhw ; real_T okqsie1xis ; real_T
dayf44tptb ; real_T a4ovn5qqow ; real_T ng5fhqdavf ; real_T bz4a51q4zh ;
real_T fzwpwip1bi ; real_T gfkr4mr43y ; real_T l4ft3tkoae ; real_T hxle11zvbw
; real_T evqgeinzhl ; real_T aba0ie0tsy ; real_T ioresh4hqd ; real_T
kond1vggyv ; real_T iplt3teglz ; real_T bulkgwmmam ; fdijpttqf5 cc2aoo0nhc ;
real_T fltycw30uc ; real_T pm0zwxkimo ; real_T aqshfp0rir ; fdijpttqf5
dzgncmrria ; fdijpttqf5 jgvwez5knrn ; real_T kv1d3o5fz3 ; } ZCV ; typedef
struct { ZCSigState emmu1baj1n ; ZCSigState gcwp0symhu ; ZCSigState
ck5u1lzcvp ; ZCSigState aqaejmbsqc ; bg3mtgiacz cc2aoo0nhc ; ZCSigState
fwipwlsvaq ; ZCSigState jcttspjmiw ; ZCSigState osoivfua0c ; bg3mtgiacz
dzgncmrria ; bg3mtgiacz jgvwez5knrn ; ZCSigState itvz2yalg2 ; } PrevZCX ;
typedef struct { rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct
ng5ktuyqvq_ { real_T Out1_Y0 ; } ; struct P_ { real_T Atenuacion_canal ;
real_T C ; real_T Datos ; real_T Frec1 ; real_T Frec2 ; real_T R1 ; real_T R2
; real_T Rb ; real_T Retraso_canal ; real_T kv ; real_T kv2 ; real_T
CompareToConstant_const ; real_T GaussianNoiseGenerator_d ; real_T
SampleandHold_ic ; real_T SampleandHold_ic_jlfvpcljxw ; real_T
SampleandHold_ic_lzb14dyui4 ; real_T GaussianNoiseGenerator_m ; real_T
GaussianNoiseGenerator_m_pvxm3ngdo5 ; real_T GaussianNoiseGenerator_s ;
real_T GaussianNoiseGenerator_s_mqeqzkwvys ; boolean_T Monostable1_ic ;
boolean_T Monostable_ic ; boolean_T Monostable1_ic_bkmb1fdrhz ; real_T _Y0 ;
real_T _Y0_db5voyihuo ; real_T _Y0_bdpgvrnswx ; real_T Integrator_IC ; real_T
ModuloIntegrator_IC ; real_T ModuloIntegrator_WrappedStateUpperValue ; real_T
ModuloIntegrator_WrappedStateLowerValue ; real_T Switch2_Threshold ; real_T
Integrator_IC_nblk03gvyi ; real_T Filtro_A [ 7 ] ; real_T Filtro_B ; real_T
Filtro_C ; real_T Filtro_InitialCondition ; real_T Informacion_Data0 [ 182 ]
; real_T ModuloIntegrator_IC_apzvenlzc5 ; real_T
ModuloIntegrator_WrappedStateUpperValue_o4nt1k5w0o ; real_T
ModuloIntegrator_WrappedStateLowerValue_ehdhuzchfk ; real_T
TransportDelay_Delay ; real_T TransportDelay_InitOutput ; real_T
TransportDelay_InitOutput_npzkuu2dfa ; real_T RandomNumber_Mean ; real_T
RandomNumber_StdDev ; real_T Buffer_ic ; real_T
TransportDelay_Delay_lnyuh05kkd ; real_T TransportDelay_InitOutput_g2gukl3g33
; real_T TransportDelay_InitOutput_itctaj4ekg ; real_T PulseGenerator_Amp ;
real_T PulseGenerator_Duty ; real_T PulseGenerator_PhaseDelay ; real_T
TransportDelay12_Delay ; real_T TransportDelay12_InitOutput ; real_T
TransportDelay2_InitOutput ; real_T TransportDelay1_InitOutput ; real_T
TransportDelay4_InitOutput ; real_T TransportDelay3_InitOutput ; real_T
TransportDelay6_InitOutput ; real_T TransportDelay5_InitOutput ; real_T
TransportDelay8_InitOutput ; real_T TransportDelay7_InitOutput ; real_T
TransportDelay9_InitOutput ; real_T TransportDelay11_InitOutput ; real_T
TransportDelay10_InitOutput ; real_T TransportDelay13_InitOutput ; real_T
Switch_Threshold ; real_T Switch1_Threshold ; real_T
RandomNumber_Mean_n4x5jyjuez ; real_T RandomNumber_StdDev_ojydngz0lp ; real_T
MatrixGain_Gain ; real_T Buffer_ic_lzvqyw2ni2 ; real_T
TransportDelay1_InitOutput_ge1vnqoztc ; real_T
TransportDelay_InitOutput_bd4zohbbpk ; real_T Filtro_A_almvbenuye [ 11 ] ;
real_T Filtro_B_cz4ovtnlbh ; real_T Filtro_C_l0jcyicm4y ; real_T
Filtro_InitialCondition_ixj5gjnfdp ; real_T Integrator_IC_dfzts412q5 ; real_T
Integrator1_IC ; real_T TransportDelay_InitOutput_ac2nn3i4uy ; real_T
TransportDelay1_InitOutput_dc05214qlk ; real_T ModuloIntegrator_IC_mhkqbc55cu
; real_T ModuloIntegrator_WrappedStateUpperValue_l42cys1cux ; real_T
ModuloIntegrator_WrappedStateLowerValue_fozsdgujhv ; real_T
Integrator_IC_hiwtnk3vzy ; real_T ModuloIntegrator_IC_pwbk55yuz2 ; real_T
ModuloIntegrator_WrappedStateUpperValue_cqbjibrf3p ; real_T
ModuloIntegrator_WrappedStateLowerValue_nzxqkuyo3a ; real_T
Integrator1_IC_ggm3f24kg1 ; real_T Constant_Value ; real_T Constant5_Value ;
real_T Constant6_Value ; real_T Constant_Value_pgh0qhw5wr ; real_T
Constant1_Value ; real_T posedge_Value [ 2 ] ; real_T negedge_Value [ 2 ] ;
real_T eitheredge_Value [ 2 ] ; real_T Constant_Value_czlel2g4xm ; real_T
Constant1_Value_bx4tgv4ysd ; real_T posedge_Value_dx0lu3aoqz [ 2 ] ; real_T
negedge_Value_kjod1cdk3f [ 2 ] ; real_T eitheredge_Value_mhaz3orisj [ 2 ] ;
real_T Constant1_Value_ju0tizjign ; real_T Constant10_Value ; real_T
Constant11_Value ; real_T Constant12_Value ; real_T Constant13_Value ; real_T
Constant14_Value ; real_T Constant15_Value ; real_T Constant16_Value ; real_T
Constant17_Value ; real_T Constant18_Value ; real_T Constant19_Value ; real_T
Constant2_Value ; real_T Constant20_Value ; real_T Constant3_Value ; real_T
Constant4_Value ; real_T Constant5_Value_ak2ogm0bur ; real_T
Constant6_Value_mfzl25kers ; real_T Constant7_Value ; real_T Constant8_Value
; real_T Constant9_Value ; real_T Constant_Value_dufhvts2ca ; real_T
Constant1_Value_j11evhb4ur ; real_T posedge_Value_arvlrnf2hc [ 2 ] ; real_T
negedge_Value_abbvesy1jz [ 2 ] ; real_T eitheredge_Value_nb0pdzkjaa [ 2 ] ;
boolean_T _Y0_dwtojptuc5 ; boolean_T Memory_InitialCondition ; boolean_T
Memory_InitialCondition_meb2sac0hw ; boolean_T
Memory_InitialCondition_aqwb21zvmj ; ng5ktuyqvq cc2aoo0nhc ; ng5ktuyqvq
dzgncmrria ; ng5ktuyqvq jgvwez5knrn ; } ; extern const char *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX ; extern DW rtDW ;
extern PrevZCX rtPrevZCX ; extern P rtP ; extern const
rtwCAPI_ModelMappingStaticInfo * FSK_GetCAPIStaticMap ( void ) ; extern
SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern const int_T
gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern rtInportTUtable
* gblInportTUtables ; extern const char * gblInportFileName ; extern const
int_T gblNumRootInportBlks ; extern const int_T gblNumModelInputs ; extern
const int_T gblInportDataTypeIdx [ ] ; extern const int_T gblInportDims [ ] ;
extern const int_T gblInportComplex [ ] ; extern const int_T
gblInportInterpoFlag [ ] ; extern const int_T gblInportContinuous [ ] ;
extern const int_T gblParameterTuningTid ; extern DataMapInfo *
rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ;
void MdlOutputs ( int_T tid ) ; void MdlOutputsParameterSampleTime ( int_T
tid ) ; void MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void
MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ;
SimStruct * raccel_register_model ( void ) ;
#endif
