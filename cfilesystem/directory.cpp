#include "directory.hpp"
using cyh::cfilesystem::FileInfo;
using cyh::cfilesystem::File;
using cyh::cfilesystem::Directory;

text FileInfo::ToXmlStr() {
	Xml xml;
	xml.Tag = "file";
	xml.Data = FullPath;
	xml.AddAttribute("time", LastWriteTime.ToText("%Y%M%D%h%m%s"));
	return xml.ToString();
}

bool File::_exist(text _path) {
	return fs::exists(_path.ToStr());
}
void File::_getfi(text _path, FileInfo& _fi) {
	if (_exist(_path)) {
		_readPath(_path, _fi);
		_fi.LastWriteTime = TU::Time::LastWriteTime(_path);
	}
}
void File::_getfi(fs::directory_entry& file, FileInfo& _fi) {
	string path = Convert::ToNarrowStr(file.path().wstring());
	if (_exist(path)) {
		_readPath(path, _fi);
		fs::file_time_type ftt = file.last_write_time();
		_fi.LastWriteTime = TU::Time::ToDateTime(ftt);
		_fi.Size = file.file_size();
	}
}
void File::_readPath(text fullPath, FileInfo& _fi) {
	_fi.FullPath = fullPath;
	std::size_t iFind = fullPath.ToStr().find_last_of("/\\");
	_fi.Path = fullPath.SubString(0, iFind);
	text fName = fullPath.SubString(iFind + 1);
	std::size_t iPoint = fName.LastIndexOf(".");
	if (iPoint < 1) {
		_fi.FileName = fName;
		_fi.ExtName = "";
	}
	else {
		_fi.FileName = fName.SubString(0, iPoint);
		_fi.ExtName = fName.SubString(iPoint + 1);
	}
}
void File::ReadAllFileList(text path, vector<text>& vOut) {
	try {
		for (const auto f : fs::recursive_directory_iterator(path.ToWStr())) {
			vOut.push_back(f.path().wstring());
		}
	}
	catch (std::exception& anyException) {
		cout << anyException.what();
	}
}
void File::ReadAllFileInfo(text path, vector<FileInfo>& vOut) {
	try {
		for (auto f : fs::recursive_directory_iterator(path.ToWStr())) {
			FileInfo fi;
			_getfi(f, fi);
			vOut.push_back(fi);
		}
	}
	catch (std::exception& anyException) {
		cout << anyException.what();
	}
}
void File::ReadFileByte(std::vector<char>& buffer, text path) {
	try {
		std::ifstream input(path.ToStr(), std::ios::binary);
		input.seekg(0, std::ios::end);
		size_t length = input.tellg();
		input.seekg(0, std::ios::beg);
		buffer.reserve(length);
		std::copy(std::istreambuf_iterator<char>(input),
			std::istreambuf_iterator<char>(),
			std::back_inserter(buffer));
	}
	catch (std::exception& anyException) {
		cout << anyException.what();
	}
}
void File::ShowFileInfo(FileInfo fi) {
	std::cout
		<< "File: " << fi.FullPath.ToStr()
		<< "; Last write: " << fi.LastWriteTime.ToText("%Y/%M/%D %h:%m:%s").ToStr()
		<< endl;
}

void File::WriteAllText(text path, text& txt) {
	std::ofstream writer(path.ToStr());
	writer << txt;
	writer.close();
}
void File::WriteAllString(text path, std::string& txt) {
	std::ofstream writer(path.ToStr());
	writer << txt;
	writer.close();
}
text File::ReadAllText(text path) {
	text buffer = "";
	std::ifstream reader(path.ToStr(),std::ios::in);
	if (!reader.is_open()) {
		return buffer;
	}
	std::stringstream ss;
	ss << reader.rdbuf();
	buffer = ss.str();
	reader.close();
	return buffer;
}
std::vector<text> File::GetAllFileList(text path) {
	std::vector<text> listFI;
	File::ReadAllFileList(path, listFI);
	return listFI;
}
std::vector<FileInfo> File::GetAllFileInfo(text path) {
	std::vector<FileInfo> listFI;
	File::ReadAllFileInfo(path, listFI);
	return listFI;
}

void Directory::SetPath(text path) {
	_path = path;
}
void Directory::ShowFileList() {
	try {
		for (auto f : fs::recursive_directory_iterator(_path.ToStr())) {
			cout << f.path().string() << endl;
		}
	}
	catch (std::exception& anyException) {
		cout << anyException.what();
	}
}
void Directory::LoadFileInfo() {
	try {
		for (auto f : fs::recursive_directory_iterator(_path.ToStr())) {
			FileInfo fi;
			File::_getfi(f, fi);
			FileList.Add(fi);
		}
	}
	catch (std::exception& anyException) {
		cout << anyException.what();
	}
}
void Directory::LogFileInfo(text logFile) {
	std::ofstream log(logFile.ToStr());
	for (auto fi : FileList) {
		log << fi.ToXmlStr().ToStr();
		log << "\n";
	}
	log.close();
}
void Directory::ClearFileInfo() {
	FileList.Clear();
}

