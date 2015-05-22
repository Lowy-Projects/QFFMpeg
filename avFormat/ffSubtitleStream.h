#ifndef FFSUBTITLESTREAM_H
#define FFSUBTITLESTREAM_H

#include <QObject>
#include "ffStream.h"

class ffSubtitleStream : public ffStream
{
public:
    ffSubtitleStream(QObject* parent);
    ffSubtitleStream(void *avStream, QObject *parent);

    QString TypeString() Q_DECL_OVERRIDE;
};

#endif // FFSUBTITLESTREAM_H
