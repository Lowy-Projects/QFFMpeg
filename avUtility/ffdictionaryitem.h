#ifndef FFDICTIONARYITEM_H
#define FFDICTIONARYITEM_H

#include <QObject>
#include <LowyLib/LowyLib.h>

class ffDictionaryItem: public QObject
{
public:
    ffDictionaryItem(QObject* parent = NULL);
    ffDictionaryItem(QString key, QString value, QObject *parent = NULL);
    ffDictionaryItem(void *ffMpegDict, QObject *parent = NULL);

    bool isOK();
    bool isError();
    lError& Error();

    void setValue(QString key, QString value);
    void setValue(QString value);

    QString Key() {return m_key;}
    QString Value() {return m_value;}

    // ffMpeg kapcsolattartó fügvények
    void    set_ffMpegValue(void *DictEntry);
    void    ffMpegValue(void **Dict);

private:
    QString m_key;
    QString m_value;
    lError  m_Error;
};

#endif // FFDICTIONARYITEM_H
