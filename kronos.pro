QT += widgets network multimedia quick qml quickwidgets sql

TEMPLATE = app

! contains(ANDROID_TARGET_ARCH, armeabi-v7a)  {  # Si no es para Android entonces para Desktop

#    message( Compilacion para Desktop )

###############################################################################################
    unix:DIR_OPENCV_LIBS = /usr/local/lib  ####################################################
###############################################################################################

    unix:INCLUDEPATH += "/usr/include/GL/"                             # OpenGL
    unix:LIBS += "/usr/lib/x86_64-linux-gnu/libglut.so"                # OpenGL

    unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_core.so         # OpenCV
    unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_highgui.so      # OpenCV
    unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_imgproc.so      # OpenCV
    unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_objdetect.so    # OpenCV
    unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_calib3d.so      # OpenCV
    unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_ml.so           # OpenCV
    unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_features2d.so

    DEFINES += DESKTOP
}

contains(ANDROID_TARGET_ARCH, armeabi-v7a)  {  # Para Android

#    message( Compilacion para Android )

###############################################################################################
    DIR_ANDROID_OPENCV = /home/cosimani/Proyecto/2017/OpenCV-3.2.0-android-sdk/sdk/native #####
###############################################################################################

    INCLUDEPATH += $$DIR_ANDROID_OPENCV/jni/include

    LIBS += $$DIR_ANDROID_OPENCV/libs/armeabi-v7a/libopencv_java3.so

    LIBS += -L"$$DIR_ANDROID_OPENCV/libs/armeabi-v7a" \
            -L"$$DIR_ANDROID_OPENCV/3rdparty/libs/armeabi-v7a"
    LIBS += \
        -lIlmImf\
        -llibjasper\
        -llibjpeg\
        -llibpng\
        -llibtiff\
        -llibwebp\
        -ltbb\
        -lopencv_core\
        -lopencv_imgproc\
        -lopencv_highgui\
        -lopencv_calib3d\
        -lopencv_features2d\
        -lopencv_ml

    DISTFILES += \
        android/AndroidManifest.xml \
        android/res/values/libs.xml \
        android/build.gradle

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    ANDROID_EXTRA_LIBS = $$DIR_ANDROID_OPENCV/libs/armeabi-v7a/libopencv_java3.so
}

SOURCES += \
    main.cpp \
    image.cpp \
    scene.cpp \
    squircle.cpp \
    database.cpp \
    boton.cpp \
    principal.cpp \
    registro.cpp \
    campotexto.cpp \
    tecladito.cpp \
    numerito.cpp

HEADERS += \
    image.hpp \
    scene.h \
    squircle.h \
    database.hpp \
    boton.h \
    principal.h \
    registro.h \
    campotexto.h \
    tecladito.h \
    numerito.h

FORMS += \
    scene.ui \
    boton.ui \
    principal.ui \
    registro.ui

RESOURCES += \
    resources.qrc \
    qmlcamera.qrc \
    files.qrc \
    openglunderqml.qrc

