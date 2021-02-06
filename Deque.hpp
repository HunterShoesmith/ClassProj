#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
	using std::string;
	using std::cout;
	using std::ostream;

class DequeException {
	private :
		string m_location;
		string m_message;
	public :
		DequeException(const string & where_thrown, const string & msg) {
			m_location = where_thrown;
			m_message = msg;
		}
		string to_string() const {
			return "*** DequeException in "+
				m_location + ": "+m_message;
		}
};

template<class E>
class Deque {
	private :
		// private inner class
		class Node {
			public:
				E element;
				Node * next;
				Node * prev;
			
				Node(const E &value, Node * nxt=nullptr, Node * prv=nullptr) {
					element = value;
					next = nxt;
					prev = prv;
				}
		};

		Node * first;
		Node * last;
		int m_size;

		void insert_first(E element) { 
			first = new Node(element,first);
			if (is_empty()) {
				last = first;
			} else {
				first->next->prev = first;
			}
			m_size++;
		}

	public:
	/*******************  Constructors / Destructors ***************/
		Deque() {
			first = last = nullptr;
			m_size = 0;
		}

		~Deque() {
			while (first) {
				dequeue();
			}
		}

		Deque( const Deque<E> &copy) {
			// This deep copy is necessary as Deque is returned as a parameter.
			m_size = 0;
			Node * tmp = copy.first;
			while (tmp) {
				push(tmp->element);
				tmp = tmp->next;
			}
		}

		/******************  Queue and Stack behaviour  *****************/

		E top() const {
			if (is_empty()) {
				throw DequeException("get_last", "Stack is empty");
			}
			return last->element;
		}

		E front() const {
			if (is_empty()) {
				throw DequeException("front", "Queue is empty");
			}
			return first->element;
		}
	
		bool is_empty() const {
			return m_size == 0;
		}

		/******************  Inserting **********************/
		void enqueue(E element) {
			last = new Node(element,nullptr,last);
			if (is_empty()) {
				first = last;
			} else {
				last->prev->next = last;
			}
			m_size++;
		}

		void push(E element) {
			enqueue(element);
		};

		/*****************  Removing ***********************/
		E dequeue() {
			if (is_empty()) {
				throw DequeException("dequeue","Queue is empty");
			}
			Node * tmp = first;
			E to_return = tmp->element;
			first = first->next;
			if (first) {
				first->prev = nullptr;
			} else {
				last = nullptr;  // we just removed the last one.
			}
			delete tmp;
			m_size--;
			return to_return;
		}
	
		E pop() {
			if (is_empty()) {
				throw DequeException("pop","Stack is empty");
			}
			if (m_size==1) {
				return dequeue();
			}
			Node * tmp = last;
			E to_return = tmp->element;
			last = last->prev;
			last->next = nullptr;
			delete tmp;
			m_size--;

			return to_return;
		}
	
		/**************** For debugging ***********************/
		// The following are not part of the Stack or Queue ADT,
		// but are helpful for debugging during programming.

		void print_queue() const {
			if (is_empty()) {
				cout << "Queue is empty.\n";
			} else {
				for (Node * tmp = first; tmp; tmp=tmp->next) {
					cout << tmp->element << " ";
				}
			}
		}

		void print_stack() const {
			if (is_empty()) {
				cout << "Stack is empty.\n";
			} else {
				for (Node * tmp = last; tmp; tmp=tmp->prev) {
					cout << tmp->element << " ";
				}
			}
		}

};
#endif
