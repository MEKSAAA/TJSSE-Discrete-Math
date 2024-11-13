#include<iostream>
using namespace std;

void deallocateMatrix(int** matrix, int n) {
	for (int i = 0;i < n;i++) {
		delete[]matrix[i];
	}
	delete[]matrix;
}  //释放动态分配的二维数组

int** matrixMultiply(int** A, int** B, int n) {
	int** result = new int* [n];
	for (int i = 0;i < n;i++) {
		result[i] = new int[n];
	}  //给结果矩阵分配内存
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			result[i][j] = 0;//初始化结果矩阵
			for (int k = 0;k < n;k++) {
				result[i][j] += A[i][k] * B[k][j];  //计算结果矩阵
				if (result[i][j] > 1)
					result[i][j] = 1;
			}
		}
	}

	return result;
}  //矩阵逻辑乘法函数

int** matrixAdd(int** A, int** B, int n) {
	int** result = new int* [n];
	for (int i = 0;i < n;i++) {
		result[i] = new int[n];
	}  //给结果矩阵分配内存
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			result[i][j] = A[i][j] + B[i][j];
			if (result[i][j] > 1)
				result[i][j] = 1;
		}
	}

	return result;
}  //矩阵逻辑加法函数

void printMatrix(int** matrix, int n) {
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			cout << matrix[i][j] << "  ";
		}
		cout << endl;
	}
}  //输出矩阵

void reflexiveClosure(int** &matrix, int n) {
	for (int i = 0;i < n;i++) {
		matrix[i][i] = 1;
	}
}  //计算自反闭包

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
}  //计算对称闭包

void transitiveClosure(int** &matrix, int size) {
	int** init = matrix;  //存放初始的矩阵A
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
		matrix = matrixAdd(matrix, temp, size);//相加
	}//A^1+A^2+...+A^n

	deallocateMatrix(temp, size);// 释放内存
}  //计算传递闭包

void dealInputError(int& n, int min = 0, int max = 1)  //处理输入错误
{
	while (1) {
		char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
		cin >> n;
		if (cin.fail() || n<min || n>max) {
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
	return;
}

int main()
{
	cout << "*******************************************\n";  //标语
	cout << "**                                       **\n";
	cout << "**        欢迎进入关系的自反、对称       **\n";
	cout << "**           和传递闭包求解程序          **\n";
	cout << "**                                       **\n";
	cout << "*******************************************\n\n\n";
	bool judge = 1;//judge用来判断是否继续输入
	while (1) {
		int size;  //矩阵的阶数
		cout << "请输入矩阵的阶数：";
		dealInputError(size, 1, 1024);
		int** myMatrix = new int* [size];
		for (int i = 0;i < size;i++) {
			myMatrix[i] = new int[size];
		}

		cout << endl << "请输入关系矩阵：" << endl;
		for (int i = 0;i < size;i++) {
			char c;
			bool judge = 0;  //第i行是否需要重新输入
			cout << endl;
			while (1) {
				cout << "请输入矩阵的第" << i + 1 << "行元素(元素为0或1，输入时以空格分隔)：";
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
				}  //个数错误
				if (judge == 0)
					break;
				else {
					cout << "输入错误，请重新输入。" << endl << endl;
					cin.clear();
					cin.ignore(9999, '\n');
					continue;
				}
			}
		}

		int z;//算法序号
		cout << endl << "输入对应序号选择算法" << endl;
		cout << "l:自反闭包" << endl;
		cout << "2:对称闭包" << endl;
		cout << "3:传递闭包" << endl;
		cout << "4:退出" << endl;
		dealInputError(z, 1, 4);
		switch (z) {
			case 1:
				reflexiveClosure(myMatrix, size);
				cout << "自反闭包的关系矩阵为：" << endl;
				printMatrix(myMatrix, size);
				break;
			case 2:
				symmetricClosure(myMatrix, size);
				cout << "对称闭包的关系矩阵为：" << endl;
				printMatrix(myMatrix, size);
				break;
			case 3:
				transitiveClosure(myMatrix, size);
				cout << "传递闭包的关系矩阵为：" << endl;
				printMatrix(myMatrix, size);
				break;
			case 4:
				judge = 0;
				break;
			default:
				break;
		}
		deallocateMatrix(myMatrix, size);

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
				cout << "输入错误，请重新输入。" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}  //个数错误
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