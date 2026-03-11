//
// Created by adrian on 2/25/26.
//

#include "include/cv2.h"

int main() {
    Canvas canvas(800, 600);
    cv::Scalar currentColor(0, 0, 255); // Predvolená červená (BGR!) [cite: 144]

    while (true) {
        canvas.show();
        int key = cv::waitKey(30); // Čakanie na kláves [cite: 120]

        if (key == 27) break; // ESC - ukončiť [cite: 130]
        if (key == ' ') canvas.clear(); // SPACE - vymazať [cite: 64]

        // Kreslenie tvarov v strede [cite: 64]
        if (key == 'c') canvas.addShape(std::make_unique<Circle>(cv::Point(400, 300), 50, currentColor));
        if (key == 'r') canvas.addShape(std::make_unique<Rectangle>(cv::Point(350, 250), cv::Point(450, 350), currentColor));

        // Zmena farieb 1-5 [cite: 64]
        if (key == '1') currentColor = cv::Scalar(0, 0, 255);   // Červená [cite: 144]
        if (key == '2') currentColor = cv::Scalar(0, 255, 0);   // Zelená [cite: 147]
        if (key == '3') currentColor = cv::Scalar(255, 0, 0);   // Modrá [cite: 149]
        if (key == '4') currentColor = cv::Scalar(0, 255, 255); // Žltá [cite: 151]
        if (key == '5') currentColor = cv::Scalar(255, 0, 255); // Purpurová [cite: 154]
    }
    return 0;
}