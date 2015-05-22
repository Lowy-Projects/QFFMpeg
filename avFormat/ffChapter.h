#ifndef FFCHAPTER_H
#define FFCHAPTER_H

#include <QObject>
#include "qffmpeg_global.h"
#include "avUtility/ffTimeStamp.h"
#include "avUtility/ffDictionary.h"

class QFFMPEGSHARED_EXPORT ffChapter : public QObject
{
    Q_OBJECT
public:
    explicit ffChapter(QObject *parent = 0);
    explicit ffChapter(void *av_Chapter, QObject *parent = 0);
    ~ffChapter();

    int                 ChapterNum() {return m_ChapterId;}
    ffTimeStamp         Start() {return m_Start;}
    ffTimeStamp         End() { return m_End;}
    ffTimeStamp         Length();
    ffDictionaryModel*  MetadataModel() {return &m_Metadata;}
    QString             Value();

    void                setStart(ffTimeStamp Start);
    void                setStart(qint64 Start, ffRational TimeBase = ffRational());
    void                setEnd(ffTimeStamp End);
    void                setEnd(qint64 End, ffRational TimeBase = ffRational());
    void                setLength(ffTimeStamp Length);
    void                setLength(qint64 Length, ffRational TimeBase = ffRational());
    void                setValue(QString title);

    QString             toString();
    int                 objectId() {return m_ObjectId;}
signals:

public slots:
private:
    int                 m_ChapterId;
//    ffRational        m_TimeBase;
    ffTimeStamp         m_Start;
    ffTimeStamp         m_End;
    ffDictionaryModel   m_Metadata;

    qint64              m_ObjectId;
};

#endif // FFCHAPTER_H
