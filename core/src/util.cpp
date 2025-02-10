#include "util.h"

#include <ctime>

namespace core::util {

    void init_random() {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    int random_int(int min, int max) {
        return min + rand() % (max - min + 1);
    }

    float random_float(float min, float max) {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

} // namespace core::util