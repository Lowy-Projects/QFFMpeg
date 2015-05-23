#include "ffStream.h"
#include "ffDemuxer.h"

#define m_pAVStream ((AVStream*)m_avStream)
#define m_ppAVStream ((AVStream**)&m_avStream)


ffStream::ffStream(QObject *parent): QObject(parent)
{
    m_Error.clear();
    m_avStream = NULL;
    m_MediaType = MediaType_Unknown;
}

ffStream::ffStream(void *avStream, QObject *parent) : QObject(parent)
{
    m_Error.clear();
    m_avStream = avStream;
    m_MediaType = MediaType_Unknown;
//    setting();
}

ffStream::~ffStream()
{
    Close();
}

// Index, a muxer/demuxerben.
int ffStream::Index()
{
    return m_pAVStream->index;
}

// Formátum specifikus azonosító
int ffStream::Id()
{
    return m_pAVStream->id;
}

void *ffStream::Codec()
{
    return (void *)m_pAVStream->codec->codec;
}

QString ffStream::CodecName()
{
    if (m_pAVStream &&
         m_pAVStream->codec &&
         m_pAVStream->codec->codec)
        return QString(m_pAVStream->codec->codec->name);

    return QString(tr("Ismeretlen"));
}

int ffStream::Profile()
{
    return m_pAVStream->codec->profile;
}

int ffStream::Level()
{
    return m_pAVStream->codec->level;
}

ffRational ffStream::BitRate()
{
    return ffRational(m_pAVStream->codec->bit_rate);
}

QString ffStream::TypeString()
{
    return QString(tr("Ismeretlen"));
}

bool ffStream::Open()
{
    AVDictionary        *opts = NULL;
    AVCodecContext *codec_ctx = m_pAVStream->codec;
    AVCodec               *codec        = avcodec_find_decoder(codec_ctx->codec_id);

    if (!codec)
    {
        Log << "Decoder not found.";
        return false;
    }

    av_dict_set(&opts, "refcounted_frames", "1", 0);
    if (avcodec_open2(codec_ctx, codec, &opts) < 0)
    {
        Log << "Decoder open error.";
        return false;
    }

    return true;
}

void ffStream::Close()
{
    if  (avcodec_is_open(m_pAVStream->codec))
        avcodec_close(m_pAVStream->codec);
}

bool ffStream::Read()
{

}

bool ffStream::Decode()
{

}

bool ffStream::isOpen()
{
    return avcodec_is_open(m_pAVStream->codec);
}

ffTimeStamp ffStream::Start()
{
    return ffTimeStamp(m_pAVStream->start_time, TimeBase());
}

ffTimeStamp ffStream::Duration()
{
    ffTimeStamp ts;

    ts.setValue(m_pAVStream->duration, TimeBase());

    if (!ts.isValid())
    {
        ffTimeStamp dur = ((ffDemuxer *)parent())->Duration();
        ts =dur;
    }

    return ts;
}

ffDictionaryModel *ffStream::Metadata()
{
    m_Error.clear();

    ffDictionaryModel *model = new ffDictionaryModel(m_pAVStream->metadata, this);

    if (!model)
        m_Error.setError(Error_NotEnoughMemory);

    return model;
}

ffRational ffStream::TimeBase()
{
    return ffRational(&(m_pAVStream->time_base));
}

ffRational ffStream::FrameRate()
{
    return ffRational(&m_pAVStream->codec->framerate);
}

QSize ffStream::FrameSize()
{
    QSize size;

    size.setWidth(m_pAVStream->codec->width);
    size.setHeight(m_pAVStream->codec->height);

    return size;
}

ffRational ffStream::PictureRatio()
{
    ffRational aspRatio;

    aspRatio.setValue(&m_pAVStream->display_aspect_ratio);

    if (! aspRatio.isValid())
    {
        QSize size = FrameSize();
        aspRatio.setValue((size.width() / (float)size.height()) * 100, 100);
    }

    return aspRatio;
}

ffRational ffStream::PixelRatio()
{
    return ffRational(&m_pAVStream->sample_aspect_ratio);
}

int ffStream::Channels()
{
    return m_pAVStream->codec->channels;
}

int ffStream::SampleRate()
{
    return m_pAVStream->codec->sample_rate;
}

int ffStream::BitDepth()
{
    return av_get_bytes_per_sample(m_pAVStream->codec->sample_fmt) * 8;
}

QString ffStream::SampleFormat()
{
   return ffSampleFormat::toString(m_pAVStream->codec->sample_fmt, true);
}

