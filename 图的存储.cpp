#include <iostream>
#include <cstdint>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>


using namespace std;

#define NULLPTR nullptr		//===nullptr
#define EMPTY -1			//空NULL

class data {
public:
	int32_t data1 = EMPTY;		//数据
	int32_t location = EMPTY;	//图的位置
	bool access_tag = false;
};

//adjacency_matrix_method_undirected_graph
class picture1 {
public:
	int32_t volume = 5;
	int32_t size = 0;
	int32_t border = 0;
	int32_t vacancy_volume = volume / 2 + 1;	// 空位数组容量
	int32_t vacancy_size = 0;				// 当前空位数量
	double multiple_expansion = 1.5;

	::data* data = new ::data[volume];
	bool** location = new bool* [volume];		// 1. 分配行指针数组
	int32_t* vacancy = new int32_t[vacancy_volume];// 存储被删除节点的位置
	picture1() {
		//为每一行分配列空间
		for (int32_t i = 0; i < volume; i++) {
			location[i] = new bool[volume];
			data[i].location = i;
		}
		for (int32_t i = 0; i < volume; i++)
			for (int32_t j = 0; j < volume; j++)
				location[i][j] = false;

		for (int32_t i = 0; i < vacancy_volume; i++)
			vacancy[i] = EMPTY;
	}
	~picture1() {
		// 4. 释放内存（先释放每一行，再释放行指针数组）
		for (int32_t i = 0; i < volume; i++)
			delete[] location[i];
		delete[] location;			// 释放行指针数组
		delete[] data;
		delete[] vacancy;
	}
	bool add(int32_t data) {

		if (vacancy_size > 0) {
			cout << "vacancy有空间,优先使用vacancy空位添加" << endl;
			this->data[vacancy[--vacancy_size]].data1 = data;
			//this->data[vacancy_size - 1].location = vacancy[vacancy_size - 1];

			vacancy[vacancy_size] = EMPTY;
			return true;
		}

		if (size >= volume) {
			cout << "size空间不足,扩容" << endl;
			expansion();//vacancy添加
			cout << "扩容完成" << endl;
		}

		this->data[size].data1 = data;
		this->data[size].location = size;
		size++;
		return true;
	}
	void expansion() {
		//if (size < volume) {
		//	cout << "volume有空间,不用扩容" << endl;
		//	return;
		//}
		int32_t new_volume = volume * multiple_expansion + 1;
		bool** new_location = new bool* [new_volume];		// 1. 分配行指针数组
		::data* new_data = new ::data[new_volume];
		for (int32_t i = 0; i < new_volume; i++) {
			new_location[i] = new bool[new_volume];
			for (int32_t j = 0; j < new_volume; j++)
				new_location[i][j] = false;
		}

		for (int32_t i = 0; i < volume; i++) {
			for (int32_t j = 0; j < volume; j++)
				new_location[i][j] = location[i][j];
			new_data[i] = data[i];
		}

		// 初始化新空间
		//初始化
		for (int32_t i = volume; i < new_volume; i++) {
			new_data[i].data1 = EMPTY;
			new_data[i].location = i;
			for (int32_t j = 0; j < volume; j++)
				new_location[j][i] = false;
			for (int32_t j = 0; j < new_volume; j++)
				new_location[i][j] = false;
		}

		for (int32_t i = 0; i < volume; i++)
			delete[] location[i];
		delete[] location;

		delete[] data;

		data = new_data;
		location = new_location;
		volume = new_volume;
	}
	void expansion_volume() {
		int32_t new_vacancy_volume = vacancy_volume * multiple_expansion + 1;
		int32_t* new_vacancy = new int32_t[new_vacancy_volume];
		for (int32_t i = 0; i < vacancy_size; i++)
			new_vacancy[i] = vacancy[i];
		//初始化
		for (int32_t i = vacancy_size; i < new_vacancy_volume; i++)
			new_vacancy[i] = EMPTY;

		delete[] vacancy;
		vacancy = new_vacancy;
		vacancy_volume = new_vacancy_volume;
		cout << "扩容完成,new_vacancy_volume:" << vacancy_volume << endl;
	}
	bool remove(int32_t location) {
		if (0 > location || location >= size) {
			cout << "location越界力" << endl;
			return false;
		}

		if (data[location].data1 == EMPTY) {
			cerr << "节点不存在" << endl;
			return false;
		}

		if (vacancy_size >= vacancy_volume) {
			cout << "vacancy_volume空间不足,扩容" << endl;
			expansion_volume();
		}

		vacancy[vacancy_size] = location;
		vacancy_size++;

		for (int32_t i = 0; i < size; i++) {
			this->location[i][location] = false;
			this->location[location][i] = false;
		}
		data[location].data1 = EMPTY;
		//data[location].location = EMPTY;
		return true;
	}
	::data* search(int32_t location) {
		return &data[location];
	}
	bool connection_determination(int32_t location1, int32_t location2) {
		if (0 > location1 || location1 >= size || 0 > location2 || location2 >= size) // 使用 size 检查位置
			return false;
		if (location[location1][location2] == true)
			return true;
		if (location[location2][location1] == true)
			return true;
		return false;
	}
	void neighbor(int32_t node, vector<int32_t>& node_arr) {
		if (0 > node || node >= size) {
			cout << "node越界力" << endl;
			return;
		}
		for (int32_t i = 0; i < size; i++) {
			if (location[i][node] == true)
				node_arr.push_back(i);
			/*
			if (this->location[location][i] == true) {

			}*/
		}
	}
	bool add_border(int32_t node1, int32_t node2) {
		if (node1 > size || node1 < 0 || node2 > size || node2 < 0 || data[node1].data1 == EMPTY || data[node2].data1 == EMPTY)
			return false;
		location[node1][node2] = true;
		location[node2][node1] = true;
		return true;
	}
	bool vacancy_find(int32_t delete_index) {
		if (delete_index > size || delete_index < 0)
			return false;
		for (int32_t i = 0; i < vacancy_size; i++)
			if (vacancy[i] == delete_index)
				return true;
		return false;
	}
	void BFS_traverse() {
		for (int32_t i = 0; i < size; i++)
			if (data[i].access_tag == false && !vacancy_find(i))
				BFS(i);


		for (int32_t i = 0; i < size; i++)
			data[i].access_tag = false;
	}
	void BFS(int32_t head) {
		queue<int32_t> vertex;
		data[head].access_tag = true;
		vertex.push(head);
		while (!vertex.empty()) {
			vector<int32_t> neighbors;
			neighbor(vertex.front(), neighbors);
			for (int32_t neighbors_index : neighbors)
				if (data[neighbors_index].access_tag == false) {
					vertex.push(neighbors_index);
					data[neighbors_index].access_tag = true;
				}

			vertex.pop();
		}
	}
	void DFS_traverse() {
		for (int32_t data_index = 0; data_index < size; data_index++)
			if (data[data_index].access_tag == false && !vacancy_find(data_index))
				DFS(data_index);

		for (int32_t data_index = 0; data_index < size; data_index++)
			data[data_index].access_tag = false;

	}
	void DFS(int32_t head) {
		//访问.........

		data[head].access_tag = true;

		vector<int32_t> neighbors;
		neighbor(head, neighbors);
		for (int32_t neighbors_index : neighbors)
			if (data[neighbors_index].access_tag == false)
				DFS(neighbors_index);
	}
	void prim(int32_t head) {
		//无向带权强连通图,每个两维数组的位置代表权

		if (size < 0 || head < 0) {
			cout << "操你妈传的是什么东西,滚" << endl;
			return;
		}

		priority_queue<pair<int32_t, int32_t>, vector<pair<int32_t, int32_t>>, greater<pair<int32_t, int32_t>>> min_heap;

		pair<int32_t, int32_t> node;	//power,location;

		int32_t overall_power = 0;

		vector<int32_t> adjacent;

		//0代表权,head代表位置
		min_heap.push({ 0,head });
		while (!min_heap.empty()) {
			node = min_heap.top();
			min_heap.pop();

			if (data[node.second].access_tag == true)
				continue;

			data[node.second].access_tag = true;
			overall_power += node.first;

			neighbor(node.second, adjacent);

			int32_t power = 0;


			for (int32_t index : adjacent) {
				if (data[index].access_tag == false) {
					power = location[node.second][index];
					min_heap.push({ power, index });
				}
			}
			adjacent.clear();
		}
		//下面应该还有一些比如不有访问空缺,不对,这是无向带权强连通图不可能有空缺......略了罢
	}
	void shortest_path_BFS(int32_t head) {
		// 添加head有效性检查
		if (head < 0 || head >= size)
			return;


		//无向图,可能有空位
		vector<int32_t> shortest(size, INT32_MAX);//从head的最短路径
		vector<int32_t> vertex(size, EMPTY);	//最短路径从哪个顶点过来
		vector<int32_t> neighbors;//该结点的邻居
		queue<int32_t> order; //遍利顺序

		shortest[head] = 0;
		order.push(head);
		data[head].access_tag = true;

		while (order.empty() == false) {
			int32_t node_location = order.front();
			neighbor(node_location, neighbors);	//输出邻居,不会输出空位结点,
			for (int32_t index : neighbors)
				if (data[index].access_tag == false) {
					order.push(index);
					shortest[index] = shortest[node_location] + 1;
					vertex[index] = node_location;
					data[index].access_tag = true;
				}
			//假设有空位滚到order了for (int32_t index : neighbors)为false,然后order.pop();没事人,对order里不太可能出现的空位也可以解决
			order.pop();
			neighbors.clear();
		}

		//初始化
		for (int32_t index = 0; index < size; index++)
			data[index].access_tag = false;

		//为了更通用,所以不察这个了
		//for (int32_t index : shortest)
		//	if (shortest[index] == INT32_MAX)
		//		return;
	}
	void dijkstra(int32_t head) {
		//无向带权邻接矩阵图实现,data中可能有空位
		if (head < 0 || head >= size)
			return;

		priority_queue<pair<int32_t, int32_t>, vector<pair<int32_t, int32_t>>, greater<pair<int32_t, int32_t>>> min_heap;
		vector<int32_t>shortest(size, INT32_MAX);//从head的最短路径
		vector<int32_t>pioneer(size, EMPTY);//最短路径从哪个顶点过来
		vector<int32_t>neighbors;//该结点的邻居
	
		//data[head].access_tag = true;
		min_heap.push({ 0,head });
		shortest[head] = 0;

		while (min_heap.empty() == false) {
			int32_t node_power = min_heap.top().first;
			int32_t node_location = min_heap.top().second;
			min_heap.pop();

			if (data[node_location].access_tag == true)
				continue;

			data[node_location].access_tag = true;

			neighbor(node_location, neighbors);//输出邻居,不会输出空位结点,

			for (int32_t index : neighbors) {//假设有空位滚到了min_heap,for (int32_t index : neighbors)也为false,之前min_heap.pop();没事人,对min_heap里不太可能出现的空位也可以解决,比如head也空
				int64_t index_power = node_power + location[index][node_location];	//int64_t防止上溢
				if (shortest[index] > index_power) {
					shortest[index] = index_power;
					pioneer[index] = node_location;
					// 将更新后的距离放入优先队列
					// 可能有重复的顶点，但距离更小的会先处理
					// 距离更小的顶点处理后也data中access_tag == true,原来更大的结点会跳过
					min_heap.push({ index_power,index });
				}
			}
			//删除旧数据
			neighbors.clear();
		}
		//初始化
		for (int32_t index = 0; index < size; index++)
			data[index].access_tag = false;
	}
	void floyd(vector<vector<int32_t>>& path_node) {
		//无向带权邻接矩阵图实现,location中可能有空位,不相连的边为∞(INT32_MAX)
		//不规范版
		vector<vector<int32_t>> arr(size, vector<int32_t>(size,INT32_MAX));
		for (int32_t proceed = 0; proceed < size; proceed++)
			for (int32_t list = proceed; list < size; list++) {//arr,location,path_node是对称的,所以可以[proceed][list],[list][proceed].path_node也可以.
				arr[proceed][list] = location[proceed][list];
				arr[list][proceed] = location[list][proceed];
				path_node[proceed][list] = EMPTY;
				path_node[list][proceed] = EMPTY;
			}

		for (int32_t node = 0; node < size; node++) {//k
			arr[node][node] = 0;
			for (int32_t proceed = 0; proceed < size; proceed++) {

				for (int32_t list = proceed; list < size; list++) {//proceed与list顺序对结果没有区别
					if (arr[proceed][node] == INT32_MAX || arr[node][list] == INT32_MAX)
						continue; // 关键检查！
					if (arr[proceed][list] > int64_t(arr[proceed][node]) + arr[node][list]) {//arr[proceed][node]转为int64_t,arr[node][list]也会转为int64_t,arr[proceed][list]也会转为int64_t
						arr[proceed][list] = arr[proceed][node] + arr[node][list];
						arr[list][proceed] = arr[list][node] + arr[node][proceed];
						path_node[proceed][list] = node;
						path_node[list][proceed] = node;
					}
				}
			}
		}
	}
	bool print_path(int32_t head , int32_t conclusion,vector<int32_t>& path, const vector<vector<int32_t>> path_node) {
		if (path_node[head][conclusion] == EMPTY)
			return false;
		path.push_back(head);
		path_reconstruction(head, conclusion, path, path_node);
		return true;
	}
	void path_reconstruction(int32_t head, int32_t conclusion, vector<int32_t>& path, const vector<vector<int32_t>>& path_node) {
		if (path_node[head][conclusion] == EMPTY)
			path.push_back(conclusion);
		else{
			path_reconstruction(head, path_node[head][conclusion], path, path_node);
			path_reconstruction(path_node[head][conclusion], conclusion, path, path_node);
		}
	}
	bool topological_sorting(vector<int32_t>& sequence) {
		sequence.clear();
		sequence.reserve(size);

		vector<int32_t>in_degree(size, 0);
		for (int32_t proceed = 0; proceed < size; proceed++)
			for (int32_t list = 0; list < size; list++)
				if (location[proceed][list] != 0)
					in_degree[list]++;

		queue<int32_t> save;

		for (int32_t index_location = 0 ; index_location < in_degree.size() ;index_location++)
			if (in_degree[index_location] == 0)
				save.push(index_location);

		int32_t num = 0;
		vector<int32_t>neighbors;
		while (save.empty() == false) {
			int32_t save_location = save.front();
			save.pop();

			sequence[num] = save_location;
			num++;

			neighbor(save_location, neighbors);//输出邻接顶点,不会输出空位结点
			for (int32_t index_location : neighbors) {
				in_degree[index_location]--;
				if (in_degree[index_location] == 0)
					save.push(index_location);
			}
			neighbors.clear();
		}

		if (num == size)
			return true;
		else
			return false;
	}
};


int32_t main() {

	return 0;
}