#ifndef GAME_CYCLE_HPP
#define GAME_CYCLE_HPP

#include <chrono>

using namespace std::chrono;

typedef duration<double, std::ratio<1, 1000>> dmilliseconds;

class GameCycle
{
public:
   GameCycle() = default;
   GameCycle(unsigned int p_framerate);
   ~GameCycle() = default;

   void set_framerate(unsigned int p_framerate);

   void update_start_point();
   void update_end_point();
   void process_input();
   void update_state();
   void render(double p_time_factor);
   void run();
   void stop();
private:
   time_point<steady_clock, dmilliseconds> m_start_point;
   time_point<steady_clock, dmilliseconds> m_end_point;
   double m_lag{0.0};
   double m_ms_per_frame{1.0/60.0};
   bool m_should_stop{false};
};

#endif //GAME_CYCLE_HPP