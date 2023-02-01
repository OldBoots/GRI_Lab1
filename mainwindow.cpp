#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    set_image("C:\\Qt\\Project\\Test-UI\\PERTSEV.bmp");
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(slot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_image(QString path)
{
    ui->label->setPixmap(QPixmap(path).scaled(400,
                                              400,
                                              Qt::KeepAspectRatio,
                                              Qt::SmoothTransformation));
}

void MainWindow::slot()
{
    // Считываем исходное изображение в массив Байт
    QFile file("C:\\Qt\\Project\\Test-UI\\PERTSEV.bmp");
    file.open(QIODevice::ReadOnly);
    QByteArray arr = file.readAll();
    file.close();
    // Создаем файл для итогового изображения
    QFile file1("C:\\Qt\\Project\\Test-UI\\PERTSEV1.bmp");
    file1.open(QIODevice::WriteOnly);
    // Пропуская первые 138 Байт (Заголовки BMP файла),
    // считываем ARGB цвета, находим самы тусклый оттенок
    // и приравниваем к нему остальные
    char min_color;
    for(int i = 138; i < arr.size(); i+=4){
        min_color = arr[i];
        for(int j = 1; j < 3; j++){
            if(arr[i+j] < min_color){
                min_color = arr[i+j];
            }
        }
        arr[i] = arr[i+1] = arr[i+2] = min_color;
    }
    // Записываем во второй файл, получившейся массив
    for(int i = 0; i < arr.size(); i++){
        file1.putChar(arr[i]);
    }
    file1.close();
    set_image("C:\\Qt\\Project\\Test-UI\\PERTSEV1.bmp");
}

