MOC_DIR = .moc
OBJECTS_DIR = .obj

TEMPLATE = app
CONFIG += qt warn_on release thread
SOURCES = terrain_efficace.cpp
TARGET = ../../build/terrain_efficace
CONFIG -= app_bundle

INCLUDEPATH += /usr/include/opencv2
QMAKE_LFLAGS += -Wl,-R/usr/lib/x86_64-linux-gnu -L/usr/lib/x86_64-linux-gnu

LIBS += \
-lopencv_core \
-lopencv_highgui \
-lopencv_imgproc \
-lopencv_features2d \
-lopencv_calib3d
