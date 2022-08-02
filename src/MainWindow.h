#ifndef GAMEOFLIFE_MAINWINDOW_H
#define GAMEOFLIFE_MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QTableView>
#include <QtGui>
#include <QHeaderView>
#include <QVBoxLayout>
#include "GameOfLifeModel.h"
#include "CubeDelegate.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();
    void keyReleaseEvent(QKeyEvent*) override;

private:
    GameOfLifeModel *model;
    QTableView *view;

    void closeEvent(QCloseEvent *event);
};
#endif
