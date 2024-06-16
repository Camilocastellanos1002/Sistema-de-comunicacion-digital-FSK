
RemovedBits = 14+25;                                                                %Bits de control y palabra Barker.
Signal_rx1 = double(out.Salida1(RemovedBits:length(InfoHamming1)+RemovedBits-1));   %Señal #1 recibida.
fprintf('\n');
disp(['Para el Mensaje #1:']);
[errors1, text1, text_fixed1] = decoder(Signal_rx1, InfoHamming1, FL1);
Signal_rx2 = double(out.Salida2(RemovedBits:length(InfoHamming2)+RemovedBits-1));   %Señal #2 recibida. 
fprintf('\n');
disp(['Para el Mensaje #2:']);
[errors2, text2, text_fixed2] = decoder(Signal_rx2, InfoHamming2, FL2);


function [errors,text,text_fixed]= decoder(Signal_rx, InfoHamming, FL)

MatrixH = [1 1 0 1 1 0 0;1 0 1 1 0 1 0;0 1 1 1 0 0 1];
Signalrx = Signal_rx.';
s = strfind(Signalrx,FL);
s = s(1);
if s ~= 1
    for j = 1:length(Signal_rx)
        if s+j-1 >= length(Signal_rx)
            Aux_vec(j,1) = 0;
        else
            Aux_vec(j,1) = Signal_rx(s+j-1);
        end
    end
Signal_rxtemp = Signal_rx;
Signal_rx = Aux_vec;
end

HammingCodrx = reshape(Signal_rx,7,[])';                   %Re-organizamos la información recibida.
HammingCodrx_fixed = HammingCodrx;                         %Copiamos los datos para corregirlos posteriormente.
HammingCodrx_fixed(:,[5 6 7]) = [];                        %Se borran los datos no correspondientes a información.
Syndrome = MatrixH * HammingCodrx';                        %Obtenemos el síndrome al realizar el producto matricial.
DimSyndrome = size(Syndrome);                              %Obtenemos el tamaño del síndrome.

%Se remueven los valores no binarios que aparecen como producto de la multiplicación matricial.
for j = 1:DimSyndrome(2)                            %Recorremos las columnas de la matríz resultante.
    for i = 1:3  
        if mod(Syndrome(i,j),2) == 0
          Syndrome(i,j) = 0;
        else
          Syndrome(i,j) = 1;
        end
    end
   
%Corrección de errores. 
%Las columnas de MatrixH indican la posicion del bit con error en HammingCod.
    for k = 1:4                         %Recorremos las columnas de MatrixH buscando similitudes con síndrome.
        if MatrixH(:,k) == Syndrome(:,j)
            if HammingCodrx_fixed(j,k) == 0
                HammingCodrx_fixed(j,k) = 1;
            else
                HammingCodrx_fixed(j,k) = 0;
            end
            x = ['Corrección en HammingCodrx: col=', num2str(k) ' fila= ', num2str(j)];
            disp(x)
        end
    end
end

%Decodificación
InfoHammingCodrx = HammingCodrx;                            %Utilizamos HammingCodrx (copia sin corrección de errores).
InfoHammingCodrx(:,[5 6 7]) = [];                           %Se borran los datos no correspondientes a información.

Inforx = reshape(InfoHammingCodrx',1,[]);                   %Convertimos la información recibida en un vector fila.
Inforx_fixed = reshape(HammingCodrx_fixed',1,[]);
text = '';
text_fixed = '';

%Decodificación para la información sin corregir.
j = 8;
for i = 1:8:DimSyndrome(2)*4    
    newchar = char(bin2dec(num2str(Inforx(i:j))));
    text = [text, newchar];
    j = j+8;
end

%Decodificación para la información corregida.
j = 8;
for i = 1:8:DimSyndrome(2)*4    
    newchar = char(bin2dec(num2str(Inforx_fixed(i:j))));
    text_fixed = [text_fixed, newchar];
    j = j+8;
end

errors = biterr(Signal_rx, InfoHamming');
disp(['Mensaje Decodificado sin corregir: ' text]);
disp(['Mensaje Decodificado corregido: ' text_fixed]);
disp(['Se tienen : ' num2str(errors) ' Errores en la información']);
end
