/*
 * @Author: yao.xie 1595341200@qq.com
 * @Date: 2024-11-20 15:08:10
 * @LastEditors: yao.xie 1595341200@qq.com
 * @LastEditTime: 2024-11-20 15:35:04
 * @FilePath: /cplusplus/framework/include/Timer.h
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */

#ifndef FUSION_TIMER_H
#define FUSION_TIMER_H

#include <chrono>
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace framework {

/// 统计时间工具
class Timer {
public:
    struct TimerRecord {
        TimerRecord() = default;
        TimerRecord(const std::string& name, double time_usage) {
            func_name_ = name;
            time_usage_in_ms_.emplace_back(time_usage);
        }
        std::string func_name_;
        std::vector<double> time_usage_in_ms_;
    };

    /**
     * 评价并记录函数用时
     * @tparam F
     * @param func
     * @param func_name
     */
    template <class F>
    static void Evaluate(F&& func, const std::string& func_name) {
        auto t1 = std::chrono::steady_clock::now();
        std::forward<F>(func)();
        auto t2 = std::chrono::steady_clock::now();
        // 微秒转毫秒
        auto time_used =
            std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;
        // 纳秒
        // auto time_used = (t2 - t1).count();

        if (records_.count(func_name) != 0) {
            records_[func_name].time_usage_in_ms_.emplace_back(time_used);
        } else {
            records_.insert({func_name, TimerRecord(func_name, time_used)});
        }
    }

    /// 打印记录的所有耗时
    static void PrintAll();

    /// 写入文件，方便作图分析
    static void DumpIntoFile(const std::string& file_name);

    /// 获取某个函数的平均执行时间
    static double GetMeanTime(const std::string& func_name);

    /// 清理记录
    static void Clear() {
        records_.clear();
    }

private:
    static std::map<std::string, TimerRecord> records_;
};

}  // namespace framework

#endif  // FUSION_TIMER_H
