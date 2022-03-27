#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, (&MainWindow::func));

    ui->spinBox_1->setValue(15);

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
            1.50, 15.132,
            1.55, 17.422,
            1.60, 20.393,
            1.65, 23.994,
            1.70, 28.160,
            1.75, 32.812,
            1.80, 37.857,
            1.85, 43.189,
            1.90, 48.689,
            1.95, 54.225,
            2.00, 59.158,
            2.05, 64.817,
            2.10, 69.550,
            2.15, 74.782,
            2.20, 79.548}; // f(x)

        size_t N = 12;
        //double x_0=0.1485-0.002*N;

        double vecS[3] = {1.6 + 0.006*N, 1.725 + 0.002*N, 1.83 + 0.003*N}; //Segment

        double eps = 0.00001;

        if((qElem_s_1.count()) == CN*2+2){

            for (size_t i = 2; i < qElem_s_1.count(); i+=1){

                qElem_s_1[i].qLineEdit->setText(QString::number(vecF[(i-2) / 2][(i-2) % 2],'f',2+i%2));
                //qElem_s_1[i+1].qLineEdit->setText(QString::number(vecF[i][1]));
            }

            qElem_s_2[0].qLineEdit->setText(QString::number(vecS[0],'f',3));
            qElem_s_2[1].qLineEdit->setText(QString::number(vecS[1],'f',3));
            qElem_s_2[2].qLineEdit->setText(QString::number(vecS[2],'f',3));
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

            for(size_t i = 0; i < 3; i++){
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
        B = QVector<double>(3, 0);
        strHtml_A.append("<b>X_G,  X_S,  X_B :</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 3; i++){
                strHtml_A.append("<td align=center> " + qElem_s_2[i].qLineEdit->text() + " </td>");
                B[i] = qElem_s_2[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");

    double eps = Epsilon.qLineEdit->text().toDouble();

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Точность :</b> ε = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    ////////////////////////////////////////////////
    int Ga,  Gb;
    double step_a, step_b;

    auto print_general = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");


        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',3) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_G_1 = [&](QVector<QVector<double>>& vec, size_t Ga, QVector<double>& c) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: green;\">Предварительное выделение элементов для 1 И. Ф. G. </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        for(int i = 0; i < CN; i++){
            strHtml_A.append("<tr>");
            for(int j = 0; j < vec[i].count(); j++){

                qDebug() << (double)j;
                qDebug() << (double)(2*Ga + 4 - 2*i)/3;

                if((((double)j == ((double)(2*Ga + 4 - 2*i)/3) and (j % 2 == 0) || ((double)j == (double)(Ga - (double)(2*(i))/3)) and (j % 2 == 1)) && (i <= Ga)) || (i == Ga && (j == 0 || j == 1)) ){//((j == (2*Ga + 1) - 2*i || j == (2*Ga + 2) - 2*i) && (i <= Ga)) || (i == Ga && (j == 0 || j == 1))
                   vec[i][j] == 0 ? strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',0) + "</b></td>")
                                  : strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',3) + "</b></td>");
                   if (j != 0 && i == 0){
                       c.push_front(vec[i][j]);
                   }else if(i > 0 && j != 0){
                       static QVector<double> st;
                       st.push_front(vec[i][j]);
                       if(st.count() == 2){
                           std::copy(st.begin(), st.end(), std::back_inserter(c));
                           st.clear();
                       }
                   }
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

    auto print_general_S = [&](QVector<QVector<double>>& vec, size_t Ga, QVector<double>& c) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: green;\">Предварительное выделение элементов для  И. Ф. C. </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        for(size_t i = 0; i < CN; i++){
            strHtml_A.append("<tr>");
            for(size_t j = 0; j < vec[i].count(); j++){
                if((((j % 2 == 0) && (j != 0)) && ( i == (Ga + 1 - 3*j/2) || i == (2*Ga + 4 - 3*j)/2 )) ||
                        ((j % 2 == 1) && ( i == (2*Ga+3*(1 - j))/2 ))){
                   vec[i][j] == 0 ? strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',0) + "</b></td>")
                                  : strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',3) + "</b></td>");
                   if (j != 0 && i == 0){
                       c.push_back(vec[i][j]);
                   }else if(i > 0 && j != 0){
                       c.push_back(vec[i][j]);
                   }
                }else{
                    i == Ga && j == 0
                        ? strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',3) + "</b></td>")
                        : vec[i][j] == 0
                          ? strHtml_A.append("<td align=center> " + QString::number(vec[i][j]) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(vec[i][j],'f',3) + " </td>");
                }
            }

            strHtml_A.append("</tr>");
        }

        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_B_1 = [&](QVector<QVector<double>>& vec, size_t Ga, QVector<double>& c) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: green;\">Предварительное выделение элементов для  И. Ф. В. </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        for(size_t i = 0; i < CN; i++){
            strHtml_A.append("<tr>");
            for(size_t j = 0; j < vec[i].count(); j++){
                if( (((j % 2 == 1) && (j != 0)) && ( i == ( (2*Ga + 3*(1 - j))/2 ) || i == (2*Ga + 5 - 3*j)/2 ))
                        || ( ((j % 2 == 0) && (j != 0)) && ( i == ((2*(Ga + 2) - 3*j)/2 ) ))
                        ){
                   vec[i][j] == 0 ? strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',0) + "</b></td>")
                                  : strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',3) + "</b></td>");
                   if (j != 0 && i == 0){
                       c.push_back(vec[i][j]);
                   }else if(i > 0 && j != 0){
                       c.push_back(vec[i][j]);
                   }
                }else{
                    i == Ga && j == 0
                        ? strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',3) + "</b></td>")
                        : vec[i][j] == 0
                          ? strHtml_A.append("<td align=center> " + QString::number(vec[i][j]) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(vec[i][j],'f',3) + " </td>");
                }
            }

            strHtml_A.append("</tr>");
        }

        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    print_general(A);

    auto general_i = [&]() -> void {
        size_t n = 3;
        auto FL = [CN = CN] (QVector<QVector<double>> NewVec, size_t N, double EPS) -> bool {
            bool FLAG = false;
            for(size_t i = 0; i < CN; i++){
                    FLAG = (abs(NewVec[i][N-1]) > EPS) ? (true) : ((FLAG == true) ? (true) : (false));
            }
            return FLAG;
        };

        auto general = [&](auto GEN, int64_t N, QVector<QVector<double>> A, QVector<double>& C) -> void {
            QVector<QVector<double>> newVec(CN,QVector<double>(N, 0));
            for(size_t i = 0; i < CN; i++){
                for(size_t j = 0; j < A[i].count(); j++){
                    newVec[i][j]=A[i][j];
                }
            }

            for(size_t i = 0; i < CN - (N - 2); i++){
                newVec[i][N - 1] = (double)(newVec[i + 1][N - 2] - newVec[i][N - 2]);
            }

            //print_general(newVec);// print all iteration's;

            if( FL(newVec, N, eps) && (N <= CN)){
                GEN(GEN, N + 1, newVec, C);
            }else{
                print_general(newVec);// print one, end iteration;

                // I И. Ф. Г.:
                {
                    // #:
                    for(size_t i = 0; i < CN; i++){
                        if(i == 0){
                            step_a = abs(A[i][0] - B[0]);
                            Ga = i;
                        }else if ( (step_a > (A[i][0] - B[0]))  && (A[i][0] <= B[0])){
                            step_a = abs(A[i][0] - B[0]);
                            Ga = i;
                        }

                        if(i == 0){
                            step_b = abs(A[(CN-1)][0] - B[0]);
                            Gb = (CN - 1);
                        }else if ( (step_b > (A[(CN-1) - i][0] - B[0])) && (A[(CN-1) - i][0] >= B[0])){
                            //qDebug() << step_b;
                            step_b = abs(A[(CN-1) - i][0] - B[0]);
                            Gb = (CN-1) - i;
                        }
                    }

                    //qDebug() << Ga;
                    //qDebug() << Gb;

                    print_general_G_1(newVec, Ga, C);
                    if((!C.empty()) && (C[C.count() - 1] == A[Ga][1])){
                            QString strHtml;
                            strHtml.clear();
                            strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                            strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(B[0]) + "; ");
                            strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(A[Ga][0]) + "; ");
                            strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(newVec[1][0] - newVec[0][0]) + "; ");
                                double q = (B[0] - A[Ga][0]) / (newVec[1][0] - newVec[0][0]);
                            strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(B[0]) + " - "
                                + QString::number(A[Ga][0]) + " )/ " + QString::number(newVec[1][0] - newVec[0][0])
                                + " = " + QString::number(q) + "; ");
                        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                            strHtml.clear();
                            strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");

                         auto P_n = [&]() -> double {
                              auto ITER = [&](auto iter, size_t i) -> double {
                                  if(i >= C.count() - 1/*COLUMN: y;*/ ) return 0;
                                  auto factorial = [](auto fact, size_t i) -> double {
                                      return (i == 1 || i == 0) ? i/*База факториала*/ : i*fact(fact, i - 1);
                                  };
                                  auto Q = [&](auto Q, size_t i) -> double {
                                     return  (i == 0) ? q
                                                      : (i % 2 == 0) ? (q + (i / 2)) * Q(Q, i - 1)
                                                                     : (q - ((i + 1) / 2)) * Q(Q, i - 1);
                                  };
                                  return C[C.count() - 1 - i] * Q(Q, i - 1) / factorial(factorial, i) + iter(iter, i + 1);
                              };
                              return C[C.count() - 1] + ITER(ITER, 1);
                          };

                        switch(C.count() - 1/*COLUMN: y;*/){
                         case(3):
                             strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: y;*/) + "</sub>(x = " + QString::number(B[0]) + ") "
                                            "= " + QString::number(P_n(), 'f', 6) + " ; ");
                             C.clear();
                             break;
                         case(2):
                             strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: x, y;*/)+ "</sub>(x = " + QString::number(B[0]) + ") = " + QString::number(P_n(), 'f', 6) + " ; ");
                             C.clear();
                             break;
                         case(1):
                             strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: x, y;*/)+ "</sub>(x = " + QString::number(B[0]) + ") = " + QString::number(P_n(), 'f', 6) + " ; ");
                             C.clear();
                             break;
                         default:
                             strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: y;*/) + "</sub>(x = " + QString::number(B[0]) + ") "
                                            "= " + QString::number(P_n(), 'f', 6) + " ; ");
                             C.clear();
                             break;
                         };
                         ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                    }
                    // #;
                }

                // И. Ф. C.:
                {
                    // #:
                    for(size_t i = 0; i < CN; i++){
                        if(i == 0){
                            step_a = abs(A[i][0] - B[1]);
                            Ga = i;
                        }else if ( (step_a > (A[i][0] - B[1]))  && (A[i][0] <= B[1])){
                            step_a = abs(A[i][0] - B[1]);
                            Ga = i;
                        }

                        if(i == 0){
                            step_b = abs(A[(CN-1)][0] - B[1]);
                            Gb = (CN - 1);
                        }else if ( (step_b > (A[(CN-1) - i][0] - B[1])) && (A[(CN-1) - i][0] > B[1])){
                            //qDebug() << step_b;
                            step_b = abs(A[(CN-1) - i][0] - B[1]);
                            Gb = (CN-1) - i;
                        }
                    }

                    //qDebug() << Ga;
                    //qDebug() << Gb;

                    print_general_S(newVec, Ga, C);
                    if((!C.empty()) && (C[C.count() - 1] == A[Ga][1])){
                        QString strHtml;
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                        strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(B[1]) + "; ");
                        strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(A[Ga][0]) + "; ");
                        strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(newVec[1][0] - newVec[0][0]) + "; ");
                            double q = (B[1] - A[Ga][0]) / (newVec[1][0] - newVec[0][0]);
                        strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(B[1]) + " - "
                            + QString::number(A[Ga][0]) + " )/ " + QString::number(newVec[1][0] - newVec[0][0])
                            + " = " + QString::number(q) + "; ");
                    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");

                     auto P_n = [&]() -> double {
                          auto ITER = [&](auto iter, size_t i) -> double {
                              if(i >= C.count() - 2/*COLUMN: y;*/ ) return 0;
                              auto factorial = [](auto fact, size_t i) -> double {
                                  return (i == 1 || i == 0) ? i/*База факториала*/ : i*fact(fact, i - 1);
                              };

                              static int STEP = 0;
                              auto Q = [&](auto Q, size_t i) -> double {
                                  int ST = STEP;
                                  double B_0 = q - STEP;
                                  double  B_1 = q + STEP;

                                  if(i == 1){
                                      return B_0;
                                  }else if(i % 2 == 0){
                                      double V_1 = B_1;
                                      double sa = V_1*Q(Q, i - 1);
                                      return sa;
                                  }else{
                                      double V_0 = B_0;
                                      STEP++;
                                      return V_0*Q(Q, i - 1);
                                  }
                              };
                              STEP = 0;

                              /*for(size_t k = 1; k < 10; k++){
                                  qDebug() << "k = " << k << "; " << "Q(k) = " << Q(Q, k);
                                  STEP = 0;
                              }*/

                              if(i % 3 != 0){
                                  qDebug() << "i: " << (2*i + 1)/3 << "STEP: " << STEP << "C_L: " << C[C.count() - 1 - i]  << "C_R: " << C[C.count() - 2 - i] << ";";
                                  int f = factorial(factorial, (2*i + 1)/3);
                                  double qr = Q(Q, (2*i + 1)/3);
                                  qDebug() << "factor(i): " << f << " Q(i): " << QString::number(qr);
                                  STEP = 0;
                                  return (C[C.count() - 1 - i] + C[C.count() - 2 - i]) * Q(Q, (2*i + 1)/3) / 2*factorial(factorial, (2*i + 1)/3) + iter(iter, i + 2);
                              }else{
                                  qDebug() << "i: " << 2*i/3 << "; STEP:" << STEP << "C: " << C[C.count() - 1 - i] ;
                                   int f = factorial(factorial, (2*i + 1)/3);
                                   double qr = Q(Q, 2*i/3);
                                   qDebug() << "factor(i): " << f << " Q(i): " << QString::number(qr);
                                   STEP = 0;
                                  //qDebug() << "; factor(i):" << factorial(factorial, (2*i + 1)/3) << "; Q(i):"  << Q(Q, 2*i/3) << ";\n";
                                  return (C[C.count() - 1 - i] + 0) * Q(Q, 2*i/3) / factorial(factorial,  2*i/3) + iter(iter, i + 1);
                              }

                              //qDebug() << C.count();
                          };
                          return C[C.count() - 1] + ITER(ITER, 1);
                      };

                    switch(C.count() - 1/*COLUMN: y;*/){
                     case(3):
                         strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(C.count() - 2/*COLUMN: y;*/) + "</sub>(x = " + QString::number(B[1]) + ") "
                                        "= " + QString::number(P_n(), 'f', 6) + " ; ");
                         C.clear();
                         break;
                     case(2):
                         strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: x, y;*/)+ "</sub>(x = " + QString::number(B[1]) + ") = " + QString::number(P_n(), 'f', 6) + " ; ");
                         C.clear();
                         break;
                     case(1):
                         strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: x, y;*/)+ "</sub>(x = " + QString::number(B[1]) + ") = " + QString::number(P_n(), 'f', 6) + " ; ");
                         C.clear();
                         break;
                     default:
                         strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(C.count() - 2/*COLUMN: y;*/) + "</sub>(x = " + QString::number(B[1]) + ") "
                                        "= " + QString::number(P_n(), 'f', 6) + " ; ");
                         C.clear();
                         break;
                     };
                     ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");

                    }
                    // #;
                 }

                // И. Ф. B.:
                {
                    // #:
                    for(size_t i = 0; i < CN; i++){
                        if(i == 0){
                            step_a = abs(A[i][0] - B[2]);
                            Ga = i;
                        }else if ( (step_a > (A[i][0] - B[2]))  && (A[i][0] <= B[2])){
                            step_a = abs(A[i][0] - B[2]);
                            Ga = i;
                        }

                        if(i == 0){
                            step_b = abs(A[(CN-1)][0] - B[2]);
                            Gb = (CN - 1);
                        }else if ( (step_b > (A[(CN-1) - i][0] - B[2])) && (A[(CN-1) - i][0] > B[2])){
                            //qDebug() << step_b;
                            step_b = abs(A[(CN-1) - i][0] - B[2]);
                            Gb = (CN - 1) - i;
                        }
                    }

                    qDebug() << Ga;
                    qDebug() << Gb;

                    print_general_B_1(newVec, Ga, C);
                    if((!C.empty()) && (C[C.count() - 2] == A[Ga][1])){
                        QString strHtml;
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                        strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(B[2]) + "; ");
                        strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(A[Ga][0]) + "; ");
                        strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(newVec[1][0] - newVec[0][0]) + "; ");
                            double q = (B[2] - A[Ga][0]) / (newVec[1][0] - newVec[0][0]);
                        strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(B[2]) + " - "
                            + QString::number(A[Ga][0]) + " )/ " + QString::number(newVec[1][0] - newVec[0][0])
                            + " = " + QString::number(q) + "; ");
                    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");

                     auto P_n = [&]() -> double {
                          auto ITER = [&](auto iter, size_t i) -> double {
                              if(i >= C.count() - 2/*COLUMN: y;*/ ) return 0;
                              auto factorial = [](auto fact, size_t i) -> double {
                                  return (i == 1 || i == 0) ? i/*База факториала*/ : i*fact(fact, i - 1);
                              };

                              static int STEP = 0;
                              auto Q = [&](auto Q, size_t i) -> double {
                                  int ST = STEP;
                                  double B_0 = q - STEP;
                                  double  B_1 = q + STEP;

                                  if(i == 1){
                                      return B_0;
                                  }else if(i % 2 == 0){
                                      double V_1 = B_1;
                                      double sa = V_1*Q(Q, i - 1);
                                      return sa;
                                  }else{
                                      double V_0 = B_0;
                                      STEP++;
                                      return V_0*Q(Q, i - 1);
                                  }
                              };
                              STEP = 0;

                              /*for(size_t k = 1; k < 10; k++){
                                  qDebug() << "k = " << k << "; " << "Q(k) = " << Q(Q, k);
                                  STEP = 0;
                              }*/

                              if(i % 3 != 0){
                                  qDebug() << "i: " << (2*i + 1)/3 << "STEP: " << STEP << "C_L: " << C[C.count() - 1 - i]  << "C_R: " << C[C.count() - 2 - i] << ";";
                                  int f = factorial(factorial, (2*i + 1)/3);
                                  double qr = Q(Q, (2*i + 1)/3);
                                  qDebug() << "factor(i): " << f << " Q(i): " << QString::number(qr);
                                  STEP = 0;
                                  return (C[C.count() - 1 - i] + C[C.count() - 2 - i]) * Q(Q, (2*i + 1)/3) / 2*factorial(factorial, (2*i + 1)/3) + iter(iter, i + 2);
                              }else{
                                  qDebug() << "i: " << 2*i/3 << "; STEP:" << STEP << "C: " << C[C.count() - 1 - i] ;
                                   int f = factorial(factorial, (2*i + 1)/3);
                                   double qr = Q(Q, 2*i/3);
                                   qDebug() << "factor(i): " << f << " Q(i): " << QString::number(qr);
                                   STEP = 0;
                                  //qDebug() << "; factor(i):" << factorial(factorial, (2*i + 1)/3) << "; Q(i):"  << Q(Q, 2*i/3) << ";\n";
                                  return (C[C.count() - 1 - i] + 0) * Q(Q, 2*i/3) / factorial(factorial,  2*i/3) + iter(iter, i + 1);
                              }

                              //qDebug() << C.count();
                          };
                          return (C[C.count() - 1] + C[C.count() - 2])/2 + ITER(ITER, 2);
                      };

                    switch(C.count() - 1/*COLUMN: y;*/){
                     case(3):
                         strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: y;*/) + "</sub>(x = " + QString::number(B[2]) + ") "
                                        "= " + QString::number(P_n(), 'f', 6) + " ; ");
                         C.clear();
                         break;
                     case(2):
                         strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: x, y;*/)+ "</sub>(x = " + QString::number(B[2]) + ") = y<sub>0</sub> "
                                        "+ q*Δy<sub>0</sub> + q(q-1)/2! * Δ<sup>2</sup>y<sub>0</sub> "
                                        " </b> = " + QString::number(P_n(), 'f', 6) + " ; ");
                         C.clear();
                         break;
                     case(1):
                         strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: x, y;*/)+ "</sub>(x = " + QString::number(B[2]) + ")  = " + QString::number(P_n(), 'f', 6) + " ; ");
                         C.clear();
                         break;
                     default:
                         strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(C.count() - 2/*COLUMN: y;*/) + "</sub>(x = " + QString::number(B[2]) + ") "
                                        "= " + QString::number(P_n(), 'f', 6) + " ; ");
                         C.clear();
                         break;
                     };
                     ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");

                    }

                    // #;
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
