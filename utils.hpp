# pragma once
# define WNCK_I_KNOW_THIS_IS_UNSTABLE
# include <libwnck/libwnck.h>
# include <string>
# include <X11/Xlib.h>
# include <gdk/gdkx.h>
# include <vector>

namespace AD
{

    struct resolution
    {
        resolution() : width(0), height(0) {}
        resolution(int w, int h) : width(w), height(h) {}
        int width;
        int height;
    };
    typedef resolution size;

    struct position
    {
        position() : x(0), y(0) {}
        position(int x, int y) : x(x), y(y) {}
        int x;
        int y;
    };

    struct geometry
    {
        position window_pos;
        size window_size;
    };

    inline int getWorkspaceCount(WnckWindow* wnd)
    {
        int count = 0;
        if(wnd)
        {
            WnckScreen* screen = wnck_window_get_screen(wnd);
            count              = wnck_screen_get_workspace_count(screen);
        }
        return count;
    }

    inline bool hasWindowName(WnckWindow* wnd)
    {
        return ((wnck_window_has_name(wnd) == TRUE) ? true : false );
    }

    inline std::string getWindowName(WnckWindow* wnd)
    {
        return { wnck_window_get_name(wnd) };
    }

    inline WnckWorkspace* getWorkspace(WnckWindow* wnd, int wsid)
    {
        int id             = 0;
        WnckScreen* screen = wnck_window_get_screen(wnd);
        GList* wss         = wnck_screen_get_workspaces(screen);

        for(; wss != nullptr; wss = wss->next)
        {
            if(id == wsid)
                return static_cast<WnckWorkspace*>(wss->data);
            else 
                ++id;
        }
        return nullptr;
    }

    inline void setWindowAbove(WnckWindow* wnd)
    {
        if(wnd)
            wnck_window_make_above(wnd);
    }

    inline void setWindowBelow(WnckWindow* wnd)
    {
        if(wnd)
            wnck_window_make_below(wnd);
    }

    inline void moveWindowTo(WnckWindow* wnd, int wsid, bool activate = false)
    {
        if(wnd)
        {
            auto ws = getWorkspace(wnd,wsid);
            if(ws)
            {
                wnck_window_move_to_workspace(wnd, ws );

                if(activate)
                    wnck_window_activate(wnd, 1);
            }
        }
    }

    inline void switchWorkspace(WnckWindow* wnd, int wsid)
    {
        if(wnd)
            wnck_workspace_activate(getWorkspace(wnd, wsid), 1);
    }

    inline resolution getScreenSize(WnckScreen* screen)
    {
        return { wnck_screen_get_width(screen), 
                 wnck_screen_get_height(screen) };
    }

    inline resolution getScreenSize(WnckWindow* wnd)
    {
        WnckScreen* tmp = wnck_window_get_screen(wnd);
        return getScreenSize(tmp);
    }

    inline geometry getWindowGeometry(WnckWindow* wnd)
    {
        geometry ret;
        wnck_window_get_geometry(wnd, &ret.window_pos.x, &ret.window_pos.y, &ret.window_size.width, &ret.window_size.height);
        return ret;
    }

    inline void setWindowGeometry(WnckWindow* wnd, const geometry& geom)
    {
        if(wnd)
            wnck_window_set_geometry(wnd, 
                                     WNCK_WINDOW_GRAVITY_CURRENT, 
                                     WnckWindowMoveResizeMask(WNCK_WINDOW_CHANGE_X + 
                                                              WNCK_WINDOW_CHANGE_Y + 
                                                              WNCK_WINDOW_CHANGE_WIDTH + 
                                                              WNCK_WINDOW_CHANGE_HEIGHT), 
                                     geom.window_pos.x, 
                                     geom.window_pos.y, 
                                     geom.window_size.width, 
                                     geom.window_size.height);
    }

    inline position getWindowPosition(WnckWindow* wnd)
    {
        int x = 0, y = 0;
        wnck_window_get_geometry(wnd, &x, &y, nullptr, nullptr);
        return {x,y};
    }

    inline void moveWindow(WnckWindow* wnd, int x, int y)
    {
        if(wnd)
            XMoveWindow(gdk_x11_get_default_xdisplay(), wnck_window_get_xid(wnd), x, y);
    }
    inline void moveWindow(WnckWindow* wnd, const position& newposition)
    {
        moveWindow(wnd, newposition.x, newposition.y);
    }
    inline void moveWindowX(WnckWindow* wnd, int x)
    {
        moveWindow(wnd, x, getWindowPosition(wnd).y );
    }
    inline void moveWindowY(WnckWindow* wnd, int y)
    {
        moveWindow(wnd, getWindowPosition(wnd).x, y );
    }
    
    inline size getWindowSize(WnckWindow* wnd)
    {
        int width = 0, height = 0;
        wnck_window_get_geometry(wnd, nullptr, nullptr, &width, &height);
        return {width, height};
    }

    inline void setWindowSize(WnckWindow* wnd, int width, int height)
    {
        if(wnd)
            XResizeWindow(gdk_x11_get_default_xdisplay(), wnck_window_get_xid(wnd), width, height);
    }

