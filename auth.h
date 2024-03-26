#ifndef AUTH_H
#define AUTH_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

namespace Ui {
class auth;
}

class auth : public QWidget
{
    Q_OBJECT
    QSqlDatabase db;
    bool isAdmin;

public:
    explicit auth(QWidget *parent = nullptr);
    ~auth();

private slots:
    void exitApplication(); // Слот для выхода из приложения
    // bool Login(); // Слот для проверки авторизации
    void funcAuth(); // Слот для авторизации
    void execMainWin(); // Слот для открытия нового окна и закрытия текущего

private:
    Ui::auth *ui;
    QPushButton *btn_Exit; // Кнопка для выхода из приложения
};

#endif // AUTH_H
