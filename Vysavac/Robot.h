#pragma once

#include <functional>
#include "Geometry.h"

namespace robot {

struct Config {
    geometry::Twist accelerations;
    geometry::Twist emergency_decelerations;
    double command_duration;
    int simulation_period_ms;
};


class Robot {
public:
    using CollisionCb = std::function<bool(geometry::RobotState)>;

    Robot(const Config& config, const CollisionCb& collision_cb = nullptr);
    ~Robot();
    void setVelocity(const geometry::Twist& velocity);
    geometry::RobotState getState() const;

    void setState(double x, double y, double theta) {
        state_.x = x;
        state_.y = y;
        state_.theta = theta;
    }
    bool isInCollision() const;
    void update(double dt);
protected:
    void update(const geometry::Twist& velocity, double dt);

private:
    Config config_;
    CollisionCb collision_cb_;
    geometry::RobotState state_;
    geometry::Twist current_velocity_;
};
} // namespace robot

