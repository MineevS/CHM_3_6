#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, (&MainWindow::func));

    ui->spinBox_1->setValue(12);

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
            2.4,3.526,
            2.6,3.782,
            2.8, 3.945,
            3.0, 4.043,
            3.2, 4.104,
            3.4, 4.155,
            3.6, 4.222,
            3.8, 4.331,
            4.0, 4.507,
            4.2, 4.775,
            4.4, 5.159,
            4.6, 5.683}; // f(x)

        size_t N = 12;
        //double x_0=0.1485-0.002*N;

        double vecS[2] = {2, (double)12}; //Segment
        double vecZ[2] = {2, (double)12};
        double vecD[2] = {2, (double)12};

        double eps = 0.00001;

        if((qElem_s_1.count()) == CN*2+2){

            for (size_t i = 2; i < qElem_s_1.count(); i+=1){

                qElem_s_1[i].qLineEdit->setText(QString::number(vecF[(i-2) / 2][(i-2) % 2],'f',3+i%2));
                //qElem_s_1[i+1].qLineEdit->setText(QString::number(vecF[i][1]));
            }

            qElem_s_2[0].qLineEdit->setText(QString::number(vecS[0],'f',0));
            qElem_s_2[1].qLineEdit->setText(QString::number(vecS[1],'f',0));
            //qElem_s_2[2].qLineEdit->setText(QString::number(vecS[2],'f',3));

            qElem_s_3[0].qLineEdit->setText(QString::number(vecZ[0],'f',0));
            qElem_s_3[1].qLineEdit->setText(QString::number(vecZ[1],'f',0));

            qElem_s_4[0].qLineEdit->setText(QString::number(vecD[0],'f',0));
            qElem_s_4[1].qLineEdit->setText(QString::number(vecD[1],'f',0));
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

        if(qElem_s_4.count() > 0){
            foreach(auto elem, qElem_s_4)
            {
                ui->gridLayout_15->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                ui->gridLayout_15->removeItem(ui->gridLayout_15->itemAtPosition(elem.row,elem.col));
            }
            qElem_s_4.clear();
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

            for(size_t i = 0; i < 2; i++){
                Elem elem_C;

                elem_C.qLineEdit = new  QLineEdit;
                elem_C.qLineEdit->setAlignment(Qt::AlignHCenter);

                ui->horizontalSpacer_10->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_10->geometry().height());
                ui->horizontalSpacer_11->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_11->geometry().height());

                elem_C.row = 0;
                elem_C.col = i;

                qElem_s_4.push_back(elem_C);

                ui->gridLayout_15->addWidget(elem_C.qLineEdit, elem_C.row, elem_C.col,Qt::Alignment());
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
        C_s = QVector<double>(2, 0);
        strHtml_A.append("<b>X_L :</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 2; i++){
                strHtml_A.append("<td align=center> " + qElem_s_3[i].qLineEdit->text() + " </td>");
                C_s[i] = qElem_s_3[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    if(qElem_s_4.count() > 0){
        D = QVector<double>(2, 0);
        strHtml_A.append("<b>X_L :</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 2; i++){
                strHtml_A.append("<td align=center> " + qElem_s_4[i].qLineEdit->text() + " </td>");
                D[i] = qElem_s_4[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");

    double eps = Epsilon.qLineEdit->text().toDouble();

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Точность :</b> ε = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    ////////////////////////////////////////////////

    ///////////////////////////////////////////////

    int Ga,  Gb;
    double step_a, step_b;

    auto print_general = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Вычисления без производной</b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',5) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_1 = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Вычисления по 1 производной</b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',5) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_2 = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Вычисления по 2 производной</b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',5) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_N = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',5) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_s_1 = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Таблица для Стирлинга: </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',5) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_s_1_1 = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Таблица 1 производной для Стирлинга: </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',5) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_s_1_2 = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: red;\">Таблица 2 производной для Стирлинга: </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',5) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_5 = [&](QVector<QVector<double>>& vec, double x) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: blue;\">Таблица приращений(конечных разностей) функции в точке x_0 = "+ QString::number(x) + " </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>T_1 :</b><table border=1 style=\"border-collapse: collapse;\">");
        strHtml_A.append("<tr><td align=center> x </td><td align=center> y = f(x) </td><td align=center> Δf(x<sub>0</sub>)/ Δx = (f(x) - f(x<sub>0</sub>))/ Δx; Δx = x - x<sub>0</sub>; </td>"
                         "<td align=center> Δ<sup>1</sup>f(x<sub>0</sub>) = (f(x) - f(x<sub>0</sub>)); Δx = x - x<sub>0</sub>; </td></tr>");

        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',5) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_3 = [&](QVector<QVector<double>>& vec) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: blue;\"> Таблица первой производной функции </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>T_1 :</b><table border=1 style=\"border-collapse: collapse;\">");
        strHtml_A.append("<tr><td align=center> x </td><td align=center> y = f<sup>'</sup>(x) </td></tr>");


        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',5) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_4 = [&](QVector<QVector<double>>& vec, double x) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: blue;\">Таблица приращений(конечных разностей) по первой производной функции в точке x_0 = "+ QString::number(x) + " </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>T_1 :</b><table border=1 style=\"border-collapse: collapse;\">");
        strHtml_A.append("<tr><td align=center> x </td><td align=center> y<sup>'</sup> = f<sup>'</sup>(x) </td><td align=center> Δ<sup>2</sup>f(x<sub>0</sub>)/ Δx = (f<sup>'</sup>(x) - f<sup>'</sup>(x<sub>0</sub>))/ Δx; Δx = x - x<sub>0</sub>; </td>"
                         "<td align=center> Δ<sup>2</sup>f<sup>'</sup>(x<sub>0</sub>) = (f<sup>'</sup>(x) - f<sup>'</sup>(x<sub>0</sub>)); Δx = x - x<sub>0</sub>; </td></tr>");

        foreach(auto str, vec){
            strHtml_A.append("<tr>");
            foreach(auto elem, str){
                elem == 0 ? strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>")
                          : strHtml_A.append("<td align=center> " + QString::number(elem,'f',5) + " </td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");
    };

    auto print_general_G_1 = [&](QVector<QVector<double>>& vec, size_t Ga, QVector<double>& c) -> void {
        strHtml_A.clear();
        strHtml_A.append("<b style=\"color: green;\">Предварительное выделение элементов для 1 И. Ф. Г. </b><b style=\"color: black;\">:</b><br>");
        strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

        for(size_t i = 0; i < CN; i++){
            strHtml_A.append("<tr>");
            for(size_t j = 0; j < vec[i].count(); j++){
                if(((j == (2*Ga + 1) - 2*i || j == (2*Ga + 2) - 2*i) && (i <= Ga)) || (i == Ga && (j == 0 || j == 1)) ){
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

        uint64_t COUNT_R = 0;

        auto general = [&](auto GEN, int64_t N, QVector<QVector<double>> A, QVector<double>& C) -> void {
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
                newVec[i][N - 1] = (double)(newVec[i + 1][N - 2] - newVec[i][N - 2]);

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

            auto print_general_N_2 = [&](QVector<QVector<double>>& vec, size_t Ga, QVector<double>& c) -> void {
                strHtml_A.clear();
                strHtml_A.append("<b style=\"color: green;\">Предварительное выделение элементов для 2 И. Ф. Н. </b><b style=\"color: black;\">:</b><br>");
                strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

                for(size_t i = 0; i < CN; i++){
                    strHtml_A.append("<tr>");
                    for(size_t j = 0; j < vec[i].count(); j++){
                        if(j==(Ga+1) - i && i>0){
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

            if( FL(newVec, N, eps) && (N <= CN) && !FLAG){
                GEN(GEN, N + 1, newVec, C);
            }else{
                ///print_general(newVec);

                // Нахождение коэффициентов снизу относительно побочной диагонали.
                for(int j = newVec[0].count() - 1; j >= 0 ; j--){
                    if(j == newVec[0].count() - 1){
                        double SUMM = 0;
                        for(int i = 0; i < newVec.count(); i++){
                            SUMM += newVec[i][j];
                        }
                        //qDebug() << (newVec.count() - (newVec[0].count() - 2)) << "\n";
                        double sred = SUMM / (newVec.count() - (newVec[0].count() - 2));
                        for(int k = newVec[0].count() - 1; k >= 0 ; k--){
                            for(int i = 0; i < newVec.count(); i++){
                                if(k == newVec[0].count() - 1 && i >= (newVec.count() - (newVec[0].count() - 2))){
                                    newVec[i][k] = sred;
                                }
                            }
                        }
                    } else {
                        if(j >= 2){
                            for(int i = 0; i < newVec.count(); i++){
                                if(i > newVec.count() - (j)){
                                    //qDebug() << i << "\n";
                                    newVec[i][j] = newVec[i - 1][j] + newVec[i - 1][j + 1];
                                }
                            }
                        }
                    }
                }

                print_general(newVec);// print one, end iteration;

                // + Интерполяционная формула Ньютона:
                {
                     Y = QVector<QVector<double>>((B[1] - B[0])/2 + 1, QVector<double>(2, 0));
                     Z = QVector<QVector<double>>((B[1] - B[0])/2 + 1, QVector<double>(2, 0));
                     S = QVector<QVector<double>>((B[1] - B[0])/2 + 1, QVector<double>(2, 0));

                    auto P_n = [&](double x, int e) -> double {

                        double q = (x - newVec[Ga][0]) / abs((newVec[1][0] - newVec[0][0]));
                        if (e == 1){
                            QString strHtml;
                            strHtml.clear();
                            strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                            strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(x) + "; ");
                            strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(newVec[Ga][0]) + "; ");
                            strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(abs(newVec[1][0] - newVec[0][0])) + "; ");

                            strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(x) + " - "
                                           + QString::number(newVec[Ga][0]) + " )/ " + QString::number(abs(newVec[1][0] - newVec[0][0]))
                                    + " = " + QString::number(q) + "; ");
                            ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                            strHtml.clear();
                            strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                        }

                        auto ITER = [&](auto iter, size_t i) -> double {
                            if(i >= newVec[Ga].count() - 1/*COLUMN: x, y;*/ ){
                                return 0;
                            }

                            auto factorial = [](auto fact, size_t i) -> double {
                                return (i == 1 || i == 0) ? 1/*База факториала*/ : i*fact(fact, i - 1);
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
                            //qDebug() << Q(Q,i-1);
                            //qDebug() << factorial(factorial, i);
                            //qDebug() << "a_1: "<< i - 1 << ";     Q: "<< Q(Q, i - 1) << "; f:" << factorial(factorial, i) << "; C:"<< newVec[Ga][1/*COLUMN: x, y;*/ + i];
                            return newVec[Ga][1/*COLUMN: x, y;*/ + i]* Q(Q, i - 1) / factorial(factorial, i) + iter(iter, i + 1);
                        };

                        //qDebug() << "a_1: " << 0 << "; C:" << newVec[Ga][1];
                        return newVec[Ga][1] + ITER(ITER, 1);
                    };

                    auto P_n_2 = [&](double x, int e) -> double {

                        double q = (x - newVec[Ga][0]) / abs((newVec[1][0] - newVec[0][0]));
                        if (e == 1){
                            QString strHtml;
                            strHtml.clear();
                            strHtml.append("<b style=\"color: red;\">Вычисления E</b><b style=\"color: black;\">:</b><br>");
                            strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(x) + "; ");
                            strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(newVec[Ga][0]) + "; ");
                            strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(abs(newVec[1][0] - newVec[0][0])) + "; ");

                            strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(x) + " - "
                                           + QString::number(newVec[Ga][0]) + " )/ " + QString::number(abs(newVec[1][0] - newVec[0][0]))
                                    + " = " + QString::number(q) + "; ");
                            ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                            strHtml.clear();
                            strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                        }

                        auto ITER = [&](auto iter, size_t i) -> double {
                            if(i >= X.count() - 1/*COLUMN: x, y;*/ ){
                                return 0;
                            }

                            auto factorial = [](auto fact, size_t i) -> double {
                                return (i == 1 || i == 0) ? 1/*База факториала*/ : i*fact(fact, i - 1);
                            };

                            auto Q = [&](auto Q, size_t i) -> double {
                                if (i == 0){
                                    return q;
                                }else if(i < 0){
                                    return 1;
                                }else{
                                    return (q+i)*Q(Q, i-1);
                                }
                            };
                            qDebug() << Q(Q,i - 1);
                            //qDebug() << factorial(factorial, i);
                            //qDebug() << "a_1: "<< i - 1 << ";     Q: "<< Q(Q, i - 1) << "; f:" << factorial(factorial, i) << "; C:"<< newVec[Ga][1/*COLUMN: x, y;*/ + i];
                            return X[i]* Q(Q, i - 1) / factorial(factorial, i) + iter(iter, i + 1);
                        };

                        //qDebug() << "a_1: " << 0 << "; C:" << newVec[Ga][1];
                        return X[0] + ITER(ITER, 1);
                    };

                    auto P_n_2_1 = [&](double x, int e) -> double {

                        double q = (x - newVec[Ga][0]) / abs((newVec[1][0] - newVec[0][0]));
                        if (e == 1){
                            QString strHtml;
                            strHtml.clear();
                            strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                            strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(x) + "; ");
                            strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(newVec[Ga][0]) + "; ");
                            strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(abs(newVec[1][0] - newVec[0][0])) + "; ");

                            strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(x) + " - "
                                           + QString::number(newVec[Ga][0]) + " )/ " + QString::number(abs(newVec[1][0] - newVec[0][0]))
                                    + " = " + QString::number(q) + "; ");
                            ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                            strHtml.clear();
                            strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                        }

                        auto ITER = [&](auto iter, size_t i) -> double {
                            static QVector<double> QS;
                            if(i >= X.count() - 1/*COLUMN: x, y;*/ ){
                                return 0;
                            }

                            auto factorial = [](auto fact, size_t i) -> double {
                                return (i == 1 || i == 0) ? 1/*База факториала*/ : i*fact(fact, i - 1);
                            };

                            auto Q = [&](auto Q, size_t i) -> double {
                                if (i == 0){
                                    QS.push_back(q);
                                    double SUM = 0;
                                    for(int i = 0; i < QS.count(); i++){
                                        double CONT = 1;
                                        for(int j = 0; j < QS.count(); j++){
                                            if(j != i){
                                                CONT *= QS[j];
                                            }
                                        }
                                        SUM += CONT;
                                    }
                                    QS.clear();
                                    return SUM;
                                }else if(i < 0){
                                    return 1;
                                }else{
                                    QS.push_back(q+i);
                                    return Q(Q, i-1);
                                }
                            };
                            qDebug() << Q(Q,i - 1);

                            //qDebug() << factorial(factorial, i);
                            //qDebug() << "a_1: "<< i - 1 << ";     Q: "<< Q(Q, i - 1) << "; f:" << factorial(factorial, i) << "; C:"<< newVec[Ga][1/*COLUMN: x, y;*/ + i];
                            return X[i]*Q(Q, i - 1) / factorial(factorial, i) + iter(iter, i + 1);
                        };

                        //qDebug() << "a_1: " << 0 << "; C:" << newVec[Ga][1];
                        return ITER(ITER, 1);
                    };

                    auto P_n_2_2 = [&](double x, int e) -> double {

                        double q = (x - newVec[Ga][0]) / abs((newVec[1][0] - newVec[0][0]));
                        if (e == 2){
                            QString strHtml;
                            strHtml.clear();
                            strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                            strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(x) + "; ");
                            strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(newVec[Ga][0]) + "; ");
                            strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(abs(newVec[1][0] - newVec[0][0])) + "; ");

                            strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(x) + " - "
                                           + QString::number(newVec[Ga][0]) + " )/ " + QString::number(abs(newVec[1][0] - newVec[0][0]))
                                    + " = " + QString::number(q) + "; ");
                            ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                            strHtml.clear();
                            strHtml.append("<b style=\"color: red;\">Вычисления </b><b style=\"color: black;\">:</b><br>");
                        }

                        auto ITER = [&](auto iter, size_t i) -> double {
                            static QVector<double> QS;
                            static QVector<double> qs;
                            if(i >= X.count() - 1/*COLUMN: x, y;*/ ){
                                return 0;
                            }

                            auto factorial = [](auto fact, size_t i) -> double {
                                return (i == 1 || i == 0) ? 1/*База факториала*/ : i*fact(fact, i - 1);
                            };

                            auto Q = [&](auto Q, size_t i) -> double {
                                if (i == 0){
                                    QS.push_back(q);
                                    double SUM = 0;
                                    for(int i = 0; i < QS.count(); i++){
                                        for(int k = 0; k < QS.count(); k++){
                                            if(k != i){
                                                qs.push_back(QS[k]);
                                            }

                                            if(k == QS.count() - 1){
                                                for(int v = 0; v < qs.count(); v++){
                                                    double CONT = 1;
                                                    for(int j = 0; j < qs.count(); j++){
                                                        if(j != v){
                                                            CONT *= qs[j];
                                                        }
                                                    }
                                                    SUM += CONT;
                                                }
                                                qs.clear();
                                            }
                                        }
                                        //SUM += SUMK;
                                    }
                                    QS.clear();
                                    return SUM;
                                }else if(i < 1){
                                    return 0;
                                }else{
                                    QS.push_back(q+i);
                                    return Q(Q, i-1);
                                }
                            };
                            qDebug() << Q(Q,i - 1);

                            //qDebug() << factorial(factorial, i);
                            //qDebug() << "a_1: "<< i - 1 << ";     Q: "<< Q(Q, i - 1) << "; f:" << factorial(factorial, i) << "; C:"<< newVec[Ga][1/*COLUMN: x, y;*/ + i];
                            return X[i]*Q(Q, i - 1) / factorial(factorial, i) + iter(iter, i + 1);
                        };

                        //qDebug() << "a_1: " << 0 << "; C:" << newVec[Ga][1];
                        return ITER(ITER, 1);
                    };

                    int m = 0;
                    for(size_t j = B[0]; j <= B[1]; j += 2){
                        double x = 5.85 - 0.09*j;

                        for(size_t i = 0; i < CN; i++){
                            if(i == 0){
                                step_a = abs(A[i][0] - x);
                                Ga = i;
                            }else if ( (step_a > (A[i][0] - x))  && (A[i][0] <= x)){
                                step_a = abs(A[i][0] - x);
                                Ga = i;
                            }

                            if(i == 0){
                                step_b = abs(A[(CN-1)][0] - x);
                                Gb = (CN - 1);
                            }else if ( (step_b > (A[(CN-1) - i][0] - x)) && (A[(CN-1) - i][0] >= x)){
                                //qDebug() << step_b;
                                step_b = abs(A[(CN-1) - i][0] - x);
                                Gb = (CN-1) - i;
                            }
                        }

                        // Определение № И. Ф. Н: 1 или 2 ?

                        switch (Ga)
                        {
                            case 1:{
                                print_general_N_1(newVec, Ga, X);
                                double y = P_n(x, 1);
                                Y[m][0] = x;
                                Y[m][1] = y;

                                m++;

                                print_general(Y);// без производной;
                                X.clear();

                                break;
                            }
                            default:{
                                    print_general_N_2(newVec, Ga, X);
                                    double y = P_n_2(x, 0);
                                    double z = P_n_2_1(x, 1);
                                    double s = P_n_2_2(x, 2);

                                    Y[m][0] = x;
                                    Y[m][1] = y;

                                    Z[m][0] = x;
                                    Z[m][1] = z;

                                    S[m][0] = x;
                                    S[m][1] = s;


                                    m++;

                                    ///print_general(Y);// без производной;
                                    ///print_general_1(Z);// c 1 производной;
                                    ///print_general_2(S);// c 2 производной;

                                    X.clear();
                                    break;
                            }
                        }
                    }

                    print_general(Y);// без производной;
                    print_general_1(Z);// c 1 производной;
                    print_general_2(S);// c 2 производной;
                }
                ///
                Y.clear();
                Z.clear();
                S.clear();

                // + Интерполяционная формула Стирлинга:
                {
                    S = QVector<QVector<double>>((C_s[1] - C_s[0])/2 + 1, QVector<double>(2, 0));
                    Y = QVector<QVector<double>>((C_s[1] - C_s[0])/2 + 1, QVector<double>(2, 0));
                    Z = QVector<QVector<double>>((C_s[1] - C_s[0])/2 + 1, QVector<double>(2, 0));

                    auto P_n_s = [&](double x) -> double {
                        QString strHtml;
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления s </b><b style=\"color: black;\">:</b><br>");
                        strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(x) + "; ");
                        strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(newVec[Ga][0]) + "; ");
                        strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(abs(newVec[1][0] - newVec[0][0])) + "; ");
                        double q = (x - newVec[Ga][0]) / abs((newVec[1][0] - newVec[0][0]));
                        strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(x) + " - "
                                       + QString::number(newVec[Ga][0]) + " )/ " + QString::number(abs(newVec[1][0] - newVec[0][0]))
                                + " = " + QString::number(q) + "; ");
                        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления s </b><b style=\"color: black;\">:</b><br>");

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

                             if(i % 3 != 0){
                                 qDebug() << "i: " << (2*i + 1)/3 << "STEP: " << STEP << "C_L: " << C[C.count() - 1 - i]  << "C_R: " << C[C.count() - 2 - i] << ";";
                                 int f = factorial(factorial, (2*i + 1)/3);
                                 double qr = Q(Q, (2*i + 1)/3);
                                 qDebug() << "factor(i): " << f << " Q(i): " << QString::number(qr);
                                 STEP = 0;
                                 return (C[C.count() - 1 - i] + C[C.count() - 2 - i]) * Q(Q, (2*i + 1)/3) / (2*factorial(factorial, (2*i + 1)/3)) + iter(iter, i + 2);
                             }else{
                                 qDebug() << "i: " << 2*i/3 << "; STEP:" << STEP << "C: " << C[C.count() - 1 - i] ;
                                  int f = factorial(factorial, (2*i + 1)/3);
                                  double qr = Q(Q, 2*i/3);
                                  qDebug() << "factor(i): " << f << " Q(i): " << QString::number(qr);
                                  STEP = 0;
                                 //qDebug() << "; factor(i):" << factorial(factorial, (2*i + 1)/3) << "; Q(i):"  << Q(Q, 2*i/3) << ";\n";
                                 return (C[C.count() - 1 - i] + 0) * Q(Q, 2*i/3) / factorial(factorial,  2*i/3) + iter(iter, i + 1);
                             }
                         };
                         return C[C.count() - 1] + ITER(ITER, 1);
                     };

                    auto P_n_s_1 = [&](double x) -> double {
                        QString strHtml;
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления s </b><b style=\"color: black;\">:</b><br>");
                        strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(x) + "; ");
                        strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(newVec[Ga][0]) + "; ");
                         double h = abs(newVec[1][0] - newVec[0][0]);
                        strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(h) + "; ");

                        double q = (x - newVec[Ga][0]) / h;
                        strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(x) + " - "
                                       + QString::number(newVec[Ga][0]) + " )/ " + QString::number(abs(newVec[1][0] - newVec[0][0]))
                                + " = " + QString::number(q) + "; ");
                        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления s </b><b style=\"color: black;\">:</b><br>");

                         auto ITER = [&](auto iter, size_t i) -> double {
                             if(i >= C.count() - 2/*COLUMN: y;*/ ) return 0;
                             auto factorial = [](auto fact, size_t i) -> double {
                                 return (i == 1 || i == 0) ? i/*База факториала*/ : i*fact(fact, i - 1);
                             };

                             static int STEP = 0;
                             auto Q = [&](auto Q, size_t i) -> double {
                                 static QVector<double> QS;
                                 int ST = STEP;
                                 double B_0 = q - STEP;
                                 double  B_1 = q + STEP;

                                 if(i == 1){
                                     QS.push_back(q);
                                     double SUM = 0;
                                     for(int i = 0; i < QS.count(); i++){
                                         double CONT = 1;
                                         for(int j = 0; j < QS.count(); j++){
                                             if(j != i){
                                                 CONT *= QS[j];
                                             }
                                         }
                                         SUM += CONT;
                                     }
                                     QS.clear();
                                     return SUM;
                                 }else if(i % 2 == 0){
                                     double V_1 = B_1;
                                     double sa = V_1*Q(Q, i - 1);
                                     QS.push_back(V_1);
                                     //QS.push_back(sa);
                                     return sa;
                                 }else{

                                     double V_0 = B_0;
                                     QS.push_back(V_0);
                                     STEP++;
                                     double sa = V_0*Q(Q, i - 1);
                                     //QS.push_back(sa);
                                     return sa;
                                 }
                             };

                             STEP = 0;

                             if(i % 3 != 0){
                                 qDebug() << "i: " << (2*i + 1)/3 << "STEP: " << STEP << "C_L: " << C[C.count() - 1 - i]  << "C_R: " << C[C.count() - 2 - i] << ";";
                                 int f = factorial(factorial, (2*i + 1)/3);
                                 double qr = Q(Q, (2*i + 1)/3);
                                 qDebug() << "factor(i): " << f << " Q(i): " << QString::number(qr);
                                 STEP = 0;
                                 return (C[C.count() - 1 - i] + C[C.count() - 2 - i]) * Q(Q, (2*i + 1)/3) / (2*factorial(factorial, (2*i + 1)/3)) + iter(iter, i + 2);
                             }else{
                                 qDebug() << "i: " << 2*i/3 << "; STEP:" << STEP << "C: " << C[C.count() - 1 - i] ;
                                  int f = factorial(factorial, (2*i + 1)/3);
                                  double qr = Q(Q, 2*i/3);
                                  qDebug() << "factor(i): " << f << " Q(i): " << QString::number(qr);
                                  STEP = 0;
                                 //qDebug() << "; factor(i):" << factorial(factorial, (2*i + 1)/3) << "; Q(i):"  << Q(Q, 2*i/3) << ";\n";
                                 return (C[C.count() - 1 - i] + 0) * Q(Q, 2*i/3) / (factorial(factorial,  2*i/3)*h) + iter(iter, i + 1);
                             }
                         };
                         return ITER(ITER, 1);
                    };

                    auto P_n_s_2 = [&](double x) -> double {
                        QString strHtml;
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления s </b><b style=\"color: black;\">:</b><br>");
                        strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(x) + "; ");
                        strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(newVec[Ga][0]) + "; ");
                         double h = abs(newVec[1][0] - newVec[0][0]);
                        strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(h) + "; ");
                        double q = (x - newVec[Ga][0]) / abs((newVec[1][0] - newVec[0][0]));
                        strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(x) + " - "
                                       + QString::number(newVec[Ga][0]) + " )/ " + QString::number(abs(newVec[1][0] - newVec[0][0]))
                                + " = " + QString::number(q) + "; ");
                        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления s </b><b style=\"color: black;\">:</b><br>");

                         auto ITER = [&](auto iter, size_t i) -> double {
                             if(i >= C.count() - 2/*COLUMN: y;*/ ) return 0;
                             auto factorial = [](auto fact, size_t i) -> double {
                                 return (i == 1 || i == 0) ? i/*База факториала*/ : i*fact(fact, i - 1);
                             };

                             static int STEP = 0;
                             auto Q = [&](auto Q, size_t i) -> double {
                                 static QVector<double> QS;
                                 static QVector<double> qs;
                                 int ST = STEP;
                                 double B_0 = q - STEP;
                                 double  B_1 = q + STEP;

                                 if(i == 1){
                                     QS.push_back(q);
                                     double SUM = 0;
                                     for(int i = 0; i < QS.count(); i++){
                                         for(int k = 0; k < QS.count(); k++){
                                             if(k != i){
                                                 qs.push_back(QS[k]);
                                             }

                                             if(k == QS.count() - 1){
                                                 for(int v = 0; v < qs.count(); v++){
                                                     double CONT = 1;
                                                     for(int j = 0; j < qs.count(); j++){
                                                         if(j != v){
                                                             CONT *= qs[j];
                                                         }
                                                     }
                                                     SUM += CONT;
                                                 }
                                                 qs.clear();
                                             }
                                         }
                                         //SUM += SUMK;
                                     }
                                     QS.clear();
                                     return SUM;
                                 }else if(i % 2 == 0){
                                     double V_1 = B_1;
                                     double sa = V_1*Q(Q, i - 1);
                                     QS.push_back(V_1);
                                     return sa;
                                 }else{

                                     double V_0 = B_0;
                                     QS.push_back(V_0);
                                     STEP++;
                                     return V_0*Q(Q, i - 1);
                                 }
                             };

                             STEP = 0;

                             if(i % 3 != 0){
                                 qDebug() << "i: " << (2*i + 1)/3 << "STEP: " << STEP << "C_L: " << C[C.count() - 1 - i]  << "C_R: " << C[C.count() - 2 - i] << ";";
                                 int f = factorial(factorial, (2*i + 1)/3);
                                 double qr = Q(Q, (2*i + 1)/3);
                                 qDebug() << "factor(i): " << f << " Q(i): " << QString::number(qr);
                                 STEP = 0;
                                 return (C[C.count() - 1 - i] + C[C.count() - 2 - i]) * Q(Q, (2*i + 1)/3) / (2*factorial(factorial, (2*i + 1)/3)) + iter(iter, i + 2);
                             }else{
                                 qDebug() << "i: " << 2*i/3 << "; STEP:" << STEP << "C: " << C[C.count() - 1 - i] ;
                                  int f = factorial(factorial, (2*i + 1)/3);
                                  double qr = Q(Q, 2*i/3);
                                  qDebug() << "factor(i): " << f << " Q(i): " << QString::number(qr);
                                  STEP = 0;
                                 //qDebug() << "; factor(i):" << factorial(factorial, (2*i + 1)/3) << "; Q(i):"  << Q(Q, 2*i/3) << ";\n";
                                 return (C[C.count() - 1 - i] + 0) * Q(Q, 2*i/3) / (factorial(factorial,  2*i/3)*qPow(h,2)) + iter(iter, i + 1);
                             }
                         };
                         return ITER(ITER, 1);
                    };

                   int m_s = 0;
                   for(size_t j = C_s[0]; j <= C_s[1]; j += 2){
                       double x = 5.83 - 0.09*j;

                       for(size_t i = 0; i < CN; i++){
                           if(i == 0){
                               step_a = abs(A[i][0] - x);
                               Ga = i;
                           }else if ( (step_a > (A[i][0] - x))  && (A[i][0] <= x)){
                               step_a = abs(A[i][0] - x);
                               Ga = i;
                           }

                           if(i == 0){
                               step_b = abs(A[(CN-1)][0] - x);
                               Gb = (CN - 1);
                           }else if ( (step_b > (A[(CN-1) - i][0] - x)) && (A[(CN-1) - i][0] >= x)){
                               //qDebug() << step_b;
                               step_b = abs(A[(CN-1) - i][0] - x);
                               Gb = (CN-1) - i;
                           }
                       }


                       auto print_general_S = [&](QVector<QVector<double>>& vec, size_t Ga, QVector<double>& c) -> void {
                           strHtml_A.clear();
                           strHtml_A.append("<b style=\"color: green;\">Предварительное выделение элементов для  И. Ф. C. </b><b style=\"color: black;\">:</b><br>");
                           strHtml_A.append("<b>newVec :</b><table border=1 style=\"border-collapse: collapse;\">");

                           for(size_t i = 0; i < CN; i++){
                               QVector<double> c_t(0, 0);
                               strHtml_A.append("<tr>");
                               for(size_t j = 0; j < vec[i].count(); j++){
                                   if((j % 2 == 0 && i < Ga+1 && j != 0) && (j == (double)2*(Ga-i)) || ((j % 2 == 1 && i < Ga+1 && j != 0) && (j == (double)2*(Ga-i)+1)) || ((j % 2 == 0 && i < Ga+1 && j != 0) && (j == (double)2*(Ga+1-i))) ){
                                      vec[i][j] == 0 ? strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',0) + "</b></td>")
                                                     : strHtml_A.append("<td align=center><b style=\"color: DarkCyan;\"> " + QString::number(vec[i][j],'f',3) + "</b></td>");
                                      if (c_t.count() == 2){
                                          c_t.push_front(vec[i][j]);
                                          foreach(auto cct, c_t){
                                              c.push_back(cct);
                                          };

                                          c_t.clear();
                                      }else if((i == Ga) && (c_t.count() == 1)){
                                          c_t.push_front(vec[i][j]);
                                          foreach(auto cct, c_t){
                                              c.push_back(cct);
                                          }

                                          c_t.clear();
                                      }else if ((j == vec[i].count() - 1) && (c_t.count() == 1)){
                                          //c_t.push_front(vec[i][j]);

                                          if(c_t.count() == 1){
                                                c_t.push_front(vec[i][j]);
                                                foreach(auto cct, c_t){
                                                    c.push_back(cct);
                                                }

                                                c_t.clear();
                                         }
                                      }else{
                                          c_t.push_front(vec[i][j]);
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

                       /*auto print_general_S = [&](QVector<QVector<double>>& vec, size_t Ga, QVector<double>& c) -> void {
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
                       };*/

                       print_general_S(newVec, Ga, C);

                       double s = P_n_s(x);
                       double y = P_n_s_1(x);
                       double z = P_n_s_2(x);

                       S[m_s][0] = x;
                       S[m_s][1] = s;

                       Y[m_s][0] = x;
                       Y[m_s][1] = y;

                       Z[m_s][0] = x;
                       Z[m_s][1] = z;

                       m_s++;

                       ///print_general_s_1(S);// без производной;
                       ///print_general_s_1_1(Y);// c 1 производной;
                       ///print_general_s_1_2(Z);// c 2 производной;

                       C.clear();
                   }

                   print_general_s_1(S);// без производной;
                   print_general_s_1_1(Y);// c 1 производной;
                   print_general_s_1_2(Z);// c 2 производной;


                }

                Y.clear();
                Z.clear();
                S.clear();

                // + Интерполяционная формула Лагранжа:
                {
                    auto Duble_A = A;

                    W = QVector<QVector<double>>(Duble_A.count(),QVector<double>(3, 0));
                    for(size_t i = 0; i < Duble_A.count(); i++){
                        for(size_t j = 1; j < 3; j++){
                            W[i][j-1] = Duble_A[i][j - 1];
                        }
                    }

                    print_general(W);

                    double q;

                    auto print_general_o = [&](QVector<QVector<double>>& vec) -> void {
                        strHtml_A.clear();
                        strHtml_A.append("<b style=\"color: red;\">Вычисления без производной для И. Ф. Л. </b><b style=\"color: black;\">:</b><br>");
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

                    auto print_general_o_1 = [&](QVector<QVector<double>>& vec) -> void {
                        strHtml_A.clear();
                        strHtml_A.append("<b style=\"color: red;\">Вычисления по 1 производной для И. Ф. Л. </b><b style=\"color: black;\">:</b><br>");
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

                    auto print_general_o_2 = [&](QVector<QVector<double>>& vec) -> void {
                        strHtml_A.clear();
                        strHtml_A.append("<b style=\"color: red;\">Вычисления по 2 производной для И. Ф. Л. </b><b style=\"color: black;\">:</b><br>");
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

                    auto P_n_L = [&, W = Duble_A](auto P_n_L, double x, int32_t i = 0) -> double {

                        if(i >= W.count()) return 0;

                        auto Z = [q = q](auto z, double x, QVector<QVector<double>> W, int32_t i, int32_t j = 0) -> double {
                            static QVector<double> QZ;
                            if(i == j){
                                //QZ.push_back(1);
                                return z(z, x, W, i, j + 1);
                            }else if(i >= W.count() || j >= W.count()){
                                QZ.clear();
                                return 1;
                            }else{
                                QZ.push_back(q - j);
                                return (q - j)*z(z, x, W, i , j + 1);
                            }
                        };

                        auto factorial = [](auto fact, size_t i) -> double {
                            return (i < 2) ? 1/*База факториала*/ : i*fact(fact, i - 1);
                        };

                        double fr = factorial(factorial, i)*factorial(factorial, W.count() - 1 - i);
                        double h = abs((newVec[1][0] - newVec[0][0]));

                        double Z_z = Z(Z, x, W, i);

                       return ((W.count() - 1 - i) % 2 == 0)
                               ?  Z_z*W[i][1]/fr + P_n_L(P_n_L, x, i + 1)
                               : (-1)*Z_z*W[i][1]/fr + P_n_L(P_n_L, x, i + 1);
                    };

                   auto P_n_L_1 = [&, W = Duble_A](auto P_n_L, double x, int32_t i = 0) -> double {

                       if(i >= W.count()) return 0;

                       auto Z = [q = q](auto z, double x, QVector<QVector<double>> W, int32_t i, int32_t j = 0) -> double {
                           static QVector<double> QZ;
                           if(i == j){
                               //QZ.push_back(1);
                               return z(z, x, W, i, j + 1);
                           }else if(i >= W.count() || j >= W.count()){

                               double SUM = 0;
                               for(int k = 0; k < QZ.count(); k++){
                                   double CONT = 1;
                                   for(int n = 0; n < QZ.count(); n++){
                                       if(n != k){
                                           CONT *= QZ[n];
                                       }
                                   }
                                   SUM += CONT;
                               }

                               QZ.clear();
                               return SUM;
                           }else{
                               QZ.push_back(q - j);
                               return z(z, x, W, i , j + 1);
                           }
                       };

                       auto factorial = [](auto fact, size_t i) -> double {
                           return (i < 2) ? 1/*База факториала*/ : i*fact(fact, i - 1);
                       };

                       double fr = factorial(factorial, i)*factorial(factorial, W.count() - 1 - i);
                       double h = abs((newVec[1][0] - newVec[0][0]));

                       double Z_z = Z(Z, x, W, i);

                      return ((W.count() - 1 - i) % 2 == 0)
                              ?  Z_z*W[i][1]/(fr*h) + P_n_L(P_n_L, x, i + 1)
                              : (-1)*Z_z*W[i][1]/(fr*h) + P_n_L(P_n_L, x, i + 1);
                   };

                  auto P_n_L_2 = [&, W = Duble_A](auto P_n_L, double x, int32_t i = 0) -> double {

                      if(i >= W.count()) return 0;

                      auto Z = [q = q](auto z, double x, QVector<QVector<double>> W, int32_t i, int32_t j = 0) -> double {
                          static QVector<double> QZ;
                          static QVector<double> qz;
                          if(i == j){
                              //QZ.push_back(1);
                              return z(z, x, W, i, j + 1);
                          }else if(i >= W.count() || j >= W.count()){

                              double SUM = 0;
                              for(int n = 0; n < QZ.count(); n++){
                                  for(int k = 0; k < QZ.count(); k++){
                                      if(k != n){
                                          qz.push_back(QZ[k]);
                                      }

                                      if(k == QZ.count() - 1){
                                          for(int v = 0; v < qz.count(); v++){
                                              double CONT = 1;
                                              for(int t = 0; t < qz.count(); t++){
                                                  if(t != v){
                                                      CONT *= qz[t];
                                                  }
                                              }
                                              SUM += CONT;
                                          }
                                          qz.clear();
                                      }
                                  }
                                  //SUM += SUMK;
                              }
                              QZ.clear();
                              return SUM;
                          }else{
                              QZ.push_back(q - j);
                              return z(z, x, W, i , j + 1);
                          }
                      };

                      auto factorial = [](auto fact, size_t i) -> double {
                          return (i < 2) ? 1/*База факториала*/ : i*fact(fact, i - 1);
                      };

                      double fr = factorial(factorial, i)*factorial(factorial, W.count() - 1 - i);
                      double h = abs((newVec[1][0] - newVec[0][0]));

                      double Z_z = Z(Z, x, W, i);

                     return ((W.count() - 1 - i) % 2 == 0)
                             ?  Z_z*W[i][1]/(fr*h) + P_n_L(P_n_L, x, i + 1)
                             : (-1)*Z_z*W[i][1]/(fr*h) + P_n_L(P_n_L, x, i + 1);
                  };

                    P = QVector<QVector<double>>((D[1] - D[0])/2+1, QVector<double>(2, 0));
                    Y = QVector<QVector<double>>((D[1] - D[0])/2+1, QVector<double>(2, 0));
                    Z = QVector<QVector<double>>((D[1] - D[0])/2+1, QVector<double>(2, 0));

                    int m = 0;

                    for(int i = D[0]; i <= D[1]; i+=2){

                        double x = 5.81 - 0.09*i;

                        // Не требуется:
                        for(size_t i = 0; i < CN; i++){
                            if(i == 0){
                                step_a = abs(A[i][0] - x);
                                Ga = i;
                            }else if ( (step_a > (A[i][0] - x))  && (A[i][0] <= x)){
                                step_a = abs(A[i][0] - x);
                                Ga = i;
                            }

                            if(i == 0){
                                step_b = abs(A[(CN-1)][0] - x);
                                Gb = (CN - 1);
                            }else if ( (step_b > (A[(CN-1) - i][0] - x)) && (A[(CN-1) - i][0] >= x)){
                                //qDebug() << step_b;
                                step_b = abs(A[(CN-1) - i][0] - x);
                                Gb = (CN-1) - i;
                            }
                        }
                        Ga = 0;

                        QString strHtml;
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления s_s </b><b style=\"color: black;\">:</b><br>");
                        strHtml.append("<b style=\"color: green;\" >x = </b> "+ QString::number(x) + "; ");
                        strHtml.append("<b style=\"color: green;\" >x_0 = </b> "+ QString::number(newVec[Ga][0]) + "; ");
                        strHtml.append("<b style=\"color: green;\" >h = </b> "+ QString::number(abs(newVec[1][0] - newVec[0][0])) + "; ");
                        q = (x - newVec[Ga][0]) / abs((newVec[1][0] - newVec[0][0]));
                        strHtml.append("<b style=\"color: blue;\" >q = (x - x_0) / h = </b> ("  + QString::number(x) + " - "
                                       + QString::number(newVec[0][0]) + " )/ " + QString::number(abs(newVec[1][0] - newVec[0][0]))
                                + " = " + QString::number(q) + "; ");
                        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml + "<p></p>");
                        strHtml.clear();
                        strHtml.append("<b style=\"color: red;\">Вычисления s </b><b style=\"color: black;\">:</b><br>");

                        double p = P_n_L(P_n_L, x);
                        double y = P_n_L_1(P_n_L_1, x);
                        double z = P_n_L_2(P_n_L_2, x);

                        P[m][0] = x;
                        P[m][1] = p;

                        Y[m][0] = x;
                        Y[m][1] = y;

                        Z[m][0] = x;
                        Z[m][1] = z;

                        m++;
                    }

                    print_general_o(P);
                    print_general_o_1(Y);
                    print_general_o_2(Z);
                }
            }
        };
        general(general, n, A, C);// A - таблица данных, С - границы таблицы, n - начальное состояние
    };
    general_i();

    ////////////////////////////////////////////////
    //ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Номер варианта:</b> N = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    QTime finish = QTime::currentTime();
    double time = start_1.msecsTo(finish) / 1000.0;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<hr>" + "<b>Время работы: </b> " +  QString::number(time) + " ;");

}
