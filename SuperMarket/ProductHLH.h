/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#ifndef SUPERMARKET_PRODUCTS_H
#define SUPERMARKET_PRODUCTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;

class ProductHLH {
public:
    ProductHLH();
    ProductHLH(long _id, string _name, double _price, int _inventory_left, int _inventory_sale);

    static ProductHLH inputProduct(ifstream& file);
    void outputProduct(ofstream& file);
    void showProduct();
    double getProductSum();

    static bool cmp(ProductHLH a, ProductHLH b) { return a.id <= b.id; };
//private:
    long id; //��ƷID
    string name; //��Ʒ����
    double price; //��Ʒ�۸�
    int inventory_left; //ʣ����
    int inventory_sale; //���۳���Ʒ����

};

#endif //SUPERMARKET_PRODUCTS_H
