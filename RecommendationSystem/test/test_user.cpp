#include "test_user.h"
#include <gtest/gtest.h>
#include "../src/User.h"
TEST(User, Contructor) {
    User user(50);
    EXPECT_EQ(user.getUserID(), 50);
}
