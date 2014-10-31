#!/bin/sh

echo ""
echo "> moving previous files to _previous_"


echo ""
echo "> copying histos.root from lpc (Spots/)"


echo ""
#root -l 'rochcor2012jan22.C+'
root -l -b -q 'Zemu.cpp'

echo ""
echo "> finished"
echo ""