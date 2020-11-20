/*
 * @Author: your name
 * @Date: 2020-11-20 21:38:29
 * @LastEditTime: 2020-11-20 23:27:48
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/include/PageLib.hpp
 */
#ifndef __Page_Lib_Hpp__
#define __Page_Lib_Hpp__
#include <vector>
#include "WebPage.hpp"
using std::vector;
class PageLib{
  public:
  void buildPageLib();
  private:
  void decodeFromXml();
  vector<WebPage> _Pages;
};
#endif