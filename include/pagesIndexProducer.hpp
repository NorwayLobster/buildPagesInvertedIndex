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
#include "pagesDeduplication.hpp"
#include <vector>
#include <string>
#include <set>
#include <map>
using std::string;
class PagesIndexProducer{
 public: 
  PagesIndexProducer()=default;
  PagesIndexProducer(splitToolCppJieba*p, pagesDeduplication *p1, const string&);
  ~PagesIndexProducer()=default;
  PagesIndexProducer(const PagesIndexProducer&)=delete;
  void buildIndex();//重点：w=tf*idf算法, tf归一化和w的归一化 //相似度计算：重点余弦相似度
  void storeIndex(const string&);
  private:
  void deduplicate();
  void decodeFromXml(const string& filePath);
  void encodeToNewXml(const string& filePath);

  private:
  splitToolCppJieba *_p;
  pagesDeduplication * _pPagesDeduplication;
  std::vector<std::vector<string>>  _wordPages;
  std::vector<std::vector<string>>  _wordNewPages;//without duplication page //TODO：可以不存储两次,节省空间
  std::map<string,std::pair<std::set<int>,double>> _index;
};
#endif