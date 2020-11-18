<!--
 * @Author: your name
 * @Date: 2020-11-17 16:12:56
 * @LastEditTime: 2020-11-18 14:43:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/README.md
-->
# buildPagesInvertedIndex
# project plan
##1. use pugixml parse rss file
##2. remove html tag using boost::regex in rss
##3. build page.dat and offset.dat, and save it into disk
##3.1 use page.xml and xpath language to query xml file inorder to get specific docid webpage, instead of page.dat and offset.dat
##4. unique pages using simhash
##5. build InvertedIndex for small data, all in  memory
##5.1 build InvertedIndex, for big data, using disk and memory, during building
##5.5  compute weight, based on tf-idf algorithm
##6.  add new page  into page.xml
##7.  增量更新倒排索引
##8.  save page into RDB, or xml db