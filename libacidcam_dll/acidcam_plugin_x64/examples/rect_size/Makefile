#CXX=x86_64-w64-mingw32-g++
CXX=g++
LIBS += ../../../libacidcam.dll ../../../acidcam_plugin_x64/libopencv*a
QMAKE_CXXFLAGS += -O3 -I../../../include -I./ -I../../../acidcam_plugin_x64/include
PLUGIN_NAME=rect_size.acidcam
all:
	$(CXX) -std=c++17 -shared -o $(PLUGIN_NAME) $(LIBS) $(QMAKE_CXXFLAGS) plugin.cpp
