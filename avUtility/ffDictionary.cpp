#include <QObject>
#include <QDebug>
#include<QLineEdit>
#include "ffDictionary.h"

extern "C" {
    typedef struct AVDictionary{
        int                 count;
        AVDictionaryEntry * elems;

    } AVDictionary;
}

ffDictionaryModel::ffDictionaryModel(QObject *parent) : QAbstractTableModel(parent)
{
    m_Error.clear();
    m_Delegate = new ffDictionaryDelegate(this);
    if (!m_Delegate)
        m_Error.setError(Error_NotEnoughMemory);
}

ffDictionaryModel::ffDictionaryModel(void *FFMpeg_Dict, QObject *parent) : QAbstractTableModel(parent)
{
    m_Error.clear();
    m_Delegate = new ffDictionaryDelegate(); //this);
    if (!m_Delegate)
    {
        m_Error.setError(Error_NotEnoughMemory);
        return;
    }

    set_ffMpegValue(FFMpeg_Dict);
}

ffDictionaryModel::~ffDictionaryModel()
{
    if (m_Delegate)
        delete m_Delegate;

    m_Items.clear();
}

void ffDictionaryModel::append(QString key, QString value)
{
    ffDictionaryItem * item;

    m_Error.clear();
    item = new ffDictionaryItem(key, value, this);
    if (!item)
    {
        m_Error.setError(Error_NotEnoughMemory);
        return;
    }

    beginInsertRows(QModelIndex(), m_Items.count(), m_Items.count());
    m_Items.append(item);
    endInsertRows();
//    InsertRow(key, value);
}

QString ffDictionaryModel::value(QString key, bool isSensitive)
{
    ffDictionaryItem * item;

    m_Error.clear();
    Qt::CaseSensitivity sense = isSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;

    for (int i = 0; i < m_Items.count(); i++)
    {
        item = m_Items[i];

        if (item->Key().compare(key, sense) == 0)
            return item->Value();
    }

    return QString();
}

void ffDictionaryModel::ffMpegValue(void **FFMpeg_Dict)
{
    ffDictionaryItem *item;

    m_Error.clear();

    for(int i = 0; i < m_Items.count(); i++)
    {
        item = m_Items[i];
        item->ffMpegValue(FFMpeg_Dict);

        if (item->isError())
        {
            m_Error.copyFrom(item->Error());
            break;
        }
    }
}

QList<ffDictionaryItem *> ffDictionaryModel::List()
{
    return m_Items;
}

void ffDictionaryModel::set_ffMpegValue(void *FFMpeg_Dict)
{
    ffDictionaryItem   *item;
    AVDictionary       *ffDic = (AVDictionary*)FFMpeg_Dict;
    AVDictionaryEntry  *entrys = NULL;
    int                 i = 0, count = 0;

    m_Error.clear();

    // Régi elemek törlése, ha van.
    if (m_Items.size())
    {
        beginRemoveRows(QModelIndex(), 0, m_Items.size() - 1);
        for(int i = 0; i < m_Items.size(); i++)
        {
            item = m_Items[0];
            m_Items.removeAt(0);
            delete item;
        }
        endRemoveRows();
    }

    // Új elemek felvétele
    if (ffDic == NULL)
        return;

    entrys = ffDic->elems;
    count  = ffDic->count;

    beginInsertRows(QModelIndex(), 0, count-1);
    for(i = 0; i < count; i++)
    {
        item = new ffDictionaryItem(entrys[i].key, entrys[i].value, this);
        if ( !item || item->isError())
            break;

        m_Items.append(item);
    }
    endInsertRows();

    if (i != count)
    {
        if (item)
            m_Error.copyFrom(item->Error());
        else
            m_Error.setError(Error_NotEnoughMemory);
    }
}

void ffDictionaryModel::setValue(QString key, QString value, bool isSensitive)
{
    ffDictionaryItem * item = NULL;
    Qt::CaseSensitivity sens = (isSensitive == true) ? Qt::CaseSensitive : Qt::CaseInsensitive;

    int i;

    m_Error.clear();

    for (i = 0; i < m_Items.size(); i++)
        if (m_Items[i]->Key().compare(key ,sens) == 0)
            item = m_Items[i];

    if (item)
    {
        item->setValue(value);
    }
    else
    {
        item = new ffDictionaryItem(key, value, this);
        beginInsertRows(QModelIndex(), m_Items.size(), m_Items.size());
        m_Items.append(item);
        endInsertRows();
    }
}

