#include "arriwal.h"
#include "ui_arriwal.h"
#include "tabprod.h"
#include "mainwindow.h"

arriwal::arriwal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::arriwal)
{
    ui->setupUi(this);
    connect(ui->ExitBtn, &QPushButton::clicked, this, &arriwal::exitApplication);
    connect(ui->AddBtn, &QPushButton::clicked, this, &arriwal::addBook);
    // Подключение сигнала нажатия кнопки к слоту deleteBook()
    connect(ui->DeleteBtn, &QPushButton::clicked, this, &arriwal::deleteBook);
    // Подключение сигнала нажатия кнопки к слоту updateBook()
    connect(ui->UpdateBtn, &QPushButton::clicked, this, &arriwal::updateBookField);
    connect(ui->tabProdBtn, &QPushButton::clicked, this, &arriwal::openTabProdForm);
    connect(ui->tabArriwal, &QPushButton::clicked, this, &arriwal::openForm);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/darlix/Рабочий стол/e/projects_db/db/library.db");

    if (!db.open()) {
        qDebug() << "Ошибка соединения с базой данных:" << db.lastError().text();
        return;
    }
}
    void arriwal::addBook()
    {
        QString documentNum = ui->lineEdit->text();
        QString providerInfo = ui->lineEdit_2->text();
        QString countExempl = ui->lineEdit_3->text();

        QSqlQuery query;
        query.prepare("INSERT INTO ArriwalBooks (document_num, provider_info, count_exempl) "
                      "VALUES (:documentNum, :providerInfo, :countExempl)");
        query.bindValue(":documentNum", documentNum);
        query.bindValue(":providerInfo", providerInfo);
        query.bindValue(":countExempl", countExempl);

        if (!query.exec()) {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return;
        }

        model->setQuery("SELECT * FROM ArriwalBooks", db);
    }

    // Удаление выбранного элемента из таблицы
    void arriwal::deleteBook() {
        // Получаем индекс выбранной строки в таблице
        QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();

        // Если ни одна строка не выбрана, выходим из функции
        if(selectedIndexes.isEmpty())
            return;

        // Получаем индекс первой выбранной строки
        QModelIndex selectedIndex = selectedIndexes.at(0);

        // Получаем значение ID выбранного элемента
        int id = model->data(model->index(selectedIndex.row(), 0)).toInt();

        // Подготавливаем SQL-запрос для удаления выбранного элемента из таблицы ArriwalBooks
        QSqlQuery query;
        query.prepare("DELETE FROM ArriwalBooks WHERE id_ArriwalBooks = :id");
        query.bindValue(":id", id);

        // Выполняем запрос на удаление записи
        if (!query.exec()) {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return;
        }

        // Обновляем модель данных, чтобы отобразить изменения в tableView
        model->setQuery("SELECT * FROM ArriwalBooks", db);
    }

    void arriwal::updateBookField() {
        // Получаем индекс выбранной ячейки
        QModelIndex selectedIndex = ui->tableView->currentIndex();

        // Получаем номер столбца выбранной ячейки
        int column = selectedIndex.column();

        // Получаем значение ID выбранного элемента
        int id = model->data(model->index(selectedIndex.row(), 0)).toInt();

        // Получаем новое значение поля для обновления
        QString newValue = ui->lineEdit_7->text(); // Предполагается, что у вас есть QLineEdit для ввода нового значения

        // Получаем название столбца по его номеру
        QString columnName = model->headerData(column, Qt::Horizontal).toString();

        // Подготавливаем SQL-запрос для обновления поля в таблице ArriwalBooks
        QSqlQuery query;
        query.prepare("UPDATE ArriwalBooks SET " + columnName + " = :newValue WHERE id_ArriwalBooks = :id");
        query.bindValue(":newValue", newValue);
        query.bindValue(":id", id);

        // Выполняем запрос на обновление поля
        if (!query.exec()) {
            qDebug() << "Ошибка выполнения запроса на обновление поля:" << query.lastError().text();
            return;
        }

        model->setQuery("SELECT * FROM ArriwalBooks", db);
    }
    void arriwal::exitApplication()
    {
        QApplication::quit(); // Выход из приложения
    }
void arriwal::openForm() {
    MainWindow *m = new MainWindow();
    m->show();
    this->close();
}

void arriwal::openTabProdForm() {
    tabProd *tabProdForm = new tabProd();
    tabProdForm->show();
    this->close();
}

arriwal::~arriwal()
{
    delete ui;
}
