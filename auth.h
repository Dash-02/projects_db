#ifndef AUTH_H
#define AUTH_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

namespace Ui {
class auth;
}

class auth : public QWidget
{
    Q_OBJECT
    bool isAdmin;

public:
    explicit auth(QWidget *parent = nullptr);
    ~auth();

private slots:
    void exitApplication(); // Слот для выхода из приложения
    // bool Login(); // Слот для проверки авторизации
    void funcAuth(); // Слот для авторизации

private:
    Ui::auth *ui;
    QPushButton *btn_Exit; // Кнопка для выхода из приложения
};

#endif // AUTH_H
