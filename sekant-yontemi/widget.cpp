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
    return x * exp(-x) + pow(x, 3) + 1;
}

void Widget::on_pushButton_clicked()
{
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setRowCount(20);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("x0"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("x1"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("f(x0)"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("f(x1)"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("x2"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("|Dx|"));

    double x0 = ui->le_x0->text().toDouble();
    double x1 = ui->le_x1->text().toDouble();
    double eps = 1e-6;
    double Dx;
    int i = 0;
    double p, q, x2;
    do {
        p = x0 * f(x1) - x1 * f(x0);
        q = f(x1) - f(x0);
        x2 = p / q;
        Dx = fabs(x2 - x1);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(x0, 'f', 15)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(x1, 'f', 15)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(f(x0), 'f', 15)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(f(x1), 'f', 15)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(x2, 'f', 15)));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(Dx, 'f', 15)));
        x0 = x1;
        x1 = x2;
        i++;
    } while (Dx > eps);
    ui->lbl_durum->setText(QString("%1. iterasyonda yakınsama sağlandı.").arg(i));

}
