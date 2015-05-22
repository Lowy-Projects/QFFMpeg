#include <QObject>
#include "qffmpeg"

QFfmpeg::QFfmpeg(QObject *parent): QObject(parent)
{
    Log << "QFFMpeg indítása.";
}

bool QFfmpeg::Init(QWidget *logWin)
{
    av_register_all();

    if (logWin)
        Log.setDirectMainWidget(logWin);

    Log.setPrefixText("QFFMpeg");
    Log << "Inicializálás kész.";

    return true;
}

ffDemuxer *QFfmpeg::OpenMedia(QString fileName)
{
    lError Error;

    Error.clear();

    ffDemuxer *demuxer = new ffDemuxer(this);

    if (demuxer)
    {
        if(!demuxer->Open(fileName))
        {
            Error.copyFrom(demuxer->Error());
            demuxer->Close();
            delete demuxer;
            demuxer = NULL;
        }
    }
    else
    Error.setError(Error_NotEnoughMemory);

    if (Error.ErrorCode() != Error_NoError)
        Error.show(0);

    return demuxer;
}

