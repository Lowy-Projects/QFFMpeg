#include <QObject>
#include <QDebug>
#include "ffDictionary.h"


ffDictionaryModel::ffDictionaryModel(QObject *parent) : QObject(parent)
{
    m_Error.clear();
    m_Dic.setParent(this);
}

ffDictionaryModel::ffDictionaryModel(void *FFMpeg_Dict, QObject *parent) : QObject(parent)
{
    set_ffMpegValue(FFMpeg_Dict);
}

ffDictionaryModel::~ffDictionaryModel()
{
}

void ffDictionaryModel::Add(QString key, QString value)
{
    InsertRow(key, value);
}

QString ffDictionaryModel::Value(QString key, bool isSensitive)
{
    QPair<QString, QString> row;

    Qt::CaseSensitivity sense = isSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;

    for (int i = 0; i < m_Dic.rowCount(); i++)
    {
        row = valuePair(i);

        if (row.first.compare(key, sense) == 0)
            return row.second;
    }

    return QString();
}

void ffDictionaryModel::ffMpegValue(void **FFMpeg_Dict)
{
    QPair<QString, QString> item;
    AVDictionary                        **dict = (AVDictionary**)FFMpeg_Dict;

    *dict = NULL;
    for(int i = 0; i < m_Dic.rowCount(); i++)
    {
        item = valuePair(i);
        if (av_dict_set(dict, item.first.toUtf8(), item.second.toUtf8(), 0) < 0)
            qDebug() << "ffDictionary::Value(**ffMpeg_Dict) error: av_dict_set error.";
    }
}

QList<QPair<QString, QString> > ffDictionaryModel::List()
{
    QList<QPair<QString, QString> > list;

    for(int i = 0; i < m_Dic.rowCount(); i++)
        list.append(valuePair(i));

    return list;
}

void ffDictionaryModel::set_ffMpegValue(void *FFMpeg_Dict)
{
    AVDictionary       *ffDic = (AVDictionary*)FFMpeg_Dict;
    AVDictionaryEntry  *entrys = ffDic->elems;
    int                 i, count = ffDic->count;

    for(i = 0; i < count; i++)
        InsertRow(entrys[i].key, entrys[i].value);
}

void ffDictionaryModel::setValue(QString key, QString value)
{
    QStandardItem* item = valueItem(key);

    if (item)
    {
        item->setData(value, 0);
    }
    else
    {
        Add(key, value);
    }
}

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


QString ffDictionaryModel::operator[](QString key)
{
    return Value(key);
}

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

