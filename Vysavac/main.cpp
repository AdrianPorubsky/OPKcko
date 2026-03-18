#include <iostream>
#include <memory>
#include <opencv4/opencv2/opencv.hpp>

#include "Environment.h"
#include "Lidar.h"
#include "Robot.h"
#include "Canvas.h"
#include "Geometry.h"

int main() {
    // Nastavenie mapky
    environment::Config env_cfg;
    env_cfg.map_filename = "opk-map.png";
    env_cfg.resolution = 0.04; // Metre na pixle
    auto env = std::make_shared<environment::Environment>(env_cfg);

    // Canvas
    Canvas canvas("Vysavac", env_cfg.map_filename, env_cfg.resolution);

    // Lidar
    lidar::Config lidar_cfg;
    lidar_cfg.max_range = 4.0;
    lidar_cfg.beam_count = 100;
    lidar_cfg.first_ray_angle = -M_PI;
    lidar_cfg.last_ray_angle = M_PI;
    auto my_lidar = std::make_shared<lidar::Lidar>(lidar_cfg, env);

    // Kolizia
    robot::Robot::CollisionCb col_func = [&](geometry::RobotState s) {
        double radius = 0.4;
        if (env->isOccupied(s.x, s.y)) return true;
        for (int i = 0; i < 8; ++i) {
            double angle = i * (M_PI / 4.0);
            if (env->isOccupied(s.x + radius * cos(angle), s.y + radius * sin(angle))) return true;
        }
        return false;
    };

    // Inicializacia vysavacu
    robot::Config rob_cfg;
    rob_cfg.simulation_period_ms = 20; // 20ms cyklus
    robot::Robot adrian_bot(rob_cfg, col_func);

    // Nastavíme počiatočnú polohu (napr. stred mapy)
    adrian_bot.setState(env->getWidth() / 2.0, env->getHeight() / 2.0, 0.0);

    std::cout << "Simulacia bezi. Ovladaj WASD, ukonci ESC." << std::endl;

    while (true) {
        canvas.clear();
        geometry::RobotState current_state = adrian_bot.getState();

        // Lidarovy sken
        auto scan = my_lidar->scan(current_state);
        canvas.drawLidarScan(scan, cv::Scalar(0, 0, 255)); // Cervene bodky

        // Vykreslime robota
        canvas.drawRobot(current_state, 0.4, cv::Scalar(0, 255, 0)); // Zelený kruh

        canvas.show(); // cv::imshow

        int key = cv::waitKey(rob_cfg.simulation_period_ms);
        if (key == 27) break; // ESC

        geometry::Twist cmd = {0.0, 0.0}; // {linear, angular}

        // Brm brm logika
        if (key == 'w' || key == 'W') cmd.linear = 8;
        if (key == 's' || key == 'S') cmd.linear = -8;
        if (key == 'a' || key == 'A') cmd.angular = -5;
        if (key == 'd' || key == 'D') cmd.angular = 5;

        adrian_bot.setVelocity(cmd);
        adrian_bot.update(rob_cfg.simulation_period_ms / 1000.0); // Prevod ms na sekundy
    }

    return 0;
}