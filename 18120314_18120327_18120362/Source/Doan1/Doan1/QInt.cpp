#include "QInt.h"

QInt::QInt() {
	this->arrayBits[0] = 0;
	this->arrayBits[1] = 0;
	this->arrayBits[2] = 0;
	this->arrayBits[3] = 0;
}
QInt::~QInt() {}

//chuyển chuỗi nhị phân thành QInt
void QInt::set_2_QInt(string a) {
	int size = a.length() - 1;
	if (size < 0)
		return;

	for (int i = 3; i >= 0; i--) {
		for (int j = 31; j >= 0; j--) {
			if (size < 0)
				break;

			if (a[size] == '1')
				this->arrayBits[i] = batbit(this->arrayBits[i], 31 - j);

			size--;
		}
	}
}
//chuyển chuỗi thập phân thành QInt
void QInt::set_10_QInt(string a) {
	if (a == "")
		return;

	int i = 127;
	int k;
	int len = a.length() - 1;
	char bit;
	while (i >= 0) {
		if (bang_0(a))
			break;

		k = i / 32;
		bit = (a[len] - 48) % 2;

		if (bit == 1)
			this->arrayBits[k] = batbit(this->arrayBits[k], 31 - (i - k * 32));
		else
			this->arrayBits[k] = tatbit(this->arrayBits[k], 31 - (i - k * 32));

		Div2(a);
		i--;
	}

	if (a[0] == '-') {
		this->Bu2(*this);
	}
}
//chuyển chuỗi thập lục phân thành QInt
void QInt::set_16_QInt(string a) {
	int length_a = a.length();
	int i = length_a - 1;
	int temp = 0;
	while (i >= 0) {
		//chuyển từng kí tự của chuỗi về kiểu int, nếu "A" chuyển thành 10, tương tự tới "F"
		if ((int)a[i] >= 65)
			temp = (int)a[i] - 55;
		else if ((int)a[i] >= 48)
			temp = (int)a[i] - 48;
		//cộng dồn 8 ký tự lưu vào 1 arrayBits
		//riêng ký tự thứ 8 mỗi lần cộng dồn, nếu kiểu int tương ứng >= 8 sẽ trừ để lấy dấu âm
		if (temp >= 8 && (length_a - i - 1) % 8 == 7)
			this->arrayBits[(i + 32 - length_a) / 8] -= (8 - temp % 8) * pow(2, ((length_a - i - 1) % 8) * 4);
		else
			this->arrayBits[(i + 32 - length_a) / 8] += temp * pow(2, ((length_a - i - 1) % 8) * 4);

		i--;
	}
}

//chuyển QInt sang chuỗi nhị phân
string QInt::get_2_QInt() {
	string bin = "";
	bool ktra = false;
	for (int i = 0; i <= 3; i++) {
		for (int j = 31; j >= 0; j--) {
			if (laybit(this->arrayBits[i], j) == 1)
				ktra = true;

			if (ktra)
				bin += to_string(laybit(this->arrayBits[i], j));
		}
	}
	return bin;
}
//chuyển QInt sang chuỗi thập phân
string QInt::get_10_QInt() {
	int j = 0;
	int a[4] = { 0 };
	string b[4];//biến dùng để lưu chuỗi thập phân khi chuyển đổi từng phần tử arrayBits
	string dec;
	size_t pos;
	for (int i = 1; i < 4; i++) {
		if (this->arrayBits[i] < 0)
			a[i] = 2;
	}

	for (int i = 3; i >= 0; i--) {
		//lưu từng chuỗi thập phân khi chuyển đổi từng phần tử arrayBits
		b[i] = to_string((this->arrayBits[i] + a[i] * pow(2, 31)) * pow(2, (3 - i) * 32));

		//xóa đuôi ".0000" nếu tìm thấy
		pos = b[i].find(".");
		if (pos != string::npos)
			b[i] = b[i].substr(0, pos);
	}

	//nếu arrayBits[0] < 0 => số thập phân âm, cộng 3 chuỗi từ b[1] tới b[3] và trừ cho b[0]
	if (this->arrayBits[0] < 0) {
		b[0] = b[0].substr(1, b[0].length());
		dec = sub_string(b[0], sum_string(b[1], sum_string(b[2], b[3])));
		//xóa các số 0 ở đầu
		while (dec[j] == '0') {
			j++;
		}
		return "-" + dec.substr(j, dec.length());
	}
	else {
		return sum_string(sum_string(b[0], b[1]), sum_string(b[2], b[3]));
	}
}
//chuyển QInt sang chuỗi thập lục phân
string QInt::get_16_QInt() {
	string a = this->get_2_QInt();//chuyển QInt sang chuỗi nhị phân
	string hex = "";
	int a_len = a.length();
	int dec = 0;

	//nếu độ dài chuỗi nhị phân không là bội của 4, thêm "0" vào đầu chuỗi cho đến khi là bội của 4
	while (a_len % 4 != 0) {
		a = "0" + a;
		a_len++;
	}
	//chuyển 1 bộ 4 kí tự nhị phân sang thập phân, sau đó chuyển số thập phân đó sang hệ 16 tương ứng 
	for (int i = a_len - 1; i >= 3; i -= 4) {
		dec = a[i] - 48 +
			(a[i - 1] - 48) * pow(2, 1) +
			(a[i - 2] - 48) * pow(2, 2) +
			(a[i - 3] - 48) * pow(2, 3);
		hex = dec_to_hex(dec) + hex;
	}
	return hex;
}

