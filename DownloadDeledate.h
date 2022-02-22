#ifndef DOWNLOADDELEDATE_H
#define DOWNLOADDELEDATE_H
#include <QStandardItem>
#include "Downloader.h"
#include <QStyledItemDelegate>
class DownloadDeledate:public QStyledItemDelegate{
public:
    DownloadDeledate(QObject *parent=nullptr);
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;

};

#endif // DOWNLOADDELEDATE_H
