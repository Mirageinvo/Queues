#include "gtest/gtest.h"
#include "list_queue_impl.hpp"
#include "stack_queue_impl.hpp"

#ifdef STACK_IMPL
using namespace stack_queue;
#endif

#ifdef LIST_IMPL
using namespace list_queue;
#endif

const int kNum = 1e5;

TEST(IntQueue, IsEmptyTest) {
  Queue<int> q;
  EXPECT_TRUE(q.is_empty());
  q.push(1);
  EXPECT_FALSE(q.is_empty());
}

TEST(IntQueue, SizeTest) {
  Queue<int> q;
  EXPECT_EQ(q.size(), 0);
  q.push(1);
  EXPECT_EQ(q.size(), 1);
  q.push(1);
  EXPECT_EQ(q.size(), 2);
}

TEST(IntQueue, PushTest) {
  Queue<int> q;
  for (int i = 0; i < kNum; ++i) {
    q.push(i);
    ASSERT_EQ(q.back(), i);
  }
}

TEST(IntQueue, BackTest) {
  Queue<int> q;
  for (int i = 0; i < kNum; ++i) {
    q.push(i);
    ASSERT_EQ(q.back(), i);
  }
}

TEST(IntQueue, PopTest) {
  Queue<int> q;
  for (int i = 0; i < kNum; ++i) {
    q.push(i);
    ASSERT_EQ(q.back(), i);
  }
  for (int i = 0; i < kNum; ++i) {
    ASSERT_EQ(q.pop(), i);
  }
}

TEST(IntQueue, FrontTest) {
  Queue<int> q;
  for (int i = 0; i < kNum; ++i) {
    q.push(i);
    ASSERT_EQ(q.back(), i);
  }
  while (!q.is_empty()) {
    int tmp = q.front();
    ASSERT_EQ(tmp, q.pop());
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}