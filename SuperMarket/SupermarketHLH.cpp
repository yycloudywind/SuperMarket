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
        while (file.peek() != EOF)//ѭ����ȡÿһ��
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
        for (int i = 0; file.peek() != EOF; i++)//ѭ����ȡÿһ��
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
        for (int i = 0; file.peek() != EOF; i++)//ѭ����ȡÿһ��
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
        for (int i = 0; file.peek() != EOF; i++)//ѭ����ȡÿһ��
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
        cout << "������ȣ�1/4��" << endl;
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
        cout << "������ȣ�2/4��" << endl;
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
        cout << "������ȣ�3/4��" << endl;
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
        cout << "������ȣ�4/4��" << endl;
        f4.close();
    }
    else
        cout << "Error to save" << endl;

}

void SupermarketHLH::showProductsList()
{
    system("cls");
    cout << "================��Ʒ�б�================" << endl;
    cout << setfill(' ') << left;
    cout << "@" << setw(10) << "��ƷID" << setw(20) << "����" << setw(10) << "����" << setw(10) << "����" << endl;
    for (int i = 0; i < products.size(); i++)
    {
        products[i].showProduct();
    }
}

void SupermarketHLH::showProductsList(int n)
{
    system("cls");
    cout << "================��Ʒ�б�================" << endl;
    cout << setfill(' ') << left;
    cout << "@" << setw(10) << "��ƷID" << setw(20) << "����" << setw(10) << "����" << setw(10) << "����" << endl;
    for (int i = 0; i < products.size(); i++)
    {
        if(products[i].inventory_left <= n)
            products[i].showProduct();
    }
}

void SupermarketHLH::searchProducts()
{
    int num;
    printf("��ѡ����Ҫ��ѯ��������");
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
        str += "��ͨ�û�";
        discount = 1.00;
    }
    else if (category == 1)
    {
        str += "VIP��Ա";
        discount = 0.98;
    }
    else if (category == 2)
    {
        str += "SVIP������Ա";
        discount = 0.95;
    }
    else
    {
        cout << "�û�״̬����" << endl;
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
    cout << "################�����嵥################" << endl;
    cout << "@ " << str << endl;
    cout << "----------------------------------------" << endl;
    cout << setfill(' ') << left << setw(10) << "���" << setw(10) << "��Ʒ����"
        << setw(20) << "��Ʒ����" << setw(10) << "��Ʒ����"
        << setw(10) << "�ۿ�" << setw(10) << "����" << setw(10) << "�۸�" << endl;
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
    cout << "�ܼۣ� " << left << setw(20) << bill << "����ʱ�䣺 " << setw(20) << current_time << endl;
    if ((category > 0) && fin) addPurchasingLog(current_time, bill);
}

void SupermarketHLH::addProduct()
{
    ProductHLH _product;
    cout << "         ������ID: ";
    std::cin >> _product.id;
    cout << "         ����������: ";
    std::cin >> _product.name;
    cout << "         ������۸�: ";
    std::cin >> _product.price;
    cout << "         ������������: ";
    std::cin >> _product.inventory_left;
    _product.inventory_sale = 0;
    products.push_back(_product);
    sort(products.begin(), products.end(), ProductHLH::cmp);
    cout << "----------------¼��ɹ�----------------" << endl;
}

void SupermarketHLH::delateCustomer()
{
    system("cls");
    showCustomersList("line");
    cout << "��������Ҫɾ�����û�id: ";
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
    cout << "ɾ���ɹ��������²�ѯ" << endl;
}

void SupermarketHLH::delateProduct()
{
    showProductsList();
    cout << "��������Ҫɾ������Ʒid: ";
    long id;
    std::cin >> id;
    for (int i = 0; i < products.size(); i++)
        if (products[i].id == id)
            products.erase(products.begin() + i);
    cout << "ɾ���ɹ��������²�ѯ" << endl;
}

