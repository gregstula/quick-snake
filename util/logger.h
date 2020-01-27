#pragma once
#include <streambuf>
#include <syslog.h>
#include <utility>
#include <ostream>

namespace util {
namespace log {

enum level
{
    emergency = LOG_EMERG,
    alert     = LOG_ALERT,
    critical  = LOG_CRIT,
    error     = LOG_ERR,
    warning   = LOG_WARNING,
    notice    = LOG_NOTICE,
    info      = LOG_INFO,
    debug     = LOG_DEBUG,
};

enum type
{
    AUTH   = LOG_AUTH,
    CRon   = LOG_CRON,
    daemon = LOG_DAEMON,
    local0 = LOG_LOCAL0,
    local1 = LOG_LOCAL1,
    local2 = LOG_LOCAL2,
    local3 = LOG_LOCAL3,
    local4 = LOG_LOCAL4,
    local5 = LOG_LOCAL5,
    local6 = LOG_LOCAL6,
    local7 = LOG_LOCAL7,
    print  = LOG_LPR,
    mail   = LOG_MAIL,
    news   = LOG_NEWS,
    user   = LOG_USER,
    uucp   = LOG_UUCP,
};

class syslog_stream;

class syslog_streambuf: public std::basic_streambuf<char>
{
public:
    explicit syslog_streambuf(const std::string& name, log::type type):
        std::basic_streambuf<char>()
    {
        openlog(name.size() ? name.data() : nullptr, LOG_PID, type);
    }
    ~syslog_streambuf() override { closelog(); }

protected:
    int_type overflow(int_type c = traits_type::eof()) override
    {
        if(traits_type::eq_int_type(c, traits_type::eof()))
            sync();
        else buffer += traits_type::to_char_type(c);

        return c;
    }

    int sync() override
    {
        if(buffer.size())
        {
            syslog(level, "%s", buffer.data());

            buffer.clear();
            level = ini_level;
        }
        return 0;
    }

    friend class syslog_stream;
    void set_level(log::level new_level) noexcept { level = new_level; }

private:
    static constexpr log::level ini_level = log::info;
    log::level level = ini_level;

    std::string buffer;
};

class syslog_stream: public std::basic_ostream<char>
{
public:
    explicit syslog_stream(const std::string& name = std::string(), log::type type = log::user):
        std::basic_ostream<char>(&streambuf),
        streambuf(name, type)
    { }

    syslog_stream& operator<<(log::level level) noexcept
    {
        streambuf.set_level(level);
        return (*this);
    }

private:
    syslog_streambuf streambuf;
};

}
}
