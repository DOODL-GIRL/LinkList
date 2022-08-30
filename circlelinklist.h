#ifndef CIRCLELINKLIST_H
#define CIRCLELINKLIST_H
#include "Node.h"
#include<iostream>
#include<stdlib.h>
using namespace std;

class Widget;

//循环链表
class CircleLinkList
{
private:
    SNode* head;
    int length;
    Widget* main_widget;

public:
    CircleLinkList(Widget* widget=NULL);
    void insertAtIndex(int index, int val);
    void deleteAtIndex(int index);
    void modifyAtIndex(int index, int val);
    int searchWithVal(int val);
    void show();
    void destroylinklist();
    ~CircleLinkList();
};

#endif // CIRCLELINKLIST_H
