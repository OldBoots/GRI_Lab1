#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    set_image("C:\\Qt\\Project\\Test-UI\\PERTSEV.bmp");
    QImage img("C:\\Qt\\Project\\Test-UI\\PERTSEV.bmp");
    QString str;
    str = "Размер изображения: " + QString::number(img.width()) + "x"
            + QString::number(img.height())
            + "\nНаличие Альфа слоя: " + yes_no(img.hasAlphaChannel())
            + "\nГлубина изображения: " + QString::number(img.depth())
            + "\nФормат изображения: " + format_image(img.format());

    ui->label_2->setText(str);
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

QString MainWindow::format_image(int format)
{
    switch(format){
    case 0:
        return "Invalid";
    case 1:
        return "Mono";
    case 2:
        return "MonoLSB";
    case 3:
        return "Indexed8";
    case 4:
        return "RGB32";
    case 5:
        return "ARGB32";
    case 6:
        return "ARGB32_Premultiplied";
    case 7:
        return "RGB16";
    case 8:
        return "ARGB8565_Premultiplied";
    case 9:
        return "RGB666";
    case 10:
        return "ARGB6666_Premultiplied";
    case 11:
        return "RGB555";
    case 12:
        return "ARGB8555_Premultiplied";
    case 13:
        return "RGB888";
    case 14:
        return "RGB444";
    default:
        return "Other";
    }
}

QString MainWindow::yes_no(bool flg)
{
    if(flg){
        return "Да";
    }
    return "Нет";
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

