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
  cout<<"pagesDeduplication::isDeduplicate(...)"<<endl;
  int topN=5;
  uint64_t simhashVal;
  _sh.make(page,topN,simhashVal);
  string simhashValString;
  simhash::Simhasher::toBinaryString(simhashVal, simhashValString);
  return _bf.testAndadd(simhashValString);
}