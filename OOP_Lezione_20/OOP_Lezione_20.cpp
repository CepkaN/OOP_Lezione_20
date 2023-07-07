#include<iostream>
#include<vector>
#include<string>
#include<tuple>
#include<memory>
#include<typeinfo> // библиотека для узнавания того, чем мы работаем
#include<type_traits> // узнаём свойства типа данных, заставляет работать , не вызываяя методы.



class fff {
	int g = 0;
};

class ddd :public fff {
	int f = 0;
};

class IPrintable {
public:
	virtual void Print()const = 0;
};

class IFOO {
public:
	virtual void FOO()= 0;
};

class A:virtual public IPrintable ,public IFOO{
private:
	int var;
public:
	virtual ~A(){}
	A() = default;
	A(int a):var(a){ }
	void foo() {
		var = 4;
	}
	void Print()const override{
		std::cout << "Что-то\n";
	}
	void FOO() override {
		std::cout << "bbbbb\n";
	}
};

class B :public A{
public:
	B():A(0){}
	~B()override {
	}
};
void Bar(const IPrintable& ob) {
	std::string tmp = typeid(ob).name();
	ob.Print();
}
void Bar2(IFOO& ob) {
	std::string tmp = typeid(ob).name();
	ob.FOO();
}

template<typename T, typename U>
auto&& F(const T& x, const U& y) {
	return x < y ? x : y;
}
template<typename Container>
decltype(auto) get_at(Container& container, size_t index) //-> decltype(container[index]) 
{
	return container[index];
}

template<typename T>
void swap1(T& x, T& y) {  // функция swap
	T t = std::move(x);
	x = std::move(y);
	y = std::move(t);
}


int main() {
	setlocale(LC_ALL, "Russian");
	double a = 5;
	const int p = 7;
	char k = static_cast<char>(a);
	std::cout << k << ' ' << sizeof(k) << '\n';

	
	ddd D;
	fff F;

	dynamic_cast<fff&>(D);
	const_cast<int&>(p);
	reinterpret_cast<int&>(a);
	volatile double b = 9;  // для хакеров ХР

	int v1 = 12; int v2 = 100;
	std::cout << v1 << ' ' << v2 << '\n';
	swap1(v1, v2);
	std::cout << v1 << ' ' << v2 << '\n';

	std::vector<int>v(10);
	get_at(v, 3) = 3;
	for (auto& it : v) {
		std::cout << it << ' ';
	}
	std::cout << '\n';

	A* pa = new B;
	A* pa2 = nullptr;
	A* pa3 = new A;

	A& ref = *pa;
	A& ref2 = *pa3;
	A& ref3 = *pa2;  // так нельзя делать.
	

	std::string tmp = typeid(*pa).name();
	std::cout << tmp << '\n';

	try {
		tmp = typeid(*pa2).name();
	}
	catch (...) { std::cerr << "Жееесть!!!\n"; }
	tmp = typeid(*pa3).name();
	std::cout << tmp << '\n';
	tmp = typeid(ref).name();
	std::cout << tmp << '\n';
	tmp = typeid(ref2).name();
	std::cout << tmp << '\n';
	std::cout << std::is_abstract<A>();  // является ли класс абстрактным
	//static_assert( std::is_abstract<A>());
	bool res = std::is_abstract<A>();

	std::vector<A>arr;
	arr.reserve(10);

	std::vector<A>arr2(10);

	std::cout<<std::hash<int>()(9);  // кодирование числа огромным числом
	// лучше сравнивать результаты хеш функций , чем строки.
	std::cout << '\n';
	std::hash<std::string>()("bbbbbb") > std::hash<std::string>()("aaaaaa") ? (std::cout << "Больше ") : (std::cout << "Неа");
	std::cout << "\n\n";

	Bar(*pa);
	Bar(*pa3);
	Bar(ref);
	B* pb = new B;
	Bar2(*pb);


	return 0;
}