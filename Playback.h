#pragma once

enum class Repeat {
    Off,
    All,
    One,
};

namespace Volume {
    constexpr int MinVolume{0};
    constexpr int MaxVolume{100};
    constexpr int DefaultVolume{MaxVolume};

    constexpr float volumeAsDecimal(int volume) {
        return 1.0 * volume / MaxVolume;
    }
}
