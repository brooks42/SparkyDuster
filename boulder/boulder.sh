#!/bin/bash
# should allow the options --restart, --start, and --stop
start=0
restart=0
stop=0
for i in "$@"
do
# case $i in
# --restart) restart=1;;
# --stop) stop=1;;
# --start) start=1;;
# -h|--default) show_help
# esac
done
# run the nodejs server
# node --use-strict index.js
# write the PID to a file somewhere for later