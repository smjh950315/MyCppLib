#pragma once
#include <Windows.h>
#include <synchapi.h>
#ifndef CONSOLE_CMD_H
#define CONSOLE_CMD_H
#include <iostream>
#include <string>
#include <vector>
namespace cyh::consolecmd {

	class CmdObj {
	public:
		int Flag;
		std::string Command = "";		
		CmdObj(int flag, std::string ctx);
	};
	class CmdFunc {
	public:
		bool loop = true;
		CmdFunc();
		void Exit();
		void Clear();
	};
	class CmdLoop :public CmdFunc {
	private:
		void _wait_input();
		void _launch_cmd(int flag);
	public:
		std::vector<CmdObj> _cmd{
			CmdObj(0,"exit"),
			CmdObj(1,"cls")
		};
		CmdLoop();
		void Start();
	};

}
#endif // !CONSOLE_CMD_H