/*
 * @Author: your name
 * @Date: 2020-11-21 15:40:58
 * @LastEditTime: 2020-11-21 15:40:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/include/pageIndexProducer.hpp
 */
#ifndef __Pages_Index_Producer_Hpp__
#define __Pages_Index_Producer_Hpp__
#include "splitToolCppJieba.hpp"
#include "simhash/simhasher.hpp"
#include <vector>
#include <string>
#include <set>
#include <map>
using std::string;
class PagesIndexProducer{
 public: 
  PagesIndexProducer()=default;
  PagesIndexProducer(splitToolCppJieba*p, simhash::Simhasher *simhasher, const string&);
  ~PagesIndexProducer()=default;
  PagesIndexProducer(const PagesIndexProducer&)=delete;
  void buildIndex();
  void storeIndex(const string&);
  private:
  void pagesDeduplication();
  void decodeFromXml(const string& filePath);

  private:
  splitToolCppJieba *_p;
  std::vector<std::vector<string>>  _wordPages;
  std::map<string,std::pair<std::set<int>,double>> _index;
  simhash::Simhasher *_pSimhasher;
};
#endif