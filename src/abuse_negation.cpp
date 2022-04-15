// Copyright 2022 Oscar Triano García
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

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
