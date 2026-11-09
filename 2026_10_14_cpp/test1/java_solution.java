/**
 * 面对面建群
 * 
面对面建群是聊天软件中一个常用功能，假设一个群的覆盖范围是以创建者所在位置为中心的九宫格。

给出一批人员的信息 members，members[i] = [标识码 flag，行位置 row，列位置 col] 分别表示一个人的标识码（例如某种爱好）、所在行、所在列。

依次处理members中每个人，进行建群或加入群，规则如下:
- 如果这个人没有被已存在的具有相同标识码的群覆盖，则新建群并加入；
- 否则，这个人加入到具有相同标识码的群中，若有多个则加入到最早建立的。

输入
参数members

1 <= members.length <= 100
0 < flag <= 1000, 0 = col < 10,
members[i] = [标识码 flag, 行位置 row，列位置 col]
0 <= row < 100

输出
一个数组，依次为从大到小的所有群的成员数量
 */

/**
 * 分析
- 本题按 flag 分组后，对每个成员遍历同 flag 的已有群，用 |row-g.row| <= 1 && |col-g.col| <= 1 判断九宫格覆盖；
- groups 按创建顺序存放，遍历命中的第一个即最早建立的群，满足"多个群则加入最早"的题意，未命中则新建群并计数为 1；
- 最后将所有群成员数降序输出。

核心正确性在于九宫格判定与"最早群"的顺序保证，代码整体通过；
仅命名上 Group.number 实为群序号（创建顺序 now），与成员数计数器 List<integer> number 重名易混淆，建议改名为 idx，且用按群序号索引的 List 累加不如在 Group 内加 size 字段直观。
 */

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;

class Solution {
    boolean judgeIn(List<Group> groups, int col, int row, List<Integer> number) {
        for (Group group : groups) {
            if (Math.abs(col - group.col) <= 1 && Math.abs(row - group.row) <= 1) {
                // 新增成员，成员数+1
                number.set(group.number, number.get(group.number) + 1);
                return true;
            }
        }
        // 否则返回false
        return false;
    }

    int[] resolve(List<UserInfo> members) {
        HashMap<Integer, List<Group>> hashMap = new HashMap<>();
        List<Integer> number = new ArrayList<>();
        int now = 0;
        for (UserInfo member : members) {
            int flag = member.flag;
            int col = member.col;
            int row = member.row;
            if (hashMap.containsKey(flag)) {
                List<Group> groups = hashMap.get(flag);
                if (judgeIn(groups, col, row, number) == false) {
                    // 如果无法覆盖这个成员，那就新建一个群，新成员加入这个新群
                    groups.add(new Group(flag, row, col, now));
                    number.add(1);
                    now++;
                }
            } else {
                // 直接创建新群
                List<Group> groups = new ArrayList<>();
                groups.add(new Group(flag, row, col, now));
                number.add(1);
                now++;
                hashMap.put(flag, groups);
            }
        }
        number.sort(Collections.reverseOrder());
        int[] res = new int[number.size()];
        for (int i = 0; i < number.size(); i++) {
            res[i] = number.get(i);
        }
        return res;
    }
}

class UserInfo {
    // 群标识码：表示这个人的爱好
    int flag;
    // 这个人的所在位置：行
    int row;
    // 这个人的所在位置：列
    int col;

    UserInfo() {}

    /**
     * toString
     *
     * @return String
     */
    public String toString() {
        return String.format(java.util.Locale.ROOT, "[%d, %d, %d]", flag, row, col);
    }
}

class Group {
    // 群标识码：表示这个群中成员的爱好
    int flag;
    // 这个群中心点的位置：行
    int row;
    // 这个群中心点的位置：列
    int col;
    // 成员数
    int number;

    Group() {}

    Group(int flag, int row, int col, int number) {
        this.flag = flag;
        this.col = col;
        this.row = row;
        this.number = number;
    }
}
