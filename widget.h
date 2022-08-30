#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsRectItem>

class SingleLinkList;
class CircleLinkList;
class DoubleLinkList;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    QString GetListType();//获取当前操作的链表类型
    QString GetOperationType();//获取当前的操作类型
    int GetIndex();//获取输入索引
    int GetVal();//获取输入数值

    void SetStatus(int status_val);//设置当前状态
    void SetTextBrowser(const QString& text);//在文本展示框中添加日志内容
    void SetTableWidget(int row,int column,QString data);//在表格控件中展示链表内容
    void ClearTableWidget();//清空展示链表

    void initUI();					//初始UI控件
    void initSceneView();			//初始化视图框架
    void adjustController();		//操作之后调整右侧输入和显示控件

    ~Widget();

public:
    Ui::Widget *ui;
    int status;//当前状态：0 链表待创建；1 链表正在进行操作 2操作完成，等待下一条指令
    SingleLinkList* slinklist;
    CircleLinkList* clinklist;
    DoubleLinkList* dlinklist;


};
#endif // WIDGET_H
