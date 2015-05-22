#ifndef FFCHAPTERMODEL_H
#define FFCHAPTERMODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QList>
#include "qffmpeg_global.h"
#include "ffChapter.h"

class ffChapterDelegat;

class QFFMPEGSHARED_EXPORT ffChapterModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    ffChapterModel(QObject* parent = 0);
    ~ffChapterModel();

    // Fejezet (Chapter) tagfügvények
    void              appendChapter(ffChapter* chapter);
    void              appendAvChapter(void **av_Chapter, int count);
    void              insertChapter(int num, ffChapter* chapter);
    void              insertAvChapter(void **av_Chapter, int first, int count);
    void              changeChapterStart(int num, ffTimeStamp start);
    void              changeChapterStart(ffChapter *chapter, ffTimeStamp start);
    void              changeChapterEnd(int num, ffTimeStamp end);
    void              changeChapterEnd(ffChapter *chapter, ffTimeStamp end);
    bool              removeChapter(int num) {return removeRow(num);}
    bool              removeChapters(int num, int count) {return removeRows(num, count);}
    ffChapter   *chapter(int num);
    bool             chapters(void **av_Chapters);
    QList<ffChapter*>&chapters() {return m_List;}
    ffChapterDelegat *delegat() {return m_Delegat;}

    // Model tagfügvények
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool     setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    signals:
    void    chapterNameChanged(ffChapter* item);

private:
    QString chapterData(int row, int colum) const;
    int          chapterNum(ffChapter *chapter);

    QList<ffChapter*>   m_List;
    ffChapterDelegat*   m_Delegat;
};

///
/// Delegát osztály a fejezet nevének modosításához
///
class ffChapterDelegat : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ffChapterDelegat(QObject * parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,
                          const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // FFCHAPTERMODEL_H
