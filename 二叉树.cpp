#include <iostream>
#include <cstdint>   // 包含 int32_t 等标准类型
#include <queue>     // 用于层次遍历的队列
#include <vector>    // 用于存储遍历结果的动态数组

using namespace std;

#define NULLPTR nullptr  // 定义空指针常量

// 节点数据类
class data {
public:
	int32_t data1 = 0;  // 节点数据值
};


class binary_tree {
public:
	::data data;                // 节点数据
	binary_tree* left = NULLPTR;    // 左子树指针
	binary_tree* right = NULLPTR;   // 右子树指针
	binary_tree* parent = NULLPTR;  // 父节点指针
	binary_tree* clue_left = NULLPTR;  // 前驱线索指针
	binary_tree* clue_right = NULLPTR; // 后继线索指针

	// 添加子节点
	bool add(bool left_false_or_right_true, ::data add_data) {
		// 根据参数决定添加左子节点还是右子节点
		if (left_false_or_right_true == false && left == NULLPTR)
			left_add(add_data);
		else if (left_false_or_right_true == true && right == NULLPTR)
			right_add(add_data);
		else
			return false;// 添加失败（对应位置已有节点）
		return true;
	}
	void preorder_traversal(binary_tree* root) {//这个函数你就当没看到
		if (root != NULLPTR) {
			cout << root->data.data1 << endl;

			preorder_traversal(root->left);
			preorder_traversal(root->right);
		}
	}
	// 设置节点线索（前驱和后继）
	void look_clues(vector<binary_tree*>preorder_arr) {
		// 检查空数组
		if (preorder_arr.empty()	)
			return;

		// 遍历节点数组设置线索
		for (int32_t i = 0; i < preorder_arr.size(); i++){
			// 设置前驱线索
			if (i == 0)
				preorder_arr[i]->clue_left = NULLPTR;// 首节点无前驱
			else
				preorder_arr[i]->clue_left = preorder_arr[i - 1];// 前驱为前一个节点
			if (i == preorder_arr.size() - 1)
				preorder_arr[i]->clue_right = NULLPTR;// 尾节点无后继
			else
				preorder_arr[i]->clue_right = preorder_arr[i + 1];// 后继为后一个节点
		}
	}
	// 层次遍历（广度优先搜索）
	vector<const binary_tree*> hierarchical_traversal(const binary_tree *root) {
		vector<const binary_tree*> result;    // 存储结果的向量
		queue<const binary_tree*> auxiliary;  // 辅助队列

		if (root != NULLPTR)
			auxiliary.push(root);  // 根节点入队

		while (!auxiliary.empty()) {
			const binary_tree* current = auxiliary.front();  // 获取队首节点
			cout << current->data.data1 << endl;  // 输出当前节点值
			result.push_back(current);  // 将节点指针加入结果

			// 左子节点入队
			if (current->left != NULLPTR)
				auxiliary.push(current->left);
			// 右子节点入队
			if (current->right != NULLPTR)
				auxiliary.push(current->right);

			auxiliary.pop();// 处理完的节点出队
		}
		return result;// 返回遍历结果
	}
	binary_tree* left_add(::data add_data) {
		left = new binary_tree;  // 创建新节点
		left->data = add_data;   // 设置节点数据
		left->parent = this;      // 设置父节点指针
		return left;              // 返回新节点指针
	}
	binary_tree* right_add(::data add_data){
		right = new binary_tree;  // 创建新节点
		right->data = add_data;   // 设置节点数据
		right->parent = this;     // 设置父节点指针
		return right;			  // 返回新节点指针
	}
};

int32_t main() {
	binary_tree P;
	P.data.data1 = 123;
	::data A1, A2, A3, A4, A5, A6;
	A1.data1 = 10;
	P.add(true, A1);
	cout << P.right->data.data1 << endl;
	A2.data1 = 20;
	P.add(false, A2);
	cout << P.left->data.data1 << endl;
	A3.data1 = 25;
	P.left->add(true, A3);
	cout << P.left->right->data.data1 << endl;
	P.preorder_traversal(&P);
	P.hierarchical_traversal(&P);
	return 0;
}