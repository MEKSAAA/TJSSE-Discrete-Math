#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

typedef map<char, int> Map_ci;
typedef map<int, char> Map_ic;
typedef map<int, int> Map_ii;
//typedef map<int, bool> Map_ib;

Map_ci priority;  //将优先级定义为全局变量，方便整个程序的多次使用

string getInput();  //获取输入的公式
bool isValidInput(const string& input);  //处理输入错误
Map_ic getProposition(string formula);  //用于获取公式中的命题变量
int findProposition(Map_ic, char p);  //用于查找命题变量在命题集合中的位置
int pow2(int n);  //计算2的n次方
Map_ii toBinary(int n_proposition, int index);   //将一个整数转化为二进制表示
int calculate(string formula, Map_ic pSet, Map_ii value);  //计算给定命题变量的值组合下的逻辑运算结果
void check(stack<int>& value, stack<char>& opter);  //辅助函数，用于处理运算符栈和值栈

int main()
{
	//运算符优先级
	priority['('] = 6;
	priority[')'] = 6;
	priority['!'] = 5;
	priority['&'] = 4;
	priority['|'] = 3;
	priority['^'] = 2;
	priority['~'] = 1;

	//输出欢迎信息
	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         欢迎进入逻辑运算软件      **\n";
	cout << "**   (可运算真值表,主范式,支持括号)  **\n";
	cout << "**                                   **\n";
	cout << "**              用!表示非            **\n";
	cout << "**              用&表示与            **\n";
	cout << "**              用|表示或            **\n";
	cout << "**             用^表示蕴含           **\n";
	cout << "**             用~表示等值           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";

	while (1)
	{
		bool judge = 1;//judge用来判断是否继续输入

		string formula;
		formula = getInput();  //输入获取公式
		Map_ic proposition_set = getProposition(formula);  //获取公式中的命题变量
		cout << endl << "该式子中的变量个数为：" << proposition_set.size() << endl << endl << "输出真值表如下：" << endl;  //输出命题变量个数
		for (unsigned int i = 0; i < proposition_set.size(); i++)
		{
			cout << proposition_set[i] << "\t";
		}
		cout << formula << endl;  //输出真值表头部
		int* m;  //m为存储真值表结果的数组，依次存放命题公式的各行(0或1)的运算结果的值
		m = (int*)malloc(sizeof(int) * pow2(proposition_set.size()));   //为m分配内存

		/*计算真值表*/
		for (int i = 0; i < pow2(proposition_set.size()); i++)
		{
			Map_ii bina_set = toBinary(proposition_set.size(), i);
			for (unsigned int j = 0; j < bina_set.size(); j++)
			{
				cout << bina_set[j] << "\t";
			}
			int result = calculate(formula, proposition_set, bina_set);
			//m[i] = result;
			*(m + i) = result;
			cout << result << endl;
		}

		/*计算主析取范式和主合取范式，并输出结果*/
		int n_m = 0, n_M = 0;  //分别用于记录主析取范式和主合取范式的数量
		cout << endl << "该命题公式的主析取范式：" << endl;
		for (int i = 0; i < pow2(proposition_set.size()); i++) {  //遍历所有命题变量值组合，共有2^n种情况
			if (*(m + i) == 1) {  //判断当前值组合是否满足主析取范式的条件，即结果为真（1）
				if (n_m == 0)
					cout << "m<" << i << ">";  //第一项无需∪的符号
				else
					cout << " \\/ m<" << i << "> ";  //后续项需要∪符号
				n_m++;  //增加主析取范式数量
			}
		}
		if (n_m == 0)
			cout << "0";  //若没有满足的主析取范式，输出0
		cout << endl << endl;
		cout << "该命题公式的主合取范式：" << endl;
		for (int i = 0; i < pow2(proposition_set.size()); i++) {  //遍历所有命题变量值组合，共有2^n种情况
			if (*(m + i) == 0) {  //判断当前值组合是否满足主析取范式的条件，即结果为假（0）
				if (n_M == 0)
					cout << "M<" << i << ">";  //第一项无需∩的符号
				else
					cout << " /\\ M<" << i << "> ";  ////后续项需要∩符号
				n_M++;  //增加主合取范式数量
			}
		}
		if (n_M == 0)
			cout << "0";  //若没有满足的主合取范式，输出0
		cout << endl;

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

/*处理输入错误*/
bool isValidInput(const string& input)
{
	int parenthesesCount = 0;  //记录括号的个数
	bool prevIsLegal = true;  //左括号紧跟字母或!或左括号
	for (size_t i = 0;i < input.size();i++) {
		char c = input[i];
		if (i == 0) {
			if (!(c == '(' || c == '!' || isalpha(c)))
				return false;
			if (c == '(')
				parenthesesCount++;
		}  //第一个字符只能是（,!,字母
		if (i > 0) {  //从第二个字符开始的判断
			if (!(isalpha(c) || c == '(' || c == ')' || c == '!' || c == '&' || c == '|' || c == '^' || c == '~'))
				return false;  //首先判断该字符是否是被允许的
			if (isalpha(c)) {  //当前字符是字母
				if (isalpha(input[i - 1]))
					return false;  //判断ab这样的错误
			}
			else if (c == '(') {  //当前字符是左括号
				if (!(input[i - 1] == '(' || input[i - 1] == '!' || input[i - 1] == '^' || input[i - 1] == '~' || input[i - 1] == '&' || input[i - 1] == '|'))
					return false;
				parenthesesCount++;  //记录左括号数
			}
			else if (c == '!') {  //当前字符是！
				if (i == input.size() - 1 || isalpha(input[i - 1]))
					return false;  //判断！在最后一个字符、a!这样的错误
			}
			else if (c == '&' || c == '|' || c == '^' || c == '~') {  //当前字符是除括号、！以外的运算符
				if (!(i != input.size() - 1 || isalpha(input[i - 1]) || input[i - 1] != ')'))
					return false;  //运算符不可以是最后一个字符，运算符前只能是字母或）
				if (!(isalpha(input[i + 1]) || input[i + 1] == '(' || input[i + 1] == '!'))
					return false;  //运算符后可以跟字母、（、！
			}
			else if (c == ')') {
				if (parenthesesCount <= 0)
					return false;  //此处是右括号，则之前必有左括号
				if (!(isalpha(input[i - 1]) || input[i - 1] == ')'))
					return false;  // )的前一个字符是字母或）
				parenthesesCount--;  //有右括号出现则可以消除一个左括号
			}
		}
	}
	if (parenthesesCount != 0)
		return false;
	else
		return true;
}

/*获取输入的公式*/
string getInput()
{
	while (1) {
		string input;
		cout << "请输入命题公式：" << endl;
		cin >> input;
		if (isValidInput(input)) {
			return input;
		}
		else {
			cout << "输入错误，请重新输入！" << endl;
			cin.clear();
			cin.ignore(99999, '\n');
		}
	}
}

/*在给定的命题集合 pSet 中查找字符 p 对应的命题变量，并返回其下标。*/
int findProposition(Map_ic pSet, char p) //返回-1，表示该命题变项尚未被遍历过，可计数；否则说明该命题变项已被遍历过，则不重复计数。另外，还可以返回指定命题变项的下标
{
	Map_ic::iterator it = pSet.begin();  //定义了一个迭代器it并将其初始化为命题集合 pSet 的第一个元素
	while (it != pSet.end()) {
		if (it->second == p)  //检查当前迭代器指向的元素的second成员（即字符）是否等于输入的字符 p
			return it->first;  //相等则返回该命题变量在pSet中的位置/下标（即first成员）
		it++;  //否则迭代器后移，继续查找
	}
	return -1;  //如果没找到，则返回-1
}

/*从给定的逻辑公式formula中提取命题变量，并将其存储在一个映射proposition中，最终返回该映射*/
Map_ic getProposition(string formula) //该函数返回所输入公式中的命题变项(不包括运算符)
{
	Map_ic proposition;  //用于存储命题变量
	int n_proposition = 0;  //用于记录命题变量的个数
	for (unsigned int i = 0; i < formula.length(); i++) {  //遍历输入的逻辑公式formula中的每个字符
		char c = formula[i];  //每次循环中，用c记录当前字符
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {  //检测当前字符是否为字母
			int r = findProposition(proposition, c);  //查找该命题变量是否已经在proposition中存在
			//cout << r << endl;
			if (r == -1) {
				//说明该命题变项尚未被遍历过
				proposition[n_proposition] = c;  //将该命题变量存储在proposition映射中，键为n_proposition（即当前的命题变量的个数）
				n_proposition++;  //增加命题变量的个数
			}
		}
		else if (!priority.count(c)) {  //count函数是map的成员函数，用于检查在映射中是否存在特定的键c
			cout << c << " is undefined!" << endl;  //说明字符c是不合法的
			exit(2);  //退出程序
		}
	}
	return proposition;  //返回存储了命题变量的映射 proposition
}

/*将一个整数index转化为包含 n_proposition 个二进制位的映射，用于表示命题变量的所有可能取值情况*/
Map_ii toBinary(int n_proposition, int index)  //该函数返回命题变项的二进制(0或1)取值
{
	Map_ii result;  //用于存储二进制表示的命题变量
	for (int i = 0; i < n_proposition; i++) {
		int r = index % 2;
		result[n_proposition - 1 - i] = r;  //按从高位到低位依次存储
		index = index / 2;  //将 index 除以 2，相当于将 index 右移一位，以获取下一个二进制位的值
	}  //用于生成二进制表示
	return result;  //返回存储了二进制表示的映射 result
}

/*计算2的n次方*/
int pow2(int n)
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}

/*计算给定命题变量的值组合value下的逻辑运算结果*/
int calculate(string formula, Map_ic pSet, Map_ii value) {
	stack<char> opter;  //运算符栈
	stack<int> pvalue;  //值栈

	for (unsigned int i = 0; i < formula.length(); i++) {
		char c = formula[i];  //遍历公式中每个字符

		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			pvalue.push(value[findProposition(pSet, c)]);
		}  //如果当前字符是字母（命题变量），则将其对应的值压入值栈中
		else {  //当前字符是运算符
			if (opter.empty() || c == '(' || priority[c] > priority[opter.top()]) {
				opter.push(c);  //当运算符栈为空或当前字符是左括号或当前运算符优先权高于运算符栈顶就将当前运算符压入栈中
			}
			else {
				while (!opter.empty() && opter.top() != '(' && priority[opter.top()] >= priority[c]) {
					check(pvalue, opter);  //否则不断运算，直到符合上述条件
				}
				opter.push(c);  //压入符栈
			}
		}

		if (i == formula.length() - 1 && (!opter.empty())) {
			while (!opter.empty()) {
				check(pvalue, opter);
			}
		}
	}

	return pvalue.top();
}

