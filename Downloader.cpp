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
    status = 0;
}

Downloader::~Downloader()
{

}
Downloader::Downloader(const Downloader &)
{

}

int Downloader::Start()
{
    status = 1;
    emit StatusChange();
    return 0;
}
int Downloader::GetFileNameFromUrl()
{
    return 0;
}
void Downloader::DownloadFinished()
{
    status = 3;
    emit StatusChange();
}
void Downloader::ReadyRead()
{

}
void Downloader::DownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{

}
void Downloader::Error(QNetworkReply::NetworkError code)
{
    status = -1;
    emit StatusChange();
}

QString Downloader::StatusString()
{
    switch (status)
    {
    case -1:
        return "错误";
    case 0:
        return "创建项目";
    case 1:
        return "下载中";
    case 2:
        return "暂停";
    case 3:
        return "已完成";
    default:
        return "未知";
    }


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
        file.setFileName(abs_file_name);//为了检测file.exists()
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
    Downloader::Start();
    qDebug()<<"下载开始";
    CreateFile(true);
    QUrl url1(url);
    QNetworkRequest request(url1);
    d_reply=d_manager.get(request);
    connect(d_reply,SIGNAL(readyRead()),this,SLOT(ReadyRead()));                //可读
    connect(d_reply,SIGNAL(finished()),this,SLOT(DownloadFinished()));                  //结束
    connect(d_reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(DownloadProgress(qint64,qint64)));   //大小
    connect(d_reply,SIGNAL(errorOccurred(QNetworkReply::NetworkError)),this,SLOT(Error(QNetworkReply::NetworkError)));  //异常
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
void HttpDownloader::DownloadFinished()
{
    qDebug()<<"下载完成";

    Downloader::DownloadFinished();
    file.close();
}
void HttpDownloader::ReadyRead()
{
    Downloader::ReadyRead();
    file.write(d_reply->readAll());
}

void HttpDownloader::DownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    local_size = bytesReceived;
    total_size = bytesTotal;
    emit PercentageChange(bytesReceived*1.0/bytesTotal*100);
}
void HttpDownloader::Error(QNetworkReply::NetworkError code)
{
    Downloader::Error(code);
    QMessageBox box(QMessageBox::Critical,"错误","网络错误"+d_reply->errorString());
    box.exec();
}
