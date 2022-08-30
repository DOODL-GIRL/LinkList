#include "widget.h"
#include "ui_widget.h"
#include "singlelinklist.h"
#include "circlelinklist.h"
#include "doublelinklist.h"
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    status=0;
    slinklist=NULL;
    clinklist=NULL;
    dlinklist=NULL;

    setFixedSize(1200,800);
    setWindowTitle("链表操作演示");


    QImage _image;
    _image.load(":/img/5.jpg");
    setAutoFillBackground(true);   // 这个属性一定要设置
    QPalette pal(palette());
    pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio,
                       Qt::SmoothTransformation)));
    setPalette(pal);

    //未创建时，除链表类型按钮和创建按钮外，其余按键一律无效
    ui->listType->setEnabled(true);
    ui->build_btn->setEnabled(true);
    ui->clear_btn->setEnabled(false);
    ui->operationType->setEnabled(false);
    ui->index->setEnabled(false);
    ui->val->setEnabled(false);
    ui->confirm_btn->setEnabled(false);

    ui->tableWidget->setRowCount(1000);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格内容不可编辑
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);		//设置不可选
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //设置滚动隐藏
    ui->tableWidget->horizontalHeader()->setVisible(false);   //隐藏行表头
    ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头

    connect(ui->clear_btn,&QPushButton::clicked,ui->textBrowser,[=](){
        ui->textBrowser->clear();
        ui->tableWidget->clear();
        //按下清空按钮，回到创建链表的状态
        ui->listType->setEnabled(true);
        ui->build_btn->setEnabled(true);
        ui->clear_btn->setEnabled(false);
        ui->operationType->setEnabled(false);
        ui->index->setValue(0);
        ui->val->setValue(0);
        ui->index->setEnabled(false);
        ui->val->setEnabled(false);
        ui->confirm_btn->setEnabled(false);
        if(GetListType()=="单链表" && slinklist !=NULL)
            slinklist->destroylinklist();
        else if(GetListType()=="循环链表"&& clinklist !=NULL)
            clinklist->destroylinklist();
        else if(GetListType()=="双向链表"&& dlinklist !=NULL)
            dlinklist->destroylinklist();
        else;
        status=0;
    });
    connect(ui->build_btn,&QPushButton::clicked,[=](){
        //按下创建按钮
        ui->listType->setEnabled(false);
        ui->build_btn->setEnabled(false);
        ui->clear_btn->setEnabled(true);
        ui->operationType->setEnabled(true);
        ui->index->setEnabled(true);
        ui->val->setEnabled(true);
        ui->confirm_btn->setEnabled(true);
        if(GetListType()=="单链表")
        {
            slinklist=new(nothrow)SingleLinkList(this);
            if(slinklist==NULL)
                exit(EXIT_FAILURE);
        }
        else if(GetListType()=="循环链表")
        {
            clinklist=new(nothrow)CircleLinkList(this);
            if(clinklist==NULL)
                exit(EXIT_FAILURE);
        }
        else
        {
            dlinklist=new(nothrow)DoubleLinkList(this);
            if(dlinklist==NULL)
                exit(EXIT_FAILURE);
        }
        ui->tableWidget->setItem(0,0,new QTableWidgetItem("head"));
        ui->tableWidget->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        status=2;
    });
    connect(ui->confirm_btn,&QPushButton::clicked,[=](){
        //按下确定按钮
        ui->listType->setEnabled(false);
        ui->build_btn->setEnabled(false);
        ui->clear_btn->setEnabled(false);
        ui->operationType->setEnabled(false);
        ui->index->setEnabled(false);
        ui->val->setEnabled(false);
        ui->confirm_btn->setEnabled(false);
        if(GetListType()=="单链表")
        {
            if(GetOperationType()=="插入")
                slinklist->insertAtIndex(GetIndex(),GetVal());
            else if(GetOperationType()=="删除")
                slinklist->deleteAtIndex(GetIndex());
            else if(GetOperationType()=="修改")
                slinklist->modifyAtIndex(GetIndex(),GetVal());
            else//查找
                slinklist->searchWithVal(GetVal());

        }
        else if(GetListType()=="循环链表")
        {
            if(GetOperationType()=="插入")
                clinklist->insertAtIndex(GetIndex(),GetVal());
            else if(GetOperationType()=="删除")
                clinklist->deleteAtIndex(GetIndex());
            else if(GetOperationType()=="修改")
                clinklist->modifyAtIndex(GetIndex(),GetVal());
            else//查找
                clinklist->searchWithVal(GetVal());
        }
        else
        {
            if(GetOperationType()=="插入")
                dlinklist->insertAtIndex(GetIndex(),GetVal());
            else if(GetOperationType()=="删除")
                dlinklist->deleteAtIndex(GetIndex());
            else if(GetOperationType()=="修改")
                dlinklist->modifyAtIndex(GetIndex(),GetVal());
            else//查找
                dlinklist->searchWithVal(GetVal());
        }
        status=1;

    });

}


QString Widget::GetListType()//获取当前操作的链表类型
{
    return ui->listType->currentText();
}

QString Widget::GetOperationType()//获取当前的操作类型
{
    return ui->operationType->currentText();
}

int Widget::GetIndex()//获取输入索引
{
    return ui->index->value();;
}

int Widget::GetVal()//获取输入数值
{
    return ui->val->value();
}

void Widget::SetStatus(int status_val)//设置当前状态
{
    status=status_val;
    ui->listType->setEnabled(false);
    ui->build_btn->setEnabled(false);
    ui->clear_btn->setEnabled(true);
    ui->operationType->setEnabled(true);
    ui->index->setEnabled(true);
    ui->val->setEnabled(true);
    ui->confirm_btn->setEnabled(true);
}

void Widget::SetTextBrowser(const QString& text)//在文本展示框中添加日志内容
{
    ui->textBrowser->append(text);
}


void Widget::SetTableWidget(int row,int column,QString data)//在表格控件中展示链表内容
{
    ui->tableWidget->setItem(row,column,new QTableWidgetItem(data));
    ui->tableWidget->item(row,column)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}

void Widget::ClearTableWidget()//清空展示链表
{
    ui->tableWidget->clear();
}

Widget::~Widget()
{
    delete ui;
}

