#pragma once
#include<iostream>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include<string>
#include<vector>
#include <array>
#include <regex>
#include<random>
#include<stdexcept>

using namespace std;
class Token {
public:
	char kind;
	double value;
	Token(char ch)
	{
		kind = ch;
		value = 0;
	}
	Token(char ch, double val)
	{
		kind = ch;
		value = val;
	}
};
class Variable {
public:
	string name;
	double value;
	Variable(string str, double val)
	{
		name = str;
		value = val;
	}
};
class Syms_var {
public:
	string name;
	double value;
	Syms_var(string str)
	{
		name = str;
		value = 1;
	}
};
vector<Variable> con = { Variable{ "Dan's_penis_cm", 0.001 }, Variable{ "penis", 20 },Variable{ "pi", 3.1415926}, Variable{ "t1",1} };
double replace_var(string str);
string str;
class Token_stream
{
public:

	Token get();
	void putback(Token t);
private:
	char mark = '0';
	Token buffer = 0;
};
Token Token_stream::get()
{
	char ch;
	cin >> ch;
	if ((ch == ';') || (ch == '(') || (ch == ')') || (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '='))
	{
		return(Token{ ch });
	}
	if (((ch >= '0') && (ch <= '9')) || (ch == '.'))
	{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token{ '8', val };
	}
	if ((ch >= 'A') && (ch <= 'z'))
	{
		return(Token{ ch });
	}
}
vector<Token> del(vector<Token>  tok, unsigned int i);
vector<Token> pluss(vector<Token>  tok, unsigned int i_s);
vector<Token> par(vector<Token> tok, unsigned int i_s);
void  prove(vector<Token> tok, unsigned int is);
vector<Token> manager(vector<Token> tok);
vector<Token>  find_str(vector<Token> tok);
vector<Token> del2(vector<Token> tok, int i, int j, double v);
string del3(double v);
string sym_or_no(string str);
bool find_op(char g);
double convert(string str);
vector<string> str_split(string str, char d);
void set_con();
void debug2(vector<Token> tok)
{
	int n = tok.size();
	cout << "\nVECTOR:\n";
	int i = 0;
	while (i < n)
	{
		if (tok.at(i).kind != '8')
		{
			cout << tok.at(i).kind << ' ';
		}
		else
		{
			cout << tok.at(i).value << ' ';
		}
		i++;
	}
	cout << '\n';
}
void debug(vector<Token> tok)
{
	int n = tok.size();
	cout << "\nVECTOR:\n";
	int i = 0;
	while (i < n)
	{
		cout << tok.at(i).kind << ' ';
		i++;
	}
	cout << '\n';
	i = 0;
	while (i < n)
	{
		cout << tok.at(i).value << ' ';
		i++;
	}
	cout << '\n';
	i = 0;
	while (i < n)
	{
		cout << i << ' ';
		i++;
	}
	cout << '\n';
	cout << '\n';
}

inline void keep_window_open(string s)
{
	if (s == "") return;
	cin.clear();
	cin.ignore(120, '\n');
	for (;;) {
		cout << "Please enter " << s << " to exit\n";
		string ss;
		while (cin >> ss && ss != s)
			cout << "Please enter " << s << " to exit\n";
		return;
	}
}
inline void error(const string& s)
{
	throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
	error(s + s2);
}

inline void error(const string& s, int i)
{
	ostringstream os;
	os << s << ": " << i;
}
vector<Token> manager(vector<Token> tok)
{
	unsigned int i = 0;
	tok = find_str(tok);
	i = 0;
	if (((tok.at(i).kind == '-') || (tok.at(i).kind == '+')))
	{
		Token tt = Token{ '8', 0 };
		tok.insert(tok.begin() + i, tt);
	}
	while (i < tok.size())
	{
		if (((tok.at(i).kind == '-') || (tok.at(i).kind == '+')) && tok.at(i - 1).kind != '8')
		{
			Token tt = Token{ '8', 0 };
			tok.insert(tok.begin() + i, tt);
		}
		if (tok.at(i).kind == '(')
		{
			tok = par(tok, i);
		}
		i++;
	}
	return pluss(tok, 0);
}

double conv(double A, double B, char p)
{
	if (p == '+')
	{
		return(A + B);
	}
	if (p == '-')
	{
		return(A - B);
	}
	if (p == '*')
	{
		return(A * B);
	}
	if (p == '/')
	{
		return(A / B);
	}
	error("FATAL INDEXING ERROR");
	return 0;
}

vector<Token> par(vector<Token> tok, unsigned int i_s)
{
	unsigned int i = i_s;

	while (i < tok.size())
	{
		if (tok.at(i).kind == '(' && i != i_s)
		{
			tok = par(tok, i);
			i = i_s;
			continue;
		}
		if (tok.at(i).kind == ')')
		{
			return(pluss(tok, i_s));
		}
		i++;
	}
	error("HEHE");
	return pluss(tok, i_s);
}

