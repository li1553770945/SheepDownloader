#ifndef DOWNLOADER_H
#define DOWNLOADER_H
#include <QString>
class Downloader{
public:
    QString url;
    QString file_name;
    QString file_path;
    int state;
    Downloader();
    virtual ~Downloader();
    virtual int Start()=0;
    virtual int StartDownloadThread() = 0;
    virtual long GetTotalFileLenth() = 0;             //获取将要下载的文件长度
    virtual long GetLocalFileLenth() = 0;         //获取本地文件长度
    virtual int GetFileNameFromUrl() = 0;      //从URL中获取文件名
    virtual int CreateDir();       //是否在本地创建目录，没有就创建



};
class HttpDownloader:public Downloader{
  public:
    HttpDownloader();
    ~HttpDownloader();
    int Start();
    int StartDownloadThread() ;
    long GetTotalFileLenth() ;
    long GetLocalFileLenth() ;
    int GetFileNameFromUrl();
};

#endif // DOWNLOADER_H
