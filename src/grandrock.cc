#include <config.h>
#include <gtk/gtk.h>
#include <string>
#include <vector>

#include "xrandr-query.h"

using namespace std;

vector<string*> slist;
GtkWidget *menu = NULL;

// Wrapper to create a strings which are deleted when new menu is created.
string *newstr(const string &str) {
    string *ptr = newstr(str);
    slist.push_back(ptr);
    return ptr;
}

void on_item_click(GtkWidget *item, gpointer data) {
    string *str=(string*)data;
    if (str->find("--mode") == string::npos || \
            gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(item)) == TRUE)
        if (system(str->c_str()) == -1)
            cout << "Warning: Call to xrandr failed." << endl;
}

void popupMenu(GtkStatusIcon *icon, guint button, guint32 time, gpointer data) {
    // Query XRANDR for device info
    vector<device_t*> devices = getdevices();

    // Get list of active devices
    vector<string> activedev;
    for (int i=0; i<devices.size(); i++)
        if (devices[i]->curres.size() > 0)
            activedev.push_back(devices[i]->name);

    // Genenerate popup menu
    if (menu != NULL) {
        gtk_widget_destroy(menu);
        menu = NULL;
        for (int i=0; i<slist.size(); i++)
            delete slist[i];
        slist.clear();
    }
    menu = gtk_menu_new();

    // Generate popup menu using device info
    vector<device_t*>::iterator dev = devices.begin();
    while (dev != devices.end()) {
        GtkWidget *dev_item = gtk_check_menu_item_new_with_label((*dev)->name.c_str());
        gtk_menu_shell_append(GTK_MENU_SHELL(menu), dev_item);
        string prefix = "xrandr --output "+(*dev)->name;
        if ((*dev)->curres.size() > 0) {
            gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(dev_item), TRUE);

            g_signal_connect(G_OBJECT(dev_item), "toggled",
                    G_CALLBACK(on_item_click),
                    newstr(prefix+" --off"));

            vector<string>::iterator res = (*dev)->reslist.begin();
            GSList *group = NULL;
            while (res != (*dev)->reslist.end()) {
                GtkWidget *devres =
                    gtk_radio_menu_item_new_with_label(group, (*res).c_str());
                group = gtk_radio_menu_item_get_group(
                        GTK_RADIO_MENU_ITEM(devres));
                gtk_menu_shell_append(GTK_MENU_SHELL(menu), devres);
                if (*res == (*dev)->curres)
                    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(devres),TRUE);
                g_signal_connect(G_OBJECT(devres), "toggled",
                        G_CALLBACK(on_item_click),
                        newstr(prefix + " --mode "+*res));
                res++;
            }

            if (activedev.size() <= 1)
                gtk_widget_set_sensitive(dev_item, FALSE);
            else {
                GtkWidget *pos_item = gtk_menu_item_new_with_label("Position");
                GtkWidget  *left_item = gtk_menu_item_new_with_label("Left of");
                GtkWidget *right_item = gtk_menu_item_new_with_label("Right of");
                GtkWidget *above_item = gtk_menu_item_new_with_label("Above of");
                GtkWidget *below_item = gtk_menu_item_new_with_label("Below of");
                GtkWidget *clone_item = gtk_menu_item_new_with_label("Clone of");
                GtkWidget *pos_menu = gtk_menu_new();
                GtkWidget  *left_menu = gtk_menu_new();
                GtkWidget *right_menu = gtk_menu_new();
                GtkWidget *above_menu = gtk_menu_new();
                GtkWidget *below_menu = gtk_menu_new();
                GtkWidget *clone_menu = gtk_menu_new();
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(pos_item), pos_menu);
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(left_item), left_menu);
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(right_item), right_menu);
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(above_item), above_menu);
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(below_item), below_menu);
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(clone_item), clone_menu);
                gtk_menu_shell_append(GTK_MENU_SHELL(pos_menu), left_item);
                gtk_menu_shell_append(GTK_MENU_SHELL(pos_menu), right_item);
                gtk_menu_shell_append(GTK_MENU_SHELL(pos_menu), above_item);
                gtk_menu_shell_append(GTK_MENU_SHELL(pos_menu), below_item);
                gtk_menu_shell_append(GTK_MENU_SHELL(pos_menu), clone_item);
                for (int i=0; i<activedev.size(); i++) {
                    if (activedev[i] != (*dev)->name) {
                        GtkWidget *leftdev =
                            gtk_menu_item_new_with_label(activedev[i].c_str());
                        GtkWidget *rightdev =
                            gtk_menu_item_new_with_label(activedev[i].c_str());
                        GtkWidget *abovedev =
                            gtk_menu_item_new_with_label(activedev[i].c_str());
                        GtkWidget *belowdev =
                            gtk_menu_item_new_with_label(activedev[i].c_str());
                        GtkWidget *clonedev =
                            gtk_menu_item_new_with_label(activedev[i].c_str());
                        gtk_menu_shell_append(GTK_MENU_SHELL(left_menu),  leftdev);
                        gtk_menu_shell_append(GTK_MENU_SHELL(right_menu), rightdev);
                        gtk_menu_shell_append(GTK_MENU_SHELL(above_menu), abovedev);
                        gtk_menu_shell_append(GTK_MENU_SHELL(below_menu), belowdev);
                        gtk_menu_shell_append(GTK_MENU_SHELL(clone_menu), clonedev);
                        g_signal_connect(G_OBJECT(leftdev), "activate",
                                G_CALLBACK(on_item_click),
                                newstr(prefix + " --left-of "+activedev[i]));
                        g_signal_connect(G_OBJECT(rightdev), "activate",
                                G_CALLBACK(on_item_click),
                                newstr(prefix + " --right-of "+activedev[i]));
                        g_signal_connect(G_OBJECT(abovedev), "activate",
                                G_CALLBACK(on_item_click),
                                newstr(prefix + " --above "+activedev[i]));
                        g_signal_connect(G_OBJECT(belowdev), "activate",
                                G_CALLBACK(on_item_click),
                                newstr(prefix + " --below "+activedev[i]));
                        g_signal_connect(G_OBJECT(clonedev), "activate",
                                G_CALLBACK(on_item_click),
                                newstr(prefix + " --same-as "+activedev[i]));
                    }
                }
                gtk_menu_shell_append(GTK_MENU_SHELL(menu), pos_item);
            }
        } else {
            g_signal_connect(G_OBJECT(dev_item), "activate",
                    G_CALLBACK(on_item_click),
                    newstr(prefix + " --auto"));
        }
        dev++;
        if (dev != devices.end())
            gtk_menu_shell_append(GTK_MENU_SHELL(menu),
                    gtk_separator_menu_item_new());
    }

    // Free device info
    for (int i=0; i<devices.size(); i++)
        delete devices[i];
    devices.clear();

    gtk_widget_show_all(menu);

    gtk_menu_popup(GTK_MENU(menu), NULL, NULL, gtk_status_icon_position_menu, icon, button, gtk_get_current_event_time());
}

static GtkStatusIcon *create_tray_icon() {
        GtkStatusIcon *tray_icon;

        tray_icon = gtk_status_icon_new();
        g_signal_connect(G_OBJECT(tray_icon),
                "activate",
                 G_CALLBACK(popupMenu), NULL);
        g_signal_connect(G_OBJECT(tray_icon),
                 "popup-menu",
                 G_CALLBACK(popupMenu), NULL);

        gtk_status_icon_set_from_icon_name(tray_icon, "grandrock");
        gtk_status_icon_set_tooltip_text(tray_icon, "XRandr Applet");
        gtk_status_icon_set_visible(tray_icon, TRUE);

        return tray_icon;
}

int main(int argc, char **argv) {
        GtkStatusIcon *tray_icon;

        gtk_init(&argc, &argv);
        g_set_application_name("Grandrock");
        gtk_window_set_default_icon_name("grandrock");
        tray_icon = create_tray_icon();
        gtk_main();

        return 0;
}
