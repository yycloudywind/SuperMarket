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


    //初始化顾客信息
    void ProductsInit();
    //初始化商品信息
    void PurchasingLogInit();
    //初始化普通会员信息
    void VipInit();
    //初始化高级会员信息
    void SVipInit();

    //保存数据至文件
    void MessageSave();

    //显示商品信息
    void showProductsList();
    void showProductsList(int n);

    //分类搜索商品
    void searchProducts();
    
    //显示顾客信息
    void showCustomersList();
    void showCustomersList(string _str);

    //添加商品信息
    void addProduct();
    //修改顾客信息
    void changeCustomer();

    //统计销售额
    void calculateSales();

    //删除商品信息
    void delateProduct();
    //删除顾客信息
    void delateCustomer();
    //打印账单
    void printBill(bool fin);
    //获取客户购买信息
    void getPurchasingMessage(Purchasing& pcs, ProductHLH pdt);
    //从列表中获取商品ID
    int findProductInList(long id);
    //从容器中获取商品ID
    int findProductWithID(long id);
    //获取vipID
    int findVipID(long id);
    //获取svipID
    int findSVipID(long id);
    //从列表中查询会员
    bool findSVipOrVipInList(string id);
    //用户购物登录
    bool login();
    //会员查询登录
    bool viplogin();
    //管理员登录
    bool adminlogin();
    //打印会员账单
    void printVipHistory();
    //添加会员
    void addVip();
    //基于对象的删除会员
    void removeVip(VipHLH _v);
    //添加超级会员
    void addSVip();
    void addSVip(VipHLH _v);
    //写入购物日志
    void addPurchasingLog(string _time, double _total_price);
    //清空购物日志容器
    void cleanPurchasingList();
    //查询销售总额
    void showTotalSales();
    //查询会员让利
    void showTotalDiscounts();
    //工具
    double calculate();
    bool isOutDate(string his_time);
    long randomID();
    time_t getTime();
    string time2str(time_t rawtime);
    time_t str2time(string str);

};


#endif //SUPERMARKET_SUPERMARKET_H
