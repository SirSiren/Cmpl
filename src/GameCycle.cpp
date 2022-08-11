#include <chrono>
#include "include/GameCycle.hpp"

GameCycle::GameCycle(unsigned int p_framerate) :
   m_lag{0.0}, m_ms_per_frame{1.0/p_framerate}, m_should_stop{false} {
}

void GameCycle::set_framerate(unsigned int p_ms_per_frame) {
   m_ms_per_frame = {1.0/p_ms_per_frame};
}

void GameCycle::update_start_point() {
   m_start_point = steady_clock::now();
}

void GameCycle::update_end_point() {
   m_end_point = steady_clock::now();
}
 
void GameCycle::process_input() {
   
}

void GameCycle::update_state() {

}

void GameCycle::render(double p_time_factor) {

}

void GameCycle::run() {
   update_start_point();
   m_lag = 0.0;
   while (!m_should_stop) {
      update_end_point();
      m_lag += (m_end_point - m_start_point).count();

      process_input();

      while (m_lag >= m_ms_per_frame) {
         update_state();
         m_lag -= m_ms_per_frame;
      }
      
      render(m_lag / m_ms_per_frame);
   }
}


void GameCycle::stop() {
   m_should_stop = true;
}