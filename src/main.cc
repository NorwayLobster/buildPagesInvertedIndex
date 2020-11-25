/*
 * @Author: your name
 * @Date: 2020-11-20 16:36:43
 * @LastEditTime: 2020-11-21 15:42:18
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/src/main.cc
 */

#include <iostream>
#include <vector>
#include <string>
#include "PageLib.hpp"
#include "pagesIndexProducer.hpp"
#include "pagesDeduplication.hpp"
#include "WebPage.hpp"
#include "DirScanner.hpp"
#include "configure.hpp"
using std::endl;
using std::cout;
using std::vector;
using std::string;

int main(int argc, char **argv){
	if(argc!=2){
		std::cerr<<"args error: ./a.out confFilePath"<<endl;
		exit(EXIT_FAILURE);
		// exit(-1);
	}

   Configuration config(argv[1]);
	string project_root_dir = config.getConf().at("project_root_dir");

#if 1
	// string en_file = project_root_dir+config.getConf().at("en_file");
  string xmlSrcFilesDir=project_root_dir+config.getConf().at("xmlSrcFilesDir");
  cout<<xmlSrcFilesDir<<endl;
	// string en_dictionary_fullpath = project_root_dir+config.getConf()["en_dictionary_fullpath"];
  string pageLibXmlDestinationFilePath=project_root_dir+config.getConf().at("pageLibXmlDestinationFilePath");
  cout<<pageLibXmlDestinationFilePath<<endl;
    // cout<<"en_file:"<<en_file<<endl;
    // cout<<"en_dict...:"<<en_dictionary_fullpath<<std::endl;
    // cout<<"en_dict_index...:"<<en_dictionary_index_fullpath<<std::endl;
    dirScanner scanner;
    scanner.scan(xmlSrcFilesDir);
    vector<string> v=scanner.get();
	port::xmlparser::PageLib pageLib;
    for(auto xmlSrcFilePath:v){
      pageLib.decodeFromXml(xmlSrcFilePath);
    }
  pageLib.encodeToXml(pageLibXmlDestinationFilePath);
#endif

#if 1 
	// string cn_fileOfFilesName_fullPath = project_root_dir+config.getConf().at("cn_file_path");
	// string cn_dictionary_fullpath = project_root_dir+config.getConf()["cn_dictionary_fullpath"];

	string jieba_dictionary_index_fullpath = project_root_dir+config.getConf()["dict_path"];
	string jieba_hmm_fullpath = project_root_dir+config.getConf()["hmm_path"];
	string jieba_user_dict_fullpath = project_root_dir+config.getConf()["user_dict_path"];
	string jieba_idf_fullpath = project_root_dir+config.getConf()["idf_path"];
	string jieba_stopword_fullpath = project_root_dir+config.getConf()["stopword_path"];
  cout<<jieba_stopword_fullpath<<endl;

    splitToolCppJieba spT(jieba_dictionary_index_fullpath, jieba_hmm_fullpath, jieba_user_dict_fullpath, jieba_idf_fullpath, jieba_stopword_fullpath);
  string bloomfilterDestinationFullPath=project_root_dir+config.getConf()["bloomfilterDestinationFullPath"];
  cout<<"bloomfilterDestinationFullPath:"<<bloomfilterDestinationFullPath<<endl;
  size_t mBloomFilterBitNo=5;//i.e. hash no.
    PagesDeduplication pagesD(bloomfilterDestinationFullPath, mBloomFilterBitNo, jieba_dictionary_index_fullpath, jieba_hmm_fullpath, jieba_idf_fullpath, jieba_stopword_fullpath);

    // Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8");
  string xmlsrc=pageLibXmlDestinationFilePath;
  string newxmldest;
  PagesIndexProducer cnIndexPro(&spT,&pagesD,xmlsrc,newxmldest);
    // dictProducer cnDictPro(&spT);
  //   std::ifstream ifs(cn_fileOfFilesName_fullPath); 
  //   string line;
  //   while(std::getline(ifs,line)){
	// string cn_file_path = project_root_dir+"inputData/"+line;
  //       // cout<<"filePullPath:"<<cn_file_path<<endl;
  //       cnDictPro.buildChineseDict(cn_file_path);
  //   }
  //   cnDictPro.storeDict(cn_dictionary_fullpath); //dictPro.storeDict("../data/dictChinese.dat");

    // indexProducer cnIndexPro;
	string indexFullPath=project_root_dir+config.getConf().at("indexFullPath");
  cnIndexPro.buildIndex();
  cnIndexPro.storeIndex(indexFullPath); //dictPro.storeIndex("../data/dictChineseIndex.dat");
#endif
    return 0;
}