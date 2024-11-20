#! /usr/bin/python3
# coding=UTF-8
import sys
import numpy as np
import matplotlib.pyplot as plt

# 文件格式
# test1, test2,
# 50.074,50.152,

class TimePlot:
    # 构造函数
    def __init__(self, path:str):
        self.path = path
        self.data = []
        self.time_usage = []
        self.method_names = []

    # 读取文件
    def read_file(self):
        with open(self.path, 'r') as f:
            lines = f.readlines()

        for line in lines:
            line = line.strip()
            #删除最后一个逗号
            line = line.rstrip(',')
            values = line.split(',')
            self.data.append(values)

    # 解析文件并存储到列表中
    def parse_data(self):
        self.time_usage = np.array(self.data[1], dtype=float)
        self.method_names = self.data[0]
    # 绘图
    def plot(self):
        plt.figure()
        plt.bar(self.method_names, self.time_usage, color=['r', 'g', 'b', 'k', 'y', 'c'])
        plt.title('Align Time Usage')
        plt.xlabel("method name")
        plt.ylabel("runtime(ms)")
        plt.grid()
        plt.show()

# 测试
if __name__ == '__main__':
    tp = TimePlot('logs/timer.log')
    tp.read_file()
    tp.parse_data()
    tp.plot()
    