/*
void ffDictionaryModel::setFromList(QList<QPair<QString, QString> > list)
{
    m_Dic.clear();
    addFromList(list);
}

void ffDictionaryModel::addFromList(QList<QPair<QString, QString> > list)
{
    int i;

    for(i = 0; i < list.count(); i++)
        InsertRow(list[i].first, list[i].second);
}
*/

// Modell kapcsolattartó függvények

int ffDictionaryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_Items.count();
}

int ffDictionaryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

QVariant ffDictionaryModel::data(const QModelIndex &index, int role) const
{
    QString str;
    int row = index.row(), column = index.column();

    switch (role) {
        case Qt::DisplayRole:                                           // Cella megjelenítendő szövege
        case Qt::EditRole:                                              // Cella szerkesztéshez megjelenítendő szöveg
            if (column == 0)
                return m_Items[row]->Key();
            if (column == 1)
                return m_Items[row]->Value();
            break;

    case Qt::TextAlignmentRole:
        return (Qt::AlignLeft + Qt::AlignHCenter);

    }
    return QVariant();
}

bool ffDictionaryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() == 0)
        return true;

    if (role == Qt::EditRole)
    {
        m_Items[index.row()]->setValue(value.toString());
        emit dictionaryValueChanged(m_Items[index.row()]);

        return true;
    }
    return false;
}

QVariant ffDictionaryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        switch(role)
        {
            case Qt::DisplayRole:

                switch (section)
                {
                case 0:
                    return m_KeyName;
                case 1:
                    return m_ValueName;
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

Qt::ItemFlags ffDictionaryModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flag = QAbstractTableModel::flags(index);

    if (index.column() == 1)
        flag |= Qt::ItemIsEditable;

    return flag;
}

bool ffDictionaryModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);

    for(int i = 0; i < count; i++)
        m_Items.removeAt(row);

    endRemoveRows();
    return true;
}


QString ffDictionaryModel::operator[](QString key)
{
    return value(key);
}

/*
bool ffDictionaryModel::InsertRow(QString s1, QString s2)
{
    QList<QStandardItem *> row;

    m_Error.clear();

    row.append(new QStandardItem(s1));
    row.append(new QStandardItem(s2));

    if (row[1] == NULL)
        delete row[0];

    if (row[0])
    {
        m_Dic.appendRow(row);
        return true;
    }

    m_Error.setError(Error_NotEnoughMemory);
    return false;
}

QPair<QString, QString> ffDictionaryModel::valuePair(int num)
{
    QPair<QString, QString> row;

    m_Error.clear();
    if (num > -1 && num < m_Dic.rowCount())
    {
        row.first  = m_Dic.item(num, 0)->data(0).toString();
        row.second = m_Dic.item(num, 1)->data(0).toString();
    }

    return row;
}

QStandardItem *ffDictionaryModel::valueItem(QString key, bool isSensitive)
{
    QStandardItem* item = NULL;
    Qt::CaseSensitivity sense = isSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
    int i;

    for(i = 0; i < m_Dic.rowCount(); i++)
    {
        if (m_Dic.item(i, 0)->data(0).toString().compare(key, sense) == 0)
        {
            item = m_Dic.item(i, 1);
            break;
        }
    }

    return item;
}

*/


//////////////////////////////////
/// Delegát osztály megvalósítása
//////////////////////////////////
ffDictionaryDelegate::ffDictionaryDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *ffDictionaryDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit* editor = NULL;
    QPalette   palette;

    if (index.column() == 1)        // Érték módosítása
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

void ffDictionaryDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit* lineEditor = static_cast<QLineEdit*>(editor);

    lineEditor->setText(value);
}

void ffDictionaryDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit* lineEditor = static_cast<QLineEdit*>(editor);

    model->setData(index, lineEditor->text(), Qt::EditRole);
}

void ffDictionaryDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    editor->setGeometry(option.rect);
}

