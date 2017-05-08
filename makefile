LIBRARYPATHS = -Llibraries -LC:/VulkanSDK/1.0.46.0/Lib
LIBRARIES = -lvulkan-1 -lSDL2main -lSDL2
COMPILER_OPTIONS = -Wall -g -std=c++11
COMPILER = x86_64-w64-mingw32-c++
TARGETNAME = cerberus.exe
LDFLAGS = $(LIBRARYPATHS) $(LIBRARIES)

VPATH = Engine Utils

OBJS = main.o engine.o window.o sdlwindow.o vulkanloader.o vulkaninstance.o vulkanengine.o vulkandevice.o

REBUILDABLES = $(OBJS) $(TARGETNAME)

all:
	make $(TARGETNAME) -j30
	echo Compile done

$(TARGETNAME): $(OBJS)
	$(COMPILER) $(COMPILER_OPTIONS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(COMPILER) $(COMPILER_OPTIONS) -o $@ -c $<

clean:
	del /s $(REBUILDABLES) $(OBJS:.o=.dep)
	echo Clean done

rebuild:
	make clean
	make -j30

%.dep : %.cpp
	$(COMPILER) -M $(COMPILER_OPTIONS) $< > $@
include $(OBJS:.o=.dep)