
#define DEBUG if(0)

struct binary_iarchive {
	binary_iarchive(ifstream& is): m_is(is) {}
	void	operator&(string& s) {
		s.clear();

		char c;
		m_is.read(&c, 1);
		while(c) {
			s.push_back(c);
			m_is.read(&c, 1);
		}
	}
	void	operator&(long int& i) {
		m_is.read((char*)&i, sizeof(long int));
	}
	void	operator&(size_t& i) {
		m_is.read((char*)&i, sizeof(size_t));
	}
	template<typename T> void	operator&(vector<T>& v) {
		v.clear();
		size_t s;
		operator&(s);
		DEBUG cout << "vector size = " << s << endl;
		for(size_t i = 0; i < s; ++i) {
			T t;
			operator&(t);
			v.push_back(t);
		}
	}
	template<typename T> void	operator&(T& t) {
		t.serialize(*this);
	}
	ifstream&	m_is;
};
struct binary_oarchive {
	binary_oarchive(ofstream& os): m_os(os) {}
	void	operator&(string& s) {
		DEBUG cout << "string \"" << s << "\" " << s.size() << endl;
		m_os.write(s.c_str(), s.size()+1);
	}
	void	operator&(long int& i) {
		m_os.write((char*)&i, sizeof(long int));
	}
	void	operator&(size_t i) {
		m_os.write((char*)&i, sizeof(size_t));

	}
	template<typename T> void	operator&(vector<T> v) {
		operator&(v.size());
		DEBUG cout << "vector size = " << v.size() << endl;

		for(auto it = v.begin(); it != v.end(); it++) {
			operator&(*it);
		}
	}
	template<typename T> void	operator&(T& t) {
		t.serialize(*this);
	}

	ofstream&	m_os;
};

struct stat_file {
	stat_file() {}
	stat_file(string file, struct dirent *dirp) {

		struct stat st;

		if(stat(file.c_str(), &st) == -1) {
			cout << strerror(errno) << endl;
			exit(1);
		}

		name = dirp->d_name;
		size = st.st_size;

	}

	string		name;
	off_t		size;

	template<typename archive> void		serialize(archive& ar) {
		ar & name;
		ar & size;
	}

};
struct stat_dir {
	stat_dir() {}
	stat_dir(string dir, struct dirent *direntp) {

		struct dirent *dirp;
		DIR* dp;

		if((dp = opendir(dir.c_str())) == NULL) {
			cout << "Error(" << errno << ") opening " << dir << endl;
			exit(1);
		}

		name = dir;

		while ((dirp = readdir(dp)) != NULL) {

			if((strcmp(dirp->d_name, ".") == 0) || (strcmp(dirp->d_name, "..") == 0)) continue;

			string file = dir + "/" + dirp->d_name;

			if(dirp->d_type == 4) {
				dirs.push_back(stat_dir(file, dirp));
			} else if(dirp->d_type == 8) {
				files.push_back(stat_file(file, dirp));
			}
		}

		closedir(dp);


	}
	template<typename archive> void		serialize(archive& ar) {
		ar & name;
		ar & dirs;
		ar & files;
	}
	off_t			size() {
		off_t s = 0;
		for(auto d : dirs) {
			s += d.size();
		}
		for(auto f : files) {
			s += f.size;
		}
		return s;
	}

	string			name;

	vector<stat_dir>	dirs;
	vector<stat_file>	files;
};

struct info {
	struct dirent*		dirp;
	struct stat*		statp;
};



