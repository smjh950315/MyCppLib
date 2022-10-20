#pragma once
#ifndef JSON_H
#define JSON_H
#include "../data/text.hpp"
#include "../data/keyvaluepair.hpp"

using cyh::data::text;
using cyh::data::KeyValuePair;
namespace cyh::data {
	class Json {
	private:
		std::vector<text> split(text t);
		KeyValuePair read_attr(text t);
		void process(text txt);
		void start_read();
		void check_valid();
		bool is_root();
		text to_text(text interval,size_t tab_space);
		text to_raw_json_text();
		Json(Json* pre);
		Json(Json* prnt, Json* pre);
		text space_tab = " ";
		text ClBrStart = "{";
		text ClBrEnd = "}";
		text Comma = ",";
	public:
		text rawStr = "";		
		Json* first = nullptr;
		Json* parent = nullptr;
		Json* child = nullptr;
		Json* prev = nullptr;
		Json* next = nullptr;
		vector<KeyValuePair> Attributes;
		bool IsValidJson = false;
		Json() {}
		~Json();

		void ReadFromText(text& t);
		text ToTextForm();
		text ToTextByStruct();
		text ToTextByStructForWinApi();
	};

}

#endif // !JSON_H
