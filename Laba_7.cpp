// Laba_7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <memory>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;
//класс, для которого создаётся контейнер
class empl
{
public:
	friend ostream& operator<<(ostream& out, const empl& op);
	friend class vector;
	empl()
	{
		id = "0000";
		name = "NoName";
		price = 0;
	}
	empl(std::string i, std::string n, int sal)
	{
		id = i;
		name = n;
		price = sal;
	}
private:
	std::string id;
	std::string name;
	int price;
};

ostream& operator<<(ostream& out, const empl& op)
{
	out << op.id << endl << op.name << endl << op.price << endl;
	return out;
}


//итератор вывода
class my_iterator :public std::iterator<std::output_iterator_tag, empl>
{
	friend class vector;
private:
	my_iterator(empl* p);
public:
	my_iterator(const my_iterator& it);
	bool operator!=(my_iterator const& other) const;
	bool operator==(my_iterator const& other) const;
	empl& operator*() const;
	empl* operator->() const;
	my_iterator& operator++();
	empl& operator[](int);
private:
	empl* p;
};

class check_bound
{
public:
	string str;
	int fl;
	check_bound(int i)
	{
		fl = 1;
		str = "Out of boundaries";
	}
	void msg()
	{
		cout << str << endl;
	}
};


class check_string
{
public:
	string str;
	int fl;
	check_string(string s)
	{
		fl = 1;
		str = "You can't enter characters as price.";
	}
	void msg()
	{
		cout << str << endl;
	}
};

//контейнер
class vector
{
public:
	vector(std::initializer_list<empl> values);
	~vector()
	{
		delete[] data;
	}
	const my_iterator begin() const;
	const my_iterator end() const;
	my_iterator begin();
	my_iterator end();
	void show()
	{
		my_iterator it = this->begin();
		while (it != this->end())
		{
			std::cout << *it << endl;
			++it;
		}
	}
	void resize(int);
	void sort(int, int, int);
	void add()
	{
		string a_id, a_name, m, temp_pos;
		int a_sal, pos;
		cout << "Enter position:" << endl;
		try
		{
			getline(cin, temp_pos);
			for (int i = 0; i < temp_pos.size(); i++)
				if (!isdigit(temp_pos[i]))
					throw check_string(temp_pos);
		}
		catch (check_string bs)
		{
			while (bs.fl == 1)
			{
				bs.msg();
				getline(cin, m);
				for (int i = 0; i < m.size(); i++)
					if (!isdigit(m[i]))
						break;
					else
						bs.fl = 0;
			}
		}
		stringstream in;
		in << temp_pos;
		in >> pos;
		try
		{
			if (pos > size - 1) throw check_bound(pos);
		}
		catch (check_bound bb)
		{
			while (bb.fl == 1)
			{
				bb.msg();
				getline(cin, m);
				for (int i = 0; i < m.size(); i++)
					if (!isdigit(m[i]))
						break;
					else
						bb.fl = 0;
				if (bb.fl == 0)
				{
					stringstream in;
					in << m;
					in >> pos;
					if (pos > size - 1)
						bb.fl = 1;
				}
			}
		}
		cout << "Enter id:" << endl;
		getline(cin, a_id);
		cout << "Enter name:" << endl;
		getline(cin, a_name);
		cout << "Enter salary:" << endl;
		try
		{
			getline(cin, m);
			for (int i = 0; i < m.size(); i++)
				if (!isdigit(m[i]))
					throw check_string(m);
		}
		catch (check_string bs)
		{
			while (bs.fl == 1)
			{
				bs.msg();
				getline(cin, m);
				for (int i = 0; i < m.size(); i++)
					if (!isdigit(m[i]))
						break;
					else
						bs.fl = 0;
			}
		}
		cout << endl << endl;
		stringstream input;
		input << m;
		input >> a_sal;
		my_iterator it = this->begin();
		if (pos == size - 1)
		{
			it[pos].id = a_id;
			it = this->begin();
			it[pos].name = a_name;
			it = this->begin();
			it[pos].price = a_sal;
		}
		else
		{
			int j = size - 1;
			it = this->begin();
			my_iterator it2 = this->begin();
			for (j; j > pos; j--)
			{
				it[j] = it2[j - 1];
				it = this->begin();
				it2 = this->begin();
			}
			it[j].id = a_id;
			it = this->begin();
			it[j].name = a_name;
			it = this->begin();
			it[j].price = a_sal;
		}

	}
	int find()//поиск по имени
	{
		string str;
		cout << "Enter name:" << endl;
		getline(cin, str);
		my_iterator it = this->begin();
		int i = 0;
		while (it != this->end())
		{
			if (it->name == str)
			{
				cout << endl << *it << endl;
				return i;
			}
			i++;
			++it;
		}
		cout << "Didn't find." << endl;
		return -1;
	}
	void del(int num)
	{
		try
		{
			if (num > size || num < 0) throw check_bound(num);
		}
		catch (check_bound bb)
		{
			bb.msg();
			return;
		}
		my_iterator it = this->begin();
		my_iterator it2 = this->begin();
		if (num == size - 1)
			resize(size - 1);
		else
		{
			it[num];
			it2[num + 1];
			while (it2 != this->end())
			{
				*it = *it2;
				++it;
				++it2;
			}
			resize(size - 1);
		}
	}
	int getSize()
	{
		return size;
	}
private:
	size_t size;
	empl* data;
};


