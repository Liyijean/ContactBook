#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void on_pushButton_clicked();      // 新增
    void on_pushButton_2_clicked();    // 匯出
    void on_pushButton_3_clicked();    // 匯入
    void on_pushButton_4_clicked();    // 結束

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
