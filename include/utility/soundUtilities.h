#ifndef SOUNDUTILITIES_H
#define SOUNDUTILITIES_H
#include <SFML/Audio.hpp>

class SoundUtilities
{
    public:
        SoundUtilities(std::string soundFilePath, float volume);
        void playSoundEffect();
        void playSoundEffectUntilFinished();
        void setVolume(float volume);
        void pauseSoundEffect();
        void stopSoundEffect();
        void setPath(std::string soundFilePath);

    private:
        sf::Sound soundEffect;
        sf::SoundBuffer soundBuffer;
};
#endif // SOUNDUTILITIES_H
