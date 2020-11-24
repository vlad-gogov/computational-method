#include "mainWindow.h"
#include <algorithm>
#include <sstream>
#include <string>
#define STEP_SLPINE 100
#define ADD_MAX 10

using namespace QtCharts;

mainWindow::mainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::mainWindowClass) {
    ui->setupUi(this);

    chartView = new QChartView(this);
    chart = new QChart();
    ui->verticalLayout->addWidget(chartView);
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    series = new QLineSeries();
    seriesLineX = new QLineSeries();
    seriesLineY = new QLineSeries();
    pointSeries = new QScatterSeries();
    pen = new QPen();
    pen->setColor(QColorConstants::Black);

    chart->setTitle("Spline Interpolation");

    connect(ui->addPoints, SIGNAL(clicked()), this, SLOT(addPointDialog()));
}

mainWindow::~mainWindow() {
    delete ui;
    delete series;
    delete seriesLineX;
    delete seriesLineY;
    delete pointSeries;
    delete chart;
}

void mainWindow::setGraphics() {
    series->clear();
    seriesLineX->clear();
    seriesLineY->clear();
    pointSeries->clear();

    chart->legend()->hide();

    seriesLineX->setPen(*pen);
    seriesLineY->setPen(*pen);
    pointSeries->setColor(QColorConstants::Red);
    pointSeries->setMarkerSize(10);
    double Xmax = interplotation.x[interplotation.countPoint - 1] + ADD_MAX, Xmin = interplotation.x[0] - ADD_MAX,
        Ymax = *std::max_element(interplotation.y.data(), interplotation.y.data() + interplotation.countPoint) + ADD_MAX, Ymin = *std::min_element(interplotation.y.data(), interplotation.y.data() + interplotation.countPoint) - ADD_MAX;


    for (double i = Xmin; i < interplotation.x[0]; i += 1. / STEP_SLPINE)
    {
        series->append(i, interplotation.getSplineValue(1, i));
    }

    pointSeries->append(interplotation.x[0], interplotation.y[0]);

    for (size_t k = 1; k < interplotation.getCountPoint(); k++) {
        pointSeries->append(interplotation.x[k], interplotation.y[k]);
        for (double i = interplotation.x[k - 1]; i < interplotation.x[k]; i += 1. / STEP_SLPINE)
        {
            series->append(i, interplotation.getSplineValue(k, i));
        }
    }

    for (double i = interplotation.x[interplotation.countPoint - 1]; i < Xmax; i += 1. / STEP_SLPINE)
    {
        series->append(i, interplotation.getSplineValue(interplotation.countPoint - 1, i));
    }

    for (double i = Xmin; i < Xmax; i += 1. / STEP_SLPINE) {
        seriesLineX->append(i, 0);
    }

    for (double i = Ymin; i < Ymax; i += 1. / STEP_SLPINE) {
        seriesLineY->append(0, i);
    }

    axisX->setTitleText("X");
    axisX->setLabelFormat("%.2lf");
    axisX->setMin(Xmin);
    axisX->setMax(Xmax);
    axisX->setTickCount(interplotation.countPoint + ADD_MAX);
    chart->addAxis(axisX, Qt::AlignBottom);

    axisY->setTitleText("Y");
    axisY->setLabelFormat("%.2lf");
    axisY->setMin(Ymin);
    axisY->setMax(Ymax);
    axisY->setTickCount(interplotation.countPoint + ADD_MAX);
    chart->addAxis(axisY, Qt::AlignLeft);

    chart->addSeries(series);
    chart->addSeries(pointSeries);
    chart->addSeries(seriesLineX);
    chart->addSeries(seriesLineY);

    series->attachAxis(axisX);
    pointSeries->attachAxis(axisX);
    seriesLineX->attachAxis(axisX);
    seriesLineY->attachAxis(axisX);

    series->attachAxis(axisY);
    pointSeries->attachAxis(axisY);
    seriesLineX->attachAxis(axisY);
    seriesLineY->attachAxis(axisY);

    chartView->setChart(chart);
}

void mainWindow::addPointDialog() {
    bool ok;
    size_t countPoint = QInputDialog::getInt(this, tr("Set Points"),
        tr("Count points:"), 0, 4, 16, 1, &ok);
    interplotation = Spline(countPoint - 1, countPoint);
    size_t i = 0;
    while(i != countPoint) {
        addPoint dialog;
        std::ostringstream ostr;
        ostr << (i + 1);
        QString title = QString::fromStdString(ostr.str());
        dialog.setWindowTitle("Add Point #" + title);
        dialog.exec();
        if (dialog.result() == QDialog::Accepted) {
            QPointF temp = dialog.pointF();
            try {
                interplotation.addPoint(temp);
                i++;
            }
            catch (const char* message) {
                QMessageBox::warning(this, "Error", message);
            }
        }
        else if (dialog.result() == QDialog::Rejected) {
            return;
        }
    }
    try {
        interplotation.solve();
        setGraphics();
        ui->addPoints->setVisible(false);
    }
    catch (const char* message) {
        QMessageBox::warning(this, "Error", message);
    }
}