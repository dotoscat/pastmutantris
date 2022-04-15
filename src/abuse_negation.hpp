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

#ifndef _ABUSE_NEGATION_
#define _ABUSE_NEGATION_

#include <vector>

class AbuseNegation {
    std::vector<int> values;
    int current_index;

    public:
        AbuseNegation();
        void set_capacity(int);
        void push_value(int);
        void clear();
        int punish(const int, int);
};

#endif
