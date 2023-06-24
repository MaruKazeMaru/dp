#!/bin/bash

RESULT_FILE="./data/dp_sym_result.txt"

cat ${RESULT_FILE} > /dev/null
[ $? -eq 0 ] && rm ${RESULT_FILE}
touch ${RESULT_FILE} 

for i in $(seq $3 $4 $5)
do
	./build/src/main.out $1 $2 $i | grep " O " | wc -l >>  ${RESULT_FILE}
	echo "$i finished"
done
