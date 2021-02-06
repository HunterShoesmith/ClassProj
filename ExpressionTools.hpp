#ifndef EXPRESSTOOLS_H
#define EXPRESSTOOLS_H

#include <iostream>
#include <vector>
	using std::cout;
	using std::string;
	using std::endl;
	using std::vector;

class ExpressionException {
	private :
		string m_location;
		string m_message;
	public :
		ExpressionException(const string & where_thrown, const string & msg) {
			m_location = where_thrown;
			m_message = msg;
		}
		string to_string() const {
			return "*** ExpressionException in "+
				m_location + ": "+m_message;
		}
};


string ltrim(const string & s); 
string rtrim(const string & s); 
string trim(const string & s);
bool is_operator(const string & s);
int get_op_precedence(char op); 
int find_infix_lowest_op_index(const vector<string> & tokens, int start, int end); 
bool is_bordered_by_parens(const vector<string> & tokens, int start, int end);
void tokenize(const string &expression, vector<string> &tokens);
double evaluate(const vector<string> &postfix);

#endif
