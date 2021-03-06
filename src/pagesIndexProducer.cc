/*
 * @Author: your name
 * @Date: 2020-11-21 15:40:49
 * @LastEditTime: 2020-11-21 15:40:50
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /buildPagesInvertedIndex/src/pageIndexProducer.cc
 */

#include "pagesIndexProducer.hpp"
#include "splitToolCppJieba.hpp"
#include "pugixml/pugixml.hpp"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cmath>
using std::pair;
using std::endl;
using std::cout;


PagesIndexProducer::PagesIndexProducer(splitToolCppJieba*p, PagesDeduplication* dedup, const string& xmlsrc, const string&xmlNewDestination)
:_cppJieBa(p)
,_pPagesDeduplication(dedup)
{
  // cout<<"PagesIndexProduer(...) ctor"<<endl;
  decodeFromXml(xmlsrc);
	// cout<<"xmlsrc:"<<xmlsrc<<endl;
  deduplicate();
  encodeToNewXml(xmlNewDestination);
  // wordSegmentationAndStatistics();
}


void PagesIndexProducer::buildIndex(){
  cout<<"PagesIndexProduer::buildIndex()"<<endl;
	vector<string> vec_word;
	std::unordered_map<string,Frequency> hashDict;
	for(auto page:_pagesNewVec){
		// cout<<"page._content:"<<page._content<<endl;
		_cppJieBa->cut(page._content,vec_word);
		_wordNewPagesVec.push_back(vec_word);//do not forget this one
		// cout<<"1"<<endl;
		for(auto word:vec_word){
        hashDict[word]+=1;
		} 
		// cout<<"2"<<endl;
		docId docid;//=std::stoul(page._docid,nullptr,0);
		// unsigned long long int docid;//=std::stoul(page._docid,nullptr,0);
		std::stringstream ss;
		ss<<page._docid;
		ss>>docid;

		// cout<<"hashDict.size():"<<hashDict.size()<<endl;
		// for(auto p:hashDict){ cout<<"first:"<<p.first<<",second:"<<p.second<<endl; }
		// cout<<"3"<<endl;
		std::unordered_map<string,Frequency>::iterator iter_max_tf_in_the_same_document=std::max_element(hashDict.begin(),hashDict.end(), [](const pair<string,Frequency> &lhs,const pair<string,Frequency> &rhs)->bool{return lhs.second<rhs.second;});
		// cout<<"3.1"<<endl;
		// cout<<"max_tf_in_the_same_document:"<<iter_max_tf_in_the_same_document->first<<endl;
		Frequency max_tf_in_the_same_document=iter_max_tf_in_the_same_document->second;
		// cout<<"4"<<endl;
		for(auto p:hashDict){
			// cout<<"page.id:"<<page._docid<<endl;
			// cout<<"word:"<<p.first<<",docid:"<<docid<<",frequencey:"<<p.second<<endl;
			// _index[p.first].insert(std::pair(docid,std::pair(p.second,0.0)));//weight 初始为0

			// cout<<"in for"<<endl;
			_index[p.first].push_back(Data(docid, p.second,0.0,max_tf_in_the_same_document));//weight 初始为0
			// _index[p.first].push_back(myTuple<docId, Frequency,tfidfWeight,Frequency>(docid, p.second,0.0,max_tf_in_the_same_document));//weight 初始为0
			// _index[p.first].push_back(std::make_tuple(docid, p.second,0.0,max_tf_in_the_same_document));//weight 初始为0
		}
		vec_word.clear();
		hashDict.clear();
		ss.clear();
	}
}


void PagesIndexProducer::caculateTfIdfWeight(){
	double a=0.4;//from 这就是搜索引擎
	// double tf=a+(1-a)*TF/max(TF_SET);
	// double idf=log(N/DF);
	int n=_wordNewPagesVec.size();
	// cout<<"n:"<<n<<endl;
	double tf;
	int df;
	double idf;
  // std::map<string,vector<std::tuple<docId, Frequency,tfidfWeight>>> _index;
	// int i=10;
	for(auto& p:_index){
		// i--;
		df=p.second.size();

		idf=std::log(n/(double)(df+1));//防止某个单词的df=0;// please note
		
		// cout<<"idf:"<<idf<<endl;
		// if(i<0) break; continue;
		for(auto& t:p.second){
			tf= a+(1-a)*(t.frequency/double(t.max_frequency));//very tricky
			// cout<<"tf:"<<tf<<endl;
			t.tfidfweight=tf*idf;
			// cout<<"t.tfidfweight:"<<t.tfidfweight<<endl;
		}
	}
}

