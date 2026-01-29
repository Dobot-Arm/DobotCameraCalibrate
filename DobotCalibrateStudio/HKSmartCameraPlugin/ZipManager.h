#ifndef ZIPMANAGER_H
#define ZIPMANAGER_H

#include <QObject>

class ZipManager
{
public:
    static bool zipFiles(const QStringList& lstFiles, const QString& strSaveFile);
    static bool zipFolder(const QString& strSrcDir, const QString& strSaveFile);
    static bool unzip(const QString& strZipFile, const QString& strSaveDir);

private:
    static void zipFolder(void* zipWriterHandle, const QString& strZipParentDirName, const QString& strSrcDir);
};

#endif // ZIPMANAGER_H
