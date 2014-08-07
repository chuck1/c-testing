
#define DEBUG if(0)

#include <errno.h>
#include <string.h>
#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#include <boost/python.hpp>

using namespace std;

template<class T> PyObject* std_vector_to_py_list(const std::vector<T>& v) {

	/*
	boost::python::object get_iter = boost::python::iterator<std::vector<T> >();
	boost::python::object iter = get_iter(v);
	boost::python::list* l = new boost::python::list(iter);
	return l->ptr();
*/
	boost::python::list* l = new boost::python::list();
	for(size_t i = 0; i < v.size(); i++)
		(*l).append(v[i]);

	return l->ptr();
}

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
		m_size = st.st_size;

	}
	off_t		size() {
		return m_size;
	}

	string		name;
	off_t		m_size;



	template<typename archive> void		serialize(archive& ar) {
		ar & name;
		ar & m_size;
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
			s += f.m_size;
		}
		return s;
	}
	void			read() {
		ifstream is(".stat", ifstream::binary);
		if(!is.is_open()) {
			exit(1);
		}
		binary_iarchive ar(is);

		serialize(ar);
	}
	PyObject*		get_dirs() {
		return std_vector_to_py_list(dirs);
	}
	PyObject*		get_files() {
		return std_vector_to_py_list(files);
	}

	string			name;

	vector<stat_dir>	dirs;
	vector<stat_file>	files;
};

struct info {
	struct dirent*		dirp;
	struct stat*		statp;
};



