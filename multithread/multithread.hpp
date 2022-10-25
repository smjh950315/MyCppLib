#pragma once
#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H
#include <Windows.h>
#include <synchapi.h>
#include <thread>
#include <vector>
#include <iostream>
#include <ppl.h>
#include "taskControl.hpp"
using std::cout;
using std::endl;
namespace cyh::multithread {
	template<class T>
	class MtTaskMgr;
	class Task {
	private:
		int* thMax = nullptr;
		int* thUsed = nullptr;
		int* finTask = nullptr;
		bool* waitAll = nullptr;
		bool* showMsg = nullptr;
		bool* flagUpdate = nullptr;
		inline void _task_start_dsp();
		inline void _task_end_dsp();
		void _run_with_msg();
		void _run_without_msg();
		friend class MtTaskMgr<Task>;
	public:
		int TaskId = 0;
		std::thread* th = nullptr;
		Task() {}
		~Task() {}
		void ReadContrlFlags(TaskCtrlFlag& flags);
		void RemoveFlags();
		void ThreadStateNow();
		void Launch();
		virtual void ToDoList() {}
	};

	template<class T>
	class MtTaskMgr {
	private:
		friend class Task;		
		int used_thread = 0;
		int finished_task = 0;
		int task_count = 0;
		bool flags_is_update = false;
				
		int max_thread = 0;
		bool console_input = false;
		bool console_show_state = false;
		bool wait_all_task = true;
		
		void _read_config(MtConfig& mtcfg) {
			max_thread = mtcfg.MAX_THREAD;
			console_input = mtcfg.CONSOLE_INPUT;			
			console_show_state = mtcfg.CONSOLE_SHOW_STATE;
			wait_all_task = mtcfg.WAIT_ALL;
		} 
		void _set_task_state(T& t) {
			t.ReadContrlFlags(ctrl_flags);
		}
		void _set_ctrl_flags() {
			ctrl_flags.finTask = &finished_task;
			ctrl_flags.showMsg = &console_show_state;
			ctrl_flags.waitAll = &wait_all_task;
			ctrl_flags.thMax = &max_thread;
			ctrl_flags.thUsed = &used_thread;
			ctrl_flags.flagUpdate = &flags_is_update;
		}
		bool _valid(T& t) {
			if (!(&t)) {
				return false;
			}
		}
	public:
		TaskCtrlFlag ctrl_flags;
		std::vector<T> Tasks;
		MtTaskMgr() {  }
		MtTaskMgr(int max_thread) {  }
		MtTaskMgr(MtConfig config) { _read_config(config); }
		void AddTask(T& t) {
			Tasks.push_back(t);
			task_count++;
		}
		void AddTask(std::vector<T>& tasks) {
			Tasks.insert(Tasks.end(), tasks.begin(), tasks.end());
			task_count+=tasks.size();
		}
		void RunTask() {
			for (auto t : Tasks) {
				_set_task_state(t);
				try {
					std::thread th(&T::Launch, t);
					th.detach();
				}
				catch (std::exception& any) {
					cout << any.what();
					return;
				}				
			}
			if (wait_all_task) {
				while (finished_task != task_count) {
					Sleep(30);
				}
			}
		}
		~MtTaskMgr() { Tasks.clear(); }
	};
}

#endif // !MULTI_THREAD_H

