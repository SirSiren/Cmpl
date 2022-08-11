#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <memory>
#include <vector>

#include "SpriteAtlas.hpp"

//Here the frame data is stored.
//Index is the Tile index in Sprite Atlas
//Duration is the time in frames during which tile is shown
struct FrameData {
   unsigned int index;
   unsigned int duration;
};

class Animation {
public:
   Animation();
   Animation(std::shared_ptr<SpriteAtlas> sprite_atlas);
   Animation(std::shared_ptr<SpriteAtlas> sprite_atlas, std::vector<FrameData>& frame);
   ~Animation();
   
   void set_sprite_atlas(std::shared_ptr<SpriteAtlas> sprite_atlas, bool safe_old_frames = false);
   void set_frame_data(std::vector<FrameData>& frame); 
   
   unsigned int get_index(int i)    const;
   unsigned int get_duration(int i) const;
   size_t       get_frame_count()   const;
private:
   std::shared_ptr<SpriteAtlas> m_sprite_atlas{nullptr};
   std::vector<FrameData> m_frame{};
};

#endif //ANIMATION_HPP