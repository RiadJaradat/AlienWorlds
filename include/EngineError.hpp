#pragma once

#include <exception>
#include <string>

class EngineError : public std::exception
{
private:
    std::string m_message;

public:
    // Pass the error message into the constructor
    explicit EngineError(const std::string& message) : m_message("[Engine Error]: " + message) {}

    // Override what() to return your stored message
    // It MUST be const and marked noexcept
    const char* what() const noexcept override
    {
        return m_message.c_str();
    }
};