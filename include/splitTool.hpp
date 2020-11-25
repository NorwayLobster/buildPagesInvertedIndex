 ///
 /// @file    splitTool.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-24 19:48:01
 ///
 
#ifndef __SPLITTOOL__
#define __SPLITTOOL__
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::string;
class splitTool{
public:
	splitTool();
	virtual	~splitTool();
	virtual void cut(const string & sentence, vector<string>&)=0;
};
#endif
