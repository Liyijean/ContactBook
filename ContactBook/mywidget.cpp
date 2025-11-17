#include "mywidget.h"
#include "ui_mywidget.h"
#include <QTableWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

QString mFilename = "C:/test/myfile.txt";

// 寫入檔案
void Write(QString Filename, QString str)
{
    QFile mFile(Filename);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "could not open file for write";
        return;
    }
    QTextStream out(&mFile);
    out << str;
    mFile.flush();
    mFile.close();
}

// 讀取檔案
QString Read(QString Filename)
{
    QFile mFile(Filename);
    if(!mFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "could not open file for read";
        return "";
    }
    QTextStream in(&mFile);
    QString allText = in.readAll();
    mFile.close();
    return allText;
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    QStringList ColTotle;
    ui->tableWidget->setColumnCount(4);
    ColTotle << QStringLiteral("學號")
             << QStringLiteral("班級")
             << QStringLiteral("姓名")
             << QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

MyWidget::~MyWidget()
{
    delete ui;
}

// 新增
void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *inputRow1, *inputRow2, *inputRow3, *inputRow4;
    inputRow1 = new QTableWidgetItem(ui->lineEdit_5->text());
    inputRow2 = new QTableWidgetItem(ui->lineEdit_6->text());
    inputRow3 = new QTableWidgetItem(ui->lineEdit_7->text());
    inputRow4 = new QTableWidgetItem(ui->lineEdit_8->text());

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, inputRow4);
}

// 匯出
void MyWidget::on_pushButton_2_clicked()
{
    QString saveFile = "";

    for(int i=0; i<ui->tableWidget->rowCount(); i++){
        for(int j=0; j<ui->tableWidget->columnCount(); j++){
            saveFile += ui->tableWidget->item(i,j)->text() + ",";
        }
        saveFile += "\n";
    }
    Write(mFilename, saveFile);
}

// 匯入
void MyWidget::on_pushButton_3_clicked()
{
    QString filename = QFileDialog::getOpenFileName();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    ui->tableWidget->setRowCount(0); // 清空表格

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",", Qt::SkipEmptyParts);
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        for (int i = 0; i < fields.size() && i < ui->tableWidget->columnCount(); ++i) {
            ui->tableWidget->setItem(row, i, new QTableWidgetItem(fields[i]));
        }
    }

    file.close();
}

// 結束
void MyWidget::on_pushButton_4_clicked()
{
    close();
}
