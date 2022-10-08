/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#include "SupermarketHLH.h"

using namespace std;


void SupermarketHLH::PurchasingLogInit()
{
    path = PurchasingLog_path;
    ifstream file;
    file.open(this->path.c_str());
    if (file.is_open())
    {     
        int _num = -1, _tag = 0;
        PurchasingLog plog;
        while (file.peek() != EOF)//循环读取每一行
        {
            char tag;
            file >> tag;
            if (tag == '@')
            {
                plog.cleanPurchasingLog();
                file >> plog.ID >> plog.total_price >> plog.time_str >> _num;
                _tag = 0;
                if (!PurchasingLog::timeLimit(plog.time_str)) continue;
            }
            else if (tag == '#')
            {
                HisPurchasingList hplist;
                file >> hplist.name >> hplist.num >> hplist.price;
                plog.his_purchasing_list.push_back(hplist);
                if (++_tag == _num) purchasing_log_list.push_back(plog);
            }
        }
        //while(true);
    }
    else
        cout << "Log Init Error" << endl;
}

void SupermarketHLH::ProductsInit()
{
    path = Products_path;
    ifstream file;
    ProductHLH __p;
    file.open(this->path.c_str());
    if (file.is_open())
    {
        for (int i = 0; file.peek() != EOF; i++)//循环读取每一行
        {
            products.push_back(ProductHLH::inputProduct(file));
        }
    }
    else
        cout << "Products Init Error" << endl;
}

void SupermarketHLH::VipInit()
{
    path = VIP_path;
    ifstream file;
    file.open(this->path.c_str());
    if (file.is_open())
    {
        for (int i = 0; file.peek() != EOF; i++)//循环读取每一行
        {
            VipHLH _vip;
            file >> _vip.ID >> _vip.name >> _vip.tel >> _vip.score;
            if(findSVipOrVipInList(_vip.ID))
                vip.push_back(_vip);
        }
    }
    else
        cout << "User Init Error" << endl;
}

void SupermarketHLH::SVipInit()
{
    path = SVIP_path;
    ifstream file;
    file.open(this->path.c_str());
    if (file.is_open())
    {
        for (int i = 0; file.peek() != EOF; i++)//循环读取每一行
        {
            SVipHLH _svip;
            file >> _svip.ID >> _svip.name >> _svip.tel >> _svip.score >> _svip.viceID;
            if (findSVipOrVipInList(_svip.ID))
                svip.push_back(_svip);
        }
    }
    else
        cout << "User Init Error" << endl;
}

SupermarketHLH::SupermarketHLH()
{
    bill = 0;
    total_sale = 0;
    ProductsInit();
    PurchasingLogInit();
    VipInit();
    SVipInit();
}

void SupermarketHLH::MessageSave()
{
    ofstream f1;
    f1.open(PurchasingLog_path, ios::ate);
    if (f1.is_open())
    {
        for (int i = 0; i < purchasing_log_list.size(); ++i)
        {
            if (isOutDate(purchasing_log_list[i].time_str)) continue;
            f1  << "@" << " "
                << purchasing_log_list[i].ID << " "
                << purchasing_log_list[i].total_price << " " 
                << purchasing_log_list[i].time_str << " "
                << purchasing_log_list[i].his_purchasing_list.size();
            for (int j = 0; j < purchasing_log_list[i].his_purchasing_list.size(); j++)
            {
                f1 << endl << "#" << " "
                    << purchasing_log_list[i].his_purchasing_list[j].name << " "
                    << purchasing_log_list[i].his_purchasing_list[j].num << " "
                    << purchasing_log_list[i].his_purchasing_list[j].price << " ";
            }
            if (i < purchasing_log_list.size() - 1) f1 << endl;
        }
        cout << "保存进度（1/4）" << endl;
        f1.close();
    }
    else
        cout << "Error to save" << endl;

    ofstream f2;
    f2.open(Products_path, ios::ate);
    if (f2.is_open())
    {
        for (int i = 0; i < products.size(); ++i)
        {
            products[i].outputProduct(f2);
            if ((i+1) < products.size()) f2 << endl;
        }
        cout << "保存进度（2/4）" << endl;
        f2.close();
    }
    else
        cout << "Error to save" << endl;

    ofstream f3;
    f3.open(VIP_path, ios::ate);
    if (f3.is_open())
    {
        for (int i = 0; i < vip.size(); ++i)
        {
            f3 << vip[i].ID << ' ' << vip[i].name << ' ' << vip[i].tel << ' ' << vip[i].score;
            if (i < (vip.size() - 1)) f3 << endl;
        }
        cout << "保存进度（3/4）" << endl;
        f3.close();
    }
    else
        cout << "Error to save" << endl;

    ofstream f4;
    f4.open(SVIP_path, ios::ate);
    if (f4.is_open())
    {
        for (int i = 0; i < svip.size(); ++i)
        {
            f4 << svip[i].ID << ' ' << svip[i].name << ' ' << svip[i].tel << ' ' << svip[i].score << ' ' << svip[i].viceID;
            if (i < (svip.size() - 1)) f4 << endl;
        }
        cout << "保存进度（4/4）" << endl;
        f4.close();
    }
    else
        cout << "Error to save" << endl;

}

