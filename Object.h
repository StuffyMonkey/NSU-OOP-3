#pragma once
#include <string>
#include "Container.h"

class Object {
    public:
	    Object(){ ++numEntities; }
	    virtual ~Object(){ --numEntities; }

        virtual std::string toString() const = 0;

		int getNumEntities(){return numEntities;}
	private:
        inline static int numEntities = 0;
};

class Task: public virtual Object {
    public:
	    virtual void run() = 0;
	    virtual bool hasResult() const = 0;
	protected:
        bool isCompleted = false;
};

class Named: public virtual Object {
    public:
        Named(std::string name) : name(name) {}

        std::string getName() const{
            return name;
        }
    private:
        std::string const name;
};

class BinaryOperationTask: public Task, public Named {
    public:
	    BinaryOperationTask(std::string const& name, double left, double right, char operation_sign): 
			Named(name),
		    left(left),
		    right(right),
		    operation_sign(operation_sign) {}

		void run() override {
			if (isCompleted) throw std::runtime_error("The task was copleted before");
			switch (operation_sign)
			{
			case '+':
				result = left + right;
				break;
			case '-':
				result = left - right;
				break;
			case '/':
				result = left / right;
				break;
			case '*':
				result = left * right;
				break;
			default:
				throw std::runtime_error("Unknown binary operation recieved");
			}
			isCompleted = true;
		}

		std::string toString() const override{
			return Named::getName() + ": " + std::to_string(left) + ' ' + operation_sign + ' ' + std::to_string(right) + " = " +
                                            (isCompleted ? std::to_string(result) : "UNKNOWN") + ' ' +
                                            (isCompleted ? "DONE" : "IN_PROCESS");
		}

		bool hasResult() const override{return true;}
    private:
        double left;
        double right;
        char operation_sign;
		double result;
};

class AddTask: public Task, public Named {
	public:
		AddTask(std::string const& name, Container<Task*>& container, Task* const task): 
                    Named(name), container(container), task(task) {}

		void run() override {
			if (isCompleted) 
            	throw std::runtime_error("The task was completed before");

			container.addLast(task);
			isCompleted = true;
		}

		std::string toString() const override{
			return Named::getName() + ": " + "Add " + task->toString() + " to container ({})" +
											(isCompleted ? "DONE" : "IN_PROCESS");
		}

		bool hasResult() const override{return false;}
    private:
    	Container<Task*>& container;
	    Task* const task;
};

class CountObjectsTask: public Task, public Named {
	public:
		CountObjectsTask(std::string const& name, Container<Object*>& container): Named(name), container(container) {}

		void run() override{
			if (isCompleted) throw std::runtime_error("The task was copleted before");
			result = container.getLen();
		}

		std::string toString() const override{
			return Named::getName() + ": " + "Container has " + (isCompleted ? std::to_string(result) : "UNKNOWN") +  
										"objects (" + (isCompleted ? "DONE" : "IN_PROCESS") + ')';
		}

		bool hasResult() const override{return true;}
	private:
		Container<Object*>& container;
		int result;
};

class CountTaskTask: public Task, public Named {
	public:
		CountTaskTask(std::string const& name, Container<Task*>& container): Named(name), container(container) {}

		void run() override {
			for (auto it = container.begin(); it != container.end(); it++) {
				Task* task = *it;
				if (task->hasResult())
					result++; 
			}
			isCompleted = true;
		}

		std::string toString() const override {
			return Named::getName() + ": " + "Container has " + (isCompleted ? std::to_string(int(result)) : "UNKNOWN") +  
											" result task (" + (isCompleted ? "DONE" : "IN_PROCESS") + ')';
		}

		bool hasResult() const override{return true;}
	private:
		Container<Task*>& container;
		int result;
};

class ClearTask: public Task {
	public:
		Container<Object*>& container;

		ClearTask(Container<Object*>& container): container(container) {}

		void run() override { 
			container.clear(); 
		}

		bool hasResult() const override{return false;}
};

class GetNumberOfObjects: public Task, public Named {
	public:
		GetNumberOfObjects(std::string const& name): Named(name) {}

		void run() override {
			result = Object::getNumEntities();
			isCompleted = true;
		}

		std::string toString() const override{
			return Named::getName() + ": " + "Number of objects: " +
								(isCompleted ? std::to_string(int(result)) : "UNKNOWN") +
								" (" + (isCompleted ? "DONE" : "IN_PROCESS") + ')';
		}

		bool hasResult() const override{return true;}
	private:
		int result;
};
