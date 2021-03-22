#ifndef SCREEN_H
#define SCREEN_H

enum class ScreenType{
    START_SCREEN,
    PLAY_SCREEN,
};

class Screen{ //Clase abstracta para las pantallas del juego
    private:
        ScreenType type;

    public:
        Screen() = default;
        Screen(ScreenType type);

        ScreenType getType();

        virtual void init() = 0;

        virtual void update(float deltaTime) = 0;

        virtual void render() = 0;

        virtual bool finished() = 0;
};


#endif
