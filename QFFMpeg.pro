#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T09:23:35
#
#-------------------------------------------------

QT += core gui
QT += widgets

QMAKE_CXXFLAGS += -D__STDC_CONSTANT_MACROS
#QMAKE_LFLAGS += -Wl,-Bsymbolic

TARGET = QFFMpeg
TEMPLATE = lib
VERSION = 0.1.10

DEFINES += QFFMPEG_LIBRARY

unix: include(linux.pro)


# QFFMpeg forráskódok
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
    avUtility/ffUtil.cpp \
    avFormat/ffAudioStream.cpp \
    avFormat/ffSubtitleStream.cpp \
    avFormat/ffDataStream.cpp \
    avUtility/ffSampleFormat.cpp \
    avUtility/ffdictionaryitem.cpp

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
    avUtility/ffUtil.h \
    avFormat/ffAudioStream.h \
    avFormat/ffSubtitleStream.h \
    avFormat/ffDataStream.h \
    avUtility/ffSampleFormat.h \
    avUtility/ffdictionaryitem.h

DISTFILES += \
    VerzióInfó.txt \
    LICENSE \
    Állapot

LIBS += -L$$FFMPEG_LIB
LIBS += $$FFMPEG_FILES
#PRE_TARGETDEPS += $$FFMPEG_LIB_NAMES

LIBS += -L$$CODEC_LIB
LIBS += $$CODEC_FILES
#PRE_TARGETDEPS += $$CODEC_LIB_NAMES


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/LowyLib/Release -lLowyLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/LowyLib/Debug/ -lLowyLib
else:unix:!macx: LIBS += -L$$HOME/lib -lLowyLib

INCLUDEPATH += $$HOME/include
DEPENDPATH += $$HOME/LowyLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build/LowyLib/Release/libLowyLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build/LowyLib/Debug/libLowyLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build/LowyLib/Release/LowyLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build/LowyLib/Debug/LowyLib.lib
else:unix:!macx: PRE_TARGETDEPS += $$HOME/lib/libLowyLib.a

INCLUDEPATH += $$FFMPEG_INCLUDE
#DEPENDPATH +=  $$FFMPEG_INCLUDE
INCLUDEPATH += $$CODEC_INCLUDE
#DEPENDPATH +=  $$CODEC_INCLUDE


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lavformat
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lavformat

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libavformat.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libavformat.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/avformat.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/avformat.lib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lavcodec
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lavcodec


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libavcodec.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libavcodec.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/avcodec.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lavdevice
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lavdevice

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libavdevice.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libavdevice.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/avdevice.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/avdevice.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lavfilter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lavfilter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libavfilter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libavfilter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/avfilter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/avfilter.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lavutil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lavutil

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libavutil.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libavutil.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/avutil.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/avutil.lib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lfdk-aac
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lfdk-aac

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libfdk-aac.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libfdk-aac.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/fdk-aac.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/fdk-aac.lib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lmp3lame
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lmp3lame

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libmp3lame.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libmp3lame.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/mp3lame.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/mp3lame.lib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lpostproc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lpostproc

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libpostproc.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libpostproc.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/postproc.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/postproc.lib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lswresample
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lswresample

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libswresample.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libswresample.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/swresample.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/swresample.lib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lswscale
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lswscale

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libswscale.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libswscale.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/swscale.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/swscale.lib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lvpx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lvpx

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libvpx.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libvpx.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/vpx.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/vpx.lib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/release/ -lx265
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib-ffmpeg/lib/debug/ -lx265

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/libx265.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/libx265.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/release/x265.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib-ffmpeg/lib/debug/x265.lib

#SUBDIRS += \
#    linux.pro

