#ifndef GAME_STUB_HPP
#define GAME_STUB_HPP

namespace Game {
    double lerp(double t, double a, double b) {
        return (1 - t) * a + t * b;
    }
}

#endif
