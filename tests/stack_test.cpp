#include <gtest/gtest.h>
#include "stack.h"

TEST(StackTest, Basic) {

    Stack<short> s; 
    s.push(42);
    EXPECT_EQ(s.peek(), 42);

    s.emplace(50);
    auto it = s.begin();
    EXPECT_EQ(*it++, 50);
    EXPECT_EQ(*it, 42);

    EXPECT_EQ(s.pop(), 50);
    EXPECT_EQ(s.pop(), 42);
}