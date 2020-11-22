/*
 * @Author: your name
 * @Date: 2020-11-20 21:38:29
 * @LastEditTime: 2020-11-21 15:26:56
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/include/PageLib.hpp
 */
#ifndef __Page_Lib_Hpp__
#define __Page_Lib_Hpp__
#include <vector>
#include "WebPage.hpp"
using std::vector;

namespace port::xmlparser {
class PageLib{
  public:
  void encodeToXml(const string& pageDestinationFullPath);
  void decodeFromXml(const string& pageSrcFullPath);
  private:
  vector<WebPage> _pagesVec;
};
}//end of namespace port::xmlparser
#endif