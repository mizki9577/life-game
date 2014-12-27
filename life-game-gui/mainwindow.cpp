#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(ui->intervalSpinBox->value());
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMatrixArea()));
    game.matrix.set(0, 1, true);
    game.matrix.set(1, 0, true);
    game.matrix.set(1, 1, true);
    game.matrix.set(1, 2, true);
    game.matrix.set(2, 0, true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::showEvent(QShowEvent *)
{
    drawMatrixArea();
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

void MainWindow::on_cellSizeSpinBox_valueChanged(int)
{
    updateMatrixArea();
}

void MainWindow::updateMatrixArea()
{
    game.next();
    drawMatrixArea();
}

void MainWindow::drawMatrixArea()
{
    auto&& cell_size = ui->cellSizeSpinBox->value();
    auto width = cell_size * (game.matrix.width() + 2);
    auto height = cell_size * (game.matrix.height() + 2);
    QPixmap pixmap(width, height);
    QPainter painter(&pixmap);

    for (int y = game.matrix.top(); y < game.matrix.bottom(); ++y) {
        for (int x = game.matrix.left(); x < game.matrix.right(); ++x) {
            if (game.matrix.get(x, y)) {
                painter.fillRect((x - game.matrix.left()) * cell_size, (y - game.matrix.top()) * cell_size, cell_size, cell_size, Qt::GlobalColor::black);
            } else {
                painter.fillRect((x - game.matrix.left()) * cell_size, (y - game.matrix.top()) * cell_size, cell_size, cell_size, Qt::GlobalColor::white);
            }
        }
    }
    ui->matrixArea->setPixmap(std::move(pixmap));
}

// vim: set ts=4 sw=4 et:
