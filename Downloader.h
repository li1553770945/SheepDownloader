#ifndef DOWNLOADER_H
#define DOWNLOADER_H
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
class Downloader:public QObject{
    Q_OBJECT
public:
    QString url;
    QString file_name;
    QString file_path;
    QFile file;
    int state;
    Downloader();
    virtual ~Downloader();
    virtual int Start()=0;
    virtual int StartDownloadThread() = 0;
    virtual long GetTotalFileLenth() = 0;             //获取将要下载的文件长度
    virtual long GetLocalFileLenth() = 0;         //获取本地文件长度
    virtual int GetFileNameFromUrl() = 0;      //从URL中获取文件名
    virtual int CreateFile();       //创建
public slots:
    virtual void DownloadFinished(QNetworkReply * reply)=0;



};
class HttpDownloader:public Downloader{
    Q_OBJECT
    QNetworkAccessManager d_manager;
    QNetworkReply *d_reply;
  public:
    HttpDownloader();
    ~HttpDownloader();
    int Start();
    int StartDownloadThread() ;
    long GetTotalFileLenth() ;
    long GetLocalFileLenth() ;
    int GetFileNameFromUrl();
public slots:
    void DownloadFinished(QNetworkReply *);
};

#endif // DOWNLOADER_H
