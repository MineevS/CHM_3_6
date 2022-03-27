#ifndef ETHREAD_H
#define ETHREAD_H

#include <QString>
#include <QThread>
#include <QDebug>
#include <windows.h>
#include <unistd.h>
#include "mainwindow.h"

class MainWindow;

class EThread : public QThread
{
    Q_OBJECT
public:
    explicit EThread(QString thread_name, size_t index, MainWindow& mw);

     ~EThread(){
        this->quit();
        this->wait();
        this->deleteLater();
    };

    void run();
    void Pause();
    void Resume();

private slots:

signals:

private:
    QString name;
    qint16 index;
    MainWindow& mw;
};

#endif // ETHREAD_H
