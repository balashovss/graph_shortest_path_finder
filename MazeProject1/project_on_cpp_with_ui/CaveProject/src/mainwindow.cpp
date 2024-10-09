#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QPainter>
#include <QPen>
#include "matrix_funcs.h"
#include "maze_gen_funcs.h"
#include "path_planning_algs.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("powered by Адский Сатана");
    setFixedSize(1000, 1000);
    maze_widget = new MazeWidget(this);
    cave_generating_button = new QPushButton("Generate Cave", this);
    maze_generating_button = new QPushButton("Generate Maze", this);
    path_showing_button = new QPushButton("Show Path", this);
    width_edit = new QTextEdit(this);
    height_edit = new QTextEdit(this);
    maze_widget->setGeometry(0, 0, 800, 800);
    cave_generating_button->setGeometry(800, 200, 200, 100);
    cave_generating_button->setCheckable(true);
    maze_generating_button->setGeometry(800, 400, 200, 100);
    maze_generating_button->setCheckable(true);
    path_showing_button->setGeometry(800, 600, 200, 100);
    path_showing_button->setCheckable(true);
    width_edit->setGeometry(800, 800, 200, 50);
    width_edit->setPlaceholderText("width");
    height_edit->setGeometry(800, 850, 200, 50);
    height_edit->setPlaceholderText("height");
    connect(cave_generating_button, &QPushButton::clicked, this, &MainWindow::GenerateCaveButtonHandler);
    connect(maze_generating_button, &QPushButton::clicked, this, &MainWindow::GenerateMazeButtonHandler);
    connect(path_showing_button, &QPushButton::clicked, this, &MainWindow::ShowPathButtonHandler);
};
void MainWindow::GenerateCaveButtonHandler() {
    if (maze_widget -> map) free_matrix(&(maze_widget->map), maze_widget->height, maze_widget->type_of_map);
    try {
        maze_widget->width = stoi(width_edit->toPlainText().toStdString());
    }
    catch (...) {
        return;
    }
    try {
        maze_widget->height = stoi(height_edit->toPlainText().toStdString());
    }
    catch (...) {
        return;
    }
    if ((maze_widget->width > 0) && (maze_widget->height > 0)) {
        maze_widget->map = NULL;
        maze_widget->type_of_map = CELL_TYPE;
        maze_widget->map = create_matrix(maze_widget->height, maze_widget -> width, maze_widget -> type_of_map);
        generate_cave(&(maze_widget->map), maze_widget->height, maze_widget->width);
    }
    maze_widget->update();
}
void MainWindow::GenerateMazeButtonHandler() {
    if (maze_widget -> map) free_matrix(&(maze_widget->map), maze_widget->height, maze_widget->type_of_map);
    try {
        maze_widget->width = stoi(width_edit->toPlainText().toStdString());
    }
    catch (...) {
        return;
    }
    try {
        maze_widget->height = stoi(height_edit->toPlainText().toStdString());
    }
    catch (...) {
        return;
    }
    if ((maze_widget->width > 0) && (maze_widget->height > 0)) {
        maze_widget->map = NULL;
        maze_widget->type_of_map = MAZE_CELL_TYPE;
        maze_widget->map = create_matrix(maze_widget->height, maze_widget -> width, maze_widget -> type_of_map);
        generate_maze(&(maze_widget->map), maze_widget->height, maze_widget->width);
    }
    maze_widget->update();
}
void MainWindow::ShowPathButtonHandler() {
    if ((maze_widget -> map) && (maze_widget->width > 0) && (maze_widget->height > 0)){ 
        if (maze_widget->type_of_map == CELL_TYPE) wave_algorithm_for_cave((cell***)(&(maze_widget->map)), maze_widget->width, maze_widget->height);
        else if (maze_widget -> type_of_map == MAZE_CELL_TYPE) wave_algorithm_for_maze((maze_cell***)(&(maze_widget->map)), maze_widget->width, maze_widget->height);
    }
    maze_widget->update();
}
MainWindow::~MainWindow()
{
};
MazeWidget::MazeWidget(QWidget *parent)
    : QWidget(parent)
{
    QPalette palette;
    this -> map = NULL;
    this -> type_of_map = CELL_TYPE;
    this -> height = -1;
    this -> width = -1;
    palette.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(palette);
};
MazeWidget::~MazeWidget()
{
    if (this -> map != NULL) free_matrix(&(this->map), this->height, this->type_of_map);
};