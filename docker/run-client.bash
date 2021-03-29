#!/bin/bash

# Use: ./run.bash

APDIR=`pwd | gawk '{ print gensub(/\/docker/, "", 1) }'`

docker run -it \
    --name pddl-planner-client --rm \
    --net=host \
    -v $APDIR:/home/robot/src/acumos-planners \
    pddl-planner-client
  

