#pragma once
#ifndef CYH_WIN_SOCKET
#define CYH_WIN_SOCKET
#include "../header.hpp"
#include <ws2tcpip.h>

namespace cyh::winapi::web {
	class WinSocketApi {
	private:
		WORD m_wVersionRequested;
		WSADATA m_wsaData;
		int wsa_startup();
		int get_addr_info(bool is_client);
		int socket_initialization();
		int set_socket_option();
		void set_ip_version(unsigned _version);
		void set_transmit_protocol(text _protocol);
		void err_msg();
		void err_msg(text msg);
	public:
		struct addrinfo* result = nullptr, * ptr = nullptr, hints;
		const char* Port = "80";
		bool IsClient = true;
		bool HasHWnd = false;
		unsigned IpVersion = AF_INET;
		long Protocol = SOCK_STREAM;
		HWND hWnd;	
		DWORD OptVal = 1; //0=off, 1=on
		SOCKET m_socket;

		void SetRequestedVersion(unsigned _primary,unsigned _secondary);
		void Startup();
		void Clear();
	};
}


#endif // !CYH_WIN_SOCKET
