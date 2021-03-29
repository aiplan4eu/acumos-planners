# Install

Install `docker`. No need to install other libraries, everything will be included in docker images.

# Build the pddl-planner client image

    cd acumos-planners/docker
    ./build.bash

will build the docker image `pddl-planner-client` including ROS and gRPC libraries. See `Dockerfile.ros_grpc` for details.

# Running client-server apps

Client-server apps can be run through pddl client and server containers.

## Run the pddl-planner server

    ./start-server.bash

## Run the pddl-planner client

    ./run-client.bash

All next commands are issues in the docker conatiner.

First time, you need to compile the code

    cd src/acumos-planners
    make
    cd python_client
    make

Note: the generated files are stored in local host file system, since the `acumos-planners` folder is mounted as a volume in the docker container.

In the `pddl-planner-client` container, now you can send a request to `pddl-planner-server`.

Examples:

C++ code:

    cd src/acumos-planners
        
    ./planner_client popf examples/domain_turtlebot.pddl examples/problem_turtlebot.pddl

    ./planner_client ff examples/dom3.pddl  examples/pb3a.pddl

    ./planner_client fd examples/philosophers/domain.pddl examples/philosophers/p01-phil2.pddl "--alias lama-first"

    ./planner_client optic  examples/dom3d.pddl  examples/pb3a.pddl "-N"


Python code:

    cd src/acumos-planners

    python3 planner_client.py popf ../examples/domain_turtlebot.pddl ../examples/problem_turtlebot.pddl

    ...


## Stop all the services

    ./stop-all.bash


