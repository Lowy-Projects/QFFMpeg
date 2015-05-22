#ifndef FFTIMESTAMP_H
#define FFTIMESTAMP_H

#include "qffmpeg_global.h"
#include "ffRational.h"
#include <QString>

class QFFMPEGSHARED_EXPORT ffTimeStamp
{
public:
    ffTimeStamp();
    ffTimeStamp(qint64 TimeStamp, ffRational TimeBase = ffRational());
    ffTimeStamp(qint64 TimeStamp, double TimeBase);
    ~ffTimeStamp();

    qint64      Value() {return t;}
    ffRational  TimeBase();
    double      TimeBaseDouble() {return timeBase.value();}

    void        setValue(qint64 TimeStamp, ffRational TimeBase = ffRational());
    void        setValue(qint64 TimeStamp, double TimeBase);

    void        add(ffTimeStamp& a) {add(a.Value(), a.TimeBase());}
    void        add(qint64 TimeStamp, ffRational TimeBase = ffRational());
    void        addFrameNum(int frames, ffRational FrameRate);
    void        sub(ffTimeStamp& a) {sub(a.Value(), a.TimeBase());}
    void        sub(qint64 TimeStamp, ffRational TimeBase = ffRational());
    void        subFrameNum(int frames, ffRational FrameRate);

    bool        isValid();

    void        rescaleTimeStamp(ffRational TimeBase = ffRational());

    double      toSec();
    QString     toStringSec();
    QString     toString(bool visibleMSec = false);

    bool operator = (ffTimeStamp& a);
//    bool operator = (ffTimeStamp a);
    bool operator ==(ffTimeStamp& a);
    bool operator !=(ffTimeStamp& a);

private:
    ffRational  timeBase;
    qint64      t;
};

#endif // FFTIMESTAMP_H
