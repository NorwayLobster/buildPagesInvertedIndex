 ///
 /// @file    splitToolCppJieba.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-24 20:33:08
 ///
 
#ifndef __SPLITTOOL_CPPJIEBA__
#define __SPLITTOOL_CPPJIEBA__

#include <iostream>
#include <vector>
#include <string>
#include "splitTool.hpp"
#include "cppjieba/Jieba.hpp"
using std::cout;
using std::endl;
using std::string;
class splitToolCppJieba: public splitTool{
public:
	splitToolCppJieba(const string&,const string&,const string&,const string&,const string&);
	virtual ~splitToolCppJieba();//派生类是virtual
	virtual	void cut(const string & sentence, vector<string>&);//派生类是virtual
private:
	cppjieba::Jieba _cppJieba;
};
#endif
