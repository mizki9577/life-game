#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include "life_game.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void on_runButton_toggled(bool checked);
        void on_resetButton_clicked();
        void on_intervalSpinBox_valueChanged(int arg1);
        void on_cellSizeSpinBox_valueChanged(int arg1);
        void updateMatrixArea();

    private:
        Ui::MainWindow *ui;
        QTimer *timer;
        life_game game;
};

#endif // MAINWINDOW_HPP
// vim: set ts=4 sw=4 et:
