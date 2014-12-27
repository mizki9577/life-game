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
    drawMatrixArea();
}

void MainWindow::updateMatrixArea()
{
    game.next();
    drawMatrixArea();
}

void MainWindow::drawMatrixArea()
{
    auto&& cell_size = ui->cellSizeSpinBox->value();
    QPainter painter;

    auto&& lwidth = -game.matrix.left();
    auto&& rwidth = game.matrix.right() - 1;
    auto&& theight = -game.matrix.top();
    auto&& bheight = game.matrix.bottom() - 1;

    QPixmap pixmap1(rwidth * cell_size, bheight * cell_size);
    QPixmap pixmap2(lwidth * cell_size, bheight * cell_size);
    QPixmap pixmap3(lwidth * cell_size, theight * cell_size);
    QPixmap pixmap4(rwidth * cell_size, theight * cell_size);

    painter.begin(&pixmap1);
    for (int y = 0; y < game.matrix.bottom() - 1; ++y) {
        for (int x = 0; x < game.matrix.right() - 1; ++x) {
            if (game.matrix.get(x, y)) {
                painter.fillRect(x * cell_size, y * cell_size, cell_size, cell_size, Qt::GlobalColor::black);
            } else {
                painter.fillRect(x * cell_size, y * cell_size, cell_size, cell_size, Qt::GlobalColor::white);
            }
        }
    }
    painter.end();

    painter.begin(&pixmap2);
    for (int y = 0; y < game.matrix.bottom() - 1; ++y) {
        for (int x = game.matrix.left(); x < 0; ++x) {
            if (game.matrix.get(x, y)) {
                painter.fillRect((x - game.matrix.left()) * cell_size, y * cell_size, cell_size, cell_size, Qt::GlobalColor::black);
            } else {
                painter.fillRect((x - game.matrix.left()) * cell_size, y * cell_size, cell_size, cell_size, Qt::GlobalColor::white);
            }
        }
    }
    painter.end();

    painter.begin(&pixmap3);
    for (int y = game.matrix.top(); y < 0; ++y) {
        for (int x = game.matrix.left(); x < 0; ++x) {
            if (game.matrix.get(x, y)) {
                painter.fillRect((x - game.matrix.left()) * cell_size, (y - game.matrix.top()) * cell_size, cell_size, cell_size, Qt::GlobalColor::black);
            } else {
                painter.fillRect((x - game.matrix.left()) * cell_size, (y - game.matrix.top()) * cell_size, cell_size, cell_size, Qt::GlobalColor::white);
            }
        }
    }
    painter.end();

    painter.begin(&pixmap4);
    for (int y = game.matrix.top(); y < 0; ++y) {
        for (int x = 0; x < game.matrix.right() - 1; ++x) {
            if (game.matrix.get(x, y)) {
                painter.fillRect(x * cell_size, (y - game.matrix.top()) * cell_size, cell_size, cell_size, Qt::GlobalColor::black);
            } else {
                painter.fillRect(x * cell_size, (y - game.matrix.top()) * cell_size, cell_size, cell_size, Qt::GlobalColor::white);
            }
        }
    }
    painter.end();

    ui->matrixArea1->setPixmap(std::move(pixmap1));
    ui->matrixArea2->setPixmap(std::move(pixmap2));
    ui->matrixArea3->setPixmap(std::move(pixmap3));
    ui->matrixArea4->setPixmap(std::move(pixmap4));
}

// vim: set ts=4 sw=4 et:
