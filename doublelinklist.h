#ifndef DOUBLELINKLIST_H
#define DOUBLELINKLIST_H
#include "Node.h"
#include<iostream>
#include<stdlib.h>
using namespace std;

class Widget;

//双向链表
class DoubleLinkList
{
private:
    DNode* head;
    int length;
    Widget* main_widget;

public:
    DoubleLinkList(Widget* widget=NULL);
    void insertAtIndex(int index, int val);
    void deleteAtIndex(int index);
    void modifyAtIndex(int index, int val);
    int searchWithVal(int val);
    void show();
    void destroylinklist();
    ~DoubleLinkList();
};

#endif // DOUBLELINKLIST_H
