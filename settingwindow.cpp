#include "settingwindow.h"
#include "ui_settingwindow.h"
#include "constant.h"
#include "qmessagebox.h"
SettingWindow::SettingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingWindowUi)
{
    ui->setupUi(this);
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
