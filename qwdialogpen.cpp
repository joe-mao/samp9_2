#include "qwdialogpen.h"
#include "ui_qwdialogpen.h"

void QWDialogPen::setPen(QPen pen)
{
    //设置QPen,并刷新显示界面
    m_pen= pen;

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

void QWDialogPen::setPen(QPen pen)
{
    //设置QPen,并刷新显示界面
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
