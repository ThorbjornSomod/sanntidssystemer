# program executable name 
TARGET = ass10
# compiler flags 
CFLAGS = -g -Wall 
# linker flags 
LDFLAGS = -g -pthread -lrt
# list of sources 
SOURCES = $(shell find -name "*.c") 
# default rule, to compile everything 
all: $(TARGET) 
# define object files 
OBJECTS = $(SOURCES:.c=.o) 
# link programs 
$(TARGET): $(OBJECTS) 
	/home/student/Downloads/Exercise10/buildroot/output/staging/usr/bin/avr32-linux-gcc $(LDFLAGS) -o $@ $^ 
# compile 
%.o : %.c 
	/home/student/Downloads/Exercise10/buildroot/output/staging/usr/bin/avr32-linux-gcc $(CFLAGS) -c -o $@ $< 
# cleaning 
clean: 
	rm -f $(TARGET) $(OBJECTS)
