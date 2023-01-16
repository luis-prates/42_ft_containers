/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:05:17 by lprates           #+#    #+#             */
/*   Updated: 2023/01/16 23:03:03 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <string>
#include <deque>
#if FT == 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <list>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
	#include <list>

#endif

#include <stdlib.h>
//#include "../includes/ft_containers.hpp"

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

// copy construct
//#define T1 int
//#define T2 int

// erase
#define T1 int
#define T2 std::string
typedef ft::pair<T1, T2> T3;

// insert
/*#define T1 int
#define T2 std::string
typedef ft::map<T1, T2>::value_type T3;
typedef ft::map<T1, T2>::iterator iterator;*/

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

static int iter = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "ret: " << mp.erase(param) << std::endl;
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param, param2);
	printSize(mp);
}

// insert
/*
template <typename MAP, typename U>
void	ft_insert(MAP &mp, U param)
{
	ft::pair<iterator, bool> tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param);
	std::cout << "insert return: " << printPair(tmp.first);
	std::cout << "Created new node: " << tmp.second << std::endl;
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_insert(MAP &mp, U param, V param2)
{
	iterator tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param, param2);
	std::cout << "insert return: " << printPair(tmp);
	printSize(mp);
}*/

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cout << "Inside catch: This is normal :)\n"; 
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		int rng1 = rand(), rng2 = rand();
		//std::cout << "inserting " << i << " with key pair: " << i << " : " << i << std::endl; 
		map_int.insert(ft::make_pair(rng1, rng2));
	}

	//! for comp and bounds test
	/*typedef ft::map<int, int>::value_type T3;
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i + 1, (i + 1) * 3));
	ft::map<int, int> mp(lst.begin(), lst.end());

	printSize(mp);

	std::cout << "begin key: " << mp.begin()->first << " end key: " << mp.end()->first << std::endl;*/
	//copy_constructor
	/*
	typedef ft::pair<const int, int> T3;
	std::list<T3> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(lst_size - i, i));

	std::cout << "start\n";
	ft::map<T1, T2> mp(lst.begin(), lst.end());
	std::cout << "checkpoint 1\n";
	printSize(mp);
	ft::map<T1, T2>::iterator it = mp.begin(), ite = mp.end();
	std::cout << "checkpoint 2\n";
	ft::map<T1, T2> mp_range(it, --(--ite));
	std::cout << "checkpoint 3\n";
	//printSize(mp_range);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;
	std::cout << "checkpoint 4\n";

	it = mp.begin(); ite = --(--mp.end());
	std::cout << "checkpoint 5\n";
	ft::map<T1, T2> mp_copy(mp);
	std::cout << "checkpoint 6\n";
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;
	std::cout << "checkpoint 7\n";
	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(mp);
	printSize(mp_range);
	printSize(mp_copy);

	mp = mp_copy;
	mp_copy = mp_range;
	mp_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(mp);
	printSize(mp_range);
	printSize(mp_copy);
	return (0);*/
	

	//erase
	/*
	std::list<T3> lst;
	unsigned int lst_size = 10;
	std::cout << "checkpoint -1\n";
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	std::cout << "checkpoint 0\n";
	ft::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	std::cout << "checkpoint 1\n";

	ft_erase(mp, ++mp.begin());
	std::cout << "checkpoint 2\n";

	ft_erase(mp, mp.begin());
	std::cout << "checkpoint 3\n";

	//TODO: fix this one. When deleted node is the one attached to the ghost node!
	//! Fixed!
	ft_erase(mp, --mp.end());

	ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
	ft_erase(mp, --(--(--mp.end())), --mp.end());

	mp[10] = "Hello";
	mp[11] = "Hi there";
	printSize(mp);
	ft_erase(mp, --(--(--mp.end())), mp.end());

	mp[12] = "ONE";
	mp[13] = "TWO";
	mp[14] = "THREE";
	mp[15] = "FOUR";
	printSize(mp);
	ft_erase(mp, mp.begin(), mp.end());*/

	// erase 2
	/*
	std::list<T3> lst;
	unsigned int lst_size = 6;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	ft::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	for (int i = 2; i < 4; ++i)
		ft_erase(mp, i);

	ft_erase(mp, mp.begin()->first);
	ft_erase(mp, (--mp.end())->first);

	mp[-1] = "Hello";
	mp[10] = "Hi there";
	mp[10] = "Hi there";
	printSize(mp);

	ft_erase(mp, 0);
	ft_erase(mp, 1);
	*/

	// tricky erase
	/*
	ft::map<T1, T2> mp;

	mp[42] = "lol";

	mp[50] = "mdr";
	mp[25] = "funny";

	mp[46] = "bunny";
	mp[21] = "fizz";
	mp[30] = "buzz";
	mp[55] = "fuzzy";

	mp[18] = "bee";
	mp[23] = "coconut";
	mp[28] = "diary";
	mp[35] = "fiesta";
	mp[44] = "hello";
	mp[48] = "world";
	mp[53] = "this is a test";
	mp[80] = "hey";

	mp[12] = "no";
	mp[20] = "idea";
	mp[22] = "123";
	mp[24] = "345";
	mp[27] = "27";
	mp[29] = "29";
	mp[33] = "33";
	mp[38] = "38";

	mp[43] = "1";
	mp[45] = "2";
	mp[47] = "3";
	mp[49] = "4";
	mp[51] = "5";
	mp[54] = "6";
	mp[60] = "7";
	mp[90] = "8";

	printSize(mp);

	ft_erase(mp, 25); // right != NULL; left != NULL
	ft_erase(mp, 55); // right != NULL; left != NULL
	*/
	int sum = 0;
	for (int i = 0; i < COUNT; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}

	// insert
	/*ft::map<T1, T2> mp, mp2;

	ft_insert(mp, T3(42, "lol"));
	ft_insert(mp, T3(42, "mdr"));

	ft_insert(mp, T3(50, "mdr"));
	ft_insert(mp, T3(35, "funny"));

	ft_insert(mp, T3(45, "bunny"));
	ft_insert(mp, T3(21, "fizz"));
	ft_insert(mp, T3(38, "buzz"));

	ft_insert(mp, mp.begin(), T3(55, "fuzzy"));

	ft_insert(mp2, mp2.begin(), T3(1337, "beauty"));
	ft_insert(mp2, mp2.end(), T3(1000, "Hello"));
	ft_insert(mp2, mp2.end(), T3(1500, "World"));*/
	
	std::cout << std::endl;
	return (0);
}

