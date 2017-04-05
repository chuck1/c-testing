
class Node
{
public:
	Node(int d)
	{
		next = NULL;
		data = d;
	}

	Node*	next;
	int	data;
};

class List
{
public:
	List()
	{
		head = NULL;
	}
	void	append(int d)
	{
		Node* n = new Node(d);
		Node* l = last();
		if(l == NULL) {
			head = n;
		} else {
			l->next = n;
		}
	}
	Node*	last()
	{
		if(head == NULL) return NULL;

		Node* n = head;
		while(n->next != NULL) {
			n = n->next;
		}
		return n;
	}
	Node*	fromFirst(int i)
	{
		Node* n = head;
		while(--i >= 0) {
			if(n == NULL) return NULL;
			n = n->next;
		}
		return n;
	}
	Node*	fromLast(int i)
	{
		Node* n0 = head;
		Node* n1 = fromFirst(i);
		
		if(n1 == NULL) return NULL;

		while(n1->next != NULL) {
			n0 = n0->next;
			n1 = n1->next;
		}
		return n0;
	}

	Node*	head;
};


