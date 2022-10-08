/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#include "CustomerHLH.h"

void VipHLH::vipinfo()
{
    cout << "========会员信息=========" << endl << setfill(' ') << left;
    cout << "=         ID: " << setw(10) << ID << "=" << endl;
    cout << "=       姓名: " << setw(10) << name << "=" << endl;
    cout << "=   电话号码: " << setw(10) << tel << "=" << endl;
    cout << "=   会员积分: " << setw(10) << score << "=" << endl;
    cout << "=========================" << endl;
}

void VipHLH::vipinfo(string _str)
{
    cout << setfill(' ') << left;
    cout << "=ID: " << setw(10) << ID;
    cout << "姓名: " << setw(10) << name;
    cout << "电话号码: " << setw(10) << tel;
    cout << "会员积分: " << setw(10) << score;
}

void SVipHLH::svipinfo()
{
    cout << "=======超级会员信息======" << endl << setfill(' ') << left;
    cout << "=         ID: " << setw(10) << ID << "=" << endl;
    cout << "=       姓名: " << setw(10) << name << "=" << endl;
    cout << "=   电话号码: " << setw(10) << tel << "=" << endl;
    cout << "=     副卡ID: " << setw(10) << viceID << "=" << endl;
    cout << "=   会员积分: " << setw(10) << score << "=" << endl;
    cout << "=========================" << endl;
}

void SVipHLH::svipinfo(string _str)
{
    cout << setfill(' ') << left;
    cout << "=ID: " << setw(10) << ID;
    cout << "姓名: " << setw(10) << name;
    cout << "电话号码: " << setw(10) << tel;
    cout << "副卡ID: " << setw(10) << viceID;
    cout << "会员积分: " << setw(10) << score;
}

void CustomerHLH::customersinfo()
{
    cout << "         ID: " << id << endl;
}