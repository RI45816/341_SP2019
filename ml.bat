if exist "%USERPROFILE%\Downloads\CMSC 341" rmdir "%USERPROFILE%\Downloads\CMSC 341"
mklink /d "%USERPROFILE%\Downloads\CMSC 341\" "%~f1"