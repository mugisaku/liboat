#include"mg_image.hpp"



namespace image{


namespace{


struct
Record
{
  uint16_t  x;
  uint16_t  y;
  uint16_t  v;

  Record(uint16_t  x_, uint16_t  y_, uint16_t  v_):
  x(x_),
  y(y_),
  v(v_)
  {}

};


struct
Pack
{
  bool  string_flag;

  std::vector<Record>  record_q;

};


std::vector<Pack>
pack_q;


std::vector<Record>
record_q;


}




void
undo()
{
    if(record_q.empty())
    {
        if(pack_q.empty())
        {
          return;
        }


      Pack  pk = std::move(pack_q.back());

      pack_q.pop_back();

        if(pk.string_flag)
        {
          auto   it = pk.record_q.crbegin();
          auto  end = pk.record_q.crend();

            while(it != end)
            {
              auto&  rec = *it++;

              put_pixel(rec.v,rec.x,rec.y,false);
            }


          return;
        }


      record_q = std::move(pk.record_q);
    }


  auto&  rec = record_q.back();

  put_pixel(rec.v,rec.x,rec.y,false);

  record_q.pop_back();
}


void
clear_undo()
{
    pack_q.clear();
  record_q.clear();
}


void
begin_to_record_string()
{
    if(record_q.size())
    {
      pack_q.emplace_back(Pack{false,std::move(record_q)});

      record_q = std::vector<Record>();
    }
}


void
end_to_record_string()
{
    if(record_q.size())
    {
      pack_q.emplace_back(Pack{true,std::move(record_q)});

      record_q = std::vector<Record>();
    }
}


void
push_undo_record(int  v, int  x, int  y)
{
  record_q.emplace_back(x,y,v);
}


}




