  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 7;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtP)
    ;%
      section.nData     = 20;
      section.data(20)  = dumData; %prealloc
      
	  ;% rtP.Atenuacion_canal
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.C
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.Datos
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtP.Frec1
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtP.Frec2
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtP.R1
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtP.R2
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtP.Rb
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtP.Retraso_canal
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtP.kv
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtP.kv2
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtP.CompareToConstant_const
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtP.GaussianNoiseGenerator_d
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtP.SampleandHold_ic
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtP.SampleandHold_ic_jlfvpcljxw
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtP.SampleandHold_ic_lzb14dyui4
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtP.GaussianNoiseGenerator_m
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtP.GaussianNoiseGenerator_m_pvxm3ngdo5
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtP.GaussianNoiseGenerator_s
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtP.GaussianNoiseGenerator_s_mqeqzkwvys
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtP.Monostable1_ic
	  section.data(1).logicalSrcIdx = 20;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.Monostable_ic
	  section.data(2).logicalSrcIdx = 21;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.Monostable1_ic_bkmb1fdrhz
	  section.data(3).logicalSrcIdx = 22;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 105;
      section.data(105)  = dumData; %prealloc
      
	  ;% rtP._Y0
	  section.data(1).logicalSrcIdx = 23;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP._Y0_db5voyihuo
	  section.data(2).logicalSrcIdx = 24;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP._Y0_bdpgvrnswx
	  section.data(3).logicalSrcIdx = 25;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtP.Integrator_IC
	  section.data(4).logicalSrcIdx = 26;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtP.ModuloIntegrator_IC
	  section.data(5).logicalSrcIdx = 27;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue
	  section.data(6).logicalSrcIdx = 28;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue
	  section.data(7).logicalSrcIdx = 29;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtP.Switch2_Threshold
	  section.data(8).logicalSrcIdx = 30;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtP.Integrator_IC_nblk03gvyi
	  section.data(9).logicalSrcIdx = 31;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtP.Filtro_A
	  section.data(10).logicalSrcIdx = 32;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtP.Filtro_B
	  section.data(11).logicalSrcIdx = 33;
	  section.data(11).dtTransOffset = 16;
	
	  ;% rtP.Filtro_C
	  section.data(12).logicalSrcIdx = 34;
	  section.data(12).dtTransOffset = 17;
	
	  ;% rtP.Filtro_InitialCondition
	  section.data(13).logicalSrcIdx = 35;
	  section.data(13).dtTransOffset = 18;
	
	  ;% rtP.Informacion_Data0
	  section.data(14).logicalSrcIdx = 37;
	  section.data(14).dtTransOffset = 19;
	
	  ;% rtP.ModuloIntegrator_IC_apzvenlzc5
	  section.data(15).logicalSrcIdx = 38;
	  section.data(15).dtTransOffset = 201;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue_o4nt1k5w0o
	  section.data(16).logicalSrcIdx = 39;
	  section.data(16).dtTransOffset = 202;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue_ehdhuzchfk
	  section.data(17).logicalSrcIdx = 40;
	  section.data(17).dtTransOffset = 203;
	
	  ;% rtP.TransportDelay_Delay
	  section.data(18).logicalSrcIdx = 41;
	  section.data(18).dtTransOffset = 204;
	
	  ;% rtP.TransportDelay_InitOutput
	  section.data(19).logicalSrcIdx = 42;
	  section.data(19).dtTransOffset = 205;
	
	  ;% rtP.TransportDelay_InitOutput_npzkuu2dfa
	  section.data(20).logicalSrcIdx = 43;
	  section.data(20).dtTransOffset = 206;
	
	  ;% rtP.RandomNumber_Mean
	  section.data(21).logicalSrcIdx = 44;
	  section.data(21).dtTransOffset = 207;
	
	  ;% rtP.RandomNumber_StdDev
	  section.data(22).logicalSrcIdx = 45;
	  section.data(22).dtTransOffset = 208;
	
	  ;% rtP.Buffer_ic
	  section.data(23).logicalSrcIdx = 46;
	  section.data(23).dtTransOffset = 209;
	
	  ;% rtP.TransportDelay_Delay_lnyuh05kkd
	  section.data(24).logicalSrcIdx = 47;
	  section.data(24).dtTransOffset = 210;
	
	  ;% rtP.TransportDelay_InitOutput_g2gukl3g33
	  section.data(25).logicalSrcIdx = 48;
	  section.data(25).dtTransOffset = 211;
	
	  ;% rtP.TransportDelay_InitOutput_itctaj4ekg
	  section.data(26).logicalSrcIdx = 49;
	  section.data(26).dtTransOffset = 212;
	
	  ;% rtP.PulseGenerator_Amp
	  section.data(27).logicalSrcIdx = 50;
	  section.data(27).dtTransOffset = 213;
	
	  ;% rtP.PulseGenerator_Duty
	  section.data(28).logicalSrcIdx = 51;
	  section.data(28).dtTransOffset = 214;
	
	  ;% rtP.PulseGenerator_PhaseDelay
	  section.data(29).logicalSrcIdx = 52;
	  section.data(29).dtTransOffset = 215;
	
	  ;% rtP.TransportDelay12_Delay
	  section.data(30).logicalSrcIdx = 53;
	  section.data(30).dtTransOffset = 216;
	
	  ;% rtP.TransportDelay12_InitOutput
	  section.data(31).logicalSrcIdx = 54;
	  section.data(31).dtTransOffset = 217;
	
	  ;% rtP.TransportDelay2_InitOutput
	  section.data(32).logicalSrcIdx = 55;
	  section.data(32).dtTransOffset = 218;
	
	  ;% rtP.TransportDelay1_InitOutput
	  section.data(33).logicalSrcIdx = 56;
	  section.data(33).dtTransOffset = 219;
	
	  ;% rtP.TransportDelay4_InitOutput
	  section.data(34).logicalSrcIdx = 57;
	  section.data(34).dtTransOffset = 220;
	
	  ;% rtP.TransportDelay3_InitOutput
	  section.data(35).logicalSrcIdx = 58;
	  section.data(35).dtTransOffset = 221;
	
	  ;% rtP.TransportDelay6_InitOutput
	  section.data(36).logicalSrcIdx = 59;
	  section.data(36).dtTransOffset = 222;
	
	  ;% rtP.TransportDelay5_InitOutput
	  section.data(37).logicalSrcIdx = 60;
	  section.data(37).dtTransOffset = 223;
	
	  ;% rtP.TransportDelay8_InitOutput
	  section.data(38).logicalSrcIdx = 61;
	  section.data(38).dtTransOffset = 224;
	
	  ;% rtP.TransportDelay7_InitOutput
	  section.data(39).logicalSrcIdx = 62;
	  section.data(39).dtTransOffset = 225;
	
	  ;% rtP.TransportDelay9_InitOutput
	  section.data(40).logicalSrcIdx = 63;
	  section.data(40).dtTransOffset = 226;
	
	  ;% rtP.TransportDelay11_InitOutput
	  section.data(41).logicalSrcIdx = 64;
	  section.data(41).dtTransOffset = 227;
	
	  ;% rtP.TransportDelay10_InitOutput
	  section.data(42).logicalSrcIdx = 65;
	  section.data(42).dtTransOffset = 228;
	
	  ;% rtP.TransportDelay13_InitOutput
	  section.data(43).logicalSrcIdx = 66;
	  section.data(43).dtTransOffset = 229;
	
	  ;% rtP.Switch_Threshold
	  section.data(44).logicalSrcIdx = 67;
	  section.data(44).dtTransOffset = 230;
	
	  ;% rtP.Switch1_Threshold
	  section.data(45).logicalSrcIdx = 68;
	  section.data(45).dtTransOffset = 231;
	
	  ;% rtP.RandomNumber_Mean_n4x5jyjuez
	  section.data(46).logicalSrcIdx = 69;
	  section.data(46).dtTransOffset = 232;
	
	  ;% rtP.RandomNumber_StdDev_ojydngz0lp
	  section.data(47).logicalSrcIdx = 70;
	  section.data(47).dtTransOffset = 233;
	
	  ;% rtP.MatrixGain_Gain
	  section.data(48).logicalSrcIdx = 71;
	  section.data(48).dtTransOffset = 234;
	
	  ;% rtP.Buffer_ic_lzvqyw2ni2
	  section.data(49).logicalSrcIdx = 72;
	  section.data(49).dtTransOffset = 235;
	
	  ;% rtP.TransportDelay1_InitOutput_ge1vnqoztc
	  section.data(50).logicalSrcIdx = 73;
	  section.data(50).dtTransOffset = 236;
	
	  ;% rtP.TransportDelay_InitOutput_bd4zohbbpk
	  section.data(51).logicalSrcIdx = 74;
	  section.data(51).dtTransOffset = 237;
	
	  ;% rtP.Filtro_A_almvbenuye
	  section.data(52).logicalSrcIdx = 75;
	  section.data(52).dtTransOffset = 238;
	
	  ;% rtP.Filtro_B_cz4ovtnlbh
	  section.data(53).logicalSrcIdx = 76;
	  section.data(53).dtTransOffset = 249;
	
	  ;% rtP.Filtro_C_l0jcyicm4y
	  section.data(54).logicalSrcIdx = 77;
	  section.data(54).dtTransOffset = 250;
	
	  ;% rtP.Filtro_InitialCondition_ixj5gjnfdp
	  section.data(55).logicalSrcIdx = 78;
	  section.data(55).dtTransOffset = 251;
	
	  ;% rtP.Integrator_IC_dfzts412q5
	  section.data(56).logicalSrcIdx = 79;
	  section.data(56).dtTransOffset = 252;
	
	  ;% rtP.Integrator1_IC
	  section.data(57).logicalSrcIdx = 80;
	  section.data(57).dtTransOffset = 253;
	
	  ;% rtP.TransportDelay_InitOutput_ac2nn3i4uy
	  section.data(58).logicalSrcIdx = 81;
	  section.data(58).dtTransOffset = 254;
	
	  ;% rtP.TransportDelay1_InitOutput_dc05214qlk
	  section.data(59).logicalSrcIdx = 82;
	  section.data(59).dtTransOffset = 255;
	
	  ;% rtP.ModuloIntegrator_IC_mhkqbc55cu
	  section.data(60).logicalSrcIdx = 83;
	  section.data(60).dtTransOffset = 256;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue_l42cys1cux
	  section.data(61).logicalSrcIdx = 84;
	  section.data(61).dtTransOffset = 257;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue_fozsdgujhv
	  section.data(62).logicalSrcIdx = 85;
	  section.data(62).dtTransOffset = 258;
	
	  ;% rtP.Integrator_IC_hiwtnk3vzy
	  section.data(63).logicalSrcIdx = 86;
	  section.data(63).dtTransOffset = 259;
	
	  ;% rtP.ModuloIntegrator_IC_pwbk55yuz2
	  section.data(64).logicalSrcIdx = 87;
	  section.data(64).dtTransOffset = 260;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue_cqbjibrf3p
	  section.data(65).logicalSrcIdx = 88;
	  section.data(65).dtTransOffset = 261;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue_nzxqkuyo3a
	  section.data(66).logicalSrcIdx = 89;
	  section.data(66).dtTransOffset = 262;
	
	  ;% rtP.Integrator1_IC_ggm3f24kg1
	  section.data(67).logicalSrcIdx = 90;
	  section.data(67).dtTransOffset = 263;
	
	  ;% rtP.Constant_Value
	  section.data(68).logicalSrcIdx = 91;
	  section.data(68).dtTransOffset = 264;
	
	  ;% rtP.Constant5_Value
	  section.data(69).logicalSrcIdx = 92;
	  section.data(69).dtTransOffset = 265;
	
	  ;% rtP.Constant6_Value
	  section.data(70).logicalSrcIdx = 93;
	  section.data(70).dtTransOffset = 266;
	
	  ;% rtP.Constant_Value_pgh0qhw5wr
	  section.data(71).logicalSrcIdx = 94;
	  section.data(71).dtTransOffset = 267;
	
	  ;% rtP.Constant1_Value
	  section.data(72).logicalSrcIdx = 95;
	  section.data(72).dtTransOffset = 268;
	
	  ;% rtP.posedge_Value
	  section.data(73).logicalSrcIdx = 96;
	  section.data(73).dtTransOffset = 269;
	
	  ;% rtP.negedge_Value
	  section.data(74).logicalSrcIdx = 97;
	  section.data(74).dtTransOffset = 271;
	
	  ;% rtP.eitheredge_Value
	  section.data(75).logicalSrcIdx = 98;
	  section.data(75).dtTransOffset = 273;
	
	  ;% rtP.Constant_Value_czlel2g4xm
	  section.data(76).logicalSrcIdx = 99;
	  section.data(76).dtTransOffset = 275;
	
	  ;% rtP.Constant1_Value_bx4tgv4ysd
	  section.data(77).logicalSrcIdx = 100;
	  section.data(77).dtTransOffset = 276;
	
	  ;% rtP.posedge_Value_dx0lu3aoqz
	  section.data(78).logicalSrcIdx = 101;
	  section.data(78).dtTransOffset = 277;
	
	  ;% rtP.negedge_Value_kjod1cdk3f
	  section.data(79).logicalSrcIdx = 102;
	  section.data(79).dtTransOffset = 279;
	
	  ;% rtP.eitheredge_Value_mhaz3orisj
	  section.data(80).logicalSrcIdx = 103;
	  section.data(80).dtTransOffset = 281;
	
	  ;% rtP.Constant1_Value_ju0tizjign
	  section.data(81).logicalSrcIdx = 104;
	  section.data(81).dtTransOffset = 283;
	
	  ;% rtP.Constant10_Value
	  section.data(82).logicalSrcIdx = 105;
	  section.data(82).dtTransOffset = 284;
	
	  ;% rtP.Constant11_Value
	  section.data(83).logicalSrcIdx = 106;
	  section.data(83).dtTransOffset = 285;
	
	  ;% rtP.Constant12_Value
	  section.data(84).logicalSrcIdx = 107;
	  section.data(84).dtTransOffset = 286;
	
	  ;% rtP.Constant13_Value
	  section.data(85).logicalSrcIdx = 108;
	  section.data(85).dtTransOffset = 287;
	
	  ;% rtP.Constant14_Value
	  section.data(86).logicalSrcIdx = 109;
	  section.data(86).dtTransOffset = 288;
	
	  ;% rtP.Constant15_Value
	  section.data(87).logicalSrcIdx = 110;
	  section.data(87).dtTransOffset = 289;
	
	  ;% rtP.Constant16_Value
	  section.data(88).logicalSrcIdx = 111;
	  section.data(88).dtTransOffset = 290;
	
	  ;% rtP.Constant17_Value
	  section.data(89).logicalSrcIdx = 112;
	  section.data(89).dtTransOffset = 291;
	
	  ;% rtP.Constant18_Value
	  section.data(90).logicalSrcIdx = 113;
	  section.data(90).dtTransOffset = 292;
	
	  ;% rtP.Constant19_Value
	  section.data(91).logicalSrcIdx = 114;
	  section.data(91).dtTransOffset = 293;
	
	  ;% rtP.Constant2_Value
	  section.data(92).logicalSrcIdx = 115;
	  section.data(92).dtTransOffset = 294;
	
	  ;% rtP.Constant20_Value
	  section.data(93).logicalSrcIdx = 116;
	  section.data(93).dtTransOffset = 295;
	
	  ;% rtP.Constant3_Value
	  section.data(94).logicalSrcIdx = 117;
	  section.data(94).dtTransOffset = 296;
	
	  ;% rtP.Constant4_Value
	  section.data(95).logicalSrcIdx = 118;
	  section.data(95).dtTransOffset = 297;
	
	  ;% rtP.Constant5_Value_ak2ogm0bur
	  section.data(96).logicalSrcIdx = 119;
	  section.data(96).dtTransOffset = 298;
	
	  ;% rtP.Constant6_Value_mfzl25kers
	  section.data(97).logicalSrcIdx = 120;
	  section.data(97).dtTransOffset = 299;
	
	  ;% rtP.Constant7_Value
	  section.data(98).logicalSrcIdx = 121;
	  section.data(98).dtTransOffset = 300;
	
	  ;% rtP.Constant8_Value
	  section.data(99).logicalSrcIdx = 122;
	  section.data(99).dtTransOffset = 301;
	
	  ;% rtP.Constant9_Value
	  section.data(100).logicalSrcIdx = 123;
	  section.data(100).dtTransOffset = 302;
	
	  ;% rtP.Constant_Value_dufhvts2ca
	  section.data(101).logicalSrcIdx = 124;
	  section.data(101).dtTransOffset = 303;
	
	  ;% rtP.Constant1_Value_j11evhb4ur
	  section.data(102).logicalSrcIdx = 125;
	  section.data(102).dtTransOffset = 304;
	
	  ;% rtP.posedge_Value_arvlrnf2hc
	  section.data(103).logicalSrcIdx = 126;
	  section.data(103).dtTransOffset = 305;
	
	  ;% rtP.negedge_Value_abbvesy1jz
	  section.data(104).logicalSrcIdx = 127;
	  section.data(104).dtTransOffset = 307;
	
	  ;% rtP.eitheredge_Value_nb0pdzkjaa
	  section.data(105).logicalSrcIdx = 128;
	  section.data(105).dtTransOffset = 309;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% rtP._Y0_dwtojptuc5
	  section.data(1).logicalSrcIdx = 129;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.Memory_InitialCondition
	  section.data(2).logicalSrcIdx = 130;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.Memory_InitialCondition_meb2sac0hw
	  section.data(3).logicalSrcIdx = 131;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtP.Memory_InitialCondition_aqwb21zvmj
	  section.data(4).logicalSrcIdx = 132;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.cc2aoo0nhc.Out1_Y0
	  section.data(1).logicalSrcIdx = 133;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.dzgncmrria.Out1_Y0
	  section.data(1).logicalSrcIdx = 134;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.jgvwez5knrn.Out1_Y0
	  section.data(1).logicalSrcIdx = 135;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 11;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtB)
    ;%
      section.nData     = 73;
      section.data(73)  = dumData; %prealloc
      
	  ;% rtB.hao2kgiuqu
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.iea4dkyy2w
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.bui2nj5eby
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.f5hdbpawyv
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.mr1s0bxcpp
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.ghegbffnb0
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtB.echlwz23fd
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtB.ong5vjnb0y
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtB.iyoofertyx
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtB.brw1yh1ujs
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtB.ibhjdwhj0b
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtB.i1k4ywizrv
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtB.geskkhqdb3
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtB.gfobd5zpxv
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtB.jmi5xid0ph
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtB.jknu1nrhnz
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtB.kwwqn5rlhs
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtB.aemhoq5few
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtB.dkfpnckao5
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtB.fnydnbixk1
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtB.lbeln3akc2
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% rtB.jw32jpeck5
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% rtB.n5sbv1oypg
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% rtB.m22qmdpsyj
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% rtB.aqj0wixgbx
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24;
	
	  ;% rtB.hjpiowuzne
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 25;
	
	  ;% rtB.d2paa5zotr
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 26;
	
	  ;% rtB.f2wibvryef
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 27;
	
	  ;% rtB.jp5azcgtac
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 28;
	
	  ;% rtB.hagpe2nohf
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 29;
	
	  ;% rtB.kj3rknv443
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 30;
	
	  ;% rtB.axx1cycxep
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 31;
	
	  ;% rtB.dxcynwwxat
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 32;
	
	  ;% rtB.hpuvpoamzd
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 33;
	
	  ;% rtB.cqkmv0ulyy
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 34;
	
	  ;% rtB.fcjlyowfli
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 35;
	
	  ;% rtB.hs1qpln3nc
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 36;
	
	  ;% rtB.e15ao1bk3m
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 37;
	
	  ;% rtB.ooknyqiljy
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 38;
	
	  ;% rtB.ijufvlmorm
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 39;
	
	  ;% rtB.jsr2vw3sph
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 40;
	
	  ;% rtB.d1ncaq24su
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 41;
	
	  ;% rtB.mzfkqi1te1
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 42;
	
	  ;% rtB.nvde5gnl32
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 43;
	
	  ;% rtB.inulkftw3y
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 44;
	
	  ;% rtB.pdl3oaaxvv
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 45;
	
	  ;% rtB.bbud2xrwvw
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 46;
	
	  ;% rtB.nhklduoiog
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 47;
	
	  ;% rtB.ik1ga1yi4x
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 48;
	
	  ;% rtB.mpss00ytce
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 49;
	
	  ;% rtB.iuiswtbqno
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 50;
	
	  ;% rtB.ctnzwjmcme
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 51;
	
	  ;% rtB.kkn0pryfbs
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 52;
	
	  ;% rtB.oarcyjxd4w
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 53;
	
	  ;% rtB.h3jkxjjtu0
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 54;
	
	  ;% rtB.lwvzpms5bv
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 55;
	
	  ;% rtB.oru1g5vkau
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 56;
	
	  ;% rtB.jiqtvtg4mt
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 57;
	
	  ;% rtB.fwzg1qmdog
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 58;
	
	  ;% rtB.kaaziuo5ef
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 59;
	
	  ;% rtB.jwmjcxympi
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 60;
	
	  ;% rtB.ma2rvcr4nq
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 61;
	
	  ;% rtB.akirm2mhww
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 62;
	
	  ;% rtB.ftsmahysaw
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 63;
	
	  ;% rtB.furzsgxei5
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 64;
	
	  ;% rtB.kp4mtdwxq5
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 65;
	
	  ;% rtB.bd1h4kdhj0
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 66;
	
	  ;% rtB.f2kmaedy0v
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 67;
	
	  ;% rtB.btp22atm5y
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 69;
	
	  ;% rtB.hg4tfoauyd
	  section.data(70).logicalSrcIdx = 69;
	  section.data(70).dtTransOffset = 71;
	
	  ;% rtB.fmyjxkxyji
	  section.data(71).logicalSrcIdx = 70;
	  section.data(71).dtTransOffset = 73;
	
	  ;% rtB.lzdd3z4ueb
	  section.data(72).logicalSrcIdx = 71;
	  section.data(72).dtTransOffset = 74;
	
	  ;% rtB.jmfd3dtamo
	  section.data(73).logicalSrcIdx = 72;
	  section.data(73).dtTransOffset = 75;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% rtB.cbutxn4e51
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.n5sddkmaty
	  section.data(2).logicalSrcIdx = 74;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.bnbr20jdr4
	  section.data(3).logicalSrcIdx = 75;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.mdla3lhngq
	  section.data(4).logicalSrcIdx = 76;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.lisqze2m0v
	  section.data(5).logicalSrcIdx = 77;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.akkrfuecb2
	  section.data(6).logicalSrcIdx = 78;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtB.cpzsxqkvzb
	  section.data(7).logicalSrcIdx = 79;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtB.pk0yjglikg
	  section.data(8).logicalSrcIdx = 80;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtB.hu24p5k4qk
	  section.data(9).logicalSrcIdx = 81;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtB.plthkbxpdz
	  section.data(10).logicalSrcIdx = 82;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtB.m4lv3kzihg
	  section.data(11).logicalSrcIdx = 83;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.cvrfqtrsgv.ddvcjkqoaj
	  section.data(1).logicalSrcIdx = 84;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.b5dbwkwsrj.ighgnitevw
	  section.data(1).logicalSrcIdx = 85;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.cc2aoo0nhc.jzxmgvajvp
	  section.data(1).logicalSrcIdx = 86;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.cfrh4agkgq.ddvcjkqoaj
	  section.data(1).logicalSrcIdx = 87;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.awkevlz2ww.ighgnitevw
	  section.data(1).logicalSrcIdx = 88;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.dzgncmrria.jzxmgvajvp
	  section.data(1).logicalSrcIdx = 89;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.edzbs02xos1.ddvcjkqoaj
	  section.data(1).logicalSrcIdx = 90;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.fqkin25shtk.ighgnitevw
	  section.data(1).logicalSrcIdx = 91;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.jgvwez5knrn.jzxmgvajvp
	  section.data(1).logicalSrcIdx = 92;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 18;
    sectIdxOffset = 11;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtDW)
    ;%
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% rtDW.dzchlxvwf3
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.akzvs10hux
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.lzar0ld5iq
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.kqtr3qx2r4
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.f2j0l3sxg1
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.nea0jvgp55
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.j5zzyh4rpr
	  section.data(1).logicalSrcIdx = 6;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% rtDW.pjddaatqz2.modelTStart
	  section.data(1).logicalSrcIdx = 7;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.hnsh4hlcjf.modelTStart
	  section.data(2).logicalSrcIdx = 8;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.aodjfyn1vf.modelTStart
	  section.data(3).logicalSrcIdx = 9;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.glkz222vzv.modelTStart
	  section.data(4).logicalSrcIdx = 10;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.ncjovmrbg0.modelTStart
	  section.data(5).logicalSrcIdx = 11;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.klfxndpfsg.modelTStart
	  section.data(6).logicalSrcIdx = 12;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.d14s1qzuzq.modelTStart
	  section.data(7).logicalSrcIdx = 13;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.mxv0osx2ez.modelTStart
	  section.data(8).logicalSrcIdx = 14;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDW.ppmbxq52ac.modelTStart
	  section.data(9).logicalSrcIdx = 15;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDW.f0yw54erky.modelTStart
	  section.data(10).logicalSrcIdx = 16;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtDW.gpmkh0kcin.modelTStart
	  section.data(11).logicalSrcIdx = 17;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtDW.bdb0yzd0st.modelTStart
	  section.data(12).logicalSrcIdx = 18;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtDW.btck01pmwp.modelTStart
	  section.data(13).logicalSrcIdx = 19;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtDW.balgznqrxg.modelTStart
	  section.data(14).logicalSrcIdx = 20;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtDW.phjdmexj3l.modelTStart
	  section.data(15).logicalSrcIdx = 21;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtDW.la2whjw243.modelTStart
	  section.data(16).logicalSrcIdx = 22;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtDW.nqs2szczzo.modelTStart
	  section.data(17).logicalSrcIdx = 23;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtDW.nxgqhfx5gi.modelTStart
	  section.data(18).logicalSrcIdx = 24;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtDW.jszw02sccm.modelTStart
	  section.data(19).logicalSrcIdx = 25;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtDW.c3s5d5tdbo.modelTStart
	  section.data(20).logicalSrcIdx = 26;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtDW.pvm13mlbpg.modelTStart
	  section.data(21).logicalSrcIdx = 27;
	  section.data(21).dtTransOffset = 20;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 27;
      section.data(27)  = dumData; %prealloc
      
	  ;% rtDW.m12hjeojxl.LoggedData
	  section.data(1).logicalSrcIdx = 28;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.ap5xq1jhre.TimePtr
	  section.data(2).logicalSrcIdx = 29;
	  section.data(2).dtTransOffset = 2;
	
	  ;% rtDW.lv2dzfblr1.TUbufferPtrs
	  section.data(3).logicalSrcIdx = 30;
	  section.data(3).dtTransOffset = 3;
	
	  ;% rtDW.ifklj3sbrn.TUbufferPtrs
	  section.data(4).logicalSrcIdx = 31;
	  section.data(4).dtTransOffset = 5;
	
	  ;% rtDW.hd1c30tkpp.TUbufferPtrs
	  section.data(5).logicalSrcIdx = 32;
	  section.data(5).dtTransOffset = 7;
	
	  ;% rtDW.ge2wwzjib2.TUbufferPtrs
	  section.data(6).logicalSrcIdx = 33;
	  section.data(6).dtTransOffset = 9;
	
	  ;% rtDW.jshlet2ssp.TUbufferPtrs
	  section.data(7).logicalSrcIdx = 34;
	  section.data(7).dtTransOffset = 11;
	
	  ;% rtDW.pkzvqa1hj0.TUbufferPtrs
	  section.data(8).logicalSrcIdx = 35;
	  section.data(8).dtTransOffset = 13;
	
	  ;% rtDW.pviiww4mxm.TUbufferPtrs
	  section.data(9).logicalSrcIdx = 36;
	  section.data(9).dtTransOffset = 15;
	
	  ;% rtDW.dwlf21fnwg.TUbufferPtrs
	  section.data(10).logicalSrcIdx = 37;
	  section.data(10).dtTransOffset = 17;
	
	  ;% rtDW.bnamprjobf.TUbufferPtrs
	  section.data(11).logicalSrcIdx = 38;
	  section.data(11).dtTransOffset = 19;
	
	  ;% rtDW.lrrduccxok.TUbufferPtrs
	  section.data(12).logicalSrcIdx = 39;
	  section.data(12).dtTransOffset = 21;
	
	  ;% rtDW.fhjti1tiah.TUbufferPtrs
	  section.data(13).logicalSrcIdx = 40;
	  section.data(13).dtTransOffset = 23;
	
	  ;% rtDW.faivwg4izm.TUbufferPtrs
	  section.data(14).logicalSrcIdx = 41;
	  section.data(14).dtTransOffset = 25;
	
	  ;% rtDW.lw4b5iw0r0.TUbufferPtrs
	  section.data(15).logicalSrcIdx = 42;
	  section.data(15).dtTransOffset = 27;
	
	  ;% rtDW.nhj2clh5pd.TUbufferPtrs
	  section.data(16).logicalSrcIdx = 43;
	  section.data(16).dtTransOffset = 29;
	
	  ;% rtDW.d1uhchttm1.TUbufferPtrs
	  section.data(17).logicalSrcIdx = 44;
	  section.data(17).dtTransOffset = 31;
	
	  ;% rtDW.egilahlbnt.TUbufferPtrs
	  section.data(18).logicalSrcIdx = 45;
	  section.data(18).dtTransOffset = 33;
	
	  ;% rtDW.lxhyqkdxwz.TUbufferPtrs
	  section.data(19).logicalSrcIdx = 46;
	  section.data(19).dtTransOffset = 35;
	
	  ;% rtDW.a4exivx0tt.TUbufferPtrs
	  section.data(20).logicalSrcIdx = 47;
	  section.data(20).dtTransOffset = 37;
	
	  ;% rtDW.idcmakdjdp.TUbufferPtrs
	  section.data(21).logicalSrcIdx = 48;
	  section.data(21).dtTransOffset = 39;
	
	  ;% rtDW.j12ztdudf4.LoggedData
	  section.data(22).logicalSrcIdx = 49;
	  section.data(22).dtTransOffset = 41;
	
	  ;% rtDW.nyj02hk5rd.LoggedData
	  section.data(23).logicalSrcIdx = 50;
	  section.data(23).dtTransOffset = 45;
	
	  ;% rtDW.btwgfjuhwu.TUbufferPtrs
	  section.data(24).logicalSrcIdx = 51;
	  section.data(24).dtTransOffset = 49;
	
	  ;% rtDW.mfdffnmnea.TUbufferPtrs
	  section.data(25).logicalSrcIdx = 52;
	  section.data(25).dtTransOffset = 51;
	
	  ;% rtDW.e10ua2pcif.LoggedData
	  section.data(26).logicalSrcIdx = 53;
	  section.data(26).dtTransOffset = 53;
	
	  ;% rtDW.ovsyej354z.LoggedData
	  section.data(27).logicalSrcIdx = 54;
	  section.data(27).dtTransOffset = 55;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtDW.n2ufwbrgzx
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.ljyjgojejj
	  section.data(2).logicalSrcIdx = 56;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtDW.dwuhp2thuf
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.h4m3xflze4
	  section.data(2).logicalSrcIdx = 58;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 25;
      section.data(25)  = dumData; %prealloc
      
	  ;% rtDW.ob0eo32bes.PrevIndex
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.eioayfkhqd.Tail
	  section.data(2).logicalSrcIdx = 60;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.hpphhvjiqw.Tail
	  section.data(3).logicalSrcIdx = 61;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.pjaubi5g0r.Tail
	  section.data(4).logicalSrcIdx = 62;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.gtgggrpqsb.Tail
	  section.data(5).logicalSrcIdx = 63;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.gfgr3iktyl.Tail
	  section.data(6).logicalSrcIdx = 64;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.pttsc0t4lz.Tail
	  section.data(7).logicalSrcIdx = 65;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.eppzhodfly.Tail
	  section.data(8).logicalSrcIdx = 66;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDW.josactzshu.Tail
	  section.data(9).logicalSrcIdx = 67;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDW.c3xd1ms0us.Tail
	  section.data(10).logicalSrcIdx = 68;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtDW.odb4cbppzt.Tail
	  section.data(11).logicalSrcIdx = 69;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtDW.deeamvwgxv.Tail
	  section.data(12).logicalSrcIdx = 70;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtDW.ftsaljquvy.Tail
	  section.data(13).logicalSrcIdx = 71;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtDW.h0kavv2rvj.Tail
	  section.data(14).logicalSrcIdx = 72;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtDW.orr2azrxe5.Tail
	  section.data(15).logicalSrcIdx = 73;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtDW.mrknrsmtwp.Tail
	  section.data(16).logicalSrcIdx = 74;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtDW.hdikw2z4pb.Tail
	  section.data(17).logicalSrcIdx = 75;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtDW.oqom4bvhu5.Tail
	  section.data(18).logicalSrcIdx = 76;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtDW.fpoqultkeo.Tail
	  section.data(19).logicalSrcIdx = 77;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtDW.iexysxku45.Tail
	  section.data(20).logicalSrcIdx = 78;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtDW.ivfrpj5iet.Tail
	  section.data(21).logicalSrcIdx = 79;
	  section.data(21).dtTransOffset = 20;
	
	  ;% rtDW.hklidk4rmf.Tail
	  section.data(22).logicalSrcIdx = 80;
	  section.data(22).dtTransOffset = 21;
	
	  ;% rtDW.oib2ggiaac
	  section.data(23).logicalSrcIdx = 81;
	  section.data(23).dtTransOffset = 22;
	
	  ;% rtDW.cb1jfiyqqe
	  section.data(24).logicalSrcIdx = 82;
	  section.data(24).dtTransOffset = 23;
	
	  ;% rtDW.jhkfehrm4t
	  section.data(25).logicalSrcIdx = 83;
	  section.data(25).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% rtDW.og5vligtf5
	  section.data(1).logicalSrcIdx = 84;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.jsih34lehs
	  section.data(2).logicalSrcIdx = 85;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.juqugykvvp
	  section.data(3).logicalSrcIdx = 86;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.nwsijekr51
	  section.data(4).logicalSrcIdx = 87;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.lomcfztmre
	  section.data(5).logicalSrcIdx = 88;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% rtDW.brpeccm2su
	  section.data(1).logicalSrcIdx = 89;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.bybwcm2hrx
	  section.data(2).logicalSrcIdx = 90;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.ltwnscr23j
	  section.data(3).logicalSrcIdx = 91;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.f3anteups0
	  section.data(4).logicalSrcIdx = 92;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.p0mgrctrnl
	  section.data(5).logicalSrcIdx = 93;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.i5mfbygyll
	  section.data(6).logicalSrcIdx = 94;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.kwcxzpft0d
	  section.data(7).logicalSrcIdx = 95;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.ljvna4i1sk
	  section.data(8).logicalSrcIdx = 96;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDW.en3gkuykg0
	  section.data(9).logicalSrcIdx = 97;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDW.c22fq5hb2l
	  section.data(10).logicalSrcIdx = 98;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtDW.isfsg2jso1
	  section.data(11).logicalSrcIdx = 99;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtDW.ht5i5wmo5i
	  section.data(12).logicalSrcIdx = 100;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtDW.dmhkjfkzni
	  section.data(13).logicalSrcIdx = 101;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtDW.giqgg3q5tt
	  section.data(14).logicalSrcIdx = 102;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtDW.g31sjopxfu
	  section.data(15).logicalSrcIdx = 103;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.cvrfqtrsgv.bl2ajkrwzq
	  section.data(1).logicalSrcIdx = 104;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.b5dbwkwsrj.mnrpt53zog
	  section.data(1).logicalSrcIdx = 105;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.cc2aoo0nhc.b4uftfd3jt
	  section.data(1).logicalSrcIdx = 106;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.cfrh4agkgq.bl2ajkrwzq
	  section.data(1).logicalSrcIdx = 107;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.awkevlz2ww.mnrpt53zog
	  section.data(1).logicalSrcIdx = 108;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.dzgncmrria.b4uftfd3jt
	  section.data(1).logicalSrcIdx = 109;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.edzbs02xos1.bl2ajkrwzq
	  section.data(1).logicalSrcIdx = 110;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.fqkin25shtk.mnrpt53zog
	  section.data(1).logicalSrcIdx = 111;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.jgvwez5knrn.b4uftfd3jt
	  section.data(1).logicalSrcIdx = 112;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 2351720087;
  targMap.checksum1 = 4125363493;
  targMap.checksum2 = 143698455;
  targMap.checksum3 = 1469152365;

