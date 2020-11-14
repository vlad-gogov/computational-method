#include "mainWindow.h"
#include <algorithm>
#include <sstream>
#include <string>

using namespace QtCharts;

mainWindow::mainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::mainWindowClass) {
    ui->setupUi(this);

    chartView = new QChartView(this);
    chart = new QChart();
    ui->verticalLayout->addWidget(chartView);
    series = new QLineSeries();
    seriesLineX = new QLineSeries();
    seriesLineY = new QLineSeries();
    pointSeries = new QScatterSeries();
    pen = new QPen();
    pen->setColor(QColorConstants::Black);

    axisX = new QValueAxis();
    axisY = new QValueAxis();

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
    delete axisX;
    delete axisY;
}

void mainWindow::setGraphic() {
    series->clear();
    seriesLineX->clear();
    seriesLineY->clear();
    pointSeries->clear();

    chart->legend()->hide();

    seriesLineX->setPen(*pen);
    seriesLineY->setPen(*pen);
    pointSeries->setColor(QColorConstants::Red);
    double Xmax = interplotation.x[interplotation.countPoint - 1] + 1, Xmin = interplotation.x[0] - 1,
        Ymax = *std::max_element(interplotation.y.data(), interplotation.y.data() + interplotation.countPoint) + 1, Ymin = *std::min_element(interplotation.y.data(), interplotation.y.data() + interplotation.countPoint) - 1;


    pointSeries->append(interplotation.x[0], interplotation.y[0]);

    for (size_t k = 1; k < interplotation.getCountPoint(); k++) {
        pointSeries->append(interplotation.x[k], interplotation.y[k]);
        for (double i = Xmin; i < interplotation.x[k]; i += 0.001)
        {
            series->append(i, interplotation.getSplineValue(k, i));
        }
    }

    for (double i = interplotation.x[interplotation.countPoint - 1]; i < Xmax; i += 0.001)
    {
        series->append(i, interplotation.getSplineValue(interplotation.countPoint - 1, i));
    }

    for (double i = Xmin; i < Xmax; i += 0.001) {
        seriesLineX->append(i, 0);
    }

    for (double i = Ymin; i < Ymax; i += 0.001) {
        seriesLineY->append(0, i);
    }

    axisX->setTitleText("X");
    axisX->setLabelFormat("%.2lf");
    axisX->setMin(Xmin);
    axisX->setMax(Xmax);
    axisX->setTickCount(interplotation.countPoint + 5);
    chart->addAxis(axisX, Qt::AlignBottom);

    axisY->setTitleText("Y");
    axisY->setLabelFormat("%.2lf");
    axisY->setMin(Ymin);
    axisY->setMax(Ymax);
    axisY->setTickCount(interplotation.countPoint + 5);
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
    interplotation.deleteSpline();
    bool ok;
    size_t countPoint = QInputDialog::getInt(this, tr("Set Points"),
        tr("Count points:"), 0, 4, 30, 1, &ok);
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
            interplotation.deleteSpline();
            return;
        }
    }
    try {
        interplotation.solve();
        setGraphic();
    }
    catch (const char* message) {
        QMessageBox::warning(this, "Error", message);
    }
}