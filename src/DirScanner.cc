/*
 * @Author: your name
 * @Date: 2020-11-22 11:46:06
 * @LastEditTime: 2020-11-22 11:54:56
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/src/DirScanner.cc
 */

#include "DirScanner.hpp"
#include <filesystem>
#include <iostream>
namespace fs=std::filesystem;
using std::endl;
using std::cout;

void dirScanner::scan(const string &p1){
  fs::path p=p1;
  for(const fs::directory_entry &entry:fs::directory_iterator(p)){
    fs::path p2=entry.path(); 
    fs::path fileFullPath=fs::absolute(p2);
    // cout<<"fileFullPath:"<<fileFullPath<<endl;
    _filesFullPathVec.push_back(fileFullPath.string());
  }
}
vector<string> & dirScanner::get(){
  // for(auto p:_filesFullPathVec){ std::cout<<p<<endl; }
  // std::cout<<std::endl;
  return _filesFullPathVec;
}