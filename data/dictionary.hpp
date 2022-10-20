#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "keyvaluepair.hpp"
#include <type_traits>
using cyh::data::text;
using cyh::data::KeyValuePair;
namespace cyh::data {

	class Dictionary {
	public:
		std::vector<KeyValuePair> KVPairs;
		Dictionary();
		void Add(text _key, text _val);
		void Add(KeyValuePair keyValuePair);

	};

}

#endif // !DICTIONARY_H



