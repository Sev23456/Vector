
CC = gcc
CFLAGS = -std=c11 -O2
LDLIBS = -lm
RM = rm -f

MAIN = main.exe
TEST = test_vectors.exe

.PHONY: all main test gen-bat run clean help

all: $(MAIN) $(TEST)

$(MAIN): main.c vector_api.c vector_api.h
	$(CC) $(CFLAGS) -o $(MAIN) main.c vector_api.c

$(TEST): test_vectors.c vector_api.c vector_api.h
	$(CC) $(CFLAGS) -o $(TEST) test_vectors.c vector_api.c $(LDLIBS)

gen-bat:
	@echo Creating build.bat...
	@echo @echo off > build.bat
	@echo gcc -std=c11 -O2 -o main.exe main.c vector_api.c >> build.bat
	@echo gcc -std=c11 -O2 -o test_vectors.exe test_vectors.c vector_api.c -lm >> build.bat
	@echo echo Build complete. >> build.bat
	@echo Build.bat created.

run: $(MAIN)
	./$(MAIN)

test: $(TEST)
	./$(TEST)

clean:
	$(RM) $(MAIN) $(TEST) build.bat

help:
	@echo Targets:
	@echo "  all     - build main and tests"
	@echo "  gen-bat - generate Windows build script build.bat"
	@echo "  run     - run main.exe"
	@echo "  test    - run test_vectors.exe"
	@echo "  clean   - remove build artifacts"
