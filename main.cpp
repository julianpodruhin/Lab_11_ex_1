#include <iostream>
#include <cmath>

class TimeException : public std::exception {
public:
    TimeException(const std::string& message) : msg(message) {}
    virtual const char* what() const throw() {
        return msg.c_str();
    }
private:
    std::string msg;
};

class Time {
public:
    Time() : hours(0), minutes(0), seconds(0) {}
    Time(int h, int m, int s) 
    {
        if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
            throw TimeException("Invalid time parameters");
        }
        hours = h + (m + s / 60) / 60;
        hours %= 24;
        minutes = (m + s / 60) % 60;
        seconds = s % 60;
    }

    int toSeconds() const {
        return hours * 3600 + minutes * 60 + seconds;
    }

    void display() const {
        std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
    }

    Time operator+(const Time& other) const {
        int totalSeconds = toSeconds() + other.toSeconds();
        int h = totalSeconds / 3600;
        int m = (totalSeconds % 3600) / 60;
        int s = totalSeconds % 60;
        return Time(h, m, s);
    }

    Time operator-(const Time& other) const {
        int totalSeconds = std::abs(toSeconds() - other.toSeconds());
        int h = totalSeconds / 3600;
        int m = (totalSeconds % 3600) / 60;
        int s = totalSeconds % 60;
        return Time(h, m, s);
    }

    Time operator+(const double& secondsToAdd) const {
        int totalSeconds = toSeconds() + static_cast<int>(secondsToAdd);
        int h = totalSeconds / 3600;
        int m = (totalSeconds % 3600) / 60;
        int s = totalSeconds % 60;
        return Time(h, m, s);
    }

    friend Time operator+(const double& secondsToAdd, const Time& time) {
        return time + secondsToAdd;
    }

    bool operator==(const Time& other) const {
        return toSeconds() == other.toSeconds();
    }

    bool operator!=(const Time& other) const {
        return !(*this == other);
    }

    bool operator<(const Time& other) const {
        return toSeconds() < other.toSeconds();
    }

    bool operator>(const Time& other) const {
        return toSeconds() > other.toSeconds();
    }

    bool operator<=(const Time& other) const {
        return *this == other || *this < other;
    }

    bool operator>=(const Time& other) const {
        return *this == other || *this > other;
    }

private:
    int hours;
    int minutes;
    int seconds;
};

int main() {
    Time t1(12, 30, 0);
    Time t2(1, 45, 30);

    // test subtraction
    Time t3 = t1 - t2;
    t3.display(); // displays "10:44:30"

    // test addition with double
    Time t4 = t1 + 3600.5;
    t4.display(); // displays "13:30:30"

    // test addition with double and reverse order
    Time t5 = 3600.5 + t1;
    t5.display(); // displays "13:30:30"

    // test comparison
    if (t1 == t2) {
        std::cout << "t1 and t2 are equal" << std::endl;
    }
    else if (t1 < t2) {
        std::cout << "t1 is earlier than t2" << std::endl;
    }
    else
    {
        std::cout << "t1 is later than t2" << std::endl;
    }

    return 0;
}