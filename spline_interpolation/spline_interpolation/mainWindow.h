#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"

#include <QLogValueAxis>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>
#include <QInputDialog>
#include <QPointF>
#include <QDialog>
#include <QMessageBox>

#include "Spline.h"
#include "addPoint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

using namespace QtCharts;

class mainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    Spline interplotation;

    QChartView* chartView;
    QLineSeries* series;
    QLineSeries* seriesLineX;
    QLineSeries* seriesLineY;
    QScatterSeries* pointSeries;
    QChart* chart;
    QValueAxis* axisX;
    QValueAxis* axisY;
    QPen* pen;

public:
    mainWindow(QWidget *parent = Q_NULLPTR);
    ~mainWindow();

    void setGraphics();

private:
    Ui::mainWindowClass *ui;

private slots:
    void addPointDialog();
};
