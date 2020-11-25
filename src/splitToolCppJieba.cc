 ///
 /// @file    splitToolEnglish.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-24 19:54:50
 ///
 
#include "splitToolCppJieba.hpp"
using std::cout;
using std::endl;
splitToolCppJieba::splitToolCppJieba(const string &dict_path, const string &hmm_path, const string &user_dict_path, const string& idf_path, const string & stopword_path)
:_cppJieba(dict_path,hmm_path,user_dict_path,idf_path,stopword_path){
	cout<<"splitToolCppJieba() ctor"<<endl;
}

splitToolCppJieba::~splitToolCppJieba(){
	cout<<"~splitToolCppJieba()"<<endl;
}

void splitToolCppJieba::cut(const string & sentence, vector<string>&words){ 
	cout<<"cut()"<<endl;
	_cppJieba.Cut(sentence,words,true);
}
