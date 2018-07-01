/*
	本工具作用：
		1>.修改了初始化宏名称
		2>.开启了STL支持
		3>.设置了日志路径、名称、格式，默认不拆分日志

	工具，默认开启了 STL 容器支持。已经支持：
			std::vector	std::list			std::deque	std::queue
			std::stack	std::priority_queue	std::set	std::multiset
			std::pair	std::bitset			std::map	std::multimap
	如果需要容器：
			std::array	std::unordered_map	std::unordered_set
		请开启下面的 #define ELPP_LOG_STD_ARRAY 等宏定义

	直接输出自定义结构体，需要重载 operator<< 。
	如果直接输出容器，容器的最大容量不能超过100。
	可以修改 easyloggingpp.h --> (base::consts::kMaxLogPerContainer) 中的这个值，但不建议。
	
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

	//设置日志参数为默认值 -- 在下面可以对相应的参数覆盖设置
	defaultConf.setToDefault();

	//设置日志输出格式
	defaultConf.set(el::Level::Global, el::ConfigurationType::Format, format);

	//设置日志输出路径
	if (detach) {
		defaultConf.set(el::Level::Debug, el::ConfigurationType::Filename, path + "\\debug_log_%datetime{%Y%M%d}.log");
		defaultConf.set(el::Level::Error, el::ConfigurationType::Filename, path + "\\error_log_%datetime{%Y%M%d}.log");
		defaultConf.set(el::Level::Warning, el::ConfigurationType::Filename, path + "\\warning_log_%datetime{%Y%M%d}.log");
		defaultConf.set(el::Level::Info, el::ConfigurationType::Filename, path + "\\info_log_%datetime{%Y%M%d}.log");
	} else {
		defaultConf.set(el::Level::Global, el::ConfigurationType::Filename, path + "\\mylog_%datetime{%Y%M%d}.log");
	}
	

	//重新注册日志格式
	el::Loggers::reconfigureLogger("default", defaultConf);
}

/*
	// 默认构造
	el::Configurations defaultConf;
	// 日志，配置项全部设置为初始值
	defaultConf.setToDefault();
	// 配置项覆盖设置
	void Configurations::set(Level level, ConfigurationType configurationType, const std::string& value)

	// 以配置文件方式初始化
	el::Configurations conf("/path/to/my-conf.conf");


	// 注册 default 生效
	el::Loggers::reconfigureLogger("default", conf);

	// 获得 xxx 日志(填想要获得的日志id，如果id不存在， 自动创建日志)
	el::Logger* log = el::Loggers::getLogger("xxx");
	
	// 增加标记 NewLineForContainer，STL 容器，每个元素一行
	el::Loggers::addFlag(el::LoggingFlag::NewLineForContainer);
	// 移除标记
	el::Loggers::removeFlag(el::LoggingFlag::NewLineForContainer);

	// 条件日志
	LOG_IF(condition, LEVEL)
	LOG_IF(1 == 1, INFO) << "1 is equal to 1";

	// 偶然日志
	// 每 N 次记录一次日志 every
	LOG_EVERY_N(n, LEVEL)
	//  N 次后记录一次日志 after
	LOG_AFTER_N(n, LEVEL)
	// 总共记录 N 次		  times
	LOG_N_TIMES(n, LEVEL)

	// CHECK宏日志, 不满足条件记录 FATAL 级别日志
	CHECK(condition)
	CHECK_EQ(a, b)

	// printf风格日志记录
	el::Logger* log = el::Loggers::getLogger("default");
	vector<int> vec;
	log->->info("My first ultimate log message %v %v %v", 123, 222, vec);
*/