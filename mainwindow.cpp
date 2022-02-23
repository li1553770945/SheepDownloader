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

    select_downloader = NULL;
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
void MainWindow::on_DownloadList_clicked (const QModelIndex &index)
{
    QVariant var = index.data(Qt::UserRole+1);
    Downloader* item_data = var.value<Downloader*>();//拿到原始数据，和放进去的时候必须对应
    if(select_downloader!=NULL)
    {
        disconnect(select_downloader,SIGNAL(PercentageChange(float)),this,SLOT(SetProgressBar(float)));
        disconnect(select_downloader,SIGNAL(StatusChange()),this,SLOT(ChangeStatus()));
    }
    select_downloader = item_data;
    connect(select_downloader,SIGNAL(PercentageChange(float)),this,SLOT(SetProgressBar(float)));
    connect(select_downloader,SIGNAL(StatusChange()),this,SLOT(ChangeStatus()));
    ui->FileName->setText(item_data->file_name);
    ui->URL->setText(item_data->url);
    ui->SavePath->setText(item_data->file_path);
    ui->Status->setText(item_data->StatusString());
}
void MainWindow::SetProgressBar(float percentage)
{
    ui->ProgressBar->setValue(percentage);
}
void MainWindow::ChangeStatus()
{
    ui->Status->setText(select_downloader->StatusString());
}
