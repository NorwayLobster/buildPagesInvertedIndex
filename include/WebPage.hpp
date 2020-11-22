/*
 * @Author: your name
 * @Date: 2020-11-20 21:29:34
 * @LastEditTime: 2020-11-21 15:18:57
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/include/WebPage.hpp
 */
#ifndef __Web_Page_Hpp__
#define __Web_Page_Hpp__
#include <string>
#include <optional>
using std::string;
class WebPage{
  public:
    string _docid; 
    string _docUrl; 
    string _docSummary; 
    string _title; 
    string _description;
    std::optional<std::string> _content;
};
#endif 