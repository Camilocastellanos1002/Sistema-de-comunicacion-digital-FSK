clc
clear all
%% variables generales
Rb=125e3; %rata de bits
A=1;    %amplitud
Gt=4;   %dbBi
Gr=4;   %dbBi
Tb=1/Rb; %tasa de transmision de bits
long1=2000; %longitud corta [m]
long2=20000; %longitud larga 20  [m]
Gt_Grdb=4*1.123; %ganancia de antenas 
k=1.3803e-23; %constante de boltzman
Te=250; %temperatura en [k]
No=10*log10(k*Te) ;  
Pot_ruidon=10^(No/10); % [dbW/Hz]
%% canal
vp=3e8; %velocidad de propagacion en el aire
alfa=0.9; % alfa*100 es el porcentaje de entraga de potencia 
frec=2.5e6; %frecuencia
lambda= vp/frec; %longitud de onda
Prob_error=4e-3; %limite de probabilidad de error
q=2.65;  %valor funcion q evaluada en 4*e-3
Atenuacion_canal=22+20*log10(long2/lambda)-Gt-Gr; %atenuacion normalizada
atenuacion_canal=10^(Atenuacion_canal/10);
att_vol=10^(Atenuacion_canal/20);
Bmin=Rb*0.5; %ancho de banda minimo entre frecuencias de modulacion
Etx=alfa*A^2/(2*Rb); %energia de bit
Energia_recibida=Etx/atenuacion_canal;  %energia recibida
eta=0.5*(Energia_recibida*(q^2)); %densidad del ruido
Pot_ruido=2*eta*Bmin;       %potencia del ruido
Ret_filtro=0.8*Tb;      %retraso del filtro
Retraso_canal=(long1/vp)+Ret_filtro; %retraso total= retraso del canal + retraso del filtro

%% modulacion fsk
Frec1=frec+0.25*Rb;     %desfase
Frec2=frec-0.25*Rb;

%% mi mensaje
info='Cambio mi vida por lámparas viejas o por los dados con los que se jugó la túnica inconsútil; por lo más anodino, por lo más obvio, por lo más fútil; por los colgajos que se guinda en las orejas la simiesca mulata, la terracota nubia; la pálida morena, la amarilla oriental, o la hiperbórea rubia; cambio mi vida por una anilla de hojalata o por la espada de Sigmundo, o por el mundo que tenía en los dedos Carlomagno: -para echar a rodar la bola..';
byte=8; 
info_enbin=reshape(dec2bin(info,byte).'-'0',1,[]);
len_info=length(info_enbin);
arreglo_info=reshape(info_enbin,4,(len_info/4));
sep=(len_info/4); %separar el mensaje en 4bits

%% Filtro acoplado
Retraso_reloj=(0.1/Rb);
umbral=0;

%% PLL:
ts=0.5/Rb;
zeta=0.9;
wn=7/ts;
C=1e-9;
kp=0.5;
kv=0.1*2*pi*Rb;
R1=(kp*kv)/(wn^2*C);
R2=(2*zeta)/(wn*C);
R2R1=(R2/R1);
R1C=1/(R1*C);
b=0.9;
kv2=Rb*Rb/8;

%% codificacion 
sin_info=rand(1,15)<0.5; %bits sin informacion para detectar y corregir aplicando hamming <7,4>
bandera=[1 1 1 1 1 0 0 1 1 0 1 0 1];

mensajecon_pari=zeros(7,sep);  %mensaje con bits de paridad
%operador logica XOR para mensaje a transmitir
for n=1 :sep
    c=xor(arreglo_info(1,n),arreglo_info(2,n));
    x=xor(c,arreglo_info(4,n)); 
    if x==1
        x1=1;
        mensajecon_pari(1,n)=x1;
    else 
        x1=0;
        mensajecon_pari(1,n)=x1;
    end 
    e=xor(arreglo_info(1,n),arreglo_info(3,n));
    y=xor(e,arreglo_info(4,n));
    if y==1
        x2=1;
        mensajecon_pari(2,n)=x2;
    else 
        x2=0;
        mensajecon_pari(2,n)=x2;
    end 
    f=xor(arreglo_info(2,n),arreglo_info(3,n));
    z=xor(f,arreglo_info(4,n));
    if z==1
        x3=1;
        mensajecon_pari(4,n)=x3;
    else 
        x3=0;
        mensajecon_pari(4,n)=x3;
    end 
        mensajecon_pari(3,n)=arreglo_info(1,n);
        mensajecon_pari(5,n)=arreglo_info(2,n);
        mensajecon_pari(6,n)=arreglo_info(3,n);
        mensajecon_pari(7,n)=arreglo_info(4,n);
end
%reorganizar el mensaje
codificacion=reshape(mensajecon_pari,1,(sep*7));
leng_cod=length(codificacion);
mensaje.time=[];
mensaje.signals.values=[sin_info';bandera';codificacion'];
mensaje.signals.dimension=1;
tiemposimu=(length(bandera)+length(sin_info)+length(codificacion)+5)/Rb;
Datos=length(codificacion);

%multiplexacion

%frecp1=(round(rand*10)*e6);
%frecp2=(round(rand*10)*e6);


%{
B_canal=8e6;
Bband=1e6;
Bt=B_canal-Bband;
Nportadoras=2;
C=Bt/2;
frecport1=2e6;
ban1=frecport1-(frecport1*0.5);
ban2=frecport1+(frecport1*0.5);
frecport2=5e6;
ban3=frecport2-(frecport2*0.5);
ban4=frecport2+(frecport2*0.5);
%}
