%Relato de Sergio Stepanski:    
%Juego mi vida, cambio mi vida,
%de todos modos
%la llevo perdida...
%Y la juego o la cambio por el más infantil espejismo,
%la dono en usufructo, o la regalo...

Infotxt1 = 'Juego mi vida, cambio mi vida, de todos modos la llevo perdida... Y la juego';
[Message1,InfoHamming1,FL1] = coder(Infotxt1);
Infotxt2 = 'o la cambio por el más infantil espejismo, la dono en usufructo, o la regalo...';
[Message2,InfoHamming2,FL2] = coder(Infotxt2);
Timesim = inf;                                          

function [Message,InfoHamming,FL] = coder(Infotxt)

Infobin = reshape(dec2bin(Infotxt,8).',1,[])-'0'; 
Infoblocks = reshape(Infobin,4,[])';

MatrixG = [1 0 0 0 1 1 0;0 1 0 0 1 0 1;0 0 1 0 0 1 1;0 0 0 1 1 1 1];
MatixP = [1 1 0;1 0 1;0 1 1;1 1 1];
HammingCod = Infoblocks * MatrixG;                  %Bits de paridad agregados al multiplicar la información con la matriz G.
Dim = size(HammingCod);

%Se remueven los valores no binarios que aparecen como producto de la multiplicación matricial.
for i = 1:Dim(1)                            %Recorremos las filas de la matriz resultante.
   for j = 5:7
      if mod(HammingCod(i,j),2) == 0        %Reemplazamos los valores no binarios por 0.
          HammingCod(i,j) = 0;
      else
          HammingCod(i,j) = 1;
      end
   end
end
FL = HammingCod(1:1, :);

Barker = [1 1 1 1 1 0 0 1 1 0 1 0 1];       %Generamos una palabra Barker.
for n = 1:10                                %Generamos una secuencia de bits de control para el mensaje a enviar.
    if n <= 5
        IniSeq(n) = 1;
    else
        IniSeq(n) = 0;
    end
end
for n = 10:25
    if mod(n,2) == 0
        IniSeq(n) = 0;
    else
        IniSeq(n) = 1;
    end
end

InfoHamming = reshape(HammingCod',1,[]);                       %Convertimos la matriz Hamming en un vector fila.
Message.time = [];
Message.signals.values = [IniSeq';Barker';InfoHamming'];       %Concatenamos los bits de control, la palabra Barker y la info.
Message.signals.dimension = 1;

end
 