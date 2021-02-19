#ifndef payload_h
#define payload_h
#include <stdint.h>

typedef enum {STATUS, POSITION} payload_1_type;

// TODO: Replan the data types for each value to reduce the payload size
typedef struct {

    unsigned long upTime;     // uptime in ms
    float temp;               // temperature maybe?
    int battery;              // Battery level
} Status;

typedef struct {
    uint16_t lat_deg;
    uint32_t lat_billionths;
    bool lat_negative;
    uint16_t lng_deg;
    uint32_t lng_billionths;
    bool lng_negative;
} Position;

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} DateTime;

typedef struct {
    DateTime dateTime;
    Position position;
} NodePosition;

union Payload_1 {
    Status status;
    NodePosition position;
};

typedef struct {
    uint8_t nodeId;           // store this nodeId
    payload_1_type payloadType;     // Type of message
    union Payload_1 payload;      // Actual payload object
} Payload_0;

typedef Payload_0 Payload;

#endif
