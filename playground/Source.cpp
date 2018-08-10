#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

class string {
public:
	size_t capacity;
	union {
		struct no_small_buffer_t {
			char* data;
			size_t size;
		} no_small_buffer;
		struct small_buffer_t {
			char data[sizeof(no_small_buffer_t)];
		}small_buffer;
	} impl;
};



template <typename T>
class array
{
	size_t len;
	T* arr;
public:
	array(size_t len = 8) : len(len), arr(new T[len]) {}
	~array() { delete[] arr; }
};



class A 
{
public:
	int p;
private:
	int a; 
protected:
	int y;
};

/*Struct inherits public members to public:
Class inherits public to */

//B inherits A public to private 
class B : A {};

//C inherits A public to public
class C : public A {};

//D inherits A public to public
struct D : A {};

//E inherits public to private
struct E : private A {};



class employee
{
public:
	//...
	typedef employee inherited;
	virtual void print();
};

class foreman : employee
{
public:
	//...
	typedef foreman inherited;
	void print();
};

class manager : foreman
{
public:
	//...
	void mprint()
	{
		inherited::print();
	}
};




class window
{
protected:
	void draw_this()
	{
		std::cout << "command: draw window" << std::endl;
	}
public:
	virtual void draw()
	{
		draw_this();
		std::cout << "OK: drawn window" << std::endl; 
	}
};

class window_w_border : virtual public window
{
protected:
	void draw_this()
	{
		std::cout << "command: draw border" << std::endl;
	}
public:
	void draw()
	{
		window::draw();
		draw_this();
		std::cout << "OK: drawn window with border" << std::endl;
	}
};

class window_w_menu : virtual public window
{
protected:
	void draw_this()
	{
		std::cout << "command: draw menu" << std::endl;
	}
public:
	void draw() 
	{
		window::draw();
		draw_this();
		std::cout << "OK: drawn window with menu" << std::endl; 
	}
};

class window_w_border_and_menu :
	public window_w_menu, 
	public window_w_border
{
protected:
	void draw_this()
	{
		window_w_border::draw_this();
		window_w_menu::draw_this();
	}
public:
	void draw()
	{
		window::draw();
		draw_this();
		std::cout << "OK: drawn window with menu and border" << std::endl;
	}
};





class human
{
private:
	std::string name;
public:
	human() {}
	human(const std::string& n) : name(n) {}
	human(const human& h) : name(h.name) {}
	human* clone() { return new human(name); }
	const std::string& get_name() const { return name; }
	virtual void print(std::ostream& os) { os << *this; }
	friend std::ostream& operator<<(std::ostream& os, const human& h) { return os << "name: " << h.get_name(); }
	~human() {}
};

human h("kjhgkj");
human h2("mnbmnb");
human h3("oipu");
human h4("khfsdgk");
//уродливо, вектор клонов :)
std::vector<human*> vec{ h.clone(), h2.clone(), h3.clone(), h4.clone() }; 
std::vector<human*> vec2{ new human(h), new human(h2), new human(h3), new human(h4) };
//вектор "новорожденных"
std::vector<human*> vec3{ new human("hjsd"), new human("oiuo"), new human("qweqw"), new human(",mn,") };

class student : public human
{
	int group;
public:
	student() {}
	student(const std::string& n, int g) : human(n), group(g) {}
	void print(std::ostream& os) { os << *this; }
	friend std::ostream& operator<<(std::ostream& os, const student& h) 
	{
		os << "name: " << h.get_name() << ", group: " << h.group; 
		return os;
	}
	~student() {}
};

student s("ksjdfh", 123);

class Someone
{
private:
	human* ptr;
public:
	Someone() : ptr(new human) {}
	template <typename T>
	Someone(const T& t) : ptr(new T(t)) {}
	friend std::ostream& operator<<(std::ostream& os, const Someone& S) { S.ptr->print(os); return os; }
	~Someone() {}
};

Someone a(s);





static class x {
public:
	x() { std::cout << "init\n"; }
	~x() { std::cout << "delete"; }
} v;





int main()
{
	B b;
	C c;
	D d;
	E e;



	window w;
	w.draw();

	window_w_border wb;
	wb.draw();

	window_w_menu wm;
	wm.draw();

	window_w_border_and_menu wbm;
	wbm.draw();





	std::vector<Someone> People{ s, s, h, h };
	
	for (Someone hm : People)
		std::cout << hm << "\n";






	std::locale russian(".866");
	std::wcout.imbue(russian);
	std::wcin.imbue(russian);

	std::wstring str;

	std::getline(std::wcin, str);

	std::wcout << str << '\n';

	return 0;
}