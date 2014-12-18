#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    timer->setInterval(ui->intervalSpinBox->value());
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMatrixArea()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runButton_toggled(bool checked)
{
    if (checked) {
        timer->start();
    } else {
        timer->stop();
    }
}

void MainWindow::on_resetButton_clicked()
{
    if (timer->isActive()) {
        timer->stop();
    }
    game.matrix.clear();
    ui->runButton->setChecked(false);
}

void MainWindow::on_intervalSpinBox_valueChanged(int arg1)
{
    timer->setInterval(arg1);
}

void MainWindow::on_cellSizeSpinBox_valueChanged(int arg1)
{
    // TODO: redraw matrix
}

void MainWindow::updateMatrixArea()
{
    // TODO: draw matrix
}

// vim: set ts=4 sw=4 et:
