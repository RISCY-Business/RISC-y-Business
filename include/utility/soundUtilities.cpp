#include "soundUtilities.h"
#include <iostream>

SoundUtilities::SoundUtilities(std::string soundFilePath, float volume)
{
    if (!soundBuffer.loadFromFile(soundFilePath))
    {
        std::cout << "Error loading " << soundFilePath << std::endl;
    }
    soundEffect.setBuffer(soundBuffer);
    soundEffect.setVolume(volume);
}

void SoundUtilities::playSoundEffect()
{
    soundEffect.play();
}

void SoundUtilities::setVolume(float volume)
{
    soundEffect.setVolume(volume);
}

void SoundUtilities::pauseSoundEffect()
{
    soundEffect.pause();
}

void SoundUtilities::stopSoundEffect()
{
    soundEffect.stop();
}

void SoundUtilities::setPath(std::string soundFilePath)
{
    if (!soundBuffer.loadFromFile(soundFilePath))
    {
        std::cout << "Error loading " << soundFilePath << std::endl;
    }
    soundEffect.setBuffer(soundBuffer);
}

void SoundUtilities::playSoundEffectUntilFinished()
{
    soundEffect.play();
    while (soundEffect.getStatus() == sf::Sound::Playing)
    {
    }
}


