# Vector CLI and Tests

Build (Windows / MinGW / MSYS or similar):

```
gcc -std=c11 -O2 -o main.exe main.c vector_api.c
gcc -std=c11 -O2 -o test_vectors.exe test_vectors.c vector_api.c
```

Run the CLI:

```
./main.exe
```

Run the tests:

```
./test_vectors.exe
```

The CLI allows creating two vectors `A` and `B` of arbitrary (non-negative) dimension, entering their elements, printing them, computing `A+B` and the scalar product `A . B`.
