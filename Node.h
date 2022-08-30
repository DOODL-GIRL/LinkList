#ifndef NODE_H
#define NODE_H

struct SNode//单链表结点
{
    int data;
    SNode* next;
};

struct DNode//双向链表结点
{
    int data;
    DNode* prior;
    DNode* next;
};

#endif // NODE_H