void SupermarketHLH::showProductsList()
{
    system("cls");
    cout << "================商品列表================" << endl;
    cout << setfill(' ') << left;
    cout << "@" << setw(10) << "商品ID" << setw(20) << "名称" << setw(10) << "单价" << setw(10) << "数量" << endl;
    for (int i = 0; i < products.size(); i++)
    {
        products[i].showProduct();
    }
}

void SupermarketHLH::showProductsList(int n)
{
    system("cls");
    cout << "================商品列表================" << endl;
    cout << setfill(' ') << left;
    cout << "@" << setw(10) << "商品ID" << setw(20) << "名称" << setw(10) << "单价" << setw(10) << "数量" << endl;
    for (int i = 0; i < products.size(); i++)
    {
        if(products[i].inventory_left <= n)
            products[i].showProduct();
    }
}

void SupermarketHLH::searchProducts()
{
    int num;
    printf("请选择需要查询的数量：");
    cin >> num;
    showProductsList(num);
}

void SupermarketHLH::showCustomersList()
{
    for (int i = 0; i < vip.size(); i++)
    {
        vip[i].vipinfo();
        cout << endl;
    }
    for (int i = 0; i < svip.size(); i++)
    {
        svip[i].svipinfo();
        cout << endl;
    }
}

void SupermarketHLH::showCustomersList(string _str)
{
    if (_str == "line")
    {
        for (int i = 0; i < vip.size(); i++)
        {
            vip[i].vipinfo(_str);
            cout << endl;
        }
        for (int i = 0; i < svip.size(); i++)
        {
            svip[i].svipinfo(_str);
            cout << endl;
        }
    }
}

double SupermarketHLH::calculate()
{
    total_sale = 0;
    for (int i = 0; i < products.size(); ++i)
        total_sale += products[i].getProductSum();
    return total_sale;
}

void SupermarketHLH::printBill(bool fin) {
    string str = "";
    if (category == 0)
    {
        str += "普通用户";
        discount = 1.00;
    }
    else if (category == 1)
    {
        str += "VIP会员";
        discount = 0.98;
    }
    else if (category == 2)
    {
        str += "SVIP超级会员";
        discount = 0.95;
    }
    else
    {
        cout << "用户状态错误！" << endl;
        return;
    }
    bill = 0;
    for (int i = 0; i < purchasing_list.size(); i++)
        bill += discount * purchasing_list[i].num * purchasing_list[i].price;
    if (category == 1 && findVipID(currentID) != -1 && fin)
    {
        vip[findVipID(currentID)].score += bill;
        vip[findVipID(currentID)].vipinfo();
    }
    else if (category == 2 && findSVipID(currentID) != -1 && fin)
    {
        svip[findSVipID(currentID)].score += bill;
        svip[svip.size() - 1].svipinfo();
    }
    cout << "################购物清单################" << endl;
    cout << "@ " << str << endl;
    cout << "----------------------------------------" << endl;
    cout << setfill(' ') << left << setw(10) << "序号" << setw(10) << "商品代号"
        << setw(20) << "商品名称" << setw(10) << "商品单价"
        << setw(10) << "折扣" << setw(10) << "数量" << setw(10) << "价格" << endl;
    for (int i = 0; i < purchasing_list.size(); i++)
    {
        cout << setw(10) << i + 1 
            << setw(10) << purchasing_list[i].id
            << setw(20) << purchasing_list[i].name
            << setw(10) << purchasing_list[i].price
            << fixed << setprecision(2) << setw(10) << discount
            << setw(10) << purchasing_list[i].num
            << setw(10) << discount * purchasing_list[i].num * purchasing_list[i].price << endl;
    }
    cout << "----------------------------------------" << endl;
    string current_time = time2str(getTime());
    cout << "总价： " << left << setw(20) << bill << "购物时间： " << setw(20) << current_time << endl;
    if ((category > 0) && fin) addPurchasingLog(current_time, bill);
}

