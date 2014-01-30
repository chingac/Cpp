#include <string>
#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "student.h"

//should declare functions as inline, or separate main in another cpp file
//declare ascending order of id functions above sorting
int main(int argc, char** argv){
	string line2;
	vector<Student> st;
	vector<string> command;
	Student s;
	string word;

	if (argc!= 2){
		cerr<< "usage: " << argv[0]<< argv[1]<<" input file"<< endl;
		return 1;
	}
	ifstream in(argv[1],ios_base::in);
	if(!in){
		cerr<<"unable to open "<<argv[1]<<endl;
		return 1;
	} 

	while(in>>s){
		st.push_back(s);
	}
	sort(st.begin(), st.end());
	while(1){
		cerr << "Enter commands: "<< endl;

		if(!getline(cin, line2)){
			break;
		}

		istringstream is(line2);
		if(is.eof()){
			break;
		}
		while(is>>word){
			command.push_back(word);
		}

		vector<string>::iterator cd;
		for(cd=command.begin(); cd != command.end(); ++cd){
			if (line2 == "show"){
				vector<Student>::iterator s;
				for (s = st.begin(); s != st.end(); ++s) {
					s->display(cout);
				}
			} else if (line2 == "showid"){
				vector<Student>::iterator s;
				for (s = st.begin(); s != st.end(); ++s) {
					s->displayallid(cout);
				}	
				//show id a11111111
			} else if (*cd == "show" && *(cd + 1)=="id"){
				for_each(st.begin(), st.end(), student1(*(cd + 2)));
			} else if (*cd == "show" && *(cd + 1)=="name"){
				vector<Student>::iterator s;
				for (s = st.begin(); s != st.end(); ++s) {
					s->displayname(cout, *(cd + 2) , *(cd + 3));
				}
				//show grade comp2510 0 100 and show grade comp2510 25
			} else if (*cd == "show" && *(cd + 1)=="grade"){
				if(command.size() == 5){
					istringstream g(*(cd + 3));
					istringstream g2(*(cd + 4));
					int grade1;
					int grade2;
					g>>grade1;
					g2>>grade2;
					for_each(st.begin(), st.end(), studentrangegrade(*(cd + 2),grade1,grade2));
					g.clear();
					g2.clear();
				} else {
					istringstream g(*(cd + 3));
					int grade1;
					g>>grade1;
					for_each(st.begin(), st.end(), studentgrade(*(cd + 2),grade1));
					g.clear();	
				}	
				//showid grade comp2510 0 100 and showid grade comp2510 25
			} else if (*cd == "showid" && *(cd + 1)=="grade"){
				if(command.size() == 5){
					istringstream g(*(cd + 3));
					istringstream g2(*(cd + 4));
					int grade1;
					int grade2;
					g>>grade1;
					g2>>grade2;
					for_each(st.begin(), st.end(), studentidrangegrade(*(cd + 2),grade1,grade2));
					g.clear();
					g2.clear();
				} else {
					istringstream g(*(cd + 3));
					int grade1;
					g>>grade1;
					for_each(st.begin(), st.end(), studentidgrade(*(cd + 2),grade1));
					g.clear();	
				}	
				//showid name
			}  else if (*cd == "showid" && *(cd + 1)=="name"){
				vector<Student>::iterator s;
				for (s = st.begin(); s != st.end(); ++s) {
					s->displaynameid(cout, *(cd + 2),*(cd + 3));
				}	
			} 
		}
		command.clear();
	}	
}