%{
    Este archivo se debe ejecutar para poder realizar la multiplexacion,
    con dos mensajes diferentes

%}


%% mensaje #1
info2='hola mundo, mi nombre es pedro pablo.. ';
byte=8; 
info_enbin2=reshape(dec2bin(info2,byte).'-'0',1,[]);
len_info2=length(info_enbin2);
arreglo_info2=reshape(info_enbin2,4,(len_info2/4));
sep2=(len_info2/4); %separar el mensaje en 4bits

mensajecon_pari2=zeros(7,sep2);  %mensaje con bits de paridad
%operador logica XOR para mensaje a transmitir
for n=1 :sep2
    c=xor(arreglo_info2(1,n),arreglo_info2(2,n));
    x=xor(c,arreglo_info2(4,n)); 
    if x==1
        x1=1;
        mensajecon_pari2(1,n)=x1;
    else 
        x1=0;
        mensajecon_pari2(1,n)=x1;
    end 
    e=xor(arreglo_info2(1,n),arreglo_info2(3,n));
    y=xor(e,arreglo_info2(4,n));
    if y==1
        x2=1;
        mensajecon_pari2(2,n)=x2;
    else 
        x2=0;
        mensajecon_pari2(2,n)=x2;
    end 
    f=xor(arreglo_info2(2,n),arreglo_info2(3,n));
    z=xor(f,arreglo_info2(4,n));
    if z==1
        x3=1;
        mensajecon_pari2(4,n)=x3;
    else 
        x3=0;
        mensajecon_pari2(4,n)=x3;
    end 
        mensajecon_pari2(3,n)=arreglo_info2(1,n);
        mensajecon_pari2(5,n)=arreglo_info2(2,n);
        mensajecon_pari2(6,n)=arreglo_info2(3,n);
        mensajecon_pari2(7,n)=arreglo_info2(4,n);
end
%reorganizar el mensaje
codificacion2=reshape(mensajecon_pari2,1,(sep2*7));
leng_cod=length(codificacion2);
mensaje2.time=[];
mensaje2.signals.values=[sin_info';bandera';codificacion2'];
mensaje2.signals.dimension=1;
tiemposimu=(length(bandera)+length(sin_info)+length(codificacion2)+5)/Rb;
Datos=length(codificacion2);


%% mi mensaje #2
frec2=5e6;
Frec3=frec2+0.25*Rb;     
Frec4=frec2-0.25*Rb;
info3='Tratamiento de señales II!';
%info='Cambio mi vida por lámparas viejas o por los dados con los que se jugó la túnica inconsútil; por lo más anodino, por lo más obvio, por lo más fútil; por los colgajos que se guinda en las orejas la simiesca mulata, la terracota nubia; la pálida morena, la amarilla oriental, o la hiperbórea rubia; cambio mi vida por una anilla de hojalata o por la espada de Sigmundo, o por el mundo que tenía en los dedos Carlomagno: -para echar a rodar la bola..';
byte=8; 
info_enbin3=reshape(dec2bin(info3,byte).'-'0',1,[]);
len_info3=length(info_enbin3);
arreglo_info3=reshape(info_enbin3,4,(len_info3/4));
sep3=(len_info3/4); %separar el mensaje en 4bits

mensajecon_pari3=zeros(7,sep3);  %mensaje con bits de paridad
%operador logica XOR para mensaje a transmitir
for n=1 :sep3
    c=xor(arreglo_info3(1,n),arreglo_info3(2,n));
    x=xor(c,arreglo_info3(4,n)); 
    if x==1
        x1=1;
        mensajecon_pari3(1,n)=x1;
    else 
        x1=0;
        mensajecon_pari3(1,n)=x1;
    end 
    e=xor(arreglo_info3(1,n),arreglo_info3(3,n));
    y=xor(e,arreglo_info3(4,n));
    if y==1
        x2=1;
        mensajecon_pari3(2,n)=x2;
    else 
        x2=0;
        mensajecon_pari3(2,n)=x2;
    end 
    f=xor(arreglo_info3(2,n),arreglo_info3(3,n));
    z=xor(f,arreglo_info3(4,n));
    if z==1
        x3=1;
        mensajecon_pari3(4,n)=x3;
    else 
        x3=0;
        mensajecon_pari3(4,n)=x3;
    end 
        mensajecon_pari3(3,n)=arreglo_info3(1,n);
        mensajecon_pari3(5,n)=arreglo_info3(2,n);
        mensajecon_pari3(6,n)=arreglo_info3(3,n);
        mensajecon_pari3(7,n)=arreglo_info3(4,n);
end
%reorganizar el mensaje
codificacion3=reshape(mensajecon_pari3,1,(sep3*7));
leng_cod=length(codificacion3);
mensaje3.time=[];
mensaje3.signals.values=[sin_info';bandera';codificacion3'];
mensaje3.signals.dimension=1;
tiemposimu=(length(bandera)+length(sin_info)+length(codificacion3)+5)/Rb;
Datos=length(codificacion3);