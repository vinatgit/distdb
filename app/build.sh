#!/bin/bash

export ROOT_DIR=$(git rev-parse --show-toplevel)
export INSTALL_DIR=$ROOT_DIR/bin
export PATH="$INSTALL_DIR/bin:$PATH"
mkdir -p $INSTALL_DIR

mkdir -p cmake/build
cd cmake/build
cmake -DCMAKE_PREFIX_PATH=$INSTALL_DIR ../..
make -j 4
