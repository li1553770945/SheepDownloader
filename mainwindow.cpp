#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constant.h"
#include <qmessagebox.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    config->Read();
    setting_window = NULL;
    ui->setupUi(this);
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

