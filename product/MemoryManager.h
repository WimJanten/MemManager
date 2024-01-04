#pragma once

#include "MList.h"
#include <cstddef>

/* Code functionality for the AllocList, think well which functionality is specific for AllocList and which is generic to MList */

class AllocList : public MList
{
public:
    int memStart;
    int maxSize;
    AllocList(int mst, int msz)
    {
        memStart = mst;
        maxSize = msz;
    };
};

/* Code functionality for the FreeList, think well which functionality is specific for FreeList and which is generic to MList */

class FreeList : public MList
{
public:
    int memStart;
    int maxSize;
    FreeList(int mst, int msz)
    {
        memStart = mst;
        maxSize = msz;
        head = new ITEM(memStart, maxSize);
    }
    void mergeFreeBlocks()
    {
        ITEM *current = head;
        bool changed = true;
        while (changed == true)
        {
            changed = false;
            while (current != NULL)
            {
                if (current->next != NULL)
                {
                    if ((current->_addr + current->_size) == current->next->_addr)
                    {
                        current->_size = (current->_size + current->next->_size);
                        ITEM *temp = current->next;
                        current->next = current->next->next;
                        delete temp;
                        changed = true;
                    }
                }
                current = current->next;
            }
            current = head; 
        }
    }
};

class MemoryManager
{
public:
    const int memStart = 1000;
    const int maxSize = 100;
    AllocList *allocList;
    FreeList *freeList;

    MemoryManager();
    ~MemoryManager();
    int claimMemory(int size);
    int freeMemory(int addr);
};
