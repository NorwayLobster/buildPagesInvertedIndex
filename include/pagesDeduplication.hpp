#ifndef __pages_Deduplication_Hpp__
#define __pages_Deduplication_Hpp__

#include "simhash/simhasher.hpp"
#include "bloomfilter/BloomFilter.hpp"
#include <string>
using std::string;
class PagesDeduplication{
  public:
  PagesDeduplication(const string&bloomfilterDestinationFullPath, size_t mBloomFilterBitNo, const string& jieba_dictionary_index_fullpath, const string& jieba_hmm_fullpath, const string& jieba_idf_fullpath, const string& jieba_stopword_fullpath);
  PagesDeduplication(const PagesDeduplication&)=delete;
  ~PagesDeduplication()=default;
  bool isDuplication(const string&page);
  private:
  BloomFilter _bf;
  simhash::Simhasher _sh;
};
#endif