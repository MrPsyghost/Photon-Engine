FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    mingw-w64 \
    cmake \
    ninja-build \
    git \
    wget \
    curl \
    pkg-config \
    make \
    unzip \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root/env

RUN mkdir deps && cd deps && \
    wget https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip && \
    unzip glfw-3.4.bin.WIN64.zip

ENV GLFW_DIR=/root/env/deps/glfw-3.4.bin.WIN64