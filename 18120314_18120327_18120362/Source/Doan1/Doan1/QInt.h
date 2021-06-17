#pragma once
#include <math.h>
#include "Chuyendoi.h"
class QInt
{
private:
	int arrayBits[4];
public:
	QInt();
	~QInt();

	void set_2_QInt(string a);
	void set_10_QInt(string a);
	void set_16_QInt(string a);

	string get_2_QInt();
	string get_10_QInt();
	string get_16_QInt();

	string change_2_to_2(string a);
	string change_2_to_10(string a);
	string change_2_to_16(string a);

	string change_10_to_2(string a);
	string change_10_to_10(string a);
	string change_10_to_16(string a);

	string change_16_to_2(string a);
	string change_16_to_10(string a);
	string change_16_to_16(string a);

	QInt ror();
	QInt rol();

	void Bu2(QInt& a);
	int batbit(int& a, int i);
	int tatbit(int& a, int i);
	int laybit(int a, int i);
	int daobit(int& a, int i);
	void Div2(string& a);
	string dec_to_hex(int a);

	QInt operator >>(int num) {
		while (num / 32 > 0) {
			//dịch phải 32 bit
			for (int i = 3; i > 0; i--)
				this->arrayBits[i] = this->arrayBits[i - 1];

			if (laybit(this->arrayBits[1], 31) == 1)
				this->arrayBits[0] = -1;
			else
				this->arrayBits[0] = 0;
			num -= 32;
		}
		for (int i = 3; i >= 0; i--) {
			//dịch phải từng phần tử của arrayBits
			this->arrayBits[i] = this->arrayBits[i] >> num;
			if (i > 0) {
				for (int j = 0; j < num; j++) {
					if (laybit(this->arrayBits[i - 1], num - j - 1) == 1)
						this->arrayBits[i] = batbit(this->arrayBits[i], 31 - j);
					else
						this->arrayBits[i] = tatbit(this->arrayBits[i], 31 - j);
				}
			}

		}
		return *this;
	}
	QInt operator <<(int num) {
		while (num / 32 > 0) {
			//dịch trái 32 bit
			for (int i = 0; i < 3; i++)
				this->arrayBits[i] = this->arrayBits[i + 1];

			this->arrayBits[3] = 0;
			num -= 32;
		}
		for (int i = 0; i <= 3; i++) {
			//dịch trái từng phần tử arrayBits 
			this->arrayBits[i] = this->arrayBits[i] << num;
			if (i < 3) {
				for (int j = 0; j < num; j++) {
					if (laybit(this->arrayBits[i + 1], 31 - j) == 1)
						this->arrayBits[i] = batbit(this->arrayBits[i], num - j - 1);
					else
						this->arrayBits[i] = tatbit(this->arrayBits[i], num - j - 1);
				}
			}
		}
		return *this;
	}
	QInt operator =(QInt b) {
		for (int i = 0; i <= 3; i++)
			this->arrayBits[i] = b.arrayBits[i];
		return *this;
	}
	QInt operator +(QInt b) {
		char temp = 0; //biến dùng để nhớ
		char a_bit, b_bit; //biến dùng để lấy từng bit của 2 số hạng để cộng
		QInt tong;
		for (int i = 3; i >= 0; i--) {
			for (int j = 0; j < 32; j++) {
				a_bit = (this->arrayBits[i] >> j) & 1;
				b_bit = (b.arrayBits[i] >> j) & 1;

				//nếu bit tương ứng ở tong = 0 và đang nhớ 1, bật bit đó 
				if (temp == 1) {
					tong.arrayBits[i] = this->batbit(tong.arrayBits[i], j);
					temp = 0;
				}

				//nếu bit tương ứng của a và b đều = 1, nhớ 1
				if (a_bit == 1 && b_bit == 1) {
					temp = 1;
				}
				else if (a_bit + b_bit == 1) {
					//vì đã cộng biến nhớ vào tổng trước đó nên ta chỉ cần đảo bit tổng tương ứng
					tong.arrayBits[i] = this->daobit(tong.arrayBits[i], j);
					if (laybit(tong.arrayBits[i], j) == 0)
						temp = 1;
				}
			}
		}

		return tong;
	}
	QInt operator -(QInt b) {
		Bu2(b);
		return *this + b;
	}
	QInt operator *(QInt b) {
		QInt A;
		int k = 128;
		char Q1 = 0;
		while (k > 0) {
			switch (laybit(this->arrayBits[3], 0) - Q1) {
			case 1: {
				A = A - b;
				break;
			}
			case -1: {
				A = A + b;
				break;
			}
			case 0: {
				break;
			}
			default:
				break;
			}

			Q1 = laybit(this->arrayBits[3], 0);
			*this >> 1;
			if (laybit(A.arrayBits[3], 0) == 0)
				this->arrayBits[0] = tatbit(this->arrayBits[0], 31);
			else
				this->arrayBits[0] = batbit(this->arrayBits[0], 31);
			A >> 1;

			k--;
		}
		return *this;
	}
	QInt operator /(QInt b) {
		QInt A;
		int k = 128;
		int dau_am = 0;//biến dùng để xác định dấu của thương

		//nếu số chia âm, đổi dấu số chia và +1 vào biến dau_am
		if (laybit(b.arrayBits[0], 31) == 1) {
			b.Bu2(b);
			dau_am++;
		}

		//tương tự cho số bị chia
		if (laybit(this->arrayBits[0], 31) == 1) {
			this->Bu2(*this);
			dau_am++;
		}

		while (k > 0) {
			//dich trái [A,*this]
			A << 1;
			if (laybit(this->arrayBits[0], 31) == 1)
				A.arrayBits[3] = batbit(A.arrayBits[3], 0);
			*this << 1;

			A = A - b;

			//nếu A < 0, restore A, ngược lại, bật bit 0 của *this
			if (laybit(A.arrayBits[0], 31) == 1)
				A = A + b;
			else
				this->arrayBits[3] = batbit(this->arrayBits[3], 0);

			k--;
		}

		//nếu 1 trong 2 số bị chia và số chia âm, dau_am = 1, đổi dấu thương
		if (dau_am == 1)
			this->Bu2(*this);

		return *this;
	}
	QInt operator &(QInt b) {
		QInt temp;
		for (int i = 0; i < 4; i++) {
			temp.arrayBits[i] = this->arrayBits[i] & b.arrayBits[i];
		}
		return temp;
	}
	QInt operator |(QInt b) {
		QInt temp;
		for (int i = 0; i < 4; i++) {
			temp.arrayBits[i] = this->arrayBits[i] | b.arrayBits[i];
		}
		return temp;
	}
	QInt operator ^(QInt b) {
		QInt temp;
		for (int i = 0; i < 4; i++) {
			temp.arrayBits[i] = this->arrayBits[i] ^ b.arrayBits[i];
		}
		return temp;
	}
	QInt operator ~() {
		QInt temp;
		for (int i = 0; i < 4; i++) {
			temp.arrayBits[i] = ~this->arrayBits[i];
		}
		return temp;
	}
};

