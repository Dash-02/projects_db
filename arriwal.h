#ifndef ARRIWAL_H
#define ARRIWAL_H

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
class arriwal;
}

class arriwal : public QWidget
{
    Q_OBJECT

public:
    explicit arriwal(QWidget *parent = nullptr);
    ~arriwal();

private:
    Ui::arriwal *ui;

    void exitApplication();
    void addBook();
    void deleteBook();
    void updateBookField();
    void openTabProdForm();
    void openForm();

    QSqlDatabase db;
    QSqlQueryModel *model;
    QPushButton *ExitBtn;
    QPushButton *AddBtn;
    QPushButton *DeleteBtn;
    QPushButton *UpdateBtn;
    QPushButton *tabProdBtn;
    QPushButton *tabArriwal;
};

#endif // ARRIWAL_H
