// #define LOGGING
#ifdef LOGGING
#define sp(...) Serial.print(__VA_ARGS__);
#define spl(...) Serial.println(__VA_ARGS__);
#else
#define sp(...)
#define spl(...)
#endif