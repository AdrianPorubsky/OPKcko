#include <iostream>
#include <memory>
#include <opencv4/opencv2/opencv.hpp>

#include "Environment.h"
#include "Lidar.h"
#include "Robot.h"
#include "Canvas.h"
#include "Geometry.h"

// Myska
struct MouseData {
    robot::Robot* robot;
    double resolution;
};

void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        MouseData* data = static_cast<MouseData*>(userdata);
        // Prepočet pixelov na metre a nastavenie polohy
        data->robot->setState(x * data->resolution, y * data->resolution, 0.0);
        std::cout << "Robot teleportovaný na: [" << x * data->resolution << "m, " << y * data->resolution << "m]" << std::endl;
    }
}

int main() {
    // Nastavenie mapky
    environment::Config env_cfg;
    env_cfg.map_filename = "opk-map.png";
    env_cfg.resolution = 0.04; // Metre na pixle
    auto env = std::make_shared<environment::Environment>(env_cfg);

    // Canvas - vytvoríme meno okna fixne
    std::string win_name = "Vysavac";
    Canvas canvas(win_name, env_cfg.map_filename, env_cfg.resolution);

    // Lidar
    lidar::Config lidar_cfg;
    lidar_cfg.max_range = 4.0;
    lidar_cfg.beam_count = 100;
    lidar_cfg.first_ray_angle = -M_PI;
    lidar_cfg.last_ray_angle = M_PI;
    auto my_lidar = std::make_shared<lidar::Lidar>(lidar_cfg, env);

    // Kolizia [cite: 38, 59]
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
    robot::Robot moj_bot(rob_cfg, col_func);

    MouseData m_data = {&moj_bot, env_cfg.resolution};
    cv::namedWindow(win_name); // Uistíme sa, že okno existuje
    cv::setMouseCallback(win_name, onMouse, &m_data);

    // Stred mapy
    moj_bot.setState(env->getWidth() / 2.0, env->getHeight() / 2.0, 0.0);

    std::cout << "Simulacia bezi. Ovladaj WASD, klikni pre teleport, ukonci ESC." << std::endl;

    while (true) {
        canvas.clear();
        geometry::RobotState current_state = moj_bot.getState(); // [cite: 44, 58]

        // Lidarovy sken
        auto scan = my_lidar->scan(current_state);
        canvas.drawLidarScan(scan, cv::Scalar(0, 0, 255));

        // Vykreslime robota
        canvas.drawRobot(current_state, 0.4, cv::Scalar(0, 255, 0));

        canvas.show();

        int key = cv::waitKey(rob_cfg.simulation_period_ms);
        if (key == 27) break;

        geometry::Twist cmd = {0.0, 0.0};

        // Brm brm logika
        if (key == 'w' || key == 'W') cmd.linear = 8.0;
        if (key == 's' || key == 'S') cmd.linear = -8.0;
        if (key == 'a' || key == 'A') cmd.angular = -5.5;
        if (key == 'd' || key == 'D') cmd.angular = 5.5;

        moj_bot.setVelocity(cmd);
        moj_bot.update(rob_cfg.simulation_period_ms / 1000.0);
    }

    return 0;
}