#ifndef FFAUDIOSTREAM_H
#define FFAUDIOSTREAM_H

#include <QObject>
#include "ffStream.h"

class ffAudioStream : public ffStream
{
public:
    ffAudioStream(QObject* parent);
    ffAudioStream(void *avStream, QObject *parent);

    QString TypeString() Q_DECL_OVERRIDE;
};

#endif // FFAUDIOSTREAM_H
