#include <MySingleton.h>
#include <thread>
#include <vector>
#include <MyThreadPool.h>

void printMessage(int idx) {
	std::cout << "thread:" << idx << std::endl;
	MySingleton::getInstance().doSomething();
}

int main() {
	std::cout << "Main thread started." << std::endl;

	const size_t threadNums = 10;

	MyThreadPool threadPool(threadNums);
	for (size_t i = 0; i < threadNums; ++i) {
		auto result = threadPool.enqueue([i]() {
			printMessage(i);
			});
	}
	std::cout << "Main thread finished." << std::endl;

	return 0;
}