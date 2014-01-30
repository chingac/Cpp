#include <string>
#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Grade {
public:
// ctor(s) & additional functions if necessary
friend std::ostream& operator<<(std::ostream& os, const Grade& g){
	os<<g.course_<<" "<<g.score_<<endl;
	return os;
}
// sample output: comp3512 90
friend std::istream& operator>>(std::istream& is, Grade& g){
	is>>g.course_>>g.score_;
	return is;
}

string getCourse() {
	return course_;
}

int getGrade() {
	return score_;
}
// additional friend declarations if necessary
private:
std::string course_; // e.g. comp3512
int score_; // e.g. 90
};

class Name {
public:
// ctor(s) & additional functions if necessary
friend std::ostream& operator<<(std::ostream& os, const Name& n){
	os<<n.first_<<" "<<n.last_<<endl;
	return os;
}
// sample output: homer simpson
friend std::istream& operator>>(std::istream& is, Name& n){
	is>>n.first_>>n.last_;
	return is;
}

string getFname() const{
	return first_;
}

string getLname() const {
	return last_;
}
// additional friend declarations if necessary
private:
std::string first_; // e.g. homer
std::string last_; // e.g. simpson
};

class Student {
public:
// ctor(s) & additional functions if necessary 
void display(std::ostream& os) const{
	os << id_ <<endl<< name_;
	
	map<string, Grade>::const_iterator it;
	for (it = grade_.begin(); it != grade_.end(); ++it) {
		os << it->second;
	}
	os<<endl;
}
void displayallid(std::ostream& os) const{
	os << id_ <<endl;
}

void displayname(std::ostream& os, string fname, string lname) const{
	if(name_.getFname() == fname && name_.getLname() == lname){
		os << id_ <<endl<< name_;

		map<string, Grade>::const_iterator it;
		for (it = grade_.begin(); it != grade_.end(); ++it) {
			os << it->second;
		}
		os<<endl;
	} else if("*" == fname && "*" == lname){
		os << id_ <<endl<< name_;

		map<string, Grade>::const_iterator it;
		for (it = grade_.begin(); it != grade_.end(); ++it) {
			os << it->second;
		}
		os<<endl;
	} else if(name_.getFname() == fname && "*" == lname){
		os << id_ <<endl<< name_;

		map<string, Grade>::const_iterator it;
		for (it = grade_.begin(); it != grade_.end(); ++it) {
			os << it->second;
		}
		os<<endl;
	} else if("*" == fname && name_.getLname() == lname){
		os << id_ <<endl<< name_;

		map<string, Grade>::const_iterator it;
		for (it = grade_.begin(); it != grade_.end(); ++it) {
			os << it->second;
		}
		os<<endl;
	}
}

void displaynameid(std::ostream& os, string fname, string lname) const{
	if(name_.getFname() == fname && name_.getLname() == lname){
		os << id_;
		os<<endl;
	} else if("*" == fname && "*" == lname){
		os << id_;
		os<<endl;
	} else if(name_.getFname() == fname && "*" == lname){
		os << id_;
		os<<endl;
	} else if("*" == fname && name_.getLname() == lname){
		os << id_;
		os<<endl;
	}
}

friend std::istream& operator>>(std::istream& is, Student& s){
	is>>s.id_>>s.name_;
	size_t integer;
	is>>integer;
	s.grade_.clear();
	for(size_t i=0;i<integer;++i){
		Grade g;
		is>>g;
		s.grademap(g.getCourse(),g);
		if(is.eof()){
			return is;
		}	
	}
	return is;
}

friend bool operator<(const Student &s1, const Student &s2){
	return s1.id_<s2.id_;
}

void grademap(string course, Grade &g){
	grade_.insert(map<string, Grade>::value_type(course, g));
}
string getid() const{
	return id_;
}

map<string, Grade> getgrade(){
	return grade_;
}

// additional friend declarations if necessary
private:
std::string id_; // e.g. a11111111
Name name_;
// an STL container of Grade objects
map<string, Grade> grade_;
//

};

struct student1 {
	string command1;
	student1(string command): command1(command) {}
	
	void operator()(const Student& s) {
			if(s.getid() == command1){
				s.displayallid(cout);
			}	
	}
};

struct studentgrade {
	string command1;
	int commandg;
	studentgrade(string command, int commandgr): command1(command), commandg(commandgr) {}
	void operator()(Student& s) {
		Grade g;
		map<string,Grade> m = s.getgrade();
		if(m.find(command1) != m.end()){
			if(m[command1].getGrade()==commandg){
				s.display(cout);
			}
		}
	}
};

struct studentidgrade {
	string command1;
	int commandg;
	studentidgrade(string command, int commandgr): command1(command), commandg(commandgr) {}
	void operator()(Student& s) {
		Grade g;
		map<string,Grade> m = s.getgrade();
		if(m.find(command1) != m.end()){
			if(m[command1].getGrade()==commandg){
				s.displayallid(cout);
			}
		}
	}

};

struct studentrangegrade {
	string command1;
	int commandg;
	int commandg2; //no need for command1=command etc.
	studentrangegrade(string command, int commandgr, int commandgr2): command1(command), commandg(commandgr),
																   commandg2(commandgr2){}
	void operator()(Student& s) {
		Grade g;
		//cout<<(s.getgrade().find(command1) == s.getgrade().end());
		map<string,Grade> m = s.getgrade();
		if(m.find(command1) != m.end()){
			if(m[command1].getGrade()>=commandg && m[command1].getGrade()<=commandg2){
				s.display(cout);
			}	
		}
	}
};

struct studentidrangegrade {
	string command1;
	int commandg;
	int commandg2; //no need for command1=command etc.
	studentidrangegrade(string command, int commandgr, int commandgr2): command1(command), commandg(commandgr),
																   commandg2(commandgr2){}
	void operator()(Student& s) {
		Grade g;
		//cout<<(s.getgrade().find(command1) == s.getgrade().end());
		map<string,Grade> m = s.getgrade();
		if(m.find(command1) != m.end()){
			if(m[command1].getGrade()>=commandg && m[command1].getGrade()<=commandg2){
				s.displayallid(cout);
			}	
		}
	}
};
