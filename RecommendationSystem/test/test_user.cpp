#include "test_user.h"
#include <gtest/gtest.h>
#include "objects/User.h"
TEST(User, Contructor) {
    User user(50);
    EXPECT_EQ(user.getUserID(), 50);
}
