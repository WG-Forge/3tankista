#pragma once

#include "game/game_configuration.h"
#include "game/game_events.h"

class Tank;

#include "ecs.h"

#include <tuple>

class UiSystem : public ecs::System<UiSystem>, public ecs::event::IEventListener
{
    enum class HealthBarPosition
    {
        TOP_LEFT,
        TOP_RIGHT,
        MIDDLE_LEFT,
        MIDDLE_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };

public:
    UiSystem();
    virtual ~UiSystem() override;

public:
    void OnHealthChanged(const HealthChanged* event);
    void OnNewTankCreated(const NewTankCreated* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();

private:
    std::string ChooseTextureForTankHealthBar(Tank* tank, HealthBarPosition pos) const;

    std::string ChooseTextureForTankType(Tank* tank) const;

private:
    std::vector<GameObjectId> healthBarsId;

    inline static const std::array<std::tuple<HealthBarPosition, Vector3i, Vector3f, Color>, 30>
        POSSIBLE_HEALTH_BAR_POSITIONS{
            std::tuple(HealthBarPosition::TOP_LEFT,
                       Vector3i{ -3, -7, -(-3) - (-7) },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.91f, 0.0f),
                       BLUE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::TOP_LEFT,
                       Vector3i{ -4, -6, -(-4) - (-6) },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.79f, 0.0f),
                       BLUE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::TOP_LEFT,
                       Vector3i{ -5, -5, -(-5) - (-5) },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.67f, 0.0f),
                       BLUE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::TOP_LEFT,
                       Vector3i{ -6, -4, -(-6) - (-4) },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.55f, 0.0f),
                       BLUE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::TOP_LEFT,
                       Vector3i{ -7, -3, -(-7) - (-3) },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.43f, 0.0f),
                       BLUE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::TOP_RIGHT,
                       Vector3i{ 3, -10, -3 - (-10) },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.91f, 0.0f),
                       BLUE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::TOP_RIGHT,
                       Vector3i{ 4, -10, -4 - (-10) },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.79f, 0.0f),
                       BLUE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::TOP_RIGHT,
                       Vector3i{ 5, -10, -5 - (-10) },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.67f, 0.0f),
                       BLUE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::TOP_RIGHT,
                       Vector3i{ 6, -10, -6 - (-10) },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.55f, 0.0f),
                       BLUE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::TOP_RIGHT,
                       Vector3i{ 7, -10, -7 - (-10) },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.43f, 0.0f),
                       BLUE_SPAWN_COLOR),

            std::tuple(HealthBarPosition::MIDDLE_LEFT,
                       Vector3i{ -10, 3, -(-10) - 3 },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.21f, 0.0f),
                       ROSE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::MIDDLE_LEFT,
                       Vector3i{ -10, 4, -(-10) - 4 },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.09f, 0.0f),
                       ROSE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::MIDDLE_LEFT,
                       Vector3i{ -10, 5, -(-10) - 5 },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.01f, 0.0f),
                       ROSE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::MIDDLE_LEFT,
                       Vector3i{ -10, 6, -(-10) - 6 },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.13f, 0.0f),
                       ROSE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::MIDDLE_LEFT,
                       Vector3i{ -10, 7, -(-10) - 7 },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.25f, 0.0f),
                       ROSE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::MIDDLE_RIGHT,
                       Vector3i{ 10, -3, -10 - (-3) },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.21f, 0.0f),
                       ROSE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::MIDDLE_RIGHT,
                       Vector3i{ 10, -4, -10 - (-4) },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * -0.09f, 0.0f),
                       ROSE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::MIDDLE_RIGHT,
                       Vector3i{ 10, -5, -10 - (-5) },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.01f, 0.0f),
                       ROSE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::MIDDLE_RIGHT,
                       Vector3i{ 10, -6, -10 - (-6) },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.13f, 0.0f),
                       ROSE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::MIDDLE_RIGHT,
                       Vector3i{ 10, -7, -10 - (-7) },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.25f, 0.0f),
                       ROSE_SPAWN_COLOR),

            std::tuple(HealthBarPosition::BOTTOM_LEFT,
                       Vector3i{ -3, 10, -(-3) - 10 },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.43f, 0.0f),
                       ORANGE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::BOTTOM_LEFT,
                       Vector3i{ -4, 10, -(-4) - 10 },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.55f, 0.0f),
                       ORANGE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::BOTTOM_LEFT,
                       Vector3i{ -5, 10, -(-5) - 10 },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.67f, 0.0f),
                       ORANGE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::BOTTOM_LEFT,
                       Vector3i{ -6, 10, -(-6) - 10 },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.79f, 0.0f),
                       ORANGE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::BOTTOM_LEFT,
                       Vector3i{ -7, 10, -(-7) - 10 },
                       Vector3f(-((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.91f, 0.0f),
                       ORANGE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::BOTTOM_RIGHT,
                       Vector3i{ 3, 7, -3 - 7 },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.43f, 0.0f),
                       ORANGE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::BOTTOM_RIGHT,
                       Vector3i{ 4, 6, -4 - 6 },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.55f, 0.0f),
                       ORANGE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::BOTTOM_RIGHT,
                       Vector3i{ 5, 5, -5 - 5 },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.67f, 0.0f),
                       ORANGE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::BOTTOM_RIGHT,
                       Vector3i{ 6, 4, -6 - 4 },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.79f, 0.0f),
                       ORANGE_SPAWN_COLOR),
            std::tuple(HealthBarPosition::BOTTOM_RIGHT,
                       Vector3i{ 7, 3, -7 - 3 },
                       Vector3f(((float)GAME_WINDOW_WIDTH) / 2.0f * 0.7f, GAME_WINDOW_HEIGHT / 2.0f * 0.91f, 0.0f),
                       ORANGE_SPAWN_COLOR)
        };
};
