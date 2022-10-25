#pragma once
#ifndef WEB_DATA_MODIFY_H
#define WEB_DATA_MODIFY_H
#include"header.hpp"
using cyh::data::text;
namespace cyh::web {
	class Modify {
	public:
		static void PureJsonString(text& content_to_post);
	};
}

#endif // !WEB_DATA_MODIFY_H
