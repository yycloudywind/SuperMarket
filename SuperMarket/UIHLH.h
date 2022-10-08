/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#ifndef UI_H
#define UI_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class UIHLH
{
public:
	void setTitle(string str);
	void setLineSize(int _size);
	void setLineStr(string str, int num);
	void showUI();
private:
	string line_title;
	string line[25];
	int line_size;
};


#endif // !UI_H

