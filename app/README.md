Get it running

cd $APP_ROOT/cmake/build
cmake ../..
make -j 4
./server &
./client &
