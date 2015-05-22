#include "ffUtil.h"
#include "ffmpeg_headers.h"

ffUtil::ffUtil()
{

}

// //////////////////////////////
// Codec Profilkezelés
// /////////////////////////////
/// \brief ffUtil::getProfiles
/// \param codec A codec, amelyhez tartozó profilok nevét kérdezzük.
/// \return QList<QString> Lista a codecen alkalmazható profilok neveivel
/// Visszaadja a codec-ben használható profilok nevét.
/// Ha nincs profil, üres listával tér vissza.
QList<QString> ffUtil::getProfiles(void *codec)
{
    QList<QString>   list;
    AVCodec                 *m_codec = (AVCodec*)codec;
    const AVProfile     *profiles = m_codec->profiles;

    if (profiles)
    {
        while (profiles->profile != FF_PROFILE_UNKNOWN)
            {
                list.append(QString(profiles->name));
                profiles++;
            }
    }

    return list;
}

/// \brief ffUtil::getProfileName
/// \param codec A codec, melyre a profil vonatkozik
/// \param profileId A profil azonosítója
/// \return QString A profil neve
/// A 'profileId'-vel azonosított profil nevét adja meg.
/// Ha nem létezik ilyen profil, vagy nem használható a codec-hez, üres stringel tér vissza.
QString ffUtil::getProfileName(void *codec, int profileId)
{
    QString                 name = QString();
    AVCodec              *m_codec = (AVCodec*)codec;
    const AVProfile   *profiles = m_codec->profiles;

    if (profiles)
    {
        while (profiles->profile != FF_PROFILE_UNKNOWN)
            {
                if (profiles->profile == profileId)
                {
                    name = QString(profiles->name);
                    break;
                }
                profiles++;
            }
    }

    return name;
}

///
/// \brief ffUtil::getProfileId
/// \param codec A codec, melyen a profilt be szeretnénk állítani
/// \param name A profil neve
/// \return A profil azonosítója.
/// Megadja a profil azonosítóját.
/// Ha nem létezik a kért nevű profil, vagy nem alkalmazható a codec-en, -1 -el tér vissza.
int ffUtil::getProfileId(void * codec, QString name)
{
    int                           id = -1;
    AVCodec              *m_codec = (AVCodec*)codec;
    const AVProfile   *profiles = m_codec->profiles;

    if (profiles)
    {
        while (profiles->profile != FF_PROFILE_UNKNOWN)
            {
                if (QString(profiles->profile).compare(name) == 0)
                {
                    id = profiles->profile;
                    break;
                }
                profiles++;
            }
    }

    return id;
}

