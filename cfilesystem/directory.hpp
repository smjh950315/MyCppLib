#pragma once
#ifndef FILESYS_H
#define FILESYS_H
#include "../includelist.h"
#include "../data/datetime.hpp"
#include "../data/convert.hpp"
#include "../data/xml.hpp"
#include "../data/list.hpp"
#include "../time/time.hpp"
using cyh::Convert;
using std::wstring;
using std::wofstream;
using cyh::data::text;
using cyh::data::DateTime;
using cyh::data::Xml;
using cyh::data::List;
namespace TU = cyh::Time;
namespace fs = ghc::filesystem;
using TU::Time;

namespace cyh::cfilesystem {
	class Directory;
	struct FileInfo {
		FileInfo* prev = nullptr;
		FileInfo* next = nullptr;
		text FullPath = "";
		text Path = "";
		text FileName = "";
		text ExtName = "";
		DateTime LastWriteTime;
		size_t Size = 0;
		FileInfo() {}
		text ToXmlStr();
	};
	class File {
	private:
		friend class Directory;
		static bool _exist(text _path);
		static void _getfi(text _path, FileInfo& _fi);
		static void _getfi(fs::directory_entry& file, FileInfo& _fi);
		static void _readPath(text _fullPath, FileInfo& _fi);

	public:
		static void ReadAllFileList(text path, vector<text>& _outputArray);
		static void ReadAllFileInfo(text path, vector<FileInfo>& _outputArray);
		static void ShowFileInfo(FileInfo fi);
		static void ReadFileByte(std::vector<char>& buffer, text path);
		
		static void WriteAllText(text path, text& _text);
		static void WriteAllString(text path, std::string& _text);
		static text ReadAllText(text path);

		static std::vector<text> GetAllFileList(text path);
		static std::vector<FileInfo> GetAllFileInfo(text path);


	};
	class Directory {
	private:
		text _path;
	public:
		List<FileInfo> FileList;
		Directory(){}
		Directory(text path){ SetPath(path); }
		~Directory(){
			if (FileList.Length!=0) {
				ClearFileInfo();
			}
		}
		text Path() { return _path; }
		void SetPath(text path);
		void ShowFileList();
		void LoadFileInfo();
		void LogFileInfo(text logFile);
		void ClearFileInfo();
	};
}
#endif // !DIRECTORY_H
