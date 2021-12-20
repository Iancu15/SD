#!/bin/bash

#/
# Created by Nan Mihai on 16.03.2017
# Copyright (c) 2017 Nan Mihai. All rights reserved.
# Laborator 4 - Structuri de date (seria CC)
#/
TOTAL=0
EXEC=prob4
ZERO=0

make &> /dev/null

for EX in {1..4}
do
    IN_FILE="tests/test"$EX".in"
    CORRECT_FILE="tests/test"$EX".ref"
    OUT_FILE="tests/test"$EX".out"
    ./$EXEC $IN_FILE $OUT_FILE &> /dev/null
    diff $OUT_FILE $CORRECT_FILE &> /dev/null
    EXIT_CODE=$?
    if [[ $EXIT_CODE -eq $ZERO ]]
    then
        TOTAL=$(awk -v TOTAL=$TOTAL 'BEGIN { print TOTAL + 0.5 }')
        echo "Problema 4 - Testul $EX ............................... trecut!"
    else
        echo "Problema 4 - Testul $EX ............................... picat!"
    fi
    rm "$OUT_FILE"
done

BEST=2

if [ "$TOTAL" -eq $BEST ]; then
	echo "Felicitari! Ai punctajul maxim: "$BEST"p! :)"
else
	echo "Ai acumulat "$TOTAL"p din maxim 2p! :("
fi

make clean &> /dev/null