/*
	���������ã�
		1>.�޸��˳�ʼ��������
		2>.������STL֧��
		3>.��������־·�������ơ���ʽ��Ĭ�ϲ������־

	���ߣ�Ĭ�Ͽ����� STL ����֧�֡��Ѿ�֧�֣�
			std::vector	std::list			std::deque	std::queue
			std::stack	std::priority_queue	std::set	std::multiset
			std::pair	std::bitset			std::map	std::multimap
	�����Ҫ������
			std::array	std::unordered_map	std::unordered_set
		�뿪������� #define ELPP_LOG_STD_ARRAY �Ⱥ궨��

	ֱ������Զ���ṹ�壬��Ҫ���� operator<< ��
	���ֱ���������������������������ܳ���100��
	�����޸� easyloggingpp.h --> (base::consts::kMaxLogPerContainer) �е����ֵ���������顣
	
*/

#pragma once
#include <string>

#define ELPP_STL_LOGGING
///#define ELPP_LOG_STD_ARRAY
///#define ELPP_LOG_UNORDERED_MAP
///#define ELPP_LOG_UNORDERED_SET
#include "easylogging++.h"

#define _Log_Start_ INITIALIZE_EASYLOGGINGPP

class logutil {

public:
	logutil();
	~logutil();

	void setPathFormat(bool detach = false, std::string path = "log", std::string format = "[%datetime | %level | %fbase:%line | %func] %msg");

};
logutil::logutil(){}
logutil::~logutil(){}

void logutil::setPathFormat(bool detach,std::string path,std::string format) {

	el::Configurations defaultConf;

	//������־����ΪĬ��ֵ -- ��������Զ���Ӧ�Ĳ�����������
	defaultConf.setToDefault();

	//������־�����ʽ
	defaultConf.set(el::Level::Global, el::ConfigurationType::Format, format);

	//������־���·��
	if (detach) {
		defaultConf.set(el::Level::Debug, el::ConfigurationType::Filename, path + "\\debug_log_%datetime{%Y%M%d}.log");
		defaultConf.set(el::Level::Error, el::ConfigurationType::Filename, path + "\\error_log_%datetime{%Y%M%d}.log");
		defaultConf.set(el::Level::Warning, el::ConfigurationType::Filename, path + "\\warning_log_%datetime{%Y%M%d}.log");
		defaultConf.set(el::Level::Info, el::ConfigurationType::Filename, path + "\\info_log_%datetime{%Y%M%d}.log");
	} else {
		defaultConf.set(el::Level::Global, el::ConfigurationType::Filename, path + "\\mylog_%datetime{%Y%M%d}.log");
	}
	

	//����ע����־��ʽ
	el::Loggers::reconfigureLogger("default", defaultConf);
}

/*
	// Ĭ�Ϲ���
	el::Configurations defaultConf;
	// ��־��������ȫ������Ϊ��ʼֵ
	defaultConf.setToDefault();
	// �����������
	void Configurations::set(Level level, ConfigurationType configurationType, const std::string& value)

	// �������ļ���ʽ��ʼ��
	el::Configurations conf("/path/to/my-conf.conf");


	// ע�� default ��Ч
	el::Loggers::reconfigureLogger("default", conf);

	// ��� xxx ��־(����Ҫ��õ���־id�����id�����ڣ� �Զ�������־)
	el::Logger* log = el::Loggers::getLogger("xxx");
	
	// ���ӱ�� NewLineForContainer��STL ������ÿ��Ԫ��һ��
	el::Loggers::addFlag(el::LoggingFlag::NewLineForContainer);
	// �Ƴ����
	el::Loggers::removeFlag(el::LoggingFlag::NewLineForContainer);

	// ������־
	LOG_IF(condition, LEVEL)
	LOG_IF(1 == 1, INFO) << "1 is equal to 1";

	// żȻ��־
	// ÿ N �μ�¼һ����־ every
	LOG_EVERY_N(n, LEVEL)
	//  N �κ��¼һ����־ after
	LOG_AFTER_N(n, LEVEL)
	// �ܹ���¼ N ��		  times
	LOG_N_TIMES(n, LEVEL)

	// CHECK����־, ������������¼ FATAL ������־
	CHECK(condition)
	CHECK_EQ(a, b)

	// printf�����־��¼
	el::Logger* log = el::Loggers::getLogger("default");
	vector<int> vec;
	log->->info("My first ultimate log message %v %v %v", 123, 222, vec);
*/