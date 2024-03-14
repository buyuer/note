#include "note.hpp"

#include <android/api-level.h>

namespace note {

std::string demo() { return std::to_string(android_get_device_api_level()); }

} // namespace note