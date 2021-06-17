#include "Chuyendoi.h"
//làm mới lại struct
void reset(ThongTin& a) {
    a.heso[0] = "";
    a.heso[1] = "";
    a.toantu = "";
    a.sohang[0] = "";
    a.sohang[1] = "";
}
//tìm 1 chuỗi có trong 1 mảng chuỗi cho trước hay không
bool sosanh(string a, string b[], int n) {
    for (int i = 0; i < n; i++) {
        if (a == b[i])
            return true;
    }
    return false;
}
//kiểm tra 1 chuỗi khi chuyển sang số nguyên có bằng 0 hay không
bool bang_0(string a) {
    for (int i = a.length() - 1; i >= 0; i--) {
        if (a[i] != '0' && a[i] != '-') {
            return false;
        }
    }
    return true;
}
//cắt từng chuỗi lưu vào struct Thongtin
ThongTin Parse(string line, ThongTin& a) {
    string SEPERATOR = " ";
    string temp;
    string heso[3] = { "2","10","16" };
    string toantu[12] = { "rol", "ror", "&", "|", "^", "~", ">>", "<<", "+", "-", "*", "/" };
    string toantu1[9] = { "&", "|", "^", ">>", "<<", "+", "-", "*", "/" };//toán tử cần 2 số hạng
    int i = 0, j = 0;

    int startpos = 0;
    size_t pos = line.find(SEPERATOR);

    while (pos != string::npos) {
        temp = line.substr(startpos, pos - startpos);
        if (sosanh(temp, heso, 3) && i < 2) {
            a.heso[i] = temp;
            i++;
        }
        else if (sosanh(temp, toantu, 12))
            a.toantu = temp;
        else {
            a.sohang[j] = temp;
            j++;
        }

        startpos = pos + SEPERATOR.length();
        pos = line.find(SEPERATOR, startpos);
    }

    if (startpos < line.length())
        a.sohang[j] = line.substr(startpos, line.length() - startpos);

    //nếu hàm hiểu nhầm lưu số số hạng có chuỗi giống với hệ số, trả lại giá trị cho số hạng
    if (sosanh(a.toantu, toantu1, 9) && a.sohang[1] == "") {
        a.sohang[1] = a.sohang[0];
        a.sohang[0] = a.heso[1];
        a.heso[1] = "";
    }

    return a;
}
//hoán vị 2 chuỗi
void swap(string& a, string& b) {
    string temp = a;
    a = b;
    b = temp;
}
//trừ 2 chuỗi không âm
string sub_string(string a, string b) {
    int dai = a.length();
    string sub(dai, 48);
    string c(dai, 48);

    int k = 0;
    for (int i = 0; i < b.length(); i++) {
        if (b[i] == '0')
            k++;
        else
            break;
    }
    for (int i = b.length() - 1; i >= 0; i--) {
        if (i == k - 1)
            break;
        c[i - (b.length() - a.length())] = b[i];
    }
    int temp = 0;
    for (int i = dai - 1; i >= 0; i--) {
        int d = a[i] - 48;
        int e = c[i] - 48;
        if (temp == 1) {
            int f = d - (e + 1);
            temp = 0;
            if (f < 0)
            {
                f = f + 10;
                temp = 1;
            }
            sub[i] = f + 48;
        }
        else {
            int f = d - e;
            if (f < 0) {
                f = f + 10;
                temp = 1;
            }
            sub[i] = f + 48;
        }
    }
    return sub;
}
//cộng 2 chuỗi không âm
string sum_string(string a, string b) {
    char temp = 0;
    char x[50] = { '0' };
    char y[50] = { '0' };
    if (b.length() > a.length()) {
        swap(a, b);
    }

    int len = a.length();
    int hieu_len = len - b.length();
    string sum(len + 1, 0);

    for (int i = len; i > 0; i--) {
        x[i] = a[i - 1];

        if (i > hieu_len)
            y[i] = b[i - hieu_len - 1];
        else
            y[i] = '0';
    }

    for (int i = len; i >= 0; i--) {
        sum[i] = (x[i] + y[i] - 48 * 2 + temp) % 10 + 48;
        temp = (x[i] + y[i] - 48 * 2 + temp) / 10;
    }
    if (sum[0] == '0') {
        for (int i = 0; i < sum.length() - 1; i++) {
            sum[i] = sum[i + 1];
        }
        sum.pop_back();
    }
    return sum;
}