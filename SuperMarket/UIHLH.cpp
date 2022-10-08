/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#include "UIHLH.h"

void UIHLH::setTitle(string str)
{
    line_title = str;
}

void UIHLH::setLineSize(int _size)
{
    if (_size < 20)
    {
        line_size = _size;
    }
    else
    {
        line_size = 20;
        cout << "invaild line size!!!";
    }
}

void UIHLH::setLineStr(string str, int num)
{
	line[num] = str;
}

void UIHLH::showUI()
{
    system("cls");
    cout << setfill('#') << setw(40) << "#" << endl;
    int tag_num = (40 - line_title.size()) / 2;
    for (int i = 1; i <= tag_num; i++)
        cout << "#";
    cout << line_title;
    for (int i = 1; i <= tag_num; i++)
        cout << "#";
    cout << endl;
    for (int i = 1; i <= line_size; i++)
    {
        cout << setfill(' ') << left;
        cout << "#             " << i << "." << setw(23) << line[i] << "#" << endl;
    }
    cout << "#             0.·µ»Ø                   #" << endl;
    cout << setfill('#') << setw(40) << "#" << endl;
}