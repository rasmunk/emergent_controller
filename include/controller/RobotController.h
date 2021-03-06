//
// Created by Rasmus Munk on 27/01/2017.
//

#ifndef EMERGENT_ROBOT_ROBOTCONTROLLER_H
#define EMERGENT_ROBOT_ROBOTCONTROLLER_H

#include <include/config/RobotConfig.h>
#include <include/configuration/RobotConfiguration.h>

class RobotController {
private:
public:
    int id = 0;
    virtual void stop() = 0;
    virtual ~RobotController() = default;
};

#endif // EMERGENT_ROBOT_ROBOTCONTROLLER_H
