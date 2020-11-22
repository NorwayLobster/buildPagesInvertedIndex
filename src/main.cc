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
#include "WebPage.hpp"
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
	string en_file = project_root_dir+config.getConf().at("en_file");
  string xmlSrcFilePath=conf.getConf("");
	string en_dictionary_fullpath = project_root_dir+config.getConf()["en_dictionary_fullpath"];
  string pageLibXmlDestinationFilePath;
	string en_dictionary_index_fullpath =project_root_dir+config.getConf()["en_dictionary_index_fullpath"];
    // cout<<"en_file:"<<en_file<<endl;
    // cout<<"en_dict...:"<<en_dictionary_fullpath<<std::endl;
    // cout<<"en_dict_index...:"<<en_dictionary_index_fullpath<<std::endl;
	port::xmlparser::PageLib pageLib;
  pageLib.decodeFromXml(xmlSrcFilePath);
  pageLib.encodeToXml(pageLibXmlDestinationFilePath);
#endif

#if 1 
	string cn_fileOfFilesName_fullPath = project_root_dir+config.getConf().at("cn_file_path");
	string cn_dictionary_fullpath = project_root_dir+config.getConf()["cn_dictionary_fullpath"];
	string cn_dictionary_index_fullpath =project_root_dir+config.getConf()["cn_dictionary_index_fullpath"];

	string jieba_dictionary_index_fullpath = project_root_dir+config.getConf()["dict_path"];
	string jieba_hmm_fullpath = project_root_dir+config.getConf()["hmm_path"];
	string jieba_user_dict_fullpath = project_root_dir+config.getConf()["user_dict_path"];
	string jieba_idf_fullpath = project_root_dir+config.getConf()["idf_path"];
	string jieba_stopword_fullpath = project_root_dir+config.getConf()["stopword_path"];

    splitToolCppJieba spT(jieba_dictionary_index_fullpath, jieba_hmm_fullpath, jieba_user_dict_fullpath, jieba_idf_fullpath, jieba_stopword_fullpath);

    pageIndexProducer indexPro;
    dictProducer cnDictPro(&spT);
    std::ifstream ifs(cn_fileOfFilesName_fullPath); 
    string line;
    while(std::getline(ifs,line)){
	string cn_file_path = project_root_dir+"inputData/"+line;
        // cout<<"filePullPath:"<<cn_file_path<<endl;
        cnDictPro.buildChineseDict(cn_file_path);
    }
    cnDictPro.storeDict(cn_dictionary_fullpath); //dictPro.storeDict("../data/dictChinese.dat");

    indexProducer cnIndexPro;
    cnIndexPro.buildIndex(cn_dictionary_fullpath);
    cnIndexPro.storeIndex(cn_dictionary_index_fullpath); //dictPro.storeIndex("../data/dictChineseIndex.dat");
#endif
    return 0;
}