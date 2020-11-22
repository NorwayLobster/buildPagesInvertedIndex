#ifndef __pages_Deduplication_Hpp__
#define __pages_Deduplication_Hpp__

#include "simhash/simhasher.hpp"
#include "bloomfilter/bloomfilter.hpp"
class pagesDeduplication{
  pagesDeduplication()=default;
  pagesDeduplication(const pagesDeduplication&)=delete;
  ~pagesDeduplication()=default;
  void deduplicate();
  private:
  BloomFilter _bf;
  simhash::Simhasher _sh;
};
#endif