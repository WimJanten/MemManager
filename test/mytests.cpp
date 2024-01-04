
#include "MemoryManager.h"
#include "MList.h"
#include "gtest/gtest.h"

class metaTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
 
  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

/* A simple example of Unit Test */
TEST_F(metaTest,testClaim)
{
  MemoryManager *mm = new MemoryManager();
  int ret = mm->claimMemory(20);
  EXPECT_EQ(mm->memStart, ret);
  EXPECT_EQ(mm->memStart, mm->allocList->head->_addr);
  EXPECT_EQ(20, mm->allocList->head->_size);
  delete mm;
}

TEST_F(metaTest, testClaimMem)
{
  MemoryManager *mm = new MemoryManager();
  int ret = mm->claimMemory(20);
  EXPECT_EQ(mm->memStart, ret);
  EXPECT_EQ(mm->memStart, mm->allocList->head->_addr);
  EXPECT_EQ(20, mm->allocList->head->_size);
  ret = mm->claimMemory(30);
  EXPECT_EQ(mm->memStart + 20, ret);
  EXPECT_EQ(mm->memStart + 20, mm->allocList->head->next->_addr);
  EXPECT_EQ(30, mm->allocList->head->next->_size);
  delete mm;
}

TEST_F(metaTest, testFreeMem){
  MemoryManager *mm = new MemoryManager();
  int ret = mm->claimMemory(20);
  EXPECT_EQ(mm->memStart, ret);
  EXPECT_EQ(mm->memStart, mm->allocList->head->_addr);
  EXPECT_EQ(20, mm->allocList->head->_size);
  ret = mm->claimMemory(30);
  EXPECT_EQ(mm->memStart + 20, ret);
  EXPECT_EQ(mm->memStart + 20, mm->allocList->head->next->_addr);
  EXPECT_EQ(30, mm->allocList->head->next->_size);
  mm->freeMemory(mm->memStart);
  EXPECT_EQ(mm->memStart + 20, mm->allocList->head->_addr);
  EXPECT_EQ(30, mm->allocList->head->_size);
  EXPECT_EQ(20, mm->freeList->head->_size);
  mm->freeMemory(mm->memStart + 20);
  EXPECT_EQ(mm->maxSize, mm->freeList->head->_size);
  EXPECT_EQ(NULL, mm->allocList->head);
  delete mm;
}

TEST_F(metaTest, testClaimMemOverMax){
  MemoryManager *mm = new MemoryManager();
  int ret = mm->claimMemory(101);
  EXPECT_EQ(-1, ret);
  delete mm;
}

TEST_F(metaTest, testFreeMemNoAlloc){
  MemoryManager *mm = new MemoryManager();
  int ret = mm->freeMemory(mm->memStart);
  EXPECT_EQ(-1, ret);
  EXPECT_EQ(mm->maxSize, mm->freeList->head->_size);
  EXPECT_EQ(NULL, mm->allocList->head);
  delete mm;
}

TEST_F(metaTest, testMergeBlocks){
  MemoryManager *mm = new MemoryManager();
  int ret = mm->claimMemory(20);
  EXPECT_EQ(mm->memStart, ret);
  EXPECT_EQ(mm->memStart, mm->allocList->head->_addr);
  EXPECT_EQ(20, mm->allocList->head->_size);
  ret = mm->claimMemory(30);
  EXPECT_EQ(mm->memStart + 20, ret);
  EXPECT_EQ(mm->memStart + 20, mm->allocList->head->next->_addr);
  EXPECT_EQ(30, mm->allocList->head->next->_size);
  mm->freeMemory(mm->memStart);
  EXPECT_EQ(mm->memStart + 20, mm->allocList->head->_addr);
  EXPECT_EQ(30, mm->allocList->head->_size);
  EXPECT_EQ(20, mm->freeList->head->_size);
  EXPECT_EQ(50, mm->freeList->head->next->_size);
  mm->freeMemory(mm->memStart + 20);
  EXPECT_EQ(mm->maxSize, mm->freeList->head->_size);
  EXPECT_EQ(NULL, mm->allocList->head);
  delete mm;
}