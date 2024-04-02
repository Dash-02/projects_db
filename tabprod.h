#ifndef TABPROD_H
#define TABPROD_H

#include <QWidget>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QPushButton>
#include <QSqlQuery>
#include <QObject>
#include <QLineEdit>

namespace Ui {
class tabProd;
}

class tabProd : public QWidget
{
    Q_OBJECT

public:
    explicit tabProd(QWidget *parent = nullptr);
    ~tabProd();

private:
    void exitApplication();
    void addBook();
    void deleteBook();
    void updateBookField();
    void openForm();
    void openFormArriwal();

    Ui::tabProd *ui;

    QSqlDatabase db;
    QSqlQueryModel *model;
    QPushButton *ExitBtn;
    QPushButton *AddBtn;
    QPushButton *DeleteBtn;
    QPushButton *UpdateBtn;
    QPushButton *back;
    QPushButton *tabArriwal;
};

#endif // TABPROD_H
