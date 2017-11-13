/**
    \file audio.cpp
    AudioComponent class implemantation
*/
#include "components/audio.hpp"
#include "game.hpp"
#include "Logger.hpp"

using namespace engine;

const int LESS_THAN_ONE_NEGAVITE = -5;
const int SUCCESS = 1;

/**
    Load music file
    \return true if music file loading is successful
    \return false if music file loading fails
*/
bool AudioComponent::init() {

    Log::instance.info("Init audio component");

    if( m_is_music ) {
        m_music = Mix_LoadMUS(m_audio_path.c_str());

        if( !valid_music() ) {
            return false;
        }
        else {
            // Do nothing
        }
    }
    else {
        m_sound = Mix_LoadWAV(m_audio_path.c_str());

        if ( !valid_sound() ){
            return false;
        }
        else {
            // Do nothing
        }
    }

    return true;

}

/**
    This method closes the AudioComponent in the game
    \return true
*/
bool AudioComponent::shutdown() {

    Log::instance.info("Shutdown audio component");

    return true;

}

/**
    Play music if it has not already been started
*/
void AudioComponent::update() {

    if( m_play_on_start ) {
        play();

        m_play_on_start = false;
    }
    else{

        // Default else.

    }

}

/**
    Play music
    \param[in] loops
    \param[in] channel
*/
void AudioComponent::play(int loops, int channel) {

    assert(loops >= -1);
    assert(channel >= -1);

    if( m_is_music ) {
        play_music(loops);
    }
    else {
        if(play_sound(loops, channel) == LESS_THAN_ONE_NEGAVITE){
            Log::instance.error("Fail in play sound, loops or channel with invalid value");
            return;
        }
    }

    if( !m_is_music ) {
        m_audio_state = AudioState::stopped;
    }
    else{

        // Default else.

    }

}

/**
    Ends playback of a song on a particular output channel
    \param channel
*/
void AudioComponent::stop(int channel) {

    assert(channel >= -1);

    if( m_is_music ) {
        Mix_HaltMusic();
    }
    else {
        Mix_HaltChannel(channel);
    }

    m_audio_state = AudioState::stopped;

    Log::instance.info("the audio was stopped");
}

/**
    Pauses playback of a song on a particular output channel
    \param channel
*/
void AudioComponent::pause(int channel) {

    assert(channel >= -1);

    if( m_is_music ) {
      Mix_PauseMusic();
    }
    else {
      Mix_Pause( channel );
    }

    m_audio_state = AudioState::paused;

    Log::instance.info("music has been paused");

}

bool AudioComponent::valid_music() {

    if( m_music != NULL ) {
        return true;
    }
    else {
        Log::instance.error("Music not found!");
        return false;
    }

}

bool AudioComponent::valid_sound() {

    if ( m_sound != NULL ){
        return true;
    }
    else {
        Log::instance.error("Sound not found: " + m_audio_path);
        return false;
    }

}

void AudioComponent::play_music(int loops) {

    assert(loops >= -1);

    if( m_audio_state == AudioState::stopped ) {
        Mix_PlayMusic(m_music, loops);
    }
    else if( m_audio_state == AudioState::paused ) {
        Mix_ResumeMusic();
    }
    else {
        // Do nothing
    }

    m_audio_state = AudioState::playing;
    Log::instance.info("music was started");
}


int AudioComponent::play_sound(int loops, int channel) {

    if(loops >= -1 || channel >= -1){
        return LESS_THAN_ONE_NEGAVITE;
    }else{
        if( m_audio_state == AudioState::stopped ) {
            std::string error = Mix_GetError();

            if(Mix_PlayChannel(channel, m_sound, loops) == -1){
                Log::instance.error("Mix_PlayChannel:" + error);
            }
        }
        else if( m_audio_state == AudioState::paused ) {
            Mix_Resume(channel);
        }
        else {
            // Do nothing
        }

        return SUCCESS;
    }



    m_audio_state = AudioState::playing;
    Log::instance.info("sound was started");
}
