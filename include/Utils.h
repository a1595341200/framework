/*
 * @Author: yao.xie 1595341200@qq.com
 * @Date: 2024-11-20 15:17:12
 * @LastEditors: yao.xie 1595341200@qq.com
 * @LastEditTime: 2024-11-20 15:19:52
 * @FilePath: /cplusplus/framework/include/Utils.h
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#ifndef UTILS_H
#define UTILS_H
#include <glog/logging.h>
namespace framework {

namespace Utils {
void initLog(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_colorlogtostderr = true;
    FLAGS_alsologtostderr = true;
    FLAGS_minloglevel = google::INFO;
    FLAGS_log_dir = "./logs";
}
}  // namespace Utils
}  // namespace framework

#endif /* UTILS_H */
