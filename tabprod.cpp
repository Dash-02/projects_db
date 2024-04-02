#include "tabprod.h"
#include "ui_tabprod.h"
#include "mainwindow.h"
#include "arriwal.h"

tabProd::tabProd(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tabProd)
{
    ui->setupUi(this);
    connect(ui->ExitBtn, &QPushButton::clicked, this, &tabProd::exitApplication);
    connect(ui->AddBtn, &QPushButton::clicked, this, &tabProd::addBook);
    // Подключение сигнала нажатия кнопки к слоту deleteBook()
    connect(ui->DeleteBtn, &QPushButton::clicked, this, &tabProd::deleteBook);
    // Подключение сигнала нажатия кнопки к слоту updateBook()
    connect(ui->UpdateBtn, &QPushButton::clicked, this, &tabProd::updateBookField);
    connect(ui->back, &QPushButton::clicked, this, &tabProd::openForm);
    connect(ui->tabArriwal, &QPushButton::clicked, this, &tabProd::openFormArriwal);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/darlix/Рабочий стол/e/projects_db/db/library.db");

    if (!db.open()) {
        qDebug() << "Ошибка соединения с базой данных:" << db.lastError().text();
        return;
    }

    model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM Sales", db);

    ui->tableView->setModel(model);
}

void tabProd::exitApplication()
{
    QApplication::quit();
}

void tabProd::addBook()
{
    QString nameBook = ui->lineEdit->text();
    QString genre = ui->lineEdit_2->text();
    QString authors = ui->lineEdit_3->text();
    QString publishingHouse = ui->lineEdit_4->text();
    QString numberPages = ui->lineEdit_5->text();
    QString countBooks = ui->lineEdit_6->text();

    QSqlQuery query;
    query.prepare("INSERT INTO Books (name_book, genre, authors, publishing_house, number_pages, count_boks) "
                  "VALUES (:nameBook, :genre, :authors, :publishingHouse, :numberPages, :countBooks)");
    query.bindValue(":nameBook", nameBook);
    query.bindValue(":genre", genre);
    query.bindValue(":authors", authors);
    query.bindValue(":publishingHouse", publishingHouse);
    query.bindValue(":numberPages", numberPages);
    query.bindValue(":countBooks", countBooks);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    model->setQuery("SELECT * FROM Sales", db);
}

// Удаление выбранного элемента из таблицы
void tabProd::deleteBook() {
    // Получаем индекс выбранной строки в таблице
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();

    // Если ни одна строка не выбрана, выходим из функции
    if(selectedIndexes.isEmpty())
        return;

    // Получаем индекс первой выбранной строки
    QModelIndex selectedIndex = selectedIndexes.at(0);

    // Получаем значение ID выбранного элемента
    int id = model->data(model->index(selectedIndex.row(), 0)).toInt();

    // Подготавливаем SQL-запрос для удаления выбранного элемента из таблицы Books
    QSqlQuery query;
    query.prepare("DELETE FROM Books WHERE id_Books = :id");
    query.bindValue(":id", id);

    // Выполняем запрос на удаление записи
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    // Обновляем модель данных, чтобы отобразить изменения в tableView
    model->setQuery("SELECT * FROM Sales", db);
}

void tabProd::updateBookField() {
    // Получаем индекс выбранной ячейки
    QModelIndex selectedIndex = ui->tableView->currentIndex();

    // Получаем номер столбца выбранной ячейки
    int column = selectedIndex.column();

    // Получаем значение ID выбранного элемента
    int id = model->data(model->index(selectedIndex.row(), 0)).toInt();

    // Получаем новое значение поля для обновления
    QString newValue = ui->lineEdit_4->text(); // Предполагается, что у вас есть QLineEdit для ввода нового значения

    // Получаем название столбца по его номеру
    QString columnName = model->headerData(column, Qt::Horizontal).toString();

    // Подготавливаем SQL-запрос для обновления поля в таблице Books
    QSqlQuery query;
    query.prepare("UPDATE Books SET " + columnName + " = :newValue WHERE id_Books = :id");
    query.bindValue(":newValue", newValue);
    query.bindValue(":id", id);

    // Выполняем запрос на обновление поля
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса на обновление поля:" << query.lastError().text();
        return;
    }

    model->setQuery("SELECT * FROM Sales", db);
}

void tabProd::openForm() {
    MainWindow *m = new MainWindow();
    m->show();
    this->close();
}

void tabProd::openFormArriwal() {
    arriwal *a = new arriwal();
    a->show();
    this->close();
}

tabProd::~tabProd()
{
    delete ui;
}
