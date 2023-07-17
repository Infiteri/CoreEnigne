@ECHO OFF
CLS

make -f "Engine.mak" all
make -f "Sandbox.mak" all
@REM make -f "Editor.mak" all