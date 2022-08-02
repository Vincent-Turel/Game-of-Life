#include "MainWindow.h"

MainWindow::MainWindow()
{
    auto *centralWidget = new QWidget;

    model = new GameOfLifeModel(this);

    view = new QTableView;
    view->setShowGrid(false);
    view->horizontalHeader()->hide();
    view->verticalHeader()->hide();
    view->verticalHeader()->setMinimumSectionSize(1);
    view->horizontalHeader()->setMinimumSectionSize(1);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setModel(model);
    view->setFixedSize(nb_colonnes*sizeOfCube, nb_lignes*sizeOfCube);

    auto *delegate = new CubeDelegate(this);
    view->setItemDelegate(delegate);

    view->resizeColumnsToContents();
    view->resizeRowsToContents();

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(view);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("The Game Of Life");
    adjustSize();
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    connect(view, SIGNAL(clicked(QModelIndex)), model, SLOT(onTableClicked(QModelIndex)));
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Return)
    {
        if (model->isPlaying())
            model->pause();
        else
            model->play();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    model->quitThread();
    event->accept();
}
