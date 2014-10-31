#!/bin/sh

echo ""
echo "> moving previous files to _previous_"

mv histos.root _previous_/
mv plots/*.png _previous_/plots/
mv log.txt _previous_/
mv summary.txt _previous_/

echo ""
echo "> copying histos.root from lpc (Spots/)"

echo ""
echo "> running Nickroot.cpp using root"

root -l -b -q 'NickZemu.cpp'
# >& summary.txt

echo ""
echo "> converting eps to png"

#./eps2png.sh plots/*.eps
##./eps2png.sh plots/MM/*.eps

#./eps2png.sh plots/EE/*.eps

echo ""
echo "> removing eps files"

rm plots/*.eps
rm plots/MM/*.eps
rm plots/EE/*.eps

echo ""
echo "> finished"
echo ""