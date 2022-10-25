#include "modify.hpp"
using cyh::web::Modify;

void Modify::PureJsonString(text& content_to_post) {
	//std::string str = content_to_post;
	//std::string newStr = "";
	//for (auto& c : str) {
	//	if (c == ' ') { continue; }
	//	if (c == '\n') { continue; }
	//	if (c == '\r') { continue; }
	//	if (c == '\t') { continue; }
	//	newStr += c;
	//}
	//content_to_post = newStr;
	content_to_post.RemoveAll(' ');
	content_to_post.RemoveAll('\n');
	content_to_post.RemoveAll('\r');
	content_to_post.RemoveAll('\t');
}
