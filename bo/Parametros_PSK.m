%Sistema de comunicaciones en Banda base:

Rb = 50000;                         %Rata en bps
Frec_port = 1000000;                        
Tb = 1 / Rb;                        %Tiempo de bit
Amplitud = 1;                       %Amplitud de los pulsos enviados.
Long_Canal = 30;                    %Distancia del canal en km 3-6 13-18 25-30
GT = 1.2589;                        %dB
Gr = 1.2589;                        %dB
Lambda = 3e8 / Frec_port;           %m
Att_dB= 22 + 20 * log10(Long_Canal * 1000 / Lambda)- GT - Gr;
Att_pot_Canal = 10^(Att_dB / 10);
Att_Volt_Canal = 10^(Att_dB / 20);
C_luz = 3e5;                            %Velocidad onda electromagnética en el vacio 
C_canal = C_luz;                        %Velocidad en el cable
Retraso_Canal = Long_Canal / C_canal;   %Retraso del canal en segundos
Retraso_filtro = 0.75 * Tb;
%Retraso_decision = Tb
Retraso_total = Retraso_Canal + Retraso_filtro;

%Probabilidad de error de bit:
Prob_error = 1e-3;                            
switch Prob_error
    case 1e-1
        x = 1.3;
    case 1e-2
        x = 2.4;
    case 1e-3
        x = 3.1;
    case 1e-4
        x = 3.8;
    case 1e-5
        x = 4.3;
    case 1e-6
        x = 4.8;
end

%Esquemas de representación de bits:
Representacion = 3;                         %Tipo: 1:RZ, 2:NRZ-Unipolar, 3:NRZ polar
switch Representacion
    case 1
        k = 0.5;
        Energia_transmitida = 0.9 * (Amplitud^2) / (4 * Rb);
        Ancho_banda_minimo = Rb / 2;
        Energia_recibida = Energia_transmitida / Att_pot_Canal;
        Umbral = Energia_recibida / 2;
    case 2
        k = 0.5;
        Energia_transmitida = 0.9 * (Amplitud^2) / (2*Rb);
        Ancho_banda_minimo = Rb / 2;
        Energia_recibida = Energia_transmitida / Att_pot_Canal;
        Umbral = Energia_recibida / 2;
    case 3
        k = 2;
        Energia_transmitida = 0.9 * (Amplitud^2) /(2 * Rb);
        Ancho_banda_minimo = Rb;
        Energia_recibida = Energia_transmitida / Att_pot_Canal;
        Umbral = 0;
end

eta = k * Energia_recibida / (x^2);
Pot_Ruido = eta * Ancho_banda_minimo;
N = 10;                                   
Delta = Tb / N;                         %N=número de retrasos

%Sincronismo de portadora:
Ts = Tb / 5;
zeta = 0.8;
Kp = 0.5;
Kv = 2 * pi * 1E6;
wn = 4.5 / Ts;
C = 1e-6;                               %Capacitancia 
R1 = Kp * Kv / (wn^2 * C);
R2 = 2 * zeta / (wn * C);
kv2 = Rb^2 / 10;
b = 0.6;