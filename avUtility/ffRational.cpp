#include "ffRational.h"
#include <qffmpeg_global.h>

ffRational::ffRational()
{
    m_num = 1;
    m_den = AV_TIME_BASE;
}

ffRational::ffRational(void *av_Rational)
{
    setValue(av_Rational);
}

ffRational::ffRational(int Num, int Den)
{
    m_num = Num;
    m_den = Den;
}

ffRational::ffRational(double rat)
{
    setValue(rat);
}

ffRational::~ffRational()
{

}

double ffRational::value() const
{
    return m_num / (double)m_den;
}

float ffRational::valueFloat() const
{
    return m_num / (float)m_den;
}

void ffRational::value(void *av_Rational)
{
    AVRational *r = (AVRational*)av_Rational;

    if (!r)
        return;

    r->num = m_num;
    r->den = m_den;
}

void ffRational::setValue(void *av_Rational)
{
    AVRational *r = (AVRational*)av_Rational;

    m_num = r->num;
    m_den = r->den;
}

void ffRational::setValue(int Num, int Den)
{
    m_num = Num;
    m_den = Den;
}

void ffRational::setValue(double rat)
{
    AVRational r = av_d2q(rat, INT_MAX);

    m_num = r.num;
    m_den = r.den;
}

bool ffRational::isValid()
{
    return m_den != 0;
}

bool ffRational::mathEqual(ffRational &a) const
{
    return value() == a.value();
}

bool operator ==(ffRational &a, ffRational &b)
{
    if (a.m_den != b.m_den)
        return false;

    if (a.m_num != b.m_num)
        return false;

    return true;
}

bool operator !=(ffRational &a, ffRational &b)
{
    return !(a == b);
}
