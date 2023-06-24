#!/bin/bash

./dp_sym.bash city011 city012 0 0.1 10
[ $? -eq 0 ] || exit 1
mv data/dp_sym_result.txt data/result_011_012.txt
echo "011 012 finished"

./dp_sym.bash city011 city021 0 0.1 10
[ $? -eq 0 ] || exit 1
mv data/dp_sym_result.txt data/result_011_021.txt
echo "011 021 finished"

./dp_sym.bash city011 city022 0 0.1 10
[ $? -eq 0 ] || exit 1
mv data/dp_sym_result.txt data/result_011_022.txt
echo "011 022 finished"

./dp_sym.bash city012 city021 0 0.1 10
[ $? -eq 0 ] || exit 1
mv data/dp_sym_result.txt data/result_012_021.txt
echo "012 021 finished"

./dp_sym.bash city011 city022 0 0.1 10
[ $? -eq 0 ] || exit 1
mv data/dp_sym_result.txt data/result_012_022.txt
echo "012 022 finished"

./dp_sym.bash city021 city022 0 0.1 10
[ $? -eq 0 ] || exit 1
mv data/dp_sym_result.txt data/result_021_022.txt
echo "021 022 finished"
