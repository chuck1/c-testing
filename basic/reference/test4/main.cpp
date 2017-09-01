
void f(int & a)
{
}
void g(int & a)
{
	//f(a);
}

int main()
{
	int b = 1;
	int & a = b;

	g(a);
	return 0;
}



