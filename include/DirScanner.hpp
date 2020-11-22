/*
 * @Author: your name
 * @Date: 2020-11-22 11:41:53
 * @LastEditTime: 2020-11-22 11:45:53
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/include/DirScanner.hpp
 */
#ifndef __Dir_Scanner_Hpp__
#define __Dir_Scanner_Hpp__
#include<vector>
#include<string>
using std::vector;
using std::string;
class dirScanner{
  public:
    dirScanner()=default;
    dirScanner(const dirScanner &)=delete;
    ~dirScanner()=default;
    void scan(const string&);
    vector<string>& get();
  private:
  vector<string>  _filesFullPathVec;
};
#endif