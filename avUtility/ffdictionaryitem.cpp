#include "ffdictionaryitem.h"
#include <QDebug>
#include "qffmpeg_global.h"

extern "C" {
    typedef struct AVDictionary{
        int                 count;
        AVDictionaryEntry * elems;

    } AVDictionary;
}

ffDictionaryItem::ffDictionaryItem(QObject *parent)
    : QObject(parent)
{
    m_Error.clear();
    m_key.clear();
    m_value.clear();
}

ffDictionaryItem::ffDictionaryItem(QString key, QString value, QObject *parent)
    : QObject(parent)
{
    m_Error.clear();
    m_key = key;
    m_value = value;
}

ffDictionaryItem::ffDictionaryItem(void *ffMpegDict, QObject *parent)
    : QObject(parent)
{
    set_ffMpegValue(ffMpegDict);
}

bool ffDictionaryItem::isOK()
{
    return !m_key.isEmpty();
}

bool ffDictionaryItem::isError()
{
    return m_Error.isError();
}

lError *ffDictionaryItem::Error()
{
    return &m_Error;
}

void ffDictionaryItem::setValue(QString value)
{
    m_value = value;
}

void ffDictionaryItem::setValue(QString key, QString value)
{
    m_key = key;
    m_value = value;
}

void ffDictionaryItem::set_ffMpegValue(void *DictEntry)
{
    AVDictionaryEntry * entry = (AVDictionaryEntry*)DictEntry;

    m_Error.clear();
    m_key = entry->key;
    m_value = entry->value;

}

void ffDictionaryItem::ffMpegValue(void **Dict)
{
    AVDictionary **dict = (AVDictionary**)Dict;

    m_Error.clear();
    if (av_dict_set(dict, m_key.toUtf8(), m_value.toUtf8(), 0) < 0)
    {
        m_Error.setError(Error_NotEnoughMemory);
        qDebug() << "ffMpeg dictionary error. Out of memory.";
    }

}

