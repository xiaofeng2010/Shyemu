:shyemu
ShyEmu-world.exe
GOTO dump

:dump 
@echo off
set datum=%date%
set datum1=%date: =-%
set datum2=%datum1:.=-%

@echo off
for /F "tokens=1-4 delims=:., " %%a in ('time/T') do set Time=%%ah-%%bmin
ECHO [ShyEmu-world] SHUTDOWN ON %datum2% %Time% >> restarterlog.log
ECHO [ShyEmu-world] Restarting ... >> restarterlog.log
GOTO shyemu