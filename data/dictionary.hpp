#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "keyvaluepair.hpp"
#include "list.hpp"
#include <type_traits>
using cyh::data::text;
using cyh::data::KeyValuePair;
using cyh::data::List;
namespace cyh::data {

	template<typename key_type, typename val_type>
	class DictionaryT {
	public:
		List<KeyValuePairT<key_type, val_type>>KVPairs;
		DictionaryT() {}
		void Add(key_type _key, val_type _val) {
			KVPairs.Add(KeyValuePairT< key_type, val_type >(_key, _val));
		}
		void Add(KeyValuePairT<key_type, val_type> keyValuePair) {
			KVPairs.Add(keyValuePair);
		}
		val_type GetValueOf(key_type _key) {
			for (auto kv : KVPairs) {
				if (kv.Key == _key) {
					return kv.Value;
				}
			}
			return val_type{ 0 };
		}
	};


	class Dictionary {
	public:
		List<KeyValuePair> KVPairs;
		Dictionary() {}
		void Add(text _key, text _val) {
			KVPairs.Add(KeyValuePair(_key, _val));
		}
		void Add(KeyValuePair keyValuePair) {
			KVPairs.Add(keyValuePair);
		}
		text GetValueOf(text _key) {
			for (auto kv : KVPairs) {
				if (kv.Key == _key.ToWStr()) {
					return kv.Value;
				}
			}
			return text{ 0 };
		}
	};

}

#endif // !DICTIONARY_H



