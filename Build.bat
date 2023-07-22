@ECHO OFF
CLS

make -f "Engine.mak" all
@REM make -f "Sandbox.mak" all
make -f "Editor.mak" all