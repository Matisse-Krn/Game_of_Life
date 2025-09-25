#include "GoL.h"

void handle_toggle_hud(t_app *app)
{
  if (!app || !app->in.req_toggle_hud)
    return ;
  app->in.req_toggle_hud = 0;
  app->hud_visible = !app->hud_visible;
}
