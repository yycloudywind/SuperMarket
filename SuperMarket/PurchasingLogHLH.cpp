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
    char* c = (char*)str.data();               // ��stringת����char*��
    tm tm_;                                    // ����tm�ṹ�塣
    int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
    sscanf(c, "%d/%d/%d-%d:%d:%d", &year, &month, &day, &hour, &minute, &second);// ��string�洢������ʱ�䣬ת��Ϊint��ʱ������
    tm_.tm_year = year - 1900;                 // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��
    tm_.tm_mon = month - 1;                        // �¡�
    tm_.tm_mday = day;                         // �ա�
    tm_.tm_hour = hour;                        // ʱ��
    tm_.tm_min = minute;                       // �֡�
    tm_.tm_sec = second;                       // �롣
    //tm_.tm_isdst = 0;                          // ������ʱ��
    time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
    return t_;                                 // ����ֵ��
}

bool PurchasingLog::timeLimit(string str)
{
    time_t now_time = getTime();
    time_t log_time = str2time(str);
    time_t dif_time = difftime(now_time, log_time);
    if (dif_time >= 31536000) return false;
    else return true;
}