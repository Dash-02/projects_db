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

    if(log == "admin" && pass == "admin")
    {
        isAdmin = true;
        MainWindow *m = new MainWindow();
        m->show();
        this->close();
    } else if(log == "user" && pass == "user")
    {
        isAdmin = false;
        MainWindow *m = new MainWindow();
        m->show();
        this->close();
    } else {
        isAdmin = false;
        QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
    }

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
