#include "Robot.h"
#include <cmath>

namespace robot {

    Robot::Robot(const Config& config, const CollisionCb& collision_cb)
        : config_(config), collision_cb_(collision_cb) {
        state_ = {0.0, 0.0, 0.0};
        current_velocity_ = {0.0, 0.0};
    }

    Robot::~Robot() {}

    void Robot::setVelocity(const geometry::Twist& velocity) {
        current_velocity_ = velocity;
    }

    geometry::RobotState Robot::getState() const {
        return state_;
    }

    void Robot::update(double dt) {
        update(current_velocity_, dt);
    }

    void Robot::update(const geometry::Twist& velocity, double dt) {
        geometry::RobotState next_state = state_;

        // Kinematika asi
        next_state.x += velocity.linear * std::cos(state_.theta) * dt;
        next_state.y += velocity.linear * std::sin(state_.theta) * dt;
        next_state.theta += velocity.angular * dt;

        if (collision_cb_) {
            if (!collision_cb_(next_state)) {
                state_ = next_state;
            }
        } else {
            state_ = next_state;
        }
    }

    bool Robot::isInCollision() const {
        if (collision_cb_) return collision_cb_(state_);
        return false;
    }

} // namespace robot