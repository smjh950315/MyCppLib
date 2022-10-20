#include "xml.hpp"
using cyh::data::Xml;

text Xml::get_tag_str(text& raw, text tagName, size_t* endIndex) {
	text tagStart = "<";
	text tagEnd = "</";
	tagStart += tagName;	
	tagEnd += tagName;
	tagEnd += ">";
	text temp = raw.GetContentEnvloped(tagStart, tagEnd);
	return temp;
}
text Xml::get_tag_str(text& raw, text tagName) {
	size_t endIndex = 0;
	return get_tag_str(raw, tagName, &endIndex);
}
text Xml::get_tag_start_str(text tagName) {
	text tagStart = "<";
	tagStart += tagName;
	tagStart += " ";
	return tagStart;
}
text Xml::get_tag_end_str(text tagName) {
	text tagEnd = "</";
	tagEnd += tagName;
	tagEnd += ">";
	return tagEnd;
}
text Xml::remove_lead_space(text t) {
	size_t iSpaceStart = 0;
	for (size_t i = 0; i < t.Length; i++) {
		if (t[i] != ' ') {
			iSpaceStart = i;
			break;
		}
	}
	if (iSpaceStart == 0 && t[0] != ' ') {
		return t;
	}
	if (iSpaceStart >= t.Length) {
		return t;
	}
	return t.SubString(iSpaceStart + 1);
}
void Xml::start_read() {

	rawStr.ReplaceAll("\n", "");
	process(rawStr);

}
void Xml::read_single(text& txt) {
	Tag = txt.Between("<", " ");
	size_t iTEnd = txt.EndIndexOf(Tag);
	text rawAttr = txt.Between(iTEnd, " ", ">");
	ReadAttributeStr(rawAttr);
	size_t IAEnd = txt.EndIndexOf(rawAttr);
	text afterAttr = txt.SubString(IAEnd);
	size_t countOfHead = afterAttr.CountOf("<" + Tag.ToStr());
	size_t countOfEnd = afterAttr.CountOf("</" + Tag.ToStr() + ">");
	Data = txt.Between(IAEnd, ">", "</" + Tag.ToStr() + ">");
}
void Xml::read_attri_from_str(text txt) {
	txt.Trim();
	vector<text> ts = txt.Splits("=\"");
	size_t len = ts.size();
	size_t i = 0;
	vector<text> keys;
	vector<text> values;
	if (!len) { return; }
	keys.push_back(ts[0]);	i++;
	for (; i < len - 1; i++) {
		vector<text> tmp = ts[i].Splits("\"");
		values.push_back(tmp[0]);
		keys.push_back(tmp[1]);
	}
	values.push_back(ts[len - 1]);
	size_t cAttr = keys.size();
	if (!cAttr) { return; }
	if (cAttr != values.size()) { return; }
	for (int k = 0; k < cAttr; k++) {
		Attributes.push_back(KeyValuePair(keys[k], values[k]));
	}
}
void Xml::get_tag_from_process_text(text& txt) {
	size_t len = txt.Length;
	for (size_t i = 0; i < len; i++) {
		wchar_t c = txt[i];
		if (c == L' ' ||c == L'>') {
			break;
		}
		else {
			Tag += c;
		}
	}
}
void Xml::get_attri_from_process_text(text& txt) {
	if (Tag.Length == 0) { return; }
	size_t iTag = txt.FirstIndexOf(Tag);
	if (iTag < 0 || iTag==std::string::npos) { return; }
	text attrStr = txt.Between(Tag+(text)" ", ">");
	read_attri_from_str(attrStr);
}
KeyValuePair Xml::GetAttribute(text _name) {
	for (auto& a : Attributes) {
		if (a.Key.ToWStr() == _name.ToWStr()) {
			return a;
		}
	}
	return KeyValuePair("", "");
}
text Xml::ToString() {
	text temp = "<" + Tag.ToStr();
	for (auto& a : Attributes) {
		text v_temp = a.Value;
		v_temp.AddWrapping("\"");
		temp += " ";
		temp += a.Key + "=" + v_temp;
	}
	temp += ">";
	temp += Data;
	temp += "</" + Tag.ToStr() + ">";
	return temp;
}
void Xml::AddAttribute(KeyValuePair attr) {
	Attributes.push_back(attr);
}
void Xml::AddAttribute(text key, text value) {
	Attributes.push_back(KeyValuePair(key, value));
}
void Xml::ReadAttributeStr(text txt) {
	txt.Trim();
	vector<text> ts = txt.Splits("=\"");
	size_t len = ts.size();
	size_t i = 0;
	vector<text> keys;
	vector<text> values;
	if (!len) { return; }
	keys.push_back(ts[0]);	i++;
	for (; i < len - 1; i++) {
		vector<text> tmp = ts[i].Splits("\"");
		values.push_back(tmp[0]);
		keys.push_back(tmp[1]);
	}
	values.push_back(ts[len - 1]);
	size_t cAttr = keys.size();
	if (cAttr != values.size()) { return; }
	for (int k = 0; k < cAttr; k++) {
		Attributes.push_back(KeyValuePair(keys[i], values[i]));
	}
}
void Xml::ReadFromText(text& _txt) {
	rawStr = _txt;
	start_read();
}
void Xml::process(text t) {
	text trimT = remove_lead_space(t);
	if (trimT.StartWith("<")) {
		vector<text> xmls = trimT.GetContentEnvloped("<", "</");
		size_t len = xmls.size();
		if (len == 0) {
			return;
		}
		else {
			for (size_t i = 0; i < len; i++) {
				if (xmls[i].Length == 0) { continue; }
				if (child == nullptr) {
					child = new Xml(this, nullptr);
					first = child;
				}
				else {
					child->next = new Xml(this, child);
					child = child->next;
				}
				child->process(xmls[i]);
			}
		}
	}
	else {
		size_t iAttriEnd = trimT.FirstIndexOf(">");
		text data = trimT.SubString(iAttriEnd + 1);
		get_tag_from_process_text(trimT);
		get_attri_from_process_text(trimT);
		if (data.Length == 0) { return; }
		vector<text> xmls = data.GetContentEnvloped("<", "</");
		size_t len = xmls.size();
		if (len == 0) {
			Data = data;
		}
		else {
			for (auto x : xmls) {
				process(x);
			}
		}
	}
}

