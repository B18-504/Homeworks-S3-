#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include "histogram.hpp"
#include "histogram.cpp"
#include <regex>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , data(new ArraySequence<Student>)
{
    ui->setupUi(this);
    this->setWindowTitle("LW2");
    this->ui->table->setColumnCount(3);
    QStringList headers;
    headers << "Last Name" << "First Name" << "Year of birth";
    this->ui->table->setHorizontalHeaderLabels(headers);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", "/Users/levmarder/Documents/Coding");

    if (fileName == "")
        QMessageBox::warning(this, "Warning!", "File was not opened");
    else {
        QMessageBox::information(this, "File opened", "Choosen file: " + fileName);
        this->ui->fileName->setText(fileName);
    }

}

int sum(ArraySequence<int>* seq) {
    int b = 0;
    for (auto i : *seq) {
        b += i;
    }
    return b;
}

void MainWindow::on_pushButton_2_clicked() {
    std::string buffer = this->ui->rangesEdit->text().toStdString();
    if (!buffer.size()) {
        QMessageBox::warning(this, "Warning", "This field can't be empty");
        return;
    }

    std::regex reg(" ");
    buffer = std::regex_replace(buffer, reg, "");

    ArraySequence<std::string> *splitted = new ArraySequence<std::string>;
    std::istringstream ss(buffer);
    std::string dummy;
    while (std::getline(ss, dummy, ','))
            splitted->append(dummy);

    if (splitted->getLength() % 2 != 0) {
        QMessageBox::warning(this, "Warning", "You have to provide full fragmetations");
        return;
    }

    ArraySequence<std::pair<int, int>> *ranges = new ArraySequence<std::pair<int, int>>;
    for (int i = 0; i < splitted->getLength(); i += 2) {
        try {
            ranges->append(std::make_pair(std::stoi(splitted->get(i)), std::stoi(splitted->get(i + 1))));
        }
        catch (std::invalid_argument exp) {
            QMessageBox::warning(this, "Warning", "Provided fragmetation can't be used\n See 'about' for more");
            return;
        }
    }

    RBDictionary<std::pair<int, int>, int> histogram = buildHistogram(data, sum, [](const std::pair<int, int>& i, const Student& j)->bool
    {return i.first <= j.year && i.second >= j.year;}, ranges);

    int max = (*histogram.begin()).second;

    QBarSet *set1 = new QBarSet("Histogram");
    for (auto i : histogram) {
        *set1 << i.second;
        if (i.second > max) max = i.second;
    }

    QBarSeries *series = new QBarSeries;
    series->append(set1);

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Algorithms comparison");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, max + 1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *widget = new QWidget;
    widget = chartView;
    widget->resize(600, 500);
    widget->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    int begin = this->ui->rangeStart->text().toInt();
    int end = this->ui->rangeEnd->text().toInt();
    int range = this->ui->fineness->text().toInt();

    if (!begin && !end && !range) {
        QMessageBox::warning(this, "Warning", "Those fields can't be empty");
        return;
    }

    RBDictionary<std::pair<int, int>, int> histogram = buildHistogram(this->data, sum, [](const std::pair<int, int>& i, const Student& j)->bool
    {return i.first <= j.year && i.second > j.year;},
    begin, end, range);

    int max = (*histogram.begin()).second;

    QBarSet *set1 = new QBarSet("Histogram");
    for (auto i : histogram) {
        *set1 << i.second;
        if (i.second > max) max = i.second;
    }

    QBarSeries *series = new QBarSeries;
    series->append(set1);

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Algorithms comparison");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, max + 1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    /*
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(begin, end);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    */

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *widget = new QWidget;
    widget = chartView;
    widget->resize(600, 500);
    widget->setWindowTitle("Histogram");
    widget->show();
}

void MainWindow::on_openFile_clicked()
{
    QString fileName = this->ui->fileName->text();
    if (fileName == "file name...") {
        QMessageBox::warning(this, "Warning", "File was not choosen.\n Choose file first.");
        return;
    }

    QFileInfo file(fileName);
    if (file.suffix() != "txt") {
        QMessageBox::warning(this, "Warning", "Wrong format.");
        return;
    }

    std::ifstream in(fileName.toStdString());
    if ( !in ) {
        QMessageBox::warning(this, "Warning", "Problem with opening the file.");
        return;
    }

    this->data->ArraySequence<Student>::~ArraySequence();

    this->ui->table->setRowCount(0);

    this->ui->fileBrowse->clear();

    std::string buffer;
    getline(in, buffer, '\n');
    while (buffer.size() != 0) {
        Student jk(buffer);
        this->data->append(jk);
        this->ui->fileBrowse->append(QString::fromStdString(buffer));
        this->ui->table->setRowCount(ui->table->rowCount() + 1);
        QTableWidgetItem *lastname = new QTableWidgetItem(QString::fromStdString(jk.surname));
        lastname->setFlags(lastname->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *firstname = new QTableWidgetItem(QString::fromStdString(jk.name));
        firstname->setFlags(firstname->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *year = new QTableWidgetItem(QString::number(jk.year));
        year->setFlags(year->flags() ^ Qt::ItemIsEditable);
        this->ui->table->setItem(this->ui->table->rowCount() - 1, LAST_NAME, lastname);
        this->ui->table->setItem(this->ui->table->rowCount() - 1, FIRST_NAME, firstname);
        this->ui->table->setItem(this->ui->table->rowCount() - 1, YEAR, year);
        getline(in, buffer, '\n');
    }

    this->ui->fileBrowse->reload();

    this->ui->pushButton_2->setEnabled(true);
    this->ui->pushButton_3->setEnabled(true);
}
