多核心說明：
要使用多核心的類別繼承Task，並覆寫ToDoList方法
使用ThreadMgr管理

範例：
	要平行處理的 class:
		class ToDo : public Task{
			public:
				ToDo(Args...);
				void ToDoList() override {
					//...
				}
		}
	MtTaskMgr 初始化：
		MtTaskMgr<ToDo> thMgr(int 最大使用執行續);
	MtTaskMgr 加入任務：
		thMgr.AddTask(ToDo(Args...));
	MtTaskMgr 啟動：
		thMgr.RunTask();
	MtTaskMgr 其他功能：
		thMgr.ShowState(bool 是否顯示訊息)


