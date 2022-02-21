#ifndef DOWNLOADINFDIALOG_H
#define DOWNLOADINFDIALOG_H

#include <QDialog>
#include "Downloader.h"
namespace Ui {
class DownloadInfDialog;
}

class DownloadInfDialog : public QDialog
{
    Q_OBJECT

public:
    Downloader* downloader;
    explicit DownloadInfDialog(Downloader* _downloader,QWidget *parent = nullptr);
    ~DownloadInfDialog();

private:
    Ui::DownloadInfDialog *ui;
private slots:
    void on_UrlLineEdit_textChanged( const QString &text );
    void on_FileNameLineEdit_textChanged( const QString &text );
    void on_SavePathLineEdit_textChanged( const QString &text );
};

#endif // DOWNLOADINFDIALOG_H