vector<Token> pluss(vector<Token> tok, unsigned int i_s)
{
	unsigned int i = i_s;

	while (i < tok.size() - 1 && tok.at(i + 1).kind != ')')
	{

		if (tok.at(i).kind == '*' || tok.at(i).kind == '/')
		{
			tok = del(tok, i);

			i = i_s;
		}
		i++;
	}

	i = i_s;

	while (i < tok.size() - 1 && tok.at(i + 1).kind != ')')
	{

		if (tok.at(i).kind == '+' || tok.at(i).kind == '-')
		{
			tok = del(tok, i);

			i = i_s;
		}
		i++;
	}
	if (tok.at(i_s).kind == '(')
	{
		tok.erase(tok.begin() + i_s + 2);
		tok.erase(tok.begin() + i_s);
	}
	return tok;
}
vector<Token> del(vector<Token> tok, unsigned int i)
{
	tok.at(i).value = conv(tok.at(i - 1).value, tok.at(i + 1).value, tok.at(i).kind);
	tok.at(i).kind = '8';
	tok.erase(tok.begin() + i + 1);
	tok.erase(tok.begin() + i - 1);
	return tok;
}

double replace_var(string str)
{
	unsigned int i = 0;
	unsigned int n = size(con);
	while (i < n)
	{
		if (con[i].name == str)
		{
			return(con[i].value);
		}
		else
		{
			abort;
		}
		i++;
	}
	return(0);
}
vector<Token>  find_str(vector<Token> tok)
{
	unsigned int i = 0;
	int j = 0;
	unsigned int n = tok.size();
	string str = "";
	while (i < n)
	{
		j = i;
		while (find_op(tok.at(i).kind) == true)
		{
			if (tok.at(i).kind != '8')
			{
				str += tok.at(i).kind;
			}
			else
			{
				str += del3(tok.at(i).value);
			}
			i++;
			if (i == n)
			{
				break;
			}
		}
		str = sym_or_no(str);
		int n1 = str.size();
		if (str.empty() != 1)
		{
			double per = replace_var(str);
			tok = del2(tok, j, i, per);
		}
		str.clear();
		i++;
		i -= n1;
		n = tok.size();

	}
	return(tok);
}
vector<Token> del2(vector<Token> tok, int i, int j, double v)
{
	tok.at(i).value = v;
	tok.at(i).kind = '8';
	tok.erase(tok.begin() + i + 1, tok.begin() + j);
	return tok;
}

string del3(double v)
{
	string str;
	str = to_string(v);
	int i = str.size() - 1;
	if (str.at(str.size() - 1) != '0')
	{
		return str;
	}
	while (i >= 0)
	{
		if (str.at(i) == '.')
		{
			break;
		}
		if (str.at(i) == '0')
		{
			str.resize(str.size() - 1);
		}
		i--;
	}
	if (str.at(str.size() - 1) == '.')
	{
		str.resize(str.size() - 1);
	}
	return str;
}

string sym_or_no(string str)
{
	int n = str.size();
	bool f = true;
	int i = 0;
	while (i < n)
	{
		if ((str.at(i) < '0' || (str.at(i) > '9')) && (find_op(str.at(i)) != false))
		{
			f = false;
		}
		i++;
	}
	if (f == true)
	{
		str.clear();
	}
	return(str);
}
bool find_op(char g)
{
	bool flag = true;
	if ((g == '+') || (g == '-') || (g == '*') || (g == '/') || (g == '(') || (g == ')') || (g == '.'))
	{
		flag = false;
	}
	return(flag);
}
void set_con()
{
	double chh;
	string st;
	vector<string> lisst2;
	cin >> st;
	if(st=="->")
	{
		return;
	}
	vector<string> lisst = str_split(st, ',');
	int n = lisst.size();
	int i = 0;
	while (i < n)
	{
		lisst2 = str_split(lisst.at(i), '=');
		con.push_back(Variable{ lisst2.at(0), convert(lisst2.at(1)) });
		i++;
	}
}
vector<string> str_split(string str, char d)
{
	vector<string> lisst;
	string sst;
	int n = str.size();
	int i = 0;
	int j = 0;
	while (i < n)
	{
		if (str.at(i) == d || i == n - 1)
		{
			if (i == n - 1)
			{
				sst.push_back(str.at(i));
			}
			lisst.push_back(sst);
			j = 0;
			i++;
			sst.clear();
			continue;
		}

		sst.push_back(str.at(i));
		i++;
		j++;
	}
	return(lisst);
}
double convert(string str)
{
	const int n = str.size();
	int i = 0;
	char* ch = new char[n];
	while (i < n)
	{
		ch[i] = str.at(i);
		i++;
	}
	double d = atof(ch);
	delete(ch);
	return d;
}