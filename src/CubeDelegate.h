#ifndef GAMEOFLIFE_CUBEDELEGATE_H
#define GAMEOFLIFE_CUBEDELEGATE_H
#include <QPainter>
#include <QAbstractItemDelegate>
#include "globals.h"

class CubeDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    CubeDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;

private:
};

#endif