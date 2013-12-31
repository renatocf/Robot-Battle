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
static const std::string RESTORE = "\033[0m";
static const std::string BLACK   = "\033[1;30m"; // Black
static const std::string RED     = "\033[1;31m"; // Red
static const std::string GREEN   = "\033[1;32m"; // Green
static const std::string YELLOW  = "\033[1;33m"; // Yellow
static const std::string BLUE    = "\033[1;34m"; // Blue
static const std::string PURPLE  = "\033[1;35m"; // Purple
static const std::string CYAN    = "\033[1;36m"; // Cyan
static const std::string WHITE   = "\033[1;37m"; // White

#endif

#endif
