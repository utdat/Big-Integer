#include <fstream>
#include "QInt.h"
#include "Chuyendoi.h"

int main(int argc, char** argv)
{
    ThongTin info;
    string line_info;
    QInt a;
    QInt b;
    QInt ketqua;
    int temp = 0;

    if (argc != 3)
        cout << "So luong tham so khong hop le";
    else {
        //mở file input để đọc
        ifstream reader(argv[1], ios::in);
        if (!reader) {
            cout << "\nKhong the mo file de doc!";
            exit(EXIT_FAILURE);
        }
        //mở file output để ghi
        ofstream writer(argv[2], ios::out);
        if (!writer) {
            cout << "\nKhong the mo file de ghi!";
            exit(EXIT_FAILURE);
        }

        do {
            //đọc từng dòng trong file input
            getline(reader, line_info);
            if (line_info == "")
                break;

            //cắt từng phần tử lưu vào struct info
            info = Parse(line_info, info);

            if (info.toantu != "") {
                //cộng
                if (info.toantu == "+") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        b.set_2_QInt(info.sohang[1]);
                        ketqua = a + b;
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        b.set_10_QInt(info.sohang[1]);
                        ketqua = a + b;
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        b.set_16_QInt(info.sohang[1]);
                        ketqua = a + b;
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                //trừ
                else if (info.toantu == "-") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        b.set_2_QInt(info.sohang[1]);
                        ketqua = a - b;
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        b.set_10_QInt(info.sohang[1]);
                        ketqua = a - b;
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        b.set_16_QInt(info.sohang[1]);
                        ketqua = a - b;
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                //nhân
                else if (info.toantu == "*") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        b.set_2_QInt(info.sohang[1]);
                        ketqua = a * b;
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        b.set_10_QInt(info.sohang[1]);
                        ketqua = a * b;
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        b.set_16_QInt(info.sohang[1]);
                        ketqua = a * b;
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                //chia
                else if (info.toantu == "/") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        b.set_2_QInt(info.sohang[1]);
                        ketqua = a / b;
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        b.set_10_QInt(info.sohang[1]);
                        ketqua = a / b;
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        b.set_16_QInt(info.sohang[1]);
                        ketqua = a / b;
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                //AND
                else if (info.toantu == "&") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        b.set_2_QInt(info.sohang[1]);
                        ketqua = a & b;
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        b.set_10_QInt(info.sohang[1]);
                        ketqua = a & b;
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        b.set_16_QInt(info.sohang[1]);
                        ketqua = a & b;
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                //OR
                else if (info.toantu == "|") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        b.set_2_QInt(info.sohang[1]);
                        ketqua = a | b;
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        b.set_10_QInt(info.sohang[1]);
                        ketqua = a | b;
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        b.set_16_QInt(info.sohang[1]);
                        ketqua = a | b;
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                //XOR
                else if (info.toantu == "^") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        b.set_2_QInt(info.sohang[1]);
                        ketqua = a ^ b;
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        b.set_10_QInt(info.sohang[1]);
                        ketqua = a ^ b;
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        b.set_16_QInt(info.sohang[1]);
                        ketqua = a ^ b;
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                //NOT
                else if (info.toantu == "~") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        ketqua = ~a;
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        ketqua = ~a;
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        ketqua = ~a;
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                //dịch trái
                else if (info.toantu == "<<") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        ketqua = a << stoi(info.sohang[1]);
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        ketqua = a << stoi(info.sohang[1]);
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        ketqua = a << stoi(info.sohang[1]);
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                //dịch phải
                else if (info.toantu == ">>") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        ketqua = a >> stoi(info.sohang[1]);
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        ketqua = a >> stoi(info.sohang[1]);
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        ketqua = a >> stoi(info.sohang[1]);
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                // rolate left
                else if (info.toantu == "rol") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        ketqua = a.rol();
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        ketqua = a.rol();
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        ketqua = a.rol();
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
                //rolate right
                else if (info.toantu == "ror") {
                    if (info.heso[0] == "2") {
                        a.set_2_QInt(info.sohang[0]);
                        ketqua = a.ror();
                        writer << ketqua.get_2_QInt() << endl;
                    }
                    else if (info.heso[0] == "10") {
                        a.set_10_QInt(info.sohang[0]);
                        ketqua = a.ror();
                        writer << ketqua.get_10_QInt() << endl;
                    }
                    else {
                        a.set_16_QInt(info.sohang[0]);
                        ketqua = a.ror();
                        writer << ketqua.get_16_QInt() << endl;
                    }
                }
            }
            //-------------------------------------------------------------
            //chuyển cơ số
            else {
                //2 sang 2
                if (info.heso[0] == "2" && info.heso[1] == "2")
                    writer << ketqua.change_2_to_2(info.sohang[0]) << endl;
                //2 sang 10
                else if (info.heso[0] == "2" && info.heso[1] == "10")
                    writer << ketqua.change_2_to_10(info.sohang[0]) << endl;
                //2 sang 16
                else if (info.heso[0] == "2" && info.heso[1] == "16")
                    writer << ketqua.change_2_to_16(info.sohang[0]) << endl;
                //10 sang 2
                else if (info.heso[0] == "10" && info.heso[1] == "2")
                    writer << ketqua.change_10_to_2(info.sohang[0]) << endl;
                //10 sang 10
                else if (info.heso[0] == "10" && info.heso[1] == "10")
                    writer << ketqua.change_10_to_10(info.sohang[0]) << endl;
                //10 sang 16
                else if (info.heso[0] == "10" && info.heso[1] == "16")
                    writer << ketqua.change_10_to_16(info.sohang[0]) << endl;
                //16 sang 2
                else if (info.heso[0] == "16" && info.heso[1] == "2")
                    writer << ketqua.change_16_to_2(info.sohang[0]) << endl;
                //16 sang 10
                else if (info.heso[0] == "16" && info.heso[1] == "10")
                    writer << ketqua.change_16_to_10(info.sohang[0]) << endl;
                //16 sang 16
                else if (info.heso[0] == "16" && info.heso[1] == "16")
                    writer << ketqua.change_16_to_16(info.sohang[0]) << endl;
            }

            //reset lại dữ liệu
            a = QInt();
            b = QInt();
            ketqua = QInt();
            reset(info);
        } while (!reader.eof());

        writer.close();
        reader.close();
    }
    return 0;
}