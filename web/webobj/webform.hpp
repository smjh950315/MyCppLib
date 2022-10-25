#pragma once
#ifndef WEB_FORM_H
#define WEB_FORM_H
#include "../header.hpp"
#include "../../struct/basic.hpp"
#include "../../data/keyvaluepair.hpp"
#include "../../data/list.hpp"
using cyh::data::text;
using cyh::data::List;
using cyh::data::KeyValuePair;

namespace cyh::web {

	struct FormData : public KeyValuePair {
		FormData(text _title, text _data) {
			SetValue(_title, _data);
		}
	};
	class WebForm {
	public:	
		List<FormData> Data;
		WebForm();
		void Add(FormData _data) {
			Data.Add(_data);
		}
		void Add(text _title, text _data) {
			Data.Add(FormData(_title, _data));

		}

	};

}


#endif // !FORM_H
