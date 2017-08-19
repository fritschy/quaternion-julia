FASTMATH = -ffast-math -ffp-contract=fast
CPPFLAGS += -I/usr/local/include -I/usr/include -Iminifb/include -Iglm -DGLM_FORCE_SWIZZLE -DGLM_FORCE_INLINE -DGLM_ENABLE_EXPERIMENTAL
LDFLAGS += -L/usr/local/lib -L/usr/lib -lX11
CXXFLAGS += -std=c++14 -march=native -O3 -g
CFLAGS += -march=native -O3 -g
CC = clang
CXX = clang++

FAST=1

ifneq ($(SANITIZER),)
   CFLAGS += -fsanitize=$(SANITIZER)
   CXXFLAGS += -fsanitize=$(SANITIZER)
   LDFLAGS += -fsanitize=$(SANITIZER)
endif

ifneq ($(FAST),)
   CXXFLAGS += $(FASTMATH)
endif

ifneq ($(OPENMP),)
   CXXFLAGS += -fopenmp
   LDFLAGS += -fopenmp
   CPPFLAGS += -DUSE_OPENMP
endif

all:	quaternion-julia

quaternion-julia: main.o minifb/src/x11/X11MiniFB.o
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	rm -f minifb/src/x11/X11MiniFB.o main.o quaternion-julia
