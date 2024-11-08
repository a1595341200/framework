/*
 * @Author: yao.xie 1595341200@qq.com
 * @Date: 2024-11-08 16:05:11
 * @LastEditors: yao.xie 1595341200@qq.com
 * @LastEditTime: 2024-11-08 16:44:48
 * @FilePath: /cplusplus/framework/include/MemoryPool.hpp
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */

#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

// MemoryPool 类定义
template <typename T>
class MemoryPool {
public:
    // 构造函数，初始化内存池，默认每块内存包含1024个对象
    explicit MemoryPool(size_t blockSize = 1024);

    // 析构函数，释放所有分配的内存块
    ~MemoryPool();

    // 禁止拷贝构造函数和拷贝赋值运算符
    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;

    // 分配内存, 返回指向T类型的指针
    template <typename... Args>
    T* allocate(Args&&... args);

    // 释放内存，将指针返回到内存池
    void deallocate(T* ptr);

private:
    // 内存块结构，用于链表管理空闲内存块
    struct FreeNode {
        FreeNode* next;
    };

    // 分配一块新的内存区域，并将其划分为多个FreeNode，加入到空闲链表中
    void allocateBlock();

    size_t m_blockSize;           // 每块内存中包含的对象数量
    std::vector<void*> m_blocks;  // 所有分配的内存块
    FreeNode* m_freeList;         // 空闲内存块链表的头指针

    std::mutex m_mutex;  // 线程安全锁
};

// MemoryPool 构造函数
template <typename T>
MemoryPool<T>::MemoryPool(size_t blockSize) : m_blockSize(blockSize), m_freeList(nullptr) {
    allocateBlock();  // 初始分配一个内存块
}

// MemoryPool 析构函数
template <typename T>
MemoryPool<T>::~MemoryPool() {
    for (auto block : m_blocks) {
        ::operator delete(block);  // 释放每个内存块
    }
}

template <typename T>
template <typename... Args>
T* MemoryPool<T>::allocate(Args&&... args) {
    std::lock_guard<std::mutex> lock(m_mutex);  // 线程安全

    if (!m_freeList) {
        allocateBlock();  // 如果空闲链表为空，分配新的内存块
    }

    // 从空闲链表中取出一个节点
    FreeNode* node = m_freeList;
    m_freeList = node->next;
    T* res = reinterpret_cast<T*>(node);
    new (res) T(std::forward<Args>(args)...);  // 调用构造函数初始化对象
    return res;
}

// 分配一块新的内存区域
template <typename T>
void MemoryPool<T>::allocateBlock() {
    // 计算每个内存块的大小，确保对齐
    size_t size = sizeof(FreeNode) > sizeof(T) ? sizeof(FreeNode) : sizeof(T);

    // 分配一大块内存
    char* block = static_cast<char*>(::operator new(size* m_blockSize));

    m_blocks.push_back(block);  // 记录分配的内存块

    // 将新分配的内存块划分为多个FreeNode，并加入空闲链表
    for (size_t i = 0; i < m_blockSize; ++i) {
        FreeNode* node = reinterpret_cast<FreeNode*>(block + i * size);
        node->next = m_freeList;
        m_freeList = node;
    }
}

// 释放内存
template <typename T>
void MemoryPool<T>::deallocate(T* ptr) {
    std::lock_guard<std::mutex> lock(m_mutex);  // 线程安全
    ptr->~T();  // 调用析构函数
    // 将释放的内存块重新加入到空闲链表
    FreeNode* node = reinterpret_cast<FreeNode*>(ptr);
    node->next = m_freeList;
    m_freeList = node;
}
