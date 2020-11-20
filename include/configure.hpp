/*
 * @Author: your name
 * @Date: 2020-11-20 21:52:30
 * @LastEditTime: 2020-11-20 23:25:39
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/include/configure.hpp
 */
 ///
 /// @file    configure.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-24 19:44:37
 ///
 
#ifndef __CONFIGURE_HPP__
#define __CONFIGURE_HPP__
#include <iostream>
#include <map>
#include <vector>
#include <string>
// #include<boost/utilities.hpp> 
// #include<boost/noncopyable.hpp> // find_package(Boost noncopyable component)
// #include "Noncopyable.h"
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
// class Configuration:public boost::noncopyable{
class Configuration{
public:
		Configuration()=default;
		Configuration(const Configuration&)=delete;
		Configuration(const string & filePath);
		map<string,string>  getConf();
		void showConfig();
		~Configuration();
private:
		void readFile();
private:
	string _filePath;
	map<string,string> _conf;
};
#endif
