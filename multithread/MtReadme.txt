�h�֤߻����G
�n�ϥΦh�֤ߪ����O�~��Task�A���мgToDoList��k
�ϥ�ThreadMgr�޲z

�d�ҡG
	�n����B�z�� class:
		class ToDo : public Task{
			public:
				ToDo(Args...);
				void ToDoList() override {
					//...
				}
		}
	MtTaskMgr ��l�ơG
		MtTaskMgr<ToDo> thMgr(int �̤j�ϥΰ�����);
	MtTaskMgr �[�J���ȡG
		thMgr.AddTask(ToDo(Args...));
	MtTaskMgr �ҰʡG
		thMgr.RunTask();
	MtTaskMgr ��L�\��G
		thMgr.ShowState(bool �O�_��ܰT��)


