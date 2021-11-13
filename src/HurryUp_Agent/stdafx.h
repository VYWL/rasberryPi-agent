#pragma once
#include <cstdio>
#include <cppcore.h>
#include <protocol.h>
#include <memory>
#include <string>
#include <string.h>
#include <mutex>
#include <ctime>
#include <future>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include <pcap.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <vector>
#include <queue>
#include <algorithm>
#include <sys/types.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()

#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <chrono>
#include <thread>
#include <functional>
#include "new_packet.h"

struct ST_ENV
{
	std::tstring ip;
	std::tstring port;
	std::tstring loggerName;
};

template<typename ... Args>
std::string StringFormatter(const std::string& format, Args ... args) {
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;

	if (size <= 0) {
		throw std::runtime_error("Error during formatting.");
	}

	std::unique_ptr<char[]> buf(new char[size]);

	snprintf(buf.get(), size, format.c_str(), args ...);

	return std::string(buf.get(), buf.get() + size - 1);
}

// For Interval

template <class F, class... Args>
void setInterval(std::atomic_bool& cancelToken, size_t interval, F&& f, Args&&... args) {
	cancelToken.store(true);
	auto cb = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
	std::async(std::launch::async, [=, &cancelToken]()mutable {
		while (cancelToken.load()) {
			cb();
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		}
		});
}
