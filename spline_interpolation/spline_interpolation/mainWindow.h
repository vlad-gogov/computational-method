#pragma once

#include <QtWidgets/QMainWindow>
#include <QtCharts/qchartview.h>
#include "ui_mainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = Q_NULLPTR);
    ~mainWindow();

private:
    Ui::mainWindowClass *ui;
};
