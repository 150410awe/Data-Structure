#include <iostream>
#include <cstdint>
#include <queue>
#include <vector> 

using namespace std;

#define NULLPTR nullptr
#define MAX_TREE_SIZE 100
#define EMPTY -1


class parents_represent_law_data {
public:
	int32_t data = EMPTY;		// �ڵ�����
	int32_t parent = EMPTY;		// ���ڵ�ָ��
};

class tree_parents_represent_law {
public:
	double multiple_expansion = 1.5;		// ����ϵ��
	int32_t volume = 5;						// ��ʼ����
	int32_t vacancy_volume = volume / 2;	// ��λ��������
	int32_t vacancy_size = 0;				// ��ǰ��λ����
	int32_t* vacancy = new int32_t[vacancy_volume];// �洢��ɾ���ڵ��λ��
	parents_represent_law_data* tree = new parents_represent_law_data[volume];// �����ṹ����
	int32_t size = 0;						// ��ǰ���нڵ�����
	const int32_t root = 0;					// ���ڵ�̶�Ϊ0����



	// ���캯��
	tree_parents_represent_law(){
		tree[root].data = 0;	// ���ڵ��ʼ��
		tree[root].parent = -1;// ���ڵ�û�и��ڵ�
		size++;

		// ��ʼ����λ����
		for (int i = 0; i < vacancy_volume; i++)
			vacancy[i] = EMPTY;
	}



	// ��������
	~tree_parents_represent_law() {
		delete[] tree;
		delete[] vacancy;
		cout << "��������,tree,vacancy���ͷ�" << endl;
		
		// �������ÿ�
		vacancy = NULLPTR;
		tree = NULLPTR;  
	}


	// ���һ���½ڵ�
	bool add(int32_t data,int32_t parent) {
		if (!parent_existence(parent)) {
			cout << "������Ч���ڵ�" << endl;
			return false;
		}

		cout << "add,parent_existence�ɹ�,����parent" << endl;

		if (size >= volume) {

			cout << "volume <= size,�ռ䲻��" << endl;

			expansion();// ����

			cout << "expansion���ݳɹ�,new_volume:" << volume << endl;
		}

		// ����ʹ��vacancy��λ���
		cout << "volume�ռ�����,�������" << endl;
		if (vacancy_size > 0) {
			cout << "vacancy�пռ�,��vacancy��,���" << endl;
			tree[vacancy_size - 1].data = data;
			tree[vacancy_size - 1].parent = parent;
			vacancy_size--;
			cout << "add�ɹ�" << "data��" << tree[vacancy_size - 1].data << " parent��" << tree[vacancy_size - 1].parent << endl;
			return true;
		}

		// û�п�λ��ֱ����β�����
		tree[size].data = data;
		tree[size].parent = parent;

		cout << "add�ɹ�" << "data��" << tree[size].data << " parent��" << tree[size].parent << endl;

		size++;

		cout << "size:" << size << endl;

		return true;
	}



	// ɾ��ָ�������Ľڵ㣨�������������
	bool expurgate(int32_t index) {
		if (size <= index || index <= root || tree[index].data == EMPTY) {
			cout << "size < index || index <= root || tree[index].data == EMPTY" << endl;
			return false;
		}

		expurgate_descendants(index);// ɾ�������ӽڵ�


		// ��λ��������������
		if (vacancy_size >= vacancy_volume)
			vacancy_expansion();

		vacancy[vacancy_size] = index;
		vacancy_size++;
		tree[index].data = EMPTY;
		tree[index].parent = EMPTY;



		cout << "expurgate�ɹ�" << endl;
		cout << "vacancy[" << vacancy_size << "]" << endl;
		return true;
	}


	// �ݹ�ɾ�������ӽڵ�
	void expurgate_descendants(int32_t parent) {
		for (int32_t i = 0; i < size; i++) {
			if ((tree[i].parent == parent) && (tree[i].data != EMPTY)) {
				cout << i << endl;	// �ݹ�ɾ��
				expurgate_descendants(i);
				if (vacancy_size >= vacancy_volume) 
					vacancy_expansion();
				

				vacancy[vacancy_size] = i;
				vacancy_size++;

				tree[i].data = EMPTY;
				tree[i].parent = EMPTY;

				cout << "ɾ���ӽڵ�: " << i << endl;
			}
		}
	}

	// �жϸ��ڵ��Ƿ����
	bool parent_existence(int32_t parent) {
		if (parent < size && parent >= 0 && tree[parent].data != EMPTY)
				return true;
		return false;
	}


