#include <iostream>
#include <cstdint>   // ���� int32_t �ȱ�׼����
#include <queue>     // ���ڲ�α����Ķ���
#include <vector>    // ���ڴ洢��������Ķ�̬����

using namespace std;

#define NULLPTR nullptr  // �����ָ�볣��

// �ڵ�������
class data {
public:
	int32_t data1 = 0;  // �ڵ�����ֵ
};


class binary_tree {
public:
	::data data;                // �ڵ�����
	binary_tree* left = NULLPTR;    // ������ָ��
	binary_tree* right = NULLPTR;   // ������ָ��
	binary_tree* parent = NULLPTR;  // ���ڵ�ָ��
	binary_tree* clue_left = NULLPTR;  // ǰ������ָ��
	binary_tree* clue_right = NULLPTR; // �������ָ��

	// ����ӽڵ�
	bool add(bool left_false_or_right_true, ::data add_data) {
		// ���ݲ�������������ӽڵ㻹�����ӽڵ�
		if (left_false_or_right_true == false && left == NULLPTR)
			left_add(add_data);
		else if (left_false_or_right_true == true && right == NULLPTR)
			right_add(add_data);
		else
			return false;// ���ʧ�ܣ���Ӧλ�����нڵ㣩
		return true;
	}
	void preorder_traversal(binary_tree* root) {//���������͵�û����
		if (root != NULLPTR) {
			cout << root->data.data1 << endl;

			preorder_traversal(root->left);
			preorder_traversal(root->right);
		}
	}
	// ���ýڵ�������ǰ���ͺ�̣�
	void look_clues(vector<binary_tree*>preorder_arr) {
		// ��������
		if (preorder_arr.empty()	)
			return;

		// �����ڵ�������������
		for (int32_t i = 0; i < preorder_arr.size(); i++){
			// ����ǰ������
			if (i == 0)
				preorder_arr[i]->clue_left = NULLPTR;// �׽ڵ���ǰ��
			else
				preorder_arr[i]->clue_left = preorder_arr[i - 1];// ǰ��Ϊǰһ���ڵ�
			if (i == preorder_arr.size() - 1)
				preorder_arr[i]->clue_right = NULLPTR;// β�ڵ��޺��
			else
				preorder_arr[i]->clue_right = preorder_arr[i + 1];// ���Ϊ��һ���ڵ�
		}
	}
	// ��α������������������
	vector<const binary_tree*> hierarchical_traversal(const binary_tree *root) {
		vector<const binary_tree*> result;    // �洢���������
		queue<const binary_tree*> auxiliary;  // ��������

		if (root != NULLPTR)
			auxiliary.push(root);  // ���ڵ����

		while (!auxiliary.empty()) {
			const binary_tree* current = auxiliary.front();  // ��ȡ���׽ڵ�
			cout << current->data.data1 << endl;  // �����ǰ�ڵ�ֵ
			result.push_back(current);  // ���ڵ�ָ�������

			// ���ӽڵ����
			if (current->left != NULLPTR)
				auxiliary.push(current->left);
			// ���ӽڵ����
			if (current->right != NULLPTR)
				auxiliary.push(current->right);

			auxiliary.pop();// ������Ľڵ����
		}
		return result;// ���ر������
	}
	binary_tree* left_add(::data add_data) {
		left = new binary_tree;  // �����½ڵ�
		left->data = add_data;   // ���ýڵ�����
		left->parent = this;      // ���ø��ڵ�ָ��
		return left;              // �����½ڵ�ָ��
	}
	binary_tree* right_add(::data add_data){
		right = new binary_tree;  // �����½ڵ�
		right->data = add_data;   // ���ýڵ�����
		right->parent = this;     // ���ø��ڵ�ָ��
		return right;			  // �����½ڵ�ָ��
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