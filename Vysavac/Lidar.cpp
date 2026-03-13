#include "Lidar.h"
#include <cmath>

namespace lidar {

    // Implementácia konštruktora - uložíme si konfig a prostredie do private premenných
    Lidar::Lidar(const Config& config, std::shared_ptr<environment::Environment> env)
        : config_(config), env_(env) {} //

    std::vector<geometry::Point2d> Lidar::scan(const geometry::RobotState& state) const {
        std::vector<geometry::Point2d> results;

        // 1. Výpočet uhlového kroku medzi lúčmi
        double angle_range = config_.last_ray_angle - config_.first_ray_angle; //
        double angle_step = angle_range / (config_.beam_count - 1); //

        for (int i = 0; i < config_.beam_count; ++i) {
            // 2. Určenie absolútneho uhla lúča (uhol robota + relatívny uhol lúča)
            double current_angle = state.theta + config_.first_ray_angle + (i * angle_step); //

            // 3. "Kráčanie" po lúči (Raycasting)
            // Posúvame sa od robota smerom von po malých krokoch (napr. 2 cm)
            for (double dist = 0.0; dist <= config_.max_range; dist += 0.02) {
                // Výpočet súradnice bodu na lúči
                double x = state.x + dist * std::cos(current_angle); //
                double y = state.y + dist * std::sin(current_angle); //

                // 4. Kontrola kolízie cez Environment
                if (env_->isOccupied(x, y)) { //
                    results.push_back({x, y}); // Zásah prekážky
                    break; // Lúč končí pri prvej prekážke
                }
            }
        }

        return results; // Vráti zoznam všetkých bodov, ktoré trafili stenu
    }

} // namespace lidar