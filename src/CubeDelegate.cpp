#include "CubeDelegate.h"

CubeDelegate::CubeDelegate(QObject *parent) : QAbstractItemDelegate(parent) {}

void CubeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    const int dead = index.model()->data(index, Qt::DisplayRole).toInt();

    painter->save();

    QColor color = dead ? Qt::black : Qt::white;

    painter->fillRect(option.rect.x(), option.rect.y(), sizeOfCube, sizeOfCube, color);

    painter->restore();
}

QSize CubeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QSize(sizeOfCube, sizeOfCube);
}



