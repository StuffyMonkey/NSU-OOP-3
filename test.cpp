#include <iostream>
#include"Container.h"
#include"Object.h"

void test() {
	Container<std::string> messages;
	// initial tak list
	Container<Task*> tasks{
		new BinaryOperationTask("addition1", 7.2, 3.0, '+'),
        new BinaryOperationTask("addition2", -9.8, 4.0, '+'),
        new BinaryOperationTask("addition3", 1.5, 9.0, '+'),
		new BinaryOperationTask("substraction1", 3.0, 4.0, '-'),
        new BinaryOperationTask("substraction2", 5.7, 9.0, '-'),
        new BinaryOperationTask("substraction3", 112.0, 9.0, '-'),
		new BinaryOperationTask("multiplication1", 12.0, 23.0, '*'),
        new BinaryOperationTask("multiplication2", 11.0, 30.0, '*'),
        new BinaryOperationTask("multiplication3", 1.5, 2.5, '*'),
		new BinaryOperationTask("division1", 5.0, 20.0, '/'),
		new BinaryOperationTask("division2", 5.0, 40.0, '/'),
		new BinaryOperationTask("division3", 155.0, 5.5, '/')
	};

	
	Task* task_to_run = new BinaryOperationTask("division4", 20.0, 4, '/');
	tasks.addFirst(task_to_run);
	// will throw exception because task was completed before
	// tasks.addLast(new AddTask("AddTaskTask", tasks, task_to_run));

	// all possible classes are involved
	tasks.addFirst(new CountTaskTask("CountTaskTask1", tasks));
	tasks.addLast(new GetNumberOfObjects("OverallObjectInfo"));
    tasks.addLast(new CountTaskTask("CountTaskTask2", tasks));
	tasks.addLast(new AddTask("AddTaskTask", tasks, new BinaryOperationTask("division5", 11.0, 5.5, '/')));

	// check list besore adding to messages
	for (auto it = tasks.begin(); it != tasks.end(); it++)
	{
		Task* task = *it;
		std::cout << task->toString() << std::endl;
	}

	std::cout << std::endl;

    // loop over tasks
	for (auto it = tasks.begin(); it != tasks.end(); it++)
	{
		Task* task = *it;
		task->run();
		messages.addLast(task->toString());
	}

	for (auto msg = messages.begin(); msg != messages.end(); msg++)
	{
		std::cout << *msg << std::endl;
	}

	messages.clear();
	tasks.clear();
}

int main() {
	test();
	return 0;
}