@echo off

set opts=-FC -GR- -EHa- -nologo -Zi
set code=%cd%
pushd Build
cl %opts% %code%\RYPRStorm -Fe.
popd
