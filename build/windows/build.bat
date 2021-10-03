: Make out folder
@if not exist out\ (
  @mkdir "out"
)

: Build
@cmake -S . -B out -D CMAKE_BUILD_TYPE=Release
@cmake --build out --config Release