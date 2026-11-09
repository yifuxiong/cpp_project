/**
 * 第2题：（设计题）内存分配和写入

题目描述：（尝试回忆内容，如果有变量名不对就说明我记性不好……但是需要几个变量和每个变量的含义应该是对的）设计一个内存分配类，实现以下功能：

1.（构造函数）Memory(string s)
初始化内存，内容即为变量string s，s是一个长度length的16进制字符串[0-9A-F]。每两个16进制为一个字节，所以意味着这段内存的字节数为length/2 .
初始所有内存均为未分配，内存的下标从0字节开始到length/2-1字节。

2. int applyMemory(int appId, int memSize)
编号为appId的应用申请一块大小为memSize的内存。内存申请时从0字节开始从小到大寻找，寻找一块没有已经被占用、大小为memSize的连续内存。
如果申请成功，返回内存首地址；申请失败返回-1。保证memSize为4字节的倍数，同一个appId可以申请多块内存。

3. void freeMemory(int appId)
释放编号为appId的应用申请过的所有的内存。没有返回值。

4. int writeData(int verify_word, int addr, string content)
需要满足以下两个条件才可以写入：
（1）addr对应的内存必须是已被某个appId申请过、且没有被free释放的内存。如果addr对应的内存没有被任意一个appId占用，写入失败，返回-1。
（2）假设addr隶属于应用appId申请的“首地址为start、长度为len”的内存，则校验码为（总之是一个公式）verify_word = (33 * (33*start + len + appId)) % 251。
    writeData的参数verify_word必须和尝试写入的地址的校验码相等才可以写入内存；如果不同，校验失败，返回0。
满足以上条件则可以成功写入：向[addr, addr+4)内存的位置写入内容content。content的长度一定为4字节，并且保证[addr, addr+4)内存一定合法。

5. string query()
输出内存被若干次操作后的内容，返回一个string类型。

样例：（试图复现当时考试时的第一个样例，内容肯定会有不一样但应该我回忆出来的差不多意思是对的；样例二有点长，和样例一相比不同点感觉只在于展示了已经被释放了的空间可以接着被分配）

函数调用列表	输出	说明
Memory("11223344556677885E5E5E5E")	null	总内存长度为12字节
appMemory(1, 4)	0	申请成功，为"11223344"这一段
appMemory(2, 4)	4	申请成功，为"55667788"这一段
appMemory(1, 8)	-1	长度不足，申请内存失败
writeData(2, 0, "AABBCCDD")	0	校验码为33*(33*0+8+1)%251=297%251=46，校验失败
writeData(46, 0, "A0B0C0D0")	1	校验码同上，校验成功，把"11223344"覆盖为"A0B0C0D0"
freeMemory(1)	null	释放[0, 4)的内存块
writeData(46, 0, "7F7F7F7F")	-1	内存块被释放了，所以写入失败返回-1
query()	"A0B0C0D0556677885E5E5E5E"

数据范围：
构造函数只在开始时调用一次，query函数只在最后调用一次，其它3个函数调用不超过100次。
初始时构造函数的string s长度不超过120,000，且只包含[0-9A-F]的16进制数（A-F为大写）。
0<=appId<10,000，0<=verify_word<=255。
 */

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Memory
{
private:
    string data;
    int len;
    vector<int> mem;
    unordered_map<int, vector<pair<int, int>>> blocks;

    int judge(int start, int memSize) const
    {
        // 首地址 + memSize 大于 分配的内存的字节数，直接返回-1
        if (start + memSize > len)
            return -1;
        // 如果当前地址已分配内存，返回首地址
        for (int i = start; i < start + memSize; ++i)
        {
            if (mem[i] != -1)
                return i;
        }
        // 如果当前地址还未分配内存，返回-2
        return -2;
    }

    // 辅助函数：填充memory数组，用appId占位
    void fillMemory(int start, int memSize, int appId)
    {
        for (int i = start; i < start + memSize; ++i)
        {
            mem[i] = appId;
        }
    }

public:
    Memory(const string &s) : data(s), len(s.size() / 2), mem(s.size() / 2, -1) {}

    int applyMemory(int appId, int memSize)
    {
        for (int i = 0; i < len; ++i)
        {
            if (mem[i] != -1)
                continue;
            int r = judge(i, memSize);
            if (r == -1)
                break;
            if (r == -2)
            {
                fillMemory(i, memSize, appId);
                blocks[appId].push_back({i, i + memSize});
                return i;
            }
            i = r;
        }
        return -1;
    }

    void freeMemory(int appId)
    {
        auto it = blocks.find(appId);
        if (it == blocks.end())
            return;
        for (auto &b : it->second)
        {
            for (int j = b.first; j < b.second; ++j)
            {
                if (mem[j] != appId)
                    break;
                mem[j] = -1;
            }
        }
    }

    int writeData(int verifyWord, int addr, const string &content)
    {
        if (addr < 0 || addr >= len)
            return -1;
        int appId = mem[addr];
        if (appId == -1)
            return -1;

        int start = 0, blockLen = 0;
        for (auto &b : blocks[appId])
        {
            if (addr >= b.first && addr < b.second)
            {
                start = b.first;
                blockLen = b.second - b.first;
                break;
            }
        }

        if ((33 * (33 * start + blockLen + appId)) % 251 != verifyWord)
            return 0;

        data.replace(addr * 2, content.size(), content);
        return 1;
    }

    string query() const
    {
        return data;
    }
};

/**
 * 题意：模拟一块字节内存，初始为十六进制串（每 2 字符 1 字节）。支持首次适配（first-fit）申请、按 appId 整体释放、带校验码的写入和最终快照查询。

实现要点：
- mem[i] 记录每字节所属 appId（-1 空闲），blocks[appId] 保存该应用所有块 [start,end)。
- applyMemory：从头扫描首个空闲位，judge 连续检查 memSize 字节，命中即填充并返回首地址，越界/无块返回 -1。
- writeData：先判 mem[addr] 是否为 -1（返回 -1），定位块后按 (33*(33*start+len+appId))%251 校验（不符返回 0），通过则替换 hex 片段并返回 1。
- freeMemory：遍历该 appId 的块将字节置 -1。

已用样例验证输出：0 8 -1 0 1 -1 A0B0C0D0556677885E5E5E5E。

注：Java 题解中样例表格的 appMemory 参数应有误记（首块实际为 8 字节才能得到校验码 46），C++ 版按题意公式实现，匹配示例结果。
 */