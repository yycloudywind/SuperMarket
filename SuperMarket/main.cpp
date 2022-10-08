/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#include "CustomerHLH.h"
#include "ProductHLH.h"
#include "SupermarketHLH.h"
#include "UIHLH.h"

using namespace std;


void printMainInterface()
{
    UIHLH main_interface;
    main_interface.setTitle("小型超市购物管理系统");
    main_interface.setLineSize(3);
    main_interface.setLineStr("用户购物", 1);
    main_interface.setLineStr("会员查询", 2);
    main_interface.setLineStr("店铺管理", 3);
    main_interface.showUI();
}

void printManage()
{
    UIHLH main_manage;
    main_manage.setTitle("请选择执行操作");
    main_manage.setLineSize(2);
    main_manage.setLineStr("商品管理", 1);
    main_manage.setLineStr("用户管理", 2);
    main_manage.showUI();
}

void printProductManage()
{
    UIHLH product_manage;
    product_manage.setTitle("请选择执行操作");
    product_manage.setLineSize(5);
    product_manage.setLineStr("查询商品信息", 1);
    product_manage.setLineStr("添加商品信息", 2);
    product_manage.setLineStr("修改商品信息", 3);
    product_manage.setLineStr("删除商品信息", 4);
    product_manage.setLineStr("分类查询商品", 5);
    product_manage.showUI();
}

void printCustomerManage()
{
    UIHLH customer_manage;
    customer_manage.setTitle("请选择执行操作");
    customer_manage.setLineSize(4);
    customer_manage.setLineStr("查询会员信息", 1);
    customer_manage.setLineStr("修改会员信息", 2);
    customer_manage.setLineStr("删除会员信息", 3);
    customer_manage.setLineStr("销售额统计", 4);
    customer_manage.showUI();
}

void printPurchasingCaption()
{
    system("cls");
    string line_title = "商品清单";
    cout << setfill('#') << setw(40) << "#" << endl;
    int tag_num = (40 - line_title.size()) / 2;
    for (int i = 1; i <= tag_num; i++)
        cout << "#";
    cout << line_title;
    for (int i = 1; i <= tag_num; i++)
        cout << "#";
    cout << endl;
    cout << setfill('#') << setw(40) << "#" << setfill(' ') << endl;
}

int getcommond() {
    int num;
    cout << "请输入指令: ";
    cin >> num;
    return num;
}

int getproductcommand() {
    int num;
    cout << "请输入想购买的商品代号（输入0进行结算）: ";
    cin >> num;
    return num;
}

int getcondition() {
    int num;
    cout << "请输入指令: ";
    cin >> num;
    return num;
}
int getitem() {
    int num;
    cout << "请输入您的选择: ";
    cin >> num;
    return num;
}

