#include "ffDataStream.h"

ffDataStream::ffDataStream(QObject *parent)
    : ffStream(parent)
{
    m_MediaType = MediaType_Data;
}

ffDataStream::ffDataStream(void *avStream, QObject *parent)
    : ffStream(avStream, parent)
{
    m_MediaType = MediaType_Data;
}

QString ffDataStream::TypeString()
{
    return tr("Adat");
}

