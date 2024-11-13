#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

typedef map<char, int> Map_ci;
typedef map<int, char> Map_ic;
typedef map<int, int> Map_ii;
//typedef map<int, bool> Map_ib;

Map_ci priority;  //�����ȼ�����Ϊȫ�ֱ�����������������Ķ��ʹ��

string getInput();  //��ȡ����Ĺ�ʽ
bool isValidInput(const string& input);  //�����������
Map_ic getProposition(string formula);  //���ڻ�ȡ��ʽ�е��������
int findProposition(Map_ic, char p);  //���ڲ���������������⼯���е�λ��
int pow2(int n);  //����2��n�η�
Map_ii toBinary(int n_proposition, int index);   //��һ������ת��Ϊ�����Ʊ�ʾ
int calculate(string formula, Map_ic pSet, Map_ii value);  //����������������ֵ����µ��߼�������
void check(stack<int>& value, stack<char>& opter);  //�������������ڴ��������ջ��ֵջ

int main()
{
	//��������ȼ�
	priority['('] = 6;
	priority[')'] = 6;
	priority['!'] = 5;
	priority['&'] = 4;
	priority['|'] = 3;
	priority['^'] = 2;
	priority['~'] = 1;

	//�����ӭ��Ϣ
	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         ��ӭ�����߼��������      **\n";
	cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
	cout << "**                                   **\n";
	cout << "**              ��!��ʾ��            **\n";
	cout << "**              ��&��ʾ��            **\n";
	cout << "**              ��|��ʾ��            **\n";
	cout << "**             ��^��ʾ�̺�           **\n";
	cout << "**             ��~��ʾ��ֵ           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";

	while (1)
	{
		bool judge = 1;//judge�����ж��Ƿ��������

		string formula;
		formula = getInput();  //�����ȡ��ʽ
		Map_ic proposition_set = getProposition(formula);  //��ȡ��ʽ�е��������
		cout << endl << "��ʽ���еı�������Ϊ��" << proposition_set.size() << endl << endl << "�����ֵ�����£�" << endl;  //��������������
		for (unsigned int i = 0; i < proposition_set.size(); i++)
		{
			cout << proposition_set[i] << "\t";
		}
		cout << formula << endl;  //�����ֵ��ͷ��
		int* m;  //mΪ�洢��ֵ���������飬���δ�����⹫ʽ�ĸ���(0��1)����������ֵ
		m = (int*)malloc(sizeof(int) * pow2(proposition_set.size()));   //Ϊm�����ڴ�

		/*������ֵ��*/
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

		/*��������ȡ��ʽ������ȡ��ʽ����������*/
		int n_m = 0, n_M = 0;  //�ֱ����ڼ�¼����ȡ��ʽ������ȡ��ʽ������
		cout << endl << "�����⹫ʽ������ȡ��ʽ��" << endl;
		for (int i = 0; i < pow2(proposition_set.size()); i++) {  //���������������ֵ��ϣ�����2^n�����
			if (*(m + i) == 1) {  //�жϵ�ǰֵ����Ƿ���������ȡ��ʽ�������������Ϊ�棨1��
				if (n_m == 0)
					cout << "m<" << i << ">";  //��һ������ȵķ���
				else
					cout << " \\/ m<" << i << "> ";  //��������Ҫ�ȷ���
				n_m++;  //��������ȡ��ʽ����
			}
		}
		if (n_m == 0)
			cout << "0";  //��û�����������ȡ��ʽ�����0
		cout << endl << endl;
		cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
		for (int i = 0; i < pow2(proposition_set.size()); i++) {  //���������������ֵ��ϣ�����2^n�����
			if (*(m + i) == 0) {  //�жϵ�ǰֵ����Ƿ���������ȡ��ʽ�������������Ϊ�٣�0��
				if (n_M == 0)
					cout << "M<" << i << ">";  //��һ������ɵķ���
				else
					cout << " /\\ M<" << i << "> ";  ////��������Ҫ�ɷ���
				n_M++;  //��������ȡ��ʽ����
			}
		}
		if (n_M == 0)
			cout << "0";  //��û�����������ȡ��ʽ�����0
		cout << endl;

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

/*�����������*/
bool isValidInput(const string& input)
{
	int parenthesesCount = 0;  //��¼���ŵĸ���
	bool prevIsLegal = true;  //�����Ž�����ĸ��!��������
	for (size_t i = 0;i < input.size();i++) {
		char c = input[i];
		if (i == 0) {
			if (!(c == '(' || c == '!' || isalpha(c)))
				return false;
			if (c == '(')
				parenthesesCount++;
		}  //��һ���ַ�ֻ���ǣ�,!,��ĸ
		if (i > 0) {  //�ӵڶ����ַ���ʼ���ж�
			if (!(isalpha(c) || c == '(' || c == ')' || c == '!' || c == '&' || c == '|' || c == '^' || c == '~'))
				return false;  //�����жϸ��ַ��Ƿ��Ǳ������
			if (isalpha(c)) {  //��ǰ�ַ�����ĸ
				if (isalpha(input[i - 1]))
					return false;  //�ж�ab�����Ĵ���
			}
			else if (c == '(') {  //��ǰ�ַ���������
				if (!(input[i - 1] == '(' || input[i - 1] == '!' || input[i - 1] == '^' || input[i - 1] == '~' || input[i - 1] == '&' || input[i - 1] == '|'))
					return false;
				parenthesesCount++;  //��¼��������
			}
			else if (c == '!') {  //��ǰ�ַ��ǣ�
				if (i == input.size() - 1 || isalpha(input[i - 1]))
					return false;  //�жϣ������һ���ַ���a!�����Ĵ���
			}
			else if (c == '&' || c == '|' || c == '^' || c == '~') {  //��ǰ�ַ��ǳ����š�������������
				if (!(i != input.size() - 1 || isalpha(input[i - 1]) || input[i - 1] != ')'))
					return false;  //����������������һ���ַ��������ǰֻ������ĸ��
				if (!(isalpha(input[i + 1]) || input[i + 1] == '(' || input[i + 1] == '!'))
					return false;  //���������Ը���ĸ��������
			}
			else if (c == ')') {
				if (parenthesesCount <= 0)
					return false;  //�˴��������ţ���֮ǰ����������
				if (!(isalpha(input[i - 1]) || input[i - 1] == ')'))
					return false;  // )��ǰһ���ַ�����ĸ��
				parenthesesCount--;  //�������ų������������һ��������
			}
		}
	}
	if (parenthesesCount != 0)
		return false;
	else
		return true;
}

/*��ȡ����Ĺ�ʽ*/
string getInput()
{
	while (1) {
		string input;
		cout << "���������⹫ʽ��" << endl;
		cin >> input;
		if (isValidInput(input)) {
			return input;
		}
		else {
			cout << "����������������룡" << endl;
			cin.clear();
			cin.ignore(99999, '\n');
		}
	}
}

/*�ڸ��������⼯�� pSet �в����ַ� p ��Ӧ��������������������±ꡣ*/
int findProposition(Map_ic pSet, char p) //����-1����ʾ�����������δ�����������ɼ���������˵������������ѱ������������ظ����������⣬�����Է���ָ�����������±�
{
	Map_ic::iterator it = pSet.begin();  //������һ��������it�������ʼ��Ϊ���⼯�� pSet �ĵ�һ��Ԫ��
	while (it != pSet.end()) {
		if (it->second == p)  //��鵱ǰ������ָ���Ԫ�ص�second��Ա�����ַ����Ƿ����������ַ� p
			return it->first;  //����򷵻ظ����������pSet�е�λ��/�±꣨��first��Ա��
		it++;  //������������ƣ���������
	}
	return -1;  //���û�ҵ����򷵻�-1
}

/*�Ӹ������߼���ʽformula����ȡ���������������洢��һ��ӳ��proposition�У����շ��ظ�ӳ��*/
Map_ic getProposition(string formula) //�ú������������빫ʽ�е��������(�����������)
{
	Map_ic proposition;  //���ڴ洢�������
	int n_proposition = 0;  //���ڼ�¼��������ĸ���
	for (unsigned int i = 0; i < formula.length(); i++) {  //����������߼���ʽformula�е�ÿ���ַ�
		char c = formula[i];  //ÿ��ѭ���У���c��¼��ǰ�ַ�
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {  //��⵱ǰ�ַ��Ƿ�Ϊ��ĸ
			int r = findProposition(proposition, c);  //���Ҹ���������Ƿ��Ѿ���proposition�д���
			//cout << r << endl;
			if (r == -1) {
				//˵�������������δ��������
				proposition[n_proposition] = c;  //������������洢��propositionӳ���У���Ϊn_proposition������ǰ����������ĸ�����
				n_proposition++;  //������������ĸ���
			}
		}
		else if (!priority.count(c)) {  //count������map�ĳ�Ա���������ڼ����ӳ�����Ƿ�����ض��ļ�c
			cout << c << " is undefined!" << endl;  //˵���ַ�c�ǲ��Ϸ���
			exit(2);  //�˳�����
		}
	}
	return proposition;  //���ش洢�����������ӳ�� proposition
}

/*��һ������indexת��Ϊ���� n_proposition ��������λ��ӳ�䣬���ڱ�ʾ������������п���ȡֵ���*/
Map_ii toBinary(int n_proposition, int index)  //�ú��������������Ķ�����(0��1)ȡֵ
{
	Map_ii result;  //���ڴ洢�����Ʊ�ʾ���������
	for (int i = 0; i < n_proposition; i++) {
		int r = index % 2;
		result[n_proposition - 1 - i] = r;  //���Ӹ�λ����λ���δ洢
		index = index / 2;  //�� index ���� 2���൱�ڽ� index ����һλ���Ի�ȡ��һ��������λ��ֵ
	}  //�������ɶ����Ʊ�ʾ
	return result;  //���ش洢�˶����Ʊ�ʾ��ӳ�� result
}

/*����2��n�η�*/
int pow2(int n)
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}

/*����������������ֵ���value�µ��߼�������*/
int calculate(string formula, Map_ic pSet, Map_ii value) {
	stack<char> opter;  //�����ջ
	stack<int> pvalue;  //ֵջ

	for (unsigned int i = 0; i < formula.length(); i++) {
		char c = formula[i];  //������ʽ��ÿ���ַ�

		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			pvalue.push(value[findProposition(pSet, c)]);
		}  //�����ǰ�ַ�����ĸ������������������Ӧ��ֵѹ��ֵջ��
		else {  //��ǰ�ַ��������
			if (opter.empty() || c == '(' || priority[c] > priority[opter.top()]) {
				opter.push(c);  //�������ջΪ�ջ�ǰ�ַ��������Ż�ǰ���������Ȩ���������ջ���ͽ���ǰ�����ѹ��ջ��
			}
			else {
				while (!opter.empty() && opter.top() != '(' && priority[opter.top()] >= priority[c]) {
					check(pvalue, opter);  //���򲻶����㣬ֱ��������������
				}
				opter.push(c);  //ѹ���ջ
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

/*�������ջ opter ��ֵջ value ��ִ���߼��������*/
void check(stack<int>& value, stack<char>& opter) //�ú������������������(ȡֵ0��1)�ĸ���������(0��1)
{
	int p, q, result;
	char opt = opter.top();  //��ȡ�����ջ����Ԫ��
	/*��������������ͽ�����Ӧ���߼�����*/
	switch (opt) {
		/*�߼�������*/
		case '&':
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();  //��ֵջ�е�������ֵp��q���ֱ��ʾ���롯���������������
			result = int(p && q);  //����p��q�Ľ��
			value.push(result);  //�����ѹ��ֵջvalue
			opter.pop();  //���������ջ���������
			break;

			/*�߼�������*/
		case '|':
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();  //��ֵջ�е�������ֵp��q���ֱ��ʾ�������������������
			result = int(p || q);  //����p��q�Ľ��
			value.push(result);  //�����ѹ��ֵջvalue
			opter.pop();  //���������ջ���������
			break;

			/*�߼�������*/
		case '!':
			p = value.top();
			value.pop();  //��ֵջ�е���һ��ֵp����ʾ���ǡ�����Ĳ�����
			result = int(!p);  //�����p�Ľ��
			value.push(result);  //�����ѹ��ֵջvalue
			opter.pop();  //���������ջ���������
			break;

			/*�߼��̺�����*/
		case '^':
			q = value.top();
			value.pop();
			p = value.top();
			value.pop();  //��ֵջ�е�������ֵp��q���ֱ��ʾ���̺������������������
			result = int(!p || q);  //����p�̺�q�Ľ��
			value.push(result);  //�����ѹ��ֵջvalue
			opter.pop();  //���������ջ���������
			break;

			/*�߼���ֵ����*/
		case '~':
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();  //��ֵջ�е�������ֵp��q���ֱ��ʾ���̺������������������
			result = (!p || q) && (p || !q);  //������
			value.push(result);  //�����ѹ��ֵջvalue
			opter.pop();  //���������ջ���������
			break;

			/*������*/
		case '(':
			break;  //�����κβ���

			/*������*/
		case ')':
			opter.pop();
			while (opter.top() != '(') {
				check(value, opter);
			}  //���������ջ���������ֱ�����������ţ�������Ӧ���߼�����
			if (opter.top() == '(')
				opter.pop();  //��������Ŵ������ջ�е���
			break;

			/*����Ĭ�����*/
		default:
			break;
	}
}