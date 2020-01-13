#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QtCharts>
#include <QMenuBar>
#include "sequences.hpp"
#include "dictionaries.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Student {
public:
    int year;
    std::string name;
    std::string surname;
    Student(const int& _year, const std::string& _name, const std::string& _surname) {
        this->year = _year;
        this->name = _name;
        this->surname = _surname;
    }
    Student(const Student& s) {
        this->year = s.year;
        this->name = s.name;
        this->surname = s.surname;
    }
    Student() {
        this->year = 0;
        this->name = "";
        this->surname = "";
    }
    Student(const std::string& line) {
        int count = 0;
        for (auto i : line) {
            if (i == ' ') count++;
        }
        if (count != 2) {
            exception_wrongInputLine e;
            throw e;
        }
        std::string buffer = line;
        auto len = buffer.find(' ');
        surname = line.substr(0, len);
        buffer = buffer.substr(len + 1);
        len = buffer.find(" ");
        name = buffer.substr(0, len);
        year = std::stoi(buffer.substr(len + 1));
    }
    Student& operator=(const Student& s) {
        this->year = s.year;
        this->name = s.name;
        this->surname = s.surname;
        return *this;
    }
    bool operator==(const Student& s) const {
        if (this->year == s.year && this->name == s.name && this->surname == s.surname)
            return true;
        return false;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_openFile_clicked();

private:
    Ui::MainWindow *ui;
    ArraySequence<Student> *data;

    enum Columns {LAST_NAME, FIRST_NAME, YEAR};
};

#endif // MAINWINDOW_H