void SupermarketHLH::changeCustomer()
{
    showCustomersList("line");
    cout << "��������Ҫ�����޸ĵ��û�id: ";
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
                    cout << "1������  2���绰���� 0������" << endl;
                    cout << "��ѡ�����޸ĵ���Ϣ��";
                    cin >> cmd;
                    switch (cmd)
                    {
                    case 1:
                    {
                        cout << "�������µ�������Ϣ��";
                        string _name;
                        cin >> _name;
                        vip[i].name = _name;
                        break;
                    }
                    case 2:
                    {
                        cout << "�������µĵ绰��Ϣ��";
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
                    cout << "1������  2���绰���� 0������" << endl;
                    cout << "��ѡ�����޸ĵ���Ϣ��";
                    cin >> cmd;
                    switch (cmd)
                    {
                    case 1:
                    {
                        cout << "�������µ�������Ϣ��";
                        string _name;
                        cin >> _name;
                        svip[i].name = _name;
                        break;
                    }
                    case 2:
                    {
                        cout << "�������µĵ绰��Ϣ��";
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
    cout << "----------��¼����----------" << endl;
    cout << "�������Ա��ID(��ͨ�˿�������10000): ";
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
        cout << "�ο͵�½�ɹ���" << endl;
        cout << "���Ĺ˿���ˮ��Ϊ��" << currentID << endl;
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
        cout << "��Ч��Ա��ID��" << endl;
        system("pause");
        return false;
    _next2:
        cout << "��Ա��½�ɹ���" << endl;
        system("pause");
        return true;
    }
}

bool SupermarketHLH::adminlogin()
{
    system("cls");
    string id_input;
    cout << "----------��¼����----------" << endl;
    cout << "����֤��������Ա�˺�: ";
    cin >> id_input;
    if (id_input == "admin@182171" || id_input == "'")
    {
        currentID = 9999;
        category = 3;
        cout << "��������Ա��½�ɹ���" << endl;
        system("pause");
        return true;
    }
    else
    {
        cout << "��֤ʧ�ܣ�����" << endl;
        return false;
    }
}

void SupermarketHLH::addVip()
{
    VipHLH _vip;
    
    system("cls");
    cout << "========��Ա���Ǽ�========" << endl;
    cout << "     ����������: ";
    cin >> _vip.name;
    cout << " ������绰����: ";
    cin >> _vip.tel;
    _vip.ID = string("v") + to_string(currentID);
    vip.push_back(_vip);
    category = 1;
    cout << "========�Ǽǳɹ���========" << endl;
    system("pause");
}

void SupermarketHLH::addSVip()
{
    SVipHLH _svip;

    system("cls");
    cout << "======������Ա���Ǽ�======" << endl;
    cout << "     ����������: ";
    cin >> _svip.name;
    cout << " ������绰����: ";
    cin >> _svip.tel;
    _svip.ID = string("sv") + to_string(currentID);
    _svip.viceID = string("v") + to_string(currentID);
    svip.push_back(_svip);
    category = 2;
    cout << "========�Ǽǳɹ���========" << endl;
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
    cout << "----------��¼����----------" << endl;
    cout << "�������Ա��ID: ";
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
    cout << "��Ч��Ա��ID��" << endl;
    system("pause");
    return false;
_next2:
    cout << "��Ա��½�ɹ���" << endl;
    system("pause");
    return true;
}

void SupermarketHLH::printVipHistory()
{
    system("cls");
    if (category == 1)
    {
        cout << "===========��Ա������ʷ��¼============" << endl;
        for (int i = 0; i < purchasing_log_list.size(); i++)
        {
            if (purchasing_log_list[i].ID == ("v" + to_string(currentID)))
            {
                cout << "@����ʱ�䣺" << purchasing_log_list[i].time_str << "   "
                    << "����� " << purchasing_log_list[i].total_price << endl;
                for (int j = 0; j < purchasing_log_list[i].his_purchasing_list.size(); j++)
                {
                    cout << "----------------------------------------" << endl;
                    cout << "=���ƣ� " << purchasing_log_list[i].his_purchasing_list[j].name << "   ";
                    cout << "�۸� " << purchasing_log_list[i].his_purchasing_list[j].price << "   ";
                    cout << "������ " << purchasing_log_list[i].his_purchasing_list[j].num << endl;
                }
                cout << "========================================" << endl;
            }
        }
    }
    else if (category == 2)
    {
        //cout << "this" << endl;
        cout << "=========������Ա������ʷ��¼==========" << endl;
        for (int i = 0; i < purchasing_log_list.size(); i++)
        {
            if (purchasing_log_list[i].ID == ("sv" + to_string(currentID)))
            {
                cout << "@����ʱ�䣺" << purchasing_log_list[i].time_str << "   "
                    << "����� " << purchasing_log_list[i].total_price << endl;
                for (int j = 0; j < purchasing_log_list[i].his_purchasing_list.size(); j++)
                {
                    cout << "----------------------------------------" << endl;
                    cout << "=���ƣ� " << purchasing_log_list[i].his_purchasing_list[j].name << "   ";
                    cout << "�۸� " << purchasing_log_list[i].his_purchasing_list[j].price << "   ";
                    cout << "������ " << purchasing_log_list[i].his_purchasing_list[j].num << endl;
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
    cout << "--------�����������--------" << endl;
    int sum = 0, counts = 0;
    for (int i = 0; i < purchasing_log_list.size(); i++)
    {
        sum += purchasing_log_list[i].total_price;
        if (purchasing_log_list[i].ID[0] == 's') counts += (purchasing_log_list[i].total_price / 19);
        else if (purchasing_log_list[i].ID[0] == 'v') counts += (purchasing_log_list[i].total_price / 49);
    }
    cout << "�����۶�: " << sum << endl;
    cout << "�Ի�Ա������: " << counts << endl;
}