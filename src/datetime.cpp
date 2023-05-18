#include "datetime.h"

namespace tools {
  DateTime::DateTime(int day = 1, int month = 1, int year = 1970, int second = 0, int min = 0, int hour = 0) :
    day(day), month(month), year(year), second(second), minute(minute), hour(hour) {

  }
  DateTime::~DateTime( ) { }
}
