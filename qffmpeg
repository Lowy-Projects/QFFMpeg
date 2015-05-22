#ifndef QFFMPEG_H
#define QFFMPEG_H

#include "qffmpeg_global.h"
#include <QObject>
#include <QWidget>
#include "avFormat/avFormat"


class QFFMPEGSHARED_EXPORT QFfmpeg: public QObject
{
    Q_OBJECT

public:
    explicit    QFfmpeg(QObject *parent = 0);
    bool         Init(QWidget *logWin = 0);
    ffDemuxer  *OpenMedia(QString fileName);
};


#endif // QFFMPEG_H
