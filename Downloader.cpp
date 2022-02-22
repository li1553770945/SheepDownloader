#include "Downloader.h"
#include "QNetworkAccessManager"
#include "QNetworkRequest"
#include "QNetworkReply"
#include "QMessageBox"
#include <QProgressDialog>
#include <QCoreApplication>
#include <QDir>
Downloader::Downloader()
{

}

Downloader::~Downloader()
{

}
Downloader::Downloader(const Downloader &)
{

}

int Downloader::Start()
{
    return 0;
}
int Downloader::GetFileNameFromUrl()
{
    return 0;
}
void Downloader::DownloadFinished(QNetworkReply * reply)
{

}
int Downloader::CreateFile(bool create)
{
    file.close();
    QDir dir;
    dir.mkpath(file_path);
    QDir dir1(file_path);
    QString abs_file_name = dir1.absoluteFilePath(file_name);
    file.setFileName(abs_file_name);
    int i=1;
    QFileInfo info(file_name);
    while(file.exists())
    {

        file_name = info.completeBaseName() + "(" +QString::number(i)+ ")." +info.suffix();
        QString abs_file_name = dir1.absoluteFilePath(file_name);
        file.setFileName(abs_file_name);
        i++;
    }
    if(create)
    {
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox box(QMessageBox::Critical, tr("错误"),
                          tr("无法创建文件%1:%2").arg(abs_file_name,file.errorString()));
            box.exec();
            return -1;
        }
    }
    return 0;
}

HttpDownloader::HttpDownloader()
{
    state = 0;
}

HttpDownloader::~HttpDownloader()
{
    if(d_reply!=NULL)
    {
        delete d_reply;
    }
}
int HttpDownloader::Start()
{
    qDebug()<<"下载开始";
    CreateFile(true);
    connect(
     &d_manager, SIGNAL (finished(QNetworkReply*)),
     this, SLOT (DownloadFinished(QNetworkReply*))
    );

    QUrl url1(url);
    QNetworkRequest request(url1);
    d_manager.get(request);
    return 0;
}
int HttpDownloader::StartDownloadThread()
{
    return 0;
}
long HttpDownloader::GetTotalFileLenth() //获取将要下载的文件长度
{
    return 0;
}
long HttpDownloader::GetLocalFileLenth()//获取本地文件长度
{
    return 0;
}
int HttpDownloader::GetFileNameFromUrl()   //从URL中获取文件名
{
    QUrl url1(url);
    file_name = url1.fileName();
    if(file_name!="")
    {
        CreateFile(false);
        return 0;
    }
    QNetworkAccessManager manager;
    QNetworkRequest request(url1);
    QNetworkReply *reply = manager.head(request);
    QProgressDialog progress("正在获取文件信息...", 0, 0, 0);
    progress.setWindowTitle("处理中");
    progress.setModal(true);
    progress.show();
    while(!reply->isFinished())
    {
        QCoreApplication::processEvents();
        if(progress.wasCanceled())
            return 0;
    }
    progress.close();
    if(reply->error()!=QNetworkReply::NoError)
    {
        QMessageBox box(QMessageBox::Critical,"错误","无法获取文件信息"+reply->errorString());
        box.exec();
        return reply->error();
    }
    qDebug()<<"header:"<<reply->rawHeaderList();
    QString filename = reply->rawHeader("Content-Disposition");
    delete reply;
    qDebug()<<"filename:"<<filename;
    file_name = filename;
    CreateFile(false);
    return 0;
}
void HttpDownloader::DownloadFinished(QNetworkReply* reply)
{
    qDebug()<<"下载完成";
    file.write(reply->readAll());
    file.close();
}
