#ifndef DOWNLOADER_H
#define DOWNLOADER_H
#include <QString>
class Downloader{
public:
    QString url;
    QString file_name;
    QString file_path;
//    virtual bool Connect();
    virtual void Download() = 0;
    virtual ~Downloader()


};
class HttpDownloader:public Downloader{
  public:
    void Download();
    ~HttpDownloader();
};

#endif // DOWNLOADER_H
