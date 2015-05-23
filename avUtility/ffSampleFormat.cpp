#include "ffSampleFormat.h"
#include "ffmpeg_headers.h"

#include <QObject>

typedef struct SampleFmtInfo {
    AVSampleFormat  sFmt;
    int                            sBits;
    bool                         sPlanar;
    float                        sFloat;
} SampleFmtInfo;

static const SampleFmtInfo Sample_Fmt_Info[] =
{
    { AV_SAMPLE_FMT_U8P,     8, true, false},
    { AV_SAMPLE_FMT_S16P, 16, true, false},
    { AV_SAMPLE_FMT_S32P, 32, true, false},
    { AV_SAMPLE_FMT_FLTP, 32, true, true},
    { AV_SAMPLE_FMT_DBLP, 64, true, true},
    { AV_SAMPLE_FMT_U8,        8, false, false},
    { AV_SAMPLE_FMT_S16,    16, false, false},
    { AV_SAMPLE_FMT_S32,    32, false, false},
    { AV_SAMPLE_FMT_FLT,    32, false, true},
    {AV_SAMPLE_FMT_DBL,    64, false, true},
};

static const int Sample_Fmt_Info_Size = sizeof(Sample_Fmt_Info) / sizeof(SampleFmtInfo);

ffSampleFormat::ffSampleFormat()
{
    m_Bits       = 16;
    m_Planar  = false;
}

ffSampleFormat::ffSampleFormat(int ffMpeg_SampleFormat)
{
    setFfMpegSampleFmt(ffMpeg_SampleFormat);
}

void ffSampleFormat::setFfMpegSampleFmt(int SampleFmt)
{
    int i = 0;
    m_Bits = -1;
    m_Planar = m_Float = false;

    while(i < Sample_Fmt_Info_Size)
    {
        if (SampleFmt == Sample_Fmt_Info[i].sFmt)
        {
            m_Bits         = Sample_Fmt_Info[i].sBits;
            m_Planar    = Sample_Fmt_Info[i].sPlanar;
            m_Float      = Sample_Fmt_Info[i].sFloat;
            return;
        }
        i++;
    }
}

int ffSampleFormat::toFfMpegSampleFmt()
{
    int i = 0;

    while(i < Sample_Fmt_Info_Size)
    {
        if ( m_Bits     == Sample_Fmt_Info[i].sBits &&
             m_Planar == Sample_Fmt_Info[i].sPlanar &&
             m_Float   == Sample_Fmt_Info[i].sFloat)
                return Sample_Fmt_Info[i].sFmt;

        i++;
    }

    return AV_SAMPLE_FMT_NONE;
}

QString ffSampleFormat::toString(bool showPlanar)
{
    QString t;

    if (m_Bits == -1)
        return QObject::tr("Ismeretlen");

    t = QString(QObject::tr("%1 bites")).arg(m_Bits);
    if (m_Float)
        t.append(QObject::tr(" lebegőpontos"));
    if (showPlanar && m_Planar)
        t.append(QObject::tr(" planar"));

    return t;
}

int ffSampleFormat::Bits(int ffMpeg_SampleFormat)
{
    ffSampleFormat f(ffMpeg_SampleFormat);

    return f.Bits();
}

bool ffSampleFormat::Planar(int ffMpeg_SampleFormat)
{
    ffSampleFormat f(ffMpeg_SampleFormat);

    return f.Planar();
}

bool ffSampleFormat::Float(int ffMpeg_SampleFormat)
{
    ffSampleFormat f(ffMpeg_SampleFormat);

    return f.Float();
}

QString ffSampleFormat::toString(int ffMpeg_SampleFormat, bool showPlanar)
{
    ffSampleFormat f(ffMpeg_SampleFormat);

    return f.toString(showPlanar);
}

bool ffSampleFormat::operator ==(ffSampleFormat &f)
{
    if (m_Bits == f.m_Bits &&
        m_Planar == f.m_Planar &&
        m_Float == f.m_Float)
            return true;

    return false;
}

bool ffSampleFormat::operator !=(ffSampleFormat &f)
{
    if (m_Bits != f.m_Bits ||
        m_Planar != f.m_Planar ||
        m_Float != f.m_Float)
            return true;

    return false;
}

