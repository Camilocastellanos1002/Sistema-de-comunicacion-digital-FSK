%% lectura de mensaje recibido #2
menrx2=length(mensajerx2); 
new_menrx2=[];
if abs(menrx2-length(codificacion2))==2
    for i=2: menrx2
        new_menrx2(i-1,1)=mensajerx2 (i,1);
        new_menrx2(menrx2,1)=0;
        new_menrx2(menrx2+1,1)=0;
        new_menrx2(menrx2+2,1)=0;
        new_menrx2(menrx2+3,1)=0;
        new_menrx2(menrx2+4,1)=0;
        new_menrx2(menrx2+5,1)=0;   
end
elseif abs(menrx2 -length(codificacion2))==0
         for i=1: menrx2
            new_menrx2(i,1)= mensajerx2(i,1);
         end 
end
%reescribir el mensaje 
len_men2=length(new_menrx2);     
mensajerecibido2=reshape(new_menrx2',7,(len_men2/7));
k=len_men2/7;
%separar bits de bits de paridad
datos2=zeros(4,k);
for j=1 :k  
    datos2(1,j)= mensajerecibido2(3,j);
    datos2(2,j)=mensajerecibido2(5,j);
    datos2(3,j) =mensajerecibido2(6,j);
    datos2(4,j) =mensajerecibido2(7,j);
end
bu2=0;
for j=1 :k  
    bu2(1,j)= mensajerecibido2(1,j);
     bu2(2,j)=mensajerecibido2(2,j);
     bu2(3,j) =mensajerecibido2(4,j);
   
end
pariedad=zeros(3,k);
%operacion logica para detectar bits
for n=1 :length(datos2)

    c=xor(datos2(1,n),datos2(2,n));
    x=xor(c,datos2(4,n));

     if x==1
        x1r=1;
        pariedad(1,n)=x1r;

     else 
        x1r=0;
        pariedad2(1,n)=x1r;
     end 
    e=xor(datos2(1,n),datos2(3,n));
    y=xor(e,datos2(4,n));

    if y==1
        x2r=1;
          pariedad(2,n)=x2r;
    else 
        x2r=0;
        pariedad(2,n)=x2r;
    end 
    f=xor(datos2(2,n),datos2(3,n));
    zr=xor(f,datos2(4,n));

    if zr==1
        x3r=1;
        pariedad(3,n)=x3r;
    else 
        x3r=0;
        pariedad(3,n)=x3r;
    end 
   
end

if bu2==pariedad;
    error=0;
else 
    error=1;
end
[m1,n1] = size(datos2);
datos2=reshape(datos2,1,4*n1);
datos2=datos2';
code2=[datos2;zeros(8-mod(length(datos2),8),1)];
palabra2=reshape(code2',8,[])';
texto2='';
for i=1: length(palabra2(:,1))
    s2=num2str(palabra2(i,:));
    s2(s2==' ')='';
    texto2=[texto2,bin2dec(s2)];
end

disp(['Segundo mensaje Recibido: ' texto2]);

