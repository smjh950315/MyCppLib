#include "MultiThread.hpp"
#include "../Data/Number.hpp"
using cyh::MultiThread::Task;
using cyh::data::Number;
using std::cout;
using std::endl;
inline void Task::_task_start_dsp() {
	(*thUsed)++; 
	cout << "Task Start!, ";
	cout << "Thread(used / all) : "
		<< *thUsed << "/" << *thMax << endl;
}
inline void Task::_task_end_dsp() {
	(*finTask)++; 
	(*thUsed)--;
	cout << "Task End!, ";
	cout << "Thread(used / all) : "
		<< *thUsed << "/" << *thMax << endl;
}
void Task::_run_with_msg() {
	while ((*thUsed) >= (*thMax)) { Sleep(Number::EzRandInt(0, 5)); }
	_task_start_dsp();
	th = new std::thread(&Task::ToDoList, this);
	(*th).join(); 
	_task_end_dsp();
}
void Task::_run_without_msg() {
	while ((*thUsed) >= (*thMax)) { Sleep(Number::EzRandInt(0, 5)); }
	(*thUsed)++;
	th = new std::thread(&Task::ToDoList, this);
	(*th).join(); 
	(*finTask)++;
	(*thUsed)--;
}
void Task::ReadContrlFlags(TaskCtrlFlag& f) {
	thMax = f.thMax;
	thUsed = f.thUsed;
	finTask = f.finTask;
	waitAll = f.waitAll;
	showMsg = f.showMsg;
	flagUpdate = f.flagUpdate;
}
void Task::RemoveFlags() {

	delete th;
	th = nullptr;

	thMax = nullptr;
	thUsed = nullptr;
	finTask = nullptr;
	waitAll = nullptr;
	showMsg = nullptr;
	flagUpdate = nullptr;
}
void Task::ThreadStateNow() {
	cout << "Thread(used / all) : "
		<< *thUsed << "/" << *thMax << endl;
}
void Task::Launch() {
	if (*showMsg) {
		_run_with_msg();
	}
	else {
		_run_without_msg();
	}
	RemoveFlags();
}


