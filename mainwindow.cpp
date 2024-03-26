#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/darlix/Рабочий стол/e/projects_db/db/Library.db");

    // Проверка соединения с базой данных
    if (!db.open()) {
        qDebug() << "Ошибка соединения с базой данных:" << db.lastError().text();
        return;
    }

    // Создание модели данных и установка запроса
    model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM Книги", db);

    // Установка модели данных в QTableView
    ui->tableView->setModel(model);
}


MainWindow::~MainWindow()
{
    delete ui;
}
