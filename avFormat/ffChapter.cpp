#include "ffChapter.h"

ffChapter::ffChapter(QObject *parent) : QObject(parent)
{
    m_ObjectId = (qint64)(this);
    m_Metadata.setParent(this);

    m_ChapterId = m_ObjectId;
    m_Start.setValue(0);
    m_End.setValue(10 * ffRational().value());
}

ffChapter::ffChapter(void *av_Chapter, QObject *parent): QObject(parent)
{
    AVChapter *chapter = (AVChapter*)av_Chapter;

    m_ObjectId = (qint64)(this);
    m_Metadata.setParent(this);

    if (!chapter)
        return;

    m_ChapterId = chapter->id;
    m_Start.setValue(chapter->start, ffRational(&chapter->time_base));
    m_End.setValue(chapter->end, ffRational(&chapter->time_base));
    m_Metadata.set_ffMpegValue(chapter->metadata);
}

ffChapter::~ffChapter()
{

}

ffTimeStamp ffChapter::Length()
{
    ffTimeStamp length = m_End;

    if (!m_Start.isValid() || !m_End.isValid())
        return ffTimeStamp();

    length.sub(m_Start);

    return length;
}

QString ffChapter::Value()
{
    return m_Metadata.Value("title");
}

void ffChapter::setStart(ffTimeStamp Start)
{
    m_Start = Start;
    m_Start.rescaleTimeStamp();
}

void ffChapter::setStart(qint64 Start, ffRational TimeBase)
{
    setStart(ffTimeStamp(Start, TimeBase));
}

void ffChapter::setEnd(ffTimeStamp End)
{
    m_End = End;
    m_End.rescaleTimeStamp();
}

void ffChapter::setEnd(qint64 End, ffRational TimeBase)
{
    setEnd(ffTimeStamp(End, TimeBase));
}

void ffChapter::setLength(ffTimeStamp Length)
{
    m_End = m_Start;
    m_End.add(Length);
}

void ffChapter::setLength(qint64 Length, ffRational TimeBase)
{
    m_End = m_Start;
    m_End.add(Length, TimeBase);
}

void ffChapter::setValue(QString title)
{
    m_Metadata.setValue("title", title);
}

QString ffChapter::toString()
{
    return QString("Chapter %0: %1 - %2 ''").arg(m_ChapterId).arg(m_Start.toString()).arg(m_End.toString()).arg(Value());
}

