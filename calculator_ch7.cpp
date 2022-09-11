#include "calculator_lib.h"
using namespace std;
int main()
{
	cout << "Enter necessary constant,or type ->, and after push enter" << '\n';
	set_con();
	int i = 0;
	while (1)
	{
		try
		{
			if (i == 0)
			{
				cout << "input an equation,and ended '=',you can use numbers from 0 to 9, and bracket, operators +-*/ : ";
			}
		vector<Token> tok;
		Token_stream ts;
		 
		while (1)
		{
			Token t = ts.get();
			if (t.kind == '=')
			{
				break;
			}
			else
			{
				tok.push_back(t);
			}
		}
		tok=manager(tok);
		cout << "The answer: " << tok.at(0).value << '\n';
		}
		catch (exception& e)
		{
			keep_window_open("~");
			cerr << e.what() << '/n';
			return 1;
		}
		i++;
	}
	return 0;
}

