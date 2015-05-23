#ifndef FFSAMPLEFORMAT_H
#define FFSAMPLEFORMAT_H

#include <QString>

class ffSampleFormat
{
public:
    ffSampleFormat();
    ffSampleFormat(int ffMpeg_SampleFormat);

    int         Bits()      {return m_Bits;}
    bool      Planar() {return m_Planar;}
    bool      Float()    {return m_Float;}

    void      setBits(int bits)                {m_Bits = bits;}
    void      setPlanar(bool isPlanar) {m_Planar = isPlanar;}
    void      setFloat(bool isFloat)      {m_Float = isFloat;}
    void      setFfMpegSampleFmt(int SampleFmt);

    int           toFfMpegSampleFmt();
    QString  toString(bool showPlanar = false);

    static int           Bits(int ffMpeg_SampleFormat);
    static bool         Planar(int ffMpeg_SampleFormat);
    static bool         Float(int ffMpeg_SampleFormat);
    static QString  toString(int ffMpeg_SampleFormat, bool showPlanar = false);

    bool    operator ==(ffSampleFormat& f);
    bool    operator != (ffSampleFormat& f);

private:
    int     m_Bits;                 // bitmélység
    bool  m_Planar;            // planar (sík) tárolás
    bool  m_Float;              //  lebegőpontos tárolás
};

#endif // FFSAMPLEFORMAT_H
