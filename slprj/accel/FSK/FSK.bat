@echo off
set MATLAB=C:\Program Files\MATLAB\R2020a
"%MATLAB%\bin\win64\gmake" -f FSK.mk  OPTS="-DTID01EQ=0"
