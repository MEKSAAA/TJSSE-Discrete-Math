#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX_VERTICES 100
#define MAX_WEIGHT 100000000
#define MIN_VERTICES 2

class UnionFind {
private:
	vector<int>parent;//��ʾÿ��Ԫ�������ļ��ϣ������ڵ�
public:
	UnionFind(int size) :parent(size) {
		for (int i = 0;i < size;i++)
			parent[i] = i; //��ʼ��ÿ���ڵ�Ϊ�����ļ���
	}//���캯��
	int findSet(int node);//���ڲ���ĳ���ڵ������ļ���
	void unionSets(int u, int v);//�ϲ�����
};

class Graph {
private:
	int V;//�ڵ���
	vector<vector<int>>adjMatrix; //�ڽӾ���,����prim
	vector<pair<int, pair<int, int>>>edges;//�洢�ߵ���Ϣ��Ȩֵ��������1������2����������kruskal
public:
	Graph(int vertices) :V(vertices), adjMatrix(vertices, vector<int>(vertices, INT_MAX)) {}//���캯��
	void addEdge(int u, int v, int weight);  //�����Ȩ��
	int Prim(int startNode, vector<pair<int, int>>& resultEdges); //prim�㷨
	int Kruskal(vector<pair<int, int>>& resultEdges); //kruskal�㷨
	void printMST(const vector<pair<int, int>>& resultEdges);//��ӡ��С�������ĸ���
};

int UnionFind::findSet(int node)
{
	if (parent[node] != node) {
		parent[node] = findSet(parent[node]);  //·��ѹ�������ڵ�ֱ�����ӵ����ڵ�
	}
	return parent[node];
}

void UnionFind::unionSets(int u, int v)
{
	int setU = findSet(u);//���ҽڵ�u���ڵļ���
	int setV = findSet(v);//���ҽڵ�v���ڵļ���
	parent[setU] = setV;//���ڵ�setU���ڼ��ϵĸ��ڵ�����ΪsetV�����ϲ���������
}

void Graph::addEdge(int u, int v, int weight)
{
	//��ӱ�ʱ���´洢�ռ�
	adjMatrix[u][v] = weight;
	adjMatrix[v][u] = weight;
	edges.push_back({ weight, {u, v} });
	return;
}

int Graph::Prim(int startNode, vector<pair<int, int>>& resultEdges)
{
	vector<bool>visited(V, false);//��¼����Ƿ��Ѿ�������С������
	vector<int>minDist(V, INT_MAX);//��¼��ǰ�ڵ㵽��С����������С����
	vector<int>parent(V, -1);//�洢��СȨֵ�����ζ�����Ϣ
	int totalWeight = 0;// ��¼��С����������Ȩ��
	int selectedNodes = 0;//��¼������С�������Ľڵ���

	minDist[startNode] = 0;// ��ָ������ʼ��㿪ʼ
	int i, j;
	for (i = 0;i < V;i++) {
		int u = -1;
		// �ҵ�δ������С�������Ҿ�����С����Ľڵ�
		for (j = 0;j < V;j++) {
			if (!visited[j] && (u == -1 || minDist[j] < minDist[u])) {
				u = j;
			}
		}

		if (minDist[u] == INT_MAX) {
			break;//����Ҳ������ʵĽڵ㣬�����
		}

		visited[u] = true;// ���ڵ���Ϊ�ѷ���
		totalWeight += minDist[u];//��Ȩ���ۼӵ���С����������Ȩ��
		selectedNodes++;//���Ӽ�����С�������Ľڵ���

		//���߼�������
		if (u != startNode)
			resultEdges.push_back({ parent[u],u });

		//�����뵱ǰ�������ڵ�δ���ʵĽڵ����С����͸����б�
		for (int v = 0;v < V;v++) {
			if (!visited[v] && adjMatrix[u][v] < minDist[v]) {
				minDist[v] = adjMatrix[u][v];
				parent[v] = u;
			}
		}
	}

	//����Ƿ������С������
	if (selectedNodes != V)
		return -1;//�����ڷ���ֵΪ-1
	return totalWeight;
}

