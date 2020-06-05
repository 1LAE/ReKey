include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += -Wall -Wextra -Werror
QMAKE_CFLAGS += -Wall -Wextra -Werror

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_imgcodecs \
    -lopencv_highgui \
    -lopencv_objdetect \
    -lopencv_video \
    -lopencv_videoio


HEADERS += \
        ../ReKey/helper.h \
        tst_allTests.h

SOURCES += main.cpp \    
    ../ReKey/helper.cpp \
    ../ReKey/convert.cpp \
    ../ReKey/process_frame.cpp

INCLUDEPATH += \
    ../ReKey \
    /usr/include/
