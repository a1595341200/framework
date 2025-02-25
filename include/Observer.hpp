/*
 * @Author: yao.xie 1595341200@qq.com
 * @Date: 2025-02-25 14:05:22
 * @LastEditors: yao.xie 1595341200@qq.com
 * @LastEditTime: 2025-02-25 14:05:30
 * @FilePath: /cplusplus/framework/include/Observer.hpp
 * @Description:
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#pragma once

class Observer {
public:
    virtual void update(float temperature, float humidity, float pressure) = 0;
    virtual ~Observer() = default;
};
