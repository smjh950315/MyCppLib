#include "winsockapi.hpp"
#include "../winapi.hpp"
using WinSocketApi = cyh::winapi::web::WinSocketApi;
using WndApi = cyh::winapi::wnd::WndApi;

int WinSocketApi::wsa_startup() {
	return WSAStartup(m_wVersionRequested, &m_wsaData);
}
int WinSocketApi::get_addr_info(bool is_client) {
	ZeroMemory(&hints, sizeof(hints));
	if (!is_client) {
		hints.ai_family = IpVersion;
	}
	else {
		hints.ai_family = AF_UNSPEC;
	}
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (!is_client) {
		hints.ai_flags = AI_PASSIVE;
	}
	return getaddrinfo(NULL, Port, &hints, &result);
}
int WinSocketApi::socket_initialization() {
	m_socket = socket(IpVersion, Protocol, 0);
	return m_socket;
}
int WinSocketApi::set_socket_option() {
	return setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&OptVal, sizeof(OptVal));
}
void WinSocketApi::set_ip_version(unsigned _version) {
	if (_version == 4) {
		IpVersion = AF_INET;
	}
	else if (_version == 6) {
		IpVersion = AF_INET6;
	}
}
void WinSocketApi::set_transmit_protocol(text _protocol) {
	if (_protocol == "UDP") {
		Protocol = SOCK_DGRAM;
	}
}
void WinSocketApi::err_msg() {
#ifdef _WINDOWS
	if (HasHWnd) {
		WndApi::ShowMsgBox(hWnd, "Error", "WSA_Error!");
	}
#else
	cout << "err!" << endl;
#endif // _WINDOWS
}
void WinSocketApi::err_msg(text msg) {
#ifdef _WINDOWS
	if (HasHWnd) {
		WndApi::ShowMsgBox(hWnd, "Error", msg);
	}
#else
	cout << (const char*)msg << endl;
#endif // _WINDOWS
}
void WinSocketApi::SetRequestedVersion(unsigned _primary, unsigned _secondary) {
	m_wVersionRequested = MAKEWORD(_primary, _secondary);
}
void WinSocketApi::Startup() {
	if (!wsa_startup()) {
		err_msg("failed when start wsa!");
		return;
	}
	if (!get_addr_info(IsClient)) {
		err_msg("failed when fet addr info!");
		WSACleanup();
		return;
	}
	if (socket_initialization() == INVALID_SOCKET) {
		err_msg("failed when socket initailize!");
		return;
	}
	if (set_socket_option() == INVALID_SOCKET) {
		err_msg("failed when setup socket!");
	}
}
void WinSocketApi::Clear() {
	freeaddrinfo(result);
}