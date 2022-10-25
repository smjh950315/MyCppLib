#pragma once
#ifndef TASK_CTRL_H
#define TASK_CTRL_H

namespace cyh::multithread {
	
	struct TaskCtrlFlag {
		int* thMax = nullptr;
		int* thUsed = nullptr;
		int* finTask = nullptr;
		bool* showMsg = nullptr;
		bool* waitAll = nullptr;		
		bool* flagUpdate = nullptr;
	};
	struct MtConfig {
		int MAX_THREAD = 0;		
		bool CONSOLE_INPUT = false;
		bool CONSOLE_SHOW_STATE = false;
		bool WAIT_ALL = true;
	};

}

#endif