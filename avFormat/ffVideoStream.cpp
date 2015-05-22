#include "ffVideoStream.h"

ffVideoStream::ffVideoStream(QObject *parent)
    : ffStream(parent)
{
    m_MediaType = MediaType_Video;
}

ffVideoStream::ffVideoStream(void *avStream, QObject *parent)
    : ffStream(avStream, parent)
{
    m_MediaType = MediaType_Video;
}

QString ffVideoStream::TypeString()
{
    return QString(tr("Video"));
}

