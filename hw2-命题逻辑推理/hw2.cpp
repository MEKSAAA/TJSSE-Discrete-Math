#include <iostream>
using namespace std;

int main()
{
	/* A:ӪҵԱA͵���ֱ�
	   B:ӪҵԱB͵���ֱ�
	   C:��������Ӫҵʱ��
	   D:B�ṩ��֤����ȷ
	   E:����δ����       */
	int A, B, C, D, E;
	for (A = 0;A <= 1;A++)
		for (B = 0;B <= 1;B++)
			for (C = 0;C <= 1;C++)
				for (D = 0;D <= 1;D++)
					for (E = 0;E <= 1;E++)
						if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E) {
							cout << "A=" << A << ", B=" << B << endl;
							if (A) cout << "A͵���ֱ�" << endl;
							if (B) cout << "B͵���ֱ�" << endl;
						}
	return 0;
}
