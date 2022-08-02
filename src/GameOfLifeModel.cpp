#include "GameOfLifeModel.h"

void executeGame(int tab[nb_lignes][nb_colonnes]);

GameOfLifeModel::GameOfLifeModel(QObject *parent) : QAbstractTableModel(parent) {
    connect(&thread, SIGNAL(newData(int,int,int)), this, SLOT(onNewData(int,int,int)));
    m_isPlaying = &m_playing;
    m_tab = new int *[nb_lignes];
    for( int i = 0 ; i < nb_lignes ; i++ )
        m_tab[i] = new int[nb_colonnes];

    for (int i(0); i < nb_lignes; i++) {
        for (int j(0); j < nb_colonnes; j++) {
            m_tab[i][j] = 0;
        }
    }
    m_tab[nb_lignes/2][nb_colonnes/2] = 1;
    thread.play(m_tab, m_isPlaying);
}

int GameOfLifeModel::rowCount(const QModelIndex &parent) const {
    return nb_lignes;
}

int GameOfLifeModel::columnCount(const QModelIndex &parent) const {
    return nb_colonnes;
}

QVariant GameOfLifeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole) || index.row() >= nb_lignes || index.column() >= nb_colonnes)
        return QVariant();

    else
        return QVariant::fromValue(m_tab[index.row()][index.column()]);
}

QVariant GameOfLifeModel::headerData(int, Qt::Orientation, int role) const
{
    if (role == Qt::SizeHintRole)
        return QSize(1, 1);
    return QVariant();
}

Qt::ItemFlags GameOfLifeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool GameOfLifeModel::setData(const QModelIndex &index,const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_tab[index.row()][index.column()] = value.toInt();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void GameOfLifeModel::onTableClicked(QModelIndex index) {
    if (m_tab[index.row()][index.column()] == 0)
        setData(index, QVariant::fromValue(1), Qt::EditRole);
    else
        setData(index, QVariant::fromValue(0), Qt::EditRole);
}

void GameOfLifeModel::onNewData(int i, int j, int value) {
    setData(this->index(i,j), QVariant::fromValue(value), Qt::EditRole);
}

void GameOfLifeModel::play() {
    *m_isPlaying = true;
    std::cout << "play" << std::endl;
}

void GameOfLifeModel::pause() {
    *m_isPlaying = false;
    std::cout << "pause" << std::endl;
}

bool GameOfLifeModel::isPlaying() {
    return *m_isPlaying;
}

void GameOfLifeModel::quitThread() {
    thread.end();
    thread.quit();
    thread.wait();
}

GameOfLifeModel::~GameOfLifeModel() {
    for( int i = 0 ; i < nb_lignes ; i++ ) {
        delete [] m_tab[i];
    }
    delete [] m_tab;
}




