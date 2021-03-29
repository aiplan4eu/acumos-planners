#!/bin/bash

APDIR=`pwd | gawk '{ print gensub(/\/docker/, "", 1) }'`

docker run -it -d \
    --name pddl-planner-server --rm \
    --net=host \
    -v $APDIR:/home/robot/src/acumos-planners \
    felixfi/pddl-planners

