@ECHO OFF
for /f "tokens=*" %%G in ('dir /b "C:\Users\n3majo00\Documents\visual studio 2012\Projects\RageAgainstBugs\RageAgainstBugs\gfx\*"') do convert.exe %%G -strip %%G