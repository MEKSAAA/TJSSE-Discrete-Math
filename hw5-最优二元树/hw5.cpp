#include<iostream>
#include<queue>
#include<vector>
#include<map>
using namespace std;

class HuffmanTree;

//������������Ľڵ���
class HuffmanNode {
	friend HuffmanTree;
private:
	char data;// �ڵ�洢���ַ�
	int frequency;// �ڵ��Ӧ�ַ��ĳ���Ƶ��
	HuffmanNode* left, * right; // �����ӽڵ�ָ��
public:
	HuffmanNode(char d, int f) :data(d), frequency(f) { left = right = NULL; }
	bool operator>(const HuffmanNode& other)const { 
		return frequency > other.frequency; 
	}//�������ȶ��еıȽϺ�����Ƶ��С�����ȼ���
};

//���������Ĺ�����
class HuffmanTree {
private:
	priority_queue<HuffmanNode, vector<HuffmanNode>, greater<HuffmanNode>>minHeap;//��С�ѣ����ڹ�����������
public:
	HuffmanTree(const map<char, int>& frequencis);//���캯��������ַ�����Ƶ�ʵ�ӳ��
	void printHuffmanCodes(HuffmanNode* root, string code);//��ӡ����������
	void printHuffmanTree();//��ӡ��������
};

HuffmanTree::HuffmanTree(const map<char, int>& frequencies)
{
	//��ÿ���ַ���Ϊһ�������Ľڵ������С��
	for (const auto& pair : frequencies) {
		minHeap.push(HuffmanNode(pair.first, pair.second));
	}
	
	//������������
	while (minHeap.size() > 1) {
		// ȡ��������СƵ�ʵĽڵ�
		HuffmanNode* left = new HuffmanNode(0, 0);
		*left = minHeap.top();
		minHeap.pop();

		HuffmanNode* right = new HuffmanNode(0, 0);
		*right = minHeap.top();
		minHeap.pop();

		// �ϲ���һ���µĽڵ㣬��Ƶ��Ϊ�����ڵ��Ƶ��֮��
		HuffmanNode combinedNode(0, left->frequency + right->frequency);
		combinedNode.left = left;
		combinedNode.right = right;

		// ���½ڵ�������ȶ���
		minHeap.push(combinedNode);
	}
}

void HuffmanTree::printHuffmanCodes(HuffmanNode* root, string code)//�ݹ�
{
	if (!root)
		return;
	if (root->data) {
		// �����Ҷ�ӽڵ㣬��ӡ�ַ��Ͷ�Ӧ�ı���
		cout << "�ַ���" << root->data << "������Ƶ�ʣ�" << root->frequency << "�����룺" << code << endl;
	}

	// �ݹ��ӡ��������
	printHuffmanCodes(root->left, code + "0");
	printHuffmanCodes(root->right, code + "1");
}

void HuffmanTree::printHuffmanTree()
{
	if (minHeap.empty()) {
		cout << "��������Ϊ�գ��ޱ��룡" << endl;
		return;
	}
	// ��ȡ���ڵ㲢��ӡ����
	HuffmanNode root = minHeap.top();
	printHuffmanCodes(&root, "");
}

int main()
{
	//����
	cout << "******************************************\n";
	cout << "**                                      **\n";
	cout << "**           ��ӭ�����������           **\n";
	cout << "**        ��ͨ�ű�����Ӧ�õĳ���        **\n";
	cout << "**                                      **\n";
	cout << "******************************************\n\n";

	while (1) {
		int num;//�ַ�����
		map<char, int>frequencies;//�ַ�Ƶ�ʵ�ӳ��

		//�����ַ�����
		while (1) {
			cout << "�������ַ��ĸ���(2-1000)��";
			char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
			cin >> num;
			if (cin.fail() || num < 2 || num > 1000) {
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

		//�����ַ����ݼ������Ƶ��
		cout << endl;
		for (int i = 0;i < num;i++) {
			while (1) {
				bool judge = 0;  //�ж��Ƿ���Ҫ��������
				char data;
				int frequency;
				cout << "�������" << i + 1 << "���ַ�������ֵ�Ƶ�ʣ��ÿո�ָ�����";
				cin >> data >> frequency;
				if (cin.fail() || frequency < 0 || frequencies.find(data) != frequencies.end()) {
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
				else {
					frequencies.insert(pair<char, int>(data, frequency));
					break;
				}
			}
		}

		//������������
		HuffmanTree myHT(frequencies);

		//��ӡ���������ı���
		cout << endl << "���������������£�" << endl << endl;
		myHT.printHuffmanTree();

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