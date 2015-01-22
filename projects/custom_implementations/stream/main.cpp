

struct stream {

	template<typename T> stream&		operator<<(T& t) {
	}
	template<typename T> void		operator<<(T& t) {
	}
};

template<typename T> stream&		operator<<(stream& s, T const & t) {
}
template<typename T> void		operator<<(stream& s, T const & t) {
}

int main() {


	stream s;

	s << 1 << 'c';


}





