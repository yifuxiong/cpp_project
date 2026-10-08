#include <bits/stdc++.h>
using namespace std;

/**
 * 题目一：日志文件系统
题目背景
某服务器上运行着多个业务模块，每个模块通过 moduleId 唯一标识。各模块会持续产生日志，日志需要落盘保存为日志文件。受存储条件限制，系统有两个硬性约束：
单个日志文件的大小上限为 singleFileSize；所有日志文件的总大小上限为 totalFileSize。
请你实现一个日志系统，管理这些日志文件的创建、追加写入与淘汰。
接口定义
class LogSystem {
public:
    LogSystem(int singleFileSize, int totalFileSize);
    int WriteLog(int moduleId, int length);
    vector<tuple<int, int, int>> QueryLog();
};
构造函数 LogSystem(singleFileSize, totalFileSize)：初始化日志系统，设定单文件大小上限和总大小上限，当前已用总空间为 0。
写日志 WriteLog(moduleId, length)：为模块 moduleId 写入一条长度为 length 字节的日志，返回本次写入后目标文件的当前大小。
        每个模块的日志文件按创建顺序从 1 开始编号，依次为 1、2、3……不同模块各自独立编号。
        若该模块已有日志文件，且写入后不超过单文件上限（singleFileSize），则直接追加到当前文件，返回追加后的文件大小。
        若当前文件剩余空间不足，则为该模块创建新日志文件
        若空间不够，按文件创建时间从最早开始依次删除文件。
查询日志 QueryLog()：返回当前系统中所有尚未被删除的日志文件列表，按文件的创建（写入）时间先后排序。每个元素是一个三元组 (moduleId, 文件编号, 文件大小)。
 */
class LogSystem
{
public:
    LogSystem(int singleFileSize, int totalFileSize)
    {
        singleFileSize_ = singleFileSize;
        totalFileSize_ = totalFileSize;
        curFileSize_ = 0;
        curModuleId_ = 0;
        curFileIndex_ = 1;
        grid_ = {};
        logs_ = {};
    }

    int WriteLog(int moduleId, int length)
    {
        int curIdx = 0;
        int size = grid_[moduleId].size();
        if (size == 0) {
            // 若当前模块还没有日志文件
            curIdx = 0;
        } else {
            // 若该模块已有日志文件
            curIdx = size - 1;
        }

        // 如果本身length就超过了单个文件大小，那么做截断操作，超过的部分复用下面的逻辑
        int prefixLength = 0;
        if (length > singleFileSize_) {
            int shan = length / singleFileSize_;
            int yu = length % singleFileSize_;
            
            if (grid_[moduleId][curIdx] != 0) {
                int addLength = singleFileSize_ - grid_[moduleId][curIdx];
                curFileSize_ += addLength;
                for (int i = 0; i < shan; i++) {
                    grid_[moduleId][curIdx] = singleFileSize_;
                    curFileSize_ += singleFileSize_;
                    curIdx++;
                    
                }
                curFileIndex_ = curIdx;
            } else {
                for (int i = 0; i < shan; i++) {
                    grid_[moduleId][curIdx] = singleFileSize_;
                    curFileSize_ += singleFileSize_;
                    curIdx++;
                    
                }
                curFileIndex_ = curIdx;
            }
            length = yu;
        }

        // 若写入后不超过单文件上限，直接追加到当前文件，返回追加后的文件大小
        if (grid_[moduleId][curIdx] + length < singleFileSize_) {
            if (curFileSize_ + length > totalFileSize_) {
                // 若空间不够，按文件创建时间从最早开始依次删除文件
                grid_[curModuleId_][curFileIndex_] = 0;
                curFileSize_ -= singleFileSize_;
                if (curFileIndex_ == grid_[curModuleId_].size() - 1) {
                    curModuleId_++;
                    curFileIndex_ = 1;
                } else {
                    curFileIndex_++;
                }
            }
            grid_[moduleId][curIdx] += length;
            curFileSize_ += length;
            return grid_[moduleId][curIdx];
        } else {
            // 若当前文件剩余空间不足，则为该模块创建新日志文件（则会多出来部分空间浪费掉，这些浪费掉的空间也算到前面这个没有追加的文件大小上，另外也要加到总空间上）
            int addLength = (singleFileSize_ - grid_[moduleId][curIdx]) + length;
            if (curFileSize_ + addLength > totalFileSize_) {
                // 若空间不够，按文件创建时间从最早开始依次删除文件
                grid_[curModuleId_][curFileIndex_] = 0;
                curFileSize_ -= singleFileSize_;
                if (curFileIndex_ == grid_[curModuleId_].size() - 1) {
                    curModuleId_++;
                    curFileIndex_ = 1;
                } else {
                    curFileIndex_++;
                }
            }
            curFileSize_ += addLength;
            grid_[moduleId][curIdx] = singleFileSize_;
            curFileSize_ += singleFileSize_;
            grid_[moduleId][curIdx + 1] += length;
            curFileSize_ += length;
            return grid_[moduleId][curIdx + 1];
        }
        
    }

    vector<tuple<int, int, int>> QueryLog()
    {
        for (int i = 0; i < grid_.size(); i++) {
            for (int j = 0; j < grid_[0].size(); j++) {
                if (grid_[i][j] != 0) {
                    tuple<int, int, int> tp = {i, j, grid_[i][j]};
                    logs_.push_back(tp);
                }
            }
        }
        return logs_;
    }

private:
    // 单个文件大小上限
    int singleFileSize_;
    // 总的空间大小上限
    int totalFileSize_;
    // 当前占用的总的空间大小
    int curFileSize_;
    // 记录每个module的每个index的占用空间大小
    vector<vector<int>> grid_;
    // 记录第一个moduleId，从0开始
    int curModuleId_;
    // 记录这个moduleId的第一个文件index，从1开始
    int curFileIndex_;
    // 文件列表
    vector<tuple<int, int, int>> logs_;
};