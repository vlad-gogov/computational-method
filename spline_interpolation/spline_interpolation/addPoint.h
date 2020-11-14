#pragma once

#include <QDialog>
#include <QPointF>

QT_BEGIN_NAMESPACE
namespace Ui { class addPoint; }
QT_END_NAMESPACE

class addPoint : public QDialog
{
    Q_OBJECT

private:
    QPointF xy;

public:
    addPoint(QWidget* parent = Q_NULLPTR);
    ~addPoint();

    QPointF pointF();

private:
    Ui::addPoint* ui;
};