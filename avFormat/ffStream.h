#ifndef FFSTREAM_H
#define FFSTREAM_H

#include "qffmpeg_global.h"
#include "avUtility/avUtility"
#include <LowyLib.h>
#include <QObject>

class QFFMPEGSHARED_EXPORT ffStream : public QObject
{
    Q_OBJECT
public:
    typedef enum MediaType {
        MediaType_Unknown = -1,
        MediaType_Video,
        MediaType_Audio,
        MediaType_Data,
        MediaType_Subtitle,
        MediaType_Attachment
    } MediaType;

public:
    explicit ffStream(QObject *parent = 0);
    explicit ffStream(void* avStream, QObject *parent = 0);
    ~ffStream();

    // Általános adatok
    int                               Index();
    int                               Id();
    void                            *Codec();
    QString                      CodecName();
    int                               Profile();
    int                               Level();
    ffRational                   BitRate();
    ffTimeStamp             Start();
    ffTimeStamp             Duration();

    ffDictionaryModel  *Metadata();
    ffRational                   TimeBase();
    MediaType                Type() {return m_MediaType;}
    virtual QString         TypeString();

    bool                            Open();
    void                            Close();
    virtual bool                Read();
    virtual bool                Decode();

    bool                            isOpen();

    // Video stream adatok
    ffRational                   FrameRate();
    QSize                          FrameSize();
    ffRational                   PictureRatio();
    ffRational                   PixelRatio();

signals:

public slots:

protected:
    void             *m_avStream;    // FFMpeg stream információk
    MediaType  m_MediaType;  // Media tipusa
    lError          m_Error;

private:
    void             setting();
};

#endif // FFSTREAM_H
