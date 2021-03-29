# Docker file for ROS & gRPC
# Luca Iocchi, 2021

FROM ros:melodic-ros-base-bionic

ARG DEBIAN_FRONTEND=noninteractive


###### USER root ######

# install libraries and ros packages 

RUN apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

RUN apt-get update && \
    apt-get install -y tmux less sudo xterm wget \
        nano unzip iputils-ping net-tools openssh-client \
        build-essential autoconf libtool pkg-config \
        python3-pip && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*


# User: robot (password: robot) with sudo power

RUN useradd -ms /bin/bash robot && echo "robot:robot" | chpasswd && adduser robot sudo


###### USER robot ######

USER robot

RUN echo "set -g mouse on" > $HOME/.tmux.conf 



### ROS ###

# Init ROS workspace

RUN mkdir -p $HOME/ros/catkin_ws/src

RUN /bin/bash -c "source /opt/ros/melodic/setup.bash && cd $HOME/ros/catkin_ws/src && catkin_init_workspace && cd .. && catkin_make"

RUN rosdep update


### gRPC ###

RUN mkdir -p $HOME/.local


# Version 3.13 or later of cmake is required to install gRPC locally

RUN mkdir -p $HOME/src/cmake && cd $HOME/src/cmake && \
    wget -q -O cmake-linux.sh https://github.com/Kitware/CMake/releases/download/v3.17.0/cmake-3.17.0-Linux-x86_64.sh && \
    sh cmake-linux.sh -- --skip-license --prefix=$HOME/.local && \
    rm cmake-linux.sh

RUN cd $HOME/src && \
    git clone --recurse-submodules -b v1.34.1 https://github.com/grpc/grpc

RUN cd $HOME/src/grpc && \
    mkdir -p cmake/build && \
    cd cmake/build && \
    $HOME/.local/bin/cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$HOME/.local \
      ../.. && \
    make -j4 && \
    make install


# build the example

RUN cd $HOME/src/grpc/examples/cpp/helloworld && \
    mkdir -p cmake/build && \
    cd cmake/build && \
    $HOME/.local/bin/cmake -DCMAKE_PREFIX_PATH=$HOME/.local ../.. && \
    make -j4

# Install Python libs

RUN pip3 install grpcio grpcio-tools


# Set up .bashrc

RUN echo "" >> $HOME/.bashrc
RUN echo "export PATH=\"$PATH:$HOME/.local/bin\"" >> $HOME/.bashrc
RUN echo "" >> $HOME/.bashrc
RUN echo "export PKG_CONFIG_PATH=\"$PKG_CONFIG_PATH:$HOME/.local/lib/pkgconfig\"" >> $HOME/.bashrc
RUN echo "" >> $HOME/.bashrc
RUN echo "source $HOME/ros/catkin_ws/devel/setup.bash" >> $HOME/.bashrc
RUN echo "" >> $HOME/.bashrc

# Check catkin_make

RUN /bin/bash -ci "cd $HOME/ros/catkin_ws; catkin_make"


# Set working dir and container command

WORKDIR /home/robot

CMD /usr/bin/tmux



