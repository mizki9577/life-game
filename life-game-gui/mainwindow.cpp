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
    game.set(0, 1, true);
    game.set(1, 0, true);
    game.set(1, 1, true);
    game.set(1, 2, true);
    game.set(2, 0, true);
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
    game.clear();
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

    auto&& lwidth = -game.left();
    auto&& rwidth = game.right() - 1;
    auto&& theight = -game.top();
    auto&& bheight = game.bottom() - 1;

    QPixmap pixmap1(rwidth * cell_size, bheight * cell_size);
    QPixmap pixmap2(lwidth * cell_size, bheight * cell_size);
    QPixmap pixmap3(lwidth * cell_size, theight * cell_size);
    QPixmap pixmap4(rwidth * cell_size, theight * cell_size);

    painter.begin(&pixmap1);
    for (int y = 0; y < game.bottom() - 1; ++y) {
        for (int x = 0; x < game.right() - 1; ++x) {
            if (game.get(x, y)) {
                painter.fillRect(x * cell_size, y * cell_size, cell_size, cell_size, Qt::GlobalColor::black);
            } else {
                painter.fillRect(x * cell_size, y * cell_size, cell_size, cell_size, Qt::GlobalColor::white);
            }
        }
    }
    painter.end();

    painter.begin(&pixmap2);
    for (int y = 0; y < game.bottom() - 1; ++y) {
        for (int x = game.left(); x < 0; ++x) {
            if (game.get(x, y)) {
                painter.fillRect((x - game.left()) * cell_size, y * cell_size, cell_size, cell_size, Qt::GlobalColor::black);
            } else {
                painter.fillRect((x - game.left()) * cell_size, y * cell_size, cell_size, cell_size, Qt::GlobalColor::white);
            }
        }
    }
    painter.end();

    painter.begin(&pixmap3);
    for (int y = game.top(); y < 0; ++y) {
        for (int x = game.left(); x < 0; ++x) {
            if (game.get(x, y)) {
                painter.fillRect((x - game.left()) * cell_size, (y - game.top()) * cell_size, cell_size, cell_size, Qt::GlobalColor::black);
            } else {
                painter.fillRect((x - game.left()) * cell_size, (y - game.top()) * cell_size, cell_size, cell_size, Qt::GlobalColor::white);
            }
        }
    }
    painter.end();

    painter.begin(&pixmap4);
    for (int y = game.top(); y < 0; ++y) {
        for (int x = 0; x < game.right() - 1; ++x) {
            if (game.get(x, y)) {
                painter.fillRect(x * cell_size, (y - game.top()) * cell_size, cell_size, cell_size, Qt::GlobalColor::black);
            } else {
                painter.fillRect(x * cell_size, (y - game.top()) * cell_size, cell_size, cell_size, Qt::GlobalColor::white);
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
