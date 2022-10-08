/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#ifndef SUPERMARKET_PURCHASINGLOG_H
#define SUPERMARKET_PURCHASINGLOG_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

struct HisPurchasingList
{
	string name;
	double price;
	int num;
};

class PurchasingLog
{
public:
	PurchasingLog() { total_price = 0; };
	vector<HisPurchasingList> his_purchasing_list;
	string ID;
	string time_str;
	double total_price;

	static time_t getTime();
	static string time2str(time_t rawtime);
	static time_t str2time(string str);

	bool cleanPurchasingLog();
	static bool timeLimit(string str);
};

#endif //SUPERMARKET_PURCHASINGLOG_H