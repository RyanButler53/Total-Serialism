cd /TotalSerialism
pwd
mkdir -p build;
pwd
cd build;
pwd
rm -rf *
echo "Starting Cmake!"
cmake -DCMAKE_BUILD_TYPE=RELEASE -DTS_DO_TESTS=FALSE ..;
cmake --build . -j15
cd ..