/*在运算符栈 opter 和值栈 value 上执行逻辑运算操作*/
void check(stack<int>& value, stack<char>& opter) //该函数返回两个命题变项(取值0或1)的各种运算结果(0或1)
{
	int p, q, result;
	char opt = opter.top();  //获取运算符栈顶的元素
	/*根据运算符的类型进行相应的逻辑运算*/
	switch (opt) {
		/*逻辑与运算*/
		case '&':
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();  //从值栈中弹出两个值p和q，分别表示‘与’运算的两个操作数
			result = int(p && q);  //计算p与q的结果
			value.push(result);  //将结果压入值栈value
			opter.pop();  //弹出运算符栈顶的运算符
			break;

			/*逻辑或运算*/
		case '|':
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();  //从值栈中弹出两个值p和q，分别表示‘或’运算的两个操作数
			result = int(p || q);  //计算p或q的结果
			value.push(result);  //将结果压入值栈value
			opter.pop();  //弹出运算符栈顶的运算符
			break;

			/*逻辑非运算*/
		case '!':
			p = value.top();
			value.pop();  //从值栈中弹出一个值p，表示‘非’运算的操作数
			result = int(!p);  //计算非p的结果
			value.push(result);  //将结果压入值栈value
			opter.pop();  //弹出运算符栈顶的运算符
			break;

			/*逻辑蕴含运算*/
		case '^':
			q = value.top();
			value.pop();
			p = value.top();
			value.pop();  //从值栈中弹出两个值p和q，分别表示‘蕴含’运算的两个操作数
			result = int(!p || q);  //计算p蕴含q的结果
			value.push(result);  //将结果压入值栈value
			opter.pop();  //弹出运算符栈顶的运算符
			break;

			/*逻辑等值运算*/
		case '~':
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();  //从值栈中弹出两个值p和q，分别表示‘蕴含’运算的两个操作数
			result = (!p || q) && (p || !q);  //计算结果
			value.push(result);  //将结果压入值栈value
			opter.pop();  //弹出运算符栈顶的运算符
			break;

			/*左括号*/
		case '(':
			break;  //不做任何操作

			/*右括号*/
		case ')':
			opter.pop();
			while (opter.top() != '(') {
				check(value, opter);
			}  //弹出运算符栈顶的运算符直至遇到左括号，进行相应的逻辑运算
			if (opter.top() == '(')
				opter.pop();  //最后将左括号从运算符栈中弹出
			break;

			/*其余默认情况*/
		default:
			break;
	}
}