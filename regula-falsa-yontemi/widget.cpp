#include "widget.h"
#include "ui_widget.h"
#include <math.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

double f(double x) {
    return 10 * exp(-x/2) * (cos(6.0 * x) + sin(8.0 * x));
}

void Widget::on_pushButton_clicked()
{
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(30);
    double a = ui->le_a->text().toDouble();
    double b = ui->le_b->text().toDouble();
    double c;
    double eps = 1e-6;
    int i = 0;
    do {
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(a)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(b)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(f(a))));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(f(b))));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(c)));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(f(c))));
        i++;
        if (f(a) * f(c) > 0) {
            a = c;
        } else {
            b = c;
        }
    } while (fabs(f(c)) > eps);
}
