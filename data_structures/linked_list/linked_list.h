template <typename T> struct ll_node
{
	public:
		ll_node()
		{
			next_ = NULL;
		}
		ll_node *insert( int i );
		ll_node *find( T t );
		ll_node *at( int i );
		ll_node *insert( int i, int n, T t );
		T t_;
		ll_node *next_;
};

template <typename T> class ll
{
private:
	ll_node<T> head_;
public:
	ll_node<T> *insert( int i, T t );
	ll_node<T> *begin();
};


template <typename T> ll_node<T> *ll<T>::insert( int i, T t )
{
	if( i < 0 ) return NULL;
	
	return head_.insert( i, -1, t );
}
template <typename T> ll_node<T> *ll<T>::begin()
{
	return head_.next_;
}

template <typename T> ll_node<T> *ll_node<T>::insert( int i, int n, T t )
{
	if( i == (n+1) )
	{
		ll_node<T>* node = new ll_node<T>;
		node->t_ = t;
		node->next_ = next_;
		next_ = node;
	}
	else if( next_ != NULL )
	{
		next_->insert( i, n+1, t );
	}
	else
	{
		return NULL;
	}
}

template <typename T> ll_node<T> *ll_node<T>::find( T t )
{
	return NULL;
}
template <typename T> ll_node<T> *ll_node<T>::at( int i )
{
	return NULL;
}

