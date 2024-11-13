#include<iostream>
#include<queue>
#include<vector>
#include<map>
using namespace std;

class HuffmanTree;

//定义哈夫曼树的节点类
class HuffmanNode {
	friend HuffmanTree;
private:
	char data;// 节点存储的字符
	int frequency;// 节点对应字符的出现频率
	HuffmanNode* left, * right; // 左右子节点指针
public:
	HuffmanNode(char d, int f) :data(d), frequency(f) { left = right = NULL; }
	bool operator>(const HuffmanNode& other)const { 
		return frequency > other.frequency; 
	}//用于优先队列的比较函数，频率小的优先级高
};

//哈夫曼树的构建类
class HuffmanTree {
private:
	priority_queue<HuffmanNode, vector<HuffmanNode>, greater<HuffmanNode>>minHeap;//最小堆，用于构建哈夫曼树
public:
	HuffmanTree(const map<char, int>& frequencis);//构造函数，获得字符及其频率的映射
	void printHuffmanCodes(HuffmanNode* root, string code);//打印哈夫曼编码
	void printHuffmanTree();//打印哈夫曼树
};

HuffmanTree::HuffmanTree(const map<char, int>& frequencies)
{
	//将每个字符作为一个单独的节点插入最小堆
	for (const auto& pair : frequencies) {
		minHeap.push(HuffmanNode(pair.first, pair.second));
	}
	
	//构建哈夫曼树
	while (minHeap.size() > 1) {
		// 取出两个最小频率的节点
		HuffmanNode* left = new HuffmanNode(0, 0);
		*left = minHeap.top();
		minHeap.pop();

		HuffmanNode* right = new HuffmanNode(0, 0);
		*right = minHeap.top();
		minHeap.pop();

		// 合并成一个新的节点，其频率为两个节点的频率之和
		HuffmanNode combinedNode(0, left->frequency + right->frequency);
		combinedNode.left = left;
		combinedNode.right = right;

		// 将新节点插入优先队列
		minHeap.push(combinedNode);
	}
}

void HuffmanTree::printHuffmanCodes(HuffmanNode* root, string code)//递归
{
	if (!root)
		return;
	if (root->data) {
		// 如果是叶子节点，打印字符和对应的编码
		cout << "字符：" << root->data << "，出现频率：" << root->frequency << "，编码：" << code << endl;
	}

	// 递归打印左右子树
	printHuffmanCodes(root->left, code + "0");
	printHuffmanCodes(root->right, code + "1");
}

void HuffmanTree::printHuffmanTree()
{
	if (minHeap.empty()) {
		cout << "哈夫曼树为空，无编码！" << endl;
		return;
	}
	// 获取根节点并打印编码
	HuffmanNode root = minHeap.top();
	printHuffmanCodes(&root, "");
}

int main()
{
	//标语
	cout << "******************************************\n";
	cout << "**                                      **\n";
	cout << "**           欢迎进入哈夫曼树           **\n";
	cout << "**        在通信编码中应用的程序        **\n";
	cout << "**                                      **\n";
	cout << "******************************************\n\n";

	while (1) {
		int num;//字符个数
		map<char, int>frequencies;//字符频率的映射

		//输入字符个数
		while (1) {
			cout << "请输入字符的个数(2-1000)：";
			char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
			cin >> num;
			if (cin.fail() || num < 2 || num > 1000) {
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

		//输入字符内容及其出现频率
		cout << endl;
		for (int i = 0;i < num;i++) {
			while (1) {
				bool judge = 0;  //判断是否需要重新输入
				char data;
				int frequency;
				cout << "请输入第" << i + 1 << "个字符及其出现的频率（用空格分隔）：";
				cin >> data >> frequency;
				if (cin.fail() || frequency < 0 || frequencies.find(data) != frequencies.end()) {
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
				else {
					frequencies.insert(pair<char, int>(data, frequency));
					break;
				}
			}
		}

		//构建哈夫曼树
		HuffmanTree myHT(frequencies);

		//打印哈夫曼树的编码
		cout << endl << "哈夫曼树编码如下：" << endl << endl;
		myHT.printHuffmanTree();

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
13
a 2
b 3
c 5
d 7
e 11
f 13
g 17
h 19
i 23
j 29
k 31
l 37
m 41
*/