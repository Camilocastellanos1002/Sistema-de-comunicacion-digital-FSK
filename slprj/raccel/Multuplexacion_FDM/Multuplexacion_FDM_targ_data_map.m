  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 13;
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
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
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
	
	  ;% rtP.frecport1
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtP.kv
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtP.kv2
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtP.CompareToConstant_const
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtP.GaussianNoiseGenerator_d
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtP.SampleandHold_ic
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtP.SampleandHold_ic_j2rdwmu3tc
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtP.SampleandHold_ic_iltoiaeoee
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtP.GaussianNoiseGenerator_m
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtP.GaussianNoiseGenerator_m_feibr5czzb
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtP.GaussianNoiseGenerator_s
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtP.GaussianNoiseGenerator_s_natqquq25k
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtP.Monostable1_ic
	  section.data(1).logicalSrcIdx = 21;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.Monostable_ic
	  section.data(2).logicalSrcIdx = 22;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.Monostable1_ic_biaz4juxj0
	  section.data(3).logicalSrcIdx = 23;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 116;
      section.data(116)  = dumData; %prealloc
      
	  ;% rtP._Y0
	  section.data(1).logicalSrcIdx = 24;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP._Y0_matapuynvo
	  section.data(2).logicalSrcIdx = 25;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP._Y0_ghe40wtwbh
	  section.data(3).logicalSrcIdx = 26;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtP.AnalogFilterDesign2_A
	  section.data(4).logicalSrcIdx = 27;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtP.AnalogFilterDesign2_B
	  section.data(5).logicalSrcIdx = 28;
	  section.data(5).dtTransOffset = 22;
	
	  ;% rtP.AnalogFilterDesign2_C
	  section.data(6).logicalSrcIdx = 29;
	  section.data(6).dtTransOffset = 23;
	
	  ;% rtP.AnalogFilterDesign2_InitialCondition
	  section.data(7).logicalSrcIdx = 30;
	  section.data(7).dtTransOffset = 24;
	
	  ;% rtP.Informacion2_Data0
	  section.data(8).logicalSrcIdx = 32;
	  section.data(8).dtTransOffset = 25;
	
	  ;% rtP.Integrator_IC
	  section.data(9).logicalSrcIdx = 33;
	  section.data(9).dtTransOffset = 207;
	
	  ;% rtP.ModuloIntegrator_IC
	  section.data(10).logicalSrcIdx = 34;
	  section.data(10).dtTransOffset = 208;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue
	  section.data(11).logicalSrcIdx = 35;
	  section.data(11).dtTransOffset = 209;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue
	  section.data(12).logicalSrcIdx = 36;
	  section.data(12).dtTransOffset = 210;
	
	  ;% rtP.Switch2_Threshold
	  section.data(13).logicalSrcIdx = 37;
	  section.data(13).dtTransOffset = 211;
	
	  ;% rtP.Integrator_IC_moexjyifg4
	  section.data(14).logicalSrcIdx = 38;
	  section.data(14).dtTransOffset = 212;
	
	  ;% rtP.informacion1_Data0
	  section.data(15).logicalSrcIdx = 40;
	  section.data(15).dtTransOffset = 213;
	
	  ;% rtP.AnalogFilterDesign_A
	  section.data(16).logicalSrcIdx = 41;
	  section.data(16).dtTransOffset = 395;
	
	  ;% rtP.AnalogFilterDesign_B
	  section.data(17).logicalSrcIdx = 42;
	  section.data(17).dtTransOffset = 414;
	
	  ;% rtP.AnalogFilterDesign_C
	  section.data(18).logicalSrcIdx = 43;
	  section.data(18).dtTransOffset = 415;
	
	  ;% rtP.AnalogFilterDesign_InitialCondition
	  section.data(19).logicalSrcIdx = 44;
	  section.data(19).dtTransOffset = 416;
	
	  ;% rtP.ModuloIntegrator_IC_esfyns1sy5
	  section.data(20).logicalSrcIdx = 45;
	  section.data(20).dtTransOffset = 417;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue_inwk4jds10
	  section.data(21).logicalSrcIdx = 46;
	  section.data(21).dtTransOffset = 418;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue_efd0rfjvev
	  section.data(22).logicalSrcIdx = 47;
	  section.data(22).dtTransOffset = 419;
	
	  ;% rtP.SineWave_Amp
	  section.data(23).logicalSrcIdx = 48;
	  section.data(23).dtTransOffset = 420;
	
	  ;% rtP.SineWave_Bias
	  section.data(24).logicalSrcIdx = 49;
	  section.data(24).dtTransOffset = 421;
	
	  ;% rtP.SineWave_Phase
	  section.data(25).logicalSrcIdx = 50;
	  section.data(25).dtTransOffset = 422;
	
	  ;% rtP.TransportDelay_Delay
	  section.data(26).logicalSrcIdx = 51;
	  section.data(26).dtTransOffset = 423;
	
	  ;% rtP.TransportDelay_InitOutput
	  section.data(27).logicalSrcIdx = 52;
	  section.data(27).dtTransOffset = 424;
	
	  ;% rtP.ModuloIntegrator_IC_i5n3se5kvp
	  section.data(28).logicalSrcIdx = 53;
	  section.data(28).dtTransOffset = 425;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue_dcyqcfnaqw
	  section.data(29).logicalSrcIdx = 54;
	  section.data(29).dtTransOffset = 426;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue_i1zhdl4bre
	  section.data(30).logicalSrcIdx = 55;
	  section.data(30).dtTransOffset = 427;
	
	  ;% rtP.TransportDelay_InitOutput_a54zvzwmak
	  section.data(31).logicalSrcIdx = 56;
	  section.data(31).dtTransOffset = 428;
	
	  ;% rtP.RandomNumber_Mean
	  section.data(32).logicalSrcIdx = 57;
	  section.data(32).dtTransOffset = 429;
	
	  ;% rtP.RandomNumber_StdDev
	  section.data(33).logicalSrcIdx = 58;
	  section.data(33).dtTransOffset = 430;
	
	  ;% rtP.Buffer_ic
	  section.data(34).logicalSrcIdx = 59;
	  section.data(34).dtTransOffset = 431;
	
	  ;% rtP.TransportDelay_Delay_dget2i1x1r
	  section.data(35).logicalSrcIdx = 60;
	  section.data(35).dtTransOffset = 432;
	
	  ;% rtP.TransportDelay_InitOutput_nb5s3gjuh0
	  section.data(36).logicalSrcIdx = 61;
	  section.data(36).dtTransOffset = 433;
	
	  ;% rtP.TransportDelay_InitOutput_bfobvi0kzf
	  section.data(37).logicalSrcIdx = 62;
	  section.data(37).dtTransOffset = 434;
	
	  ;% rtP.PulseGenerator_Amp
	  section.data(38).logicalSrcIdx = 63;
	  section.data(38).dtTransOffset = 435;
	
	  ;% rtP.PulseGenerator_Duty
	  section.data(39).logicalSrcIdx = 64;
	  section.data(39).dtTransOffset = 436;
	
	  ;% rtP.PulseGenerator_PhaseDelay
	  section.data(40).logicalSrcIdx = 65;
	  section.data(40).dtTransOffset = 437;
	
	  ;% rtP.TransportDelay_InitOutput_pz2dgrhemk
	  section.data(41).logicalSrcIdx = 66;
	  section.data(41).dtTransOffset = 438;
	
	  ;% rtP.TransportDelay1_InitOutput
	  section.data(42).logicalSrcIdx = 67;
	  section.data(42).dtTransOffset = 439;
	
	  ;% rtP.TransportDelay12_Delay
	  section.data(43).logicalSrcIdx = 68;
	  section.data(43).dtTransOffset = 440;
	
	  ;% rtP.TransportDelay12_InitOutput
	  section.data(44).logicalSrcIdx = 69;
	  section.data(44).dtTransOffset = 441;
	
	  ;% rtP.TransportDelay2_InitOutput
	  section.data(45).logicalSrcIdx = 70;
	  section.data(45).dtTransOffset = 442;
	
	  ;% rtP.TransportDelay1_InitOutput_km2up0labu
	  section.data(46).logicalSrcIdx = 71;
	  section.data(46).dtTransOffset = 443;
	
	  ;% rtP.TransportDelay4_InitOutput
	  section.data(47).logicalSrcIdx = 72;
	  section.data(47).dtTransOffset = 444;
	
	  ;% rtP.TransportDelay3_InitOutput
	  section.data(48).logicalSrcIdx = 73;
	  section.data(48).dtTransOffset = 445;
	
	  ;% rtP.TransportDelay6_InitOutput
	  section.data(49).logicalSrcIdx = 74;
	  section.data(49).dtTransOffset = 446;
	
	  ;% rtP.TransportDelay5_InitOutput
	  section.data(50).logicalSrcIdx = 75;
	  section.data(50).dtTransOffset = 447;
	
	  ;% rtP.TransportDelay8_InitOutput
	  section.data(51).logicalSrcIdx = 76;
	  section.data(51).dtTransOffset = 448;
	
	  ;% rtP.TransportDelay7_InitOutput
	  section.data(52).logicalSrcIdx = 77;
	  section.data(52).dtTransOffset = 449;
	
	  ;% rtP.TransportDelay9_InitOutput
	  section.data(53).logicalSrcIdx = 78;
	  section.data(53).dtTransOffset = 450;
	
	  ;% rtP.TransportDelay11_InitOutput
	  section.data(54).logicalSrcIdx = 79;
	  section.data(54).dtTransOffset = 451;
	
	  ;% rtP.TransportDelay10_InitOutput
	  section.data(55).logicalSrcIdx = 80;
	  section.data(55).dtTransOffset = 452;
	
	  ;% rtP.TransportDelay13_InitOutput
	  section.data(56).logicalSrcIdx = 81;
	  section.data(56).dtTransOffset = 453;
	
	  ;% rtP.Switch_Threshold
	  section.data(57).logicalSrcIdx = 82;
	  section.data(57).dtTransOffset = 454;
	
	  ;% rtP.Switch1_Threshold
	  section.data(58).logicalSrcIdx = 83;
	  section.data(58).dtTransOffset = 455;
	
	  ;% rtP.RandomNumber_Mean_pbcszkatmd
	  section.data(59).logicalSrcIdx = 84;
	  section.data(59).dtTransOffset = 456;
	
	  ;% rtP.RandomNumber_StdDev_iveng2gmn4
	  section.data(60).logicalSrcIdx = 85;
	  section.data(60).dtTransOffset = 457;
	
	  ;% rtP.MatrixGain_Gain
	  section.data(61).logicalSrcIdx = 86;
	  section.data(61).dtTransOffset = 458;
	
	  ;% rtP.Buffer_ic_b4vk0qmtfp
	  section.data(62).logicalSrcIdx = 87;
	  section.data(62).dtTransOffset = 459;
	
	  ;% rtP.TransportDelay1_InitOutput_cz0jjsby1m
	  section.data(63).logicalSrcIdx = 88;
	  section.data(63).dtTransOffset = 460;
	
	  ;% rtP.TransportDelay_InitOutput_nwut2o4lpm
	  section.data(64).logicalSrcIdx = 89;
	  section.data(64).dtTransOffset = 461;
	
	  ;% rtP.Filtro_A
	  section.data(65).logicalSrcIdx = 90;
	  section.data(65).dtTransOffset = 462;
	
	  ;% rtP.Filtro_B
	  section.data(66).logicalSrcIdx = 91;
	  section.data(66).dtTransOffset = 473;
	
	  ;% rtP.Filtro_C
	  section.data(67).logicalSrcIdx = 92;
	  section.data(67).dtTransOffset = 474;
	
	  ;% rtP.Filtro_InitialCondition
	  section.data(68).logicalSrcIdx = 93;
	  section.data(68).dtTransOffset = 475;
	
	  ;% rtP.Integrator_IC_ptowdeldtu
	  section.data(69).logicalSrcIdx = 94;
	  section.data(69).dtTransOffset = 476;
	
	  ;% rtP.Integrator1_IC
	  section.data(70).logicalSrcIdx = 95;
	  section.data(70).dtTransOffset = 477;
	
	  ;% rtP.ModuloIntegrator_IC_nahsh2vkhw
	  section.data(71).logicalSrcIdx = 96;
	  section.data(71).dtTransOffset = 478;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue_h455it4xzm
	  section.data(72).logicalSrcIdx = 97;
	  section.data(72).dtTransOffset = 479;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue_bslhwjjmfb
	  section.data(73).logicalSrcIdx = 98;
	  section.data(73).dtTransOffset = 480;
	
	  ;% rtP.Integrator_IC_nfolmlihr0
	  section.data(74).logicalSrcIdx = 99;
	  section.data(74).dtTransOffset = 481;
	
	  ;% rtP.ModuloIntegrator_IC_cw2uxsyp5l
	  section.data(75).logicalSrcIdx = 100;
	  section.data(75).dtTransOffset = 482;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue_hgarqjv2uf
	  section.data(76).logicalSrcIdx = 101;
	  section.data(76).dtTransOffset = 483;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue_mxtqs3uocj
	  section.data(77).logicalSrcIdx = 102;
	  section.data(77).dtTransOffset = 484;
	
	  ;% rtP.Integrator1_IC_dcpkt2betd
	  section.data(78).logicalSrcIdx = 103;
	  section.data(78).dtTransOffset = 485;
	
	  ;% rtP.Constant_Value
	  section.data(79).logicalSrcIdx = 104;
	  section.data(79).dtTransOffset = 486;
	
	  ;% rtP.Constant5_Value
	  section.data(80).logicalSrcIdx = 105;
	  section.data(80).dtTransOffset = 487;
	
	  ;% rtP.Constant6_Value
	  section.data(81).logicalSrcIdx = 106;
	  section.data(81).dtTransOffset = 488;
	
	  ;% rtP.Constant_Value_mvnfzatsby
	  section.data(82).logicalSrcIdx = 107;
	  section.data(82).dtTransOffset = 489;
	
	  ;% rtP.Constant1_Value
	  section.data(83).logicalSrcIdx = 108;
	  section.data(83).dtTransOffset = 490;
	
	  ;% rtP.posedge_Value
	  section.data(84).logicalSrcIdx = 109;
	  section.data(84).dtTransOffset = 491;
	
	  ;% rtP.negedge_Value
	  section.data(85).logicalSrcIdx = 110;
	  section.data(85).dtTransOffset = 493;
	
	  ;% rtP.eitheredge_Value
	  section.data(86).logicalSrcIdx = 111;
	  section.data(86).dtTransOffset = 495;
	
	  ;% rtP.Constant_Value_izjuzrtanz
	  section.data(87).logicalSrcIdx = 112;
	  section.data(87).dtTransOffset = 497;
	
	  ;% rtP.Constant1_Value_lpebpexhqd
	  section.data(88).logicalSrcIdx = 113;
	  section.data(88).dtTransOffset = 498;
	
	  ;% rtP.posedge_Value_iryngzqrd1
	  section.data(89).logicalSrcIdx = 114;
	  section.data(89).dtTransOffset = 499;
	
	  ;% rtP.negedge_Value_a22nqhbklc
	  section.data(90).logicalSrcIdx = 115;
	  section.data(90).dtTransOffset = 501;
	
	  ;% rtP.eitheredge_Value_a1qgi2i0lx
	  section.data(91).logicalSrcIdx = 116;
	  section.data(91).dtTransOffset = 503;
	
	  ;% rtP.Constant1_Value_obqa0ysasv
	  section.data(92).logicalSrcIdx = 117;
	  section.data(92).dtTransOffset = 505;
	
	  ;% rtP.Constant10_Value
	  section.data(93).logicalSrcIdx = 118;
	  section.data(93).dtTransOffset = 506;
	
	  ;% rtP.Constant11_Value
	  section.data(94).logicalSrcIdx = 119;
	  section.data(94).dtTransOffset = 507;
	
	  ;% rtP.Constant12_Value
	  section.data(95).logicalSrcIdx = 120;
	  section.data(95).dtTransOffset = 508;
	
	  ;% rtP.Constant13_Value
	  section.data(96).logicalSrcIdx = 121;
	  section.data(96).dtTransOffset = 509;
	
	  ;% rtP.Constant14_Value
	  section.data(97).logicalSrcIdx = 122;
	  section.data(97).dtTransOffset = 510;
	
	  ;% rtP.Constant15_Value
	  section.data(98).logicalSrcIdx = 123;
	  section.data(98).dtTransOffset = 511;
	
	  ;% rtP.Constant16_Value
	  section.data(99).logicalSrcIdx = 124;
	  section.data(99).dtTransOffset = 512;
	
	  ;% rtP.Constant17_Value
	  section.data(100).logicalSrcIdx = 125;
	  section.data(100).dtTransOffset = 513;
	
	  ;% rtP.Constant18_Value
	  section.data(101).logicalSrcIdx = 126;
	  section.data(101).dtTransOffset = 514;
	
	  ;% rtP.Constant19_Value
	  section.data(102).logicalSrcIdx = 127;
	  section.data(102).dtTransOffset = 515;
	
	  ;% rtP.Constant2_Value
	  section.data(103).logicalSrcIdx = 128;
	  section.data(103).dtTransOffset = 516;
	
	  ;% rtP.Constant20_Value
	  section.data(104).logicalSrcIdx = 129;
	  section.data(104).dtTransOffset = 517;
	
	  ;% rtP.Constant3_Value
	  section.data(105).logicalSrcIdx = 130;
	  section.data(105).dtTransOffset = 518;
	
	  ;% rtP.Constant4_Value
	  section.data(106).logicalSrcIdx = 131;
	  section.data(106).dtTransOffset = 519;
	
	  ;% rtP.Constant5_Value_pqkhorznoi
	  section.data(107).logicalSrcIdx = 132;
	  section.data(107).dtTransOffset = 520;
	
	  ;% rtP.Constant6_Value_oth1tjvwv0
	  section.data(108).logicalSrcIdx = 133;
	  section.data(108).dtTransOffset = 521;
	
	  ;% rtP.Constant7_Value
	  section.data(109).logicalSrcIdx = 134;
	  section.data(109).dtTransOffset = 522;
	
	  ;% rtP.Constant8_Value
	  section.data(110).logicalSrcIdx = 135;
	  section.data(110).dtTransOffset = 523;
	
	  ;% rtP.Constant9_Value
	  section.data(111).logicalSrcIdx = 136;
	  section.data(111).dtTransOffset = 524;
	
	  ;% rtP.Constant_Value_pmuy4epl2c
	  section.data(112).logicalSrcIdx = 137;
	  section.data(112).dtTransOffset = 525;
	
	  ;% rtP.Constant1_Value_bsax1tsxxz
	  section.data(113).logicalSrcIdx = 138;
	  section.data(113).dtTransOffset = 526;
	
	  ;% rtP.posedge_Value_fsgb0grkvo
	  section.data(114).logicalSrcIdx = 139;
	  section.data(114).dtTransOffset = 527;
	
	  ;% rtP.negedge_Value_ackdjcny40
	  section.data(115).logicalSrcIdx = 140;
	  section.data(115).dtTransOffset = 529;
	
	  ;% rtP.eitheredge_Value_lzvwtrli1x
	  section.data(116).logicalSrcIdx = 141;
	  section.data(116).dtTransOffset = 531;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% rtP._Y0_ld4ghr3opr
	  section.data(1).logicalSrcIdx = 142;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.Memory_InitialCondition
	  section.data(2).logicalSrcIdx = 143;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.Memory_InitialCondition_jlkxne1qro
	  section.data(3).logicalSrcIdx = 144;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtP.Memory_InitialCondition_cdrhhgyi4a
	  section.data(4).logicalSrcIdx = 145;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.abmuy5rnsq.OUT_Y0
	  section.data(1).logicalSrcIdx = 146;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.mpycb0evfp.OUT_Y0
	  section.data(1).logicalSrcIdx = 147;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.jiixgvrfhd.Out1_Y0
	  section.data(1).logicalSrcIdx = 148;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.gggqmave4q.OUT_Y0
	  section.data(1).logicalSrcIdx = 149;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.fkhi333c1w.OUT_Y0
	  section.data(1).logicalSrcIdx = 150;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.dyorcglstw.Out1_Y0
	  section.data(1).logicalSrcIdx = 151;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.d5zlt11l1pl.OUT_Y0
	  section.data(1).logicalSrcIdx = 152;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.dnioykk3w1k.OUT_Y0
	  section.data(1).logicalSrcIdx = 153;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.mivhx1fvuuy.Out1_Y0
	  section.data(1).logicalSrcIdx = 154;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(13) = section;
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
      section.nData     = 110;
      section.data(110)  = dumData; %prealloc
      
	  ;% rtB.gzkvmusrdv
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.l2slq2pxao
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.hqvlr0c1t3
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.l3viz5m5kx
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.ifswdaywbt
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.ph3uie01yv
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtB.cwrlg5uwpe
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtB.m1xi1b0n5m
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtB.omyffgmxzc
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtB.otfd1hdnf4
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtB.dwygygnfyu
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtB.kvdiwfhjmc
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtB.oddjfmdyew
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtB.ftbsaajysf
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtB.i3olz0n0gi
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtB.d4sffuf0wj
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtB.ckmrjxysf3
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtB.jaf1or2u2g
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtB.lisu5vhdeu
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtB.czpmrjwdbw
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtB.eqpfzakwij
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% rtB.cuyzwij0cy
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% rtB.dc0ixgrh4v
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% rtB.bonunno3da
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% rtB.p5sg0ao2sd
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24;
	
	  ;% rtB.hnghqt15hm
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 25;
	
	  ;% rtB.pbihxnhzkv
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 26;
	
	  ;% rtB.ehk41k1jvu
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 27;
	
	  ;% rtB.jdmdbzovgb
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 28;
	
	  ;% rtB.dl2z1kzk4x
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 29;
	
	  ;% rtB.drqnxkzet4
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 30;
	
	  ;% rtB.hduwbah451
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 31;
	
	  ;% rtB.osh4e3wkbx
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 32;
	
	  ;% rtB.jkosinqwcz
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 33;
	
	  ;% rtB.mhvwbma2wc
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 34;
	
	  ;% rtB.hoboqemidv
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 35;
	
	  ;% rtB.pw3nmstdx1
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 36;
	
	  ;% rtB.aekkmo2dza
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 37;
	
	  ;% rtB.leuwvo5bd0
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 38;
	
	  ;% rtB.kzkfn1s2js
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 39;
	
	  ;% rtB.hdfbddrmbc
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 40;
	
	  ;% rtB.fetl3awrl2
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 41;
	
	  ;% rtB.hd11xynwm2
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 42;
	
	  ;% rtB.nuzxbadudr
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 43;
	
	  ;% rtB.dfyucx0pjs
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 44;
	
	  ;% rtB.owlyu5iz4l
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 45;
	
	  ;% rtB.dwfqmte2n3
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 46;
	
	  ;% rtB.loxkzong0h
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 47;
	
	  ;% rtB.gx1uxu4kds
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 48;
	
	  ;% rtB.co4tajx3jh
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 49;
	
	  ;% rtB.hd0ccnz5kj
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 50;
	
	  ;% rtB.kmsebnmjbu
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 51;
	
	  ;% rtB.ay4kbspa2f
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 52;
	
	  ;% rtB.dwuvmlamlj
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 53;
	
	  ;% rtB.iup0qas13y
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 54;
	
	  ;% rtB.pbk3xyooxn
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 55;
	
	  ;% rtB.jj2crb3wdo
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 56;
	
	  ;% rtB.flwwemz4a3
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 57;
	
	  ;% rtB.pskl4q2wwt
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 58;
	
	  ;% rtB.exdbaattar
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 59;
	
	  ;% rtB.izg2hxr1hm
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 60;
	
	  ;% rtB.f1l5jsixgw
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 61;
	
	  ;% rtB.fosqwahuok
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 62;
	
	  ;% rtB.orkfi0mp2e
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 63;
	
	  ;% rtB.izpbcjjrig
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 64;
	
	  ;% rtB.gwu42iz5ys
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 65;
	
	  ;% rtB.pgvargzqvr
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 66;
	
	  ;% rtB.ityop505e4
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 67;
	
	  ;% rtB.hrs0mectw5
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 68;
	
	  ;% rtB.fgrkiz4z0n
	  section.data(70).logicalSrcIdx = 69;
	  section.data(70).dtTransOffset = 69;
	
	  ;% rtB.cswpv2o1kk
	  section.data(71).logicalSrcIdx = 70;
	  section.data(71).dtTransOffset = 70;
	
	  ;% rtB.de2xsxb24p
	  section.data(72).logicalSrcIdx = 71;
	  section.data(72).dtTransOffset = 71;
	
	  ;% rtB.hx1rf2yrz2
	  section.data(73).logicalSrcIdx = 72;
	  section.data(73).dtTransOffset = 72;
	
	  ;% rtB.cviwvtwqhc
	  section.data(74).logicalSrcIdx = 73;
	  section.data(74).dtTransOffset = 73;
	
	  ;% rtB.l5nwaj4e3i
	  section.data(75).logicalSrcIdx = 74;
	  section.data(75).dtTransOffset = 74;
	
	  ;% rtB.looejrxoki
	  section.data(76).logicalSrcIdx = 75;
	  section.data(76).dtTransOffset = 75;
	
	  ;% rtB.awasz3p2hm
	  section.data(77).logicalSrcIdx = 76;
	  section.data(77).dtTransOffset = 76;
	
	  ;% rtB.axof5reva4
	  section.data(78).logicalSrcIdx = 77;
	  section.data(78).dtTransOffset = 77;
	
	  ;% rtB.m3xclbw4n1
	  section.data(79).logicalSrcIdx = 78;
	  section.data(79).dtTransOffset = 78;
	
	  ;% rtB.jka1elz4sz
	  section.data(80).logicalSrcIdx = 79;
	  section.data(80).dtTransOffset = 79;
	
	  ;% rtB.ikxyn0xytc
	  section.data(81).logicalSrcIdx = 80;
	  section.data(81).dtTransOffset = 80;
	
	  ;% rtB.h32dvvdjsr
	  section.data(82).logicalSrcIdx = 81;
	  section.data(82).dtTransOffset = 81;
	
	  ;% rtB.cfvwyihfgi
	  section.data(83).logicalSrcIdx = 82;
	  section.data(83).dtTransOffset = 82;
	
	  ;% rtB.bbdybg5bbo
	  section.data(84).logicalSrcIdx = 83;
	  section.data(84).dtTransOffset = 83;
	
	  ;% rtB.nb4mlfbe25
	  section.data(85).logicalSrcIdx = 84;
	  section.data(85).dtTransOffset = 84;
	
	  ;% rtB.nrzgv2asbm
	  section.data(86).logicalSrcIdx = 85;
	  section.data(86).dtTransOffset = 85;
	
	  ;% rtB.kb3qoydtul
	  section.data(87).logicalSrcIdx = 86;
	  section.data(87).dtTransOffset = 86;
	
	  ;% rtB.emzymu3s4t
	  section.data(88).logicalSrcIdx = 87;
	  section.data(88).dtTransOffset = 87;
	
	  ;% rtB.dhvezilxca
	  section.data(89).logicalSrcIdx = 88;
	  section.data(89).dtTransOffset = 88;
	
	  ;% rtB.fy1jpymzvl
	  section.data(90).logicalSrcIdx = 89;
	  section.data(90).dtTransOffset = 89;
	
	  ;% rtB.gwfkgabvtm
	  section.data(91).logicalSrcIdx = 90;
	  section.data(91).dtTransOffset = 90;
	
	  ;% rtB.ijhgy4lexb
	  section.data(92).logicalSrcIdx = 91;
	  section.data(92).dtTransOffset = 91;
	
	  ;% rtB.csu05jokxd
	  section.data(93).logicalSrcIdx = 92;
	  section.data(93).dtTransOffset = 92;
	
	  ;% rtB.eg0uqlyrw2
	  section.data(94).logicalSrcIdx = 93;
	  section.data(94).dtTransOffset = 93;
	
	  ;% rtB.dhxzfrd1ut
	  section.data(95).logicalSrcIdx = 94;
	  section.data(95).dtTransOffset = 94;
	
	  ;% rtB.ihg3emy0vs
	  section.data(96).logicalSrcIdx = 95;
	  section.data(96).dtTransOffset = 95;
	
	  ;% rtB.l1ylzo5bhw
	  section.data(97).logicalSrcIdx = 96;
	  section.data(97).dtTransOffset = 96;
	
	  ;% rtB.cj3eokpnbs
	  section.data(98).logicalSrcIdx = 97;
	  section.data(98).dtTransOffset = 97;
	
	  ;% rtB.i14aygkcoq
	  section.data(99).logicalSrcIdx = 98;
	  section.data(99).dtTransOffset = 98;
	
	  ;% rtB.a4wt4ee5p1
	  section.data(100).logicalSrcIdx = 99;
	  section.data(100).dtTransOffset = 99;
	
	  ;% rtB.fz1wrzhdaa
	  section.data(101).logicalSrcIdx = 100;
	  section.data(101).dtTransOffset = 100;
	
	  ;% rtB.kp3wrgz5sh
	  section.data(102).logicalSrcIdx = 101;
	  section.data(102).dtTransOffset = 101;
	
	  ;% rtB.fuwgkaabcp
	  section.data(103).logicalSrcIdx = 102;
	  section.data(103).dtTransOffset = 102;
	
	  ;% rtB.d2vdhfxwnv
	  section.data(104).logicalSrcIdx = 103;
	  section.data(104).dtTransOffset = 103;
	
	  ;% rtB.fto4cglprz
	  section.data(105).logicalSrcIdx = 104;
	  section.data(105).dtTransOffset = 104;
	
	  ;% rtB.nj0vsa0aao
	  section.data(106).logicalSrcIdx = 105;
	  section.data(106).dtTransOffset = 106;
	
	  ;% rtB.i4cllywuc1
	  section.data(107).logicalSrcIdx = 106;
	  section.data(107).dtTransOffset = 108;
	
	  ;% rtB.dduxw540hu
	  section.data(108).logicalSrcIdx = 107;
	  section.data(108).dtTransOffset = 110;
	
	  ;% rtB.munnuokh3b
	  section.data(109).logicalSrcIdx = 108;
	  section.data(109).dtTransOffset = 111;
	
	  ;% rtB.lufwcivalw
	  section.data(110).logicalSrcIdx = 109;
	  section.data(110).dtTransOffset = 112;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% rtB.o2g3bsob40
	  section.data(1).logicalSrcIdx = 110;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.f0xjphnymz
	  section.data(2).logicalSrcIdx = 111;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.nekkkm0p0a
	  section.data(3).logicalSrcIdx = 112;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.eaief2hsbj
	  section.data(4).logicalSrcIdx = 113;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.dumyggkchi
	  section.data(5).logicalSrcIdx = 114;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.hgcnrsrftd
	  section.data(6).logicalSrcIdx = 115;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtB.ghaifzgd35
	  section.data(7).logicalSrcIdx = 116;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtB.bnhnntm3f4
	  section.data(8).logicalSrcIdx = 117;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtB.ajbeq5hpnj
	  section.data(9).logicalSrcIdx = 118;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtB.eizf1ealtw
	  section.data(10).logicalSrcIdx = 119;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtB.e1nhqxjvjn
	  section.data(11).logicalSrcIdx = 120;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.abmuy5rnsq.ltgb5gkcbo
	  section.data(1).logicalSrcIdx = 121;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.mpycb0evfp.hmpzhh3n3o
	  section.data(1).logicalSrcIdx = 122;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.jiixgvrfhd.hml4vbrazh
	  section.data(1).logicalSrcIdx = 123;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.gggqmave4q.ltgb5gkcbo
	  section.data(1).logicalSrcIdx = 124;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.fkhi333c1w.hmpzhh3n3o
	  section.data(1).logicalSrcIdx = 125;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.dyorcglstw.hml4vbrazh
	  section.data(1).logicalSrcIdx = 126;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.d5zlt11l1pl.ltgb5gkcbo
	  section.data(1).logicalSrcIdx = 127;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.dnioykk3w1k.hmpzhh3n3o
	  section.data(1).logicalSrcIdx = 128;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.mivhx1fvuuy.hml4vbrazh
	  section.data(1).logicalSrcIdx = 129;
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
      
	  ;% rtDW.ou0ychata3
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.dbk2xqyp1n
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.bwkxnxzhy1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.kikmlfmksm
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.livmyfqsgc
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.nfditlbohk
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.kklmtkqxdm
	  section.data(1).logicalSrcIdx = 6;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% rtDW.khrc1lwffi.modelTStart
	  section.data(1).logicalSrcIdx = 7;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.cssnev1fy3.modelTStart
	  section.data(2).logicalSrcIdx = 8;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.oa42qrjv3l.modelTStart
	  section.data(3).logicalSrcIdx = 9;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.ggwyhatdea.modelTStart
	  section.data(4).logicalSrcIdx = 10;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.cuje003nlw.modelTStart
	  section.data(5).logicalSrcIdx = 11;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.puzaleogwu.modelTStart
	  section.data(6).logicalSrcIdx = 12;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.n1qb5g4n41.modelTStart
	  section.data(7).logicalSrcIdx = 13;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.bfwzmi2uyh.modelTStart
	  section.data(8).logicalSrcIdx = 14;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDW.ebk2ryovno.modelTStart
	  section.data(9).logicalSrcIdx = 15;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDW.ptkzu50g4c.modelTStart
	  section.data(10).logicalSrcIdx = 16;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtDW.kya31t5ner.modelTStart
	  section.data(11).logicalSrcIdx = 17;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtDW.kfvog22y10.modelTStart
	  section.data(12).logicalSrcIdx = 18;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtDW.lq15frqj0j.modelTStart
	  section.data(13).logicalSrcIdx = 19;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtDW.iyu2cdjdjo.modelTStart
	  section.data(14).logicalSrcIdx = 20;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtDW.bleq0imc3q.modelTStart
	  section.data(15).logicalSrcIdx = 21;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtDW.jxtss4hooy.modelTStart
	  section.data(16).logicalSrcIdx = 22;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtDW.auetjjv433.modelTStart
	  section.data(17).logicalSrcIdx = 23;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtDW.hqpl32qj3u.modelTStart
	  section.data(18).logicalSrcIdx = 24;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtDW.pvitriryga.modelTStart
	  section.data(19).logicalSrcIdx = 25;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtDW.fm4mcliygj.modelTStart
	  section.data(20).logicalSrcIdx = 26;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtDW.phs2xz5445.modelTStart
	  section.data(21).logicalSrcIdx = 27;
	  section.data(21).dtTransOffset = 20;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 30;
      section.data(30)  = dumData; %prealloc
      
	  ;% rtDW.d0yoqq0s2u.TimePtr
	  section.data(1).logicalSrcIdx = 28;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.fcafpomhwg.LoggedData
	  section.data(2).logicalSrcIdx = 29;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.eckmfvfwps.LoggedData
	  section.data(3).logicalSrcIdx = 30;
	  section.data(3).dtTransOffset = 3;
	
	  ;% rtDW.gtget4fvsy.TimePtr
	  section.data(4).logicalSrcIdx = 31;
	  section.data(4).dtTransOffset = 5;
	
	  ;% rtDW.j0ojopv3o4.TUbufferPtrs
	  section.data(5).logicalSrcIdx = 32;
	  section.data(5).dtTransOffset = 6;
	
	  ;% rtDW.odiqda1u1t.TUbufferPtrs
	  section.data(6).logicalSrcIdx = 33;
	  section.data(6).dtTransOffset = 8;
	
	  ;% rtDW.mx1qnjpwkr.TUbufferPtrs
	  section.data(7).logicalSrcIdx = 34;
	  section.data(7).dtTransOffset = 10;
	
	  ;% rtDW.c1abig5l5b.TUbufferPtrs
	  section.data(8).logicalSrcIdx = 35;
	  section.data(8).dtTransOffset = 12;
	
	  ;% rtDW.l3olmqutvm.TUbufferPtrs
	  section.data(9).logicalSrcIdx = 36;
	  section.data(9).dtTransOffset = 14;
	
	  ;% rtDW.laigziygdt.TUbufferPtrs
	  section.data(10).logicalSrcIdx = 37;
	  section.data(10).dtTransOffset = 16;
	
	  ;% rtDW.dkdfqlezt3.LoggedData
	  section.data(11).logicalSrcIdx = 38;
	  section.data(11).dtTransOffset = 18;
	
	  ;% rtDW.duyhxp3i2o.TUbufferPtrs
	  section.data(12).logicalSrcIdx = 39;
	  section.data(12).dtTransOffset = 20;
	
	  ;% rtDW.pfzlxqtttd.TUbufferPtrs
	  section.data(13).logicalSrcIdx = 40;
	  section.data(13).dtTransOffset = 22;
	
	  ;% rtDW.kpyzd0zppl.TUbufferPtrs
	  section.data(14).logicalSrcIdx = 41;
	  section.data(14).dtTransOffset = 24;
	
	  ;% rtDW.anw4lh3mkt.TUbufferPtrs
	  section.data(15).logicalSrcIdx = 42;
	  section.data(15).dtTransOffset = 26;
	
	  ;% rtDW.hth3y5boa4.TUbufferPtrs
	  section.data(16).logicalSrcIdx = 43;
	  section.data(16).dtTransOffset = 28;
	
	  ;% rtDW.jkfvz1vsm1.TUbufferPtrs
	  section.data(17).logicalSrcIdx = 44;
	  section.data(17).dtTransOffset = 30;
	
	  ;% rtDW.axitmt5w4i.TUbufferPtrs
	  section.data(18).logicalSrcIdx = 45;
	  section.data(18).dtTransOffset = 32;
	
	  ;% rtDW.bz4cstgndq.TUbufferPtrs
	  section.data(19).logicalSrcIdx = 46;
	  section.data(19).dtTransOffset = 34;
	
	  ;% rtDW.ifxwkbjtsf.TUbufferPtrs
	  section.data(20).logicalSrcIdx = 47;
	  section.data(20).dtTransOffset = 36;
	
	  ;% rtDW.oydq1getqe.TUbufferPtrs
	  section.data(21).logicalSrcIdx = 48;
	  section.data(21).dtTransOffset = 38;
	
	  ;% rtDW.nzhehebsh0.TUbufferPtrs
	  section.data(22).logicalSrcIdx = 49;
	  section.data(22).dtTransOffset = 40;
	
	  ;% rtDW.erisf50gfz.TUbufferPtrs
	  section.data(23).logicalSrcIdx = 50;
	  section.data(23).dtTransOffset = 42;
	
	  ;% rtDW.jszhk4b0c2.TUbufferPtrs
	  section.data(24).logicalSrcIdx = 51;
	  section.data(24).dtTransOffset = 44;
	
	  ;% rtDW.emliqyd1hi.TUbufferPtrs
	  section.data(25).logicalSrcIdx = 52;
	  section.data(25).dtTransOffset = 46;
	
	  ;% rtDW.j0z4zsdtwg.TUbufferPtrs
	  section.data(26).logicalSrcIdx = 53;
	  section.data(26).dtTransOffset = 48;
	
	  ;% rtDW.fgn1xd2f0g.LoggedData
	  section.data(27).logicalSrcIdx = 54;
	  section.data(27).dtTransOffset = 50;
	
	  ;% rtDW.n05q2zm0z1.LoggedData
	  section.data(28).logicalSrcIdx = 55;
	  section.data(28).dtTransOffset = 54;
	
	  ;% rtDW.g4w5bwgqfc.LoggedData
	  section.data(29).logicalSrcIdx = 56;
	  section.data(29).dtTransOffset = 58;
	
	  ;% rtDW.lp4l4cdghx.LoggedData
	  section.data(30).logicalSrcIdx = 57;
	  section.data(30).dtTransOffset = 60;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtDW.nnzogj4mrn
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.dvmb0i40bs
	  section.data(2).logicalSrcIdx = 59;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtDW.imgdcg24fm
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.kzibzv5iwi
	  section.data(2).logicalSrcIdx = 61;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 26;
      section.data(26)  = dumData; %prealloc
      
	  ;% rtDW.fxbkkikmgg.PrevIndex
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.j4hthgivby.PrevIndex
	  section.data(2).logicalSrcIdx = 63;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.actgbahxga.Tail
	  section.data(3).logicalSrcIdx = 64;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.cc05czrsze.Tail
	  section.data(4).logicalSrcIdx = 65;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.ikxgblv1zv.Tail
	  section.data(5).logicalSrcIdx = 66;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.c0ewitmagq.Tail
	  section.data(6).logicalSrcIdx = 67;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.mw4jmqmb5m.Tail
	  section.data(7).logicalSrcIdx = 68;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.mbpoqz0vfq.Tail
	  section.data(8).logicalSrcIdx = 69;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDW.jqyvcdfdil.Tail
	  section.data(9).logicalSrcIdx = 70;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDW.b5jqmouq00.Tail
	  section.data(10).logicalSrcIdx = 71;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtDW.dsos1nl3ug.Tail
	  section.data(11).logicalSrcIdx = 72;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtDW.miosm0kvi1.Tail
	  section.data(12).logicalSrcIdx = 73;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtDW.daastispqd.Tail
	  section.data(13).logicalSrcIdx = 74;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtDW.ga03tvlrh0.Tail
	  section.data(14).logicalSrcIdx = 75;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtDW.d2cdydaqvh.Tail
	  section.data(15).logicalSrcIdx = 76;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtDW.lo3fy120pk.Tail
	  section.data(16).logicalSrcIdx = 77;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtDW.i5j0s3drdy.Tail
	  section.data(17).logicalSrcIdx = 78;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtDW.naehoe5c24.Tail
	  section.data(18).logicalSrcIdx = 79;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtDW.atsr3zriuy.Tail
	  section.data(19).logicalSrcIdx = 80;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtDW.ogdeiw34cz.Tail
	  section.data(20).logicalSrcIdx = 81;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtDW.nan1e3l5p0.Tail
	  section.data(21).logicalSrcIdx = 82;
	  section.data(21).dtTransOffset = 20;
	
	  ;% rtDW.oivjundpbe.Tail
	  section.data(22).logicalSrcIdx = 83;
	  section.data(22).dtTransOffset = 21;
	
	  ;% rtDW.os1vqq3jgt.Tail
	  section.data(23).logicalSrcIdx = 84;
	  section.data(23).dtTransOffset = 22;
	
	  ;% rtDW.nfgd4hmkks
	  section.data(24).logicalSrcIdx = 85;
	  section.data(24).dtTransOffset = 23;
	
	  ;% rtDW.hhfaeeexeg
	  section.data(25).logicalSrcIdx = 86;
	  section.data(25).dtTransOffset = 24;
	
	  ;% rtDW.oxgn4zxxpe
	  section.data(26).logicalSrcIdx = 87;
	  section.data(26).dtTransOffset = 25;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% rtDW.lekdfle5yl
	  section.data(1).logicalSrcIdx = 88;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.cjvs3g4hfh
	  section.data(2).logicalSrcIdx = 89;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.moelhnb1d2
	  section.data(3).logicalSrcIdx = 90;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.loneq0nrmu
	  section.data(4).logicalSrcIdx = 91;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.hbnvwgns2u
	  section.data(5).logicalSrcIdx = 92;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% rtDW.ita0atad5a
	  section.data(1).logicalSrcIdx = 93;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.oz50sdopcp
	  section.data(2).logicalSrcIdx = 94;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.pejw2pyiiz
	  section.data(3).logicalSrcIdx = 95;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.j2llbcud4w
	  section.data(4).logicalSrcIdx = 96;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.by0zcdyxc4
	  section.data(5).logicalSrcIdx = 97;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.alduujhq0a
	  section.data(6).logicalSrcIdx = 98;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.kmeshewsao
	  section.data(7).logicalSrcIdx = 99;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.cbjfpdjiyu
	  section.data(8).logicalSrcIdx = 100;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDW.bctphvd2sv
	  section.data(9).logicalSrcIdx = 101;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDW.alglspiynp
	  section.data(10).logicalSrcIdx = 102;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtDW.koquxjpxpa
	  section.data(11).logicalSrcIdx = 103;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtDW.bqhe24xuds
	  section.data(12).logicalSrcIdx = 104;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtDW.ox1bxr2hww
	  section.data(13).logicalSrcIdx = 105;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtDW.kltylslzkb
	  section.data(14).logicalSrcIdx = 106;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtDW.luhachiin3
	  section.data(15).logicalSrcIdx = 107;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.abmuy5rnsq.faxymqm3qy
	  section.data(1).logicalSrcIdx = 108;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.mpycb0evfp.k2unbokluf
	  section.data(1).logicalSrcIdx = 109;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.jiixgvrfhd.fmzbbk3ukv
	  section.data(1).logicalSrcIdx = 110;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.gggqmave4q.faxymqm3qy
	  section.data(1).logicalSrcIdx = 111;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.fkhi333c1w.k2unbokluf
	  section.data(1).logicalSrcIdx = 112;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.dyorcglstw.fmzbbk3ukv
	  section.data(1).logicalSrcIdx = 113;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.d5zlt11l1pl.faxymqm3qy
	  section.data(1).logicalSrcIdx = 114;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.dnioykk3w1k.k2unbokluf
	  section.data(1).logicalSrcIdx = 115;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.mivhx1fvuuy.fmzbbk3ukv
	  section.data(1).logicalSrcIdx = 116;
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


  targMap.checksum0 = 3625068466;
  targMap.checksum1 = 1078413989;
  targMap.checksum2 = 1015600188;
  targMap.checksum3 = 1100843694;

