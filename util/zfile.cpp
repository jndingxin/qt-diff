#include "zfile.h"
#include <QTextStream>
#include <QFileIconProvider>
#include <QTemporaryFile>
#include "zhash.h"

ZFile::ZFile()
{

}

ZFile::~ZFile()
{

}

int ZFile::lines(QFile *file)
{
    int count = -1;
    if(!file->open(QIODevice::ReadOnly))
    {
        return count;
    }
    else
    {
        count = 0;
    }

    QTextStream in(file);
    in.setCodec("UTF-8");
    while(!in.atEnd())
    {
        in.readLine();
        count++;
    }
    file->close();

    return count;
}

int ZFile::linesWithLine(QFile *file, QList<QString> &lineLst)
{
    int count = -1;
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return count;
    }
    else
    {
        count = 0;
    }

    QTextStream in(file);
    in.setCodec("UTF-8");
    while(!in.atEnd())
    {
        lineLst.append(in.readLine());
        count++;
    }
    file->close();

    return count;
}

int ZFile::linesWithHash(QFile *file, QList<unsigned int> &hashLst)
{
    int count = -1;
    if(!file->open(QIODevice::ReadOnly))
    {
        return count;
    }
    else
    {
        count = 0;
    }

    QTextStream in(file);
    in.setCodec("UTF-8");
    while(!in.atEnd())
    {
        QString line = in.readLine();
        hashLst.append(ZHash::ELFHash(line));
        count++;
    }
    file->close();

    return count;
}

QFileInfoList ZFile::files(const QString &path)
{
    QFileInfoList fileList;
    if(!path.isEmpty())
    {
        QDir dir(path);
        fileList = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        QFileInfoList folderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

        for(int i = 0; i < folderList.size(); i++)
        {
             QString path = folderList.at(i).absoluteFilePath();
             QFileInfoList childFileList = files(path);
             fileList.append(childFileList);
        }
    }

    return fileList;
}

QIcon ZFile::icon(const QString &path)
{
    QFileIconProvider provider;
    QIcon icon;
    QTemporaryFile tmpFile(path);
    tmpFile.setAutoRemove(false);

    if (tmpFile.open())
    {
        tmpFile.close();
        icon = provider.icon(QFileInfo(path));
        tmpFile.remove();
    }

    return icon;
}
