#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct ThongTin {
    string heso[2] = { "", "" }; //lưu các hệ số
    string toantu = ""; //lưu các toán tử
    string sohang[2] = { "","" }; //lưu các số hạng
};

void reset(ThongTin& a);
bool bang_0(string a);
bool sosanh(string a, string b[], int n);
ThongTin Parse(string line, ThongTin& a);
void swap(string& a, string& b);
string sub_string(string a, string b);
string sum_string(string a, string b);