void SupermarketHLH::addProduct()
{
    ProductHLH _product;
    cout << "         请输入ID: ";
    std::cin >> _product.id;
    cout << "         请输入名字: ";
    std::cin >> _product.name;
    cout << "         请输入价格: ";
    std::cin >> _product.price;
    cout << "         请输入库存数量: ";
    std::cin >> _product.inventory_left;
    _product.inventory_sale = 0;
    products.push_back(_product);
    sort(products.begin(), products.end(), ProductHLH::cmp);
    cout << "----------------录入成功----------------" << endl;
}

void SupermarketHLH::delateCustomer()
{
    system("cls");
    showCustomersList("line");
    cout << "请输入需要删除的用户id: ";
    string id;
    std::cin >> id;
    if (id[0] == 'v')
    {
        for (int i = 0; i < vip.size(); i++)
            if (vip[i].ID == id)
                vip.erase(vip.begin() + i);
    }
    else if (id[0] == 's')
    {
        for (int i = 0; i < svip.size(); i++)
            if (svip[i].ID == id)
                svip.erase(svip.begin() + i);
    }
    cout << "删除成功，请重新查询" << endl;
}

void SupermarketHLH::delateProduct()
{
    showProductsList();
    cout << "请输入需要删除的商品id: ";
    long id;
    std::cin >> id;
    for (int i = 0; i < products.size(); i++)
        if (products[i].id == id)
            products.erase(products.begin() + i);
    cout << "删除成功，请重新查询" << endl;
}

void SupermarketHLH::changeCustomer()
{
    showCustomersList("line");
    cout << "请输入需要进行修改的用户id: ";
    string id;
    std::cin >> id;
    if (id[0] == 'v')
    {
        for (int i = 0; i < vip.size(); i++)
        {
            if (vip[i].ID == id)
            {
                int cmd = -1;
                while (cmd != 0)
                {
                    system("cls");
                    vip[i].vipinfo();
                    cout << "1、姓名  2、电话号码 0、返回" << endl;
                    cout << "请选择想修改的信息：";
                    cin >> cmd;
                    switch (cmd)
                    {
                    case 1:
                    {
                        cout << "请输入新的姓名信息：";
                        string _name;
                        cin >> _name;
                        vip[i].name = _name;
                        break;
                    }
                    case 2:
                    {
                        cout << "请输入新的电话信息：";
                        string _tel;
                        cin >> _tel;
                        vip[i].tel = _tel;
                        break;
                    }
                    }
                }
            }
            else
            {
                cout << "error!" << endl;
            }
        }
    }
    else if (id[0] == 's')
    {
        for (int i = 0; i < svip.size(); i++)
        {
            if (svip[i].ID == id)
            {
                int cmd = -1;
                while (cmd != 0)
                {
                    system("cls");
                    svip[i].svipinfo();
                    cout << "1、姓名  2、电话号码 0、返回" << endl;
                    cout << "请选择想修改的信息：";
                    cin >> cmd;
                    switch (cmd)
                    {
                    case 1:
                    {
                        cout << "请输入新的姓名信息：";
                        string _name;
                        cin >> _name;
                        svip[i].name = _name;
                        break;
                    }
                    case 2:
                    {
                        cout << "请输入新的电话信息：";
                        string _tel;
                        cin >> _tel;
                        svip[i].tel = _tel;
                        break;
                    }
                    }
                }
            }
            else
            {
                cout << "error!" << endl;
            }
        }
    }
}

time_t SupermarketHLH::getTime()
{
    time_t rawtime;
    time(&rawtime);
    return rawtime;
}

string SupermarketHLH::time2str(time_t rawtime)
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

time_t SupermarketHLH::str2time(string str)
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

void SupermarketHLH::getPurchasingMessage(Purchasing& pcs, ProductHLH pdt)
{
    pcs.id = pdt.id;
    pcs.name = pdt.name;
    pcs.price = pdt.price;
    pcs.num = 1;
}

int SupermarketHLH::findProductInList(long id)
{
    for (int i = 0; i < purchasing_list.size(); i++)
        if (id == purchasing_list[i].id)
            return i;
    return -1;
}

int SupermarketHLH::findProductWithID(long id)
{
    for (int i = 0; i < products.size(); i++)
        if (id == products[i].id)
            return i;
    return -1;
}

long SupermarketHLH::randomID()
{
    srand((unsigned)time(NULL));
    long rad = (rand() % 89999) + 10001;
    return rad;
}

