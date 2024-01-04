#include <iostream>
#include "MList.h"

using namespace std;

/* Implementation of all your MList methods */
void MList::cleanList()
{
    ITEM *current = head;
    while (current != NULL)
    {
        ITEM *temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
    tail = NULL;
}

int MList::add(int addr, int size)
{
    ITEM *current = head;
    if (current == NULL)
    {
        head = new ITEM(addr, size);
        tail = head;
        return 0;
    }
    while (current != NULL)
    {
        if (current->_addr > addr)
        {
            if (current == head)
            {
                head = new ITEM(addr, size);
                head->next = current;
                return 0;
            }
            else
            {
                ITEM *temp = new ITEM(addr, size);
                temp->next = current;
                current = temp;
                return 0;
            }
        }
        if (current->_addr == addr)
        {
            return -1;
        }
        if (current->next == NULL)
        {
            current->next = new ITEM(addr, size);
            tail = current->next;
            return 0;
        }
        if (current->next->_addr > addr)
        {
            ITEM *temp = new ITEM(addr, size);
            temp->next = current->next;
            current->next = temp;
            return 0;
        }
        current = current->next;
    }
    return -1;
}

int MList::remove(int addr)
{
    ITEM *current = head;
    if (current == NULL)
    {
        return -1;
    }
    if (current->_addr == addr)
    {
        head = current->next;
        delete current;
        return 0;
    }
    while (current != NULL)
    {
        if (current->next == NULL)
        {
            return -1;
        }
        if (current->next->_addr == addr)
        {
            ITEM *temp = current->next;
            current->next = current->next->next;
            delete temp;
            return 0;
        }
        current = current->next;
    }
    return -1;
}
