/*
 * @Author: yao.xie 1595341200@qq.com
 * @Date: 2024-11-20 15:13:16
 * @LastEditors: yao.xie 1595341200@qq.com
 * @LastEditTime: 2024-11-20 16:06:35
 * @FilePath: /cplusplus/framework/tests/timer_tests.cpp
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#include <thread>

#include <gtest/gtest.h>

#include "Timer.h"
#include "Utils.h"

TEST(TimerTest, TimerWorks) {
    for (size_t i = 0; i < 10; ++i) {
        framework::Timer::Evaluate(
            [&i]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(50 * i));
            },
            std::string("test1-") + std ::to_string(i));
    }

    framework::Timer::PrintAll();
    framework::Timer::DumpIntoFile("./logs/timer.log");
}

int main(int argc, char* argv[]) {
    framework::Utils::initLog(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
