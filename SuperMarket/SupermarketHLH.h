/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#ifndef SUPERMARKET_SUPERMARKET_H
#define SUPERMARKET_SUPERMARKET_H

constexpr auto Products_path = "ProductLog.txt";
constexpr auto PurchasingLog_path = "PurchasingLog.txt";
constexpr auto VIP_path = "Vip.txt";
constexpr auto SVIP_path = "SVip.txt";

#define _CRT_SECURE_NO_WARNINGS
#include "ProductHLH.h"
#include "CustomerHLH.h"
#include "PurchasingLogHLH.h"
#include <ctime>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Purchasing
{
    long id;
    string name;
    double price;
    int num;
};

class SupermarketHLH {
public:
    SupermarketHLH();

    vector<Purchasing> purchasing_list;
    vector<PurchasingLog> purchasing_log_list;
    vector<ProductHLH> products;
    vector<CustomerHLH> customers;
    vector<VipHLH>vip;
    vector<SVipHLH>svip;

    int category;
    long currentID;

    string path;

    double bill;
    double discount;
    double total_sale;


    //��ʼ���˿���Ϣ
    void ProductsInit();
    //��ʼ����Ʒ��Ϣ
    void PurchasingLogInit();
    //��ʼ����ͨ��Ա��Ϣ
    void VipInit();
    //��ʼ���߼���Ա��Ϣ
    void SVipInit();

    //�����������ļ�
    void MessageSave();

    //��ʾ��Ʒ��Ϣ
    void showProductsList();
    void showProductsList(int n);

    //����������Ʒ
    void searchProducts();
    
    //��ʾ�˿���Ϣ
    void showCustomersList();
    void showCustomersList(string _str);

    //�����Ʒ��Ϣ
    void addProduct();
    //�޸Ĺ˿���Ϣ
    void changeCustomer();

    //ͳ�����۶�
    void calculateSales();

    //ɾ����Ʒ��Ϣ
    void delateProduct();
    //ɾ���˿���Ϣ
    void delateCustomer();
    //��ӡ�˵�
    void printBill(bool fin);
    //��ȡ�ͻ�������Ϣ
    void getPurchasingMessage(Purchasing& pcs, ProductHLH pdt);
    //���б��л�ȡ��ƷID
    int findProductInList(long id);
    //�������л�ȡ��ƷID
    int findProductWithID(long id);
    //��ȡvipID
    int findVipID(long id);
    //��ȡsvipID
    int findSVipID(long id);
    //���б��в�ѯ��Ա
    bool findSVipOrVipInList(string id);
    //�û������¼
    bool login();
    //��Ա��ѯ��¼
    bool viplogin();
    //����Ա��¼
    bool adminlogin();
    //��ӡ��Ա�˵�
    void printVipHistory();
    //��ӻ�Ա
    void addVip();
    //���ڶ����ɾ����Ա
    void removeVip(VipHLH _v);
    //��ӳ�����Ա
    void addSVip();
    void addSVip(VipHLH _v);
    //д�빺����־
    void addPurchasingLog(string _time, double _total_price);
    //��չ�����־����
    void cleanPurchasingList();
    //��ѯ�����ܶ�
    void showTotalSales();
    //��ѯ��Ա����
    void showTotalDiscounts();
    //����
    double calculate();
    bool isOutDate(string his_time);
    long randomID();
    time_t getTime();
    string time2str(time_t rawtime);
    time_t str2time(string str);

};


#endif //SUPERMARKET_SUPERMARKET_H
