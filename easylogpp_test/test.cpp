#include <iostream>
#include <string>

#include "logutil.hpp"
using namespace std;

_Log_Start_

struct person  {
	string name;
	int age;
};
ostream& operator<<(ostream &out, const person &p) {
	out << "(" 
		<< "name:"<< p.name <<"," 
		<< "age:" << p.age <<")";
	return out;
}

int main()
{
	logutil().setPathFormat(true);

	std::vector<int> vn = { 1,2,3 };
	LOG(INFO) << vn;

	LOG(DEBUG) << "debug string test";

	vector<person> vp = { { "a",19 } ,{ "b",20 },{ "c",21 } };

	LOG(WARNING)<< "warning string test";

	/// ���ӱ�� NewLineForContainer
	//el::Loggers::addFlag(el::LoggingFlag::NewLineForContainer);
	LOG(INFO) << "new line for container: ";
	LOG(INFO) << vp;
	//el::Loggers::removeFlag(el::LoggingFlag::NewLineForContainer);
	/// ɾ����� NewLineForContainer

	// żȻ��־
	for (int i = 1; i <= 100; ++i) {
		LOG_N_TIMES(3, INFO) << "Log only 3 times; " << i;
	}

	system("pause");
	return 0;
}