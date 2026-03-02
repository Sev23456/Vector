@echo off
echo Building main.exe and test_vectors.exe...
gcc -std=c11 -O2 -o main.exe main.c vector_api.c
if errorlevel 1 (
  echo Failed to build main.exe
  exit /b 1
)
gcc -std=c11 -O2 -o test_vectors.exe test_vectors.c vector_api.c -lm
if errorlevel 1 (
  echo Failed to build test_vectors.exe
  exit /b 1
)
echo Build complete.
exit /b 0
