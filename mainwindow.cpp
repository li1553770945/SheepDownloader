#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constant.h"
#include <qmessagebox.h>
#include "Downloader.h"
#include "downloadinfdialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    InitConfig();
    setting_window = NULL;
    ui->setupUi(this);
}
void MainWindow::InitConfig()
{
    config->Read();
    if(config->Get("default_path")==QJsonValue::Undefined)
    {
        config->Set("default_path","c:/download");
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::on_SettingAction_triggered()
{
    if(setting_window==NULL)
    {
        setting_window = new SettingWindow;
    }

    setting_window -> show();
}
void MainWindow::Download()
{
    QStringList url_list = ui->UrlTextEdit->toPlainText().split("\n");
    for(auto &url:url_list)
    {
        if(url.length()==0)
        {
            continue;
        }
        if(url.mid(0,4)=="http")
        {
            HttpDownloader * downloader = new HttpDownloader;
            downloader->file_path = config->Get("default_path").toString();
            downloader->url = url;
            DownloadInfDialog dialog(downloader,this);
            if(dialog.exec()==QDialog::Accepted)
            {
                   downloader->Download();
            }
            else
            {
                    delete downloader;
            }
        }
        else
        {
            QMessageBox box(QMessageBox::Critical,"错误","无法解析链接:"+url);
            box.exec();
        }
    }
}
void MainWindow::on_DownloadButton_clicked()
{
    Download();
}
