/*
 * @Author: yao.xie 1595341200@qq.com
 * @Date: 2025-02-25 14:04:07
 * @LastEditors: yao.xie 1595341200@qq.com
 * @LastEditTime: 2025-02-25 14:46:13
 * @FilePath: /cplusplus/framework/include/Subject.hpp
 * @Description:
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#pragma once
#include <memory>
#include "Observer.hpp"

class Subject {
public:
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
    std::vector<std::shared_ptr<Observer>> mObservers;
};
