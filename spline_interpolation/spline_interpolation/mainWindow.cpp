#include "mainWindow.h"
#include <algorithm>

#include <QLogValueAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>

#include "Spline.h"

using namespace QtCharts;

mainWindow::mainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::mainWindowClass)
{
    ui->setupUi(this);

    size_t countPoint = 5;

    std::vector<double> x(countPoint), y(countPoint);

    for (size_t i = 0; i < countPoint; i++) {
        x[i] = i;
    }

    y[0] = 0;
    y[1] = 1;
    y[2] = 2;
    y[3] = 1;
    y[4] = 0;

    Spline interplotation(x, y);

    QChartView* chartView = new QChartView(this);
    ui->verticalLayout->addWidget(chartView);

    QLineSeries* series = new QLineSeries();
    double Xmax = x[countPoint - 1] + 1, Xmin = x[0] - 1,
        Ymax = *std::max_element(y.data(), y.data() + countPoint) + 1, Ymin = *std::min_element(y.data(), y.data() + countPoint) - 1;

    for (double i = Xmin; i < x[0]; i += 0.01)
    {
        series->append(i, interplotation.getSplineValue(0, i));
    }

    for (size_t k = 1; k < interplotation.getCountPoint(); k++) {
        for (double i = x[k - 1]; i < x[k]; i += 0.01)
        {
            series->append(i, interplotation.getSplineValue(k, i));
        }
    }

    for (double i = x[countPoint - 1]; i < Xmax; i += 0.01)
    {
        series->append(i, interplotation.getSplineValue(countPoint - 1, i));
    }

    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("Graphic");
    chart->addSeries(series);

    QValueAxis* axisX = new QValueAxis();
    axisX->setTitleText("X");
    axisX->setLabelFormat("%.2lf");
    axisX->setMin(Xmin);
    axisX->setMax(Xmax);
    axisX->setTickCount(countPoint);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Y");
    axisY->setLabelFormat("%.2lf");
    axisY->setMin(Ymin);
    axisY->setMax(Ymax);
    axisY->setTickCount(countPoint);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView->setChart(chart);
}

mainWindow::~mainWindow()
{
    delete ui;
}