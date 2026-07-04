#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>

/*
////////// to clearify: ///////////////
// sound track is a biom spesific track that contain enviroment sounds
//// eg. Water, Thermal Vents and more.
*/

struct SoundEffect
{
    sf::Sound sound;

    void setPosition(sf::Vector2f p)
    {
        sound.setPosition(p.x, p.y, 0.f);
    }
};

class AudioManager
{
private:
    float soundVolume = 50.f;
    float minDistance2D = 100.f;
    float attenuation = 1.f;

    sf::Music *currentSoundTrack = nullptr;

    std::vector<SoundEffect> sounds;

public:
    AudioManager()
    {
        sf::Listener::setDirection(0.f, -1.f, 0.f);   // temperarly
    }

    void setLisitenerPosition(const sf::Vector2f &postition)
    {
        sf::Listener::setPosition(postition.x, postition.y, 0.f);
    }

    void playSoundEffect(const sf::SoundBuffer &buffer, const sf::Vector2f &position)
    {
        sounds.emplace_back();
        sounds.back().sound.setBuffer(buffer);
        sounds.back().sound.setPosition(position.x, position.y, 0.f);
        sounds.back().sound.setVolume(soundVolume);
        sounds.back().sound.setRelativeToListener(false);
        sounds.back().sound.setAttenuation(attenuation);
        sounds.back().sound.setMinDistance(minDistance2D);
        sounds.back().sound.play();
    }

    void playSoundTrack(sf::Music &music, bool isforce = false, bool loop = true)
    {
        if (currentSoundTrack == &music && currentSoundTrack->getStatus() == sf::Music::Playing && !isforce)
            return;

        if (currentSoundTrack)
            currentSoundTrack->stop();
        currentSoundTrack = &music;
        currentSoundTrack->setVolume(soundVolume);
        currentSoundTrack->setLoop(loop);
        currentSoundTrack->play();
    }

    void pause()
    {
        if (currentSoundTrack)
            currentSoundTrack->pause();
    }

    void resume()
    {
        if (currentSoundTrack)
            currentSoundTrack->play();
    }

    void setVolume(const float newVolume)
    {
        soundVolume = newVolume;
        if (currentSoundTrack)
            currentSoundTrack->setVolume(soundVolume);
        for (auto &se : sounds)
            se.sound.setVolume(soundVolume);
    }

    void update()
    {
        sounds.erase(
            std::remove_if(
                sounds.begin(),
                sounds.end(),
                [](const SoundEffect &se) // FIXED: must match the vector type (SoundEffect)
                {
                    return se.sound.getStatus() == sf::Sound::Stopped;
                }),
            sounds.end());
    }

    void stopSoundTrack()
    {
        if (currentSoundTrack)
        {
            currentSoundTrack->stop();
            currentSoundTrack = nullptr;
        }
    }
};