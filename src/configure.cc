/*
 * @Author: your name
 * @Date: 2020-11-20 21:52:16
 * @LastEditTime: 2020-11-20 23:17:47
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/src/configure.cc
 */
 ///
 /// @file    configure.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-24 20:47:25
 ///
 
#include <iostream>
#include <cstdlib>
#include "configure.hpp"
#include <sstream>
#include <fstream>
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::stringstream;

Configuration::Configuration(const string & filePath):
_filePath(filePath)
{
	cout<<"Configuration() ctor"<<endl;
	readFile();
}
map<string,string>  Configuration::getConf() {
	return _conf;
}

void Configuration::readFile(){
	cout<<"readFile()"<<endl;
    ifstream ifs(_filePath);
    if(!ifs){
        cerr<<"ifs error"<<endl;
        return ;
    }
	string key,val,line;
	stringstream ss;
	while(getline(ifs,line)){
		ss.clear();
		ss<<line;
		ss>>key>>line;
		cout<<key<<"$"<<line<<endl;
		_conf[key]=line;
	}

}
Configuration::~Configuration(){
	cout<<"~Configuration()"<<endl;
}
void Configuration::showConfig(){
    cout<<"showConfig()"<<endl;
	for(auto &p:_conf){
		cout<<"key-val:"<<p.first<<",";
		if(p.first!="thread_num")
			cout<<p.second<<endl;
		else
			cout<<p.second<<endl;
		//	cout<<atoi(p.second.c_str())<<endl;
	}
		
}

