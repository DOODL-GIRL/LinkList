#include "doublelinklist.h"
#include "widget.h"

DoubleLinkList::DoubleLinkList(Widget* widget)
{
    head = new(nothrow)DNode;
    if (head == NULL)
        exit(EXIT_FAILURE);
    head->data = 0;
    head->prior = NULL;
    head->next = NULL;
    length = 0;
    main_widget=widget;
    show();
}

void DoubleLinkList::insertAtIndex(int index, int val)//在索引index前插入元素值为val
{
    if (index > length || index < 0)
    {
        main_widget->SetTextBrowser("索引不正确，插入结点失败！");
        main_widget->SetStatus(2);
    }
    DNode* p = head;
    for (int i = 0; i < index; i++)
    {
        p = p->next;
        main_widget->SetTextBrowser("正在索引第"+QString::number(i)+"项");
    }
    DNode* new_node = new(nothrow)DNode;
    if (new_node == NULL)
        exit(EXIT_FAILURE);
    new_node->data = val;
    new_node->next = p->next;
    new_node->prior = p;
    p->next = new_node;
    length++;
    main_widget->SetTextBrowser("在"+QString::number(index)+"处插入元素值为"+QString::number(val)+"的结点成功！");
    show();
    main_widget->SetStatus(2);
    return;
}

void DoubleLinkList::deleteAtIndex(int index)//删除索引index处的结点
{
    if (index < 0 || index >= length)
    {
        main_widget->SetTextBrowser("索引不正确，删除结点失败！");
        main_widget->SetStatus(2);
        return;
    }
    DNode* p = head;
    for (int i = 0; i < index; i++)
    {
        p = p->next;
        main_widget->SetTextBrowser("正在索引第"+QString::number(i)+"项");
    }
    DNode* q = p->next;
    p->next = q->next;
    q->next->prior = p;
    delete q;
    length--;
    main_widget->SetTextBrowser("删除索引"+QString::number(index)+"处的结点成功！");
    show();
    main_widget->SetStatus(2);
    return;
}

void DoubleLinkList::modifyAtIndex(int index, int val)//将index处结点的元素值修改为val
{
    if (index < 0 || index >= length)
    {
        main_widget->SetTextBrowser("索引不正确，修改结点失败！");
        main_widget->SetStatus(2);
        return;
    }
    DNode* p = head->next;
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

int DoubleLinkList::searchWithVal(int val)//按值查找元素，返回索引
{
    DNode* p = head->next;
    int index=0;
    while (p != NULL)
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

void DoubleLinkList::show()//展示链表元素
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
    DNode* p = head->next;
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

void DoubleLinkList::destroylinklist()
{
    if(head==NULL)
        return;
    DNode* p = head->next;
    while (p != NULL)
    {
        DNode* q = p;
        p = p->next;
        delete q;
    }
    delete head;
}

DoubleLinkList::~DoubleLinkList()
{
    if(head==NULL)
        return;
    DNode* p = head->next;
    while (p != NULL)
    {
        DNode* q = p;
        p = p->next;
        delete q;
    }
    delete head;
}
