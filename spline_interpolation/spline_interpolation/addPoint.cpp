#pragma once

#include "addPoint.h"
#include "ui_addPoint.h"

addPoint::addPoint(QWidget* parent) : QDialog(parent), ui(new Ui::addPoint) {
    ui->setupUi(this);
}

addPoint::~addPoint() {
    delete ui;
}

QPointF addPoint::pointF() {
    QPointF result;
    result.setX(ui->doubleSpinBoxX->value());
    result.setY(ui->doubleSpinBoxY->value());
    return result;
}