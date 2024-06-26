#!/bin.bash

export ROOT_DIR=$(git rev-parse --show-toplevel)
export INSTALL_DIR=$ROOT_DIR/bin
export PATH="$INSTALL_DIR/bin:$PATH"
mkdir -p $INSTALL_DIR

# Install dependencies
yes | brew install autoconf automake libtool pkg-config

# Clone grpc
git clone --recurse-submodules -b v1.64.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc
cd grpc
mkdir -p cmake/build
cd cmake/build
cmake -DgRPC_INSTALL=ON \
      -DCMAKE_BUILD_TYPE=Release \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
      ../..
make -j 4
make install

cd $ROOT_DIR
rm -rf grpc
