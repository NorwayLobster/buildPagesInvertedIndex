/*
 * @Author: your name
 * @Date: 2020-11-20 16:36:43
 * @LastEditTime: 2020-11-20 23:29:29
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/src/main.cc
 */

#include <iostream>
#include <vector>
#include "hello.hpp"
#include "PageLib.hpp"
#include "WebPage.hpp"
#include "configure.hpp"
using std::endl;
using std::cout;
using std::vector;
int main(int argc, char **argv){
  if(2!=argc){
    std::cerr<<"./a.out  configurePath"<<endl;
    exit(-1);
  }
  Configuration conf(argv[1]);
  PageLib pageLib;
  return 0;
}