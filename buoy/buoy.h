#ifndef BUOY_H_
#define BUOY_H_

void setup();
void loop();

// transmit data from buoy
void transmit();
// collect data using buoy sensors
void dataCollect();
// command buoy to descend
void descend();
// command buoy to ascend
void ascend();

enum Status
{
    SURFACE,
    UNDERWATER,
    ASCEND,
    DESCEND
};

#endif /* BUOY_H_ */