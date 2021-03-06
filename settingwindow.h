#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H



#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SettingWindowUi; }
QT_END_NAMESPACE

class SettingWindow : public QMainWindow
{
    Q_OBJECT

public:
    SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

private:
    Ui::SettingWindowUi *ui;

private slots:
    void on_SaveButton_clicked();
    void on_SelectSavePath_clicked();
    void on_SavePath_textChanged(const QString &);

};
#endif // SETTINGWINDOW_H
