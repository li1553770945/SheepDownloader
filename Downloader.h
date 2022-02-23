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
    long long local_size;
    long long total_size;
    int status;
    Downloader();
    virtual ~Downloader();
    Downloader(const Downloader &);
    virtual int Start();
    virtual int GetFileNameFromUrl() ;      //从URL中获取文件名
    virtual int CreateFile(bool);       //创建文件，传入true表示在磁盘创建，否则只修改file变量
    QString StatusString(); //当前状态
public slots:
    virtual void DownloadFinished();    //下载完成
    virtual void ReadyRead();    //可以读取
    virtual void DownloadProgress(qint64,qint64); //修改大小
    virtual void Error(QNetworkReply::NetworkError code); //发生错误
signals:
    void PercentageChange(float); //发送当前百分比
    void StatusChange(); //状态发生变化的信号
};
class HttpDownloader:public Downloader{
    Q_OBJECT
    QNetworkAccessManager d_manager;
    QNetworkReply *d_reply;
  public:
    HttpDownloader();
    ~HttpDownloader();
    int Start();
    int GetFileNameFromUrl();

public slots:
    void ReadyRead();
    void DownloadFinished();
    void DownloadProgress(qint64,qint64);
    void Error(QNetworkReply::NetworkError code);

};
Q_DECLARE_METATYPE(Downloader*)
#endif // DOWNLOADER_H
