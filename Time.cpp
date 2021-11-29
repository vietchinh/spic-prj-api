#include "Time.hpp"

using namespace spic;

double Time::timeScale {1.0f};
double Time::deltaTime {Time::timeScale / 60.0f};

double Time::DeltaTime() {
    return deltaTime;
}

double Time::TimeScale() {
    return timeScale;
}

void Time::TimeScale(double newTimeScale) {
    timeScale = newTimeScale;
}

void Time::SetDeltaTime(double newDeltaTime) {
    Time::deltaTime = Time::timeScale / newDeltaTime;
}