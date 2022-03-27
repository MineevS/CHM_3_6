#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, (&MainWindow::func));

    ui->spinBox_1->setValue(9);//9/5

    ui->pushButton->setVisible(false);

    func_X();
}

void MainWindow::func_X()
{
    CN = ui->spinBox_1->value();

    if(CN > 0)
    {
        QVector<QVector<double>> VECTOR(CN,QVector<double>(2, 0));

        double vecF[][2] = {
            0.593, 0.532050,
            0.598, 0.535625,
            0.605, 0.540598,
            0.613, 0.546235,
            0.619, 0.550431,
            0.627, 0.555983,
            0.632, 0.559428,
            0.640, 0.568738,
            0.650, 0.575298}; // f(x)


        /*double vecF[][2] = {
            0, 1,
            2, 4,
            3, 11,
            7, 26,
            10, 53};*/


        size_t N = 12;
        //double x_0=0.1485-0.002*N;

        double vecS[2] = {9, (double)3*N}; //Segment
        double vecZ[2] = {5, (double)3*N};

        double eps = 0.00001;

        if((qElem_s_1.count()) == CN*2+2){

            for (size_t i = 2; i < qElem_s_1.count(); i+=1){

                qElem_s_1[i].qLineEdit->setText(QString::number(vecF[(i-2) / 2][(i-2) % 2],'f',5+i%2));// Точность
                //qElem_s_1[i+1].qLineEdit->setText(QString::number(vecF[i][1]));
            }

            qElem_s_2[0].qLineEdit->setText(QString::number(vecS[0],'f',0));
            qElem_s_2[1].qLineEdit->setText(QString::number(vecS[1],'f',0));
            //qElem_s_2[2].qLineEdit->setText(QString::number(vecS[2],'f',3));

            qElem_s_3[0].qLineEdit->setText(QString::number(vecZ[0],'f',0));
            qElem_s_3[1].qLineEdit->setText(QString::number(vecZ[1],'f',0));
        }

        Epsilon.qLineEdit->setText(QString::number(eps,'f', 5));
    }
}

void MainWindow::func()
{
    if(ui->spinBox_1->value() < 10)
    {
        qDebug() << qElem_s_1.count()*qElem_s_1.count();

        if(qElem_s_1.count() > 0)
        {
            foreach (auto elem, qElem_s_1) {
                ui->gridLayout_3->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.row,elem.col));
            }
            qElem_s_1.clear();
        }

        //qDebug() << "CountCol:" << ui->gridLayout_3->columnCount();

        //ui->gridLayout_3->setGeometry(QRect(10, 10, 100, 1000));
        //ui->spinBox_1->setValue(ui->spinBox_1->value() + 1);

        for(size_t i = 0; i < ui->spinBox_1->value(); i++){

                Elem elem;

                ui->horizontalSpacer_1->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_1->geometry().height());
                ui->horizontalSpacer_2->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_1->geometry().height());

                elem.qLineEdit = new  QLineEdit;
                elem.qLineEdit->setAlignment(Qt::AlignHCenter);

                elem.row = 0;
                elem.col = i;

                qElem_s_1.push_back(elem);

                ui->gridLayout_3->addWidget(elem.qLineEdit,elem.row,elem.col,Qt::Alignment());
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->timer->start(1000);
}

