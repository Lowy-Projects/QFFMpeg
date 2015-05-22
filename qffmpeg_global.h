#ifndef QFFMPEG_GLOBAL_H
#define QFFMPEG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QFFMPEG_LIBRARY)
#  define QFFMPEGSHARED_EXPORT Q_DECL_EXPORT
#  include "ffmpeg_headers.h"
#else
#  define QFFMPEGSHARED_EXPORT Q_DECL_IMPORT
#endif

#define ffTimeBaseDefault  -1

#endif // QFFMPEG_GLOBAL_H