    inline void setWindowSize(WnckWindow* wnd, const size& newsize)
    {
        setWindowSize(wnd, newsize.width, newsize.height);
    }

    inline void moveResizeWindow(WnckWindow* wnd, int x, int y, int width, int height)
    {
        if(wnd)
            XMoveResizeWindow(gdk_x11_get_default_xdisplay(), wnck_window_get_xid(wnd), x, y, width, height);
    }

    inline void moveResizeWindow(WnckWindow* wnd, const position& pos, const size& newsize)
    {
        if(wnd)
            moveResizeWindow(wnd, pos.x, pos.y, newsize.width, newsize.height);
    }

    inline void center(WnckWindow* wnd)
    {
        if(wnd)
        {
            auto wssize  = getScreenSize(wnd);
            auto wndsize = getWindowSize(wnd);
            int x        = (wssize.width  - wndsize.width ) / 2;
            int y        = (wssize.height - wndsize.height) / 2;
            moveWindow(wnd, x, y);
        }
    }

    inline void setFullscreen(WnckWindow* wnd)
    {
        if(wnd)
            wnck_window_set_fullscreen(wnd, true);
    }
    inline void setMaximized(WnckWindow* wnd)
    {
        if(wnd)
            wnck_window_set_fullscreen(wnd, false);
    }

    inline void close(WnckWindow* wnd)
    {
        if(wnd)
            wnck_window_close(wnd,1 );
    }

    inline Atom getAtom(const char* atomname)
    {
        return XInternAtom(gdk_x11_get_default_xdisplay(), atomname, 0);
    }

    inline Screen* getXscreen(WnckWindow* wnd)
    {
        Window   xid;
        XWindowAttributes attrs;

        xid = wnck_window_get_xid (wnd);
        XGetWindowAttributes(gdk_x11_get_default_xdisplay(), xid, &attrs);

        return attrs.screen;
    }

    # define _NET_WM_STATE_REMOVE 0
    # define _NET_WM_STATE_ADD    1
    # define _NET_WM_STATE_TOGGLE 2
    void change_state(Screen *screen, Window xwindow, gboolean add, Atom state1, Atom state2)
    {
        XEvent xev;
        xev.xclient.type = ClientMessage;
        xev.xclient.serial = 0;
        xev.xclient.send_event = True;
        xev.xclient.display = gdk_x11_get_default_xdisplay();
        xev.xclient.window = xwindow;
        xev.xclient.message_type = getAtom("_NET_WM_STATE");
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = add ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        xev.xclient.data.l[1] = state1;
        xev.xclient.data.l[2] = state2;

        XSendEvent (gdk_x11_get_default_xdisplay(),
                        RootWindowOfScreen (screen),
                        False,
                        SubstructureRedirectMask | SubstructureNotifyMask,
                        &xev);
    }

    # define PROP_MOTIF_WM_HINTS_ELEMENTS 5
    # define MWM_HINTS_DECORATIONS (1L << 1)
    inline void set_decorations(WnckWindow *window, bool decorate)
    {
        struct 
        {
            unsigned long flags;
            unsigned long functions;
            unsigned long decorations;
            long inputMode;
            unsigned long status;
        } hints = {0};

        hints.flags = MWM_HINTS_DECORATIONS;
        hints.decorations = decorate;

        XChangeProperty(gdk_x11_get_default_xdisplay(), 
                        wnck_window_get_xid (window),
                        getAtom("_MOTIF_WM_HINTS"),
                        getAtom("_MOTIF_WM_HINTS"), 
                        32, 
                        PropModeReplace,
                        (unsigned char *)&hints, 
                        PROP_MOTIF_WM_HINTS_ELEMENTS);

        change_state (getXscreen(window),
                      wnck_window_get_xid(window), 
                      !decorate,
                      getAtom("_OB_WM_STATE_UNDECORATED"), 
                      0);

    }

    inline void removeDecorations(WnckWindow* wnd)
    {
        if(wnd)
            set_decorations(wnd, false);
    }
    inline void addDecorations(WnckWindow* wnd)
    {
        if(wnd)
            set_decorations(wnd, true);
    }

    inline void tile(WnckWindow* wnd, std::vector<WnckWindow*>& vec)
    {
        if(wnd)
            vec.push_back(wnd);
    }

    inline void do_tile(std::vector<WnckWindow*> vec, int panel_height, int panel_width)
    {
        if(!vec.empty())
        {
          int count = 0;
          int count2 = 0;
          for(int i = 0; i < vec.size(); ++i)
          {
            auto screen_size = AD::getScreenSize(vec[i]);
            int width = screen_size.width / (count + 2 );
            int height = screen_size.height / (count + 1);
            setWindowSize(vec[i], width - panel_width, height );

            if(i == 0)
              moveWindow(vec[i], panel_width, 0);
            else
            {
              auto last_pos = getWindowPosition(vec[i-1]);
              auto last_size = getWindowSize(vec[i-1]);
              moveWindow(vec[i], last_pos.x + last_size.width + panel_width, (last_pos.y + last_size.height) * count2);
              setWindowSize(vec[i], (screen_size.width - last_size.width - panel_width ) / (count2+1), screen_size.height / (count2+2) );
              ++count2;
            }
            ++count;
          }
        }
    }
} // End of AD namespace
    