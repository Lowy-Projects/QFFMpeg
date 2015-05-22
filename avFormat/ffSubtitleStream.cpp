#include "ffSubtitleStream.h"

ffSubtitleStream::ffSubtitleStream(QObject *parent)
    : ffStream(parent)
{
    m_MediaType = MediaType_Subtitle;
}

ffSubtitleStream::ffSubtitleStream(void *avStream, QObject *parent)
    : ffStream(avStream, parent)
{
    m_MediaType = MediaType_Subtitle;
}

QString ffSubtitleStream::TypeString()
{
    return QString(tr("Felirat"));
}

