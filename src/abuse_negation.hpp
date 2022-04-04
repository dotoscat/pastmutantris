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
