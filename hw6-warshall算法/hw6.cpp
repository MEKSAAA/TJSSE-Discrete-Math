#include <iostream>
#include<cstring>
using namespace std;

//�ýṹ������ʾ��Ԫ��ϵ
typedef struct{
	char a;
	char b;
}BR;

int n, m; //n ��ʾ���� A �е�Ԫ�ظ�����m ��ʾ��Ԫ��ϵ R �е�Ԫ�ظ���

//�����������
void dealInputError(int& n, int min = 1, int max = 1024)  
{
	while (1) {
		char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
		cin >> n;
		if (cin.fail() || n<min || n>max) {
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
	return;
}

//��ʼ������A
void init_aggregation(char*& A)  
{

	cout << "�����뼯�� A �е�Ԫ�ظ���(������)�����س���������һ�" << endl;
	dealInputError(n);
	A = new char[n];
	cout << "���������뼯�� A �е�";
	cout << n; //n �Ǽ��� A �е�Ԫ�ظ���
	cout << "��Ԫ��(���磺a b c d ......�����ĸ�ʽ)�����س���������һ�" << endl;
	while (1) {
		bool judge = 0;//�ж��Ƿ���Ҫ��������

		for (int i = 0;i < n;i++) {
			cin >> A[i];
			if (cin.fail() || (!isalpha(A[i]))) {
				cout << "����������������롣" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				judge = 1;
				break;
			}
		}
		if (judge)
			continue;
		char c;  //������ȡ�����ַ�
		if (cin.get(c) && c != '\n') {
			cout << "����������������롣" << endl;
			cin.clear();
			cin.ignore(9999, '\n');
			judge = 1;
		}  //�����Ԫ�ظ�������
		if (judge)
			continue;
		else
			break;
	}
}

//�ж��ַ�c�Ƿ����ַ���str��
bool my_strchr(const char* str, int c)
{
	while (*str != '\0') {
		if (*str == c) {
			return true;
		}
		++str;
	}
	return false;
}

//�������� A �Ķ�Ԫ��ϵ R �ļ��ϲ���ʼ��
void init_BinaryRelation(BR*& R, const char* A)  
{
	cout << "�������Ԫ��ϵ R �е�Ԫ�ظ���(������)�����س���������һ�" << endl;
	dealInputError(m, 1, n * n);
	R = new BR[m];

	cout << "���������� R �е�";
	cout << m; //m �� R �е�Ԫ�ظ���
	cout << "��Ԫ�أ�һ����һ��Ԫ��" << endl;
	cout << "(���磺" << endl << "a b" << endl;
	cout << "b c" << endl;
	cout << "c d" << endl;
	cout << "......" << endl;
	cout << "�����ĸ�ʽ)�����س���������һ�" << endl;

	for (int i = 0; i < m; i++) {
		while (1) {
			char a, b;
			bool judge = 0;  //�ж��Ƿ���Ҫ��������
			cout << "�������" << i + 1 << "��Ԫ�أ�";

			cin >> a >> b;
			if (cin.fail() || (!isalpha(a)) || (!my_strchr(A, a)) || (!isalpha(b)) || (!my_strchr(A, b))) {
				judge = true;
			}//��������ݴ���
			char c;  //������ȡ�����ַ�
			if (judge == false && cin.get(c) && c != '\n') {
				judge = true;
			}  //�����Ԫ�ظ�������

			if (judge) {
				cin.clear();
				cin.ignore(9999, '\n');
				cout << "�������������������ȷ��Ԫ�ء�" << endl;
				continue;
			}
			else {
				R[i].a = a;
				R[i].b = b;
				break;
			}
		}
	}
}

// �ڼ��� A �в����ַ� ch ������
int fun(char ch, char*& A)
{
	for (int i = 0; i < n; i++){
		if (ch == A[i]){
			return i;
		}
	}
	return -1;
}

//Warshall �㷨�ĺ��Ĳ���
void Warshall(char*& A, BR*& R, bool**& tR)
{
	int i, j, k;
	int x, y;
	//�ù�ϵ�����ʾ��Ԫ��ϵ R
	for (i = 0; i < m; i++){
		x = fun(R[i].a, A);
		y = fun(R[i].b, A);
		tR[x][y] = 1;
	}
	//���㴫�ݱհ��Ĺ���
	for (i = 0; i < n; i++){ //������
		for (j = 0; j < n; j++){ //������
			if (tR[j][i] == 1){
				for (k = 0; k < n; k++){
					tR[j][k] = tR[j][k] + tR[i][k];
				}
			}
		}
	}
}

//�����ݱհ� t(R)�Ĺ�ϵ�����ʾת��Ϊ���ϱ�ʾ
void translation_output(char*& A, bool**& tR)
{
	cout << endl;
	cout << "R �Ĵ��ݱհ�(������ʽ)Ϊ��" << endl;
	cout << "t(R) = {";

	int num = 0;//�հ��е�Ԫ�ظ���
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			if (tR[i][j] == 1)
				num++;
		}
	}
	int k = 0;  //���ڼ������ж��費��Ҫ�������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (tR[i][j] == 1) {
				k++;
				cout << "<" << A[i] << "," << A[j] << ">";
				if (k < num)
					cout << ",";
			}
		}
	}
	cout << "}" << endl;
}

//������
int main()
{
	cout << "********************************************\n";  //����
	cout << "**                                        **\n";
	cout << "**         ��ӭ������Warshall�㷨         **\n";
	cout << "**         ����ϵ�Ĵ��ݱհ�����         **\n";
	cout << "**                                        **\n";
	cout << "********************************************\n\n";
	while (1) {
		char* A;
		init_aggregation(A); //��ʼ������ A
		BR* R;
		init_BinaryRelation(R, A); //��ʼ����Ԫ��ϵ
		bool** tR; //���ݱհ�����
		//��̬���� bool ���͵Ķ�ά����
		tR = new bool* [n];
		for (int i = 0; i < n; i++) {
			tR[i] = new bool[n];
		}
		//��ʼ����ά����(ȫ����ֵΪ 0)
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tR[i][j] = 0;
			}
		}
		Warshall(A, R, tR);//���� Warshall �㷨����
		translation_output(A, tR); //�����ݱհ� t(R)�Ĺ�ϵ�����ʾת��Ϊ���ϱ�ʾ

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
				cout << "����������������롣" << endl;
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