#ifndef SCREEN_H
#define SCREEN_H

enum class ScreenType{
    START_SCREEN,
    PLAY_SCREEN,
};

enum class ScreenState{
    RUNNING,
    PAUSED,
    FINISHED,
    CLOSE_GAME,
};

class Screen{ //Clase abstracta para las pantallas del juego
    private:
        ScreenType type;

    protected:
        ScreenState state;

    public:
        Screen() = default;
        Screen(ScreenType type);
        virtual ~Screen();

        ScreenType getType();

        ScreenState getState();

        virtual void init() = 0;

        virtual void update(float deltaTime) = 0;

        virtual void render() = 0;
};


#endif
