#include <iostream>
#include<cstring>
using namespace std;

//用结构体来表示二元关系
typedef struct{
	char a;
	char b;
}BR;

int n, m; //n 表示集合 A 中的元素个数，m 表示二元关系 R 中的元素个数

//处理输入错误
void dealInputError(int& n, int min = 1, int max = 1024)  
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

//初始化集合A
void init_aggregation(char*& A)  
{

	cout << "请输入集合 A 中的元素个数(正整数)，按回车键输入下一项：" << endl;
	dealInputError(n);
	A = new char[n];
	cout << "请依次输入集合 A 中的";
	cout << n; //n 是集合 A 中的元素个数
	cout << "个元素(形如：a b c d ......这样的格式)，按回车键输入下一项：" << endl;
	while (1) {
		bool judge = 0;//判断是否需要重新输入

		for (int i = 0;i < n;i++) {
			cin >> A[i];
			if (cin.fail() || (!isalpha(A[i]))) {
				cout << "输入错误，请重新输入。" << endl;
				cin.clear();
				cin.ignore(9999, '\n');
				judge = 1;
				break;
			}
		}
		if (judge)
			continue;
		char c;  //用来获取最后的字符
		if (cin.get(c) && c != '\n') {
			cout << "输入错误，请重新输入。" << endl;
			cin.clear();
			cin.ignore(9999, '\n');
			judge = 1;
		}  //输入的元素个数错误
		if (judge)
			continue;
		else
			break;
	}
}

//判断字符c是否在字符串str中
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

//创建集合 A 的二元关系 R 的集合并初始化
void init_BinaryRelation(BR*& R, const char* A)  
{
	cout << "请输入二元关系 R 中的元素个数(正整数)，按回车键输入下一项：" << endl;
	dealInputError(m, 1, n * n);
	R = new BR[m];

	cout << "请依次输入 R 中的";
	cout << m; //m 是 R 中的元素个数
	cout << "个元素，一行是一个元素" << endl;
	cout << "(形如：" << endl << "a b" << endl;
	cout << "b c" << endl;
	cout << "c d" << endl;
	cout << "......" << endl;
	cout << "这样的格式)，按回车键输入下一项：" << endl;

	for (int i = 0; i < m; i++) {
		while (1) {
			char a, b;
			bool judge = 0;  //判断是否需要重新输入
			cout << "请输入第" << i + 1 << "个元素：";

			cin >> a >> b;
			if (cin.fail() || (!isalpha(a)) || (!my_strchr(A, a)) || (!isalpha(b)) || (!my_strchr(A, b))) {
				judge = true;
			}//输入的内容错误
			char c;  //用来获取最后的字符
			if (judge == false && cin.get(c) && c != '\n') {
				judge = true;
			}  //输入的元素个数错误

			if (judge) {
				cin.clear();
				cin.ignore(9999, '\n');
				cout << "输入错误，请重新输入正确的元素。" << endl;
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

// 在集合 A 中查找字符 ch 的索引
int fun(char ch, char*& A)
{
	for (int i = 0; i < n; i++){
		if (ch == A[i]){
			return i;
		}
	}
	return -1;
}

//Warshall 算法的核心部分
void Warshall(char*& A, BR*& R, bool**& tR)
{
	int i, j, k;
	int x, y;
	//用关系矩阵表示二元关系 R
	for (i = 0; i < m; i++){
		x = fun(R[i].a, A);
		y = fun(R[i].b, A);
		tR[x][y] = 1;
	}
	//计算传递闭包的过程
	for (i = 0; i < n; i++){ //检索列
		for (j = 0; j < n; j++){ //检索行
			if (tR[j][i] == 1){
				for (k = 0; k < n; k++){
					tR[j][k] = tR[j][k] + tR[i][k];
				}
			}
		}
	}
}

//将传递闭包 t(R)的关系矩阵表示转化为集合表示
void translation_output(char*& A, bool**& tR)
{
	cout << endl;
	cout << "R 的传递闭包(集合形式)为：" << endl;
	cout << "t(R) = {";

	int num = 0;//闭包中的元素个数
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			if (tR[i][j] == 1)
				num++;
		}
	}
	int k = 0;  //用于计数以判断需不需要输出逗号
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

//主函数
int main()
{
	cout << "********************************************\n";  //标语
	cout << "**                                        **\n";
	cout << "**         欢迎进入用Warshall算法         **\n";
	cout << "**         求解关系的传递闭包程序         **\n";
	cout << "**                                        **\n";
	cout << "********************************************\n\n";
	while (1) {
		char* A;
		init_aggregation(A); //初始化集合 A
		BR* R;
		init_BinaryRelation(R, A); //初始化二元关系
		bool** tR; //传递闭包矩阵
		//动态开辟 bool 类型的二维数组
		tR = new bool* [n];
		for (int i = 0; i < n; i++) {
			tR[i] = new bool[n];
		}
		//初始化二维数组(全部赋值为 0)
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tR[i][j] = 0;
			}
		}
		Warshall(A, R, tR);//调用 Warshall 算法函数
		translation_output(A, tR); //将传递闭包 t(R)的关系矩阵表示转化为集合表示

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
		cout << endl;
		if (answer == 'y' || answer == 'Y')
			continue;
		else if (answer == 'n' || answer == 'N')
			break;
	}
	return 0;
}