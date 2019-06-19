#include "qwdialogpen.h"
#include "ui_qwdialogpen.h"

void QWDialogPen::setPen(QPen pen)
{
    //设置QPen,并刷新显示界面
    m_pen= pen;
    this->ui->spinWidth->setValue(pen.width());//线宽
    int i = static_cast<int>(pen.style());//枚举类型转换为整型
    this->ui->comboPenStyle->setCurrentIndex(i);
    QColor color = pen.color();
    this->ui->btnColor->setAutoFillBackground(true);//设置颜色按钮的背景色
    QString str = QString::asprintf("background-color: rgb(%d, %d, %d);", color.red(), color.green(), color.blue());
    this->ui->btnColor->setStyleSheet(str);
}

QPen QWDialogPen::getPen()
{
    //获得设置的属性
    m_pen.setStyle(Qt::PenStyle(this->ui->comboPenStyle->currentIndex()));//线型
    m_pen.setWidth(this->ui->spinWidth->value());//线宽
    QColor color = this->ui->btnColor->palette().color(QPalette::Button);
    m_pen.setColor(color);//颜色
    return m_pen;
}

QPen QWDialogPen::getPen(QPen iniPen, bool &ok)
{
    //静态函数，获取QPen
    QWDialogPen * Dlg = new QWDialogPen;//创建一个对话乱搞；
    Dlg->setPen(iniPen);//设置初始化QPen
    QPen pen;
    int ret = Dlg->exec();//弹出对话框
    if(ret == QDialog::Accepted){
        pen = Dlg->getPen();//获取
        ok = true;
    }else{
        pen = iniPen;
        ok = false;
    }
    delete Dlg;//删除对话框对象
    return pen;//返回设置的QPen对象
}




QWDialogPen::QWDialogPen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogPen)
{
    ui->setupUi(this);
}

QWDialogPen::~QWDialogPen()
{
    delete ui;
}
