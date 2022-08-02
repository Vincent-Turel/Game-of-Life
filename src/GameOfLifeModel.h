#ifndef GAMEOFLIFE_GAMEOFLIFEMODEL_H
#define GAMEOFLIFE_GAMEOFLIFEMODEL_H

#include <QAbstractItemModel>
#include <QSize>
#include <iostream>
#include "PlayThread.h"
#include "globals.h"

class GameOfLifeModel : public QAbstractTableModel{
    Q_OBJECT
public:
    GameOfLifeModel(QObject *parent = nullptr);
    ~GameOfLifeModel();

    void play();
    void pause();
    bool isPlaying();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;

    void quitThread();

public slots:
    void onTableClicked(QModelIndex index);
    void onNewData(int i, int j, int value);

private:
    bool m_playing = false;
    bool* m_isPlaying;
    int** m_tab;
    PlayThread thread;
};
#endif
