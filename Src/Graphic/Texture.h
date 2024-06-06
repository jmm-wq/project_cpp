#ifndef SRC_GRAPHIC_TEXTURE_H_

#define SRC_GRAPHIC_TEXTURE_H_

#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

namespace CC {

/**
 * @brief A collection of texture that we are going to load from the disk,
 * We are using a singleton because we don't want our texture to be open anywhere else in the program and we want anyone to be able to access the texture anywhere in the program
 */
class TextureCollection : private sf::NonCopyable {
 public:
    /**
     * @brief Name of all textures available
     */
    enum Id : int {
        SpriteSheet = 0,    // Source : see individual sprites
        Andromeda,          // Source : https://www.pexels.com/photo/sky-space-milky-way-stars-110854/, Edited using Pixelator.com
        Galaxy1,            // Source : https://www.pexels.com/photo/photo-of-galaxy-207529/, Edited using Pixelator.com
        Galaxy2,            // Source : https://www.pexels.com/photo/sky-space-dark-galaxy-2150/, Edited using Pixelator.com
        GalaxyCluster,      // Source : https://www.pexels.com/photo/sky-space-dark-galaxy-2162/, Edited using Pixelator.com
        MilkyWay1,          // Source : https://www.pexels.com/photo/milky-way-galaxy-during-nighttime-1252890/, Edited using Pixelator.com
        MilkyWay2,          // Source : https://www.pexels.com/photo/milky-way-illustration-1169754/, Edited using Pixelator.com
        Nebula,             // Source : https://www.pexels.com/photo/sky-space-telescope-universe-41951/, Edited using Pixelator.com
        PurpleSun,          // Source : https://www.pexels.com/photo/purple-and-brown-colored-planet-39561/, Edited using Pixelator.com
        StarCluster1,       // Source : https://www.pexels.com/photo/cluster-of-stars-1341279/, Edited using Pixelator.com
        StarCluster2,       // Source : https://www.pexels.com/photo/photography-of-starry-sky-810890/, Edited using Pixelator.com
        YellowSun,           // Source : https://www.pexels.com/photo/yellow-sphere-illustration-39649/, Edited using Pixelator.com
        Enemy               // Source : https://www.deviantart.com/dellkan/art/Evil-circle-20149424, Edited using Pixelator.com
    };

    /**
     * @brief Load the texture
     * @return True if the texture was loaded, false otherwise
     */
    static bool Load();

    /**
     * @brief Get the SFML texture
     * @return A reference to the SFML texture
     */
    static sf::Texture& Get(TextureCollection::Id textureId) {
        return instance.textures[textureId]; }

 protected:
    std::unordered_map<TextureCollection::Id, sf::Texture> textures;  ///< The SFML texture that we loaded

 private:
    TextureCollection() { }
    static TextureCollection instance;
};

}  // namespace CC

#endif  // SRC_GRAPHIC_TEXTURE_H_
