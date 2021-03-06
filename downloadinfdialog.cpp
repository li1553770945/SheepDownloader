#include "downloadinfdialog.h"
#include "ui_downloadinfdialog.h"
#include <QFileDialog>

DownloadInfDialog::DownloadInfDialog(Downloader* _downloader,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadInfDialog)
{
    ui->setupUi(this);
    downloader = _downloader;
    ui->UrlLineEdit->setText(downloader->url);
    ui->FileNameLineEdit->setText(downloader->file_name);
    ui->SavePathLineEdit->setText(downloader->file_path);
}

DownloadInfDialog::~DownloadInfDialog()
{
    delete ui;
}
void DownloadInfDialog::on_UrlLineEdit_textChanged( const QString &text )
{
    downloader->url = text;
}
void DownloadInfDialog::on_FileNameLineEdit_textChanged( const QString &text )
{
    downloader->file_name = text;
}
void DownloadInfDialog::on_SavePathLineEdit_textChanged( const QString &text )
{
    downloader->file_path = text;
}
void DownloadInfDialog::on_SelectPathButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,"选择文件保存位置",".");
    if(!path.isEmpty())
    {
        ui->SavePathLineEdit->setText(path);
    }

}
