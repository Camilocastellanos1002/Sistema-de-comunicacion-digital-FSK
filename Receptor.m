%lectura de mensaje recibido
menrx=length(mensajerx); 
new_menrx=[];
if abs(menrx-length(codificacion))==2
    for i=2: menrx
        new_menrx(i-1,1)=mensajerx (i,1);
        new_menrx(menrx,1)=0;
        new_menrx(menrx+1,1)=0;
        new_menrx(menrx+2,1)=0;
        new_menrx(menrx+3,1)=0;
        new_menrx(menrx+4,1)=0;
        new_menrx(menrx+5,1)=0;   
end
elseif abs(menrx -length(codificacion))==0
         for i=1: menrx
            new_menrx(i,1)= mensajerx(i,1);
         end 
end
%reescribir el mensaje 
len_men=length(new_menrx);     
mensajerecibido=reshape(new_menrx',7,(len_men/7));
k=len_men/7;
%separar bits de bits de paridad
datos=zeros(4,k);
for j=1 :k  
    datos(1,j)= mensajerecibido(3,j);
    datos(2,j)=mensajerecibido(5,j);
    datos(3,j) =mensajerecibido(6,j);
    datos(4,j) =mensajerecibido(7,j);
end
for j=1 :k  
    bu(1,j)= mensajerecibido(1,j);
     bu(2,j)=mensajerecibido(2,j);
     bu(3,j) =mensajerecibido(4,j);
   
end
pariedad=zeros(3,k);
%operacion logica para detectar bits
for n=1 :length(datos)

    c=xor(datos(1,n),datos(2,n));
    x=xor(c,datos(4,n));

     if x==1
        x1r=1;
        pariedad(1,n)=x1r;

     else 
        x1r=0;
        pariedad(1,n)=x1r;
     end 
    e=xor(datos(1,n),datos(3,n));
    y=xor(e,datos(4,n));

    if y==1
        x2r=1;
          pariedad(2,n)=x2r;
    else 
        x2r=0;
        pariedad(2,n)=x2r;
    end 
    f=xor(datos(2,n),datos(3,n));
    zr=xor(f,datos(4,n));

    if zr==1
        x3r=1;
        pariedad(3,n)=x3r;
    else 
        x3r=0;
        pariedad(3,n)=x3r;
    end 
   
end

if bu==pariedad;
    error=0;
else 
    error=1;
end
[m,n] = size(datos);
datos=reshape(datos,1,4*n);
datos=datos';
code=[datos;zeros(8-mod(length(datos),8),1)];
palabra=reshape(code',8,[])';
texto='';
for i=1: length(palabra(:,1))
    s=num2str(palabra(i,:));
    s(s==' ')='';
    texto=[texto,bin2dec(s)];
end

disp(['Mensaje Recibido: ' texto]);