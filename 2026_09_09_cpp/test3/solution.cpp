#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

/**
 * 题目三：简易指令集虚拟机
题目背景
请你模拟一台简化的小型虚拟机（CPU）。该机器配置如下：
32 个通用寄存器，每个寄存器宽 8 字节，初始值全部为 0；
内存区域，用一个十六进制字符串 data 表示，每 2 个字符代表 1 字节；
指令序列 instructions，每条指令是一个字符串，包含8字符，格式为：
第 1~8个字节：操作码（十六进制）；
第 9~16 个字节：寄存器编号（十六进制）；
第 17~22个字节：保留位
第 23~32 个字节起：参数
虚拟机从第 0 条指令开始顺序执行，程序结束后返回数据区的最终内容。
接口定义
string ExecInstruction(const vector<string>& instructions, const string& data);

指令序列 instructions，每条指令是一个字符串，包含8字符
data为内存区域的输出值，内存区域的大小由data的大小确认

| 操作码 | 含义 | 语义 |
|--|--|--|
| 03 | LOAD（读数据区 → 寄存器） | 将内存区域中字节偏移 para 处开始的 8 字节装入寄存器 rigid
| 08 | STORE（写寄存器 → 数据区） | 将寄存器 rigid 中的 8 字节写入内存区域字节偏移 para 处
| 22 | CALL（函数调用） | 将当前全部 R1~R32寄存器的当前值(不保存R0)和下一条指令的执行地址压入调用栈，然后跳转到第 para 条指令执行
| 30 | RET（函数返回） | 若调用栈为空，整个程序结束；否则弹出栈顶，恢复寄存器R1~R32寄存器的值，跳回保存的返回地址继续执行
 */

class Solution
{
public:
    struct CallStore
    {
        vector<string> rigister;
        int nextInsIdx;
    };

    stack<CallStore> stk;
    vector<string> curRigister;

    void init_register()
    {
        // 16位
        this->curRigister = vector<string>(32, "0000000000000000");
    }

    string ExecInstruction(const vector<string> &instructions, const string &data)
    {
        init_register();
        string myData = data;
        for (int i = 0; i < instructions.size();)
        {
            string opCode = instructions[i].substr(0, 2);
            int rigid = stoi(instructions[i].substr(2, 2), nullptr, 16);
            int tempPara = stoi(instructions[i].substr(5), nullptr, 16);
            int para = tempPara & 0x3FF;
            if (opCode == "03")
            {
                curRigister[rigid] = myData.substr(para * 2, 16);
                i++;
                continue;
            }
            if (opCode == "08")
            {
                int curIdx = 0;
                for (int j = para * 2; j < para * 2 + 16; j++)
                {
                    myData[j] = curRigister[rigid][curIdx];
                    curIdx++;
                }
                i++;
                continue;
            }
            if (opCode == "22")
            {
                CallStore tempCallStore{curRigister, i + 1};
                stk.push(tempCallStore);
                i = para;
                continue;
            }
            if (stk.empty())
            {
                break;
            }
            auto [prevRigister, nextIdx] = stk.top();
            stk.pop();
            for (int j = 1; j < 32; j++)
            {
                curRigister[j] = prevRigister[j];
            }
            i = nextIdx;
            continue;
        }
        return myData;
    }
};