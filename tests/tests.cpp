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

TEST(IntQueue, CopyConstrTest) {
  Queue<int> q1;
  for (int i = 0; i < kNum; ++i) {
    q1.push(i);
    ASSERT_EQ(q1.back(), i);
  }
  Queue<int> q2(q1);
  for (int i = 0; i < kNum; ++i) {
    ASSERT_EQ(q2.pop(), i);
  }
}

TEST(IntQueue, MoveConstrTest) {
  Queue<int> q1;
  for (int i = 0; i < kNum; ++i) {
    q1.push(i);
    ASSERT_EQ(q1.back(), i);
  }
  Queue<int> q2(std::move(q1));
  for (int i = 0; i < kNum; ++i) {
    ASSERT_EQ(q2.pop(), i);
  }
}

TEST(IntQueue, BoolEqOperatorTest) {
  Queue<int> q1;
  Queue<int> q2;
  ASSERT_TRUE(q1 == q2);
  for (int i = 0; i < kNum; ++i) {
    q1.push(i);
    ASSERT_EQ(q1.back(), i);
    q2.push(i);
    ASSERT_EQ(q2.back(), i);
    if (i == 3) {
      q1.pop();
      q1.pop();
    } else if (i == 50000) {
      q2.pop();
      q2.pop();
    }
  }
  ASSERT_TRUE(q1 == q2);
  q1.pop();
  ASSERT_FALSE(q1 == q2);
  q2.pop();
  ASSERT_TRUE(q1 == q2);
}

TEST(IntQueue, BoolUneqOperatorTest) {
  Queue<int> q1;
  Queue<int> q2;
  ASSERT_FALSE(q1 != q2);
  for (int i = 0; i < kNum; ++i) {
    q1.push(i);
    ASSERT_EQ(q1.back(), i);
    q2.push(i);
    ASSERT_EQ(q2.back(), i);
  }
  ASSERT_FALSE(q1 != q2);
  q1.pop();
  ASSERT_TRUE(q1 != q2);
  q2.pop();
  ASSERT_FALSE(q1 != q2);
}

TEST(IntQueue, EqCopyOperatorTest) {
  Queue<int> q1;
  Queue<int> q2;
  ASSERT_TRUE(q1 == q2);
  for (int i = 0; i < kNum; ++i) {
    q1.push(i);
    ASSERT_EQ(q1.back(), i);
  }
  q2 = q1;
  for (int i = 0; i < kNum; ++i) {
    ASSERT_EQ(q2.pop(), i);
  }
  ASSERT_TRUE(q2.is_empty());
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}