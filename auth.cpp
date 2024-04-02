#include "auth.h"
#include "ui_auth.h"
#include "mainwindow.h"

auth::auth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auth)
{
    ui->setupUi(this);
    connect(ui -> btn_Exit, &QPushButton::clicked, this, &auth::exitApplication); // Соединение сигнала нажатия кнопки со слотом
    // connect(ui -> lineLogin, &QLineEdit::text, this, &auth::Login);
    // connect(ui -> linePass, &QLineEdit::text, this, &auth::Login);
    connect(ui -> btnAuth, &QPushButton::clicked, this, &auth::funcAuth);
    QT_FEATURE_pushbutton;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/darlix/Рабочий стол/e/projects_db/db/library.db");

    if (!db.open()) {
         qDebug() << "Ошибка соединения с базой данных:" << db.lastError().text();

     }
     db.close();
}

auth::~auth()
{
    delete ui;
}

void auth::exitApplication()
{
    QApplication::quit(); // Выход из приложения
}

// bool auth::Login()
// {
//     QString log = ui->lineLogin->text();
//     QString pass = ui->linePass->text();

//     if(log == "admin" && pass == "admin")
//     {
//         return isAuth = true;
//     } else {
//         return isAuth = false;
//     }
// }

void auth::funcAuth()
{
    QString log = ui->lineLogin->text();
    QString pass = ui->linePass->text();
    // Открываем соединение с базой данных
    qDebug() << "Пытаюсь открыть базу данных...";
    qDebug() << "Путь к базе данных:" << db.databaseName();

    if (!db.open()) {
        qDebug() << "Ошибка соединения с базой данных:" << db.lastError().text();
        return;
    }

    // Подготавливаем SQL-запрос для получения данных пользователя с указанным логином и паролем
    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE login = :login AND password = :password");
    query.bindValue(":login", log);
    query.bindValue(":password", pass);

    // Выполняем запрос
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        db.close(); // Закрываем соединение с базой данных
        return;
    }

    // Проверяем, есть ли данные в результате запроса
    if (query.next()) {
        // Пользователь с указанным логином и паролем найден
        isAdmin = (query.value(3).toInt() == 1); // Предполагаем, что 4-й столбец в таблице Users указывает на роль пользователя (админ или обычный)
        db.close(); // Закрываем соединение с базой данных
        execMainWin();
    } else {
        // Пользователь не найден или введены неправильные логин/пароль
        db.close(); // Закрываем соединение с базой данных
        QMessageBox::critical(this, "Ошибка", "Пользователь не найден");
    }
    // QString log = ui->lineLogin->text();
    // QString pass = ui->linePass->text();

    // if(log == "sukuna" && pass == "admin")
    // {
    //     isAdmin = true;
    //     execMainWin();
    // } else if(log == "user" && pass == "user")
    // {
    //     isAdmin = false;
    //     execMainWin();
    // } else {
    //     isAdmin = false;
    //     QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
    // }

    // if(isAuth == true)
    // {
    //     MainWindow *m = new MainWindow();
    //     m->show();
    //     this->close();
    // }
    // else {
    //     QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
    // }
}

void auth::execMainWin()
{
    MainWindow *m = new MainWindow();
    m->show();
    this->close();
}
