#ifndef SRC_GAME_WORLD_H_

#define SRC_GAME_WORLD_H_

#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Game/Base.h"
#include "Game/Tile.h"

namespace CC {

/**
 * @brief The representation of the world in our game
 */
class World : public sf::Drawable {
 public:
    /**
     * @brief Construct a new empty world with a 0 size.
     */
    World();

    /**
     * @brief Add an entity in the world
     * @param entity Entity to add in the world
     * @return True if the entity has been add in the world (False if there is already an entity at the param entity position)
     */
    bool AddEntity(Entity* entity);

    /**
     * @brief Test if an entity can move to a destination position
     * @param entity The entity that we want to test
     * @param destination The wanted destination of the entity
     * @return True if entity can move to destination
     */
    bool CanMove(Entity* entity, sf::Vector2u destination);

    /**
     * @brief Move an entity to a destination position (The entity position will be change !)
     * @param entity The entity that we want to move
     * @param destination The wanted destination of the entity
     * @return True if the entity was successfully moved
     */
    bool Move(Entity* entity, sf::Vector2u destination);

    /**
     * @brief Generate the tiles of the world
     * @param random If the size of the world is random (if not it will be the size of the window)
     */
    void GenerateTiles(bool random);

    /**
     * @brief Generate a random background for the world
     */
    void GenerateRandomBackground();

    /**
     * @brief Generate entities to populate the world (Asteroids, ennemies, ...)
     * @return A list of all entities created. World doesn't own the generated entities
     */
    std::vector<Entity*> GenerateEntities();

    /**
     * @brief Add all base building to the world
     * @param base The player base
     */
    void SetupBase(Base& base);

    /**
     * @brief Draw the world on screen
     * @param target Render target to draw to
     * @param states Current render states
     */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states) const override;

    /// Get the size of the world (in tile)
    inline sf::Vector2u GetSize() const { return size; }

    inline int I(unsigned int x, unsigned int y) const {
        return x + size.x * y; }
    inline Tile& T(unsigned int x, unsigned int y) {
        return tiles[I(x, y)]; }
    inline const Tile& T(unsigned int x, unsigned int y) const {
        return tiles[I(x, y)]; }
    inline int I(sf::Vector2u p) const {
        return p.x + size.x * p.y; }
    inline Tile& T(sf::Vector2u p) {
        return tiles[I(p.x, p.y)]; }
    inline const Tile& T(sf::Vector2u p) const {
        return tiles[I(p.x, p.y)]; }

 protected:
    sf::Vector2u size;  ///< Size of the world (in tiles)
    std::vector<Tile> tiles;  ///< Tiles that compose the world
    sf::Sprite background;  ///< Sprite of the background
    std::mt19937 generator;  ///< Pseudo random number generator for this world
};

}  // namespace CC

#endif  // SRC_GAME_WORLD_H_
