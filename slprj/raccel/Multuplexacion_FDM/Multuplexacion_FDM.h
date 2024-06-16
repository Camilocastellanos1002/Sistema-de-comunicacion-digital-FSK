#ifndef RTW_HEADER_Multuplexacion_FDM_h_
#define RTW_HEADER_Multuplexacion_FDM_h_
#include <string.h>
#include <stddef.h>
#include <float.h>
#include "rtw_modelmap.h"
#ifndef Multuplexacion_FDM_COMMON_INCLUDES_
#define Multuplexacion_FDM_COMMON_INCLUDES_
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
#include "Multuplexacion_FDM_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_zcfcn.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME Multuplexacion_FDM
#define NSAMPLE_TIMES (6) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (130) 
#define NUM_ZC_EVENTS (11) 
#ifndef NCSTATES
#define NCSTATES (37)   
#elif NCSTATES != 37
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
typedef struct { real_T hml4vbrazh ; } mtjjwddujs ; typedef struct { int8_T
fmzbbk3ukv ; } bpumykcckk ; typedef struct { real_T nletqtn2tu ; } llzkwq4yk5
; typedef struct { ZCSigState aw5lle212o ; } hixkhuf4px ; typedef struct {
boolean_T hmpzhh3n3o ; } fikkek4bti ; typedef struct { int8_T k2unbokluf ; }
f3nkengjqz ; typedef struct { boolean_T ltgb5gkcbo ; } atopmxixl1 ; typedef
struct { int8_T faxymqm3qy ; } p0p5r3rifc ; typedef struct { real_T
gzkvmusrdv ; real_T l2slq2pxao ; real_T hqvlr0c1t3 ; real_T l3viz5m5kx ;
real_T ifswdaywbt ; real_T ph3uie01yv ; real_T cwrlg5uwpe ; real_T m1xi1b0n5m
; real_T omyffgmxzc ; real_T otfd1hdnf4 ; real_T dwygygnfyu ; real_T
kvdiwfhjmc ; real_T oddjfmdyew ; real_T ftbsaajysf ; real_T i3olz0n0gi ;
real_T d4sffuf0wj ; real_T ckmrjxysf3 ; real_T jaf1or2u2g ; real_T lisu5vhdeu
; real_T czpmrjwdbw ; real_T eqpfzakwij ; real_T cuyzwij0cy ; real_T
dc0ixgrh4v ; real_T bonunno3da ; real_T p5sg0ao2sd ; real_T hnghqt15hm ;
real_T pbihxnhzkv ; real_T ehk41k1jvu ; real_T jdmdbzovgb ; real_T dl2z1kzk4x
; real_T drqnxkzet4 ; real_T hduwbah451 ; real_T osh4e3wkbx ; real_T
jkosinqwcz ; real_T mhvwbma2wc ; real_T hoboqemidv ; real_T pw3nmstdx1 ;
real_T aekkmo2dza ; real_T leuwvo5bd0 ; real_T kzkfn1s2js ; real_T hdfbddrmbc
; real_T fetl3awrl2 ; real_T hd11xynwm2 ; real_T nuzxbadudr ; real_T
dfyucx0pjs ; real_T owlyu5iz4l ; real_T dwfqmte2n3 ; real_T loxkzong0h ;
real_T gx1uxu4kds ; real_T co4tajx3jh ; real_T hd0ccnz5kj ; real_T kmsebnmjbu
; real_T ay4kbspa2f ; real_T dwuvmlamlj ; real_T iup0qas13y ; real_T
pbk3xyooxn ; real_T jj2crb3wdo ; real_T flwwemz4a3 ; real_T pskl4q2wwt ;
real_T exdbaattar ; real_T izg2hxr1hm ; real_T f1l5jsixgw ; real_T fosqwahuok
; real_T orkfi0mp2e ; real_T izpbcjjrig ; real_T gwu42iz5ys ; real_T
pgvargzqvr ; real_T ityop505e4 ; real_T hrs0mectw5 ; real_T fgrkiz4z0n ;
real_T cswpv2o1kk ; real_T de2xsxb24p ; real_T hx1rf2yrz2 ; real_T cviwvtwqhc
; real_T l5nwaj4e3i ; real_T looejrxoki ; real_T awasz3p2hm ; real_T
axof5reva4 ; real_T m3xclbw4n1 ; real_T jka1elz4sz ; real_T ikxyn0xytc ;
real_T h32dvvdjsr ; real_T cfvwyihfgi ; real_T bbdybg5bbo ; real_T nb4mlfbe25
; real_T nrzgv2asbm ; real_T kb3qoydtul ; real_T emzymu3s4t ; real_T
dhvezilxca ; real_T fy1jpymzvl ; real_T gwfkgabvtm ; real_T ijhgy4lexb ;
real_T csu05jokxd ; real_T eg0uqlyrw2 ; real_T dhxzfrd1ut ; real_T ihg3emy0vs
; real_T l1ylzo5bhw ; real_T cj3eokpnbs ; real_T i14aygkcoq ; real_T
a4wt4ee5p1 ; real_T fz1wrzhdaa ; real_T kp3wrgz5sh ; real_T fuwgkaabcp ;
real_T d2vdhfxwnv ; real_T fto4cglprz [ 2 ] ; real_T nj0vsa0aao [ 2 ] ;
real_T i4cllywuc1 [ 2 ] ; real_T dduxw540hu ; real_T munnuokh3b ; real_T
lufwcivalw ; boolean_T o2g3bsob40 ; boolean_T f0xjphnymz ; boolean_T
nekkkm0p0a ; boolean_T eaief2hsbj ; boolean_T dumyggkchi ; boolean_T
hgcnrsrftd ; boolean_T ghaifzgd35 ; boolean_T bnhnntm3f4 ; boolean_T
ajbeq5hpnj ; boolean_T eizf1ealtw ; boolean_T e1nhqxjvjn ; atopmxixl1
abmuy5rnsq ; fikkek4bti mpycb0evfp ; mtjjwddujs jiixgvrfhd ; atopmxixl1
gggqmave4q ; fikkek4bti fkhi333c1w ; mtjjwddujs dyorcglstw ; atopmxixl1
d5zlt11l1pl ; fikkek4bti dnioykk3w1k ; mtjjwddujs mivhx1fvuuy ; } B ; typedef
struct { real_T ou0ychata3 ; real_T dbk2xqyp1n ; real_T bwkxnxzhy1 ; real_T
kikmlfmksm ; real_T livmyfqsgc ; real_T nfditlbohk ; int64_T kklmtkqxdm ;
struct { real_T modelTStart ; } khrc1lwffi ; struct { real_T modelTStart ; }
cssnev1fy3 ; struct { real_T modelTStart ; } oa42qrjv3l ; struct { real_T
modelTStart ; } ggwyhatdea ; struct { real_T modelTStart ; } cuje003nlw ;
struct { real_T modelTStart ; } puzaleogwu ; struct { real_T modelTStart ; }
n1qb5g4n41 ; struct { real_T modelTStart ; } bfwzmi2uyh ; struct { real_T
modelTStart ; } ebk2ryovno ; struct { real_T modelTStart ; } ptkzu50g4c ;
struct { real_T modelTStart ; } kya31t5ner ; struct { real_T modelTStart ; }
kfvog22y10 ; struct { real_T modelTStart ; } lq15frqj0j ; struct { real_T
modelTStart ; } iyu2cdjdjo ; struct { real_T modelTStart ; } bleq0imc3q ;
struct { real_T modelTStart ; } jxtss4hooy ; struct { real_T modelTStart ; }
auetjjv433 ; struct { real_T modelTStart ; } hqpl32qj3u ; struct { real_T
modelTStart ; } pvitriryga ; struct { real_T modelTStart ; } fm4mcliygj ;
struct { real_T modelTStart ; } phs2xz5445 ; struct { void * TimePtr ; void *
DataPtr ; void * RSimInfoPtr ; } d0yoqq0s2u ; struct { void * LoggedData [ 2
] ; } fcafpomhwg ; struct { void * LoggedData [ 2 ] ; } eckmfvfwps ; struct {
void * TimePtr ; void * DataPtr ; void * RSimInfoPtr ; } gtget4fvsy ; struct
{ void * TUbufferPtrs [ 2 ] ; } j0ojopv3o4 ; struct { void * TUbufferPtrs [ 2
] ; } odiqda1u1t ; struct { void * TUbufferPtrs [ 2 ] ; } mx1qnjpwkr ; struct
{ void * TUbufferPtrs [ 2 ] ; } c1abig5l5b ; struct { void * TUbufferPtrs [ 2
] ; } l3olmqutvm ; struct { void * TUbufferPtrs [ 2 ] ; } laigziygdt ; struct
{ void * LoggedData [ 2 ] ; } dkdfqlezt3 ; struct { void * TUbufferPtrs [ 2 ]
; } duyhxp3i2o ; struct { void * TUbufferPtrs [ 2 ] ; } pfzlxqtttd ; struct {
void * TUbufferPtrs [ 2 ] ; } kpyzd0zppl ; struct { void * TUbufferPtrs [ 2 ]
; } anw4lh3mkt ; struct { void * TUbufferPtrs [ 2 ] ; } hth3y5boa4 ; struct {
void * TUbufferPtrs [ 2 ] ; } jkfvz1vsm1 ; struct { void * TUbufferPtrs [ 2 ]
; } axitmt5w4i ; struct { void * TUbufferPtrs [ 2 ] ; } bz4cstgndq ; struct {
void * TUbufferPtrs [ 2 ] ; } ifxwkbjtsf ; struct { void * TUbufferPtrs [ 2 ]
; } oydq1getqe ; struct { void * TUbufferPtrs [ 2 ] ; } nzhehebsh0 ; struct {
void * TUbufferPtrs [ 2 ] ; } erisf50gfz ; struct { void * TUbufferPtrs [ 2 ]
; } jszhk4b0c2 ; struct { void * TUbufferPtrs [ 2 ] ; } emliqyd1hi ; struct {
void * TUbufferPtrs [ 2 ] ; } j0z4zsdtwg ; struct { void * LoggedData [ 4 ] ;
} fgn1xd2f0g ; struct { void * LoggedData [ 4 ] ; } n05q2zm0z1 ; struct {
void * LoggedData [ 2 ] ; } g4w5bwgqfc ; struct { void * LoggedData ; }
lp4l4cdghx ; int32_T nnzogj4mrn ; int32_T dvmb0i40bs ; uint32_T imgdcg24fm ;
uint32_T kzibzv5iwi ; struct { int_T PrevIndex ; } fxbkkikmgg ; struct {
int_T PrevIndex ; } j4hthgivby ; struct { int_T Tail ; int_T Head ; int_T
Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; } actgbahxga ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } cc05czrsze ; struct { int_T Tail ; int_T Head ; int_T Last
; int_T CircularBufSize ; int_T MaxNewBufSize ; } ikxgblv1zv ; struct { int_T
Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize
; } c0ewitmagq ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } mw4jmqmb5m ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
mbpoqz0vfq ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } jqyvcdfdil ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
b5jqmouq00 ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } dsos1nl3ug ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
miosm0kvi1 ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } daastispqd ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
ga03tvlrh0 ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } d2cdydaqvh ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
lo3fy120pk ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } i5j0s3drdy ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
naehoe5c24 ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } atsr3zriuy ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
ogdeiw34cz ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } nan1e3l5p0 ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
oivjundpbe ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } os1vqq3jgt ; int_T nfgd4hmkks ;
int_T hhfaeeexeg ; int_T oxgn4zxxpe ; int8_T lekdfle5yl ; int8_T cjvs3g4hfh ;
int8_T moelhnb1d2 ; int8_T loneq0nrmu ; int8_T hbnvwgns2u ; boolean_T
ita0atad5a ; boolean_T oz50sdopcp ; boolean_T pejw2pyiiz ; boolean_T
j2llbcud4w ; boolean_T by0zcdyxc4 ; boolean_T alduujhq0a ; boolean_T
kmeshewsao ; boolean_T cbjfpdjiyu ; boolean_T bctphvd2sv ; boolean_T
alglspiynp ; boolean_T koquxjpxpa ; boolean_T bqhe24xuds ; boolean_T
ox1bxr2hww ; boolean_T kltylslzkb ; boolean_T luhachiin3 ; p0p5r3rifc
abmuy5rnsq ; f3nkengjqz mpycb0evfp ; bpumykcckk jiixgvrfhd ; p0p5r3rifc
gggqmave4q ; f3nkengjqz fkhi333c1w ; bpumykcckk dyorcglstw ; p0p5r3rifc
d5zlt11l1pl ; f3nkengjqz dnioykk3w1k ; bpumykcckk mivhx1fvuuy ; } DW ;
typedef struct { real_T ccwzf3tws3 [ 10 ] ; real_T cgdhzp3x0l ; real_T
imuz3fx4o3 ; real_T cfrslgfjyu ; real_T ids2w4qbzk [ 10 ] ; real_T nc3vmkovco
; real_T psx2ki4ws3 ; real_T hrccq1fi0z [ 6 ] ; real_T gxe5sdikfw ; real_T
cc5042ocv2 ; real_T husvwrmjnn ; real_T g01iry0rqn ; real_T iquu4mgvfb ;
real_T lnhetubiv2 ; } X ; typedef int_T PeriodicIndX [ 5 ] ; typedef real_T
PeriodicRngX [ 10 ] ; typedef struct { real_T ccwzf3tws3 [ 10 ] ; real_T
cgdhzp3x0l ; real_T imuz3fx4o3 ; real_T cfrslgfjyu ; real_T ids2w4qbzk [ 10 ]
; real_T nc3vmkovco ; real_T psx2ki4ws3 ; real_T hrccq1fi0z [ 6 ] ; real_T
gxe5sdikfw ; real_T cc5042ocv2 ; real_T husvwrmjnn ; real_T g01iry0rqn ;
real_T iquu4mgvfb ; real_T lnhetubiv2 ; } XDot ; typedef struct { boolean_T
ccwzf3tws3 [ 10 ] ; boolean_T cgdhzp3x0l ; boolean_T imuz3fx4o3 ; boolean_T
cfrslgfjyu ; boolean_T ids2w4qbzk [ 10 ] ; boolean_T nc3vmkovco ; boolean_T
psx2ki4ws3 ; boolean_T hrccq1fi0z [ 6 ] ; boolean_T gxe5sdikfw ; boolean_T
cc5042ocv2 ; boolean_T husvwrmjnn ; boolean_T g01iry0rqn ; boolean_T
iquu4mgvfb ; boolean_T lnhetubiv2 ; } XDis ; typedef struct { real_T
ccwzf3tws3 [ 10 ] ; real_T cgdhzp3x0l ; real_T imuz3fx4o3 ; real_T cfrslgfjyu
; real_T ids2w4qbzk [ 10 ] ; real_T nc3vmkovco ; real_T psx2ki4ws3 ; real_T
hrccq1fi0z [ 6 ] ; real_T gxe5sdikfw ; real_T cc5042ocv2 ; real_T husvwrmjnn
; real_T g01iry0rqn ; real_T iquu4mgvfb ; real_T lnhetubiv2 ; } CStateAbsTol
; typedef struct { real_T ccwzf3tws3 [ 10 ] ; real_T cgdhzp3x0l ; real_T
imuz3fx4o3 ; real_T cfrslgfjyu ; real_T ids2w4qbzk [ 10 ] ; real_T nc3vmkovco
; real_T psx2ki4ws3 ; real_T hrccq1fi0z [ 6 ] ; real_T gxe5sdikfw ; real_T
cc5042ocv2 ; real_T husvwrmjnn ; real_T g01iry0rqn ; real_T iquu4mgvfb ;
real_T lnhetubiv2 ; } CXPtMin ; typedef struct { real_T ccwzf3tws3 [ 10 ] ;
real_T cgdhzp3x0l ; real_T imuz3fx4o3 ; real_T cfrslgfjyu ; real_T ids2w4qbzk
[ 10 ] ; real_T nc3vmkovco ; real_T psx2ki4ws3 ; real_T hrccq1fi0z [ 6 ] ;
real_T gxe5sdikfw ; real_T cc5042ocv2 ; real_T husvwrmjnn ; real_T g01iry0rqn
; real_T iquu4mgvfb ; real_T lnhetubiv2 ; } CXPtMax ; typedef struct { real_T
dnmjo5cczs ; real_T ijuxvdku2m ; real_T g3zy3hubrz ; real_T oyjjegcjyy ;
real_T djgwmqbkch ; real_T ocfvj3cewj ; real_T nheeorwalf ; real_T bvrnndoiby
; real_T k3coiq1vdz ; real_T lywec2rsyi ; real_T cig4gducut ; real_T
oul53rl51h ; real_T mmgl4pfrpz ; real_T dreagcpm3h ; real_T p1gxley4ws ;
real_T f2wbwiipfc ; llzkwq4yk5 jiixgvrfhd ; real_T gka5abjfmy ; real_T
hyeiuiejxp ; real_T fgsusy0byz ; llzkwq4yk5 dyorcglstw ; llzkwq4yk5
mivhx1fvuuy ; real_T eegs2utgml ; } ZCV ; typedef struct { ZCSigState
mqbxqqegfa ; ZCSigState mj4uwtxvw4 ; ZCSigState kci0nfmn3i ; ZCSigState
ctjn34sghg ; hixkhuf4px jiixgvrfhd ; ZCSigState otkgxfzkeh ; ZCSigState
coh1zb2qmc ; ZCSigState cvp0g55jmi ; hixkhuf4px dyorcglstw ; hixkhuf4px
mivhx1fvuuy ; ZCSigState p1xn3fs3d3 ; } PrevZCX ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct b2hegj220n_ { real_T
Out1_Y0 ; } ; struct knxgvh15og_ { boolean_T OUT_Y0 ; } ; struct pgxloeq2x1_
{ boolean_T OUT_Y0 ; } ; struct P_ { real_T Atenuacion_canal ; real_T C ;
real_T Datos ; real_T Frec1 ; real_T Frec2 ; real_T R1 ; real_T R2 ; real_T
Rb ; real_T Retraso_canal ; real_T frecport1 ; real_T kv ; real_T kv2 ;
real_T CompareToConstant_const ; real_T GaussianNoiseGenerator_d ; real_T
SampleandHold_ic ; real_T SampleandHold_ic_j2rdwmu3tc ; real_T
SampleandHold_ic_iltoiaeoee ; real_T GaussianNoiseGenerator_m ; real_T
GaussianNoiseGenerator_m_feibr5czzb ; real_T GaussianNoiseGenerator_s ;
real_T GaussianNoiseGenerator_s_natqquq25k ; boolean_T Monostable1_ic ;
boolean_T Monostable_ic ; boolean_T Monostable1_ic_biaz4juxj0 ; real_T _Y0 ;
real_T _Y0_matapuynvo ; real_T _Y0_ghe40wtwbh ; real_T AnalogFilterDesign2_A
[ 19 ] ; real_T AnalogFilterDesign2_B ; real_T AnalogFilterDesign2_C ; real_T
AnalogFilterDesign2_InitialCondition ; real_T Informacion2_Data0 [ 182 ] ;
real_T Integrator_IC ; real_T ModuloIntegrator_IC ; real_T
ModuloIntegrator_WrappedStateUpperValue ; real_T
ModuloIntegrator_WrappedStateLowerValue ; real_T Switch2_Threshold ; real_T
Integrator_IC_moexjyifg4 ; real_T informacion1_Data0 [ 182 ] ; real_T
AnalogFilterDesign_A [ 19 ] ; real_T AnalogFilterDesign_B ; real_T
AnalogFilterDesign_C ; real_T AnalogFilterDesign_InitialCondition ; real_T
ModuloIntegrator_IC_esfyns1sy5 ; real_T
ModuloIntegrator_WrappedStateUpperValue_inwk4jds10 ; real_T
ModuloIntegrator_WrappedStateLowerValue_efd0rfjvev ; real_T SineWave_Amp ;
real_T SineWave_Bias ; real_T SineWave_Phase ; real_T TransportDelay_Delay ;
real_T TransportDelay_InitOutput ; real_T ModuloIntegrator_IC_i5n3se5kvp ;
real_T ModuloIntegrator_WrappedStateUpperValue_dcyqcfnaqw ; real_T
ModuloIntegrator_WrappedStateLowerValue_i1zhdl4bre ; real_T
TransportDelay_InitOutput_a54zvzwmak ; real_T RandomNumber_Mean ; real_T
RandomNumber_StdDev ; real_T Buffer_ic ; real_T
TransportDelay_Delay_dget2i1x1r ; real_T TransportDelay_InitOutput_nb5s3gjuh0
; real_T TransportDelay_InitOutput_bfobvi0kzf ; real_T PulseGenerator_Amp ;
real_T PulseGenerator_Duty ; real_T PulseGenerator_PhaseDelay ; real_T
TransportDelay_InitOutput_pz2dgrhemk ; real_T TransportDelay1_InitOutput ;
real_T TransportDelay12_Delay ; real_T TransportDelay12_InitOutput ; real_T
TransportDelay2_InitOutput ; real_T TransportDelay1_InitOutput_km2up0labu ;
real_T TransportDelay4_InitOutput ; real_T TransportDelay3_InitOutput ;
real_T TransportDelay6_InitOutput ; real_T TransportDelay5_InitOutput ;
real_T TransportDelay8_InitOutput ; real_T TransportDelay7_InitOutput ;
real_T TransportDelay9_InitOutput ; real_T TransportDelay11_InitOutput ;
real_T TransportDelay10_InitOutput ; real_T TransportDelay13_InitOutput ;
real_T Switch_Threshold ; real_T Switch1_Threshold ; real_T
RandomNumber_Mean_pbcszkatmd ; real_T RandomNumber_StdDev_iveng2gmn4 ; real_T
MatrixGain_Gain ; real_T Buffer_ic_b4vk0qmtfp ; real_T
TransportDelay1_InitOutput_cz0jjsby1m ; real_T
TransportDelay_InitOutput_nwut2o4lpm ; real_T Filtro_A [ 11 ] ; real_T
Filtro_B ; real_T Filtro_C ; real_T Filtro_InitialCondition ; real_T
Integrator_IC_ptowdeldtu ; real_T Integrator1_IC ; real_T
ModuloIntegrator_IC_nahsh2vkhw ; real_T
ModuloIntegrator_WrappedStateUpperValue_h455it4xzm ; real_T
ModuloIntegrator_WrappedStateLowerValue_bslhwjjmfb ; real_T
Integrator_IC_nfolmlihr0 ; real_T ModuloIntegrator_IC_cw2uxsyp5l ; real_T
ModuloIntegrator_WrappedStateUpperValue_hgarqjv2uf ; real_T
ModuloIntegrator_WrappedStateLowerValue_mxtqs3uocj ; real_T
Integrator1_IC_dcpkt2betd ; real_T Constant_Value ; real_T Constant5_Value ;
real_T Constant6_Value ; real_T Constant_Value_mvnfzatsby ; real_T
Constant1_Value ; real_T posedge_Value [ 2 ] ; real_T negedge_Value [ 2 ] ;
real_T eitheredge_Value [ 2 ] ; real_T Constant_Value_izjuzrtanz ; real_T
Constant1_Value_lpebpexhqd ; real_T posedge_Value_iryngzqrd1 [ 2 ] ; real_T
negedge_Value_a22nqhbklc [ 2 ] ; real_T eitheredge_Value_a1qgi2i0lx [ 2 ] ;
real_T Constant1_Value_obqa0ysasv ; real_T Constant10_Value ; real_T
Constant11_Value ; real_T Constant12_Value ; real_T Constant13_Value ; real_T
Constant14_Value ; real_T Constant15_Value ; real_T Constant16_Value ; real_T
Constant17_Value ; real_T Constant18_Value ; real_T Constant19_Value ; real_T
Constant2_Value ; real_T Constant20_Value ; real_T Constant3_Value ; real_T
Constant4_Value ; real_T Constant5_Value_pqkhorznoi ; real_T
Constant6_Value_oth1tjvwv0 ; real_T Constant7_Value ; real_T Constant8_Value
; real_T Constant9_Value ; real_T Constant_Value_pmuy4epl2c ; real_T
Constant1_Value_bsax1tsxxz ; real_T posedge_Value_fsgb0grkvo [ 2 ] ; real_T
negedge_Value_ackdjcny40 [ 2 ] ; real_T eitheredge_Value_lzvwtrli1x [ 2 ] ;
boolean_T _Y0_ld4ghr3opr ; boolean_T Memory_InitialCondition ; boolean_T
Memory_InitialCondition_jlkxne1qro ; boolean_T
Memory_InitialCondition_cdrhhgyi4a ; pgxloeq2x1 abmuy5rnsq ; knxgvh15og
mpycb0evfp ; b2hegj220n jiixgvrfhd ; pgxloeq2x1 gggqmave4q ; knxgvh15og
fkhi333c1w ; b2hegj220n dyorcglstw ; pgxloeq2x1 d5zlt11l1pl ; knxgvh15og
dnioykk3w1k ; b2hegj220n mivhx1fvuuy ; } ; extern const char *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX ; extern DW rtDW ;
extern PrevZCX rtPrevZCX ; extern P rtP ; extern const
rtwCAPI_ModelMappingStaticInfo * Multuplexacion_FDM_GetCAPIStaticMap ( void )
; extern SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern
const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
extern const int_T gblNumRootInportBlks ; extern const int_T
gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ; extern
const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [ ] ;
extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( void
) ;
#endif
