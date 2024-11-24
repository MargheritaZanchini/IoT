#ifndef __SENSOR_H__
#define __SENSOR_H__

class Sensor {
public:
    virtual ~Sensor() = default;
    virtual float read() = 0;
};

#endif