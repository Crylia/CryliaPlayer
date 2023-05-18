#pragma once

#include <string>

namespace tools {
  class DateTime {
  private:
    int hour;
    int minute;
    int second;

    int year;
    int month;
    int day;
  public:
    DateTime(int day, int month, int, int second, int min, int hour);
    ~DateTime( );

    DateTime& operator+(DateTime);
    DateTime& operator-(DateTime);
    bool operator==(DateTime);

    DateTime NewDate( );
    DateTime NewTime( );

    std::string ToString( );
    std::string TimeToString( );
    std::string DateToString( );
  };

} // namespace tools
