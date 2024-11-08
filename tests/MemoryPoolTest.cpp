/*
 * @Author: yao.xie 1595341200@qq.com
 * @Date: 2024-11-08 16:11:23
 * @LastEditors: yao.xie 1595341200@qq.com
 * @LastEditTime: 2024-11-08 16:19:11
 * @FilePath: /cplusplus/framework/tests/MemoryPoolTest.cpp
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#include <iostream>
#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "MemoryPool.hpp"

// 假设内存池类已经定义，如上文所示

class MyObject {
public:
    MyObject(int data = 0) : data_(data) {
        std::cout << "MyObject constructed with data = " << data_ << std::endl;
    }

    ~MyObject() {
        std::cout << "MyObject destructed with data = " << data_ << std::endl;
    }

    void setData(int data) {
        data_ = data;
    }
    int getData() const {
        return data_;
    }

private:
    int data_;
};

TEST(memoryPoolTest, testMemoryPool) {
    // 创建一个内存池，预分配1024个MyObject对象
    MemoryPool<MyObject> pool(1024);

    // 分配一个MyObject对象
    MyObject* obj1 = pool.allocate(42);

    std::cout << "obj1 data: " << obj1->getData() << std::endl;
    ASSERT_EQ(obj1->getData(), 42);
    
    // 使用完毕后，调用析构函数并释放内存
    pool.deallocate(obj1);

    // 分配多个对象
    std::vector<MyObject*> objects;
    for (int i = 0; i < 10; ++i) {
        MyObject* obj = pool.allocate();
        new (obj) MyObject(i);
        objects.push_back(obj);
    }

    // 输出对象数据
    for (auto obj : objects) {
        std::cout << "MyObject data: " << obj->getData() << std::endl;
    }

    // 释放对象
    for (auto obj : objects) {
        obj->~MyObject();
        pool.deallocate(obj);
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
