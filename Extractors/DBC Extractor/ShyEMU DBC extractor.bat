REM ## Universal DBC Extractor for ShyEMU ##
COLOR 3

@CLS
@ECHO OFF
REM ## Main Menu
:menu
cls

ECHO.
ECHO.
ECHO		 ####################################
ECHO		 #######        ShyEMU        #######
ECHO		 ######      DBC Extractor     ######
ECHO		 ####################################
ECHO.
ECHO		 Please type the letter for the option:
ECHO.
ECHO		  1 = Extract US DBC Files
ECHO		  2 = Extract GB DBC Files
ECHO.
ECHO.
ECHO		  x - Exit
ECHO.

set /p l=             Enter Letter:

if %l%==1 goto us_english
if %l%==2 goto gb_english
if %l%==x goto quit
if %l%==X goto quit
goto error

REM ## US English
:us_english
CLS
ECHO.
ECHO.
ECHO [Extraction] Started...
ECHO [Extraction] Extracting DBC Files ...
mpqe /p locale-enUS.MPQ DBFilesClient\*.dbc
GOTO move_files

REM ## GB English
:gb_english
CLS
ECHO.
ECHO.
ECHO [Extraction] Started...
ECHO [Extraction] Extracting DBC Files ...
mpqe /p locale-enGB.MPQ DBFilesClient\*.dbc


:move_files

md dbc
copy MPQOUT\DBFilesClient dbc

RMDIR /s /q MPQOUT
CLS
ECHO [Extraction] Finished
ECHO.
PAUSE
GOTO menu

:error
CLS
ECHO.
ECHO.
ECHO [ERROR] An error has occured, you will be directed back to the
ECHO [ERROR] main menu.
PAUSE    
GOTO menu

GOTO quit  
:quit