# if [ -d "build" ]; then
#     rm -rf build
# fi
cmake -G Ninja -B build && cmake --build build --config Release