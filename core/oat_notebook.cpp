#include"oat_notebook.hpp"




namespace oat{




NoteBook::
NoteBook():
top(nullptr),
top_index(0)
{
}




int
NoteBook::
get_top_index() const
{
  return top_index;
}


void
NoteBook::
change_top(int  i)
{
  int  ii = 0;

    for(auto  child: children)
    {
        if(ii == i)
        {
          child->unset_flag(Widget::hidden_flag);
          child->need_to_redraw();

          top = child;
        }

      else
        {
          child->set_flag(Widget::hidden_flag);
        }


      ii += 1;
    }


  top_index = i;

  set_flag(needed_to_redraw_perfect_flag);
}


void
NoteBook::
join(Widget*  child, int  x, int  y)
{
    if(child)
    {
      child->change_parent(*this,x,y);

      children.emplace_back(child);

        if(!top)
        {
          top = child;
        }

      else
        {
          child->set_flag(Widget::hidden_flag);
        }
    }
}




void
NoteBook::
update_sizes()
{
  int  w = 0;
  int  h = 0;

    for(auto  child: children)
    {
        if(child)
        {
          child->update_sizes();

          auto&  rpt = child->get_relative_point();

          w = std::max(w,(rpt.x+child->width ));
          h = std::max(h,(rpt.y+child->height));
        }
    }


  change_content_width( w);
  change_content_height(h);

  Box::update_sizes();
}


void
NoteBook::
reform()
{
  const int  old_right  = get_right() ;
  const int  old_bottom = get_bottom();

  update_points(parent? &parent->get_box().get_content_rectangle().point:nullptr);

    for(auto  child: children)
    {
        if(child && child->test_flag(needed_to_reform_flag))
        {
          child->reform();

          set_flag(needed_to_redraw_child_flag);
        }
    }


  update_sizes();

    if((get_right()  > old_right ) ||
       (get_bottom() > old_bottom))
    {
      set_flag(needed_to_redraw_perfect_flag);
    }

  else
    {
      set_flag(needed_to_redraw_self_flag);
    }


  notify_flag(needed_to_redraw_child_flag);

  unset_flag(needed_to_reform_flag);
}


}




