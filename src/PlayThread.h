#ifndef GAMEOFLIFE_PLAYTHREAD_H
#define GAMEOFLIFE_PLAYTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "globals.h"

class PlayThread : public QThread
{
Q_OBJECT

public:
    PlayThread(QObject *parent = nullptr);
    ~PlayThread();

    void play(int **tab, bool *isPlaying);
    void run() override;
    void end();

signals:
    void newData(int, int, int);

private:
    bool exitPressed = false;
    bool *m_isPlaying;
    int **m_tab;
    int m_tabCopy[nb_lignes][nb_colonnes];
};

#endif
