# Make out folder
if [ ! -d "out" ]; then
  mkdir "out"
fi

# Build
cmake -S . -B out -D CMAKE_BUILD_TYPE=Release
cmake --build out --config Release