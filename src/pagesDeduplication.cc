#include "pagesDeduplication.hpp"
#include <string>
#include <iostream>
using std::string;
using std::endl;
using std::cout;

PagesDeduplication::PagesDeduplication(const string&bloomfilterDestinationFullPath, size_t mBloomFilterBitNo, const string& jieba_dictionary_index_fullpath, const string& jieba_hmm_fullpath, const string& jieba_idf_fullpath, const string& jieba_stopword_fullpath)
:_bf(bloomfilterDestinationFullPath.c_str(),mBloomFilterBitNo)
,_sh(jieba_dictionary_index_fullpath,  jieba_hmm_fullpath,  jieba_idf_fullpath,  jieba_stopword_fullpath)
{
  cout<<"pagesDeduplication(...) ctor"<<endl;
}

bool PagesDeduplication::isDuplication(const string&page){
  // cout<<"pagesDeduplication::isDeduplicate(...)"<<endl;
  // cout<<"page:"<<page<<endl;
  int topN=5;
  uint64_t simhashVal;
  _sh.make(page,topN,simhashVal);
  // cout<<"simhashVal:"<<simhashVal<<endl;
  uint64_t lhs=simhashVal;
  int n=3;
  for(auto rhs:_simhashvalVec){
    //isEqual(): o(N), 可以优化成O(1)
      bool flag=simhash::Simhasher::isEqual(lhs, rhs,n);//A和B的海明距离是否小于等于n，这个n值根据经验一般取值为3,
      if(flag)
        return true;//有重复
  }
  _simhashvalVec.push_back(simhashVal);
  return false;//无重复
  // string simhashValString;
  // simhash::Simhasher::toBinaryString(simhashVal, simhashValString);
  // cout<<"simhashValString:"<<simhashValString<<endl;
  // return _bf.testAndadd(simhashValString);
}