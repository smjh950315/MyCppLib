#include "json.hpp"
using cyh::data::Json;

std::vector<text> Json::split(text t) {
	int cbStart = 0;
	int sbStart = 0;
	vector<text> ts;
	text temp = "";
	size_t i = 0;
	size_t len = t.Length;
	for (; i < len; i++) {
		auto c = t[i];
		if (c == L'}')
		{
			cbStart--;
		}
		if (c == L'{')
		{
			cbStart++;
		}
		if (c == L']')
		{
			sbStart--;
		}
		if (c == L'[')
		{
			sbStart++;
		}
		if (c == L',' && cbStart == 0 && sbStart == 0)
		{
			ts.push_back(temp);
			temp = L"";
		}
		else
		{
			temp += c;
		}
		if (i == len - 1)
		{
			ts.push_back(temp);
		}
	}
	return ts;
}
KeyValuePair Json::read_attr(text t) {
	text temp = "";
	KeyValuePair attr;
	bool hasKey = false;
	size_t len = t.Length;
	for (size_t i = 0; i < len; i++) {

		auto c = t[i];
		if (c == L':' && !hasKey)
		{
			if (temp.StartWith("\""))
			{
				temp = temp.SubString(1);
			}
			if (temp.EndWith("\""))
			{
				temp = temp.SubString(0, temp.Length - 1);
			}
			attr.Key = temp;
			hasKey = true;
			temp = "";
		}
		else
		{
			temp += c;
		}
		if (i == len - 1)
		{
			if (temp.StartWith("\""))
			{
				temp = temp.SubString(1);
			}
			if (temp.EndWith("\""))
			{
				temp = temp.SubString(0, temp.Length - 1);
			}
			attr.Value = temp;
		}
	}
	return attr;
}
void Json::process(text t) {
	if (t.StartWith("[") && t.EndWith("]")) {
		t = t.GetContentEnvloped("[", "]");
		process(t);
	}
	else if (t.StartWith(L"{") && t.EndWith(L"}")) {
		vector<text> txts = t.GetContentEnvloped("{", "}");
		if (txts.size() == 0) { return; }
		else {
			size_t txtsCount = txts.size();
			for (size_t i = 0; i < txtsCount; i++) {
				if (child == nullptr) {
					child = new Json(this, nullptr);
					first = child;
				}
				else {
					child->next = new Json(this, child);
					child = child->next;
				}
				child->ReadFromText(txts[i]);
			}
		}
	}
	else {
		vector<text> attrs = split(t);
		size_t cItem = attrs.size();
		if (cItem == 0) {
			return;
		}
		if (cItem == 1) {
			KeyValuePair attr = read_attr(attrs[0]);
			if (attr.Key.Length != 0)
			{
				Attributes.push_back(attr);
				process(attr.Value);
			}
		}
		else {
			for (auto attr : attrs) {
				process(attr);
			}
		}
	}
}
void Json::start_read() {
	check_valid();
	if (!IsValidJson) { return; }
	process(rawStr);
}
void Json::check_valid() {
	if (rawStr.Length == 0) { return; }
	if (rawStr.CountOf("[") != rawStr.CountOf("]")) { return; }
	if (rawStr.CountOf("{") != rawStr.CountOf("}")) { return; }
	if (rawStr.StartWith("[") && !rawStr.EndWith("]")) { return; }
	if (rawStr.StartWith("{") && !rawStr.EndWith("}")) { return; }
	if (rawStr.FirstIndexOf("]") < rawStr.FirstIndexOf("[")) { return; }
	if (rawStr.FirstIndexOf("}") < rawStr.FirstIndexOf("{")) { return; }
	if (rawStr.LastIndexOf("]") < rawStr.LastIndexOf("[")) { return; }
	if (rawStr.LastIndexOf("}") < rawStr.LastIndexOf("{")) { return; }
	IsValidJson = true;
}
bool Json::is_root() {
	return parent == nullptr;
}
text Json::to_text(text interval, size_t tab_space) {
	text t = "";
	text space_tab = text(" ", tab_space);
	Json* temp = first;
	if (temp != nullptr) {
		t += ClBrStart + interval + space_tab;
		t += temp->to_text(interval, tab_space);
		while (temp->next != nullptr) {
			t += Comma + interval + space_tab;
			temp = temp->next;
			t += temp->to_text(interval, tab_space);
		}
		t += interval + ClBrEnd;
	}
	size_t attrCount = Attributes.size();
	if (attrCount != 0) {
		if (t.Length > 0) {
			t += Comma + interval + space_tab;
		}
		t += ClBrStart + interval + space_tab;
		for (size_t i = 0; i < attrCount - 1; i++) {
			t += space_tab + Attributes[i].ToString() + Comma + interval + space_tab;
		}
		t += space_tab + Attributes[attrCount - 1].ToString() + interval + space_tab + ClBrEnd;
	}
	return t;
}
text Json::to_raw_json_text() {
	text t = "";
	if (is_root()) {
		t += "[";
	}
	t += to_text("", 0);
	if (is_root()) {
		t += "]";
	}
	return t;
}
Json::Json(Json* pre) {
	prev = pre;
}
Json::Json(Json* prnt, Json* pre) {
	parent = prnt;
	prev = pre;
}
Json::~Json() {
	if (first != nullptr) {
		while (first->next != nullptr) {
			first = first->next;
			delete first->prev;
		}
		delete first;
	}
}
void Json::ReadFromText(text& t) {
	rawStr = t;
	start_read();
}
text Json::ToTextForm() {
	return to_raw_json_text();
}
text Json::ToTextByStruct() {
	return to_text("\n", 2);
}
text Json::ToTextByStructForWinApi() {
	return to_text("\r\n", 2);
}

