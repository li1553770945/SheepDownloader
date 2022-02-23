#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingwindow.h"
#include <QStandardItemModel>
#include "Downloader.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Downloader * select_downloader;
    QStandardItemModel* model;
    void InitConfig();
    void Download();
    Ui::MainWindow *ui;
    SettingWindow* setting_window;
    void ReadDownloadList();
    void SaveDownloadList();

private slots:
    void on_SettingAction_triggered();
    void on_DownloadButton_clicked();
    void on_DownloadList_clicked (const QModelIndex &);
    void SetProgressBar(float);
    void ChangeStatus();
};
#endif // MAINWINDOW_H
