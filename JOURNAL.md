# Project Journal — Drone Obstacle Avoidance System

## 2026-11-26 — Day 1: Project Setup & Architecture Planning
- Created the public repository `drone-obstacle-avoidance` on GitHub.
- Defined the MVP scope: an obstacle avoidance module for drones using an ESP32 microcontroller, distance sensors (Ultrasonic/ToF), and an IMU (MPU6050) to detect obstacles and choose safe avoidance directions.
- Planned digital-first workflow before ordering hardware: Wokwi simulation -> KiCad/EasyEDA schematic & PCB -> 3D enclosure -> GitHub documentation & Hack Club submission.
- Time spent: 0.5 hours.


## 2026-11-26 — Wokwi 4-Sensor Simulation & Decision Logic

* Built a 4-sensor ultrasonic obstacle avoidance simulation (`Front`, `Left`, `Right`, `Down`) with `ESP32` and status LEDs in Wokwi.
* Implemented threshold-based avoidance logic (`MAINTAIN COURSE`, `TURN LEFT`, `TURN RIGHT`, `CLIMB UP`) and verified all cases via Serial Monitor.
* Resolved missing `GPIO 22` on the board layout by rerouting `TRIG_RIGHT` to `GPIO 27` and wired `VCC`/`GND` across all four sensors.
* Backed up `sketch.ino` and `diagram.json` to the repository.
* Time spent: 1.5 hours.
