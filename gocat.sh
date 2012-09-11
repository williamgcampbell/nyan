#!/bin/bash

# config
. `pwd`/config

move() {
    for((x=0; x < $LINES; x++));
    do tput $1
    done;
}

# watch for ^C and quit
trap finally INT
finally() {
    # make cursor visible again
    tput cnorm

    # reset cursor to beginning
    move "cud1"

    # stop audio

    echo "Done..."
    exit 0
}

# need multi-space strings
IFS='%'

# start audio

# hide the cursor
tput civis

# main loop
while [ 1 ]; do
    printf $cat1
    move "cuu1"
    sleep $SLEEP_TIME
    printf $cat2
    move "cuu1"
    sleep $SLEEP_TIME
done;

#CTRL+C to quit
