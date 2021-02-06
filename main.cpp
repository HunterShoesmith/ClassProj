/*
By Hunter
*/
#include <iostream>
#include "BinaryTree.hpp"
#include "Deque.hpp"
#include "ExpressionTools.hpp"
#include "ExpressionTree.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
int main() {
  string expression;
  cout << "enter the math expression: ";

  getline(cin,expression);

  vector<string> tokens;

  tokenize(expression,tokens);

  std::cout << tokens.size() << std::endl;
  
  ExpressionTree workPlz(tokens);

  vector<string> postToken;

  workPlz.get_postfix_expression(postToken);

  double answer;

  try{
    answer = evaluate(postToken);

    std::cout <<"look for miracle: " <<  answer << std::endl;
    std::cout << "WOW! 5/5 can't beleive it got my number!" << std::endl << "-Random guy on YAHOO!" << std::endl; 
  }catch(ExpressionException &ee){
    std::cout << ee.to_string() << std::endl;
  }
  



}