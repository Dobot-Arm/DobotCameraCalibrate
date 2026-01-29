#include "ZipManager.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QVector>
#include <memory>
#include <QtGui/private/qzipreader_p.h>
#include <QtGui/private/qzipwriter_p.h>

bool ZipManager::zipFiles(const QStringList& lstFiles, const QString& strSaveFile)
{
    QFile file(strSaveFile);
    if (!file.open(QFile::WriteOnly|QFile::Truncate)){
        qDebug()<<file.errorString();
        return false;
    }
    std::unique_ptr<QZipWriter> zipWriter(new QZipWriter(&file));
    for (const QString &fileName : lstFiles)
    {
        if (fileName.isEmpty()) continue;
        QFileInfo fileInfo(fileName);
        if (!fileInfo.exists()) continue;
        QFile tmpFile(fileName);
        if (!tmpFile.open(QIODevice::ReadOnly)){
            qDebug()<<tmpFile.errorString();
            continue;
        }
        zipWriter->addFile(fileInfo.fileName(), tmpFile.readAll());
        tmpFile.close();
    }
    zipWriter->close();
    file.close();
    return true;
}

void ZipManager::zipFolder(void* zipWriterHandle, const QString& strZipParentDirName, const QString& strSrcDir)
{
    QZipWriter* zipWriter = (QZipWriter*)zipWriterHandle;
    QDir directory(strSrcDir);
    QFileInfoList fileList = directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &fileInfo : fileList) {
        QString strRelatePath = fileInfo.fileName();
        if (!strZipParentDirName.isEmpty()){
            strRelatePath.prepend(strZipParentDirName+"/");
        }
        if (fileInfo.isDir()) {
            zipWriter->addDirectory(strRelatePath);
            zipFolder(zipWriter, strRelatePath, fileInfo.absoluteFilePath());
        } else {
            QFile file(fileInfo.absoluteFilePath());
            if (!file.open(QIODevice::ReadOnly)) continue;
            zipWriter->addFile(strRelatePath, file.readAll());
            file.close();
        }
    }
}
bool ZipManager::zipFolder(const QString& strSrcDir, const QString& strSaveFile)
{
    QFile file(strSaveFile);
    if (!file.open(QFile::WriteOnly)){
        return false;
    }
    std::unique_ptr<QZipWriter> zipWriter(new QZipWriter(&file));
    zipFolder(zipWriter.get(), "", strSrcDir);
    zipWriter->close();
    file.close();
    return true;
}

bool ZipManager::unzip(const QString& strZipFile, const QString& strSaveDir)
{
    QFile file(strZipFile);
    if (!file.open(QFile::ReadOnly)){
        return false;
    }
    QDir dir(strSaveDir);
    if (!dir.exists()){
        if (!dir.mkpath(strSaveDir)){
            return false;
        }
    }
    std::unique_ptr<QZipReader> zipReader(new QZipReader(&file));
    return zipReader->extractAll(strSaveDir);
}
