#include "MemoryManager.h"
#include "MList.h"
#include <iostream>

using namespace std;

/* Starting point for MemoryManager constructor */
MemoryManager::MemoryManager()
{
	allocList = new AllocList(memStart, maxSize);
	freeList = new FreeList(memStart, maxSize);
}

/* Code correct destructor to cleanup all memory */
MemoryManager::~MemoryManager()
{
	allocList->cleanList();
	freeList->cleanList();
	delete allocList;
	delete freeList;
}

/* pre : size > 0
 * post: If no memory block of size "size" available return -1
 *       Otherwise claimMemory() returns the first
 *       address in the freeList where a memory block of at least size is present.
 *       This memory is allocated and not any more available.
 *       The newly allocated block is added to the allocList and addr of the newly
 *       allocated block is returned
 */

int MemoryManager::claimMemory(int size)
{
	if (size <= 0 || size > maxSize)
	{
		return -1;
	}
	ITEM *current = freeList->head;
	while (current != NULL)
	{
		if (current->_size >= size)
		{
			int result = allocList->add(current->_addr, size);
			if (result == -1)
			{
				return -1;
			}
			int addr = current->_addr;
			if (current->_size == size)
			{
				int result2 = freeList->remove(current->_addr);
				if (result2 == -1)
				{
					return -1;
				}
				return addr;
			}
			else
			{
				current->_addr = (current->_addr + size);
				current->_size = (current->_size - size);
			}
			return addr;
		}
		current = current->next;
	}
	return -1;
}

/* pre:  Parameter addr must match the start of an allocatd memory block. Otherwhise return -1.
 *
 * post: If addr is a part of allocated memory of allocList then the memory from this address
 * 	     with registered size should be removed from the allocList and added to the freeList
 *
 *       freeMemory(addr) returns number of bytes (size) belongig to the address addr
 *       In all other cases freeMemory(freeList,allocList,addr) returns -1.
 */

int MemoryManager::freeMemory(int addr)
{
	ITEM *current = allocList->head;
	while (current != NULL)
	{
		if (current->_addr == addr)
		{
			int result = freeList->add(current->_addr, current->_size);
			if (result == -1)
			{
				return -1;
			}
			int size = current->_size;
			int result2 = allocList->remove(current->_addr);
			if (result2 == -1)
			{
				return -1;
			}
			freeList->mergeFreeBlocks();

			return size;
		}
		current = current->next;
	}
	return -1;
}
