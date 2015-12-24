#ifndef FFDICTIONARY_H
#define FFDICTIONARY_H

#include "qffmpeg_global.h"

#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QList>
#include "ffdictionaryitem.h"

#include <QObject>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QList>
#include <QPair>
#include <LowyLib/LowyLib.h>
#include "ffdictionaryitem.h"

class ffDictionaryDelegate;

class QFFMPEGSHARED_EXPORT ffDictionaryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ffDictionaryModel(QObject *parent = 0);
    explicit ffDictionaryModel(void * FFMpeg_Dict, QObject *parent = 0);
    ~ffDictionaryModel();

    void     append(QString key, QString value);
    void     clear();
    int      count() {return m_Items.count();}
    QString  value(QString key, bool isSensitive = true);

//    QStandardItemModel*     Model() {return &m_Dic;}

    ffDictionaryDelegate *   delegate() {return m_Delegate;}
    QList<ffDictionaryItem*> List();
    void                    setValue(QString key, QString value, bool isSensitive = true);
//    void                    setFromList(QList<QPair<QString, QString> >list);
//    void                    addFromList(QList<QPair<QString, QString> > list);

    // Model tagfügvények
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool     setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;


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
    void dictionaryValueChanged(ffDictionaryItem *item);

public slots:

private:
//    bool                        InsertRow(QString s1, QString s2);
//    QPair<QString, QString>     valuePair(int num);
//    QStandardItem               *valueItem(QString key,  bool isSensitive = true);

    QString                     m_KeyName;
    QString                     m_ValueName;
    QList<ffDictionaryItem *>   m_Items;
    ffDictionaryDelegate*       m_Delegate;
    lError                      m_Error;
};

//
/// Delegát osztály a szerkesztéshez
//

class ffDictionaryDelegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    ffDictionaryDelegate(QObject * parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,
                          const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

};

#endif // FFDICTIONARY_H