	// ������������
	void expansion() {
		int32_t new_volume = volume * multiple_expansion;
		parents_represent_law_data* new_tree = new parents_represent_law_data[new_volume];
		
		for (int32_t i = 0; i < new_volume; i++) {
			new_tree[i].data = EMPTY;
			new_tree[i].parent = EMPTY;
		}
		for (int32_t i = 0; i < volume; i++) {
			new_tree[i].data = tree[i].data;
			new_tree[i].parent = tree[i].parent;
		}

		delete[] tree;
		tree = new_tree;
		volume = new_volume;
		cout << "�������,new_volume:" << volume << endl;
	}


	// ���ݿ�λ����
	void vacancy_expansion() {
		int32_t new_vacancy_volume = vacancy_volume * multiple_expansion + 1;
		int32_t* new_vacancy = new int32_t[new_vacancy_volume];
		for (int32_t i = 0; i < vacancy_size; i++) 
			new_vacancy[i] = vacancy[i];
		
		delete[] vacancy;
		vacancy = new_vacancy;
		vacancy_volume = new_vacancy_volume;
		cout << "�������,new_vacancy_volume:" << vacancy_volume << endl;
	}


	// ������ṹ
	void cout_tree() {
		for (int32_t i = 0; i < size; i++) 
			cout << i << "\t" << "data:" << tree[i].data << "\t" << "parent:" << tree[i].parent << endl;
	}


	// ���Ҹ��ڵ㣨�˺���Ŀǰ�̶����� root��
	parents_represent_law_data* find_root(int32_t data) {
		return      &tree[root];
	}


	// �ϲ���һ������tree������ǰ����
	bool tree_and(tree_parents_represent_law& tree) {
		if (this == &tree)
			return true;

		const int32_t new_arr_size = this->size + tree.size;
		const int32_t new_vacancy_size = this->vacancy_size + tree.vacancy_size;

		if (this->size >= tree.size) {	
			// �����������㹻

			if (this->volume >= new_arr_size) {
				this->tree[this->size].data = tree.tree[tree.root].data;
				this->tree[this->size].parent = 0;

				for (int32_t i = 1; i < tree.size; i++) {
					this->tree[this->size + i] = tree.tree[i];
					this->tree[this->size + i].parent += this->size;
				}
			}
			else {
				// �����鲻��������
				const int32_t new_volume = new_arr_size * multiple_expansion;
				parents_represent_law_data* new_tree = new parents_represent_law_data[new_volume];

				for (int32_t i = 0; i < this->size; i++) 
					new_tree[i] = this->tree[i];


				new_tree[this->size].data = tree.tree[tree.root].data;
				new_tree[this->size].parent = 0;

				for (int32_t i = 1; i < tree.size; i++) {
					new_tree[this->size + i] = tree.tree[i];
					new_tree[this->size + i].parent += this->size;
				}

				delete[] this->tree;
				this->tree = new_tree;
				this->volume = new_volume;

			}
			// ��λ����ϲ�
			if (this->vacancy_volume >= new_vacancy_size) {

				for (int32_t i = 0; i < tree.vacancy_size; i++)
					this->vacancy[i + this->vacancy_size] = tree.vacancy[i] + this->size;

			}
			else {

				const int32_t new_volume = new_vacancy_size * multiple_expansion;
				int32_t* new_vacancy = new int32_t[new_volume];
				
				for (int32_t i = 0; i < this->vacancy_size; i++)
					new_vacancy[i] = this->vacancy[i];
				
				for (int32_t i = 0; i < tree.vacancy_size; i++)
					new_vacancy[i + this->vacancy_size] = tree.vacancy[i] + this->size;

				delete[] this->vacancy;
				this->vacancy = new_vacancy;
				this->vacancy_volume = new_volume;
			}
			// ��վ���
			tree.size = 0;
			tree.vacancy_size = 0;
			tree.volume = 0;
			tree.vacancy_volume = 0;
			delete[] tree.tree;
			delete[] tree.vacancy;
			tree.tree = NULLPTR;
			tree.vacancy = NULLPTR;	
		}
		else {
			// ��ǰ����С���������ϲ�
			// �������߼����ƣ�����Ͳ��ظ�дע����
			if (tree.volume >= new_arr_size) {

				tree.tree[tree.size].data = this->tree[this->root].data;
				tree.tree[tree.size].parent = 0;

				for (int32_t i = 1; i < this->size; i++) {
					tree.tree[tree.size + i] = this->tree[i];
					tree.tree[tree.size + i].parent += tree.size;
				}
			}
			else {
				const int32_t new_volume = new_arr_size * multiple_expansion;
				parents_represent_law_data* new_tree = new parents_represent_law_data[new_volume];

				for (int32_t i = 0; i < tree.size; i++) 
					new_tree[i] = tree.tree[i];

				new_tree[tree.size].data = this->tree[this->root].data;
				new_tree[tree.size].parent = 0;

				for (int32_t i = 1; i < this->size; i++) {
					new_tree[tree.size + i] = this->tree[i];
					new_tree[tree.size + i].parent += tree.size;
				}

				delete[] tree.tree;
				tree.tree = new_tree;
				tree.volume = new_volume;
			}
			if (tree.vacancy_volume >= new_vacancy_size) {
				for (int32_t i = 0; i < this->vacancy_size; i++)
					tree.vacancy[i + tree.vacancy_size] = this->vacancy[i] + tree.size;
			}
			else {
				const int32_t new_volume = new_vacancy_size * multiple_expansion;
				int32_t* new_vacancy = new int32_t[new_volume];

				for (int32_t i = 0; i < tree.vacancy_size; i++)
					new_vacancy[i] = tree.vacancy[i];

				for (int32_t i = 0; i < this->vacancy_size; i++)
					new_vacancy[i + tree.vacancy_size] = this->vacancy[i] + tree.size;

				delete[] tree.vacancy;
				tree.vacancy = new_vacancy;
				tree.vacancy_volume = new_volume;
			}

			this->size = 0;
			this->vacancy_size = 0;
			this->volume = 0;
			this->vacancy_volume = 0;
			delete[] this->tree;
			delete[] this->vacancy;
			this->tree = NULLPTR;
			this->vacancy = NULLPTR;
		}
		this->size = new_arr_size;
		this->vacancy_size = new_vacancy_size;
		return true;
	}
};

