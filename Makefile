LIBCMINI=../libcmini
LIBCMINI_INCLUDE=$(LIBCMINI)/include
LIBCMINI_LIB=$(LIBCMINI)/build/

TOOLCHAIN_PREFIX=m68k-atari-mint
CXX=$(TOOLCHAIN_PREFIX)-c++

STACK=$(TOOLCHAIN_PREFIX)-stack 

TARGET=mini++.prg
TARGETM=miniml.prg

SRCS= \
	main.cc

OBJS = $(patsubst %.cc, %.o, $(SRCS))

CXXFLAGS=-fomit-frame-pointer \
	-O2 \
	-std=c++0x \
	-nostdlib \
	-g


# for the global constructors to be called, we need to link libgcc twice
# since __main() resides in libgcc.
LDFLAGS=-lstdc++ -L$(LIBCMINI_LIB) -lgcc -lcmini -lgcc

all: $(TARGET)

$(TARGET):$(OBJS)
	echo $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBCMINI_LIB)/startup.o $(OBJS) $(LDFLAGS) -o $@ 
	$(STACK) -S 1M $(TARGET)

# link with mintlib for comparision
$(TARGETM):$(OBJS)
	$(CXX) -o $@ $(OBJS)
	$(STACK) -S 1M $(TARGETM)

%.o%.cc:
	$(CXX) -c -I$(LIBCMINI_INCLUDE) $< -o $@

.PHONY: clean
clean:
	- rm -f $(OBJS) $(TARGET)

.PHONY: printvars
printvars:
	$(foreach V,$(.VARIABLES), $(if $(filter-out environment% default automatic, $(origin $V)),$(warning $V=$($V))))
