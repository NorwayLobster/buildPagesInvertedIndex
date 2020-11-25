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

PagesIndexProducer::PagesIndexProducer(splitToolCppJieba*p, PagesDeduplication* dedup, const string& xmlsrc, const string&xmlNewDestination)
:_cppJieBa(p)
,_pPagesDeduplication(dedup)
{
  cout<<"PagesIndexProduer(...) ctor"<<endl;
  decodeFromXml(xmlsrc);
  // deduplicate();
  encodeToNewXml(xmlNewDestination);
  wordSegmentationAndStatistics();
}


void PagesIndexProducer::wordSegmentationAndStatistics(){
  cout<<"PagesIndexProduer::wordSegmentation()"<<endl;
}
void PagesIndexProducer::encodeToNewXml(const string&xmlNewDestination){
  cout<<"PagesIndexProduer::encodeToNewXml()"<<endl;
	// _pagesNewVec;
}
void PagesIndexProducer::deduplicate(){
  cout<<"PagesIndexProduer::deduplicate()"<<endl;
	for(auto page:_pagesVec){
		if(!_pPagesDeduplication->isDuplication(page._content)){
			_pagesNewVec.push_back(page);
		}
	}
}
void PagesIndexProducer::buildIndex(){
  cout<<"PagesIndexProduer::buildIndex()"<<endl;
}
void PagesIndexProducer::storeIndex(const string& dest){
  cout<<"PagesIndexProduer::storeIndex(const string& src)"<<endl;
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
	for(pugi::xml_node &page_node:pages_node.children("page")){ //range taraverse
		// cout<<"title:"<<item_node.child("title").text().get()<<endl;
		WebPage page;
		page._title=page_node.child("title").text().get();//title,description need word segmentation?
		page._link=page_node.child("link").text().get();
		page._description=page_node.child("description").text().get();
		// cout<<"description:"<<item_node.child("description").text().get()<<endl;
		const string &iContent=page_node.child("content").text().get();
		_pagesVec.push_back(page);
  }
}