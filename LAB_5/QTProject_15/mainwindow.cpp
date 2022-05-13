#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, (&MainWindow::func));

    ui->spinBox_1->setValue(9);

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

        size_t N = 12;
        //double x_0=0.1485-0.002*N;

        double vecS[2] = {0.6, 1.6}; //Segment
        double vecZ[2] = {0.6, 1.4};
        double vecW[2] = {0.2, 2.5};

        double vecN[3] = {8, 4, 5};

        double eps = 0.001;

        if((qElem_s_1.count()) == CN*2+2){

            for (size_t i = 2; i < qElem_s_1.count(); i+=1){

                qElem_s_1[i].qLineEdit->setText(QString::number(vecF[(i-2) / 2][(i-2) % 2],'f',3+i%2));
                //qElem_s_1[i+1].qLineEdit->setText(QString::number(vecF[i][1]));
            }

            qElem_s_2[0].qLineEdit->setText(QString::number(vecS[0],'f',1));
            qElem_s_2[1].qLineEdit->setText(QString::number(vecS[1],'f',1));
            //qElem_s_2[2].qLineEdit->setText(QString::number(vecS[2],'f',3));

            qElem_s_3[0].qLineEdit->setText(QString::number(vecZ[0],'f',1));
            qElem_s_3[1].qLineEdit->setText(QString::number(vecZ[1],'f',1));

            qElem_s_4[0].qLineEdit->setText(QString::number(vecW[0],'f',1));
            qElem_s_4[1].qLineEdit->setText(QString::number(vecW[1],'f',1));

            qElem_s_5[0].qLineEdit->setText(QString::number(vecN[0],'f',0));
            qElem_s_5[1].qLineEdit->setText(QString::number(vecN[1],'f',0));
            qElem_s_5[2].qLineEdit->setText(QString::number(vecN[2],'f',0));
        }

        Epsilon.qLineEdit->setText(QString::number(eps,'f', 3));
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

        if(qElem_s_4.count() > 0){
            foreach(auto elem, qElem_s_3)
            {
                ui->gridLayout_16->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                ui->gridLayout_16->removeItem(ui->gridLayout_16->itemAtPosition(elem.row,elem.col));
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

            qElem_s_5 = QVector<Elem>(3, Epsilon);

            qElem_s_5[0].qLineEdit = ui->lineEdit_1;
            qElem_s_5[1].qLineEdit = ui->lineEdit_2;
            qElem_s_5[2].qLineEdit = ui->lineEdit_3;

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

            for(size_t i = 0; i < 2; i++){
                Elem elem_C;

                elem_C.qLineEdit = new  QLineEdit;
                elem_C.qLineEdit->setAlignment(Qt::AlignHCenter);

                ui->horizontalSpacer_12->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_12->geometry().height());
                ui->horizontalSpacer_13->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_13->geometry().height());

                elem_C.row = 0;
                elem_C.col = i;

                qElem_s_4.push_back(elem_C);

                ui->gridLayout_16->addWidget(elem_C.qLineEdit, elem_C.row, elem_C.col,Qt::Alignment());
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
    strHtml_A.append("<b style=\"color: red;\">Принятые данные </b><b style=\"color: black;\">:</b><br>");

    /*if(qElem_s_1.count() > 0){
        A = QVector<QVector<double>>(CN, QVector<double>(2,0));
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
    }*/

    if(qElem_s_2.count() > 0){
        B = QVector<double>(2, 0);
        strHtml_A.append("<b>B :</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 2; i++){
                strHtml_A.append("<td align=center> " + qElem_s_2[i].qLineEdit->text() + " </td>");
                B[i] = qElem_s_2[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    if(qElem_s_3.count() > 0){
        C = QVector<double>(2, 0);
        strHtml_A.append("<b>C :</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 2; i++){
                strHtml_A.append("<td align=center> " + qElem_s_3[i].qLineEdit->text() + " </td>");
                C[i] = qElem_s_3[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    if(qElem_s_4.count() > 0){
        D = QVector<double>(2, 0);
        strHtml_A.append("<b>D :</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 2; i++){
                strHtml_A.append("<td align=center> " + qElem_s_4[i].qLineEdit->text() + " </td>");
                D[i] = qElem_s_4[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    n_1 = QVector<double>(1, 0);
    n_2 = QVector<double>(2, 0);

    n_1[0] = qElem_s_5[0].qLineEdit->text().toDouble();

    n_2[0] = qElem_s_5[1].qLineEdit->text().toDouble();
    n_2[1] = qElem_s_5[2].qLineEdit->text().toDouble();

    strHtml_A.append("<b>n_1 :</b><table border=1 style=\"border-collapse: collapse;\"><tr><td align=center>"+ qElem_s_5[0].qLineEdit->text() +"</td></tr></table><br>");
    strHtml_A.append("<b>n_2 :</b><table border=1 style=\"border-collapse: collapse;\"><tr><td align=center>" + qElem_s_5[1].qLineEdit->text()
            + " </td><td align=center>" + qElem_s_5[2].qLineEdit->text() + " </td></tr></table>");

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");

    double eps = Epsilon.qLineEdit->text().toDouble();

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Точность :</b> ε = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    ////////////////////////////////////////////////

    auto print_general = [&](QVector<QVector<double>>& vec) -> void {
         strHtml_A.clear();
         strHtml_A.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
         strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

         for(int i = 0; i < vec.count(); ++i){
             strHtml_A.append("<tr>");
             for(int j = 0; j < vec[i].count(); ++j){
                 switch(j){
                    case(0):
                        strHtml_A.append("<td align=center> " + QString::number(vec[i][j]) + " </td>");
                        break;
                    default:
                        vec[i][j] == 0 ? strHtml_A.append("<td align=center> " + QString::number(vec[i][j]) + " </td>")
                               : strHtml_A.append("<td align=center> " + QString::number(vec[i][j],'f',3) + " </td>");
                        break;
                 }
             }
         }

         strHtml_A.append("</table>");
         ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
     };

    auto print_general_C_FXV = [&](QVector<double>& C, QVector<double>& X, double r) -> void {
         strHtml_A.clear();
         strHtml_A.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
         strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

         strHtml_A.append("<tr><td>n = " + QString::number(C.count()) + "; <td></tr>");
            strHtml_A.append("<tr>");
            strHtml_A.append("<td> =");
            for(int i = 0; i < C.count() - 1; ++i){
                strHtml_A.append("C<sub>" + QString::number(i) + "</sub>*"+"X<sub>"+ QString::number(i) +"</sub> +");
            }
            strHtml_A.append("C<sub>" + QString::number(C.count() - 1) + "</sub>*"+"X<sub>"+ QString::number(C.count() - 1) +"</sub>");

            strHtml_A.append(" = ");
            double SUMM = 0;
            for(int i = 0; i < C.count() - 1; ++i){
                SUMM += C[i]*X[i];

                strHtml_A.append(QString::number(C[i]) + "*"+ QString::number(X[i]) +"+");

            }
            SUMM -= r;
            strHtml_A.append(QString::number(C[C.count() - 1]) + "*"+ QString::number(X[C.count() - 1]) +" = " + QString::number(SUMM));

            strHtml_A.append("</td></tr>");

         strHtml_A.append("</table>");
         ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
     };

    // + Вычисления по формуле трапеции:
    {
        // 1. Определение шага интегрирования.

        auto h_min = [&]()->double{
            auto M_2 = [&](double a, double b) -> double {
                double MAX = 0;
                for(double x = a; x <= b; x+= eps){
                    double M = (2*qPow(x, 2) - 0.8)/(qPow(qPow(x, 2) + 0.8, 2.5));
                    if(M > MAX) MAX = M;
                }
                return MAX;
            };
            return sqrt(12*eps/((B[1] - B[0])*M_2(B[0], B[1])));
        };
        auto ER = [&](double h) -> double {
            auto M_2 = [&](double a, double b) -> double {
                double MAX = 0;
                for(double x = a; x <= b; x+= eps){
                    double M = (2*qPow(x, 2) - 0.8)/(qPow(qPow(x, 2) + 0.8, 2.5));
                    if(M > MAX) MAX = M;
                }
                return MAX;
            };
            //qDebug() <<"MAX: " << M_2(B[0], B[1]);
            double r = B[1] - B[0];
            //qDebug() <<"h*h: " << QString::number(qPow(h, 2), 'f', 10);
            return (((double)r*qPow(h, 2))/12)*M_2(B[0], B[1]);
        };
        auto F = [] (double x) -> double {
            return 1/(sqrt(qPow(x, 2) + 0.8));
        };

        double h = eps;
        double er = 0;
        do{ h += eps; }while(!(abs(eps) <= (double)ER(h)));

        qDebug() << ER(h);

        qDebug() << h;
        qDebug() << "h_min: " << h_min();

        qDebug() << "h_min_w: " << QString::number(h_min(),'f', 1).toDouble() + 0.1;

        int n = (B[1] - B[0]) / (QString::number(h_min(),'f', 1).toDouble() + 0.1);

        qDebug() << n;

        X = QVector<QVector<double>>(n+1, QVector<double>(3, 0));

        for(int i = 0; i < n + 1; i++){
            X[i][0] = i;
            X[i][1] = B[0] + i*(QString::number(h_min(),'f', 1).toDouble() + 0.1);
            X[i][2] = F(X[i][1]);
        }

        print_general(X);

        QString strHtml_B;
        strHtml_B.append("<b style=\"color: green;\">Расчеты по формуле трапеции </b><b style=\"color: black;\">:</b><br>");
        strHtml_B.append("<b style=\"color: black;\">∫f(x)dx = </b><b style=\"color: black;\">h*( 0.5*y<sub>0</sub> + </b>");

        for(size_t i = 1;  i < X.count() - 1;i++){
            strHtml_B.append("<b style=\"color: black;\"> y<sub>" + QString::number(i) + "</sub> + </b>");
        }

        strHtml_B.append("<b style=\"color: black;\"> 0.5*y<sub>" + QString::number(X.count() - 1) + "</sub>) = </b>");

        double SUMM = 0;
        for(size_t i = 0;  i < X.count();i++){
            if(i == 0 || i == X.count() - 1) {
                SUMM += X[i][2]/2;
                (i == 0) ? strHtml_B.append("<b style=\"color: black;\"> " + QString::number(QString::number(h_min(),'f', 1).toDouble() + 0.1) +"*(</b><b style=\"color: black;\"> " + QString::number(X[i][2]/2) + " + </b>")
                         : strHtml_B.append("<b style=\"color: black;\"> " + QString::number(X[i][2]/2) + ")</b>");
            }else{
                SUMM += X[i][2];
                strHtml_B.append("<b style=\"color: black;\"> " + QString::number(X[i][2]) + " + </b>");
            }
        }

        SUMM = SUMM*(QString::number(h_min(),'f', 1).toDouble() + 0.1) ;
        strHtml_B.append("<b style=\"color: black;\"> = " + QString::number(SUMM) + "; </b><br>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_B);
    }

    // + Вычисления по формуле Симсона:
    {
       double h_S = (C[1] - C[0])/(n_1[0]);

       Y = QVector<QVector<double>>(n_1[0] + 1, QVector<double>(3, 0));

       auto F_S = [](double x) -> double {
           return qPow(x, 2)*qCos(x);
       };

       for(int i = 0; i < n_1[0] + 1; i++){
           Y[i][0] = i;
           Y[i][1] = C[0] + i*h_S;//
           Y[i][2] = F_S(Y[i][1]);
       }

       print_general(Y);

       QString strHtml_C;
       strHtml_C.append("<b style=\"color: green;\">Расчеты по формуле Симсона </b><b style=\"color: black;\">:</b><br>");
       strHtml_C.append("<b style=\"color: black;\">∫f(x)dx = </b><b style=\"color: black;\">0.(3)*h*(0.5*y<sub>0</sub> + </b>");

       for(size_t i = 1;  i < Y.count() - 1;i++){
           if(i % 2 == 0)
                strHtml_C.append("<b style=\"color: black;\"> 2*y<sub>" + QString::number(i) + "</sub> + </b>");
           else
               strHtml_C.append("<b style=\"color: black;\"> 4*y<sub>" + QString::number(i) + "</sub> + </b>");

       }

       strHtml_C.append("<b style=\"color: black;\"> 0.5*y<sub>" + QString::number(Y.count() - 1) + "</sub>) = </b>");

       double SUMM = 0;
       for(size_t i = 0;  i < Y.count();i++){
           if(i == 0 || i == Y.count() - 1) {
               SUMM += Y[i][2]/2;
               (i == 0) ? strHtml_C.append("<b style=\"color: black;\"> 0.(3)*" + QString::number(h_S) +"*(</b><b style=\"color: black;\"> " + QString::number(Y[i][2]/2) + " + </b>")
                        : strHtml_C.append("<b style=\"color: black;\"> 2*" + QString::number(Y[i][2]/2) + ")</b>");
           }else{
               if(i % 2 == 0){
                     SUMM += (2*Y[i][2]);
                     strHtml_C.append("<b style=\"color: black;\"> 2*" + QString::number(Y[i][2]) + " + </b>");
               }else{
                   SUMM += (4*Y[i][2]);
                   strHtml_C.append("<b style=\"color: black;\"> 4*" + QString::number(Y[i][2]) + " + </b>");
               }
           }
       }

       SUMM = SUMM*(h_S/3) ;
       strHtml_C.append("<b style=\"color: black;\"> = " + QString::number(SUMM) + "; </b><br>");
       ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_C);
    }
    Y.clear();

    // * Вычисления по формуле Гаусса:
    {
        //1. Построение полинома Лежандра n-ой степени.
        auto P_n_x = [](auto P_n,int n, double x) -> double {
            switch(n){
            case(0):
                return 1.0;
            case(1):
                return (double)x;
            default:
                return (double)((double)(2*n - 1)*x*P_n(P_n, n - 1, x) - (double)(n - 1)*P_n(P_n, n - 2, x)) / (double)n;
            };
        };

        //qDebug() << P_n_x(P_n_x, 4, 1);

        for(int n = 4; n < 6; ++n){
            int COUNT = 0;
            double EPS = 0;
            qDebug() << "n: " << n;

            //qPow(n,2)*qPow(n-1,2)*qPow(n-2,2)*qPow(n-3,2);

            if (n == 4) EPS = 0.009882;//0.01//(double)(1)/(n*n*(n+1))//0.009885//(double)2/(n*qPow(n,1)*qPow(n-1,4)*qPow(n-2,3)*qPow(n-3,2))
            if (n == 5) EPS = (double)(1- (-1))/(2*n*(n-1));//0.01
            if (n == 6) EPS = (double)(1- (-1))/(2*n*(n-1));//0.03
            if (n >= 7) EPS = 0.05;//(double)(1- (-1))/(2*n*(n-1))//0.05
            if (n >= 8) EPS = 0.04;//(double)(1- (-1))/(2*n*(n-1))//0.05

            qDebug() << "EPS: " << EPS;

            QVector<double> PNX(n, 0);
            for(double x = 0; (x <= 1) or ((COUNT < n) && (x <= 1)) ; x += EPS){
                double y = P_n_x(P_n_x, n, x);
                //qDebug() << "x: " << x << "y: " << y;
                if(abs(y) < EPS && COUNT < PNX.count() && (n % 2 == 0)){
                    PNX[COUNT] = QString::number(x, 'f', 3).toDouble();
                    PNX[COUNT + 1] = -1*QString::number(x, 'f', 3).toDouble();
                    COUNT+=2;
                }else if(abs(y) < EPS && COUNT < PNX.count()){
                    if(x == 0){
                        PNX[COUNT] = QString::number(x, 'f', 3).toDouble();
                        COUNT+=1;
                    }else{
                        PNX[COUNT] = QString::number(x, 'f', 3).toDouble();
                        PNX[COUNT + 1] = -1*QString::number(x, 'f', 3).toDouble();
                        COUNT+=2;
                    }

                }
            }

            //qDebug() << PNX[0];qDebug() << PNX[1]; qDebug() << PNX[2];qDebug() << PNX[3];
            //if(n > 4) qDebug() << PNX[4];if(n > 5) qDebug() << PNX[5];if(n > 6) qDebug() << PNX[6];if(n > 7) qDebug() << PNX[7];

            X_1 = QVector<double>(n, 0);
            int k = n - 1;
            for(int i = 0; i <= k; ++i){
                //double var = ((double)(((double)(D[1] + D[0]) +(double)(D[1] - D[0])*PNX[i])/2));
                X_1[i] = (double)(((double)(D[1] + D[0]) +(double)(D[1] - D[0])*PNX[i])/2);
            }

            C_1 = QVector<double>(n, 0);

            auto print_general_A = [&](QVector<QVector<double>>& vec) -> void {
                 strHtml_A.clear();
                 strHtml_A.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                 strHtml_A.append("<b>A :</b><table border=1 style=\"border-collapse: collapse;\">");

                 for(int i = 0; i < vec.count(); ++i){
                     strHtml_A.append("<tr>");

                     for(int j = 0; j < vec[i].count(); ++j){
                         vec[i][j] = QString::number(vec[i][j],'f', 2).toDouble();
                         switch(j){
                            case(0):
                                strHtml_A.append("<td align=center> " + QString::number(vec[i][j]) + " </td>");
                                break;
                            default:
                                vec[i][j] == 0 ? strHtml_A.append("<td align=center> " + QString::number(vec[i][j]) + " </td>")
                                       : strHtml_A.append("<td align=center> " + QString::number(vec[i][j],'f',3) + " </td>");
                                break;
                         }
                     }
                 }

                 strHtml_A.append("</table>");
                 ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
             };

            auto print_general_B = [&](QVector<double>& vec) -> void {
                 strHtml_A.clear();
                 strHtml_A.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                 strHtml_A.append("<b>B :</b><table border=1 style=\"border-collapse: collapse;\">");

                 for(int i = 0; i < vec.count(); ++i){
                     strHtml_A.append("<tr>");
                     switch(i){
                        case(0):
                            strHtml_A.append("<td align=center> " + QString::number(vec[i]) + " </td>");
                            break;
                        default:
                            vec[i] == 0 ? strHtml_A.append("<td align=center> " + QString::number(vec[i]) + " </td>")
                                   : strHtml_A.append("<td align=center> " + QString::number(vec[i],'f',3) + " </td>");
                            break;
                     }
                     strHtml_A.append("</tr>");
                 }

                 strHtml_A.append("</table>");
                 ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
             };

            auto print_general_T = [&](QVector<double>& vec) -> void {
                 strHtml_A.clear();
                 strHtml_A.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                 strHtml_A.append("<b>T :</b><table border=1 style=\"border-collapse: collapse;\">");

                 for(int i = 0; i < vec.count(); ++i){
                     strHtml_A.append("<tr>");
                     switch(i){
                        case(0):
                            strHtml_A.append("<td align=center> " + QString::number(vec[i]) + " </td>");
                            break;
                        default:
                            vec[i] == 0 ? strHtml_A.append("<td align=center> " + QString::number(vec[i]) + " </td>")
                                   : strHtml_A.append("<td align=center> " + QString::number(vec[i],'f',3) + " </td>");
                            break;
                     }
                     strHtml_A.append("</tr>");
                 }

                 strHtml_A.append("</table>");
                 ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
             };

            auto print_general_X = [&](QVector<double>& vec) -> void {
                 strHtml_A.clear();
                 strHtml_A.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                 strHtml_A.append("<b>X :</b><table border=1 style=\"border-collapse: collapse;\">");

                 for(int i = 0; i < vec.count(); ++i){
                     strHtml_A.append("<tr>");
                     switch(i){
                        case(0):
                            strHtml_A.append("<td align=center> " + QString::number(vec[i]) + " </td>");
                            break;
                        default:
                            vec[i] == 0 ? strHtml_A.append("<td align=center> " + QString::number(vec[i]) + " </td>")
                                   : strHtml_A.append("<td align=center> " + QString::number(vec[i],'f',3) + " </td>");
                            break;
                     }
                     strHtml_A.append("</tr>");
                 }

                 strHtml_A.append("</table>");
                 ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
             };


            auto A_ = [&](QVector<double>& T) -> QVector<double>{

                QVector<double> X(T.count(), 0);
                QVector<double> B(T.count(), 0);
                QVector<QVector<double>> A(T.count(), QVector<double>(T.count(), 0));

                auto T_SORT =[](QVector<double>& T){
                    std::sort (T.begin(), T.end(), [](const double& lha, const double& rha){return abs(lha) < abs(rha);});
                };

                T_SORT(T);

                print_general_T(T);

                for(int i = 0; i < T.count(); ++i){
                    for(int j = 0; j < T.count(); ++j){
                        A[i][j] = qPow(-1, i)*qPow(T[j], i);
                    }
                }

                for(int k = 0; k < T.count(); ++k){
                    if(k % 2 == 1){
                        B[k] = 0;
                    }else{
                       B[k] = (double)((double)2/(k+1));
                    }
                    //B[i] = (double)((i % 2 == 0) ? (double)(2/(i+1)): 0);
                }

                print_general_A(A);
                print_general_B(B);

                /// Прямой ход Гаусса:

                switch(T.count() % 2){
                case(0):
                    for(int k = (n % 2); k < T.count(); ++k){// k-столбец
                        for(int i = T.count() - 1; i >= ((T.count()-1) % 2) + k; --i){// i-строка

                            double coef = ((double)A[i][k]/A[i - 1][k]);

                            qDebug() << "COEF: " << coef;

                            B[i] = (double)B[i] - (double)((double)A[i][k]/A[i - 1][k])*B[i - 1];
                            A[i][k] = A[i][k] - ((double)A[i][k]/A[i - 1][k])*A[i - 1][k];

                            for(int j = k + 1; j < A[k].count(); ++j){
                               // B[i] = (double)B[i] - (double)((double)A[i][k]/A[i - 2][k])*B[i - 2];
                                A[i][j] = A[i][j] - coef*A[i - 1][j];
                            }

                        }
                    }
                    break;
                case(1):
                    for(int k = (T.count() % 2); k < T.count(); ++k){// k-столбец
                        for(int i = T.count() - 1; i > k; --i){// i-строка

                            double coef = ((double)A[i][k]/A[i - 1][k]);

                            qDebug() << "COEF: " << coef;

                            B[i] = (double)B[i] - (double)((double)A[i][k]/A[i - 1][k])*B[i - 1];
                            A[i][k] = A[i][k] - ((double)A[i][k]/A[i - 1][k])*A[i - 1][k];

                            for(int j = k + 1; j < A[k].count(); ++j){
                               // B[i] = (double)B[i] - (double)((double)A[i][k]/A[i - 2][k])*B[i - 2];
                                A[i][j] = A[i][j] - coef*A[i - 1][j];
                            }
                        }
                    }
                    break;
                }

                print_general_A(A);
                print_general_B(B);

                /// Обратный ход Гаусса:
                for(int k = T.count() - 1; k >= 0; --k){//k - строка
                    auto ITER = [&](auto iter, QVector<QVector<double>>& A, QVector<double>& B, double k, int i)->double{
                        if(k == i){
                            return (double)(B[i] - iter(iter, A, B, k, i + 1))/A[k][k];
                        }else if(i < B.count() - 1){
                            return X[i]*A[k][i] + iter(iter, A, B, k, i + 1);
                        }else{
                            return X[i]*A[k][i];//
                        }
                    };

                    if(k == T.count() - 1){
                        X[k] = B[k]/A[k][k];
                    }else{
                        X[k] = ITER(ITER, A, B, k, k);
                    }
                }

                print_general_X(X);

                return X;
            };

            QVector<double> PNC = A_(PNX);

            for(int i = 0; i <= k; ++i){
                //PNC[i-1] = A_(i);
                qDebug() << "A_i: " << PNC[i];
                C_1[i] = (double)(D[1] - D[0])*PNC[i]/2;
            }

            FXV = QVector<double>(0, 0);
            auto FX = [&]()-> bool{
                auto f = [](double x)->double{
                    return sqrt(x*x + 2)/(x + 2);
                };

                foreach(auto elem, X_1){
                    FXV.push_back(f(elem));
                }
            };

            FX();

            auto R_n = [](int n, double a, double b, double e)-> double {
                auto factorial = [](auto factorial, int i) -> double {
                    return (i < 2) ? 1 : i * factorial(factorial, i - 1);
                };

                auto DF = [](int n)->double{
                    return (n == 4) ? 91.3397 : 840.5809;
                };

                qDebug() << "DF: " << DF(n);

                return (qPow(b - a,2*n + 1)*qPow(factorial(factorial, n), 4)*DF(n))/(qPow(factorial(factorial, 2*n),3)*(2*n+1));

            };

            double r = (double)R_n(n, D[0], D[1], (D[1]-D[0])/2);

            qDebug() << "R: " << QString::number(r,'f', 9);

            print_general_C_FXV(C_1, FXV, r);
        }
    }

    ////////////////////////////////////////////////

    //ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Номер варианта:</b> N = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    QTime finish = QTime::currentTime();
    double time = start_1.msecsTo(finish) / 1000.0;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<hr>" + "<b>Время работы: </b> " +  QString::number(time) + " ;");

}
