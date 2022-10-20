#include "cmdinput.hpp"
using namespace cyh::consolecmd;

CmdObj::CmdObj(int flag, std::string ctx) {
	Flag = flag;
	Command = ctx;
}

CmdFunc::CmdFunc() {}
void CmdFunc::Exit() {
	loop = 0;
}
void CmdFunc::Clear() {
	std::cout << "\x1B[2J\x1B[H";
}

void CmdLoop::_wait_input() {
	std::string ctx = "";
	for (; loop;) {
		Sleep(20);
		getline(std::cin, ctx);
		for (auto& c : _cmd) {
			if (c.Command == ctx) {
				_launch_cmd(c.Flag);
				break;
			}
		}
	}
}
void CmdLoop::_launch_cmd(int flag) {
	switch (flag)
	{
	case 0:
		Exit();
		break;
	case 1:
		Clear();
		break;
	default:
		break;
	}
}
CmdLoop::CmdLoop() {}
void CmdLoop::Start() {
	_wait_input();
}