void PagesIndexProducer::storeIndex(const string& dest){
  cout<<"PagesIndexProduer::storeIndex(const string& src)"<<endl;
	std::ofstream ofs(dest);
	if(!ofs){
		std::cerr<<"of error"<<endl;
		exit(-1);
	}
	for(auto p:_index){
			ofs<<p.first<<":";
			// ofs<<p.first<<" ";
			// cout<<"word:"<<p.first;
			// for(auto p_:p.second){
			// 	// cout<<",docid:"<<p_.first<<",frequencey:"<<p_.second.first<<" ";
			// 	ofs<<p_.first<<" "<<p_.second.first<<" "<<p_.second.second<<" ";
			// }

			for(auto t:p.second){
				// ofs<<std::get<0>(t)<<" "<<std::get<1>(t)<<" "<<std::get<2>(t)<<" ";
					ofs<<t.id<<","<<t.frequency<<","<<t.tfidfweight<<","<<t.max_frequency<<" ";
					// ofs<<t.id<<" "<<t.frequency<<" "<<t.tfidfweight<<" "<<t.max_frequency<<",";
			}
			ofs<<endl;
			// cout<<endl;
	}
}



void PagesIndexProducer::encodeToNewXml(const string&filepath){
  cout<<"PagesIndexProduer::encodeToNewXml()"<<endl;
	// _pagesNewVec;
  pugi::xml_document doc;
  pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
  decl.append_attribute("version") = "1.0";
  decl.append_attribute("encoding") = "UTF-8";
  pugi::xml_node webData = doc.append_child("WebPageData");
	int index=0;
  for (auto& webpage :_pagesNewVec) {
    pugi::xml_node pageData = webData.append_child("page");
    pugi::xml_node docid= pageData.append_child("docid");
		// add docid
    docid.text().set(std::to_string(index++).c_str());
    pugi::xml_node title = pageData.append_child("title");
    title.text().set(webpage._title.c_str());
    pugi::xml_node link = pageData.append_child("link");
    link.text().set(webpage._link.c_str());

		pugi::xml_node content = pageData.append_child("content");
    content.text().set(webpage._content.c_str());
    // if (webpage._content.has_value()) {
    // content.text().set(webpage._content.value().c_str());
    // } else {
    // content.text().set(webpage._description.c_str());
      // LOG_DEBUG( "ShUserData2Xml::createUserDataXml: Servie Data missed in " "ServiceIndication", "servIndId", v->servIndId);
    // }
  }
  // std::stringstream ss;
  // doc.save(ss);
  // userData = ss.str();
		doc.save_file(filepath.c_str());
  // LOG_DEBUG("createUserDataXml: create userData XML string finished", "userData", userData);
}

void PagesIndexProducer::deduplicate(){
  cout<<"PagesIndexProduer::deduplicate()"<<endl;
	for(auto page:_pagesVec){
// 
		bool flag=_pPagesDeduplication->isDuplication(page._content);
		// cout<<"Duplication flag:"<<flag<<endl;
		if(!flag){
		// if(!_pPagesDeduplication->isDuplication(page._content)){
			_pagesNewVec.push_back(page);
		}
	}
}

void PagesIndexProducer::decodeFromXml(const string& filePath){
	// cout<<"test0"<<endl;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filePath.c_str());
	if(!result){
		std::cerr<<"pugixml parse error"<<endl;
		return ;
	}
	// cout<<doc.child("rss").attribute("version").value()<<endl;
	// cout<<doc.child("rss").child("channel").child("title").text().get()<<endl;
	// cout<<doc.child("rss").child("channel").child("description").text().get()<<endl;
	// cout<<doc.child("rss").child("channel").child("link").text().get()<<endl;
	// cout<<doc.child("rss").child("channel").child("item").child("title").text().get()<<endl;
	// cout<<doc.child("rss").child("channel").child("item").child("link").text().get()<<endl;
	// // cout<<doc.child("rss").child("channel").child("item").child("content:encoded").text().get()<<endl;
	// cout<<doc.child("rss").child("channel").child("item").next_sibling().child("title").text().get()<<endl;
// cout<<endl;
	pugi::xml_node pages_node= doc.child("WebPageData");
	// for(xml_node_iterator it= items_node.begin();it!=items_node.end();++it){ cout<<"title:"<<it->child("title").text().get()<<endl; }
	// cout<<endl;
	// int i=0;
	for(pugi::xml_node &page_node:pages_node.children("page")){ //range taraverse
		// cout<<"title:"<<item_node.child("title").text().get()<<endl;
		WebPage page;
		// page._docid=std::to_string(i++);
		page._docid=page_node.child("docid").text().get();//title,description need word segmentation?
		page._title=page_node.child("title").text().get();//title,description need word segmentation?
		page._link=page_node.child("link").text().get();
		page._description=page_node.child("description").text().get();
		// cout<<"description:"<<item_node.child("description").text().get()<<endl;
		page._content=page_node.child("content").text().get();
		// cout<<"page.page:"<<page._content<<endl;
		_pagesVec.push_back(page);
  }
}