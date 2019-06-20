#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLegendFont_clicked();

    void on_radioSeries0_clicked();

    void on_radioX_clicked();

    void on_btnTickFormat_clicked();

private:
    Ui::MainWindow *ui;

private:
    QLineSeries * curSeries;//当前序列
    QValueAxis * curAxis;//当前坐标轴
    void createChart();//创建图表
    void prepareData();//更新数据
    void updateFromChart();//从图表更新到界面
};

#endif // MAINWINDOW_H
