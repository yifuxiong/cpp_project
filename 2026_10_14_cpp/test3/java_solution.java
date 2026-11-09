/**
 * 题目3：二叉树的上下遍历，兄弟节点遍历
 */

import java.util.ArrayList; 
import java.util.HashMap; 
import java.util.List; 
import java.util.Map;

class NTreeNode {
    int val;
    int statu = -1; // 3种状态：-1表示未选，0表示半选，1表示全选
    NTreeNode parent; // 父节点
    List<NTreeNode> children = new ArrayList<>(); // 子节点列表

    public NTreeNode(int val) {
        this.val = val;
    }
}

public class Solution {
    NTreeNode root;
    // 值与节点对应
    Map<Integer, NTreeNode> nodes = new HashMap<>();

    int selectNodes(int[][] dirTree, int[] operations) {
        // 初始化节点
        for (int[] pair : dirTree) {
            int parentVal = pair[0];
            int curVal = pair[1];
            NTreeNode parentNode = nodes.getOrDefault(parentVal, new NTreeNode(parentVal));
            NTreeNode curNode = nodes.getOrDefault(curVal, new NTreeNode(curVal));
            if (parentVal == -1) {
                // 当前节点就是根节点
                root = curNode;
                nodes.put(curVal, curNode);
            } else {
                parentNode.children.add(curNode);
                curNode.parent = parentNode;
                nodes.put(parentVal, parentNode);
                nodes.put(curVal, curNode);
            }
        }

        // 顺序遍历操作
        for (int oparetion : operations) {
            NTreeNode curNode = nodes.get(oparetion);
            // -1 -> 1
            // 0 -> 1
            // 1 -> -1
            int nextStatu = curNode.statu < 1 ? 1 : -1;
            downDfs(curNode, nextStatu);
            upDfs(curNode);
        }
        // 查看操作后的结果
        int count = 0; 
        for (NTreeNode nTreeNode : nodes.values()) {
            if (nTreeNode.statu == -1) {
                count++;
            }
        }
        return count;
    }

    /**
     * 向下递归
     */
    public void downDfs(NTreeNode nTreeNode, int newStatu) { 
        if (nTreeNode == null) { 
            return; 
        } 
        nTreeNode.statu = newStatu; 
        for (NTreeNode child : nTreeNode.children) { 
            // 从每个子节点向下递归
            downDfs(child, newStatu); 
        } 
    } 

    /**
     * 向上递归
     */
    public void upDfs(NTreeNode nTreeNode) {
        if (nTreeNode == null) {
            return;
        }
        boolean isSameStatu = true;
        if (nTreeNode.children.size() == 0) {
            return;
        }
        int firstChildStatu = nTreeNode.children.get(0).statu;
        for (NTreeNode child : nTreeNode.children) {
            if (child.statu != firstChildStatu) {
                isSameStatu = false;
                break; 
            }
        }
        if (isSameStatu) {
            // 所有子节点状态相同
            nTreeNode.statu = firstChildStatu; 
        } else {
            // 所有子节点存在不同的状态
            // 如果第一个子节点的state == -1，表示存在兄弟节点state是0或者1，那这一层state是0，表示半选
            // 如果第一个子节点的state == 0，表示存在兄弟节点state是-1或者1，那这一层state是0，表示半选
            // 如果第一个子节点的state == 1，表示存在兄弟节点state是-1或者0，那这一层state是0，表示半选
            nTreeNode.statu = 0;
        }
        // 继续向上递归
        upDfs(nTreeNode.parent);
    } 

    public static void main(String[] args) {
        int[][] dirTree = {
            {-1, 0}, 
            {0, 6}, 
            {0, 2}, 
            {1, 4}, 
            {2, 1}, 
            {2, 3}, 
            {4, 5}
        };
        int[] operations = {1, 6, 2, 4}; // 3

        int[][] dirTree2 = {
            {-1, 10}, 
            {10, 1}, 
            {10, 2}, 
            {1, 4}, 
            {10, 3}, 
            {1, 5}, 
            {4, 6}, 
            {4, 7}
        };
        int[] operations2 = {4, 4, 1, 6}; // 3

        Solution solut = new Solution();
        System.out.println(solut.selectNodes(dirTree2, operations2));
    }
}