void MainWindow::on_spinBox_1_valueChanged(int arg1)
{
    if(arg1 >= 0){
        if(qElem_s_1.count() > 0){
            foreach (auto elem, qElem_s_1){
                ui->gridLayout_3->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.row,elem.col));

                //ui->gridLayout_3->itemAtPosition(elem.lrow, elem.lcol)->widget()->deleteLater();
                //ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.lrow,elem.lcol));
            }
            qElem_s_1.clear();
        }

        if(qElem_s_2.count() > 0){
            foreach(auto elem, qElem_s_2)
            {
                ui->gridLayout_6->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                ui->gridLayout_6->removeItem(ui->gridLayout_6->itemAtPosition(elem.row,elem.col));
            }
            qElem_s_2.clear();
        }

        if(qElem_s_3.count() > 0){
            foreach(auto elem, qElem_s_3)
            {
                ui->gridLayout_12->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                ui->gridLayout_12->removeItem(ui->gridLayout_12->itemAtPosition(elem.row,elem.col));
            }
            qElem_s_3.clear();
        }

        // Epsilon:

        if(Epsilon.qLineEdit != nullptr){
            ui->gridLayout_9->itemAtPosition(Epsilon.row, Epsilon.col)->widget()->deleteLater();
            ui->gridLayout_9->removeItem(ui->gridLayout_9->itemAtPosition(Epsilon.row,Epsilon.col));

            delete Epsilon.qLineEdit;
        }

            Epsilon.qLineEdit = new  QLineEdit;
            Epsilon.qLineEdit->setAlignment(Qt::AlignHCenter);
            Epsilon.row = 0;
            Epsilon.col = 0;

            ui->gridLayout_9->addWidget(Epsilon.qLineEdit,Epsilon.row,Epsilon.col,Qt::Alignment());

            for(size_t i = 0; i < 2; i++){
                Elem elem_B;

                elem_B.qLineEdit = new  QLineEdit;
                elem_B.qLineEdit->setAlignment(Qt::AlignHCenter);

                ui->horizontalSpacer_4->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_4->geometry().height());
                ui->horizontalSpacer_5->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_5->geometry().height());

                elem_B.row = 0;
                elem_B.col = i;

                qElem_s_2.push_back(elem_B);

                ui->gridLayout_6->addWidget(elem_B.qLineEdit,elem_B.row,elem_B.col,Qt::Alignment());
            }

            for(size_t i = 0; i < 2; i++){
                Elem elem_C;

                elem_C.qLineEdit = new  QLineEdit;
                elem_C.qLineEdit->setAlignment(Qt::AlignHCenter);

                ui->horizontalSpacer_8->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_8->geometry().height());
                ui->horizontalSpacer_9->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_9->geometry().height());

                elem_C.row = 0;
                elem_C.col = i;

                qElem_s_3.push_back(elem_C);

                ui->gridLayout_12->addWidget(elem_C.qLineEdit, elem_C.row, elem_C.col,Qt::Alignment());
            }

        for(size_t i = 0; i < arg1*2+2; i+=1){

             Elem elem;

             ui->horizontalSpacer_1->changeSize(50,ui->horizontalSpacer_1->geometry().height());
             ui->horizontalSpacer_2->changeSize(1000/((i+2)),ui->horizontalSpacer_2->geometry().height());

             elem.qLineEdit = new  QLineEdit;
             elem.qLineEdit->setAlignment(Qt::AlignHCenter);
             elem.qLabel = new QLabel;
             elem.qLabel->setTextFormat(Qt::RichText);

             QFont newFont("Times New Roman", 12, QFont::Times, true);

              elem.qLabel->setFont(newFont);

              /*if(i < arg1*2){
                  elem.qLabel->setText("<html><head/><body><p>x<span style=\" vertical-align:super;\">"+ QString::number(arg1 - i/2)+"</span>+</p></body></html>");
              }else{
                  elem.qLabel->setText("<html><head/><body><p>x<span style=\" vertical-align:super;\">"+ QString::number(arg1 - i/2)+"</span></p></body></html>");
              }*/

             elem.row = i / 2;
             elem.col = i % 2;

             //elem.lrow = i % 2;
             //elem.lcol = 1;

             qElem_s_1.push_back(elem);

             ui->gridLayout_3->addWidget(elem.qLineEdit,elem.row,elem.col,Qt::Alignment());

             if(i/2 == 0){
                 switch(i % 2){
                 case(0):
                         elem.qLineEdit->setText("x");
                     break;
                 default:// 1;
                        elem.qLineEdit->setText("y");
                     break;
                 }
             }
             //ui->gridLayout_3->addWidget(elem.qLabel,elem.lrow,elem.lcol,Qt::Alignment());
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QTime start_1 = QTime::currentTime();

    ui->textBrowser_1->clear();

    this->CN = ui->spinBox_1->value();

    QString strHtml_A;

    if(qElem_s_1.count() > 0){
        A = QVector<QVector<double>>(CN, QVector<double>(2,0));
        strHtml_A.append("<b style=\"color: red;\">Принятые данные </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>A :</b><table border=1 style=\"border-collapse: collapse;\">");
        for(size_t i = 2; i < CN*2+2; i+=2){
            if (i==2){
                strHtml_A.append("<tr>");
                strHtml_A.append("<td align=center> " + qElem_s_1[i-2].qLineEdit->text() + " </td>");
                strHtml_A.append("<td align=center> " + qElem_s_1[i-1].qLineEdit->text() + " </td>");
                strHtml_A.append("</tr>");
            }
            strHtml_A.append("<tr>");
                strHtml_A.append("<td align=center> " + qElem_s_1[i].qLineEdit->text() + " </td>");
                strHtml_A.append("<td align=center> " + qElem_s_1[i+1].qLineEdit->text() + " </td>");
                A[(i-2)/2][0] = qElem_s_1[i].qLineEdit->text().toDouble();
                A[(i-2)/2][1] = qElem_s_1[i+1].qLineEdit->text().toDouble();
                strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
    }

    if(qElem_s_2.count() > 0){
        B = QVector<double>(2, 0);
        strHtml_A.append("<b>X_N:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 2; i++){
                strHtml_A.append("<td align=center> " + qElem_s_2[i].qLineEdit->text() + " </td>");
                B[i] = qElem_s_2[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    if(qElem_s_3.count() > 0){
        E = QVector<double>(2, 0);
        strHtml_A.append("<b>X_L :</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 2; i++){
                strHtml_A.append("<td align=center> " + qElem_s_3[i].qLineEdit->text() + " </td>");
                E[i] = qElem_s_3[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");

    //double eps = Epsilon.qLineEdit->text().toDouble();

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Точность :</b> ε = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    ////////////////////////////////////////////////

    ////////////////////////////////////////////////
    int Ga,  Gb;
    double step_a, step_b;

    auto print_general = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table align=center border=1 style=\"border-collapse: collapse;\">");

        if (vec.count() == 2) strHtml_A.append("<tr><td align=center> x </td><td align=center> y </td></tr>" );
        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f', 6) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_o = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Ответ </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>Y :</b><table align=center border=1 style=\"border-collapse: collapse;\">");

        strHtml_A.append("<tr><td align=center> x </td><td align=center> y </td></tr>" );
        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f', 6) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_N = [&](QVector<QVector<double>>& vec, QVector<double>& c) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: green;\">Предварительное выделение элементов для И. Ф. N. с неравноотстающими узлами </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table align=center border=1 style=\"border-collapse: collapse;\">");

        strHtml_A.append("<tr><td align=center> x </td>"
                         "<td align=center> y </td>"
                         "<td align=center> [x<sub>0</sub> ; x<sub>1</sub>] </td>"
                         "<td align=center> [x<sub>0</sub> ; x<sub>1</sub> ; x<sub>2</sub>] </td>"
                         "<td align=center> [x<sub>0</sub> ; x<sub>1</sub> ; x<sub>2</sub> ; x<sub>3</sub>] </td>"
                         "<td align=center> [x<sub>0</sub> ; x<sub>1</sub> ; x<sub>2</sub> ; x<sub>3</sub> ; x<sub>4</sub>] </td>"
                         "<td align=center> [x<sub>0</sub> ; x<sub>1</sub> ; x<sub>2</sub> ; x<sub>3</sub> ; x<sub>4</sub> ; x<sub>5</sub>] </td>"
                         "<td align=center> [x<sub>0</sub> ; x<sub>1</sub> ; x<sub>2</sub> ; x<sub>3</sub> ; x<sub>4</sub> ; x<sub>5</sub> ; x<sub>6</sub>] </td>"
                         "<td align=center> [x<sub>0</sub> ; x<sub>1</sub> ; x<sub>2</sub> ; x<sub>3</sub> ; x<sub>4</sub> ; x<sub>5</sub> ; x<sub>6</sub> ; x<sub>7</sub>] </td>"
                         "<td align=center> [x<sub>0</sub> ; x<sub>1</sub> ; x<sub>2</sub> ; x<sub>3</sub> ; x<sub>4</sub> ; x<sub>5</sub> ; x<sub>6</sub> ; x<sub>7</sub> ; x<sub>8</sub>] </td></tr>");

        for(size_t i = 0; i < CN; i++){
            strHtml_A.append("<tr>");
            for(size_t j = 0; j < vec[i].count(); j++){
                if(i == 0 && j > 0){
                   vec[i][j] == 0 ? strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',0) + "</b></td>")
                                  : strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',3) + "</b></td>");
                   c.push_front(vec[i][j]);
                }else{
                    vec[i][j] == 0 ? strHtml_A.append("<td align=center> " + QString::number(vec[i][j]) + " </td>")
                                   : strHtml_A.append("<td align=center> " + QString::number(vec[i][j],'f',3) + " </td>");
                }
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    print_general(A);

    auto Duble_A = A;

    auto general_i = [&]() -> void {
        size_t n = 3;
        auto FL = [CN = CN] (QVector<QVector<double>> NewVec, size_t N, double EPS) -> bool {
            bool FLAG = false;
            for(size_t i = 0; i < CN; i++){
                    FLAG = (abs(NewVec[i][N-1]) > EPS) ? (true) : ((FLAG == true) ? (true) : (false));
            }
            return FLAG;
        };

        auto general = [&](auto GEN, int64_t N, QVector<QVector<double>>& A, QVector<double>& C) -> void {
            QVector<QVector<double>> newVec(CN,QVector<double>(N, 0));
            for(size_t i = 0; i < CN; i++){// Копирование данных из А в newVec.
                for(size_t j = 0; j < A[i].count(); j++){
                    newVec[i][j] = A[i][j];
                }
            }

            auto razd_raznost = [](auto r,QVector<QVector<double>>& A,int64_t K, int64_t i) -> double {
                return (A[i + 1][K - 1] - A[i][K - 1])/((A[i + K - 1][0] - A[i][0]));
            };

            for(size_t i = 0; i < CN - (N - 2); i++){
                newVec[i][N - 1] = razd_raznost(razd_raznost, A, N - 1, i);
            }

            //print_general(newVec);// print all iteration's;

            if((N <= CN)){// FL(newVec, N, eps) &&
                GEN(GEN, N + 1, newVec, D);
            }else{

                // 1. Интерполяционный многочлен Ньютона.
                {
                    print_general_N(newVec, D);// print one, end iteration;
                    Y = QVector<QVector<double>>(B[1] - B[0] + 1, QVector<double>(2, 0));

                    auto P_n = [D = D, A = A](auto P_n, double x, uint32_t i = 0) -> double {

                        if(i > D.count()) return 0;

                        auto R = [A = A](auto r, double x, uint32_t i) -> double {
                            if (i == 1) return 1;
                            return (x - A[i - 2][0])*r(r, x, i - 1);
                        };

                        if (i == 0){
                            return D[D.count() - 1] + P_n(P_n, x, i + 2);
                        }else{
                            //qDebug() << "i: " << i <<  ";   R: " << R(R, x, i) << "; \n";
                            return D[D.count() - i]*R(R, x, i) + P_n(P_n, x, i + 1);
                        }
                    };

                    for(int i = B[0]; i <= B[1]; i++){

                        double x = 0.609 + 0.002*i;
                        double y = P_n(P_n, x);

                        Y[i - B[0]][0] = x;
                        Y[i - B[0]][1] = y;
                    }

                    print_general_o(Y);
                //P_n(P_n, );
                }

                // 2. интерполяционный многочлен лагранжа.
                {
                    print_general(Duble_A);

                    W = QVector<QVector<double>>(Duble_A.count(),QVector<double>(3, 0));
                    for(size_t i = 0; i < Duble_A.count(); i++){
                        for(size_t j = 1; j < 3; j++){
                            W[i][j] = Duble_A[i][j - 1];
                        }
                    }

                    print_general(W);

                    auto P_n_L = [W = Duble_A](auto P_n_L, double x, int32_t i = 0) -> double {

                        if(i >= W.count()) return 0;

                        auto Z = [](auto z, double x, QVector<QVector<double>> W, int32_t i, int32_t j = 0) -> double {
                            if(i == j){
                                return z(z, x, W, i, j + 1);
                            }else if(i >= W.count() || j >= W.count()){
                                return 1;
                            }else {

                                return(x - W[j][0])/(W[i][0] - W[j][0])*z(z, x, W, i , j + 1);
                            }
                        };

                        //qDebug() << "i: "<< i << ";   Coef: " << Z(Z, x, W, i) << "\n";

                        return W[i][1]*Z(Z, x, W, i) + P_n_L(P_n_L, x, i + 1);
                    };

                    P = QVector<QVector<double>>(E[1] - E[0] + 1, QVector<double>(2, 0));

                    for(int i = E[0]; i <= E[1]; i++){

                        double x = 0.629 + 0.003*i;
                        double y = P_n_L(P_n_L, x);

                        P[i - E[0]][0] = x;
                        P[i - E[0]][1] = y;
                    }

                    print_general_o(P);

                }
            }

        };
        general(general, n, A, C);
    };
    general_i();

    ////////////////////////////////////////////////
    //ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Номер варианта:</b> N = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    QTime finish = QTime::currentTime();
    double time = start_1.msecsTo(finish) / 1000.0;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<hr>" + "<b>Время работы: </b> " +  QString::number(time) + " ;");

}
