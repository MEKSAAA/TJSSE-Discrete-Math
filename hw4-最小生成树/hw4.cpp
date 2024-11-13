#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX_VERTICES 100
#define MAX_WEIGHT 100000000
#define MIN_VERTICES 2

class UnionFind {
private:
	vector<int>parent;//表示每个元素所属的集合，即父节点
public:
	UnionFind(int size) :parent(size) {
		for (int i = 0;i < size;i++)
			parent[i] = i; //初始化每个节点为独立的集合
	}//构造函数
	int findSet(int node);//用于查找某个节点所属的集合
	void unionSets(int u, int v);//合并集合
};

class Graph {
private:
	int V;//节点数
	vector<vector<int>>adjMatrix; //邻接矩阵,用于prim
	vector<pair<int, pair<int, int>>>edges;//存储边的信息（权值，（顶点1，顶点2）），用于kruskal
public:
	Graph(int vertices) :V(vertices), adjMatrix(vertices, vector<int>(vertices, INT_MAX)) {}//构造函数
	void addEdge(int u, int v, int weight);  //添加有权边
	int Prim(int startNode, vector<pair<int, int>>& resultEdges); //prim算法
	int Kruskal(vector<pair<int, int>>& resultEdges); //kruskal算法
	void printMST(const vector<pair<int, int>>& resultEdges);//打印最小生成树的各边
};

int UnionFind::findSet(int node)
{
	if (parent[node] != node) {
		parent[node] = findSet(parent[node]);  //路径压缩，将节点直接连接到根节点
	}
	return parent[node];
}

void UnionFind::unionSets(int u, int v)
{
	int setU = findSet(u);//查找节点u所在的集合
	int setV = findSet(v);//查找节点v所在的集合
	parent[setU] = setV;//将节点setU所在集合的根节点设置为setV，即合并两个集合
}

void Graph::addEdge(int u, int v, int weight)
{
	//添加边时更新存储空间
	adjMatrix[u][v] = weight;
	adjMatrix[v][u] = weight;
	edges.push_back({ weight, {u, v} });
	return;
}

int Graph::Prim(int startNode, vector<pair<int, int>>& resultEdges)
{
	vector<bool>visited(V, false);//记录结点是否已经加入最小生成树
	vector<int>minDist(V, INT_MAX);//记录当前节点到最小生成树的最小距离
	vector<int>parent(V, -1);//存储最小权值边两段顶点信息
	int totalWeight = 0;// 记录最小生成树的总权重
	int selectedNodes = 0;//记录加入最小生成树的节点树

	minDist[startNode] = 0;// 从指定的起始结点开始
	int i, j;
	for (i = 0;i < V;i++) {
		int u = -1;
		// 找到未加入最小生成树且具有最小距离的节点
		for (j = 0;j < V;j++) {
			if (!visited[j] && (u == -1 || minDist[j] < minDist[u])) {
				u = j;
			}
		}

		if (minDist[u] == INT_MAX) {
			break;//如果找不到合适的节点，则结束
		}

		visited[u] = true;// 将节点标记为已访问
		totalWeight += minDist[u];//将权重累加到最小生成树的总权重
		selectedNodes++;//增加加入最小生成树的节点树

		//将边加入结果集
		if (u != startNode)
			resultEdges.push_back({ parent[u],u });

		//更新与当前结点和相邻的未访问的节点的最小距离和父亲列表
		for (int v = 0;v < V;v++) {
			if (!visited[v] && adjMatrix[u][v] < minDist[v]) {
				minDist[v] = adjMatrix[u][v];
				parent[v] = u;
			}
		}
	}

	//检查是否存在最小生成树
	if (selectedNodes != V)
		return -1;//不存在返回值为-1
	return totalWeight;
}

int Graph::Kruskal(vector<pair<int, int>>& resultEdges)
{
	sort(edges.begin(), edges.end());//将边按权值升序排序
	UnionFind uf(V);
	int totalWeight = 0;
	for (const auto& edge : edges) {
		int u = edge.second.first;
		int v = edge.second.second;
		int weight = edge.first;

		//判断加入该边是否会形成回路
		if (uf.findSet(u) != uf.findSet(v)) {
			uf.unionSets(u, v);//合并集合
			totalWeight += weight;//累加权值
			resultEdges.push_back({ u,v });//// 将边加入最小生成树的边集合
		}
	}

	//检查是否存在最小生成树
	if (resultEdges.size() != V - 1)
		return -1;//不存在返回值为-1

	return totalWeight;
}

void Graph::printMST(const vector<pair<int, int>>& resultEdges)
{
	for (const auto& edge : resultEdges) {
		cout << edge.first + 1 << "---" << edge.second + 1 << endl;
	}
}

