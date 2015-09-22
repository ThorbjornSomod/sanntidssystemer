# program executable name 
TARGET = main
# compiler flags 
CFLAGS = -g -Wall 
# linker flags 
LDFLAGS = -g -pthread -lrt -lcomedi -lm
# list of sources 
SOURCES = $(shell find -name "*.c") 
# default rule, to compile everything 
all: $(TARGET) 
# define object files 
OBJECTS = $(SOURCES:.c=.o) 
# link programs 
$(TARGET): $(OBJECTS) 
	gcc $^ -o $@ $(LDFLAGS)  
# compile 
%.o : %.c 
	gcc $(CFLAGS) -c -o $@ $< 
# cleaning 
clean: 
	rm -f $(TARGET) $(OBJECTS)
