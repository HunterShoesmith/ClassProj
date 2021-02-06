#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "Deque.hpp"

#include <iostream>
	using std::string;

class BinaryTree {

	protected :

		// Because the BinaryTree will likely be subclassed,
		// everything that is inherited is protected as opposed
		// to private.

		class TreeNode {
			public:
				string id; 
				string element;
				TreeNode * lchild;
				TreeNode * rchild;
				TreeNode * parent;

				TreeNode(const string &value, TreeNode* left=nullptr, TreeNode * right=nullptr,
						TreeNode * par=nullptr) {
					element = value;
					lchild =left;
					rchild = right;
					parent = par;
					id = "\""+std::to_string(++node_count)+"_("+element+")\"";
				}
		};


		TreeNode * root;
		int m_size;

	private :
		static int node_count;
		void gen_preorder(Deque<string> & Q, TreeNode * node) const;
		void gen_inorder(Deque<string> & Q, TreeNode * node) const;
		void gen_postorder(Deque<string>& Q, TreeNode * node) const;
		void doDotPrint(BinaryTree::TreeNode * node);
		
		TreeNode * build_subtree(const TreeNode * node);
		TreeNode * delete_subtree(TreeNode * node);
		int get_height(TreeNode * subroot) const;
		void doDotPrint(TreeNode * node) const;

	public:
		BinaryTree(string element, BinaryTree left_tree, BinaryTree right_tree); 
		BinaryTree(string element);
		BinaryTree();
		BinaryTree( const BinaryTree &copy);
		~BinaryTree();

		/******************  gets and sets  *****************/
		int size() const;
		bool is_empty() const;
		int height() const;
		void pre_order(Deque<string>& Q) const;
		void in_order(Deque<string> & Q) const;
		void post_order(Deque<string> & Q) const;
		void DOT_translation() const;
				
};
#endif
