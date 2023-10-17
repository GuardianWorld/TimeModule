#ifndef TIMEERROR_HPP
#define TIMEERROR_HPP
#include <iostream>


class InvalidDateException : public std::exception {
public:
    InvalidDateException(const std::string& errorMessage) : errorMessage_(errorMessage) {}
    const char* what() const noexcept override {
        return errorMessage_.c_str();
    }
private:
    std::string errorMessage_;
};

class InvalidTimeException : public std::exception {
public:
    InvalidTimeException(const std::string& errorMessage) : errorMessage_(errorMessage) {}
    const char* what() const noexcept override {
        return errorMessage_.c_str();
    }
private:
    std::string errorMessage_;
};

#endif //TIMEERROR_HPP