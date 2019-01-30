LIBCMINI=../libcmini
LIBCMINI_INCLUDE=$(LIBCMINI)/include
LIBCMINI_LIB=$(LIBCMINI)/build/

TOOLCHAIN_PREFIX=m68k-atari-mint
CXX=$(TOOLCHAIN_PREFIX)-c++

DEPEND=depend 

STACK=$(TOOLCHAIN_PREFIX)-stack 
STACKSIZE=470K

TARGET=mini++.prg
TARGETM=miniml.prg

SRCS= \
	main.cc

OBJS = $(patsubst %.cc, %.o, $(SRCS))

CXXFLAGS=-fomit-frame-pointer \
    -Wall \
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
	$(CXX) $(CXXFLAGS) $(LIBCMINI_LIB)/startup.o $? $(LDFLAGS) -o $@ 
	$(STACK) -S $(STACKSIZE) $(TARGET)

# link with mintlib for comparision
$(TARGETM):$(OBJS)
	$(CXX) -o $@ $?
	$(STACK) -S $(STACKSIZE) $@

%.o%.cc:
	$(CXX) -c -I$(LIBCMINI_INCLUDE) $< -o $@

.PHONY: clean
clean:
	- rm -f $(OBJS) $(TARGET) $(TARGETM) $(DEPEND)

strip: $(TARGET) $(TARGETM)
	$(TOOLCHAIN_PREFIX)-strip $?

$(DEPEND): $(SRCS)
	- rm -f $(DEPEND)
	$(CXX) $(CXXFLAGS) -I$(LIBCMINI_INCLUDE) -M $? >> $(DEPEND)

.PHONY: printvars
printvars:
	$(foreach V,$(.VARIABLES), $(if $(filter-out environment% default automatic, $(origin $V)),$(warning $V=$($V))))

ifneq (clean,$(MAKECMDGOALS))
-include $(DEPEND)
endif
