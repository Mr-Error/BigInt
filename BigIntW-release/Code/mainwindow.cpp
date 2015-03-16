/*
    Copyright 2015 Error

    This file is part of BigInt.
    BigInt is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BigInt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// A + B
void MainWindow::on_plus_clicked()
{
    QString str1 = ui->Num1->toPlainText();
    QString str2 = ui->Num2->toPlainText();

    QString res = "\0";

    if (Check_String(str1) && Check_String(str2))
    {
        if ((*str1.begin() == '-') && (*str2.begin() == '-'))
        {
            str1.remove(0,1);
            str2.remove(0,1);
            res = "-" + plus(str1, str2);
        }
        else if (*str1.begin() == '-')
        {
            str1.remove(0,1);
            res = mins(str2, str1);
        }
        else if (*str2.begin() == '-')
        {
            str2.remove(0,1);
            res = mins(str1, str2);
        }
        else
        {
            res = plus(str1, str2);
        }
    }
    else
    {
        ui->Result->setText("输入含有非法字符");
        return;
    }


    ui->Result->setText(res);

}

// A - B
void MainWindow::on_mins_clicked()
{
    QString str1 = ui->Num1->toPlainText();
    QString str2 = ui->Num2->toPlainText();

    QString res = "\0";

    if (Check_String(str1) && Check_String(str2))
    {
        if ((*str1.begin() == '-') && (*str2.begin() == '-'))
        {
            str1.remove(0,1);
            str2.remove(0,1);
            res = mins(str2, str1);
        }
        else if (*str1.begin() == '-')
        {
            str1.remove(0,1);
            res = '-' + plus(str2, str1);
        }
        else if (*str2.begin() == '-')
        {
            str2.remove(0,1);
            res = plus(str1, str2);
        }
        else
        {
            res = mins(str1, str2);
        }
    }
    else
    {
        ui->Result->setText("输入含有非法字符");
        return;
    }

    ui->Result->setText(res);
}

// A * B
void MainWindow::on_x_clicked()
{
    QString str1 = ui->Num1->toPlainText();
    QString str2 = ui->Num2->toPlainText();

    QString res = "\0";

    if (Check_String(str1) && Check_String(str2))
    {
        res = mult(str1, str2);
    }
    else
    {
        ui->Result->setText("输入含有非法字符");
        return;
    }

    ui->Result->setText(res);
}

// A ^ B
void MainWindow::on_Power_clicked()
{

    QString num1 = ui->Num1->toPlainText();
    QString num2 = ui->Num2->toPlainText();

    QString result = "1";


    for (QString i = "1"; Compare(num2, i); i = plus(i, "1"))
    {
        result = mult(result,num1);
    }

    ui->Result->setText(result);
}

void MainWindow::on_Continue_clicked()
{
    if (ui->Result->toPlainText() != "\0")
    {
        ui->Num1->setText(ui->Result->toPlainText());
        ui->Num2->setText("\0");
        ui->Result->setText("\0");
    }
    else
    {
        return;
    }
}

// Help
void MainWindow::on_pushButton_clicked()
{
    QFile inputFile("Help.txt");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->Result->setPlainText(line);
    QTextCursor cursor = ui->Result->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}

void MainWindow::on_actionAbout_triggered()
{
    QFile inputFile("About.txt");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->Result->setPlainText(line);
    QTextCursor cursor = ui->Result->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}

void MainWindow::on_Qiut_triggered()
{
    QApplication::quit();
}

QString MainWindow::I2S(int x)
{
    switch (x)
    {
    case 1 : return "1";
    case 2 : return "2";
    case 3 : return "3";
    case 4 : return "4";
    case 5 : return "5";
    case 6 : return "6";
    case 7 : return "7";
    case 8 : return "8";
    case 9 : return "9";
    case 0 : return "0";
    default: return "0";
    }
}

bool MainWindow::Compare(QString a, QString b)  // true : a is bigger , false : b is bigger
{
    int lena = a.length();
    int lenb = b.length();

    if (lena > lenb)
    {
        return true;
    }
    else if (lena < lenb)
    {
        return false;
    }

    QString::iterator ita = a.begin();
    QString::iterator itb = b.begin();

    for (;ita != a.end(); ++ita, ++itb)
    {
        if (ita->digitValue() > itb->digitValue())
        {
            return true;
        }
        else if (ita->digitValue() < itb->digitValue())
        {
            return false;
        }
        else
        {
            continue;
        }
    }

    return true;
}

QString MainWindow::mult(QString str1, QString str2)
{

    bool symbol = true;


    if ((*str1.begin() == '-') && (*str2.begin() == '-'))
    {
        str1.remove(0,1);
        str2.remove(0,1);
    }
    if (*str1.begin() == '-')
    {
        str1.remove(0,1);
        symbol = false;
    }
    else if (*str2.begin() == '-')
    {
        str2.remove(0,1);
        symbol = false;
    }

    QString::iterator it1 = str1.end() - 1;
    QString::iterator it2 = str2.end() - 1;

    int jinwei = 0;

    QString mid = "\0";

    QString res = "\0";

    int n = 0;

    while (it2 >= str2.begin())
    {
        int x = it1->digitValue() * it2->digitValue() + jinwei;

        jinwei = x / 10;

        x = x % 10;

        mid = I2S(x) + mid;

        if (it1 == str1.begin())
        {
            if (jinwei != 0)
            {
                mid = I2S(jinwei) + mid;
                jinwei = 0;
            }

            --it2;
            it1 = str1.end();

            for (int m = 0; m != n; ++m)
            {
                mid = mid + "0";
            }

            res = plus(res, mid);

            mid = "\0";
            ++n;
        }

        --it1;
    }

    if (!symbol)
    {
        res = '-' + res;
    }

    return res;
}

QString MainWindow::plus(QString str1, QString str2)
{
    QString zero = "0";

    int len1 = str1.length();
    int len2 = str2.length();

    if (len1 < len2)
    {
        for (int i = 0; i != len2 - len1; ++i)
        {
            str1 = zero + str1;
        }
    }
    else
    {
        for (int i = 0; i != len1 - len2; ++i)
        {
            str2 = zero + str2;
        }
    }

    QString::iterator it2 = str2.end() - 1;
    QString::iterator it1 = str1.end() - 1;
    QString res = "\0";

    bool sign = false;

    for (;it1 >= str1.begin(); --it1, --it2)
    {
        int x = it1->digitValue() + it2->digitValue();

        if (sign)
        {
            ++x;
            sign = false;
        }

        if (x >= 10)
        {
            x = x % 10;
            sign = true;
        }

        res = I2S(x) + res;
    }

    if (sign)
    {
        res = "1" + res;
    }

    return res;
}

QString MainWindow::mins(QString str1, QString str2)
{
    QString zero = "0";

    if (str1 == str2)
    {
        return "0";
    }

    bool symbol = true;

    if (!Compare(str1,str2))
    {
        symbol = false;
        QString temp = str1;
        str1 = str2;
        str2 = temp;
    }

    int len1 = str1.length();
    int len2 = str2.length();

    if (len1 < len2)
    {
        for (int i = 0; i != len2 - len1; ++i)
        {
            str1 = zero + str1;
        }
    }
    else
    {
        for (int i = 0; i != len1 - len2; ++i)
        {
            str2 = zero + str2;
        }
    }

    QString::iterator it1 = str1.end() - 1;
    QString::iterator it2 = str2.end() - 1;
    QString res = "\0";

    bool sign = false;

    while (it1 >= str1.begin())
    {
        int x = 0;

        if (sign)
        {
            x = it1->digitValue() - 1 - it2->digitValue();
            sign = false;
        }
        else
        {
            x = it1->digitValue() - it2->digitValue();
        }

        if (x < 0)
        {
            x = x + 10;
            sign = true;
        }

        res = I2S(x) + res;

        --it1;
        --it2;
    }

    while (*res.begin() == '0')
    {
        res.remove(0,1);
    }

    if (!symbol)
    {
        res = '-' + res;
    }

    return res;
}

bool MainWindow::Check_String(QString str)
{

    for (auto r : str)
    {
        if (r != '-' && (!r.isNumber()))
            return false;
    }

    return true;
}