int main()
{
	//标语
	cout << "******************************************\n"; 
	cout << "**                                      **\n";
	cout << "**               欢迎进入               **\n";
	cout << "**          用Prim和Kruskal算法         **\n";
	cout << "**          求解最小生成树程序          **\n";
	cout << "**                                      **\n";
	cout << "******************************************\n\n";

	while (1) {
		int n;//顶点数
		int m;//边数
		int start;//最小生成树起始节点序号
		int u, v, w;
		int totalWeight;//最小生成树的总值
		vector<pair<int, int>> resultEdges;//存最小生成树中的边

		//输入顶点数和边数
		while (1) {
			bool judge = 0;  //判断是否需要重新输入
			cout << "请输入所求图的顶点数目和边的数目(以空格分隔）：" << endl;
			cin >> n >> m;
			if (cin.fail() || n < MIN_VERTICES || n > MAX_VERTICES || m < n - 1) {
				judge = true;
			}//输入的内容错误
			char c;  //用来获取最后的字符
			if (judge == false && cin.get(c) && c != '\n') {
				judge = true;
			}  //输入的元素个数错误
			if (judge) {
				cin.clear();
				cin.ignore(9999, '\n');
				cout << "输入错误，请重新输入。" << endl;
				continue;
			}
			else
				break;
		}

		Graph myGraph(n);  //构造图

		cout << "请输入各边的头尾节点序号及该边的权值(以空格分隔)：" << endl;  //输入所有边及其权值
		for (int i = 0;i < m;i++) {
			while (1) {
				bool judge = 0;  //判断是否需要重新输入
				cout << "请输入第" << i + 1 << "条边的信息：";
				cin >> u >> v >> w;
				if (cin.fail() || u<1 || u>n || v<1 || v>n || w<-MAX_WEIGHT || w>MAX_WEIGHT) {
					judge = true;
				}//输入的内容错误
				char c;  //用来获取最后的字符
				if (judge == false && cin.get(c) && c != '\n') {
					judge = true;
				}  //输入的元素个数错误
				if (judge) {
					cin.clear();
					cin.ignore(9999, '\n');
					cout << "输入错误，请重新输入。" << endl;
					continue;
				}
				else
					break;
			}
			myGraph.addEdge(u - 1, v - 1, w);//把边加到图中，用户的第u个点是程序中的第u-1个点
		}

		//选择由哪一种方法求解
		cout << endl;
		cout << "1.用Prim算法求解最小生成树" << endl;
		cout << "2.用Kruskal算法求解最小生成树" << endl;
		int choice;
		while (1) {
			cout << "请选择使用的算法（1/2）：";
			cin >> choice;
			char c;
			if (cin.fail() || (choice != 1 && choice != 2)) {
				cout << "输入无效，请重新输入。" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}  //内容错误
			else if (cin.get(c) && c != '\n') {
				cout << "输入无效，请重新输入。" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}  //个数错误
			else
				break;
		}//输入处理

	    //两种算法
		if (choice == 1) {
			cout << endl << "使用Prim算法：" << endl;
			//输入起始的节点序号
			cout << endl;
			while (1) {
				cout << "请输入起始的节点序号：";
				char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
				cin >> start;
				if (cin.fail() || start < 1 || start > n) {
					cout << "输入错误，请重新输入。" << endl;
					cin.clear();
					cin.ignore(9999, '\n');
					continue;
				}  //内容错误
				else if (cin.get(c) && c != '\n') {
					cout << "输入错误，请重新输入。" << endl;
					cin.clear();
					cin.ignore(9999, '\n');
					continue;
				}  //个数错误
				else
					break;
			}

			//prim核心部分
			totalWeight = myGraph.Prim(start - 1, resultEdges);  //prim算法
			if (totalWeight == -1) {
				cout << endl << "此图不存在最小生成树！" << endl;
			}
			else {
				cout << endl << "最小生成树中的各边：" << endl;
				myGraph.printMST(resultEdges);  //打印边
				cout << endl << "最小生成树的总权值为：" << totalWeight << endl;
			}
		}
		else if (choice == 2) {
			cout << endl << "使用Kruskal算法：" << endl;
			//kruskal核心部分
			totalWeight = myGraph.Kruskal(resultEdges);  //kruskal算法
			if (totalWeight == -1) {
				cout << endl << "此图不存在最小生成树！" << endl;
			}
			else {
				cout << endl << "最小生成树中的各边：" << endl;
				myGraph.printMST(resultEdges);  //打印边
				cout << endl << "最小生成树的总权值为：" << totalWeight << endl;
			}
		}

		//判断是否继续运行程序
		char answer;
		while (1) {
			cout << endl << "是否继续运行该程序？（y/n）：";
			cin >> answer;
			char c;
			if (cin.fail() || (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N')) {
				cout << "输入无效，请重新输入。" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}  //内容错误
			else if (cin.get(c) && c != '\n') {
				cout << "输入无效，请重新输入。" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}  //个数错误
			else
				break;
		}
		cout << endl;
		if (answer == 'y' || answer == 'Y')
			continue;
		else if (answer == 'n' || answer == 'N')
			break;
	}
	return 0;
}

/*
测试数据：
7 12
1 2 20
2 3 15
3 4 3
4 5 17
5 6 28
6 1 23
1 7 1
2 7 4
3 7 9
4 7 16
5 7 25
6 7 36
*/

