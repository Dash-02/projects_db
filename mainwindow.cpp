#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Книги");

    QWidget->findChild<QTableView*>("tableView");
    tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
