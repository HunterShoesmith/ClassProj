#include "ExpressionTree.hpp"
#include "ExpressionTools.hpp"

#include <iostream>
	using std::string;


ExpressionTree::ExpressionTree() {
	root = nullptr;
	m_size = 0;
}

// Copy constructor is punted to the BinaryTree copy constructor.
ExpressionTree::ExpressionTree(const ExpressionTree &copy):BinaryTree(copy) {}

// Destructor punted to the BinaryTree destructor.
ExpressionTree::~ExpressionTree() {}


ExpressionTree::ExpressionTree(const vector<string> & infix_tokens) {
	// calls the recursive helper function
  try{
	  root = build_subtree(infix_tokens,0,infix_tokens.size());
  }catch(ExpressionException &expExc){
    std::cout << expExc.to_string();
  }

}

/**************  STUDENT TO COMPLETE THE FOLLOWING: 
// NOTE: Follow the tips for the base cases and recursion

 * For the student.
 * Private recursive function that builds a subtree from the 
 * sub-expression bordered by the tokens from start to end-1.
 * @param tokens vector of full expression infix tokens.
 * @param start index position of first token in sub-expression
 * @param end index position that is one past the last token.
 * @return tree node that is the root of the current subtree related to the sub-expression.
 * @throw ExpressionException if there is an imbalance between operators and operands.
 */
BinaryTree::TreeNode * ExpressionTree::build_subtree(const vector<string> &tokens, int start, int end) {
	// case 1: start >= end:
	// means that there are too many operators.  We expect to find a number at least
  if (start >= end){
    //std::cout << "too many operators" << std::endl;
    throw ExpressionException("build_subtree","too many operators or improper ordering of operators.");
  }


	// case 2: remove outside parens and continue
	// if the subexpression has a '(' in start and a ')' in end-1, AND they are a matching
	// set, then make the sub-expression smaller so they are not included.
	// No need to return, just keep going after change the values of start and end
  while (is_bordered_by_parens(tokens, start,end)){
    start++;
    end--;
  }



	// case 3: the subexpression is a single number
	// 	create a new treenode with the number and return that
  if (end-1==start){
      m_size++;
      return new BinaryTree::TreeNode(tokens[start]);
  }

	// case 4: find the rightmost lowest priority operator to be a root node of a subtree.
	// insert the opertor into a new node, and attach (recursively) the left part of the subexpression and the right part of the subexpressions as its children.
	//return the new node
  int lowPrio = find_infix_lowest_op_index(tokens,start,end);

  
  TreeNode * lchild = build_subtree(tokens,start,lowPrio);
  TreeNode * rchild = build_subtree(tokens,lowPrio+1,end);

  m_size++;
  root = new TreeNode(tokens[lowPrio],lchild,rchild);

  root->rchild->parent = root;
  root->lchild->parent = root;



  return root;
  
}


void ExpressionTree::get_postfix_expression(vector<string> &postfix_tokens) {

  gen_postfix(root,postfix_tokens);

	// STUDENT TO COMPLETE
}

/**
 * Private recursive helper function that processes the elements in a subtree
 * 	in postfix order.
 * @param node the root node of the current subtree.
 * @parm postfix the vector that is storing the elements of the subtree.
 */
void ExpressionTree::gen_postfix(TreeNode *node, vector<string> &postfix) {
  if (node == nullptr) return;

  string ele = node->element;

  gen_postfix(node->lchild,postfix);

  gen_postfix(node->rchild,postfix);

  postfix.push_back(ele);
  //Q.enqueue(ele);
	// STUDENT TO COMPLETE
}