vector::vector(std::initializer_list<empl> values) :
	size(values.size())
{
	data = new empl[size];
	std::copy(values.begin(), values.end(), data);
}

const my_iterator vector::begin() const
{
	return my_iterator(data);
}

const my_iterator vector::end() const
{
	return my_iterator(data + size);
}

my_iterator vector::begin()
{
	return my_iterator(data);
}

my_iterator vector::end()
{
	return my_iterator(data + size);
}

my_iterator::my_iterator(empl* p) :
	p(p)
{

}


my_iterator::my_iterator(const my_iterator& it) :
	p(it.p)
{

}

bool my_iterator::operator!=(my_iterator const& other) const
{
	return p != other.p;
}



empl& my_iterator::operator*() const
{
	return *p;
}

empl* my_iterator::operator->() const
{
	return p;
}


my_iterator& my_iterator::operator++()
{
	++p;
	return *this;
}

empl& my_iterator::operator[](int n)
{
	for (int i = 0; i < n; i++)
		++p;
	return *p;
}


bool my_iterator::operator==(my_iterator const& other) const
{
	return p == other.p;
}

void vector::sort(int m, int left, int right)
{
	int l = left, r = right;
	empl mem;
	if ((right - left) > 1)
	{
		while (l < r)
		{
			while ((data[l].name[0] <= data[m].name[0]) && l < m)
				l++;
			while ((data[r].name[0] > data[m].name[0]) && r > m)
				r--;
			if (l < r)
			{
				mem = data[r];
				data[r] = data[l];
				data[l] = mem;
			}
		}
		sort(m / 2, left, m);
		sort((m + right) / 2, m, right);
	}
}



void vector::resize(int new_size)
{
	empl* mem = new empl[new_size];
	if (new_size < size || size == 0) size = new_size;
	for (int i = 0; i < size; i++)
		mem[i] = data[i];
	delete[] data;
	size = new_size;
	data = mem;
}

int main()
{
	empl E = { "11","Cat3",111 };
	empl Q = { "22","Dat1",222 };
	empl W = { "33","Xat2",333 };
	empl R = { "44","Fat4",444 };
	vector V = { E,Q,W,R };
	my_iterator it = V.begin();
	V.show();
	V.resize(5);
	it = V.begin();
	V.add();
	cout << "After add:" << endl;
	V.show();
	V.del(V.find());
	cout << "After del:" << endl;
	V.show();
	V.sort(V.getSize() / 2, 0, V.getSize() - 1);
	cout << "After sorting:" << endl;
	V.show();
	std::cout << std::endl;
	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
