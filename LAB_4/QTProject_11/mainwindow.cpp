#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, (&MainWindow::func));

    ui->spinBox_1->setValue(13);

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
            0.101, 1.26183,
            0.106, 1.27644,
            0.111, 1.29122,
            0.116, 1.30617,
            0.121, 1.32130,
            0.126, 1.33660,
            0.131, 1.35207,
            0.136, 1.36773,
            0.141, 1.38357,
            0.146, 1.39959,
            0.151, 1.41579,
            0.156, 1.42683,
            0.161, 1.43356}; // f(x)

        size_t N=12;
        double x_0=0.1485-0.002*N;

        double vecS[2] = {1, 3}; //Segment

        double eps = 0.00001;

        if((qElem_s_1.count()) == CN*2+2){

            for (size_t i = 2; i < qElem_s_1.count(); i+=1){

                qElem_s_1[i].qLineEdit->setText(QString::number(vecF[(i-2) / 2][(i-2) % 2]));
                //qElem_s_1[i+1].qLineEdit->setText(QString::number(vecF[i][1]));
            }

            qElem_s_2[0].qLineEdit->setText(QString::number(x_0));
            //qElem_s_2[1].qLineEdit->setText(QString::number(vecS[1]));
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

            for(size_t i = 0; i < 1; i++){
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
        B = QVector<double>(1, 0);
        strHtml_A.append("<b>X_0 :</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 1; i++){
                strHtml_A.append("<td align=center> " + qElem_s_2[i].qLineEdit->text() + " </td>");
                B[i] = qElem_s_2[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");

    double eps = Epsilon.qLineEdit->text().toDouble();

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Номер варианта:</b> N = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    ////////////////////////////////////////////////

    // Определение границ элемента x  в матрицы А относительно строк.
    int Ga,  Gb;
    double step_a, step_b;
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

    // Метод вывода данных из матриц.
    auto print_general = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',6) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    switch(Gb - Ga){
    case(1):
        while(Ga != 0){
            A.removeFirst();
            Ga--; Gb--; CN--;
        }

        qDebug() << Ga;
        qDebug() << Gb;

        break;
    default:
        break;
    }

    print_general(A);

    auto print_general_N_1 = [&](QVector<QVector<double>>& vec, size_t Ga, QVector<double>& c) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: green;\">Предварительное выделение элементов для 1 И. Ф. Н. </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        for(size_t i = 0; i < CN; i++){
            strHtml_A.append("<tr>");
            for(size_t j = 0; j < vec[i].count(); j++){
                if(i == Ga){
                   vec[i][j] == 0 ? strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',0) + "</b></td>")
                                  : strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',5) + "</b></td>");
                   c.push_front(vec[i][j]);
                }else{
                    vec[i][j] == 0 ? strHtml_A.append("<td align=center> " + QString::number(vec[i][j]) + " </td>")
                                   : strHtml_A.append("<td align=center> " + QString::number(vec[i][j],'f',5) + " </td>");
                }
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto general_i = [&]() -> void {
        size_t n = 3;
        auto FL = [CN = CN] (QVector<QVector<double>> NewVec, size_t N, double EPS) -> bool {
            bool FLAG = false;
            for(size_t i = 0; i < CN; i++){
                    FLAG = (abs(NewVec[i][N-1]) > EPS) ? (true) : ((FLAG == true) ? (true) : (false));
            }
            return FLAG;
        };

        uint64_t COUNT_R = 0;

        auto general = [&,CN = CN, print_general = print_general, eps = eps, FL = FL, ui=ui, B=B, print_general_N_1=print_general_N_1](auto GEN, int64_t N, QVector<QVector<double>> A) -> void {
            QVector<QVector<double>> newVec(CN,QVector<double>(N, 0));
            for(size_t i = 0; i < CN; i++){
                for(size_t j = 0; j < A[i].count(); j++){
                    newVec[i][j] = A[i][j];

                    if(j == 1){
                        uint64_t COUNT = 0;
                        std::string number = std::to_string(A[i][j]);//A[i][j]
                        number = number.substr(0, number.find_last_not_of('0')); // Убираем последние нули
                        size_t dotFound;
                        std::stoi(number, &dotFound);

                        COUNT = std::string(number).substr(dotFound).size();

                        if(COUNT > COUNT_R){
                            COUNT_R = COUNT;
                        }
                    }
                }
            }

            bool FLAG = true;

            for(size_t i = 0; i < CN - (N - 2); i++){
                newVec[i][N-1] = (double)(newVec[i+1][N - 2] - newVec[i][N - 2]);

                uint64_t COUNT = 0;
                std::string number = std::to_string(newVec[i][N - 1]);
                number = number.substr(0, number.find_last_not_of('0')); // Убираем последние нули;
                size_t dotFound;
                std::stoi(number, &dotFound);

                COUNT = std::string(number).substr(dotFound).size();

                double x = newVec[i][N - 1] - floor(newVec[i][N - 1]);

                double fractpart,                   // дробная часть
                       intpart;                     // целая часть

                fractpart = modf( newVec[i][N - 1], &intpart);
                fractpart = QString::number(fractpart, 'f', COUNT_R).toDouble();

                double f = QString::number(fractpart, 'f', COUNT_R - 1).toDouble();
                double f_i = fractpart - f;

                if(fractpart - f_i != 0){
                    FLAG = false;
                }
            }

            //print_general(newVec);// print all iteration's;

            if( FL(newVec, N, eps) && (N <= CN) && !FLAG){
                GEN(GEN, N + 1, newVec);
            }else{
                print_general(newVec);// print one, end iteration;
                print_general_N_1(newVec, Ga, X);

                QString strHtml;
                strHtml.clear();
                strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(B[0]) + "; ");
                strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(newVec[0][0]) + "; ");
                strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(newVec[1][0] - newVec[0][0]) + "; ");
                double q = (B[0] - newVec[0][0]) / (newVec[1][0] - newVec[0][0]);
                strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(B[0]) + " - " + QString::number(newVec[0][0]) + " )/ " + QString::number(newVec[1][0] - newVec[0][0])
                        + " = " + QString::number(q) + "; ");
                ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");

                strHtml.clear();
                strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                //strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(B[0]) + "; ");
                //strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(newVec[0][0]) + "; ");
                //strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(newVec[1][0] - newVec[0][0]) + "; ");
                //double q = (B[0] - newVec[0][0]) / (newVec[1][0] - newVec[0][0]);

                auto P_n = [&]() -> double {

                    auto ITER = [&](auto iter, size_t i) -> double {

                        if(i >= newVec[0].count() - 2/*COLUMN: x, y;*/ ){
                            return 0;
                        }

                        auto factorial = [](auto fact, size_t i) -> double {
                            return (i == 1 || i == 0) ? i/*База факториала*/ : i*fact(fact, i - 1);
                        };

                        auto Q = [&](auto Q, size_t i) -> double {
                            if (i == 0){
                                return q;
                            }else if(i < 0){
                                return 1;
                            }else{
                                return (q-i)*Q(Q, i-1);
                            }
                        };

                        return newVec[0][2/*COLUMN: x, y;*/ + i]*Q(Q,i-1) / factorial(factorial, i) + iter(iter, i + 1);
                    };

                    return newVec[0][1] + ITER(ITER, 1);
                };

                switch(N - 2/*COLUMN: x, y;*/){
                case(8):
                    strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: x, y;*/)+ "</sub>(x = " + QString::number(B[0]) + ") = y<sub>0</sub> "
                                   "+ q*Δy<sub>0</sub> + q(q-1)/2! * Δ<sup>2</sup>y<sub>0</sub> + q(q-1)(q-2)/3! * Δ<sup>3</sup>y<sub>0</sub> + q(q-1)(q-2)(q-3)/4! * Δ<sup>4</sup>y<sub>0</sub> "
                                   "+ q(q-1)(q-2)(q-3)(q-4)/5! * Δ<sup>5</sup>y<sub>0</sub> + q(q-1)(q-2)(q-3)(q-4)(q-5)/6! * Δ<sup>6</sup>y<sub>0</sub> "
                                   "+ q(q-1)(q-2)(q-3)(q-4)(q-5)(q-6)/7! * Δ<sup>7</sup>y<sub>0</sub> + q(q-1)(q-2)(q-3)(q-4)(q-5)(q-6)(q-7)/8! * Δ<sup>8</sup>y<sub>0</sub>"
                                   " </b> = " + QString::number(P_n(), 'f', 6) + " ; ");
                    break;
                case(2):
                    strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: x, y;*/)+ "</sub>(x = " + QString::number(B[0]) + ") = y<sub>0</sub> "
                                   "+ q*Δy<sub>0</sub> + q(q-1)/2! * Δ<sup>2</sup>y<sub>0</sub> "
                                   " </b> = " + QString::number(P_n(), 'f', 6) + " ; ");
                    break;
                case(1):
                    strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: x, y;*/)+ "</sub>(x = " + QString::number(B[0]) + ") = y<sub>0</sub> "
                                   "+ q*Δy<sub>0</sub> </b> = " + QString::number(P_n(), 'f', 6) + " ; ");
                    break;
                default:
                    strHtml.append("<b style=\"color: orangeRed;\" >P<sub>n</sub>(x) = P<sub>" + QString::number(N - 2/*COLUMN: x, y;*/)+ "</sub>(x = " + QString::number(B[0]) + ") = y<sub>0</sub> "
                                   "+ q*Δy<sub>0</sub> </b> = " + QString::number(P_n(), 'f', 6) + " ; ");
                    break;
                };

                ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
            }
        };
        general(general, n, A);
    };
    general_i();

    ////////////////////////////////////////////////
    //ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Номер варианта:</b> N = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    QTime finish = QTime::currentTime();
    double time = start_1.msecsTo(finish) / 1000.0;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<hr>" + "<b>Время работы: </b> " +  QString::number(time) + " ;");

}
