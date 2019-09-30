#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "sortalgos.hpp"
#include "sortalgos.cpp"

#include <QMainWindow>
#include <QMessageBox>
#include <QtCharts>
#include <QProcess>
#include <aboutwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    ArraySequence<int> *seqA1 = nullptr;
    ArraySequence<int> *seqA2 = nullptr;
    ListSequence<int> *seqL1 = nullptr;
    ListSequence<int> *seqL2 = nullptr;
    QString type;
    double time1 = .0;
    double time2 = .0;
    double time = .0;
};
#endif // MAINWINDOW_H
