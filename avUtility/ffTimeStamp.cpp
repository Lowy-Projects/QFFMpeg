#include "ffTimeStamp.h"
#include "ffRational.h"
#include "libavutil/mathematics.h"
#include "LowyLib.h"

ffTimeStamp::ffTimeStamp()
{
    setValue(AV_NOPTS_VALUE, ffRational());
}

ffTimeStamp::ffTimeStamp(qint64 TimeStamp, ffRational TimeBase)
{
    setValue(TimeStamp, TimeBase);
}

ffTimeStamp::ffTimeStamp(qint64 TimeStamp, double TimeBase)
{
    setValue(TimeStamp, TimeBase);
}

ffTimeStamp::~ffTimeStamp()
{

}

ffRational ffTimeStamp::TimeBase()
{
    return timeBase;
}

void ffTimeStamp::setValue(qint64 TimeStamp, ffRational TimeBase)
{
    AVRational rat;

    TimeBase.value(&rat);
    timeBase.setValue(&rat);     // .setValue(TimeBase.num, TimeBase.den);
    t = TimeStamp;
}

void ffTimeStamp::setValue(qint64 TimeStamp, double TimeBase)
{
    timeBase.setValue(TimeBase);
    t = TimeStamp;
}

void ffTimeStamp::add(qint64 TimeStamp, ffRational TimeBase)
{
    AVRational aRat, bRat;

    timeBase.value(&aRat);
    TimeBase.value(&bRat);

    if (timeBase != TimeBase)
        TimeStamp = av_rescale_q(TimeStamp, bRat, aRat);        // Időbélyeg átalakítás az osztály által használt időbázisra.

    t += TimeStamp;
}

void ffTimeStamp::addFrameNum(int frames, ffRational FrameRate)
{
    double         frameLength;

    frameLength = ((1 / timeBase.value()) / FrameRate.value()) * frames;

    t += frameLength;
}

void ffTimeStamp::sub(qint64 TimeStamp, ffRational TimeBase)
{
    AVRational aRat, bRat;

    timeBase.value(&aRat);
    TimeBase.value(&bRat);

    if (timeBase != TimeBase)
        TimeStamp = av_rescale_q(TimeStamp, bRat, aRat);        // Időbélyeg átalakítás az osztály által használt időbázisra.

    t -= TimeStamp;
}

void ffTimeStamp::subFrameNum(int frames, ffRational FrameRate)
{
    double         frameLength;

    frameLength = ((1 / timeBase.value()) / FrameRate.value()) * frames;

    t -= frameLength;
}

bool ffTimeStamp::isValid()
{
    if (t == AV_NOPTS_VALUE)
        return false;

    return true;
}

void ffTimeStamp::rescaleTimeStamp(ffRational TimeBase)
{
    AVRational oldR, newR;

    timeBase.value(&oldR);
    TimeBase.value(&newR);

    t = av_rescale_q(t, oldR, newR);                    // ffMpeg funkció, az átszámításra.
    timeBase.setValue(&newR);
}

double ffTimeStamp::toSec()
{
    return timeBase.value() * t;
}

QString ffTimeStamp::toStringSec()
{
    if (!isValid())
        return QObject::tr("Ismeretlen");

    return QString("%0").arg(toSec());
}

QString ffTimeStamp::toString(bool visibleMSec)
{
    double  dsec = timeBase.value() * t;
    QString s;

    if (!isValid())
        return QObject::tr("Ismeretlen");

    if (dsec < 0)
    {
        dsec *= -1;
        s = "- ";
    }

    qint64 sec  = dsec;
    int    msec = (dsec - sec) * 1000;
    int    min  = sec / 60; sec %= 60;
    int    hour = min / 60; min %= 60;

    s.append( QString("%1:%2:%3").arg(hour, 2, 10, QChar('0')).arg(min, 2, 10, QChar('0')).arg(sec, 2, 10, QChar('0')) );
    if (visibleMSec)
        s.append(QString(".%1").arg(msec, 3, 10, QChar('0')));

    return s;
}

/*
bool ffTimeStamp::operator =(ffTimeStamp a)
{
    setValue(a.Value(), a.TimeBase());

    return true;
}
*/
bool ffTimeStamp::operator =(ffTimeStamp &a)
{
    setValue(a.Value(), a.TimeBase());

    return true;
}

bool ffTimeStamp::operator ==(ffTimeStamp &a)
{
    double secLeft   = timeBase.value() * t;
    double secRight  = a.TimeBase().value() * a.Value();

    if (secLeft == secRight)
        return true;

    return false;
}

bool ffTimeStamp::operator !=(ffTimeStamp &a)
{
    double secLeft   = timeBase.value() * t;
    double secRight  = a.TimeBase().value() * a.Value();

    if (secLeft == secRight)
        return false;

    return true;
}
