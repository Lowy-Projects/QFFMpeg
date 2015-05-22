#ifndef FFRATIONAL_H
#define FFRATIONAL_H

#include "qffmpeg_global.h"

class QFFMPEGSHARED_EXPORT ffRational
{
public:
    ffRational();
    ffRational(void *av_Rational);
    ffRational(int Num, int Den);
    ffRational(double rat);

    ~ffRational();

    double  value() const;
    float   valueFloat() const;
    void    value(void *av_Rational);

    void    setValue(void *av_Rational);
    void    setValue(int Num, int Den);
    void    setValue(double rat);

    bool    isValid();
    bool    mathEqual(ffRational &a) const;

    friend bool    operator == (ffRational &a, ffRational &b);
    friend bool    operator != (ffRational &a, ffRational &b);

private:
    int m_num;
    int m_den;
};

#endif // FFRATIONAL_H
