#ifndef FFVIDEOSTREAM_H
#define FFVIDEOSTREAM_H

#include <QObject>
#include "ffStream.h"

class ffVideoStream : public ffStream
{
public:
    ffVideoStream(QObject* parent);
    ffVideoStream(void *avStream, QObject *parent);

    QString TypeString() Q_DECL_OVERRIDE;
};

#endif // FFVIDEOSTREAM_H
