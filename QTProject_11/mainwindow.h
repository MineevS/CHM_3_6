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

    QVector<QVector<double>>& GB(){
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

    bool paus = false;

    QVector<Elem>qElem_s_1;

    QVector<bool> FLAG_s_Ethread;

    int CN;// Count_Nodes
    QVector<QVector<double>> A;
    //QVector<double> A;
    //QVector<QVector<double>> C;
    QList<QVector<double>> C;
    QVector<double> B;

    //QVector<QVector<double>> VECTOR(CN,QVector<double>(2, 0));

    QVector<QVector<double>> Y;
    QVector<double> X;

    QVector<bool> Count;


};
#endif // MAINWINDOW_H

