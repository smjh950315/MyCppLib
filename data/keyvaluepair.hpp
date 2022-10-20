#pragma once
#ifndef KEY_VALUE_PAIR
#define KEY_VALUE_PAIR
#include "text.hpp"
using cyh::data::text;

namespace cyh::data {
	struct KeyValuePair {
		text Key;
		text Value; 
		void SetValue(text _key, text _val) {
			Key = _key;
			Value = _val;
		}
		KeyValuePair(){}
		KeyValuePair(text _key) { SetValue(_key, ""); }
		KeyValuePair(text _key, text _val) { SetValue(_key, _val); }
		text ToString() {
			text t= (text)"\"" + Key + (text)"\":\"" + Value + (text)"\"";
			return t;
		}
		text ToJsonString() {
			text t = (text)"\"" + Key + (text)"\":\"" + Value + (text)"\"";
			return t;
		}
		text ToWebFormString() {
			text t = (text)"\"" + Key + (text)"\":\"" + Value + (text)"\"";
			return t;
		}
	};
}
#endif // !KEY_VALUE_PAIR_H


