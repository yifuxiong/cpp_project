/**
 * t2.内存地址校验
某系统在用户申请内存时，会生成校验字，后续对每个地址写操作前会进行一致性校验。请实现如下内存管理的接口:

接口定义
1.MemorySys(string data)初始化一段长度为 data.length/2 字节、首地址为 0 的内存供用户使用，初始内容为 data，用 16 进制字符串表示，每两个字符表示 1 个字节。

2.applyMem(int appld, int memSize)应用 appId 申请大小为 memSize 字节的内存，成功则返回申请到的内存块的首地址，否则返回-1。

内存分配策略：从低地址往高地址搜索第一个满足大小的连续空闲内存空间

注意：用例保证 memSize 是4的整数倍；同一个 appld 可多次申请内存

3.freeMem(int appld)释放应用 appId 所申请的所有内存。输入保证：appld已成功分配。

4. writeData(int verifyWord, int addr, string content)写内存。

若内存未分配，则不做处理，返回-1;

若内存已分配:
a.根据 addr 获取其所在被分配内存块的首地址、长度和 appld，计算校验字:
校验字 =（33 *（33 * 内存块首地址 + 内存块长度 + appld)) % 251

b.若校验字和 verifyWord 相同，则将 content 从地址 addr 写入内存，并返回 1；否则，不做处理并返 content 是待写入的内容（用 16 进制字符串表示），
content长度 == 8，表示 4 个字节的内容

5.query()查询完整的内存数据，返回内存完整十六进制字符串。

注意：applyMem 和 freeMem 时仅改变内存的占用状态；仅 writeData 会改变内存内容

输入：
每行表示一个函数调用，初始化函数仅首行调用一次，累计函数调用不超过 100 次。query()函数只会在最后一次调用。

约束:
16 <= data.length（偶数）<= 120000，字符为[0-9A-F]，字母大写
0 < appld < 10000；4 <= memSize <= 128，且申请的长度不会超过内存长度
0 <= verifyWord <= 255，addr 在内存有效范围内，用例保证 addr 按 4字节对齐，且 addr + 4 字节不会超过data边界
content 格式同 data, content.length == 8，表示4个字节的内容

输出：
答题时按照函数/方法原型中的要求（含返回值）进行实现，输出由框架完成（其中首行固定输出null)

==========

样例1
输入:
MemorySys("A1B2C3D47D7D7D7D5E5E5E5E"
applyMem(1,8)
writeData(46,4,"11223344")
writeData(160,0,"FF0000FF")
freeMem(1)
writeData(46,4,"7B00007B")

输出:

=====

 */


/**
分析：

本题用字节级占用数组 memory[]（每字节存所属 appId，-1 表示空闲）做 first-fit 分配：
1、applyMem 从低地址扫描首个空闲位并 judge 校验连续 memSize 全空闲后落块，map 记录每个 appId 的全部块 [start,end) 以支持多次申请；
2、writeData 先查 memory[addr] 未分配返回 -1，再定位 addr 所在块首地址与长度，
按公式 (33 * (33 * start + memSize + appId)) % 251 校验字一致才用 substring 替换 data 中对应 hex 片段，否则返回 0。

整体正确性成立：分配策略、校验字公式、addr 4 字节对齐块内写入、free 后字节置 -1、对已释放地址写返回 -1 均与题意一致；

可优化点：freeMem 后未从 map 移除 appId（address 列表残留已释放块记录，
因 writeData 先判 memory[addr] 不影响正确性）、占用数组开到 1280000 偏大可按 len 缩、judge/fillMem 命名语义化不足。
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

class MemorySys {
    String data;
    int[] memory = new int[1280000];
    // 当前分配的内存的字节数（即length/2)
    int len = 0;
    // <k, v> -> <appId, 内存>
    HashMap<Integer, Memory> map = new HashMap<>();

    MemorySys(String data) {
        this.data = data;
        len = data.length() / 2;
        // 初始化用-1占位
        fillMem(0, len, -1);
    }

    int judge(int start, int memSize) {
        // 首地址 + memSize 大于 分配的内存的字节数，直接返回-1
        if (start + memSize > len) {
            return -1;
        }
        // 如果当前地址已分配内存，返回首地址
        for (int i = start; i < start + memSize; i++) {
            if (memory[i] != -1)
                return i;
        }
        // 如果当前地址还未分配内存，返回-2
        return -2;
    }

    // 辅助函数：填充memory数组，用appId占位
    void fillMem(int start, int memSize, int appId) {
        for (int i = start; i < start + memSize; i++) {
            memory[i] = appId;
        }
    }

    int applyMem(int appId, int memSize) {
        for (int i = 0; i < len; i++) {
            // 从左到右找第一个还未被分配内存的首地址
            if (memory[i] == -1) {
                int n = judge(i, memSize);
                if (n == -1)
                    break;
                if (n == -2) {
                    fillMem(i, memSize, appId);
                    if (map.containsKey(appId)) {
                        // 如果已经存在这个内存地址
                        Memory m = map.get(appId);
                        int[] addr = new int[2];
                        addr[0] = i;
                        addr[1] = i + memSize;
                        m.address.add(addr);
                    } else {
                        // 否则新增一个内存地址
                        Memory m = new Memory(appId, i, i + memSize);
                        map.put(appId, m);
                    }
                    // 返回当前首地址
                    return i;
                } else {
                    // 快速跳到下一个已分配内存的首地址
                    i = n;
                }
            }
        }
        return -1;
    }

    void freeMem(int appId) {
        Memory m = map.get(appId);
        for (int[] addr : m.address) {
            for (int j = addr[0]; j < addr[1]; j++) {
                if (memory[j] != appId)
                    break;
                memory[j] = -1;
            }
        }
    }

    int writeData(int verifyWord, int addr, String content) {
        int appId = memory[addr];
        if (appId == -1)
            return -1;
        Memory m = map.get(appId);
        int start = 0;
        int memsize = 0;
        for (int[] add : m.address) {
            if (addr >= add[0] && addr < add[1]) {
                start = add[0];
                memsize = add[1] - add[0];
                break;
            }
        }
        // 校验公式，校验失败
        if ((33 * (33 * start + memsize + appId)) % 251 != verifyWord)
            return 0;
        // 前面部分字符串保留
        String front = data.substring(0, addr * 2);
        // 后面部分字符串保留
        String last = data.substring(addr * 2 + content.length());
        // 只把中间部分字符串替换
        data = front + content + last;

        return 1;
    }

    String query() {
        return data;
    }
}

class Memory {
    int appId;
    List<int[]> address;

    Memory() {}
    
    Memory(int appId, int start, int end) {
        this.appId = appId;

        int[] addr = new int[2];
        addr[0] = start;
        addr[1] = end;

        List<int[]> addrs = new ArrayList<>();
        addrs.add(addr);
        this.address = addrs;
    }
}