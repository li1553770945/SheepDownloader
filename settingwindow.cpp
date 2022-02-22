#include "settingwindow.h"
#include "ui_settingwindow.h"
#include "constant.h"
#include "qmessagebox.h"
#include <QFileDialog>
SettingWindow::SettingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingWindowUi)
{
    ui->setupUi(this);
    ui->SavePath->setText(config->Get("default_path").toString());
}

SettingWindow::~SettingWindow()
{
    delete ui;
}
void SettingWindow::on_SaveButton_clicked()
{
    config->Save();
    QMessageBox box(QMessageBox::Information, "提示", "保存成功");
    box.exec();
}
void SettingWindow::on_SelectSavePath_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,"选择默认保存位置",".");
    if(!path.isEmpty())
    {
        ui->SavePath->setText(path);
    }

}
void SettingWindow::on_SavePath_textChanged(const QString &text)
{
    config->Set("default_path",text);
}
