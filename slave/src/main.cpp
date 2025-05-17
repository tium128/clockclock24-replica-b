#include <Wire.h>

#include "board_config.h"
#include "board.h"
#include "clock_state.h"
#include "i2c.h"

const t_clock default_clock = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


t_half_digit target_clocks_state;
t_half_digit current_clocks_state;

// I2C runs on main core (core 0)
void receiveEvent(int how_many)
{
  // Serial.println("Received something");
  if (how_many >= sizeof(half_digit))
  {
    t_half_digit tmp_state;
    I2C_readAnything (tmp_state);

    for (uint8_t i = 0; i < 3; i++)
    {
      target_clocks_state.clocks[i] = tmp_state.clocks[i];
      target_clocks_state.change_counter[i] = tmp_state.change_counter[i];
    }
  }
}

void setup()
{  
  Serial.begin(115200);
  Serial.println("clockclock24 replica by Vallasc slave v1.0");

  board_begin();
  target_clocks_state = {{default_clock, default_clock, default_clock}, {0, 0, 0}};

  Wire.begin(get_i2c_address());
  Wire.onReceive(receiveEvent);
}

void loop()
{
  delay(10);
}

void setup1() 
{
  current_clocks_state = {{default_clock, default_clock, default_clock}, {0, 0, 0}};
}

// Steppers on core 1
void loop1()
{
  board_loop();
  for (uint8_t i = 0; i < 3; i++)
  {
    if(!clock_is_running(i) && current_clocks_state.change_counter[i] != target_clocks_state.change_counter[i])
    {
      //Serial.printf("Inside clock %d\n", i);
      current_clocks_state.clocks[i] = target_clocks_state.clocks[i];
      current_clocks_state.change_counter[i] = target_clocks_state.change_counter[i];

      if(current_clocks_state.clocks[i].mode_h == ADJUST_HAND)
        adjust_h_hand(i, current_clocks_state.clocks[i].adjust_h);

      if(current_clocks_state.clocks[i].mode_m == ADJUST_HAND)
        adjust_m_hand(i, current_clocks_state.clocks[i].adjust_m);

      if(current_clocks_state.clocks[i].mode_h <= MAX_DISTANCE3)
        set_clock(i, current_clocks_state.clocks[i]);
    }
  }
}