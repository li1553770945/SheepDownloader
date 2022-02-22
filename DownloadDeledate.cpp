#include "DownloadDeledate.h"
#include "Downloader.h"
#include <QPainter>
#include <QPainterPath>
DownloadDeledate::DownloadDeledate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

void DownloadDeledate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->save();

        QVariant var = index.data(Qt::UserRole+1);
        Downloader* item_data = var.value<Downloader*>();//拿到原始数据，和放进去的时候必须对应

        // item 矩形区域
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        QPainterPath path;
        path.moveTo(rect.topRight());
        path.lineTo(rect.topLeft());
        path.quadTo(rect.topLeft(), rect.topLeft());
        path.lineTo(rect.bottomLeft());
        path.quadTo(rect.bottomLeft(), rect.bottomLeft());
        path.lineTo(rect.bottomRight());
        path.quadTo(rect.bottomRight(), rect.bottomRight());
        path.lineTo(rect.topRight());
        path.quadTo(rect.topRight(), rect.topRight());

        // 鼠标悬停或者选中时改变背景色
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->setPen(QPen(QColor(239,246,254)));
            painter->setBrush(QColor(239,246,254));
            painter->drawPath(path);
        }
        if (option.state.testFlag(QStyle::State_Selected)) {
            painter->setPen(QPen(QColor(229,240,254)));
            painter->setBrush(QColor(229,240,254));
            painter->drawPath(path);
        }
        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Microsoft Yahei", 10));
        QString filename=QString(item_data->file_name);
        painter->drawText(rect,filename);
        painter->restore();
    }
}

QSize DownloadDeledate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 50);
}
