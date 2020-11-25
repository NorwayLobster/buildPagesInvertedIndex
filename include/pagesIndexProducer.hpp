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
#include "WebPage.hpp"
#include <vector>
#include <string>
#include <set>
#include <map>
#include <utility>
using std::string;
class PagesIndexProducer{
 public: 
 using docId=size_t;
 using Frequency=size_t;
 using tfidfWeight=double;
  PagesIndexProducer()=default;
  PagesIndexProducer(splitToolCppJieba*p, PagesDeduplication *p1, const string&src,const string&destNew);
  ~PagesIndexProducer()=default;
  PagesIndexProducer(const PagesIndexProducer&)=delete;
  void buildIndex();//重点：w=tf*idf算法, tf归一化和w的归一化 //相似度计算：重点余弦相似度
  void storeIndex(const string&);
  private:
  void deduplicate();
  void decodeFromXml(const string& filePath);
  void encodeToNewXml(const string& xmlNewDestination);
  // void wordSegmentationAndStatistics();

  private:
  splitToolCppJieba *_cppJieBa;
  PagesDeduplication * _pPagesDeduplication;
  std::vector<WebPage>  _pagesVec;
  std::vector<WebPage>  _pagesNewVec;//without duplication page //TODO：可以不存储两次,节省空间
  // std::vector<std::vector<string>>  _wordPages;
  std::vector<std::vector<string>>  _wordNewPagesVec;
  std::map<string,std::set<std::pair<docId, std::pair<Frequency,tfidfWeight>>>> _index;
  //word, <docid,(frequency,weight)>, <docid,(frequency,weight)>, ...
};
#endif