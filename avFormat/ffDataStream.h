#ifndef FFDATASTREAM_H
#define FFDATASTREAM_H

#include <QObject>
#include "ffStream.h"

class ffDataStream : public ffStream
{
public:
    ffDataStream(QObject *parent);
    ffDataStream(void *avStream, QObject *parent);

    QString TypeString() Q_DECL_OVERRIDE;
};

#endif // FFDATASTREAM_H
