#include "ffChapterModel.h"
#include <QLineEdit>

ffChapterModel::ffChapterModel(QObject *parent): QAbstractTableModel(parent)
{
    m_Delegate = new ffChapterDelegate(this);
}

ffChapterModel::~ffChapterModel()
{
    if (m_Delegate)
        delete m_Delegate;
}

void ffChapterModel::appendChapter(ffChapter *chapter)
{
    beginInsertRows(QModelIndex(), m_List.count(), m_List.count());
    m_List.append(chapter);
    endInsertRows();
}

void ffChapterModel::append_ffMpegAvChapter(void **av_Chapter, int count)
{
    beginInsertRows(QModelIndex(), m_List.count(), m_List.count() + count - 1);
    for(int i = 0; i < count; i++)
        m_List.append(new ffChapter(av_Chapter[i], this));
    endInsertRows();

}

void ffChapterModel::insertChapter(int num, ffChapter *chapter)
{
    if (chapter == NULL)
        return;

    if (num >= m_List.count())
        num = m_List.count();

    if (num < 0)
        num = 0;

    beginInsertRows(QModelIndex(), num, num);
    m_List.insert(num, chapter);
    endInsertRows();
}

void ffChapterModel::insert_ffMpegAvChapter(void **av_Chapter, int first, int count)
{
    if (first >= m_List.count())
        first = m_List.count();

    if (first < 0)
        first = 0;

    beginInsertRows(QModelIndex(), first, first + count - 1);
    for(int i = 0; i < count; i++)
        m_List.insert(first++, new ffChapter(av_Chapter[i], this));
    endInsertRows();
}

void ffChapterModel::changeChapterStart(int num, ffTimeStamp start)
{
    ffChapter * chapter = m_List[num];
    QModelIndex chIndex = index(num, 0);

    chapter->setStart(start);
    setData(chIndex, QVariant(), Qt::EditRole);
}

void ffChapterModel::changeChapterStart(ffChapter *chapter, ffTimeStamp start)
{
    int                    num       = chapterNum(chapter);
    QModelIndex chIndex = index(num, 0);

    chapter->setStart(start);
    setData(chIndex, QVariant(), Qt::EditRole);
}

void ffChapterModel::changeChapterEnd(int num, ffTimeStamp end)
{
    ffChapter * chapter = m_List[num];
    QModelIndex chIndex = index(num, 1);

    chapter->setEnd(end);
    setData(chIndex, QVariant(), Qt::EditRole);
}

void ffChapterModel::changeChapterEnd(ffChapter *chapter, ffTimeStamp end)
{
    int                    num       = chapterNum(chapter);
    QModelIndex chIndex = index(num, 1);

    chapter->setEnd(end);
    setData(chIndex, QVariant(), Qt::EditRole);
}

ffChapter *ffChapterModel::chapter(int num)
{
    if ((num >= m_List.count()) || (num < 0))
        return NULL;

    return m_List[num];
}

bool ffChapterModel::chapters(void **av_Chapters)
{
    AVChapter  *chapters;
    ffChapter    *chapter;

    *av_Chapters = NULL;
    chapters = (AVChapter*) av_malloc(m_List.count() * sizeof(AVChapter));
    if (!chapters)
        return false;

    *av_Chapters = chapters;
    for(int i = 0; i < m_List.count(); i++)
    {
        chapter = m_List[i];
        chapters[i].start = chapter->Start().Value();
        chapters[i].end   = chapter->End().Value();
        chapters[i].id      = chapter->ChapterNum();

        chapter->Start().TimeBase().ffMpegValue(&chapters[i].time_base);
        chapter->MetadataModel()->ffMpegValue((void**)& chapters[i].metadata);
    }

    return true;
}

///
/// Model tabfügvények, melyek a model-ként való működéshez kellenek.
///
// Sorok száma
int ffChapterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_List.count();
}

// Oszlopok száma
int ffChapterModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 3;
}

// Adatok lekérdezése
QVariant ffChapterModel::data(const QModelIndex &index, int role) const
{
    int row = index.row(), column = index.column();

    switch (role) {
    case Qt::DisplayRole:                                           // Cella megjelenítendő szövege
    case Qt::EditRole:                                              // Cella szerkesztéshez megjelenítendő szöveg
        return chapterData(row, column);

    case Qt::TextAlignmentRole:                                     // Cella tartalmának igazítása
        int alignment = Qt::AlignVCenter;

        if (column != 2)
            alignment |= Qt::AlignHCenter;
        return alignment;

    }
    return QVariant();
}

// Adatok beírása
bool ffChapterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    ffChapter* chapter = m_List[index.row()];
    if (index.column() < 2)
        return true;

    if (role == Qt::EditRole)
    {
        chapter->setValue(value.toString());
        emit chapterNameChanged(chapter);

        return true;
    }

    return false;
}

// Fejléc adatok
QVariant ffChapterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        switch(role)
        {
            case Qt::DisplayRole:

                switch (section)
                {
                case 0:
                    return tr("Eleje");
                case 1:
                    return tr("Vége");
                case 2:
                    return tr("Címe");
                }
        }
    }
    else
    {
        if (role == Qt::DisplayRole)
            return section + 1;
    }

    return QVariant();
}

// Cella tulajdonságai.
Qt::ItemFlags ffChapterModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flag = QAbstractTableModel::flags(index);

    if (index.column() == 2)
        flag |= Qt::ItemIsEditable;

    return flag;
}

bool ffChapterModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);

    for(int i = 0; i < count; i++)
        m_List.removeAt(row);

    endRemoveRows();
    return true;
}

// Egy fejezet adatainak lekérdezése.
QString ffChapterModel::chapterData(int row, int column) const
{
    switch (column) {
    case 0:
        return m_List[row]->Start().toString(true);
        break;

    case 1:
        return m_List[row]->End().toString(true);
        break;

    case 2:
        return m_List[row]->Value();
        break;

    default:
        return QString();
        break;
    }
}

int ffChapterModel::chapterNum(ffChapter *chapter)
{
    int i = 0;

    foreach (ffChapter* item, m_List) {
        if (item->ChapterNum() == chapter->ChapterNum())
            return i;
        i++;
    }

    return -1;
}

//////////////////////////////////
/// Delegát osztály megvalósítása
//////////////////////////////////
ffChapterDelegate::ffChapterDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *ffChapterDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    Q_UNUSED(option);

    QLineEdit* editor = NULL;
    QPalette   palette;

    if (index.column() == 2)
    {
        editor = new QLineEdit(parent);
        palette = editor->palette();
        palette.setColor(QPalette::Base,option.palette.color(QPalette::Highlight));
        palette.setColor(QPalette::Text, option.palette.color(QPalette::HighlightedText));
        editor->setPalette(palette);
        editor->setAutoFillBackground(true);
    }

    return editor;
}

void ffChapterDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit* lineEditor = static_cast<QLineEdit*>(editor);

    lineEditor->setText(value);
}

void ffChapterDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit* lineEditor = static_cast<QLineEdit*>(editor);

    model->setData(index, lineEditor->text(), Qt::EditRole);
}

void ffChapterDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    editor->setGeometry(option.rect);
}

