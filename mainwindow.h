#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void set_image(QString str);
    QString format_image(int format);
    QString yes_no(bool flg);
private:
    Ui::MainWindow *ui;
private slots:
    void slot();
};
#endif // MAINWINDOW_H
