#include "Lidar.h"
#include <cmath>

namespace lidar {

    Lidar::Lidar(const Config& config, std::shared_ptr<environment::Environment> env)
        : config_(config), env_(env) {} //

    std::vector<geometry::Point2d> Lidar::scan(const geometry::RobotState& state) const {
        std::vector<geometry::Point2d> results;

        // Uhlovy krok
        double angle_range = config_.last_ray_angle - config_.first_ray_angle; //
        double angle_step = angle_range / (config_.beam_count - 1); //

        for (int i = 0; i < config_.beam_count; ++i) {
            // Uhol
            double current_angle = state.theta + config_.first_ray_angle + (i * angle_step); //

            // Skenovanie po troske
            for (double dist = 0.0; dist <= config_.max_range; dist += 0.02) {

                double x = state.x + dist * std::cos(current_angle); //
                double y = state.y + dist * std::sin(current_angle); //

                // Kontrola kolizie
                if (env_->isOccupied(x, y)) { //
                    results.push_back({x, y});
                    break;
                }
            }
        }

        return results;
    }

} // namespace lidar