#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include "BinaryTree.hpp"

#include <vector>
#include <iostream>
	using std::string;
	using std::vector;

class ExpressionTree : public BinaryTree {
	public:
		/*******************  Constructors / Destructors ***************/
		ExpressionTree();
		ExpressionTree( const vector<string> &infix_tokens );
		ExpressionTree( const ExpressionTree &copy);
		~ExpressionTree();

		/*******************  getters / setters  ***************/
		void get_postfix_expression(vector<string> &postfix_tokens);

		/*******************  helpers   ***************/
	private:
		void gen_postfix(TreeNode *node, vector<string> &postfix);
		TreeNode * build_subtree(const vector<string> &postfix, int start, int end);

};
#endif
