# Make out folder
if [ ! -d "out" ]; then
  mkdir "out"
fi

# Build
cmake -S . -B out
cd out
make
cd ..