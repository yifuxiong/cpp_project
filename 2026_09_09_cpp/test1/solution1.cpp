#include <vector>
#include <tuple>
#include <bits/stdc++.h>
using namespace std;

class LogSystem
{
public:
    LogSystem(int singleFileSize, int totalFileSize)
    {
        this->singleFileSize = singleFileSize;
        this->totalFileSize = totalFileSize;
        this->curTotalFileSize = 0;
    }

    // 空间不够，按文件创建时间从最早开始依次删除文件
    void tempfunc1(int moduleId, int length)
    {
        // lst保存的是按照时间顺序存放的文件信息，tuple<int, int, int>分别表示moduleId, fileId, fileSize
        auto releaseIt = lst.begin();
        int releaseModuleId = get<0>(*releaseIt);
        int releaseModuleIdx = get<1>(*releaseIt);
        // idx是unordered_map
        auto &[curIdx, unused, curState] = idx[releaseModuleId];
        if (curIdx == releaseModuleIdx)
        {
            // 1表示正常，0表示被释放
            curState = 0;
        }
        curTotalFileSize -= get<2>(*releaseIt);
        lst.pop_front();
    }

    int WriteLog(int moduleId, int length)
    {
        while (curTotalFileSize + length > totalFileSize)
        {
            tempfunc1(moduleId, length);
        }
        if (idx.find(moduleId) == idx.end())
        { // 首次创建
            if (curTotalFileSize >= totalFileSize)
            {
                tempfunc1(moduleId, length);
            }
            lst.push_back({moduleId, 1, length});
            curTotalFileSize += length;
            idx[moduleId] = make_tuple(1, prev(lst.end(), 1), 1);
            return length;
        }

        auto &[curindex, curIt, curState] = idx[moduleId];
        int curlength = get<2>(*curIt);
        if (curState == 0 || curlength + length > singleFileSize)
        {
            if (curTotalFileSize >= totalFileSize)
            {
                tempfunc1(moduleId, length);
            }
            int prevIdx = get<1>(*curIt);
            int curIdx = prevIdx + 1;
            lst.push_back({moduleId, curIdx, length});
            curTotalFileSize += length;
            idx[moduleId] = make_tuple(curIdx, prev(lst.end(), 1), 1);
        }
        else
        {
            if (curlength + length <= singleFileSize)
            {
                get<2>(*curIt) = curlength + length;
                curTotalFileSize += length;
                return curlength = length;
            }
        }
        return length;
    }

    // 可以使用std::get访问tuple中的成员，比如std::get<0>(obj)可访问obj中的第一个成员
    vector<tuple<int, int, int>> QueryLog()
    {
        vector<tuple<int, int, int>> ans;
        for (auto it = lst.begin(); it != lst.end(); it++)
        {
            ans.push_back(*it);
        }
        return ans;
    }

private:
    // 每个模块id的index，第三个int表示状态：1正常，0被释放
    unordered_map<int, tuple<int, list<tuple<int, int, int>>::iterator, int>> idx;
    // 文件按时间顺序放到链表中，tuple<int, int, int>分别表示moduleId, fileId, fileSize
    list<tuple<int, int, int>> lst;
    int singleFileSize;
    int totalFileSize;
    int curTotalFileSize;
};