bool SupermarketHLH::login()
{
    system("cls");
    string id_input;
    cout << "----------登录界面----------" << endl;
    cout << "请输入会员卡ID(普通顾客请输入10000): ";
    cin >> id_input;
    if (id_input == "10000")
    {
        bool flag = 0;
        long rad;
        do
        {
            rad = randomID();     
            if (!vip.empty())
                for (int i = 0; i < vip.size(); i++)
                    if (atoi(vip[i].ID.c_str()) == rad)
                    {
                        flag = 1;
                        break;
                    }
            if (!svip.empty())
                for (int i = 0; i < svip.size(); i++)
                    if (atoi(svip[i].ID.c_str()) == rad)
                    {
                        flag = 1;
                        break;
                    }
        } while (flag);
        currentID = rad;
        category = 0;
        cout << "游客登陆成功！" << endl;
        cout << "您的顾客流水号为：" << currentID << endl;
        system("pause");
        return true;
    }
    else
    {
        if (!vip.empty())
            for (int i = 0; i < vip.size(); i++)
                if (vip[i].ID == id_input)
                {
                    id_input = vip[i].ID.substr(1);
                    currentID = atoi(id_input.c_str());
                    category = 1;
                    goto _next2;
                }
        if (!svip.empty())
            for (int i = 0; i < svip.size(); i++)
                if (svip[i].ID == id_input || svip[i].viceID == id_input)
                {
                    id_input = svip[i].ID.substr(2);
                    currentID = atoi(id_input.c_str());
                    category = 2;
                    goto _next2;
                }
        cout << "无效会员卡ID！" << endl;
        system("pause");
        return false;
    _next2:
        cout << "会员登陆成功！" << endl;
        system("pause");
        return true;
    }
}

bool SupermarketHLH::adminlogin()
{
    system("cls");
    string id_input;
    cout << "----------登录界面----------" << endl;
    cout << "请认证超级管理员账号: ";
    cin >> id_input;
    if (id_input == "admin@182171" || id_input == "'")
    {
        currentID = 9999;
        category = 3;
        cout << "超级管理员登陆成功！" << endl;
        system("pause");
        return true;
    }
    else
    {
        cout << "认证失败！！！" << endl;
        return false;
    }
}

void SupermarketHLH::addVip()
{
    VipHLH _vip;
    
    system("cls");
    cout << "========会员卡登记========" << endl;
    cout << "     请输入姓名: ";
    cin >> _vip.name;
    cout << " 请输入电话号码: ";
    cin >> _vip.tel;
    _vip.ID = string("v") + to_string(currentID);
    vip.push_back(_vip);
    category = 1;
    cout << "========登记成功！========" << endl;
    system("pause");
}

void SupermarketHLH::addSVip()
{
    SVipHLH _svip;

    system("cls");
    cout << "======超级会员卡登记======" << endl;
    cout << "     请输入姓名: ";
    cin >> _svip.name;
    cout << " 请输入电话号码: ";
    cin >> _svip.tel;
    _svip.ID = string("sv") + to_string(currentID);
    _svip.viceID = string("v") + to_string(currentID);
    svip.push_back(_svip);
    category = 2;
    cout << "========登记成功！========" << endl;
    system("pause");
}

void SupermarketHLH::addSVip(VipHLH _v)
{
    SVipHLH _svip;
    _svip.name = _v.name;
    _svip.tel = _v.tel;
    _svip.ID = string("sv") + to_string(currentID);
    _svip.viceID = string("v") + to_string(currentID);
    svip.push_back(_svip);
    category = 2;
}
void SupermarketHLH::removeVip(VipHLH _v)
{
    for (int i = 0; i < vip.size(); i++)
        if (vip[i].ID == _v.ID)
            vip.erase(vip.begin() + i);
}

void SupermarketHLH::addPurchasingLog(string _time, double _total_price)
{
    PurchasingLog pl;
    for (int i = 0; i < purchasing_list.size(); i++)
    {
        HisPurchasingList hpt;
        hpt.name = purchasing_list[i].name;
        hpt.price = purchasing_list[i].price;
        hpt.num = purchasing_list[i].num;
        pl.his_purchasing_list.push_back(hpt);
    }
    string str = "";
    if (category == 1) str = "v" + str;
    else if (category == 2) str = "sv" + str;
    pl.ID = str + to_string(currentID);
    pl.time_str = _time;
    pl.total_price = _total_price;
    purchasing_log_list.push_back(pl);
}

void SupermarketHLH::cleanPurchasingList()
{
    vector<Purchasing>().swap(purchasing_list);
}

