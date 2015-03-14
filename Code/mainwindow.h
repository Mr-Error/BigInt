#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_plus_clicked();

    QString I2S(int);

    void on_Continue_clicked();

    void on_mins_clicked();

    bool Compare(QString, QString);

    void on_x_clicked();

    void on_Qiut_triggered();

    void on_Power_clicked();

    QString mult(QString, QString);

    QString plus(QString, QString);

    void on_actionAbout_triggered();

    void on_pushButton_clicked();

    bool Check_String(QString str);

    QString mins(QString str1, QString str2);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
