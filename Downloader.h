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
    QString time;
    int progress;
    int state;
    Downloader();
    virtual ~Downloader();
    Downloader(const Downloader &);
    virtual int Start();
//    virtual int StartDownloadThread() = 0;
//    virtual long GetTotalFileLenth() = 0;             //获取将要下载的文件长度
//    virtual long GetLocalFileLenth() = 0;         //获取本地文件长度
    virtual int GetFileNameFromUrl() ;      //从URL中获取文件名
    virtual int CreateFile(bool);       //创建文件，传入true表示在磁盘创建，否则只修改file变量
public slots:
    virtual void DownloadFinished(QNetworkReply * reply);



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
Q_DECLARE_METATYPE(Downloader*)
#endif // DOWNLOADER_H
