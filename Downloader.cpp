#include "Downloader.h"
Downloader::Downloader()
{

}

Downloader::~Downloader()
{

}
int Downloader::CreateDir()
{
    return 0;
}

HttpDownloader::HttpDownloader()
{
    state = 0;
}

HttpDownloader::~HttpDownloader()
{

}
int HttpDownloader::Start()
{
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
    return 0;
}

