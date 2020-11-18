 ///
 /// @file    main.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-11-17 16:29:00
 ///
 
#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <boost/regex.hpp>
#include "pugi/pugixml.hpp"
using namespace std;
using namespace pugi;
struct WebPage{
	string _title;
	string _link;
	string _description;
	std::optional<std::string> _content;
};

namespace port::xmlparser {
void decodeFromXml(const string& filePath, vector<WebPage>& page_vec){
	cout<<"test0"<<endl;
	xml_document doc;
	xml_parse_result result = doc.load_file(filePath.c_str());
	if(!result){
		cerr<<"pugixml parse error"<<endl;
		return ;
	}
	cout<<doc.child("rss").attribute("version").value()<<endl;
	cout<<doc.child("rss").child("channel").child("title").text().get()<<endl;
	cout<<doc.child("rss").child("channel").child("description").text().get()<<endl;
	cout<<doc.child("rss").child("channel").child("link").text().get()<<endl;
	cout<<doc.child("rss").child("channel").child("item").child("title").text().get()<<endl;
	cout<<doc.child("rss").child("channel").child("item").child("link").text().get()<<endl;
	// cout<<doc.child("rss").child("channel").child("item").child("content:encoded").text().get()<<endl;
	cout<<doc.child("rss").child("channel").child("item").next_sibling().child("title").text().get()<<endl;
cout<<endl;
	pugi::xml_node items_node= doc.child("rss").child("channel");
	for(xml_node_iterator it= items_node.begin();it!=items_node.end();++it){
		cout<<"title:"<<it->child("title").text().get()<<endl;
	}
	cout<<endl;
	for(xml_node &item_node:items_node.children("item")){ //range taraverse
		cout<<"title:"<<item_node.child("title").text().get()<<endl;
		WebPage page;
		page._title=item_node.child("title").text().get();
		page._link=item_node.child("link").text().get();
		page._description=item_node.child("description").text().get();
		// cout<<"description:"<<item_node.child("description").text().get()<<endl;
		const string &iContent=item_node.child("content:encoded").text().get();

		//remove html tag
		string szReg = "<.*?>";
		boost::regex fmt(szReg);
		page._content=boost::regex_replace(string(iContent),fmt,string(""));

		page_vec.push_back(page);
	}
}
void encodeToXml(const string& filepath,vector<WebPage>&page_vec){
  // LOG_DEBUG("createUserDataXml: start create userData AVP with XML");
  pugi::xml_document doc;
  pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
  decl.append_attribute("version") = "1.0";
  decl.append_attribute("encoding") = "UTF-8";
  pugi::xml_node webData = doc.append_child("WebPageData");
	int index=0;
  for (auto& webpage : page_vec) {
    pugi::xml_node pageData = webData.append_child("page");
    pugi::xml_node docid= pageData.append_child("docid");
		// add docid
    docid.text().set(to_string(index++).c_str());
    pugi::xml_node title = pageData.append_child("title");
    title.text().set(webpage._title.c_str());
    pugi::xml_node link = pageData.append_child("link");
    link.text().set(webpage._link.c_str());

		pugi::xml_node content = pageData.append_child("content");
    if (webpage._content.has_value()) {
    content.text().set(webpage._content.value().c_str());
    } else {
    content.text().set(webpage._description.c_str());
      // LOG_DEBUG( "ShUserData2Xml::createUserDataXml: Servie Data missed in " "ServiceIndication", "servIndId", v->servIndId);
    }
  }
  // std::stringstream ss;
  // doc.save(ss);
  // userData = ss.str();
		doc.save_file(filepath.c_str());
  // LOG_DEBUG("createUserDataXml: create userData XML string finished", "userData", userData);
}
}//end of namespace port::xmlparser
int main(int argc, char **argv){
	if(argc!=3){
		cerr<<"./a.out srcFilePath destinationFilePath"<<endl;
		exit(-1);
	}
	vector<WebPage> pages;
	port::xmlparser::decodeFromXml(argv[1],pages);
	port::xmlparser::encodeToXml(argv[2],pages);
	return 0;
}
