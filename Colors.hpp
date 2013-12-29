#ifndef HPP_COLORS_DEFINED
#define HPP_COLORS_DEFINED

// Windows environment
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string RESTORE = "";
static const std::string BLACK   = ""; // Black
static const std::string RED     = ""; // Red
static const std::string GREEN   = ""; // Green
static const std::string YELLOW  = ""; // Yellow
static const std::string BLUE    = ""; // Blue
static const std::string PURPLE  = ""; // Purple
static const std::string CYAN    = ""; // Cyan
static const std::string WHITE   = ""; // White

// Unix-alike
#else 
static const std::string RESTORE = "\e[0m";
static const std::string BLACK   = "\e[1;30m"; // Black
static const std::string RED     = "\e[1;31m"; // Red
static const std::string GREEN   = "\e[1;32m"; // Green
static const std::string YELLOW  = "\e[1;33m"; // Yellow
static const std::string BLUE    = "\e[1;34m"; // Blue
static const std::string PURPLE  = "\e[1;35m"; // Purple
static const std::string CYAN    = "\e[1;36m"; // Cyan
static const std::string WHITE   = "\e[1;37m"; // White

#endif

#endif
