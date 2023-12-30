LIBS += ./libacidcam.dll ./acidcam_plugin_x64/libopencv*a
QMAKE_CXXFLAGS += -O3 -I./include -I./
PLUGIN_NAME=plugin.acidcam
all:
	g++ -std=c++17 -shared -o $(PLUGIN_NAME) $(LIBS) $(QMAKE_CXXFLAGS) plugin.cpp
