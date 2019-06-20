#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createChart();//创建图表
    prepareData();//生成数据
    updateFromChart();//从图表获得属性值，刷新界面显示
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createChart()
{
    //创建图标的各个部件
    QChart * chart = new QChart();
    chart->setTitle("简单函数曲线");
    this->ui->chartView->setChart(chart);
    this->ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries * series0 = new QLineSeries();
    QLineSeries * series1 = new QLineSeries();
    series0->setName("sin曲线");
    series1->setName("Cos曲线");
    curSeries = series0;//当前序列

    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    series0->setPen(pen);//折线序列的线条设置
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::blue);
    series1->setPen(pen);//另一条折线序列的线条设置
    chart->addSeries(series0);
    chart->addSeries(series1);

    //创建坐标轴
    QValueAxis * axisX = new QValueAxis;
    curAxis = axisX;//当前坐标轴
    axisX->setRange(0, 10);//设置坐标抽范围
    axisX->setLabelFormat("%.1f");//标签格式
    axisX->setTickCount(11);//主分隔个数
    axisX->setMinorTickCount(4);
    axisX->setTitleText("time(secs)");//标题

//    //序列添加数值
//    qreal t = 0, y1, y2, intv = 0.1;
//    int cnt = 1000;
//    for(int i = 0; i < cnt; ++i){
//        y1 = qSin(t);
//        series0->append(t, y1);
//        y2 = qSin(t+20);
//        series1->append(t, y2);
//        t += intv;
//    }

    QValueAxis * axisY = new QValueAxis;
    axisY->setRange(-2, 2);
    axisY->setTitleText("value");
    axisY->setTickCount(5);
    axisY->setLabelFormat("%.2f");//标签格式
    axisY->setMinorTickCount(4);

    chart->setAxisX(axisX, series0);//设置x轴坐标
    chart->setAxisX(axisX, series1);//设置x轴坐标
    chart->setAxisY(axisY, series0);//设置y轴坐标
    chart->setAxisY(axisY, series1);//设置y坐标

}

void MainWindow::prepareData()
{
    //为序列生成数据
    QLineSeries * series0 = (QLineSeries *)ui->chartView->chart()->series().at(0);
    QLineSeries * series1 = (QLineSeries *)ui->chartView->chart()->series().at(1);
    series0->clear();//清除数据
    series1->clear();
    qsrand(QTime::currentTime().second());//随机数初始变化


    qreal t = 0, y1, y2, intv = 0.1;
    qreal rd;
    int cnt = 100;
    for(int i = 0; i < cnt; ++i){
        rd = (qrand() % 10) - 5;//随机数-5 ~ 5
        y1 = qSin(t) + rd / 50;
        series0->append(t, y1);//序列添加数据点
        rd = (qrand() % 10) - 5;//随机数-5 ~ 5
        y2 = qSin(t) + rd / 50;
        series1->append(t, y2);//序列添加数据点
        t += intv;
    }

}

void MainWindow::updateFromChart()
{
    //从图表上获取数据更新界面显示
    QChart * aChart = this->ui->chartView->chart();//获取chart
    this->ui->editTitle->setText(aChart->title());//图表标题
    QMargins mg = aChart->margins();//边距
    this->ui->spinMarginLeft->setValue(mg.left());
    this->ui->spinMarginRight->setValue(mg.right());
    this->ui->spinMarginTop->setValue(mg.top());
    this->ui->spinMarginBottom->setValue(mg.bottom());
}

void MainWindow::on_btnLegendFont_clicked()
{
    //图例的字体设置
    QFont font = this->ui->chartView->chart()->legend()->font();
    bool ok = false;
    font = QFontDialog::getFont(&ok, font);
    if(ok){
        this->ui->chartView->chart()->legend()->setFont(font);
    }
}

void MainWindow::on_radioSeries0_clicked()
{
    //获取当前序列数据
    if(this->ui->radioSeries0->isChecked()){
        curSeries = (QLineSeries *)this->ui->chartView->chart()->series().at(0);
    }else{
        curSeries = (QLineSeries *)this->ui->chartView->chart()->series().at(1);
    }
    //获取序列的属性值，并显示到界面上
    this->ui->editSeriesName->setText(curSeries->name());
    this->ui->chkSeriesVisible->setChecked(curSeries->isVisible());
    this->ui->chkPointVisible->setChecked(curSeries->pointsVisible());
    this->ui->sliderSeriesOpacity->setValue(curSeries->opacity() * 10);
    this->ui->chkPointLabelVisible->setChecked(curSeries->pointLabelsVisible());

}

void MainWindow::on_radioX_clicked()
{
    //获取当前坐标轴
    if(this->ui->radioX->isChecked()){
        curAxis = (QValueAxis *)this->ui->chartView->chart()->axisX();
    }else{
        curAxis = (QValueAxis *)this->ui->chartView->chart()->axisY();
    }

    //获取坐标轴的各种属性，显示到界面上
    this->ui->spinAxisMin->setValue(curAxis->min());
    this->ui->spinAxisMax->setValue(curAxis->max());
    this->ui->editAxisTitle->setText(curAxis->titleText());
    this->ui->chkBoxAxisTitle->setChecked(curAxis->isTitleVisible());
    this->ui->editAxisLabelFormat->setText(curAxis->labelFormat());
    this->ui->chkBoxLabelsVisible->setChecked(curAxis->labelsVisible());
    this->ui->chkGridLineVisible->setChecked(curAxis->isGridLineVisible());
    this->ui->chkAxisLineVisible->setChecked(curAxis->isLineVisible());
    this->ui->spinTickCount->setValue(curAxis->tickCount());
    //this->ui->chkAxisLineVisible->setChecked(curAxis->isLineVisible());
    this->ui->spinMinorTickCount->setValue(curAxis->minorTickCount());
    this->ui->chkMinorTickVisible->setChecked(curAxis->isMinorGridLineVisible());

}

void MainWindow::on_btnTickFormat_clicked()
{
   //设置坐标抽标签格式
    curAxis->setLabelFormat(this->ui->editAxisLabelFormat->text());
}
