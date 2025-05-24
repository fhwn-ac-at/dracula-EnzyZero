#include <gtest/gtest.h>
#include "stack.h"

TEST(StackTest, Basic) {

    Stack<int> s;
    s.push(42);
    EXPECT_EQ(s.peek(), 42);

    EXPECT_EQ(s.pop(), 42);
    EXPECT_TRUE(s.empty()); 
}