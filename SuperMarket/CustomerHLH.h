/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#ifndef SUPERMARKET_CUSTOMER_H
#define SUPERMARKET_CUSTOMER_H

#include<iostream>
#include<string>
#include<ctime>
#include<vector>
#include<iomanip>

using namespace std;

class CustomerHLH {
public:
    CustomerHLH() {};
    void customersinfo();    

    string id;
};

class VipHLH : public CustomerHLH {
public:
    VipHLH() { score = 0; }

    void vipinfo();
    void vipinfo(string _str);

    string ID;
    string name;
    string tel;
    int score;
};

class SVipHLH : public VipHLH {
public:
    SVipHLH() { score = 0; }
    void svipinfo();
    void svipinfo(string _str);

    string viceID;
};

#endif //SUPERMARKET_CUSTOMER_H