//chuyển hệ 2 sang 2
string QInt::change_2_to_2(string a) {
	this->set_2_QInt(a);
	return this->get_2_QInt();
}
//chuyển hệ 2 sang 10
string QInt::change_2_to_10(string a) {
	this->set_2_QInt(a);
	return this->get_10_QInt();
}
//chuyển hệ 2 sang 16
string QInt::change_2_to_16(string a) {
	this->set_2_QInt(a);
	return this->get_16_QInt();
}

//chuyển hệ 10 sang 2
string QInt::change_10_to_2(string a) {
	this->set_10_QInt(a);
	return this->get_2_QInt();
}
//chuyển hệ 10 sang 10
string QInt::change_10_to_10(string a) {
	this->set_10_QInt(a);
	return this->get_10_QInt();
}
//chuyển hệ 10 sang 16
string QInt::change_10_to_16(string a) {
	this->set_10_QInt(a);
	return this->get_16_QInt();
}

//chuyển hệ 16 sang 2
string QInt::change_16_to_2(string a) {
	this->set_16_QInt(a);
	return this->get_2_QInt();
}
//chuyển hệ 16 sang 10
string QInt::change_16_to_10(string a) {
	this->set_16_QInt(a);
	return this->get_10_QInt();
}
//chuyển hệ 16 sang 16
string QInt::change_16_to_16(string a) {
	this->set_16_QInt(a);
	return this->get_16_QInt();
}

//xoay phải
QInt QInt::ror() {
	QInt temp;
	bool i = laybit(this->arrayBits[3], 0);
	temp = *this >> 1;
	if (i == 1) temp.arrayBits[0] = batbit(temp.arrayBits[0], 31);
	else temp.arrayBits[0] = tatbit(temp.arrayBits[0], 31);
	return temp;
}
//xoay trái
QInt QInt::rol() {
	QInt temp;
	bool i = laybit(this->arrayBits[0], 31);
	temp = *this << 1;
	if (i == 1) temp.arrayBits[3] = batbit(temp.arrayBits[3], 0);
	else temp.arrayBits[3] = tatbit(temp.arrayBits[3], 0);
	return temp;
}

//lấy số bù 2
void QInt::Bu2(QInt& a) {
	char ktra = 1;
	for (int i = 3; i >= 0; i--) {
		for (int j = 0; j < 32; j++) {
			if (laybit(a.arrayBits[i], j) == 1 && ktra == 1)
				ktra = 0;
			else if (ktra == 0)
				a.arrayBits[i] = daobit(a.arrayBits[i], j);
		}
	}
}
int QInt::batbit(int& a, int i) {
	return (1 << i) | a;
}
int QInt::tatbit(int& a, int i) {
	return ~(1 << i) & a;
}
int QInt::laybit(int a, int i) {
	return (a >> i) & 1;
}
int QInt::daobit(int& a, int i) {
	return (1 << i) xor a;
}
//chia chuỗi cho 2 lấy dư
void QInt::Div2(string& a) {
	char du = '0';
	if (a[0] == '-')
	{
		for (int i = 1; i <= a.length(); i++)
		{
			char temp = a[i];
			a[i] = (((a[i] - 48) + 10 * (du - 48)) / 2) + 48;
			du = ((temp - 48) % 2) + 48;
		}
	}
	else
	{
		for (int i = 0; i <= a.length(); i++)
		{
			char temp = a[i];
			a[i] = (((a[i] - 48) + 10 * (du - 48)) / 2) + 48;
			du = ((temp - 48) % 2) + 48;
		}
	}
}
//chuyển các số thập phân sang kí tự hệ 16
string QInt::dec_to_hex(int a) {
	if (a < 10) {
		return to_string(a);
	}
	else {
		switch (a) {
		case 10:
			return "A";
		case 11:
			return "B";
		case 12:
			return "C";
		case 13:
			return "D";
		case 14:
			return "E";
		case 15:
			return "F";
		default:
			return 0;
		}
	}
}


