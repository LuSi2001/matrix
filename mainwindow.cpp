#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mspmatrix.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Matrix<int> m(2, 3);
    Matrix<int> o(2, 3);
    qDebug() << m;
    for(int i = 0; i < m.rows(); i++)
    {
        for(int j = 0; j < m.columns(); j++)
        {
            m[i][j] = 1;
            o[i][j] = 2;
        }
    }
    qDebug() << m;
    qDebug() << o;
    qDebug() << m + o;
    qDebug() << m - o;
    QList<int> col1 = {1, 3, 3, 4};
    QList<int> col2 = {2, 4, 5, 5};
    Matrix<int> a({col1, col2});
    QList<int> col4 = {1, 3};
    QList<int> col5 = {2, 4};
    QList<int> col6 = {3, 5};
    QList<int> col7 = {4, 6};
    Matrix<int> b({col4, col5, col6, col7});
    qDebug() << a;
    qDebug() << b;
    qDebug() << a * b;
    Matrix<int> c(2, 4);
    qDebug() << c;
    qDebug() << c.transponed();
    Matrix<int> d({{2, 1, 3}, {3, 4, 3}, {0, 5, 3}, {2, 4, 5}});
    qDebug() << d;
    qDebug() << d.transponed();
    d.transpone();
    qDebug() << d;
    qDebug() << d * 2;
    qDebug() << 3 * d;
    Matrix<int> e({{2, 2, 2}, {2, 3, 2}, {2, 2, 2}});
    qDebug() << e * e;
    qDebug() << (e^5);
}

MainWindow::~MainWindow()
{
    delete ui;
}
