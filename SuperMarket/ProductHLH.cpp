/*************************
 * @Author: hlh          *
 * @Date:2022/9/11       *
 *************************/
#include "ProductHLH.h"

using namespace std;

ProductHLH::ProductHLH() {
    inventory_sale = 0;
}

ProductHLH::ProductHLH(long _id, string _name, double _price, int _inventory_left, int _inventory_sale)
{
    id = _id;
    name = _name;
    price = _price;
    inventory_left = _inventory_left;
    inventory_sale = _inventory_sale;
}

ProductHLH ProductHLH::inputProduct(ifstream &file)
{
    long _id_;
    string _name_;
    double _price_;
    int _inventory_left_, _inventory_sale_;
    file >> _id_ >> _name_ >> _price_ >> _inventory_left_ >> _inventory_sale_;
    ProductHLH p = ProductHLH(_id_, _name_, _price_, _inventory_left_, _inventory_sale_);
    return p;
}

void ProductHLH::outputProduct(ofstream& file)
{
    file << id << " " << name << " " << price << " " << inventory_left << " " << inventory_sale;
}

void ProductHLH::showProduct()
{
    cout << "@" << setw(10) << id << setw(20) << name
         << "$" << setw(10) << price << setw(10) << inventory_left << endl;
}

double ProductHLH::getProductSum()
{
    if (inventory_sale > 0) return price * (double)inventory_sale;
    else return 0;
}