#include <gtest/gtest.h>
#include "fifo_lib/frame_fifo.hpp"

TEST(CameraFIFO, NewFrameFIFOIsEmpty) {
    FrameFifo fifo;
    EXPECT_EQ(fifo.empty(), true);
}

TEST(FrameFifoBlackBox, Hypothesis2_PushBackTwice) {
    FrameFifo fifo;
    CameraFrame frame1;
    CameraFrame frame2;

    fifo.pushBack(frame1);
    fifo.pushBack(frame2);

    EXPECT_EQ(fifo.getSize(), 2);

    // Predpokladáme, že at() vracia objekt typu FramePtr alebo podobný,
    // ktorý má metódu lock() alebo get() pre prístup k pointeru
    auto ptr0 = fifo.at(0).lock();
    auto ptr1 = fifo.at(1).lock();

    ASSERT_NE(ptr0, nullptr);
    ASSERT_NE(ptr1, nullptr);
    EXPECT_NE(ptr0, ptr1); // Musia to byť dve rôzne adresy v pamäti
}