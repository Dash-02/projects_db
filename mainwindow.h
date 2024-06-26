#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTableView *tableView;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void exitApplication();
    void addBook();
    void deleteBook();
    void updateBookField();
    void openTabProdForm();
    void openTabArriwal();
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    QPushButton *ExitBtn;
    QPushButton *AddBtn;
    QPushButton *DeleteBtn;
    QPushButton *UpdateBtn;
    QPushButton *tabProdBtn;
    QPushButton *tabArriwal;
};
#endif // MAINWINDOW_H
