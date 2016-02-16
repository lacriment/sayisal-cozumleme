#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double f(double x) {
    return x * exp(-x) + pow(x, 3.0) + 1;
}

void MainWindow::on_pushButton_clicked()
{

    double a = ui->le_a->text().toDouble();
    double b = ui->le_b->text().toDouble();
    double eps = 1e-6;
    int n = 1;
    double m;

    if (f(a) * f(b) > 0) {
        ui->lbl_durum->setText("Verilen aralıkta kök yoktur.");
    }
    else {
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->setColumnCount(9);
        ui->tableWidget->setRowCount(30);
        for (int i = 0; i < 9; i++) {
            ui->tableWidget->setColumnWidth(i,50);
        }
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem("#"));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem("a"));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem("b"));
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem("m"));
        ui->tableWidget->setItem(0, 4, new QTableWidgetItem("f(a)"));
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem("f(b)"));
        ui->tableWidget->setItem(0, 6, new QTableWidgetItem("f(m)"));
        ui->tableWidget->setItem(0, 7, new QTableWidgetItem("f(a) * f(m)"));
        ui->tableWidget->setItem(0, 8, new QTableWidgetItem("abs((b - a) / 2))"));


        while (fabs((b - a) / 2) > eps) {
            m = (a + b) / 2;
            ui->tableWidget->setItem(n, 0, new QTableWidgetItem(QString::number(n)));
            ui->tableWidget->setItem(n, 1, new QTableWidgetItem(QString::number(a)));
            ui->tableWidget->setItem(n, 2, new QTableWidgetItem(QString::number(b)));
            ui->tableWidget->setItem(n, 3, new QTableWidgetItem(QString::number(m)));
            ui->tableWidget->setItem(n, 4, new QTableWidgetItem(QString::number(f(a))));
            ui->tableWidget->setItem(n, 5, new QTableWidgetItem(QString::number(f(b))));
            ui->tableWidget->setItem(n, 6, new QTableWidgetItem(QString::number(f(m))));
            ui->tableWidget->setItem(n, 7, new QTableWidgetItem(QString::number( f(a) * f(m) )));
            ui->tableWidget->setItem(n, 8, new QTableWidgetItem(
                                         QString::number( fabs((b-a)/2) )
                                         ));
            if (f(a) * f(m) < 0){
                b = m;
            } else {
                a = m;
            }
            n++;
        }
        ui->lbl_durum->setText(QString("%1. iterasyonda yakınsama sağlandı.").arg(n-1));
    }
}
