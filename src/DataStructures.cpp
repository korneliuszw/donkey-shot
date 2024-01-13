#include <DataStructures.h>

bool safe_string_compare(char* a, char* b) {
return strncmp(a, b, min(strlen(a), strlen(b))) == 0;
}
