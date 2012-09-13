#!/usr/bin/env bash

BASEDIR=$(dirname $0)
SLEEP_TIME=.5

printf "( •_•)"
sleep $SLEEP_TIME
printf ">\033[30m⌐■-■\033[0m"
sleep $SLEEP_TIME

# move back 11 spots (to the beginning of the line
printf "\b\b\b\b\b\b\b\b\b\b\b"
# we need extra spaces at the end to overwrite the printf statements
printf "(\033[30m⌐■\033[0m_\033[30m■\033[0m)     \n"

afplay "$BASEDIR/instantcsi.mp3"
