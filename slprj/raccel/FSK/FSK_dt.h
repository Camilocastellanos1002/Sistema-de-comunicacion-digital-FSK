#include "ext_types.h"
static DataTypeInfo rtDataTypeInfoTable [ ] = { { "real_T" , 0 , 8 } , {
"real32_T" , 1 , 4 } , { "int8_T" , 2 , 1 } , { "uint8_T" , 3 , 1 } , {
"int16_T" , 4 , 2 } , { "uint16_T" , 5 , 2 } , { "int32_T" , 6 , 4 } , {
"uint32_T" , 7 , 4 } , { "boolean_T" , 8 , 1 } , { "fcn_call_T" , 9 , 0 } , {
"int_T" , 10 , 4 } , { "pointer_T" , 11 , 8 } , { "action_T" , 12 , 8 } , {
"timer_uint32_pair_T" , 13 , 8 } , { "int64_T" , 14 , 8 } , { "int64_T" , 15
, 8 } , { "uint64_T" , 16 , 8 } } ; static uint_T rtDataTypeSizes [ ] = {
sizeof ( real_T ) , sizeof ( real32_T ) , sizeof ( int8_T ) , sizeof (
uint8_T ) , sizeof ( int16_T ) , sizeof ( uint16_T ) , sizeof ( int32_T ) ,
sizeof ( uint32_T ) , sizeof ( boolean_T ) , sizeof ( fcn_call_T ) , sizeof (
int_T ) , sizeof ( pointer_T ) , sizeof ( action_T ) , 2 * sizeof ( uint32_T
) , sizeof ( int64_T ) , sizeof ( int64_T ) , sizeof ( uint64_T ) } ; static
const char_T * rtDataTypeNames [ ] = { "real_T" , "real32_T" , "int8_T" ,
"uint8_T" , "int16_T" , "uint16_T" , "int32_T" , "uint32_T" , "boolean_T" ,
"fcn_call_T" , "int_T" , "pointer_T" , "action_T" , "timer_uint32_pair_T" ,
"int64_T" , "int64_T" , "uint64_T" } ; static DataTypeTransition
rtBTransitions [ ] = { { ( char_T * ) ( & rtB . hao2kgiuqu ) , 0 , 0 , 76 } ,
{ ( char_T * ) ( & rtB . cbutxn4e51 ) , 8 , 0 , 11 } , { ( char_T * ) ( & rtB
. cvrfqtrsgv . ddvcjkqoaj ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtB .
b5dbwkwsrj . ighgnitevw ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtB . cc2aoo0nhc
. jzxmgvajvp ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . cfrh4agkgq .
ddvcjkqoaj ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtB . awkevlz2ww . ighgnitevw
) , 8 , 0 , 1 } , { ( char_T * ) ( & rtB . dzgncmrria . jzxmgvajvp ) , 0 , 0
, 1 } , { ( char_T * ) ( & rtB . edzbs02xos1 . ddvcjkqoaj ) , 8 , 0 , 1 } , {
( char_T * ) ( & rtB . fqkin25shtk . ighgnitevw ) , 8 , 0 , 1 } , { ( char_T
* ) ( & rtB . jgvwez5knrn . jzxmgvajvp ) , 0 , 0 , 1 } , { ( char_T * ) ( &
rtDW . dzchlxvwf3 ) , 0 , 0 , 6 } , { ( char_T * ) ( & rtDW . j5zzyh4rpr ) ,
14 , 0 , 1 } , { ( char_T * ) ( & rtDW . pjddaatqz2 . modelTStart ) , 0 , 0 ,
21 } , { ( char_T * ) ( & rtDW . m12hjeojxl . LoggedData [ 0 ] ) , 11 , 0 ,
56 } , { ( char_T * ) ( & rtDW . n2ufwbrgzx ) , 6 , 0 , 2 } , { ( char_T * )
( & rtDW . dwuhp2thuf ) , 7 , 0 , 2 } , { ( char_T * ) ( & rtDW . ob0eo32bes
. PrevIndex ) , 10 , 0 , 25 } , { ( char_T * ) ( & rtDW . og5vligtf5 ) , 2 ,
0 , 5 } , { ( char_T * ) ( & rtDW . brpeccm2su ) , 8 , 0 , 15 } , { ( char_T
* ) ( & rtDW . cvrfqtrsgv . bl2ajkrwzq ) , 2 , 0 , 1 } , { ( char_T * ) ( &
rtDW . b5dbwkwsrj . mnrpt53zog ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
cc2aoo0nhc . b4uftfd3jt ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
cfrh4agkgq . bl2ajkrwzq ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
awkevlz2ww . mnrpt53zog ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
dzgncmrria . b4uftfd3jt ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
edzbs02xos1 . bl2ajkrwzq ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
fqkin25shtk . mnrpt53zog ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
jgvwez5knrn . b4uftfd3jt ) , 2 , 0 , 1 } } ; static DataTypeTransitionTable
rtBTransTable = { 29U , rtBTransitions } ; static DataTypeTransition
rtPTransitions [ ] = { { ( char_T * ) ( & rtP . Atenuacion_canal ) , 0 , 0 ,
20 } , { ( char_T * ) ( & rtP . Monostable1_ic ) , 8 , 0 , 3 } , { ( char_T *
) ( & rtP . _Y0 ) , 0 , 0 , 311 } , { ( char_T * ) ( & rtP . _Y0_dwtojptuc5 )
, 8 , 0 , 4 } , { ( char_T * ) ( & rtP . cc2aoo0nhc . Out1_Y0 ) , 0 , 0 , 1 }
, { ( char_T * ) ( & rtP . dzgncmrria . Out1_Y0 ) , 0 , 0 , 1 } , { ( char_T
* ) ( & rtP . jgvwez5knrn . Out1_Y0 ) , 0 , 0 , 1 } } ; static
DataTypeTransitionTable rtPTransTable = { 7U , rtPTransitions } ;
