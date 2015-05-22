#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T09:23:35
#
#-------------------------------------------------

QT += core gui
QT += widgets

QMAKE_CXXFLAGS += -D__STDC_CONSTANT_MACROS
#QMAKE_CFLAGS += -fPIC
QMAKE_LFLAGS += -Wl,-Bsymbolic

TARGET = QFfmpeg
TEMPLATE = lib

DEFINES += QFFMPEG_LIBRARY

SOURCES += \
    qffmpeg_base.cpp \
    avFormat/ffChapter.cpp \
    avFormat/ffDemuxer.cpp \
    avFormat/ffStream.cpp \
    avUtility/ffDictionary.cpp \
    avUtility/ffRational.cpp \
    avUtility/ffTimeStamp.cpp \
    avFormat/ffChapterModel.cpp \
    avFormat/ffVideoStream.cpp \
    avUtility/ffUtil.cpp

HEADERS += \
        qffmpeg_global.h \
    ffmpeg_headers.h \
    qffmpeg \
    avFormat/avFormat \
    avFormat/ffChapter.h \
    avFormat/ffDemuxer.h \
    avFormat/ffStream.h \
    avUtility/avUtility \
    avUtility/ffDictionary.h \
    avUtility/ffRational.h \
    avUtility/ffTimeStamp.h \
    avFormat/ffChapterModel.h \
    avFormat/ffVideoStream.h \
    avUtility/ffUtil.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/LowyLib/Release -lLowyLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/LowyLib/Debug/ -lLowyLib
else:unix:!macx: LIBS += -L$$PWD/../build/LowyLib/Debug/ -lLowyLib

INCLUDEPATH += $$PWD/../LowyLib
DEPENDPATH += $$PWD/../LowyLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build/LowyLib/Release/libLowyLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build/LowyLib/Debug/libLowyLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build/LowyLib/Release/LowyLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build/LowyLib/Debug/LowyLib.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../build/LowyLib/Debug/libLowyLib.a

INCLUDEPATH += $$PWD/../../lib-ffmpeg/include
DEPENDPATH += $$PWD/../../lib-ffmpeg/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lavformat
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lavformat
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lavformat

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libavformat.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libavformat.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/avformat.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/avformat.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libavformat.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lavcodec
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lavcodec
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lavcodec


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libavcodec.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libavcodec.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/avcodec.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/avcodec.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libavcodec.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lavdevice
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lavdevice
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lavdevice

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libavdevice.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libavdevice.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/avdevice.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/avdevice.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libavdevice.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lavfilter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lavfilter
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lavfilter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libavfilter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libavfilter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/avfilter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/avfilter.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libavfilter.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lavutil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lavutil
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lavutil

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libavutil.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libavutil.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/avutil.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/avutil.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libavutil.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lfdk-aac
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lfdk-aac
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lfdk-aac


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libfdk-aac.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libfdk-aac.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/fdk-aac.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/fdk-aac.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libfdk-aac.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lmp3lame
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lmp3lame
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lmp3lame

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libmp3lame.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libmp3lame.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/mp3lame.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/mp3lame.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libmp3lame.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lpostproc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lpostproc
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lpostproc


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libpostproc.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libpostproc.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/postproc.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/postproc.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libpostproc.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lswresample
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lswresample
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lswresample


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libswresample.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libswresample.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/swresample.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/swresample.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libswresample.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lswscale
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lswscale
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lswscale


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libswscale.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libswscale.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/swscale.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/swscale.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libswscale.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lvpx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lvpx
else:unix:!macx: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lvpx


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libvpx.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libvpx.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/vpx.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/vpx.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libvpx.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lx265
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lx265
else:unix: LIBS += -L$$PWD/../../lib-ffmpeg/lib/ -lx265

INCLUDEPATH += $$PWD/../../lib-ffmpeg/include
DEPENDPATH += $$PWD/../../lib-ffmpeg/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libx265.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libx265.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/x265.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/x265.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/libx265.a

LIBS += -lvorbis
LIBS += -lvorbisenc
LIBS += -lvorbisfile
LIBS += -ltheora
LIBS += -ltheoraenc
LIBS += -ltheoradec
LIBS += -lx264
LIBS += -lz
LIBS += -lvdpau
LIBS += -lva

