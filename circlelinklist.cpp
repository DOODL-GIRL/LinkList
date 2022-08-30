#include "circlelinklist.h"
#include "widget.h"

CircleLinkList::CircleLinkList(Widget *widget)
{
    head = new(nothrow)SNode;
    if (head == NULL)
        exit(EXIT_FAILURE);
    head->data = 0;
    head->next = head;
    length = 0;
    main_widget=widget;
    show();
}

void CircleLinkList::insertAtIndex(int index, int val)//在索引index前插入元素值为val
{
    if (index > length || index < 0)
    {
        main_widget->SetTextBrowser("索引不正确，插入结点失败！");
        main_widget->SetStatus(2);
        return;
    }
    SNode* p = head;
    for (int i = 0; i < index; i++)
    {
        p = p->next;
        main_widget->SetTextBrowser("正在索引第"+QString::number(i)+"项");
    }
    SNode* new_node = new(nothrow)SNode;
    if (new_node == NULL)
        exit(EXIT_FAILURE);
    new_node->data = val;
    new_node->next = p->next;
    p->next = new_node;
    length++;
    main_widget->SetTextBrowser("在"+QString::number(index)+"处插入元素值为"+QString::number(val)+"的结点成功！");
    show();
    main_widget->SetStatus(2);
    return;
}

void CircleLinkList::deleteAtIndex(int index)//删除索引index处的结点
{
    if (index < 0 || index >= length)
    {
        main_widget->SetTextBrowser("索引不正确，删除结点失败！");
        main_widget->SetStatus(2);
        return;
    }
    SNode* p = head;
    for (int i = 0; i < index; i++)
    {
        p = p->next;
        main_widget->SetTextBrowser("正在索引第"+QString::number(i)+"项");
    }
    SNode* q = p->next;
    p->next = q->next;
    delete q;
    length--;
    main_widget->SetTextBrowser("删除索引"+QString::number(index)+"处的结点成功！");
    show();
    main_widget->SetStatus(2);
    return;
}

void CircleLinkList::modifyAtIndex(int index, int val)//将index处结点的元素值修改为val
{
    if (index < 0 || index >= length)
    {
        main_widget->SetTextBrowser("索引不正确，修改结点失败！");
        main_widget->SetStatus(2);
        return;
    }
    SNode* p = head->next;
    for (int i = 0; i < index; i++)
    {
        p = p->next;
        main_widget->SetTextBrowser("正在索引第"+QString::number(i)+"项");
    }
    p->data = val;
    main_widget->SetTextBrowser("修改索引"+QString::number(index)+"处结点的元素值为"+QString::number(val)+"成功！");
    show();
    main_widget->SetStatus(2);
    return;
}

int CircleLinkList::searchWithVal(int val)//按值查找元素，返回索引
{
    SNode* p = head->next;
    int index=0;
    while (p != head)
    {
        if (p->data == val)
        {
            main_widget->SetTextBrowser("值为"+QString::number(val)+"对应元素索引为"+QString::number(index));
            main_widget->SetStatus(2);
            return p - head->next;
        }
        p = p->next;
        index++;
    }
    main_widget->SetTextBrowser("元素不存在，查找失败！");
    main_widget->SetStatus(2);
    return -1;
}

void CircleLinkList::show()//展示链表元素
{
    main_widget->ClearTableWidget();
    main_widget->SetTableWidget(0,0,"head");
    QString elements="当前列表中的内容为：";
    if (length == 0)
    {
        elements=elements+"空";
        main_widget->SetTextBrowser(elements);
        main_widget->SetStatus(2);
        return;
    }
    int i=0;
    int j=0;
    SNode* p = head->next;
    while (p != NULL)
    {
        if(j==3)
        {
            i++;
            j=0;
        }
        else
            j++;
        elements=elements+QString::number(p->data)+" ";
        main_widget->SetTableWidget(i,j,QString::number(p->data));
        p = p->next;
    }
    main_widget->SetTextBrowser(elements);
    main_widget->SetStatus(2);
    return;
}

void CircleLinkList::destroylinklist()
{
    if(head==NULL)
        return;
    SNode* p = head->next;
    while (p != head)
    {
        SNode* q = p;
        p = p->next;
        delete q;
    }
    delete head;
}

CircleLinkList::~CircleLinkList()
{
    if(head==NULL)
        return;
    SNode* p = head->next;
    while (p != head)
    {
        SNode* q = p;
        p = p->next;
        delete q;
    }
    delete head;
}
