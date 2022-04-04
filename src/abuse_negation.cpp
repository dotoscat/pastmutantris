#include "abuse_negation.hpp"

AbuseNegation::AbuseNegation(): current_index(0) {}

void AbuseNegation::set_capacity(int capacity) {
    values.assign(capacity, -1);
    current_index = 0;
}

void AbuseNegation::push_value(int value) {
    if (value < 0) {
        return;
    }
    if (current_index >= values.size()) {
        current_index = 0;
    }
    values[current_index] = value;
    current_index++;
}

void AbuseNegation::clear() {
    values.assign(values.size(), -1);
    current_index = 0;
}

int AbuseNegation::punish(const int POINTS, int value) {
    float count = 0;
    float length = static_cast<float>(values.size());
    for (auto v : values) {
        count += v == value ? 1.f : 0.f;
    }
    int points = POINTS - static_cast<float>(POINTS) * (count / length);
    return points;
}
