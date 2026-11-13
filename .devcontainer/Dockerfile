FROM ubuntu:26.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    clang \
    clangd \
    clang-tidy \
    cmake \
    git \
    ninja-build \
    python3 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

ENV CC=clang
ENV CXX=clang++

USER ubuntu
