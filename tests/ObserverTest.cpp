/*
 * @Author: yao.xie 1595341200@qq.com
 * @Date: 2025-02-25 14:42:22
 * @LastEditors: yao.xie 1595341200@qq.com
 * @LastEditTime: 2025-02-25 14:48:03
 * @FilePath: /cplusplus/framework/tests/ObserverTest.cpp
 * @Description:
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "Observer.hpp"
#include "Subject.hpp"

// ConcreteSubject: 天气站
class WeatherStation : public Subject {
private:
    float temperature;
    float humidity;
    float pressure;

public:
    void attach(std::shared_ptr<Observer> observer) override {
        mObservers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) override {
        mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer),
                         mObservers.end());
    }

    void notify() override {
        for (const auto& observer : mObservers) {
            observer->update(temperature, humidity, pressure);
        }
    }

    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        notify();  // 通知所有观察者
    }
};

// ConcreteObserver: 显示设备
class DisplayDevice : public Observer, public std::enable_shared_from_this<DisplayDevice> {
private:
    std::string name;

public:
    DisplayDevice(const std::string& name) : name(name) {
    }

    void update(float temperature, float humidity, float pressure) override {
        std::cout << name << " - Update received: "
                  << "Temperature = " << temperature << "°C, "
                  << "Humidity = " << humidity << "%, "
                  << "Pressure = " << pressure << "hPa" << std::endl;
    }

    void subscribe(std::shared_ptr<Subject> subject) {
        subject->attach(shared_from_this());
    }

    void unsubscribe(std::shared_ptr<Subject> subject) {
        subject->detach(shared_from_this());
    }
};

// 客户端代码
int main() {
    // 创建天气站
    auto weatherStation = std::make_shared<WeatherStation>();

    // 创建显示设备
    auto display1 = std::make_shared<DisplayDevice>("Display 1");
    auto display2 = std::make_shared<DisplayDevice>("Display 2");

    // 订阅天气站
    display1->subscribe(weatherStation);
    display2->subscribe(weatherStation);

    // 更新天气数据
    weatherStation->setMeasurements(25.5, 65, 1013);
    weatherStation->setMeasurements(26.0, 70, 1012);

    // 取消订阅
    display2->unsubscribe(weatherStation);

    // 再次更新天气数据
    weatherStation->setMeasurements(27.0, 75, 1011);

    return 0;
}
