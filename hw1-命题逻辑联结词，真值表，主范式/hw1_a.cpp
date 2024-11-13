#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;

void dealInputError(int& n, string str, int min = 0, int max = 1)  //处理输入错误
{
    while (1) {
        char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
        cout << str << endl;
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
    bool a[4] = { 0 };  //存放运算结果
    int i = -1, j = -1;  //用i,j分别表示P,Q
    char s;  //读取是否结束

    cout << "***************************************" << endl;
    cout << "**                                   **" << endl;
    cout << "**        欢迎进入逻辑运算程序       **" << endl;
    cout << "**                                   **" << endl;
    cout << "***************************************" << endl << endl;

    while (1)
    {
        bool judge = 1;//judge用来判断是否继续输入

        //读取P的值
        dealInputError(i, "请输入P的值（0或1）,以回车结束:");
        //读取Q的值
        dealInputError(j, "请输入Q的值（0或1）,以回车结束:");

        a[0] = i && j;  //合取
        a[1] = i || j;  //析取
        a[2] = (!i) || j;  //条件，转化为与或非形式
        a[3] = ((!i) || j) && ((!j) || i);  //双向条件，转化为与或非形式

        //输出结果
        cout << endl << endl << "合取: P/\\Q = " << a[0] << endl;
        cout << "析取: P\\/Q = " << a[1] << endl;
        cout << "条件: P->Q = " << a[2] << endl;
        cout << "双向条件: P<->Q = " << a[3] << endl << endl;

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