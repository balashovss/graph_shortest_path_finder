#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPen>
#include <QPainter>
#include "matrix_funcs.h"
#include "maze_gen_funcs.h"
#include "path_planning_algs.h"
#include <QMainWindow>
#include <iostream>
class QPushButton;
class MazeWidget;
class QTextEdit;
class QPixmap;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QPushButton *cave_generating_button;
    QPushButton *maze_generating_button;
    QPushButton *path_showing_button;
    QPushButton *entering_button;
    MazeWidget *maze_widget;
    QTextEdit *width_edit;
    QTextEdit *height_edit;
signals:
public slots:
    void GenerateCaveButtonHandler();
    void GenerateMazeButtonHandler();
    void ShowPathButtonHandler();
    // void EnterButtonHandler();
};
class MazeWidget : public QWidget
{
    Q_OBJECT
    public:
        MazeWidget(QWidget *parent);
        ~MazeWidget();
        void** map;
        TYPES type_of_map;
        int height;
        int width;
//  public slots:
//   void slot(void** map, int type_of_map, int height, int width) {
//     this->height = height;
//     this->width = width;
//     this->map = map;
//     this->type_of_map = type_of_map;
//   }
  protected:
    void paintEvent(QPaintEvent *event) override{
        Q_UNUSED(event);
        if (this -> map != NULL) {
        int cell_width = 0;
        int cell_height = 0;
        try {
            cell_height = 800/(this->height);
        }
        catch (...) {
            return;
        }
        try {
            cell_width = 800/(this->width);
        }
        catch(...) {
            return;
        }
        QPen pen;
        QPainter painter(this);
        pen.setWidth(2);//отрисовка сетки
        pen.setColor(QColorConstants::Svg::red);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        if (this->type_of_map == CELL_TYPE) {
        for (int j = 0; j < width; j++) {
            painter.drawLine(j*cell_width, 0, j*cell_width, 800);
        }
        for (int i = 0; i < height; i++) {
            painter.drawLine(0, i*cell_height, 800, i*cell_height);
        }//конец отрисовки сетки
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if ((((cell**)(this->map))[i][j] == WALL)) {
                        pen.setColor(QColorConstants::Svg::white);
                        pen.setWidth(2);
                        painter.setPen(pen);
                        painter.drawLine(j*cell_width, i*cell_height, (j+1)*cell_width, (i+1)*cell_height);
                        painter.drawLine((j+1)*cell_width, i*cell_height, j*cell_width, (i+1)*cell_height);
                    }
                    else if (((cell**)(this->map))[i][j] == PATH) {
                        pen.setColor(QColorConstants::Svg::yellow);
                        pen.setWidth(2);
                        painter.setPen(pen);
                        painter.drawLine(j*cell_width, i*cell_height, (j+1)*cell_width, (i+1)*cell_height);
                        painter.drawLine((j+1)*cell_width, i*cell_height, j*cell_width, (i+1)*cell_height);
                    }
                }
            }
        }
        else if (this -> type_of_map == MAZE_CELL_TYPE) {
            pen.setColor(QColorConstants::Svg::white);
            pen.setWidth(2);
            painter.setPen(pen);
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    pen.setColor(QColorConstants::Svg::white);
                    pen.setWidth(2);
                    painter.setPen(pen);
                    if ((((maze_cell**)(this->map))[i][j].right == WALL)) painter.drawLine((j+1)*cell_width, i*cell_height, (j+1)*cell_width, (i+1)*cell_height);
                    if ((((maze_cell**)(this->map))[i][j].bottom == WALL)) painter.drawLine(j*cell_width, (i+1)*cell_height, (j+1)*cell_width, (i+1)*cell_height);
                    if ((((maze_cell**)(this->map))[i][j].isPartOfPath == PATH)) {
                        pen.setColor(QColorConstants::Svg::yellow);
                        pen.setWidth(2);
                        painter.setPen(pen);
                        painter.drawLine(j*cell_width, i*cell_height, (j+1)*cell_width, (i+1)*cell_height);
                        painter.drawLine((j+1)*cell_width, i*cell_height, j*cell_width, (i+1)*cell_height);
                    }
                }
            }
        }
        }
        else {
            QPen pen;
            QPainter painter(this);
            pen.setWidth(800);
            pen.setColor(QColorConstants::Svg::black);
            pen.setStyle(Qt::SolidLine);
            painter.setPen(pen);
            painter.drawLine(400, 0, 400, 800);
        }
        // for (int i = 0; i < height; i++) {
        //     for (int j = 0; j < width; j++) {
        //         if ((this->type_of_map == CAVE_GEN) && (((cell**)(this->map))[i][j] == WALL)) painter.drawLine(j*cell_width, i*cell_height, (j+1)*cell_width, i*cell_height);
        //     }
        // }
    }
};
#endif // MAINWINDOW_H
