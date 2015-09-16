#--------------------------------------------------
#
# qffMpeg lib ffMpeg linking settings
# By: Lowy 2015
#

    HOME = $$system(echo $HOME)

# ffmpeg és kódek könyvtárak
        FFMPEG_LIB = /usr/lib
        FFMPEG_INCLUDE = /usr/include
        CODEC_LIB = /usr/lib
        CODEC_INCLUDE = /usr/include

# Telepítési beállítások
    header_files.files = $$PWD/*.h
    header_files.files += $$PWD/qffmpeg
    header_files.path = /usr/include/QFFMpeg
    INSTALLS += header_files

    header_avFormat.files = $$PWD/avFormat/*.h
    header_avFormat.files += $$PWD/avFormat/avFormat
    header_avFormat.path = /usr/include/QFFMpeg/avFormat
    INSTALLS += header_avFormat

    header_avUtility.files = $$PWD/avUtility/*.h
    header_avUtility.files += $$PWD/avUtility/avUtility
    header_avUtility.path = /usr/include/QFFMpeg/avUtility
    INSTALLS += header_avUtility

    target.path = /usr/lib
    INSTALLS += target

# ffmpeg könyvtárak
FFMPEG_FILES = \
        -lavformat \
        -lavcodec  \
        -lavdevice \
        -lavfilter   \
        -lavutil      \
        -lpostproc \
        -lswresample \
        -lswscale

FFMPEG_LIB_NAMES = \
        $$FFMPEG_LIB/libavformat      \
        $$FFMPEG_LIB/libavcodec        \
        $$FFMPEG_LIB/libavdevice       \
        $$FFMPEG_LIB/libavfilter          \
        $$FFMPEG_LIB/libavutil            \
        $$FFMPEG_LIB/libpostproc      \
        $$FFMPEG_LIB/libswresample \
        $$FFMPEG_LIB/libswscale


#ffmpeg statikus kódekek
CODEC_FILES = \
        -lmp3lame \
        -lfdk-aac     \
        -lvpx

CODEC_LIB_NAMES = \
        $$CODEC_LIB/libmp3lame.a \
        $$CODEC_LIB/libfdk-aac.a     \
        $$CODEC_LIB/libvpx.a

# ffmpeg shared kódekek
LIBS += -lvorbis
LIBS += -lvorbisenc
LIBS += -lvorbisfile
LIBS += -lx264
LIBS += -lx265
LIBS += -lz

//LIBS += -lvdpau
//LIBS += -lva
//LIBS += -ltheora
//LIBS += -ltheoraenc
//LIBS += -ltheoradec
