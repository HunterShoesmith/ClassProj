#include "Deque.hpp"
#include "ExpressionTools.hpp"

#include <iostream>
#include <regex>
#include <vector>
#include <cmath>
	using std::cout;
	using std::string;
	using std::endl;
	using std::vector;
	using std::regex;
	using std::sregex_iterator;
	using std::smatch;

// completed working function:
string ltrim(const string & s) {
	return std::regex_replace(s,regex("^\\s+"),string(""));
}

// completed working function:
string rtrim(const string & s) {
	return std::regex_replace(s,regex("\\s+$"),string(""));
}

string trim(const string & s) {
	// INCOMPLETE IMPLEMENTATION
  rtrim(s);
  ltrim(s);
  return s;
	// use the previous two functions to help this one
}

bool is_operator(const string &token) {
	// INCOMPLETE IMPLEMENTATION
	// recommend a switch statement for this

  switch(token[0]){
		case '^':
		case '*':
		case '/':
		case '%':
		case '+':
		case '-':
    return true;
		default:
			return false;
  }
}


	
// completed working function
int get_op_precedence(char op) {
	switch(op) {
		case '^':
			return 3;
		case '*':
		case '/':
		case '%':
			return 2;
		case '+':
		case '-':
			return 1;
		default:
			return 0;
	}
}

int find_infix_lowest_op_index(const vector<string> & tokens, int start, int end) {

  //check for op_precedence 1
  
    bool inBracket=false;



  for (int x=end-1;x>=start;x--){
    //ignore if in brackets
    if (')'==tokens[x][0]) inBracket=true;
    if ('('==tokens[x][0]) inBracket=false;

    if (1==get_op_precedence(tokens[x][0])&&!(inBracket)){
      if ('('==tokens[x][0]) inBracket=true;
      if (')'==tokens[x][0]) inBracket=false;
      return x;
    }
  }

  //check for op_precedence 2
  for (int x=end-1;x>=start;x--){
    //ignore if in brackets
    if (')'==tokens[x][0]) inBracket=true;
    if ('('==tokens[x][0]) inBracket=false;

    if (2==get_op_precedence(tokens[x][0])&&!(inBracket)){
      return x;
    }
  }
  
  //check for op_precedence 3
  for (int x=end-1;x>=start;x--){
    //ignore if in brackets
    if (')'==tokens[x][0]) inBracket=true;
    if ('('==tokens[x][0]) inBracket=false;

    if (3==get_op_precedence(tokens[x][0])&&!(inBracket)){
      return x;
    }
  }

  return -1;

	// return the index of the rightmost lowest precedence operator
	// use the get_op_precedence function to get the precedence.
	// note that anything inside parentheses is not going to be
	// the lowest precedence.

	// INCOMPLETE IMPLEMENTATION

}

// completed working function
bool is_bordered_by_parens(const vector<string> & tokens, int start, int end) {
	if (tokens[start] != "(" || tokens[end-1] != ")") {
		return false;
	}
	int paren_balance = 1;
	for (int i=start+1; i<end-1; i++) {
		if (tokens[i] == "(") {
			paren_balance++;
		} else if (tokens[i] == ")") {
			paren_balance--;
		}
		if (paren_balance == 0) {
			return false;
		}
	}
	return true;
}

// completed and working function:
void tokenize(const string& expression, vector<string>& tokens) {
	// looking for operators or parentheses.
	regex ops("[-+*/^%()]");
	sregex_iterator it(expression.begin(), expression.end(), ops);
	sregex_iterator it_end;

	int match_startindex = 0;
	int nonmatch_startindex = 0;
	string lastmatch = "";
	string match= "";
	string nonmatch = "";

	for(;it != it_end;++it) {
		// get the next match of an operator or paren:
		// and its particulars
		smatch sm = *it;
		match = sm.str();
		match_startindex = sm.position(0);
		nonmatch = expression.substr(nonmatch_startindex,match_startindex-nonmatch_startindex);
		nonmatch = trim(nonmatch);
		// The very first '-' or the one that follows another operator or a '(' is a negative sign
		if (match[0] == '-') {
			if (match_startindex == 0 || nonmatch == "" && lastmatch != ")") {
				continue;  // ignore this match: its part of a number.
			}
		}
		// nonmatch can be empty when an operator follows a ')'
		if (nonmatch.length() != 0) {
			tokens.push_back(nonmatch);
		}
		nonmatch_startindex = match_startindex+match.length();
		tokens.push_back(match);
		lastmatch = match;
	}
	// parse the final substring after the last operator or paren.
	if (nonmatch_startindex < expression.length()) {
		nonmatch = expression.substr(nonmatch_startindex,expression.length());
		nonmatch = trim(nonmatch);
		tokens.push_back(nonmatch);
	}
}

double evaluate(const vector<string> &postfix) {

  int y=0;


  Deque<string> stack;
  
  for (int x=0;x< postfix.size();x++){


    if (!(get_op_precedence(postfix[x][0])))
    {
      try{
        double num1 = std::stod(postfix[x]);
      }catch(std::invalid_argument &ia) 
      {
        throw ExpressionException("evaluate","operand is not a number");
      }
      stack.push(postfix[x]);
    }
    else{

      double op2 = std::stod(stack.pop());

      double op1 = std::stod(stack.pop());

      double result=0;

      if (postfix[x][0]=='+'){
        result = op2 + op1;
      }

      if (postfix[x][0]=='-'){
        result = op1 - op2;
      }

      if (postfix[x][0]=='*'){
        result = op2 * op1;
      }

      if (postfix[x][0]=='/'){
        if (op2==0) throw ExpressionException("evaluate","Divide by zero");
        result = op1 / op2;
      }

      if (postfix[x][0]=='%'){
        if (!(int(op1)==op1 && int(op2)==op2)) std::cout << "treating modulo as fmod for: " << op1 << '%' << op2 << std::endl;
        result = fmod(op1,op2);
      }

      if (postfix[x][0]=='^'){
        result = pow(op1,op2);
      }

      stack.push(std::to_string(result));
    }
  }

  
  double result;
  if (stack.is_empty()){
    throw ExpressionException("evaluate","Nothing to evaluate");
  }
  else {
    try {
      result = std::stod(stack.pop());
    }catch (DequeException &de) {

      throw ExpressionException("evaluate","too few operands");
    }

    
    

  }


  
  if (!(stack.is_empty())) throw ExpressionException("evaluate","too many operands");

  return result;
	// STUDENT TO COMPLETE 
	// MAKE THIS THE LAST FUNCTION TO IMPLEMENT
}

