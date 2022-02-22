#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constant.h"
#include <qmessagebox.h>
#include "Downloader.h"
#include "downloadinfdialog.h"
#include "DownloadDeledate.h"
#include <QStandardItem>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitConfig();
    model = new QStandardItemModel(this);
    ui->DownloadList->setModel(model);
    DownloadDeledate * deledate = new DownloadDeledate(this);
    ui->DownloadList->setItemDelegate(deledate);
    ReadDownloadList();
    setting_window = NULL;

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
            downloader->GetFileNameFromUrl();
            DownloadInfDialog dialog(downloader,this);
            if(dialog.exec()==QDialog::Accepted)
            {
                downloader->Start();
                QVariant variant;
                variant.setValue(downloader);
                QStandardItem *item = new QStandardItem();
                item->setData(variant);
                model->appendRow(item);
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
void MainWindow::ReadDownloadList()
{

}
void MainWindow::SaveDownloadList()
{

}
