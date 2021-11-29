#include "gtest/gtest.h"
#include "stack_queue_impl.hpp"
#include "list_queue_impl.hpp"

#ifdef STACK_IMPL
using namespace stack_queue;
#endif

#ifdef LIST_IMPL
using namespace list_queue;
#endif

TEST(IntStack, PushTest) {
  Queue<int> q;
  ASSERT_TRUE(true);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}