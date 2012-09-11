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
    killall afplay

    exit 0
}

# need multi-space strings
IFS='%'

# start audio
afplay $AUDIO_FILE&

# hide the cursor
tput civis

printf $sky_
move "cuu1"
sleep $START_WAIT_TIME

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
