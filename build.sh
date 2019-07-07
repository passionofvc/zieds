mkdir -p build 1>/dev/null 2>&1
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
#cmake  -DCMAKE_BUILD_TYPE=Release ..
make
