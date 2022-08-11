#include "include/Animation.hpp"
#include "include/Animation.hpp"

Animation::Animation() :
   m_sprite_atlas{nullptr}, m_frame{} {
}

Animation::Animation(std::shared_ptr<SpriteAtlas> sprite_atlas) :
   m_sprite_atlas{sprite_atlas}, m_frame{} {
}

Animation::Animation(std::shared_ptr<SpriteAtlas> sprite_atlas, std::vector<FrameData>& frame) :
   m_sprite_atlas{sprite_atlas}, m_frame{} {
}

Animation::~Animation() {
}

void Animation::set_sprite_atlas(std::shared_ptr<SpriteAtlas> sprite_atlas, bool safe_old_frames) {
   if(!safe_old_frames) {
      m_frame.erase(m_frame.begin(), m_frame.end());
   }
   m_sprite_atlas = sprite_atlas;
}

void Animation::set_frame_data(std::vector<FrameData>& frame) {
   m_frame.erase(m_frame.begin(), m_frame.end());
   m_frame = frame;
}

unsigned int Animation::get_index(int i) const {
   return m_frame[i].index;
}
unsigned int Animation::get_duration(int i) const {
   return m_frame[i].duration;
}

size_t Animation::get_frame_count() const {
   return m_frame.size();
}