#include <gtest/gtest.h>
#include "board.h"
#include "tetromino.h"

const size_t DEFAULT_WIDTH=12;
const size_t DEFAULT_HEIGHT=18;

const uint8_t DEFAULT_BORDER=9;

TEST(Board, ctor){
    Board b;

    EXPECT_EQ(b.width(), DEFAULT_WIDTH);
    EXPECT_EQ(b.height(), DEFAULT_HEIGHT);
    EXPECT_EQ(b(0, 0), '\0');
}

TEST(Board, init){
    // Arrange
    Board b;
    const size_t w = DEFAULT_WIDTH;
    const size_t h = DEFAULT_HEIGHT;

    // Act
    b.init();

    // Assert
    EXPECT_EQ(b.width(), w);
    EXPECT_EQ(b.height(), h);

    EXPECT_EQ(b(0, 0), DEFAULT_BORDER);
    EXPECT_EQ(b(0, 1), 0);
    EXPECT_EQ(b(0, DEFAULT_WIDTH-1), DEFAULT_BORDER);
    EXPECT_EQ(b(DEFAULT_HEIGHT-1, 0), DEFAULT_BORDER);
    EXPECT_EQ(b(DEFAULT_HEIGHT-1, 1), DEFAULT_BORDER);
    EXPECT_EQ(b(DEFAULT_HEIGHT-1, DEFAULT_WIDTH-1), DEFAULT_BORDER);
}

TEST(Board, lock_tetromino)
{
    // Arrange
    Board b;
    b.init();
    Tetromino t;

    // Act
    b.lock(t);

    // Assert
    EXPECT_EQ(b(0, 0), DEFAULT_BORDER);
    EXPECT_EQ(b(0, 1), 0);
    EXPECT_EQ(b(0, 2), 1);
    EXPECT_EQ(b(0, 3), 0);
}