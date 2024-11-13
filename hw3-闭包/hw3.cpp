#include<iostream>
using namespace std;

void deallocateMatrix(int** matrix, int n) {
	for (int i = 0;i < n;i++) {
		delete[]matrix[i];
	}
	delete[]matrix;
}  //�ͷŶ�̬����Ķ�ά����

int** matrixMultiply(int** A, int** B, int n) {
	int** result = new int* [n];
	for (int i = 0;i < n;i++) {
		result[i] = new int[n];
	}  //�������������ڴ�
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			result[i][j] = 0;//��ʼ���������
			for (int k = 0;k < n;k++) {
				result[i][j] += A[i][k] * B[k][j];  //����������
				if (result[i][j] > 1)
					result[i][j] = 1;
			}
		}
	}

	return result;
}  //�����߼��˷�����

int** matrixAdd(int** A, int** B, int n) {
	int** result = new int* [n];
	for (int i = 0;i < n;i++) {
		result[i] = new int[n];
	}  //�������������ڴ�
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			result[i][j] = A[i][j] + B[i][j];
			if (result[i][j] > 1)
				result[i][j] = 1;
		}
	}

	return result;
}  //�����߼��ӷ�����

void printMatrix(int** matrix, int n) {
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			cout << matrix[i][j] << "  ";
		}
		cout << endl;
	}
}  //�������

void reflexiveClosure(int** &matrix, int n) {
	for (int i = 0;i < n;i++) {
		matrix[i][i] = 1;
	}
}  //�����Է��հ�

void symmetricClosure(int** &matrix, int n) {
	int** tmp = new int* [n];
	for (int i = 0;i < n;i++) {
		tmp[i] = new int[n];
	}
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			tmp[i][j] = matrix[j][i];
		}
	}
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			if (matrix[i][j] + tmp[i][j] > 0)
				matrix[i][j] = 1;
		}
	}
}  //����ԳƱհ�

void transitiveClosure(int** &matrix, int size) {
	int** init = matrix;  //��ų�ʼ�ľ���A
	int** temp = new int* [size];
	for (int i = 0; i < size; i++) {
		temp[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp[i][j] = matrix[i][j];
		}
	}

	for (int i = 2;i <= size;i++) {
		temp = matrixMultiply(temp, init, size);
		matrix = matrixAdd(matrix, temp, size);//���
	}//A^1+A^2+...+A^n

	deallocateMatrix(temp, size);// �ͷ��ڴ�
}  //���㴫�ݱհ�

void dealInputError(int& n, int min = 0, int max = 1)  //�����������
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

int main()
{
	cout << "*******************************************\n";  //����
	cout << "**                                       **\n";
	cout << "**        ��ӭ�����ϵ���Է����Գ�       **\n";
	cout << "**           �ʹ��ݱհ�������          **\n";
	cout << "**                                       **\n";
	cout << "*******************************************\n\n\n";
	bool judge = 1;//judge�����ж��Ƿ��������
	while (1) {
		int size;  //����Ľ���
		cout << "���������Ľ�����";
		dealInputError(size, 1, 1024);
		int** myMatrix = new int* [size];
		for (int i = 0;i < size;i++) {
			myMatrix[i] = new int[size];
		}

		cout << endl << "�������ϵ����" << endl;
		for (int i = 0;i < size;i++) {
			char c;
			bool judge = 0;  //��i���Ƿ���Ҫ��������
			cout << endl;
			while (1) {
				cout << "���������ĵ�" << i + 1 << "��Ԫ��(Ԫ��Ϊ0��1������ʱ�Կո�ָ�)��";
				for (int j = 0;j < size;j++) {
					cin >> myMatrix[i][j];
					if (cin.fail() || myMatrix[i][j] < 0 || myMatrix[i][j]>1) {
						judge = 1;
						break;
					}
					else
						judge = 0;
				}
				if (cin.get(c) && c != '\n') {
					judge = 1;
				}  //��������
				if (judge == 0)
					break;
				else {
					cout << "����������������롣" << endl << endl;
					cin.clear();
					cin.ignore(9999, '\n');
					continue;
				}
			}
		}

		int z;//�㷨���
		cout << endl << "�����Ӧ���ѡ���㷨" << endl;
		cout << "l:�Է��հ�" << endl;
		cout << "2:�ԳƱհ�" << endl;
		cout << "3:���ݱհ�" << endl;
		cout << "4:�˳�" << endl;
		dealInputError(z, 1, 4);
		switch (z) {
			case 1:
				reflexiveClosure(myMatrix, size);
				cout << "�Է��հ��Ĺ�ϵ����Ϊ��" << endl;
				printMatrix(myMatrix, size);
				break;
			case 2:
				symmetricClosure(myMatrix, size);
				cout << "�ԳƱհ��Ĺ�ϵ����Ϊ��" << endl;
				printMatrix(myMatrix, size);
				break;
			case 3:
				transitiveClosure(myMatrix, size);
				cout << "���ݱհ��Ĺ�ϵ����Ϊ��" << endl;
				printMatrix(myMatrix, size);
				break;
			case 4:
				judge = 0;
				break;
			default:
				break;
		}
		deallocateMatrix(myMatrix, size);

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
		if (judge == 0)
			break;

		cout << endl;
		if (answer == 'y' || answer == 'Y')
			continue;
		else if (answer == 'n' || answer == 'N')
			break;
	}
	return 0;
}