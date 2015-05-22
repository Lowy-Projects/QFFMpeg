#include "ffAudioStream.h"

ffAudioStream::ffAudioStream(QObject *parent)
    : ffStream(parent)
{
    m_MediaType = MediaType_Audio;
}

ffAudioStream::ffAudioStream(void *avStream, QObject *parent)
    : ffStream(avStream, parent)
{
    m_MediaType = MediaType_Audio;
}

QString ffAudioStream::TypeString()
{
        return QString(tr("Audio"));
}


