rm -rf build
mkdir ./build/ && cd ./build/ && conan install .. --build=missing  -s compiler.libcxx=libstdc++11 -j3
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
mv bin/r-type_client ..
mv bin/r-type_server ..