class child_notation_node {
public:
	int32_t location = EMPTY;
	int32_t data = 0;
	child_notation_node* next = NULLPTR;
};

class tree_child_notation {
public:
	child_notation_node tree[MAX_TREE_SIZE];
	int32_t size = 0;
	int32_t root_location = 0;
	tree_child_notation() {
		tree[root_location].location = 0;
		tree[root_location].data = 0;
		size = 1;
	}
	bool add(int32_t location, int32_t data) {
		if (location >= size || location < 0)
			return false;
		if (size >= MAX_TREE_SIZE)
			return false;
		child_notation_node* parent = &tree[location];
		if (parent->next == NULLPTR) 
			parent->next = &tree[size];
		else {
			child_notation_node* current = parent->next;
			while (current->next != NULLPTR)
				current = current->next;
			current->next = &tree[size];
		}
		tree[size].data = data;
		tree[size].location = size;
		size++;
		return true;
	}
};

class tree_child_brother_notation {
public:
	int32_t data = 0;
	int32_t size = 0;
	tree_child_brother_notation* firstchild = NULLPTR;
	tree_child_brother_notation* right = NULLPTR;
	bool add_root(int32_t data) {
		if (size != 0)
			return false;
		this->data = data;
		size = 1;
		return true;
	}
	bool add(tree_child_brother_notation* add_location,int32_t data) {
		if (size == 0) {
			if (add_location == this)
				return add_root(data);
			return false;
		}
		if (querying(add_location) == EMPTY)
			return false;
		tree_child_brother_notation* new_node = new tree_child_brother_notation;
		new_node->data = data;
		if (add_location->firstchild == NULLPTR) 
			add_location->firstchild = new_node;
		else {
			tree_child_brother_notation* objects = add_location->firstchild;
			while (objects->right != NULLPTR)
				objects = objects->right;
			objects->right = new_node;
		}
		size++;
		return true;
	}
	int32_t querying(tree_child_brother_notation* objects) {
		if (objects == NULLPTR)
			return EMPTY;
		const tree_child_brother_notation* traversal = this;
		queue<const tree_child_brother_notation*> buffer;
		for (int32_t i = 0; i < size; i++) {
			if (traversal == objects)
				return traversal->data;
			if (traversal->firstchild != NULLPTR)
				buffer.push(traversal->firstchild);
			if (traversal->right != NULLPTR) 
				traversal = traversal->right;
			else {
				if (!buffer.empty()){
					traversal = buffer.front();
					buffer.pop();
				}
			}
		}
		return EMPTY;
	}
};


int32_t main() {
	tree_parents_represent_law A;
	cout << A.tree[A.root].data << " " << A.tree[A.root].parent << endl;
	A.add(10, 0);
	A.add(20, 1);
	A.add(30, 0);
	A.add(40, 2);
	A.add(50, 4);
	A.cout_tree();
	A.expurgate(2);
	A.expurgate(3);
	A.expurgate(4);
	cout << A.vacancy[0] << endl;
	cout << A.vacancy[1] << endl;
	A.add(10,2);
	cout << A.vacancy[A.vacancy_size] << endl;
	cout << A.vacancy[A.vacancy_size - 1] << endl;
	A.add(10, 1);
	A.cout_tree();
	A.expurgate(0);
	return 0;
}