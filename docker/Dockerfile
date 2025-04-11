FROM ubuntu:latest

# Avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package lists and install essential build tools and dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    python3 \
    python3-pip \
    python3-dev \
    libopencv-dev \
    wget \
    gcc \
    g++ \
    gfortran \
    gcc-multilib \
    g++-multilib \
    binutils \
    libtool \
    autoconf \
    automake \
    make \
    && rm -rf /var/lib/apt/lists/*

# Install additional C++ development tools
RUN apt-get update && apt-get install -y \
    gdb \
    valgrind \
    clang \
    clang-format \
    gcc-doc \
    cpp-doc \
    libstdc++-12-dev \
    libstdc++-12-doc \
    && rm -rf /var/lib/apt/lists/*

# Set Python3 as default python
RUN ln -s /usr/bin/python3 /usr/bin/python

# Set working directory
WORKDIR /workdir

