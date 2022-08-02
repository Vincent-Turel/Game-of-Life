#include <iostream>
#include "PlayThread.h"

PlayThread::PlayThread(QObject *parent) : QThread(parent) {}

PlayThread::~PlayThread() {
    wait();
}

void PlayThread::run() {
    for (;;) {
        if (exitPressed)
            return;
        if (*m_isPlaying) {
            for (int i(0); i < nb_lignes; i++) {
                for (int j(0); j < nb_colonnes; j++) {
                    m_tabCopy[i][j] = m_tab[i][j];
                }
            }
            int nbAliveNeighboor;
            for (int i(0); i < nb_lignes; i++) {
                for (int j(0); j < nb_colonnes; j++) {
                    nbAliveNeighboor = 0;
                    for (int x = std::max(0, i - 1); x <= std::min(i + 1, nb_lignes); x++) {
                        for (int y = std::max(0, j - 1); y <= std::min(j + 1, nb_colonnes); y++) {
                            if (x != i || y != j) {
                                nbAliveNeighboor += m_tabCopy[x][y];
                            }

                        }
                    }
                    if (nbAliveNeighboor == 3) {
                        m_tab[i][j] = 1;
                    }
                    if (nbAliveNeighboor < 2 || nbAliveNeighboor > 3) {
                        m_tab[i][j] = 0;
                    }
                    emit newData(i, j, m_tab[i][j]);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
    }
}

void PlayThread::play(int **tab, bool *isPlaying) {
    m_isPlaying = isPlaying;
    m_tab = tab;
    if (!isRunning()) {
        start();
    }
}

void PlayThread::end() {
    exitPressed = true;
}