int SupermarketHLH::findVipID(long id)
{
    string ID = "v" + to_string(id);
    for (int i = 0; i < vip.size(); i++)
        if (ID == vip[i].ID)
            return i;
    return -1;
}

int SupermarketHLH::findSVipID(long id)
{
    string ID = "sv" + to_string(id);
    for (int i = 0; i < svip.size(); i++)
        if (ID == svip[i].ID)
            return i;
    return -1;
}

bool SupermarketHLH::viplogin()
{
    system("cls");
    string id_input;
    cout << "----------登录界面----------" << endl;
    cout << "请输入会员卡ID: ";
    cin >> id_input;

    if (!vip.empty())
        for (int i = 0; i < vip.size(); i++)
            if (vip[i].ID == id_input)
            {
                id_input = vip[i].ID.substr(1);
                currentID = atoi(id_input.c_str());
                category = 1;
                goto _next2;
            }
    if (!svip.empty())
        for (int i = 0; i < svip.size(); i++)
            if (svip[i].ID == id_input || svip[i].viceID == id_input)
            {
                id_input = svip[i].ID.substr(2);
                currentID = atoi(id_input.c_str());
                category = 2;
                goto _next2;
            }
    cout << "无效会员卡ID！" << endl;
    system("pause");
    return false;
_next2:
    cout << "会员登陆成功！" << endl;
    system("pause");
    return true;
}

void SupermarketHLH::printVipHistory()
{
    system("cls");
    if (category == 1)
    {
        cout << "===========会员购物历史记录============" << endl;
        for (int i = 0; i < purchasing_log_list.size(); i++)
        {
            if (purchasing_log_list[i].ID == ("v" + to_string(currentID)))
            {
                cout << "@购物时间：" << purchasing_log_list[i].time_str << "   "
                    << "购物金额： " << purchasing_log_list[i].total_price << endl;
                for (int j = 0; j < purchasing_log_list[i].his_purchasing_list.size(); j++)
                {
                    cout << "----------------------------------------" << endl;
                    cout << "=名称： " << purchasing_log_list[i].his_purchasing_list[j].name << "   ";
                    cout << "价格： " << purchasing_log_list[i].his_purchasing_list[j].price << "   ";
                    cout << "数量： " << purchasing_log_list[i].his_purchasing_list[j].num << endl;
                }
                cout << "========================================" << endl;
            }
        }
    }
    else if (category == 2)
    {
        //cout << "this" << endl;
        cout << "=========超级会员购物历史记录==========" << endl;
        for (int i = 0; i < purchasing_log_list.size(); i++)
        {
            if (purchasing_log_list[i].ID == ("sv" + to_string(currentID)))
            {
                cout << "@购物时间：" << purchasing_log_list[i].time_str << "   "
                    << "购物金额： " << purchasing_log_list[i].total_price << endl;
                for (int j = 0; j < purchasing_log_list[i].his_purchasing_list.size(); j++)
                {
                    cout << "----------------------------------------" << endl;
                    cout << "=名称： " << purchasing_log_list[i].his_purchasing_list[j].name << "   ";
                    cout << "价格： " << purchasing_log_list[i].his_purchasing_list[j].price << "   ";
                    cout << "数量： " << purchasing_log_list[i].his_purchasing_list[j].num << endl;
                }
                cout << "========================================" << endl;
            }
        }
    }
    else
    {
        cout << "error vip category!";
        return;
    }
}

bool SupermarketHLH::isOutDate(string his_time)
{
    time_t now_time = getTime();
    time_t log_time = str2time(his_time);
    time_t dif_time = difftime(now_time, log_time);
    if (dif_time >= 31536000) return true;
    else return false;
}

bool SupermarketHLH::findSVipOrVipInList(string id)
{
    for (int i = 0; i < purchasing_log_list.size(); ++i)
        if (purchasing_log_list[i].ID == id) return true;
    return false;
}

void SupermarketHLH::calculateSales()
{
    system("cls");
    cout << "--------超市销售情况--------" << endl;
    int sum = 0, counts = 0;
    for (int i = 0; i < purchasing_log_list.size(); i++)
    {
        sum += purchasing_log_list[i].total_price;
        if (purchasing_log_list[i].ID[0] == 's') counts += (purchasing_log_list[i].total_price / 19);
        else if (purchasing_log_list[i].ID[0] == 'v') counts += (purchasing_log_list[i].total_price / 49);
    }
    cout << "总销售额: " << sum << endl;
    cout << "对会员总让利: " << counts << endl;
}