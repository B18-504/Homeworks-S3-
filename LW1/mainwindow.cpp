#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->status->setText("Sequences are empty");
    this->setFixedSize(600, 450);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    int length = ui->length->text().toInt();
    ui->length->clear();
    if (!length) {
        QMessageBox::warning(this, "Warning", "Length can't be 0\nChange input");
        return;
    }
    type = ui->comboBox->currentText();
    if (!((seqA1 && seqA2) || (seqL1 && seqL2))) {
        if (type == "Array") {
            seqA1 = new ArraySequence<int>(length, 10, 1000);
            seqA2 = new ArraySequence<int>(seqA1);
        }
        else if (type == "List") {
            seqL1 = new ListSequence<int>(length, 10, 1000);
            seqL2 = new ListSequence<int>(seqL1);
        }
        ui->status->setText("Sequences are created\nLength: " + QString::number(length) + "\nType: " + type);
    }
    else {
        QMessageBox::warning(this, "Warning", "Sequences were already created\nPress CLEAR to delete them");
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (time == .0) {
        QMessageBox::warning(this, "Warning", "Sequences are not sorted");
        return;
    }

    QBarSet *set1 = new QBarSet("Algorithm 1");
    *set1 << time1;
    QBarSet *set2 = new QBarSet("Algorithm 2");
    *set2 << time2;

    QBarSeries *series = new QBarSeries;
    series->append(set1);
    series->append(set2);

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Algorithms comparison");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, time);
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
    if (!((seqA1 && seqA2) || (seqL1 && seqL2))) {
        QMessageBox::warning(this, "Warning", "You have to create Sequences\nTry first block");
        return;
    }
    if (time != .0) {
        QMessageBox::warning(this, "Warning", "Sequences are already sorted");
        return;
    }
    if (seqA1 && seqA2) {
        auto start = std::chrono::steady_clock::now();
        if (ui->sort1->currentText() == "Bubble") {
            Sort<int>::bubbleSort(seqA1, 0, seqA1->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        else if (ui->sort1->currentText() == "Merge") {
            Sort<int>::mergeSort(seqA1, 0, seqA1->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        else if (ui->sort1->currentText() == "Quick") {
            Sort<int>::quickSort(seqA1, 0, seqA1->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        auto end = std::chrono::steady_clock::now();
        time1 = std::stod(std::to_string(std::chrono::duration<double, std::milli>(end - start).count()));
        start = std::chrono::steady_clock::now();
        if (ui->sort2->currentText() == "Bubble") {
            Sort<int>::bubbleSort(seqA2, 0, seqA2->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        else if (ui->sort2->currentText() == "Merge") {
            Sort<int>::mergeSort(seqA2, 0, seqA2->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        else if (ui->sort2->currentText() == "Quick") {
            Sort<int>::quickSort(seqA2, 0, seqA2->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        end = std::chrono::steady_clock::now();
        time2 = std::stod(std::to_string(std::chrono::duration<double, std::milli>(end - start).count()));
        ui->status->setText("Sequences are sorted\nLength: " + QString::number(seqA1->getLength()) + "\nType: " + type
        + "\nAlgorithm 1 time: " + QString::number(time1) + " ms\n" + "Algorithm 2 time: " + QString::number(time2) + " ms");
    }
    else if (seqL1 && seqL2) {
        auto start = std::chrono::steady_clock::now();
        if (ui->sort1->currentText() == "Bubble") {
            Sort<int>::bubbleSort(seqL1, 0, seqL1->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        else if (ui->sort1->currentText() == "Merge") {
            Sort<int>::mergeSort(seqL1, 0, seqL1->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        else if (ui->sort1->currentText() == "Quick") {
            Sort<int>::quickSort(seqL1, 0, seqL1->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        auto end = std::chrono::steady_clock::now();
        time1 = std::stod(std::to_string(std::chrono::duration<double, std::milli>(end - start).count()));
        start = std::chrono::steady_clock::now();
        if (ui->sort2->currentText() == "Bubble") {
            Sort<int>::bubbleSort(seqL2, 0, seqL2->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        else if (ui->sort2->currentText() == "Merge") {
            Sort<int>::mergeSort(seqL2, 0, seqL2->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        else if (ui->sort2->currentText() == "Quick") {
            Sort<int>::quickSort(seqL2, 0, seqL2->getLength() - 1, [](const int& l1, const int& l2)->bool {return l1 > l2;});
        }
        end = std::chrono::steady_clock::now();
        time2 = std::stod(std::to_string(std::chrono::duration<double, std::milli>(end - start).count()));
        ui->status->setText("Sequences are sorted\nLength: " + QString::number(seqL1->getLength()) + "\nType: " + type
        + "\nAlgorithm 1 time: " + QString::number(time1) + " ms\n" + "Algorithm 2 time: " + QString::number(time2) + " ms");
    }
    time = time1 + time2;
}

void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Are you sure?", "Are you sure?");
    if (reply == QMessageBox::Yes) {
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
    else {
        return;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    AboutWindow *window = new AboutWindow;
    window->setModal(true);
    window->exec();
}
