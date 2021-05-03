#include <gtest/gtest.h>
#include "tetromino.h"

TEST(Tetromino, ctor){
    Tetromino t;

    EXPECT_EQ(t.index(), 0);
}