/*
#include <iostream>
#include <string>
#include <deque>
#include "../includes/ft_containers.hpp"
#if FT == 0
# define container std
#else
# define container ft
#endif

void say(std::string std, std::string color = ENDC) {
	std::cout << color << std << ENDC << std::endl;
}

template<class T>
void print_vector_status(container::vector<T> &vec) {
	say("Vector Status", BLUE);
	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Max Size: " << vec.max_size() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;
	std::cout << "Empty? " << (vec.empty() ? "YES" : "NO") << std::endl;
	std::cout << "Content: ";
	if (vec.size() < 50) {
		for (typename container::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	} else {
		unsigned short int i = 0;
		for (typename container::vector<T>::iterator it = vec.begin(); it != vec.end() && i < 20; ++it, ++i)
			std::cout << ' ' << *it;
		say(" more than 50 elements....", RED);
	}
}

template<class T>
void print_vector_status(const container::vector<T> &vec) {
	say("Vector Status", BLUE);
	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Max Size: " << vec.max_size() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;
	std::cout << "Empty? " << (vec.empty() ? "YES" : "NO") << std::endl;
	std::cout << "Content: ";
	if (vec.size() < 50) {
		for (typename container::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	} else {
		unsigned short int i = 0;
		for (typename container::vector<T>::const_iterator it = vec.begin(); it != vec.end() && i < 20; ++it, ++i)
			std::cout << ' ' << *it;
		say(" more than 50 elements....", RED);
	}
}

void test_vector_constructors(void) {
	say("****************", RED);
	say("* CONSTRUCTORS *", RED);
	say("****************", RED);
	{
		say("Construct a vector of 100,000 with the value 9", YELLOW);
		container::vector<int> vec1 (100000, 9);
		print_vector_status(vec1);
		say("Construct a vector of 3,000,000 with default value", YELLOW);
		container::vector<int> vec2 (3000000);
		print_vector_status(vec2);
		say("Construct an empty vector", YELLOW);
		container::vector<int> vec3;
		print_vector_status(vec3);
	}
	{
		say("Copy Constructor test", YELLOW);
		container::vector<int> vct(5);
		container::vector<int>::iterator it = vct.begin(), ite = vct.end();

		std::cout << "len: " << (ite - it) << std::endl;
		for (; it != ite; ++it)
			*it = (ite - it);

		it = vct.begin();
		container::vector<int> vct_range(it, --(--ite));
		for (int i = 0; it != ite; ++it)
			*it = ++i * 5;

		it = vct.begin();
		container::vector<int> vct_copy(vct);
		for (int i = 0; it != ite; ++it)
			*it = ++i * 7;
		vct_copy.push_back(42);
		vct_copy.push_back(21);

		std::cout << "\t-- PART ONE --" << std::endl;
		print_vector_status(vct);
		print_vector_status(vct_range);
		print_vector_status(vct_copy);

		vct = vct_copy;
		vct_copy = vct_range;
		vct_range.clear();

		std::cout << "\t-- PART TWO --" << std::endl;
		print_vector_status(vct);
		print_vector_status(vct_range);
		print_vector_status(vct_copy);

	}
}

// class Obj {
// 	public:
// 		Obj(): _n(0) {}
// 		Obj(size_t n): _n(n) {}
// 		size_t m() const {return(_n);}
// 	private:
// 		int _n;
// };
// std::ostream& operator<<(std::ostream& os, const Obj& obj) {
// 	os << obj.m() << std::endl;
//     return os;
// }

void test_vector_iterators(void) {
	say("**************", RED);
	say("* IITERATORS *", RED);
	say("**************", RED);
	{
		const int size = 5;
		container::vector<std::string> vct(size);
		container::vector<std::string>::iterator it(vct.begin());
		container::vector<std::string>::const_iterator ite(vct.end());

		for (int i = 1; ite != it; ++i)
			*it++ = std::string(i, i + 65);
		print_vector_status(vct);

		it = vct.begin();
		ite = vct.begin();

		std::cout << *(++ite) << std::endl;
		std::cout << *(ite++) << std::endl;
		std::cout << *ite++ << std::endl;
		std::cout << *++ite << std::endl;

		it->length();
		ite->length();

		std::cout << *(++it) << std::endl;
		std::cout << *(it++) << std::endl;
		std::cout << *it++ << std::endl;
		std::cout << *++it << std::endl;

		std::cout << *(--ite) << std::endl;
		std::cout << *(ite--) << std::endl;
		std::cout << *--ite << std::endl;
		std::cout << *ite-- << std::endl;

		(*it).length();
		(*ite).length();

		std::cout << *(--it) << std::endl;
		std::cout << *(it--) << std::endl;
		std::cout << *it-- << std::endl;
		std::cout << *--it << std::endl;
	}
	{
		say("Rev iterators", YELLOW);
		const int size = 5;
		container::vector<int> vct(size);
		container::vector<int>::iterator it_ = vct.begin();
		container::vector<int>::reverse_iterator it(it_);

		for (int i = 0; i < size; ++i)
			vct[i] = (i + 1) * 5;
		print_vector_status(vct);

		std::cout << (it_ == it.base()) << std::endl;
		std::cout << (it_ == (it + 3).base()) << std::endl;

		std::cout << *(it.base() + 1) << std::endl;
		// std::cout << *(it - 3) << std::endl;
		std::cout << *(it - 3).base() << std::endl;
		it -= 3;
		std::cout << *it.base() << std::endl;

		std::cout << "TEST OFFSET" << std::endl;
		// std::cout << *(it) << std::endl;
		std::cout << *(it).base() << std::endl;
		std::cout << *(it - 0) << std::endl;
		std::cout << *(it - 0).base() << std::endl;
		std::cout << *(it - 1).base() << std::endl;
	}
	{
		// const int size = 5;
		// container::vector<int> vct(size);
		// container::vector<int>::reverse_iterator it = vct.rbegin();
		// container::vector<int>::const_reverse_iterator ite = vct.rbegin();

		// for (int i = 0; i < size; ++i)
		// 	it[i] = (size - i) * 5;

		// it = it + 5;
		// it = 1 + it;
		// it = it - 4;
		// std::cout << *(it += 2) << std::endl;
		// std::cout << *(it -= 1) << std::endl;

		// *(it -= 2) = 42;
		// *(it += 2) = 21;

		// std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

		// std::cout << "(it == const_it): " << (ite == it) << std::endl;
		// std::cout << "(const_ite - it): " << (ite - it) << std::endl;
		// std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

		// print_vector_status(vct);
	}
}


static void	checkErase(container::vector<std::string> const &vct, container::vector<std::string>::const_iterator const &it) {
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	print_vector_status(vct);
}

void test_vector_capacity(void) {
	say("************", RED);
	say("* CAPACITY *", RED);
	say("************", RED);	
	{
		say("Resizing A VECTOR & RESERVING CAPACITY", YELLOW);
		container::vector<int> myvector;

		say("Construct a vector [1..9]", YELLOW);
		for (int i=1;i<10;i++) myvector.push_back(i);
		print_vector_status(myvector);
		say("Resize(5)", YELLOW);
		myvector.resize(5);
		print_vector_status(myvector);
		say("Resize(8, 100)", YELLOW);
		myvector.resize(8,100);
		print_vector_status(myvector);
		say("Resize(12)", YELLOW);
		myvector.resize(12);
		print_vector_status(myvector);
		say("Reserve(50)", YELLOW);
		myvector.reserve(50);
		print_vector_status(myvector);
		say("Add 100000 random elements to see how the vector grows in capacity", YELLOW);
		for (int i=1;i<100000;i++) myvector.push_back(rand() % i);
		print_vector_status(myvector);

	}
	{
		say("erase() tests:", YELLOW);
		container::vector<std::string> vct(10);

		for (unsigned long int i = 0; i < vct.size(); ++i)
			vct[i] = std::string((vct.size() - i), i + 65);
		print_vector_status(vct);

		checkErase(vct, vct.erase(vct.begin() + 2));

		checkErase(vct, vct.erase(vct.begin()));
		checkErase(vct, vct.erase(vct.end() - 1));

		checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
		checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

		vct.push_back("Hello");
		vct.push_back("Hi there");
		print_vector_status(vct);
		checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

		vct.push_back("ONE");
		vct.push_back("TWO");
		vct.push_back("THREE");
		vct.push_back("FOUR");
		print_vector_status(vct);
		checkErase(vct, vct.erase(vct.begin(), vct.end()));
	}

}

void test_vector_element_access(void) { 
	say("******************", RED);
	say("* ELEMENT ACCESS *", RED);
	say("******************", RED);
	{
		say("at() exceptions", YELLOW);
		container::vector<std::string> myvector;
		try {
			std::cout << myvector.at(0) << std::endl;
		} catch (std::out_of_range &e) {
			std::cout << RED << e.what() << ENDC << std::endl;
		}
		try {
			myvector.push_back("Hello World");
			myvector.push_back("Bye World");
			std::cout << myvector.at(9) << std::endl;
		} catch (std::out_of_range &e) {
			std::cout << RED << e.what() << ENDC << std::endl;
		}
	}
	{
		say("back() & front()", YELLOW);
		container::vector<int> myvector;

		myvector.push_back(10);
		while (myvector.back() != 0)
			myvector.push_back ( myvector.back() - 1 );
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size() ; i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
		myvector.clear();
		myvector.push_back(78);
		myvector.push_back(16);
		myvector.front() -= myvector.back();
		std::cout << "myvector.front() is now " << myvector.front() << '\n';
	}
	{
		say("more back() & front()", YELLOW);
		container::vector<int> vct(7);

		for (unsigned long int i = 0; i < vct.size(); ++i)
		{
			vct.at(i) = (vct.size() - i) * 3;
			std::cout << "vct.at(): " << vct.at(i) << " | ";
			std::cout << "vct[]: " << vct[i] << std::endl;
		}
		print_vector_status(vct);


		container::vector<int> const vct_c(vct);

		print_vector_status(vct_c);

		std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
		std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;


		try {
			vct.at(10) = 42;
		}
		catch (std::out_of_range &e) {
			std::cout << "Catch out_of_range exception!" << std::endl;
		}
		catch (std::exception &e) {
			std::cout << "Catch exception: " << e.what() << std::endl;
		}

	}
}

void test_vector_modifiers(void) {
	say("*************", RED);
	say("* MODIFIERS *", RED);
	say("*************", RED);
	{
		say("assign() to a vector which already has elements", YELLOW);
		container::vector<int> myvector;
		say("Before", BLUE);
		myvector.push_back(25);
		while (myvector.back() != 0)
			myvector.push_back ( myvector.back() - 1 );
		print_vector_status(myvector);
		say("After", BLUE);
		myvector.assign(10, 500);
		print_vector_status(myvector);
	}
	{
		say("Testing pop_back() with a vector of 3 elements [100, 200, 300]", YELLOW);
		container::vector<int> myvector;
		int sum (0);
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);
		print_vector_status(myvector);
		
		while (!myvector.empty()) {
			sum+=myvector.back();
			myvector.pop_back();
			say("pop_back()", YELLOW);
			print_vector_status(myvector);
		}
		std::cout << "The elements of myvector add up to " << sum << '\n';
	}
	{
		say("Testing insert()", YELLOW);

		container::vector<int> myvector (3,100);
		container::vector<int>::iterator it;

		say("Original:", YELLOW);
		print_vector_status(myvector);
		it = myvector.begin() + 1;
		it = myvector.insert (it, 200);
		say("Insert single at begin() + 1:", YELLOW);
		print_vector_status(myvector);

		myvector.insert (it, 2, 300);
		say("Insert n(2) elements at iterator begin() + 1 BEFORE last insert:", YELLOW);
		print_vector_status(myvector);
		// "it" no longer valid, get a new one:
		it = myvector.begin();

		say("Another Original vector:", YELLOW);
		container::vector<int> anothervector (2,400);
		print_vector_status(anothervector);
		myvector.insert (it+2 ,anothervector.begin(),anothervector.end());
		say("Insert to the old vector, using iterators begin() & end() of another original vector at begin() + 2", YELLOW);
		print_vector_status(myvector);

		int myarray [] = {501, 502, 503};
		myvector.insert (myvector.begin(), myarray, myarray+3);
		say("Insert to original vector using an array {501, 502, 503} (with iterators) at begin()", YELLOW);
		print_vector_status(myvector);

		std::cout << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
			std::cout << ' ' << *it;
		std::cout << '\n';

		say("Insert Test 2", YELLOW);
		container::vector<int> vct(8);
		container::vector<int> vct2;
		container::vector<int> vct3;

		for (unsigned long int i = 0; i < vct.size(); ++i)
			vct[i] = (vct.size() - i) * 3;
		print_vector_status(vct);

		vct2.insert(vct2.end(), 42);
		print_vector_status(vct2);
		vct2.insert(vct2.begin(), 2, 21);
		print_vector_status(vct2);

		vct2.insert(vct2.end() - 2, 42);
		print_vector_status(vct2);

		vct2.insert(vct2.end(), 2, 84);
		print_vector_status(vct2);

		vct2.resize(4);
		print_vector_status(vct2);

		vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
		vct.clear();
		print_vector_status(vct2);

		print_vector_status(vct);

		for (int i = 0; i < 5; ++i)
			vct3.insert(vct3.end(), i);
		vct3.insert(vct3.begin() + 1, 2, 111);
		print_vector_status(vct3);
	}
	{
		say("Testing erase()", YELLOW);

		container::vector<int> myvector;

		for (int i=1; i<=10; i++) myvector.push_back(i);

		say("erase the 6th element", YELLOW);
		myvector.erase (myvector.begin()+5);
		print_vector_status(myvector);

		say("erase the first 3 elements", YELLOW);
		myvector.erase (myvector.begin(),myvector.begin()+3);
		print_vector_status(myvector);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}
	{
		say("Testing swap()", YELLOW);

		container::vector<int> foo (3,100);   // three ints with a value of 100
		container::vector<int> bar (5,200);   // five ints with a value of 200		

		say("foo contains:", YELLOW);
		print_vector_status(foo);

		say("bar contains:", YELLOW);
		print_vector_status(bar);

		say("swap()", YELLOW);
		foo.swap(bar);

		say("foo contains:", YELLOW);
		print_vector_status(foo);

		say("bar contains:", YELLOW);
		print_vector_status(bar);
	}
}

void test_vector_non_member_functions() {
	say("************************", RED);
	say("* NON_MEMBER FUNCTIONS *", RED);
	say("************************", RED);
	{
		container::vector<int> foo (3,42);   // three ints with a value of 100
		container::vector<int> bar (2,42);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	say("******************", GREEN);
	{
		container::vector<int> foo (3,200);   // three ints with a value of 100
		container::vector<int> bar (3,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	say("******************", GREEN);
	{
		container::vector<int> foo (3,200);
		container::vector<int> bar (3,100);

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	say("******************", GREEN);
	{
		container::vector<int> foo (10,200);
		container::vector<int> bar (103,42);
		print_vector_status(foo);
		print_vector_status(bar);

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
}

// void test_map_constructors() {
// 	say("****************", RED);
// 	say("* CONSTRUCTORS *", RED);
// 	say("****************", RED);
// 	{
// 		say("Construct an empty vector", YELLOW);
// 		std::map<char,int> mymap;
// 		say("Insert Values", YELLOW);
// 		mymap['b'] = 100;
// 		mymap['a'] = 200;
// 		mymap['c'] = 300;
// 		for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//     		std::cout << it->first << " => " << it->second << std::endl;
// 	}
// }

void bt_test(void) {
	say("****************", RED);
	say("* Testing PAIR *", RED);
	say("****************", RED);
	container::pair<int, char> pair;
	pair = container::make_pair(999, 'a');
	std::cout << pair.first << ", " << pair.second << std::endl;
	//
	say("****************", RED);
	say("* Testing NODE *", RED);
	say("****************", RED);
	ft::Node<ft::pair<int, char>, std::less<int> > *root = new ft::Node<ft::pair<int, char>, std::less<int> >(ft::make_pair(999, 'a'));
	ft::Node<ft::pair<int, char>, std::less<int> > *child1 = new ft::Node<ft::pair<int, char>, std::less<int> >(ft::make_pair(1, 'z'));
	ft::Node<ft::pair<int, char>, std::less<int> > *child2 = new ft::Node<ft::pair<int, char>, std::less<int> >(ft::make_pair(4999, 'y'));
	ft::Node<ft::pair<int, char>, std::less<int> > *child3 = new ft::Node<ft::pair<int, char>, std::less<int> >(ft::make_pair(49929, 'e'));
	root->put_left(child1);
	root->put_right(child2);
	child2->put_right(child3);
	std::cout << "Size: " << root->size() << " | Height: " << root->height() << std::endl;
	root->display();
	say("***************", RED);
	say("* Testing RBT *", RED);
	say("***************", RED);
	ft::RedBlackTree<int, char, ft::pair<int, char> > rbt;
	say("***************", RED);
	say("* Testing Map *", RED);
	say("***************", RED);
	// rbt.insert(9);
	// rbt.insert(1);
	// rbt.insert(10);
	// rbt.insert(99);
	// rbt.insert(100);
	// rbt.insert(130);
	// rbt.insert(0);
	// rbt.insert(3);
	// rbt.insert(4);
	rbt.displayRBT();
	say("************", RED);
	say("* Copy RBT *", RED);
	say("************", RED);
	// ft::RedBlackTree<int, char, ft::pair<int, char> > tmp;
	// tmp = rbt;
	say("***************", RED);
	say("* Find in RBT *", RED);
	say("***************", RED);
	// ft::Node<int, std::less<int> > *res = rbt.find(3);
	// ft::Node<int, std::less<int> > *res2 = rbt.find(30);
	// ft::Node<int, std::less<int> > *res3 = rbt.find(99);
	// if (res)
	// 	res->print_node_info();
	// else
	// 	std::cout<<"\n\t NOT FOUND" << std::endl;
	// if (res2)
	// 	res2->print_node_info();
	// else
	// 	std::cout<<"\n\t NOT FOUND" << std::endl;
	// if (res3)
	// 	res3->print_node_info();
	// else
	// 	std::cout<<"\n\t NOT FOUND" << std::endl;
	// say("*******************", RED);
	// say("* Remove from RBT *", RED);
	// say("*******************", RED);
	// rbt.erase(4);
	// rbt.displayRBT();
	// say("*******************", RED);
	// say("* Remove from RBT *", RED);
	// say("*******************", RED);
	// rbt.erase(99);
	// rbt.displayRBT();
	// say("*******************", RED);
	// say("* Remove from RBT *", RED);
	// say("*******************", RED);
	// rbt.erase(10);
	// rbt.displayRBT();
	// say("****************", RED);
	// say("* Iterator RBT *", RED);
	// say("****************", RED);
	ft::RedBlackTree<int, char, ft::pair<int, char> >::iterator it = rbt.begin();;

	for (; it != rbt.end(); it++) {
		std::cout << *it << ", ";
	}
	std::cout << *it << std::endl;
	delete(root);
	delete(child1);
	delete(child2);
	delete(child3);

}

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

void test_map_constructors() {
	container::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;


	container::map<char,int> second (first.begin(),first.end());

	container::map<char,int> third (second);

	container::map<char,int,classcomp> fourth;                 // class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	container::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
}

void test_map_iterators() {
 	say("*****************", RED);
	say("* Map iterators *", RED);
	say("*****************", RED);
	{
		say("*******************", RED);
		say("* Map begin & end *", RED);
		say("*******************", RED);
		container::map<char,int> mymap;

		mymap['b'] = 100;
		mymap['a'] = 200;
		mymap['c'] = 300;

		// show content:
		for (container::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		say("*********************", RED);
		say("* Map rbegin & rend *", RED);
		say("*********************", RED);
		container::map<char,int> mymap;

		mymap['x'] = 100;
  		mymap['y'] = 200;
  		mymap['z'] = 300;

		container::map<char,int>::reverse_iterator rit;
  		for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
    		std::cout << rit->first << " => " << rit->second << '\n';
	}
}

void test_map_capacity() {
	say("****************", RED);
	say("* Map capacity *", RED);
	say("****************", RED);
	{
		say("************", RED);
		say("* Empty *", RED);
		say("************", RED);
		container::map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		while (!mymap.empty())
		{
		std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
		}
	}
	{
		say("****************", RED);
		say("* EXTREME Size *", RED);
		say("****************", RED);
		std::map<int,char> mymap;

		size_t num = 100000;
		for(size_t x=0;x<num;x++) {
			size_t random = 100000 + (rand() % 9000000);
	  		mymap[random] = random % 128;
	  		mymap[random] = random % 128;
			mymap[random] = random % 128;
		}
		std::cout << "mymap.size() is " << mymap.size() << '\n';
	}
	{
		say("************", RED);
		say("* Max Size *", RED);
		say("************", RED);
		int i;
		container::map<int,int> mymap;

		if (mymap.max_size()>1000) {
			for (i=0; i<1000; i++) mymap[i]=0;
				std::cout << "The map contains 1000 elements.\n";
		}
		else
			std::cout << "The map could not hold 1000 elements.\n";
	}
}

void test_map_element_access() {
	say("******************", RED);
	say("* Element Access *", RED);
	say("******************", RED);
	{
		say("**************", RED);
		say("* operator[] *", RED);
		say("**************", RED);

		container::map<char,std::string> mymap;

		mymap['a']="an element";
		mymap['b']="another element";
		mymap['c']=mymap['b'];

		std::cout << "mymap['a'] is " << mymap['a'] << '\n';
		std::cout << "mymap['b'] is " << mymap['b'] << '\n';
		std::cout << "mymap['c'] is " << mymap['c'] << '\n';
		std::cout << "mymap['d'] is " << mymap['d'] << '\n';

		std::cout << "mymap now contains " << mymap.size() << " elements.\n";
	}
	{
		say("******", RED);
		say("* at *", RED);
		say("******", RED);	
		container::map<std::string,int> mymap;

        mymap["alpha"] = 0;
        mymap["beta"] = 0;
        mymap["gamma"] = 0; 

		mymap.at("alpha") = 10;
		mymap.at("beta") = 20;
		mymap.at("gamma") = 30;

		for (container::map<std::string,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
}

void test_map_modifiers() {
	say("*************", RED);
	say("* Modifiers *", RED);
	say("*************", RED);
	{
		say("**********", RED);
		say("* Insert *", RED);
		say("**********", RED);
		container::map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert ( container::pair<char,int>('a',100) );
		mymap.insert ( container::pair<char,int>('z',200) );

		container::pair<container::map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( container::pair<char,int>('z',500) );
		if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
		}

		// second insert function version (with hint position):
		container::map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, container::pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, container::pair<char,int>('c',400));  // no max efficiency inserting

		// third insert function version (range insertion):
		container::map<char,int> anothermap;
		anothermap.insert(mymap.begin(),mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "anothermap contains:\n";
		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		say("**********", RED);
		say("* Erase *", RED);
		say("**********", RED);
		container::map<char,int> mymap;
		container::map<char,int>::iterator it;

		// insert some values:
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		mymap['d']=40;
		mymap['e']=50;
		mymap['f']=60;
		
		it=mymap.find('b');
		mymap.erase (it);                   // erasing by iterator

		mymap.erase ('c');                  // erasing by key

		it=mymap.find ('e');
		mymap.erase ( it, mymap.end() );    // erasing by range

		// show content:
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		say("********", RED);
		say("* Swap *", RED);
		say("********", RED);
 		container::map<char,int> foo,bar;

		foo['x']=100;
		foo['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;

		foo.swap(bar);

		std::cout << "foo contains:\n";
		for (container::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "bar contains:\n";
		for (container::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		say("********", RED);
		say("* Clear *", RED);
		say("********", RED);
		container::map<char,int> mymap;

		mymap['x']=100;
		mymap['y']=200;
		mymap['z']=300;

		std::cout << "mymap contains:\n";
		for (container::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		mymap.clear();
		mymap['a']=1101;
		mymap['b']=2202;

		std::cout << "mymap contains:\n";
		for (container::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
}

void test_map_non_member_functions() {
	say("**************", RED);
	say("* NON_MEMBER *", RED);
	say("**************", RED);
	container::map<char,int> foo,bar;
	foo['a']=100;
	foo['b']=200;
	bar['a']=10;
	bar['z']=1000;

	// foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

int	main(void) {
	srand(0);
	// std::cout << "Testing Container -> " << (FT == 0 ? "std" : "ft") << std::endl;
	say("Pulgamecanica greets you :D Welcome to ft_containers", WHITE);
	{
		container::vector<int> first;                                // empty vector of ints
		container::vector<int> second (4,100);                       // four ints with value 100
		container::vector<int> third (second.begin(),second.end());  // iterating through second
		container::vector<int> fourth (third);                       // a copy of third

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		container::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		std::cout << "The contents of fifth are [";
		for (container::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << " ]\n";
	}
	{
		try {
			test_vector_constructors();
			test_vector_iterators();
			test_vector_capacity();
			test_vector_element_access(); 
			test_vector_modifiers();
			test_vector_non_member_functions();
		} catch (std::exception &e) {
			std::cout << RED << e.what() << ENDC << std::endl;
		}
	}
	{
		try {
			//bt_test();
			test_map_constructors();
			test_map_iterators();
			test_map_capacity();
			test_map_element_access(); 
			test_map_modifiers();
			test_map_non_member_functions();
		} catch (std::exception &e) {
			std::cout << RED << e.what() << ENDC << std::endl;
		}
	}
	
	return (0);
}*/