#include"gramk_card.hpp"
#include"gramk_painter.hpp"
#include<cstring>




void  Card::set_recording_flag()  {recording_flag =  true;}
void  Card::unset_recording_flag(){recording_flag = false;}



void
Card::
undo()
{
RESTART:
    if(operation_log.size())
    {
      auto&  dot = operation_log.back();

      color_table[dot.y][dot.x] = dot.color;

      operation_log.pop_back();
    }

  else
    if(!log_list.empty())
    {
      auto&  log = log_list.front();

        if(log.solid_flag)
        {
          auto   it = log.stack.crbegin();
          auto  end = log.stack.crend();

            while(it != end)
            {
              color_table[it->y][it->x] = it->color;

              ++it;
            }


          log_list.pop_front();
        }

      else
        {
          operation_log = std::move(log.stack);

          log_list.pop_front();

          goto RESTART;
        }
    }
}



void
Card::
prepare_new_log(bool  solid_flag)
{
    if(operation_log.size())
    {
      log_list.emplace_front(std::move(operation_log),solid_flag);

      operation_log.clear();
    }
}





