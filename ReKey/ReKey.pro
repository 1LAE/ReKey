CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        convert.cpp \
        helper.cpp \
        main.cpp \
        process_frame.cpp

HEADERS += \
    helper.h

LIBS += -lopencv_core \
#        -L/usr/local/lib \
#        -L/usr/lib/x86_64-linux-gnu \
        -lopencv_imgproc \
        -lopencv_video \
#        -lopencv_imgcodecs \
#        -lopencv_videoio

INCLUDEPATH += ../opencv4/

