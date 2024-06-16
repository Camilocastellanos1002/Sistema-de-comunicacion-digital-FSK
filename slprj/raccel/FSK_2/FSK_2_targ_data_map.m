  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
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
      section.nData     = 36;
      section.data(36)  = dumData; %prealloc
      
	  ;% rtP.Atenuacion_canal
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.Frec2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.Frec4
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtP.Rb
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtP.Retraso_canal
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtP.frec
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtP.GaussianNoiseGenerator_d
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtP.GaussianNoiseGenerator_m
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtP.GaussianNoiseGenerator_s
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtP.Informacion_Data0
	  section.data(10).logicalSrcIdx = 10;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtP.AnalogFilterDesign_A
	  section.data(11).logicalSrcIdx = 11;
	  section.data(11).dtTransOffset = 191;
	
	  ;% rtP.AnalogFilterDesign_B
	  section.data(12).logicalSrcIdx = 12;
	  section.data(12).dtTransOffset = 210;
	
	  ;% rtP.AnalogFilterDesign_C
	  section.data(13).logicalSrcIdx = 13;
	  section.data(13).dtTransOffset = 211;
	
	  ;% rtP.AnalogFilterDesign_InitialCondition
	  section.data(14).logicalSrcIdx = 14;
	  section.data(14).dtTransOffset = 212;
	
	  ;% rtP.AnalogFilterDesign2_A
	  section.data(15).logicalSrcIdx = 15;
	  section.data(15).dtTransOffset = 213;
	
	  ;% rtP.AnalogFilterDesign2_B
	  section.data(16).logicalSrcIdx = 16;
	  section.data(16).dtTransOffset = 232;
	
	  ;% rtP.AnalogFilterDesign2_C
	  section.data(17).logicalSrcIdx = 17;
	  section.data(17).dtTransOffset = 233;
	
	  ;% rtP.AnalogFilterDesign2_InitialCondition
	  section.data(18).logicalSrcIdx = 18;
	  section.data(18).dtTransOffset = 234;
	
	  ;% rtP.Informacion1_Data0
	  section.data(19).logicalSrcIdx = 20;
	  section.data(19).dtTransOffset = 235;
	
	  ;% rtP.ModuloIntegrator_IC
	  section.data(20).logicalSrcIdx = 21;
	  section.data(20).dtTransOffset = 417;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue
	  section.data(21).logicalSrcIdx = 22;
	  section.data(21).dtTransOffset = 418;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue
	  section.data(22).logicalSrcIdx = 23;
	  section.data(22).dtTransOffset = 419;
	
	  ;% rtP.SineWave_Amp
	  section.data(23).logicalSrcIdx = 24;
	  section.data(23).dtTransOffset = 420;
	
	  ;% rtP.SineWave_Bias
	  section.data(24).logicalSrcIdx = 25;
	  section.data(24).dtTransOffset = 421;
	
	  ;% rtP.SineWave_Phase
	  section.data(25).logicalSrcIdx = 26;
	  section.data(25).dtTransOffset = 422;
	
	  ;% rtP.ModuloIntegrator_IC_p52dz1dzx0
	  section.data(26).logicalSrcIdx = 27;
	  section.data(26).dtTransOffset = 423;
	
	  ;% rtP.ModuloIntegrator_WrappedStateUpperValue_kbmmwvx1uc
	  section.data(27).logicalSrcIdx = 28;
	  section.data(27).dtTransOffset = 424;
	
	  ;% rtP.ModuloIntegrator_WrappedStateLowerValue_mg14ul40s3
	  section.data(28).logicalSrcIdx = 29;
	  section.data(28).dtTransOffset = 425;
	
	  ;% rtP.TransportDelay_Delay
	  section.data(29).logicalSrcIdx = 30;
	  section.data(29).dtTransOffset = 426;
	
	  ;% rtP.TransportDelay_InitOutput
	  section.data(30).logicalSrcIdx = 31;
	  section.data(30).dtTransOffset = 427;
	
	  ;% rtP.TransportDelay_Delay_mpjovd0fow
	  section.data(31).logicalSrcIdx = 32;
	  section.data(31).dtTransOffset = 428;
	
	  ;% rtP.TransportDelay_InitOutput_erb5xkljw0
	  section.data(32).logicalSrcIdx = 33;
	  section.data(32).dtTransOffset = 429;
	
	  ;% rtP.TransportDelay_InitOutput_npzkuu2dfa
	  section.data(33).logicalSrcIdx = 34;
	  section.data(33).dtTransOffset = 430;
	
	  ;% rtP.RandomNumber_Mean
	  section.data(34).logicalSrcIdx = 35;
	  section.data(34).dtTransOffset = 431;
	
	  ;% rtP.RandomNumber_StdDev
	  section.data(35).logicalSrcIdx = 36;
	  section.data(35).dtTransOffset = 432;
	
	  ;% rtP.Buffer_ic
	  section.data(36).logicalSrcIdx = 37;
	  section.data(36).dtTransOffset = 433;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
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
    nTotSects     = 1;
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
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% rtB.bdmiwmnwdi
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.a2ej4vwwfz
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.cydck3mxyr
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.ixhdtyqkuo
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.dzdmp2qvuc
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.a1nwn30zom
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtB.pxelcov220
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtB.br52h0oi5h
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtB.clkvycwj4m
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtB.o0un153nbh
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
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
    nTotSects     = 4;
    sectIdxOffset = 1;
    
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
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% rtDW.osax4czyvz
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.ahatirdp3v.modelTStart
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.nkby1sxpuw.modelTStart
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.fhwaru4dxv.modelTStart
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% rtDW.i00x1wwgsf.TimePtr
	  section.data(1).logicalSrcIdx = 4;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.bmmqaeqn53.LoggedData
	  section.data(2).logicalSrcIdx = 5;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.jf1myj4gvp.TimePtr
	  section.data(3).logicalSrcIdx = 6;
	  section.data(3).dtTransOffset = 3;
	
	  ;% rtDW.ozc2tf4c2y.LoggedData
	  section.data(4).logicalSrcIdx = 7;
	  section.data(4).dtTransOffset = 4;
	
	  ;% rtDW.aw2n3f4po1.TUbufferPtrs
	  section.data(5).logicalSrcIdx = 8;
	  section.data(5).dtTransOffset = 6;
	
	  ;% rtDW.bmxd34jmp4.TUbufferPtrs
	  section.data(6).logicalSrcIdx = 9;
	  section.data(6).dtTransOffset = 8;
	
	  ;% rtDW.haguqrracw.TUbufferPtrs
	  section.data(7).logicalSrcIdx = 10;
	  section.data(7).dtTransOffset = 10;
	
	  ;% rtDW.pqkcete42o.LoggedData
	  section.data(8).logicalSrcIdx = 11;
	  section.data(8).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.ezauhd3tt0
	  section.data(1).logicalSrcIdx = 12;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% rtDW.h4rggrbxnc.PrevIndex
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.powianu2bz.PrevIndex
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.oxfi1zw3ko.Tail
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.engssbe05o.Tail
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.m0cwy3q4nt.Tail
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
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


  targMap.checksum0 = 4193358515;
  targMap.checksum1 = 617856143;
  targMap.checksum2 = 3689207024;
  targMap.checksum3 = 1471515770;

