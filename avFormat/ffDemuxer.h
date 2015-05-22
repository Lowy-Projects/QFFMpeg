#ifndef FFDEMUXER_H
#define FFDEMUXER_H

#include <QObject>
#include <QList>
#include <QFileInfo>
#include <LowyLib.h>
#include "qffmpeg_global.h"

#include "ffStream.h"
#include "ffChapterModel.h"
#include "avUtility/ffDictionary.h"

class QFFMPEGSHARED_EXPORT ffDemuxer : public QObject
{
    Q_OBJECT
public:
    explicit ffDemuxer(QObject *parent = 0);
    ~ffDemuxer();

    // Megnyitás, lezárás, streamek
    bool                Open(QString fileName);
    void                Close();
    QList<ffStream*>    Streams() {return m_streams;}
    QList<ffStream *> VideoStreams();

    // Időadatok
    ffTimeStamp             Start();
    ffTimeStamp             Duration();
    int                               BitRate();

    // Infórmációk
    ffDictionaryModel  *Metadata();
    ffChapterModel     *Chapter();

    QFileInfo           SourceInfo() {return m_file;}
    QString             ContainerName();
    QString             ContainerLongName();
    lError             &Error() {return m_Error;}
signals:

public slots:
    void                DeleteStream(ffStream *stream);

protected:

private:
    bool            DetectStreams();    // Stream-ek létrehozása

    bool                m_Ok;
    QFileInfo       m_file;         // Input file
    void              *m_ctx;          // FFMpeg formátum leíró
    QList<ffStream*>m_streams;
    lError          m_Error;
};

#endif // FFDEMUXER_H
