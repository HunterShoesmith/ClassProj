#include "BinaryTree.hpp"
#include "Deque.hpp"

#include <iostream>
	using std::string;
	using std::cout;
	using std::endl;

/**
 * Something to keep track of the nodes; drawing them requires
 * that each node be uniquely identified.
 * Since elements may not always be unique, this helps id them.
 */
int BinaryTree::node_count = 0;

BinaryTree::BinaryTree(string element, BinaryTree left_tree, BinaryTree right_tree) {
	TreeNode * left_subtree = build_subtree(left_tree.root);
	TreeNode * right_subtree = build_subtree(right_tree.root);
	root = new TreeNode(element, left_subtree, right_subtree);
	m_size = 1 + left_tree.m_size + right_tree.m_size;
}

BinaryTree::BinaryTree(string element) {
	root = new TreeNode(element);
	m_size = 1;
}

BinaryTree::BinaryTree() {
	root = nullptr;
	m_size = 0;
}

/**
 * Private recursive helper function that builds a copy of a subtree rooted at node.
 * Even if the parent links are not in the original, they are linked in the copied 
 * version; it won't make a difference to the invariants.
 * @param node The root of the subtree to copy.
 */
BinaryTree::TreeNode * BinaryTree::build_subtree(const TreeNode * node) {
  

	  if (node == nullptr) {
			return nullptr;
		}

		TreeNode *t = new TreeNode(node->element, build_subtree(node->lchild),build_subtree(node->rchild));

		if (t->lchild) {
			t->lchild->parent = t;
		}

		if (t->rchild) {
			t->rchild->parent = t;
		}

		return t;
}
			 
BinaryTree::BinaryTree( const BinaryTree & copy) {
	m_size = copy.m_size;
	root = build_subtree(copy.root);
}


BinaryTree::~BinaryTree() {
	delete_subtree(root);
}

/**
 * Private recursive helper function that deletes the nodes in a subtree rootd at node.
 * @param The root of a subtree.
 */
BinaryTree::TreeNode * BinaryTree::delete_subtree( TreeNode * node ) {
	if (node == nullptr) {
		return nullptr;
	}
	if (node->lchild != nullptr) {
		node->lchild = delete_subtree(node->lchild);
	}
	if (node->rchild != nullptr) {
		node->rchild = delete_subtree(node->rchild);
	}
	delete node;
	return nullptr;
}


int BinaryTree::size() const {
	return m_size;
}

bool BinaryTree::is_empty() const {
	return m_size == 0;
}

int BinaryTree::height() const {
	return get_height(root);
}

/**
 * Private recursive function that determines the height of a subtree
 * rooted at subroot.
 * @param subroot the root of the subtree.
 */
int BinaryTree::get_height(TreeNode * subroot) const {
	if (subroot == nullptr) {
		return 0;
	}
	return (1 + std::max(get_height(subroot->lchild),
					get_height(subroot->rchild)));
}

void BinaryTree::pre_order(Deque<string>& Q) const {
	gen_preorder(Q,root);
}

/**
 * Private recursive function that processes the nodes in preorder.
 * Processing means inserting the element into a queue.
 * @param Q the queue to store the elements.
 * @param node the root of the current subtree.
 */
void BinaryTree::gen_preorder(Deque<string> & Q, TreeNode * node) const {
	if (node != nullptr) {
		Q.enqueue(node->element);
		gen_preorder(Q,node->lchild);
		gen_preorder(Q,node->rchild);
	}
}

void BinaryTree::in_order(Deque<string> & Q) const {
	gen_inorder(Q, root);
}

/**
 * Private recursive function that processes the nodes in order.
 * Processing means inserting the element into a queue.
 * @param Q the queue to store the elements.
 * @param node the root of the current subtree.
 */
void BinaryTree::gen_inorder(Deque<string> & Q, TreeNode * node) const {
	if (node != nullptr) {
		gen_inorder(Q,node->lchild);
		Q.enqueue(node->element);
		gen_inorder(Q,node->rchild);
	}
}

void BinaryTree::post_order(Deque<string> & Q) const {
	gen_postorder(Q, root);
}

/**
 * Private recursive function that processes the nodes in postorder.
 * Processing means inserting the element into a queue.
 * @param Q the queue to store the elements.
 * @param node the root of the current subtree.
 */
void BinaryTree::gen_postorder(Deque<string>& Q, TreeNode * node) const {
	if (node != nullptr) {
		gen_postorder(Q,node->lchild);
		gen_postorder(Q,node->rchild);
		Q.enqueue(node->element);
	}
}

/**
 * Prints out the necessary information about the tree in DOT language.
 * The output can then be translated by a graph drawing program to produce
 * a picture of the tree structure.
 */
void BinaryTree::DOT_translation() const {
	cout << "DOT translation begins:"<<endl;
	cout<<"digraph BST {"<<endl;
	cout<<"\tnode [fontname=\"Arial\"];"<<endl;

	if (root) {
		doDotPrint(root);
	} 
	cout<<"}"<<endl;
	cout << "DOT translation ends:"<<endl;
}

/**
 * Private recursive function that process the DOT language 
 * for each subtree in the tree.
 * @param node the root of the current subtree.
 */
void BinaryTree::doDotPrint(BinaryTree::TreeNode * node) const {

	if (node->lchild) {
		cout<<"\t"<<node->id
			<<" -> "<<node->lchild->id
			<<";"<<endl;
		doDotPrint(node->lchild);
	}
	if (node->rchild) {
		cout <<"\t"<<node->id
			<<" -> "<<node->rchild->id
			<<";"<<endl;
		doDotPrint(node->rchild);
	}
}