int Graph::Kruskal(vector<pair<int, int>>& resultEdges)
{
	sort(edges.begin(), edges.end());//���߰�Ȩֵ��������
	UnionFind uf(V);
	int totalWeight = 0;
	for (const auto& edge : edges) {
		int u = edge.second.first;
		int v = edge.second.second;
		int weight = edge.first;

		//�жϼ���ñ��Ƿ���γɻ�·
		if (uf.findSet(u) != uf.findSet(v)) {
			uf.unionSets(u, v);//�ϲ�����
			totalWeight += weight;//�ۼ�Ȩֵ
			resultEdges.push_back({ u,v });//// ���߼�����С�������ı߼���
		}
	}

	//����Ƿ������С������
	if (resultEdges.size() != V - 1)
		return -1;//�����ڷ���ֵΪ-1

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
	//����
	cout << "******************************************\n"; 
	cout << "**                                      **\n";
	cout << "**               ��ӭ����               **\n";
	cout << "**          ��Prim��Kruskal�㷨         **\n";
	cout << "**          �����С����������          **\n";
	cout << "**                                      **\n";
	cout << "******************************************\n\n";

	while (1) {
		int n;//������
		int m;//����
		int start;//��С��������ʼ�ڵ����
		int u, v, w;
		int totalWeight;//��С����������ֵ
		vector<pair<int, int>> resultEdges;//����С�������еı�

		//���붥�����ͱ���
		while (1) {
			bool judge = 0;  //�ж��Ƿ���Ҫ��������
			cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ(�Կո�ָ�����" << endl;
			cin >> n >> m;
			if (cin.fail() || n < MIN_VERTICES || n > MAX_VERTICES || m < n - 1) {
				judge = true;
			}//��������ݴ���
			char c;  //������ȡ�����ַ�
			if (judge == false && cin.get(c) && c != '\n') {
				judge = true;
			}  //�����Ԫ�ظ�������
			if (judge) {
				cin.clear();
				cin.ignore(9999, '\n');
				cout << "����������������롣" << endl;
				continue;
			}
			else
				break;
		}

		Graph myGraph(n);  //����ͼ

		cout << "��������ߵ�ͷβ�ڵ���ż��ñߵ�Ȩֵ(�Կո�ָ�)��" << endl;  //�������б߼���Ȩֵ
		for (int i = 0;i < m;i++) {
			while (1) {
				bool judge = 0;  //�ж��Ƿ���Ҫ��������
				cout << "�������" << i + 1 << "���ߵ���Ϣ��";
				cin >> u >> v >> w;
				if (cin.fail() || u<1 || u>n || v<1 || v>n || w<-MAX_WEIGHT || w>MAX_WEIGHT) {
					judge = true;
				}//��������ݴ���
				char c;  //������ȡ�����ַ�
				if (judge == false && cin.get(c) && c != '\n') {
					judge = true;
				}  //�����Ԫ�ظ�������
				if (judge) {
					cin.clear();
					cin.ignore(9999, '\n');
					cout << "����������������롣" << endl;
					continue;
				}
				else
					break;
			}
			myGraph.addEdge(u - 1, v - 1, w);//�ѱ߼ӵ�ͼ�У��û��ĵ�u�����ǳ����еĵ�u-1����
		}

		//ѡ������һ�ַ������
		cout << endl;
		cout << "1.��Prim�㷨�����С������" << endl;
		cout << "2.��Kruskal�㷨�����С������" << endl;
		int choice;
		while (1) {
			cout << "��ѡ��ʹ�õ��㷨��1/2����";
			cin >> choice;
			char c;
			if (cin.fail() || (choice != 1 && choice != 2)) {
				cout << "������Ч�����������롣" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}  //���ݴ���
			else if (cin.get(c) && c != '\n') {
				cout << "������Ч�����������롣" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}  //��������
			else
				break;
		}//���봦��

	    //�����㷨
		if (choice == 1) {
			cout << endl << "ʹ��Prim�㷨��" << endl;
			//������ʼ�Ľڵ����
			cout << endl;
			while (1) {
				cout << "��������ʼ�Ľڵ���ţ�";
				char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
				cin >> start;
				if (cin.fail() || start < 1 || start > n) {
					cout << "����������������롣" << endl;
					cin.clear();
					cin.ignore(9999, '\n');
					continue;
				}  //���ݴ���
				else if (cin.get(c) && c != '\n') {
					cout << "����������������롣" << endl;
					cin.clear();
					cin.ignore(9999, '\n');
					continue;
				}  //��������
				else
					break;
			}

			//prim���Ĳ���
			totalWeight = myGraph.Prim(start - 1, resultEdges);  //prim�㷨
			if (totalWeight == -1) {
				cout << endl << "��ͼ��������С��������" << endl;
			}
			else {
				cout << endl << "��С�������еĸ��ߣ�" << endl;
				myGraph.printMST(resultEdges);  //��ӡ��
				cout << endl << "��С����������ȨֵΪ��" << totalWeight << endl;
			}
		}
		else if (choice == 2) {
			cout << endl << "ʹ��Kruskal�㷨��" << endl;
			//kruskal���Ĳ���
			totalWeight = myGraph.Kruskal(resultEdges);  //kruskal�㷨
			if (totalWeight == -1) {
				cout << endl << "��ͼ��������С��������" << endl;
			}
			else {
				cout << endl << "��С�������еĸ��ߣ�" << endl;
				myGraph.printMST(resultEdges);  //��ӡ��
				cout << endl << "��С����������ȨֵΪ��" << totalWeight << endl;
			}
		}

		//�ж��Ƿ�������г���
		char answer;
		while (1) {
			cout << endl << "�Ƿ�������иó��򣿣�y/n����";
			cin >> answer;
			char c;
			if (cin.fail() || (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N')) {
				cout << "������Ч�����������롣" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}  //���ݴ���
			else if (cin.get(c) && c != '\n') {
				cout << "������Ч�����������롣" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}  //��������
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
�������ݣ�
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

