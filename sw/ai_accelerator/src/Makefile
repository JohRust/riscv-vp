OBJECTS  = main.o bootstrap.o ai_accelerator.o ai_caller.o shap.o irq.o
CFLAGS   = -march=rv32i -mabi=ilp32 -g
CXXFLAGS = -march=rv32i -mabi=ilp32 -g
LDFLAGS  = -nostartfiles -Wl,--no-relax

include ../../Makefile.common
override LD = $(CXX)

# Make test target and run tests
test:
	$(MAKE) -C ../test
	./../test/test_all

clean: test_clean # Add test_clean to clean target
test_clean::# Clean test directory
	$(MAKE) -C ../test clean
