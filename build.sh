# if [ -d "build" ]; then
#     rm -rf build
# fi
# cmake -G Ninja -B build && cmake --build build --config Release
cmake -G Ninja -B build -DBUILD_APP=$1 && cmake --build build --config Release
./dist/$1