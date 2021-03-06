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
// #include <utility>
#include <tuple>
using std::string;
using std::vector;
class PagesIndexProducer{
 using docId=unsigned long long int;
 using Frequency=size_t;
//  using Frequency=int;
 using tfidfWeight=double;
//  template<typename T1, typename T2, typename T3, typename T4> struct myTuple{ T1 id; T2 frequency; T3 tfidfweight; T4 max_frequency; };
  class Data{
    public:
    docId id; 
    Frequency frequency; 
    tfidfWeight tfidfweight;
    Frequency max_frequency;
    Data(docId i, Frequency fre, tfidfWeight w, Frequency max_fre)
    :id(i)
    ,frequency(fre)
    ,tfidfweight(w)
    ,max_frequency(max_fre)
    {}
  };
 public: 
  PagesIndexProducer()=default;
  PagesIndexProducer(splitToolCppJieba*p, PagesDeduplication *p1, const string&src,const string&destNew);
  ~PagesIndexProducer()=default;
  PagesIndexProducer(const PagesIndexProducer&)=delete;
  void buildIndex();//重点：w=tf*idf算法, tf归一化和w的归一化 //相似度计算：重点余弦相似度
  void caculateTfIdfWeight();
  void storeIndex(const string&);
  private:
  void deduplicate();
  void decodeFromXml(const string& filePath);
  void encodeToNewXml(const string& xmlNewDestination);
  // void wordSegmentationAndStatistics();

  private:
  splitToolCppJieba *_cppJieBa;
  PagesDeduplication * _pPagesDeduplication;
  vector<WebPage>  _pagesVec;
  vector<WebPage>  _pagesNewVec;//without duplication page //TODO：可以不存储两次,节省空间
  // std::vector<std::vector<string>>  _wordPages;
  vector<vector<string>>  _wordNewPagesVec;
  // std::map<string,std::set<std::pair<docId, std::pair<Frequency,tfidfWeight>>>> _index;
  std::map<string,vector<Data>> _index;
  // std::map<string,vector<myTuple<docId, Frequency,tfidfWeight,Frequency>>> _index;
  // std::map<string,vector<std::tuple<docId, Frequency,tfidfWeight>>> _index;
  //word, <docid,(frequency,weight)>, <docid,(frequency,weight)>, ...
};
#endif