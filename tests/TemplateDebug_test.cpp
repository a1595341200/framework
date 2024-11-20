/*
 * @Author: yao.xie 1595341200@qq.com
 * @Date: 2024-09-24 15:12:04
 * @LastEditors: yao.xie 1595341200@qq.com
 * @LastEditTime: 2024-11-20 15:13:34
 * @FilePath: /cplusplus/framework/tests/TemplateDebug_test.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
/*
 * @Author: yao.xie 1595341200@qq.com
 * @Date: 2024-07-15 15:02:25
 * @LastEditors: yao.xie 1595341200@qq.com
 * @LastEditTime: 2024-07-15 17:28:00
 * @FilePath: /cplusplus/framework/tests/TemplateDebug_test.cpp
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#include "TemplateDebug.hpp"

#include <iostream>

class T1 {
public:
    void print(){};
};

auto main()->int {
    // TemplateDebug<decltype(&T1::print)> test;
    return 0;
}