int main() {
    SupermarketHLH sm;
    int command = 1;
    int condition = 1;
    int item = 1;
    while (condition != 0)
    {
        printMainInterface();
        condition = getcondition();
        if (condition == 0) return 0;
        switch (condition)
        {
        case 1: //用户购物
            if (!sm.login()) continue;
            sm.cleanPurchasingList();
            while (command != 0)
            {                
                //printPurchasingCaption();  
                sm.showProductsList();
                sm.printBill(0);
                Purchasing pcs;
                command = getproductcommand();
                if (command != 0)
                {
                    int ls = sm.findProductWithID(command);
                    if (ls > sm.products.size())
                    {
                        cout << "没有该商品！" << endl;
                        system("pause");
                        continue;
                    }
                    sm.products[ls].inventory_left--;
                    sm.products[ls].inventory_sale++;
                    sm.getPurchasingMessage(pcs, sm.products[ls]);
                    if (sm.findProductInList(pcs.id) < 0)
                        sm.purchasing_list.push_back(pcs);
                    else
                    {
                        cout << sm.findProductInList(pcs.id) << endl;
                        sm.purchasing_list[sm.findProductInList(pcs.id)].num++;
                    }
                }
                else
                {                    
                    if (!sm.category) //普通顾客
                    {
                        if (sm.bill >= 1000 && sm.bill < 2000) {
                            cout << "您已购物满1000$，满足会员卡开通条件，是否开通会员？(按0取消，按1开通)" << endl;
                            if (getitem())
                            {
                                sm.addVip();
                            }
                        }
                        else if(sm.bill >= 2000)
                        {
                            cout << "您已购物满2000$，满足超级会员卡开通条件，是否开通超级会员？(按0取消，按1开通)" << endl;
                            if (getitem())
                            {
                                sm.addSVip();
                            }                       
                        }
                        system("cls");
                        //if(sm.category == 1) sm.vip[sm.vip.size() - 1].vipinfo();
                        //else if(sm.category == 2) sm.svip[sm.svip.size() - 1].svipinfo();
                        sm.printBill(1);
                    }
                    else if (sm.category == 1) //vip
                    {
                        if (sm.bill >= 1000)
                        {
                            cout << "您已购物满1000$，满足超级会员卡开通条件，是否开通超级会员？(按0取消，按1开通)" << endl;
                            if (getitem())
                            {
                                int vipID = sm.findVipID(sm.currentID);
                                if (vipID == -1)
                                {
                                    cout << "error!" << endl;
                                    continue;
                                }
                                sm.addSVip(sm.vip[vipID]);
                                sm.removeVip(sm.vip[vipID]);
                            }
                        }
                        system("cls");
                        //if (sm.category == 1) sm.vip[sm.vip.size() - 1].vipinfo();
                        //else if (sm.category == 2) sm.svip[sm.svip.size() - 1].svipinfo();
                        sm.printBill(1);
                    }
                    else if(sm.category == 2) //svip
                    {
                        system("cls");
                        //sm.svip[sm.svip.size() - 1].svipinfo();
                        sm.printBill(1);
                    }
                    cout << "----------------谢谢惠顾----------------" << endl;
                    std::system("pause");
                }
            }
            sm.MessageSave();
            std::system("pause");
            break;
        case 2: //会员查询
            if (!sm.viplogin()) continue;
            sm.printVipHistory();
            std::system("pause");
            break;
        case 3: //店铺管理
            if (!sm.adminlogin()) continue;
            while (command != 0)
            {
                frm:
                printManage();
                command = getcommond();
                switch (command)
                {
                case 1:
                    while (command != 0)
                    {
                        printProductManage();
                        command = getcommond();
                        switch (command)
                        {
                        case 1: //查询商品信息
                            sm.showProductsList();
                            std::system("pause");
                            continue;
                        case 2: //添加商品信息                            
                            sm.addProduct();
                            std::system("pause");
                            continue;
                        case 3: //修改商品信息
                            sm.delateProduct();
                            sm.addProduct();
                            std::system("pause");
                            continue;
                        case 4: //删除商品信息
                            sm.delateProduct();
                            std::system("pause");
                            continue;
                        case 5: //分类搜索商品
                            sm.searchProducts();
                            std::system("pause");
                            continue;
                        case 0: //返回
                            goto frm;
                            break;
                        default:
                            cout << "input error!" << endl;
                            std::system("pause");
                            break;
                        }
                    }
                case 2:
                    while (command != 0)
                    {
                        printCustomerManage();
                        command = getcommond();
                        switch (command)
                        {
                        case 1: //查询会员信息
                            sm.showCustomersList("line");
                            std::system("pause");
                            continue;
                        case 2: //修改会员信息
                            sm.changeCustomer();
                            std::system("pause");
                            continue;
                        case 3: //删除会员信息
                            sm.delateCustomer();
                            std::system("pause");
                            continue;
                        case 4: //销售额统计
                        {
                            sm.calculateSales();
                            std::system("pause");
                            continue;
                        }
                        case 0:
                            goto frm;
                            break;
                        default:
                            cout << "input error!" << endl;
                            std::system("pause");
                            break;
                        }
                    }
                case 0: //返回
                    break;
                default:
                    cout << "input error!" << endl;
                    std::system("pause");
                    break;
                }
            }
            sm.MessageSave();
            std::system("pause");
            break;
        default:
            cout << "input error!" << endl;
            std::system("pause");
            break;
        }
        condition = 1;
        command = 1;
        std::system("cls");
    }
    return 0;
}