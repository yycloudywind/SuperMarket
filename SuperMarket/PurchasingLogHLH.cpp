/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#include "PurchasingLogHLH.h"

bool PurchasingLog::cleanPurchasingLog()
{
	ID = "";
	time_str = "";
	total_price = 0;
	vector<HisPurchasingList>().swap(his_purchasing_list);
	return true;
}

time_t PurchasingLog::getTime()
{
    time_t rawtime;
    time(&rawtime);
    return rawtime;
}

string PurchasingLog::time2str(time_t rawtime)
{
    struct tm* ptr_tm_info;
    ptr_tm_info = localtime(&rawtime);
    string timestr =
        to_string(ptr_tm_info->tm_year + 1900) + "/" +
        to_string(ptr_tm_info->tm_mon + 1) + "/" +
        to_string(ptr_tm_info->tm_mday) + "-" +
        to_string(ptr_tm_info->tm_hour / 10) + to_string(ptr_tm_info->tm_hour % 10) + ':' +
        to_string(ptr_tm_info->tm_min / 10) + to_string(ptr_tm_info->tm_min % 10) + ':' +
        to_string(ptr_tm_info->tm_sec / 10) + to_string(ptr_tm_info->tm_sec % 10);
    return timestr;
}

time_t PurchasingLog::str2time(string str)
{
    char* c = (char*)str.data();               // 将string转换成char*。
    tm tm_;                                    // 定义tm结构体。
    int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
    sscanf(c, "%d/%d/%d-%d:%d:%d", &year, &month, &day, &hour, &minute, &second);// 将string存储的日期时间，转换为int临时变量。
    tm_.tm_year = year - 1900;                 // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
    tm_.tm_mon = month - 1;                        // 月。
    tm_.tm_mday = day;                         // 日。
    tm_.tm_hour = hour;                        // 时。
    tm_.tm_min = minute;                       // 分。
    tm_.tm_sec = second;                       // 秒。
    //tm_.tm_isdst = 0;                          // 非夏令时。
    time_t t_ = mktime(&tm_);                  // 将tm结构体转换成time_t格式。
    return t_;                                 // 返回值。
}

bool PurchasingLog::timeLimit(string str)
{
    time_t now_time = getTime();
    time_t log_time = str2time(str);
    time_t dif_time = difftime(now_time, log_time);
    if (dif_time >= 31536000) return false;
    else return true;
}