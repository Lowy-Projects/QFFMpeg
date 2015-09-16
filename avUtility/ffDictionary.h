#ifndef FFDICTIONARY_H
#define FFDICTIONARY_H

#include "qffmpeg_global.h"
#include <QObject>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QList>
#include <QPair>
#include <LowyLib/LowyLib.h>
#include "ffdictionaryitem.h"

class QFFMPEGSHARED_EXPORT ffDictionaryModel : public QObject
{
    Q_OBJECT
public:
    explicit ffDictionaryModel(QObject *parent = 0);
    explicit ffDictionaryModel(void * FFMpeg_Dict, QObject *parent = 0);
    ~ffDictionaryModel();

    void     Add(QString key, QString value);
    void     Clear();
    int      Count() {return m_Dic.rowCount();}
    QString  Value(QString key, bool isSensitive = true);

    QStandardItemModel*     Model() {return &m_Dic;}

    QList<QPair<QString, QString> > List();
    void                    setValue(QString key, QString value);
    void                    setFromList(QList<QPair<QString, QString> >list);
    void                    addFromList(QList<QPair<QString, QString> > list);

/***********************************
 * ffMpeg kapcsolattartó fügvények.
 ***********************************/
    void     ffMpegValue(void  **FFMpeg_Dict);
    void     set_ffMpegValue(void * FFMpeg_Dict);

/***********************************
* Operátorok
***********************************/

    QString operator[] (QString key);

signals:

public slots:

private:
    bool                        InsertRow(QString s1, QString s2);
    QPair<QString, QString>     valuePair(int num);
    QStandardItem               *valueItem(QString key,  bool isSensitive = true);

    QStandardItemModel          m_Dic;
    lError                      m_Error;
};

#endif // FFDICTIONARY_H
