#ifndef FFUTIL_H
#define FFUTIL_H

#include <QString>
#include <QList>

class ffUtil
{
public:
    ffUtil();

    static QList<QString >  getProfiles(void *codec);
    static QString          getProfileName(void * codec, int profileId);
    static int              getProfileId(void * codec, QString name);

};

#endif // FFUTIL_H
