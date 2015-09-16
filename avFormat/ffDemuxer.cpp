#include "ffDemuxer.h"
#include "ffStream.h"
#include "ffAudioStream.h"
#include "ffVideoStream.h"
#include "ffSubtitleStream.h"
#include "ffDataStream.h"
#include "ffChapter.h"
#include "avUtility/ffDictionary.h"

#define m_fCtx  ((AVFormatContext*)m_ctx)
#define m_pfCtx ((AVFormatContext**)&m_ctx)

ffDemuxer::ffDemuxer(QObject *parent) : QObject(parent)
{
    m_Error.clear();
    m_ctx = NULL;
    m_Ok = false;
}

ffDemuxer::~ffDemuxer()
{
    foreach (ffStream* stream, m_streams) {
        m_streams.removeOne(stream);
        delete stream;
    }
}

bool ffDemuxer::Open(QString fileName)
{
    int ret;
    m_Error.clear();
    m_Ok = false;

    // Ha már nyitott egy médiát, hiba.
    if (m_ctx)
    {
        m_Error.setError(Error_QFFmpegDemuxerReopen);
        return false;
    }

 // A fájl létezésének és olvashatóságának ellenőrzése.
    m_file.setFile(fileName);
    if(!m_file.exists())
    {
        m_Error.setError(Error_FileNotFound);
        return false;
    }

    if(!m_file.isReadable())
    {
        m_Error.setError(Error_FileReadError);
        return false;
    }

 // Megnyitás
    ret = avformat_open_input(m_pfCtx, m_file.absoluteFilePath().toUtf8(), NULL, NULL);
    if (ret < 0)
    {
        m_Error.setError(Error_FileReadError);
        return false;
    }

    ret = avformat_find_stream_info(m_fCtx, NULL);
    if (ret < 0)
    {
        m_Error.setError(Error_FileFormatError);
        return false;
    }

    ret = DetectStreams();
    if (ret == false)
        return false;

    m_Ok = true;
    return true;
}

void ffDemuxer::Close()
{
    foreach (ffStream *stream, m_streams) {
        m_streams.removeOne(stream);
        delete stream;
    }

    if (m_ctx)
    {
        avformat_close_input(m_pfCtx);
        m_ctx = NULL;
    }

}

QList<ffStream *> ffDemuxer::VideoStreams()
{
    QList<ffStream*>    videoList;

    foreach (ffStream* stream, m_streams) {
        if (stream->Type() == ffStream::MediaType_Video)
            videoList.append(stream);
    }

    if (videoList.count() == 0)
        videoList.append(NULL);

    return videoList;
}

ffTimeStamp ffDemuxer::Start()
{
    return ffTimeStamp(m_fCtx->start_time);
}

ffTimeStamp ffDemuxer::Duration()
{
    return ffTimeStamp(m_fCtx->duration);
}

int ffDemuxer::BitRate()
{
    return m_fCtx->bit_rate;
}

ffDictionaryModel *ffDemuxer::Metadata()
{
    ffDictionaryModel *dict = new ffDictionaryModel(m_fCtx->metadata, this);

    if (!dict)
    {
        m_Error.setError(Error_NotEnoughMemory);
        return NULL;
    }

    return dict;
}

ffChapterModel* ffDemuxer::Chapter()
{
    ffChapterModel* chapterModel = new ffChapterModel(this),
                                * chapterModel2 = new ffChapterModel(this);
AVChapter *chapters;

    chapterModel2->append_ffMpegAvChapter((void**)m_fCtx->chapters, m_fCtx->nb_chapters);

    chapterModel2->chapters((void**)&chapters);
    chapterModel->append_ffMpegAvChapter((void**)&chapters, m_fCtx->nb_chapters);
    delete chapterModel2;
    av_free(chapters);
Log << "AVChapter tömb létrehozási test tőrlendő!!";

return chapterModel;
}

QString ffDemuxer::ContainerName()
{
    if (m_fCtx &&
         m_fCtx->iformat &&
         m_fCtx->iformat->name)
            return QString(m_fCtx->iformat->name);

    return QString(tr("Ismeretlen konténertipus"));
}

QString ffDemuxer::ContainerLongName()
{
    if (m_fCtx &&
         m_fCtx->iformat &&
         m_fCtx->iformat->long_name)
            return QString(m_fCtx->iformat->long_name);

    return QString(tr("Ismeretlen konténertipus"));
}

void ffDemuxer::DeleteStream(ffStream *stream)
{
    if (m_streams.removeOne(stream))
        delete stream;
}

bool ffDemuxer::DetectStreams()
{
    ffStream   *ff_stream;
    AVStream *stream;
    int i, nStreams = m_fCtx->nb_streams;

    for(i = 0; i < nStreams; i++)
    {
        stream = m_fCtx->streams[i];
        switch (stream->codec->codec_type) {
        case AVMEDIA_TYPE_VIDEO:
            ff_stream = new ffVideoStream(stream, this);
            break;

        case AVMEDIA_TYPE_AUDIO:
            ff_stream = new ffAudioStream(stream, this);
            break;

        case AVMEDIA_TYPE_SUBTITLE:
            ff_stream = new ffSubtitleStream(stream, this);
            break;

        case AVMEDIA_TYPE_DATA:
            ff_stream = new ffDataStream(stream, this);
            break;

        default:
            ff_stream = new ffStream(stream, this);
        }

        if (ff_stream)
            m_streams.append(ff_stream);
        else
        {
            m_Error.setError(Error_NotEnoughMemory);
            Close();
            return false;
        }
    }

    return true;
}

