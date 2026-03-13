#include <iostream>
#include <memory>
#include <cmath>
#include <opencv2/opencv.hpp>
#include "Environment.h"
#include "Lidar.h"
#include "Geometry.h"

// Funkcia na kontrolu kolízie celého obvodu robota
bool isCollisionFree(double x, double y, double radius, std::shared_ptr<environment::Environment> env) {
    // Skontrolujeme stred a 8 bodov po obvode (každých 45 stupňov)
    if (env->isOccupied(x, y)) return false;

    for (int i = 0; i < 8; ++i) {
        double angle = i * (M_PI / 4.0);
        double check_x = x + radius * std::cos(angle);
        double check_y = y + radius * std::sin(angle);
        if (env->isOccupied(check_x, check_y)) return false;
    }
    return true;
}

int main() {
    environment::Config env_cfg;
    env_cfg.map_filename = "opk-map.png";
    env_cfg.resolution = 0.04;
    auto env = std::make_shared<environment::Environment>(env_cfg);

    lidar::Config lidar_cfg;
    lidar_cfg.max_range = 5.0;
    lidar_cfg.beam_count = 120;
    lidar_cfg.first_ray_angle = -M_PI;
    lidar_cfg.last_ray_angle = M_PI;
    lidar::Lidar my_lidar(lidar_cfg, env);

    geometry::RobotState state;
    // Dynamický spawn v strede mapy
    state.x = env->getWidth() / 2.0;
    state.y = env->getHeight() / 2.0;
    state.theta = 0.0;

    // VYŠŠIE RÝCHLOSTI pre seamless pocit
    double linear_speed = 0.15;  // 15cm na krok
    double angular_speed = 0.12; // rýchlejšia rotácia
    double robot_radius = 0.4;   // Polomer robota v metroch (cca 8 pixelov pri 0.05 res)

    std::cout << "Turbo Smooth ovládanie zapnuté. WASD pre pohyb." << std::endl;

    while (true) {
        // Načítanie mapy (na tvojom CPU to pôjde bleskovo)
        cv::Mat canvas = cv::imread(env_cfg.map_filename, cv::IMREAD_COLOR);
        if (canvas.empty()) break;

        auto to_px = [&](double m) { return static_cast<int>(m / env_cfg.resolution); };

        // 1. LIDAR body
        auto scan_points = my_lidar.scan(state);
        for (const auto& pt : scan_points)
            cv::circle(canvas, cv::Point(to_px(pt.x), to_px(pt.y)), 1, cv::Scalar(0, 0, 255), -1);

        // 2. Vykreslenie robota
        int rx = to_px(state.x);
        int ry = to_px(state.y);
        int r_px = static_cast<int>(robot_radius / env_cfg.resolution);

        cv::circle(canvas, cv::Point(rx, ry), r_px, cv::Scalar(0, 200, 0), 2); // Telo

        // Smerovka (predok)
        cv::line(canvas, cv::Point(rx, ry),
                 cv::Point(rx + (r_px+5) * std::cos(state.theta), ry + (r_px+5) * std::sin(state.theta)),
                 cv::Scalar(255, 0, 0), 2);

        cv::imshow("Turbo Vysavac", canvas);

        // 3. SEAMLESS INPUT
        int key = cv::waitKey(1); // Iba 1ms čakanie
        if (key == 27) break;

        double next_x = state.x;
        double next_y = state.y;

        if (key == 'w' || key == 'W') {
            next_x += linear_speed * std::cos(state.theta);
            next_y += linear_speed * std::sin(state.theta);
        }
        if (key == 's' || key == 'S') {
            next_x -= linear_speed * std::cos(state.theta);
            next_y -= linear_speed * std::sin(state.theta);
        }
        if (key == 'a' || key == 'A') state.theta -= angular_speed;
        if (key == 'd' || key == 'D') state.theta += angular_speed;

        // 4. KONTROLA KOLÍZIE OBVODU
        if (isCollisionFree(next_x, next_y, robot_radius, env)) {
            state.x = next_x;
            state.y = next_y;
        } else {
            // Malý vizuálny feedback v konzole (nepovinné)
            // std::cout << "Kontakt!" << std::endl;
        }
    }

    return 0;
}