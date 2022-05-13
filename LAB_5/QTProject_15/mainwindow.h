#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QGridLayout>
#include <QLineEdit>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QVector>
//#include <functional>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QtCore/qmath.h>
//#include <QtGlobal>
#include "ethread.h"
#include <QTime>
#include <QLabel>
#include <iostream>

class EThread;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Elem
{
    QLineEdit* qLineEdit = nullptr;
    qint16 row = 0, col = 0;

    QLabel* qLabel = nullptr;
    qint16 lrow = 0, lcol = 0;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void func();
    void func_X();

    QVector<Elem>& GetQElem_s_2(){
        return qElem_s_2;
    };

    QVector<Elem>& GetQElem_s_1(){
        return qElem_s_1;
    };

    double setNewValue(const QString& fhStr);

    int& GetCN(){
        return CN;
    };

    bool GetPaus(){
        return paus;
    };

    void SetPaus(bool p){
         paus = p;
    };

    QMutex& GetMutex(){
        return mutex;
    };

    QVector<QVector<double>>& GA(){
        return A;
    };

    QVector<double>& GC(){
        return C;
    };

    QVector<bool>& GetFLAG_s_Ethread(){
        return FLAG_s_Ethread;
    };

    void SetFLAG_s_Ethread(int index,bool flg){
        FLAG_s_Ethread[index - 1] = flg;
    };

    QVector<bool> GetCount(){
        return Count;
    }

private:
     QMutex mutex;
     EThread* thread_1;
     EThread* thread_2;

private slots:
    void on_pushButton_clicked();

    void on_spinBox_1_valueChanged(int arg1);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QVector<QGridLayout> gridLayout;

    Elem Epsilon;
    ////////////////////////

    QVector<Elem> qElem_s_2;
    QVector<Elem> qElem_s_3;
    QVector<Elem> qElem_s_4;

    QVector<Elem> qElem_s_5;



    bool paus = false;

    QVector<Elem>qElem_s_1;

    QVector<bool> FLAG_s_Ethread;

    int CN;// Count_Nodes
    QVector<QVector<double>> A;
    QVector<QVector<double>> A_1;
    //QVector<double> A;
    //QVector<QVector<double>> C;
    QList<double> C;
    QVector<double> B;
    QVector<double> D;

    QVector<double> n_1;
    QVector<double> n_2;
    QVector<int> ITER_BUFF;
    QVector<QVector<double>> Z_W;
    QVector<QVector<double>> W;

    //QVector<QVector<double>> VECTOR(CN,QVector<double>(2, 0));

    QVector<QVector<double>> Y;
    QVector<QVector<double>> X;
    QVector<QVector<double>> X_2;

    QVector<double> X_1;
    QVector<double> C_1;
    QVector<double> FXV;

    QVector<bool> Count;


};
#endif // MAINWINDOW_H

