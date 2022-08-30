#ifndef SINGLELINKLIST_H
#define SINGLELINKLIST_H
#include "Node.h"
#include<iostream>
#include<stdlib.h>
using namespace std;

class Widget;

//单链表
class SingleLinkList
{
private:
    SNode* head;
    int length;
    Widget* main_widget;

public:
    SingleLinkList(Widget* widget=NULL);
    void insertAtIndex(int index, int val);
    void deleteAtIndex(int index);
    void modifyAtIndex(int index, int val);
    int searchWithVal(int val);
    void show();
    void destroylinklist();
    ~SingleLinkList();
};

#endif // SINGLELINKLIST_H
