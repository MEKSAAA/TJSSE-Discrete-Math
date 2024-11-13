#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;

void dealInputError(int& n, string str, int min = 0, int max = 1)  //�����������
{
    while (1) {
        char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
        cout << str << endl;
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
    bool a[4] = { 0 };  //���������
    int i = -1, j = -1;  //��i,j�ֱ��ʾP,Q
    char s;  //��ȡ�Ƿ����

    cout << "***************************************" << endl;
    cout << "**                                   **" << endl;
    cout << "**        ��ӭ�����߼��������       **" << endl;
    cout << "**                                   **" << endl;
    cout << "***************************************" << endl << endl;

    while (1)
    {
        bool judge = 1;//judge�����ж��Ƿ��������

        //��ȡP��ֵ
        dealInputError(i, "������P��ֵ��0��1��,�Իس�����:");
        //��ȡQ��ֵ
        dealInputError(j, "������Q��ֵ��0��1��,�Իس�����:");

        a[0] = i && j;  //��ȡ
        a[1] = i || j;  //��ȡ
        a[2] = (!i) || j;  //������ת��Ϊ������ʽ
        a[3] = ((!i) || j) && ((!j) || i);  //˫��������ת��Ϊ������ʽ

        //������
        cout << endl << endl << "��ȡ: P/\\Q = " << a[0] << endl;
        cout << "��ȡ: P\\/Q = " << a[1] << endl;
        cout << "����: P->Q = " << a[2] << endl;
        cout << "˫������: P<->Q = " << a[3] << endl << endl;

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