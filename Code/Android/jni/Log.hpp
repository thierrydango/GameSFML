#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <sstream>
#include "android/log.h"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "MyApp",__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "MyApp",__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "MyApp",__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "MyApp",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "MyApp",__VA_ARGS__)

// namespace log
// {
//     class cdebug_t : public std::ostream
//     {
//         public:
//             template <class T>
//             cdebug_t& operator<<(T const& toLog);
//     };
//
//     cdebug_t cdebug;
// }
//
// template <class T>
// log::cdebug_t& log::cdebug_t::operator<<(T const& toLog)
// {
//     std::string output;
//     std::stringstream stream;
//     stream << toLog;
//     stream >> output;
//     __android_log_print(ANDROID_LOG_DEBUG, "MyApp", output.c_str());
//     return *this;
// }

#endif // LOG_HPP
