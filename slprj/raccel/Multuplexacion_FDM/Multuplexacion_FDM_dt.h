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
rtBTransitions [ ] = { { ( char_T * ) ( & rtB . gzkvmusrdv ) , 0 , 0 , 113 }
, { ( char_T * ) ( & rtB . o2g3bsob40 ) , 8 , 0 , 11 } , { ( char_T * ) ( &
rtB . abmuy5rnsq . ltgb5gkcbo ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtB .
mpycb0evfp . hmpzhh3n3o ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtB . jiixgvrfhd
. hml4vbrazh ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtB . gggqmave4q .
ltgb5gkcbo ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtB . fkhi333c1w . hmpzhh3n3o
) , 8 , 0 , 1 } , { ( char_T * ) ( & rtB . dyorcglstw . hml4vbrazh ) , 0 , 0
, 1 } , { ( char_T * ) ( & rtB . d5zlt11l1pl . ltgb5gkcbo ) , 8 , 0 , 1 } , {
( char_T * ) ( & rtB . dnioykk3w1k . hmpzhh3n3o ) , 8 , 0 , 1 } , { ( char_T
* ) ( & rtB . mivhx1fvuuy . hml4vbrazh ) , 0 , 0 , 1 } , { ( char_T * ) ( &
rtDW . ou0ychata3 ) , 0 , 0 , 6 } , { ( char_T * ) ( & rtDW . kklmtkqxdm ) ,
14 , 0 , 1 } , { ( char_T * ) ( & rtDW . khrc1lwffi . modelTStart ) , 0 , 0 ,
21 } , { ( char_T * ) ( & rtDW . d0yoqq0s2u . TimePtr ) , 11 , 0 , 61 } , { (
char_T * ) ( & rtDW . nnzogj4mrn ) , 6 , 0 , 2 } , { ( char_T * ) ( & rtDW .
imgdcg24fm ) , 7 , 0 , 2 } , { ( char_T * ) ( & rtDW . fxbkkikmgg . PrevIndex
) , 10 , 0 , 26 } , { ( char_T * ) ( & rtDW . lekdfle5yl ) , 2 , 0 , 5 } , {
( char_T * ) ( & rtDW . ita0atad5a ) , 8 , 0 , 15 } , { ( char_T * ) ( & rtDW
. abmuy5rnsq . faxymqm3qy ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
mpycb0evfp . k2unbokluf ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
jiixgvrfhd . fmzbbk3ukv ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
gggqmave4q . faxymqm3qy ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
fkhi333c1w . k2unbokluf ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
dyorcglstw . fmzbbk3ukv ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
d5zlt11l1pl . faxymqm3qy ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
dnioykk3w1k . k2unbokluf ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
mivhx1fvuuy . fmzbbk3ukv ) , 2 , 0 , 1 } } ; static DataTypeTransitionTable
rtBTransTable = { 29U , rtBTransitions } ; static DataTypeTransition
rtPTransitions [ ] = { { ( char_T * ) ( & rtP . Atenuacion_canal ) , 0 , 0 ,
21 } , { ( char_T * ) ( & rtP . Monostable1_ic ) , 8 , 0 , 3 } , { ( char_T *
) ( & rtP . _Y0 ) , 0 , 0 , 533 } , { ( char_T * ) ( & rtP . _Y0_ld4ghr3opr )
, 8 , 0 , 4 } , { ( char_T * ) ( & rtP . abmuy5rnsq . OUT_Y0 ) , 8 , 0 , 1 }
, { ( char_T * ) ( & rtP . mpycb0evfp . OUT_Y0 ) , 8 , 0 , 1 } , { ( char_T *
) ( & rtP . jiixgvrfhd . Out1_Y0 ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtP .
gggqmave4q . OUT_Y0 ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtP . fkhi333c1w .
OUT_Y0 ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtP . dyorcglstw . Out1_Y0 ) , 0
, 0 , 1 } , { ( char_T * ) ( & rtP . d5zlt11l1pl . OUT_Y0 ) , 8 , 0 , 1 } , {
( char_T * ) ( & rtP . dnioykk3w1k . OUT_Y0 ) , 8 , 0 , 1 } , { ( char_T * )
( & rtP . mivhx1fvuuy . Out1_Y0 ) , 0 , 0 , 1 } } ; static
DataTypeTransitionTable rtPTransTable = { 13U , rtPTransitions } ;
