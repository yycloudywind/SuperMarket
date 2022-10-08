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
    main_interface.setTitle("С�ͳ��й������ϵͳ");
    main_interface.setLineSize(3);
    main_interface.setLineStr("�û�����", 1);
    main_interface.setLineStr("��Ա��ѯ", 2);
    main_interface.setLineStr("���̹���", 3);
    main_interface.showUI();
}

void printManage()
{
    UIHLH main_manage;
    main_manage.setTitle("��ѡ��ִ�в���");
    main_manage.setLineSize(2);
    main_manage.setLineStr("��Ʒ����", 1);
    main_manage.setLineStr("�û�����", 2);
    main_manage.showUI();
}

void printProductManage()
{
    UIHLH product_manage;
    product_manage.setTitle("��ѡ��ִ�в���");
    product_manage.setLineSize(5);
    product_manage.setLineStr("��ѯ��Ʒ��Ϣ", 1);
    product_manage.setLineStr("�����Ʒ��Ϣ", 2);
    product_manage.setLineStr("�޸���Ʒ��Ϣ", 3);
    product_manage.setLineStr("ɾ����Ʒ��Ϣ", 4);
    product_manage.setLineStr("�����ѯ��Ʒ", 5);
    product_manage.showUI();
}

void printCustomerManage()
{
    UIHLH customer_manage;
    customer_manage.setTitle("��ѡ��ִ�в���");
    customer_manage.setLineSize(4);
    customer_manage.setLineStr("��ѯ��Ա��Ϣ", 1);
    customer_manage.setLineStr("�޸Ļ�Ա��Ϣ", 2);
    customer_manage.setLineStr("ɾ����Ա��Ϣ", 3);
    customer_manage.setLineStr("���۶�ͳ��", 4);
    customer_manage.showUI();
}

void printPurchasingCaption()
{
    system("cls");
    string line_title = "��Ʒ�嵥";
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
    cout << "������ָ��: ";
    cin >> num;
    return num;
}

int getproductcommand() {
    int num;
    cout << "�������빺�����Ʒ���ţ�����0���н��㣩: ";
    cin >> num;
    return num;
}

int getcondition() {
    int num;
    cout << "������ָ��: ";
    cin >> num;
    return num;
}
int getitem() {
    int num;
    cout << "����������ѡ��: ";
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
        case 1: //�û�����
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
                        cout << "û�и���Ʒ��" << endl;
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
                    if (!sm.category) //��ͨ�˿�
                    {
                        if (sm.bill >= 1000 && sm.bill < 2000) {
                            cout << "���ѹ�����1000$�������Ա����ͨ�������Ƿ�ͨ��Ա��(��0ȡ������1��ͨ)" << endl;
                            if (getitem())
                            {
                                sm.addVip();
                            }
                        }
                        else if(sm.bill >= 2000)
                        {
                            cout << "���ѹ�����2000$�����㳬����Ա����ͨ�������Ƿ�ͨ������Ա��(��0ȡ������1��ͨ)" << endl;
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
                            cout << "���ѹ�����1000$�����㳬����Ա����ͨ�������Ƿ�ͨ������Ա��(��0ȡ������1��ͨ)" << endl;
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
                    cout << "----------------лл�ݹ�----------------" << endl;
                    std::system("pause");
                }
            }
            sm.MessageSave();
            std::system("pause");
            break;
        case 2: //��Ա��ѯ
            if (!sm.viplogin()) continue;
            sm.printVipHistory();
            std::system("pause");
            break;
        case 3: //���̹���
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
                        case 1: //��ѯ��Ʒ��Ϣ
                            sm.showProductsList();
                            std::system("pause");
                            continue;
                        case 2: //�����Ʒ��Ϣ                            
                            sm.addProduct();
                            std::system("pause");
                            continue;
                        case 3: //�޸���Ʒ��Ϣ
                            sm.delateProduct();
                            sm.addProduct();
                            std::system("pause");
                            continue;
                        case 4: //ɾ����Ʒ��Ϣ
                            sm.delateProduct();
                            std::system("pause");
                            continue;
                        case 5: //����������Ʒ
                            sm.searchProducts();
                            std::system("pause");
                            continue;
                        case 0: //����
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
                        case 1: //��ѯ��Ա��Ϣ
                            sm.showCustomersList("line");
                            std::system("pause");
                            continue;
                        case 2: //�޸Ļ�Ա��Ϣ
                            sm.changeCustomer();
                            std::system("pause");
                            continue;
                        case 3: //ɾ����Ա��Ϣ
                            sm.delateCustomer();
                            std::system("pause");
                            continue;
                        case 4: //���۶�ͳ��
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
                case 0: //����
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