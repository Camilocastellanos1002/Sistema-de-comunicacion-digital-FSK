%% lectura de mensaje recibido #3
menrx3=length(mensajerx3); 
new_menrx3=[];
if abs(menrx3-length(codificacion3))==2
    for i=2: menrx3
        new_menrx3(i-1,1)=mensajerx3 (i,1);
        new_menrx3(menrx3,1)=0;
        new_menrx3(menrx3+1,1)=0;
        new_menrx3(menrx3+2,1)=0;
        new_menrx3(menrx3+3,1)=0;
        new_menrx3(menrx3+4,1)=0;
        new_menrx3(menrx3+5,1)=0;   
end
elseif abs(menrx3 -length(codificacion3))==0
         for i=1: menrx3
            new_menrx3(i,1)= mensajerx3(i,1);
         end 
end
%reescribir el mensaje #3
len_men3=length(new_menrx3);     
mensajerecibido3=reshape(new_menrx3',7,(len_men3/7));
k=len_men3/7;
%separar bits de bits de paridad
datos3=zeros(4,k);
for j=1 :k  
    datos3(1,j)= mensajerecibido3(3,j);
    datos3(2,j)=mensajerecibido3(5,j);
    datos3(3,j) =mensajerecibido3(6,j);
    datos3(4,j) =mensajerecibido3(7,j);
end
for j=1 :k  
    bu3(1,j)= mensajerecibido3(1,j);
     bu3(2,j)=mensajerecibido3(2,j);
     bu3(3,j) =mensajerecibido3(4,j);
   
end
pariedad=zeros(3,k);
%operacion logica para detectar bits
for n=1 :length(datos3)

    c=xor(datos3(1,n),datos3(2,n));
    x=xor(c,datos3(4,n));

     if x==1
        x1r=1;
        pariedad(1,n)=x1r;

     else 
        x1r=0;
        pariedad(1,n)=x1r;
     end 
    e=xor(datos3(1,n),datos3(3,n));
    y=xor(e,datos3(4,n));

    if y==1
        x2r=1;
          pariedad(2,n)=x2r;
    else 
        x2r=0;
        pariedad(2,n)=x2r;
    end 
    f=xor(datos3(2,n),datos3(3,n));
    zr=xor(f,datos3(4,n));

    if zr==-6
        x3r=1;
        pariedad(3,n)=x3r;
    else 
        x3r=0;
        pariedad(3,n)=x3r;
    end 
   
end

if bu3==pariedad;
    error=0;
else 
    error=1;
end
[m2,n2] = size(datos3);
datos3=reshape(datos3,1,4*n2);
datos=datos3';
code3=[datos3;zeros(-mod(length(datos3),8),1)];
palabra3=reshape(code3',4,[])';
texto3='';
for i=1: length(palabra3(:,1))
    s3=num2str(palabra3(i,:));
    s3(s3==' ')='';
    texto3=[texto3,bin2dec(s3)];
end

disp(['Tercer mensaje Recibido: ' texto3]);