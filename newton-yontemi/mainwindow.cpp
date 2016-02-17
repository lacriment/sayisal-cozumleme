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

double df(double x) {
    return exp(-x) - x * exp(-x) + 3 * pow(x,2);
}

void MainWindow::on_solve_clicked()
{
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setRowCount(20);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("i"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("xi"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("f(xi)"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("f'(xi)"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("xi + 1"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("|Dx|"));

    double x0 = ui->le_baslangic->text().toDouble();
    double x1;
    double eps = 1e-6;
    double Dx;
    int i = 0;
    do {
        x1 = x0 - f(x0)/df(x0);
        Dx = fabs(x1 - x0);

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(x0)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(f(x0))));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(df(x0))));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(x1)));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(Dx)));

        x0 = x1;
        i++;
    } while (Dx > eps);
}
