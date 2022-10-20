#pragma once
#ifndef XML_H
#define XML_H
#include "../data/text.hpp"
#include "../data/keyvaluepair.hpp"
using cyh::data::text;
using cyh::data::KeyValuePair;
namespace cyh::data {
	class Xml {	
		text get_tag_str(text& raw,text tagName, size_t* endIndex);
		text get_tag_str(text& raw,text tagName);
		text get_tag_start_str(text tagName);
		text get_tag_end_str(text tagName);
		text remove_lead_space(text txt);
		void start_read();
		void read_single(text& text);
		void read_attri_from_str(text txt);	
		void get_tag_from_process_text(text& txt);
		void get_attri_from_process_text(text& txt);		
	public:
		text Tag;
		text Data;
		text rawStr;
		Xml* first = nullptr;
		Xml* parent = nullptr;
		Xml* child = nullptr;
		Xml* prev = nullptr;
		Xml* next = nullptr;
		vector<KeyValuePair> Attributes;
		Xml():Tag("tag"),Data("NULL"){}
		Xml(Xml* pre):prev(pre){}
		Xml(Xml* prnt, Xml* pre):parent(prnt),prev(pre){}
		KeyValuePair GetAttribute(text _name);
		text ToString();
		void AddAttribute(KeyValuePair attr);
		void AddAttribute(text key, text value);
		void ReadAttributeStr(text t);
		void ReadFromText(text& text);
		void process(text _txt);
	};
}
#endif // !JSON_H
