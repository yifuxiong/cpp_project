/**
 * 跟着cpp的代码思路自己写一遍
 */

#include <bits/stdc++.h>
using namespace std;

class Memory
{
private:
    // <k, v> -> <appId, memory>, pair<start, end>
    unordered_map<int, vector<pair<int, int>>> memoryToAppId;
    vector<int> memory;
    // len = length / 2
    int len;
    string data;

    // 辅助函数：填充memory数组，用appId占位
    void fillMem(int start, int memSize, int appId) {
        for (int i = start; i < start + memSize; i++) {
            memory[i] = appId;
        }
    }

    // 辅助函数：判断当前地址开始的长度为 memSize 的内存是否有效
    int judgeMem(int start, int memSize) {
        // 首地址 + memSize 大于 分配的内存的字节数，直接返回-1
        if (start + memSize > len) {
            return -1;
        }
        // 如果当前地址已分配内存，返回首地址
        for (int i = start; i < start + memSize; i++) {
            if (memory[i] != -1) {
                return i;
            }
        }
        // 否则这一段是没有分配过内存的
        return -2;
    }

public:
    // Memory(const string &s) {
    //     this->data = s;
    //     this->len = s.size() / 2;
    //     this->memory.assign(s.size() / 2, -1);
    // }

    // 构造函数
    Memory(const string &s): data(s), len(s.size() / 2), memory(s.size() / 2, -1) {}

    // 编号为appId的应用申请一块大小为memSize的内存。
    // - 内存申请时从0字节开始从小到大寻找，寻找一块没有已经被占用、大小为memSize的连续内存。
    // - 如果申请成功，返回内存首地址；申请失败返回-1。保证memSize为4字节的倍数，同一个appId可以申请多块内存。
    int applyMemory(int appId, int memSize) {
        for (int i = 0; i < len; i++) {
            // != -1说明当前这个字节已经被申请了
            if (memory[i] != -1) {
                continue;
            }
            // 直到找到首个-1
            int res = judgeMem(i, memSize);
            if (res == -1) {
                break;
            }
            if (res == -2) {
                // 说明这一段是没有分配过内存的，那我们就拿这块首地址+memSize分配内存大小
                fillMem(i, memSize, appId);
                // 然后把分配的这段内存加到 map 中
                memoryToAppId[appId].push_back({i, i + memSize});
                return i;
            }
            // 否则直接跳到已经分配内存地址块的末尾索引
            i = res;
        }
        return -1;
    }

    // 释放编号为appId的应用申请过的所有的内存
    void freeMemory(int appId) {
        // 这里.find()拿到的是一个迭代器，即 iterator[k, v]
        auto iter = memoryToAppId.find(appId);
        if (iter == memoryToAppId.end()) {
            return;
        }
        // b = pair<start, end>
        for (auto &b: iter->second) {
            for (int j = b.first; j < b.second; j++) {
                if (memory[j] != appId) {
                    break;
                }
                memory[j] = -1;
            }
        }
    }

    // 需要满足以下两个条件才可以写入：
    // - addr对应的内存必须是已被某个appId申请过、且没有被free释放的内存。如果addr对应的内存没有被任意一个appId占用，写入失败，返回-1。
    // - 假设addr隶属于应用appId申请的“首地址为start、长度为len”的内存，则校验码为（总之是一个公式）verify_word = (33 * (33*start + len + appId)) % 251。
    //   writeData的参数verify_word必须和尝试写入的地址的校验码相等才可以写入内存；如果不同，校验失败，返回0。
    // 满足以上条件则可以成功写入：向[addr, addr+4)内存的位置写入内容content。content的长度一定为4字节，并且保证[addr, addr+4)内存一定合法。
    int writeData(int verifyWord, int addr, string content) {
        if (addr < 0 || addr >= len) {
            return -1;
        }
        int appId = memory[addr];
        // 未被申请过
        if (appId == -1) {
            return -1;
        }

        int start = 0;
        int memSize = 0;
        // 这里拿到的是 pair<start, end>
        for (auto &b: memoryToAppId[appId]) {
            if (addr >= b.first && addr <= b.second) {
                // 如果地址在[start, end]这个范围内
                start = b.first;
                memSize = b.second - b.first;
                break;
            }
        }

        // 开始校验码校验
        if ((33 * (33 * start + memSize + appId)) % 251 != verifyWord)
            return 0;

        string prefix = data.substr(0, addr * 2);
        string subfix = data.substr(addr * 2 + content.size());
        data = prefix + content + subfix;
        return 1;
    }

    string query() {
        return data;
    }
};