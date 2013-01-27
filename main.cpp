# define WNCK_I_KNOW_THIS_IS_UNSTABLE
# include "utils.hpp"
# include "parse.hpp"
# include <sys/stat.h>

static std::vector<AD::config> configs;
static std::vector<WnckWindow*> tiled_windows;
static bool ad_debug = false;
static bool simulate = false;

static void on_window_opened(WnckScreen *screen, WnckWindow *window, gpointer data)
{
  if(window)
  {
    auto type = wnck_window_get_window_type(window);
    int panel_width  = 0;
    int panel_height = 0;
    if(type == WNCK_WINDOW_DOCK)
    {
      auto tmp = AD::getWindowSize(window);
      panel_width = tmp.width;
      panel_height = tmp.height;
    }

    for(auto i = configs.begin(); i != configs.end(); ++i)
      {
        auto wname = AD::getWindowName(window);

        if( (wname.find(i->appname) != std::string::npos || i->appname == "*") && 
              type != WNCK_WINDOW_DESKTOP && 
              type != WNCK_WINDOW_DOCK)
        {
          for(auto j = i->funcs.begin(); j != i->funcs.end(); ++j)
          {
            if(j->func == "center")
            {
              if(!simulate)
                AD::center(window);
              if(ad_debug)
                std::cout<<"[***] Centered window ("<<wname<<")\n";
            }          
            else if(j->func == "moveTo")
            {
              int ws = std::atoi(j->params[0].c_str());

              if(!simulate)
                AD::moveWindowTo(window, ws);

              if(ad_debug)
                std::cout<<"[***] Moved window ("<<wname<<") to workspace ("<<ws<<")\n";
            }
            else if(j->func == "moveActivateTo")
            {
              int ws = std::atoi(j->params[0].c_str());

              if(!simulate)
                AD::moveWindowTo(window, ws, true);

              if(ad_debug)
                std::cout<<"[***] Moved and activated window ("<<wname<<") to workspace ("<<ws<<")\n";
            }
            else if(j->func == "move")
            {
              if(j->params[0] == "*")
              {
                int y = std::atoi(j->params[1].c_str());

                if(!simulate)
                  AD::moveWindowY(window, y);

                if(ad_debug)
                  std::cout<<"[***] Moved window ("<<wname<<") on Y axis to ("<<y<<")\n";
              }
              else if(j->params[1] == "*")
              {
                int x = std::atoi(j->params[0].c_str());

                if(!simulate)
                  AD::moveWindowX(window, x);
                
                if(ad_debug)
                  std::cout<<"[***] Moved window ("<<wname<<") on X axis to ("<<x<<")\n";
              }
              else
              {
                int x = std::atoi(j->params[0].c_str());
                int y = std::atoi(j->params[1].c_str());

                if(!simulate)
                  AD::moveWindow(window, x, y);
                
                if(ad_debug)
                  std::cout<<"[***] Moved window ("<<wname<<") on both axes to ("<<x<<","<<y<<")\n";
              }
            }
            else if(j->func == "setAbove")
            {
              if(!simulate)
                AD::setWindowAbove(window);
              if(ad_debug)
                std::cout<<"[***] Set window ("<<wname<<") above\n";
            }
            else if(j->func == "setBelow")
            {
              if(!simulate)
                AD::setWindowBelow(window);
              if(ad_debug)
                std::cout<<"[***] Set window ("<<wname<<") below\n";
            }
            else if(j->func == "setFullscreen")
            {
              if(!simulate)
                AD::setFullscreen(window);
              if(ad_debug)
                std::cout<<"[***] Set window ("<<wname<<") fullscreen\n";
            }
            else if(j->func == "setMaximized")
            {
              if(!simulate)
                AD::setMaximized(window);
              if(ad_debug)
                std::cout<<"[***] Set window ("<<wname<<") maximized\n";
            }
            else if(j->func == "close")
            {
              if(!simulate)
                AD::close(window);
              if(ad_debug)
                std::cout<<"[***] Closed window ("<<wname<<")\n";
            }
            else if(j->func == "removeDecorations")
            {
              if(!simulate)
                AD::removeDecorations(window);
              if(ad_debug)
                std::cout<<"[***] Removed window ("<<wname<<") decorations\n";
            }
            else if(j->func == "addDecorations")
            {
              if(!simulate)
                AD::addDecorations(window);
              if(ad_debug)
                std::cout<<"[***] Added window ("<<wname<<") decorations\n";
            }
            else if(j->func == "tile")
            {
              if(!simulate)
                AD::tile(window, tiled_windows);
              if(ad_debug)
                std::cout<<"[***] Adding window ("<<wname<<") to tile queue\n";
            }

          }
          break;
        }
      }

    if(!simulate)
      AD::do_tile(tiled_windows, panel_height, panel_width);
    if(ad_debug)
      std::cout<<"[***] Tilling windows\n";
  }
}

void readfiles()
{
  std::string script_folder = g_get_user_config_dir();
  script_folder += "/angeldust";

  if(!g_file_test(script_folder.c_str(), G_FILE_TEST_IS_DIR))
    if(mkdir(script_folder.c_str(), 0700) != 0 )
    {
      std::cerr<<"Could not create folder: "<<script_folder<<"\n";
      return;
    }

  GDir* dir = g_dir_open(script_folder.c_str(), 0, nullptr);
  const char* curent = nullptr;

  while((curent=g_dir_read_name(dir)))
  {
    std::string fl = g_build_path(G_DIR_SEPARATOR_S, ".",curent, NULL);
    if(g_str_has_suffix(curent,".ad"))
      {
        fl = fl.substr(1);

        if(ad_debug)
          std::cout<<"[***] Parsing file ("<<script_folder + fl<<")\n";

        AD::parse(script_folder + fl, configs);
      }
  }
  g_dir_close(dir);

  for(int i = 0;i < configs.size(); ++i)
    if(configs[i].appname == "*" && i != configs.size() - 1)
    {
      auto tmp = configs[configs.size()-1];
      configs[configs.size()-1] = configs[i];
      configs[i] = tmp;
      break;
    }
}

int main (int argc, char *argv[])
{
  if(argc > 1)
    for (int i = 1; i < argc; ++i)
    {
        std::string ar(argv[i]);
        if( ar == "-d")
          ad_debug = true;
        else if( ar == "-s")
          simulate = true;
    }

  readfiles();
  
  GMainLoop *loop;
  WnckScreen *screen;

  gdk_init (&argc, &argv);

  loop = g_main_loop_new (NULL, FALSE);
  screen = wnck_screen_get_default ();

  g_signal_connect (screen, "window-opened", G_CALLBACK (on_window_opened), NULL);
  g_main_loop_run (loop);
  g_main_loop_unref (loop);

  return 0;
}
