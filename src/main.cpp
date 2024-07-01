#include "../include/main.h"

typedef struct
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button[18];
} Calc;
GtkWidget *box;
using namespace std;
static void activate(GtkApplication *app, gpointer data);
static void btn_click(GtkWidget *w, gpointer data);
static char sequence[100];
int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;
    app = gtk_application_new("com.salimkhani.GtkCalc", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect
    (
        app,
        "activate",
        G_CALLBACK(activate),
        NULL
    );
    status = g_application_run
    (
        G_APPLICATION(app),
        argc,
        argv
    );
    g_object_unref(app);
    return status;
}

static void activate(GtkApplication *app, gpointer data)
{
    Calc calc;
    GMenu *menu_bar;

    GMenuItem *about_menu_item;
    GMenuItem *quit_menu_item;
    GtkIconTheme *icon_theme;
    menu_bar = g_menu_new();
    about_menu_item = g_menu_item_new("About", "app.about");
    quit_menu_item = g_menu_item_new("Quit","app.quit");
    g_menu_append_item(menu_bar, about_menu_item);
    g_menu_append_item(menu_bar, quit_menu_item);
    icon_theme = gtk_icon_theme_get_for_display (gdk_display_get_default ());
    gtk_icon_theme_add_search_path(icon_theme,"/usr/bin/GtkCalc_Files/"); 

    if(gtk_icon_theme_has_icon(icon_theme,"GtkCalc")!=1)
       {
        // manage error
       }
    
    GtkWidget *window = calc.window;
    window = gtk_application_window_new(app);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_icon_name("GtkCalc");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
    gtk_window_set_title(GTK_WINDOW(window), "Calc");
    gtk_widget_add_css_class(window, "flat");

    calc.grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), calc.grid);
    box = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(box), FALSE);

    for (int i = 0; i < 10; i++)
    {
        char buff[50];
        sprintf(buff, "%d", i);
        calc.button[i] = gtk_button_new_with_label(buff);
    }
    calc.button[10] = gtk_button_new_with_label(".");
    calc.button[11] = gtk_button_new_with_label("+");
    calc.button[12] = gtk_button_new_with_label("-");
    calc.button[13] = gtk_button_new_with_label("*");
    calc.button[14] = gtk_button_new_with_label("/");
    calc.button[15] = gtk_button_new_with_label("C");
    calc.button[16] = gtk_button_new_with_label("=");
    calc.button[17] = gtk_button_new_with_label("<-");

    gtk_grid_attach(GTK_GRID(calc.grid), box, 0,0,12,1);

    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[15], 0,1,4,5);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[17], 4,1,4,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[14], 8,1,4,1);

    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[7], 4,2,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[8], 6,2,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[9], 8,2,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[13], 10,2,2,1);


    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[4], 4,3,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[5], 6,3,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[6], 8,3,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[12], 10,3,2,1);

    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[1], 4,4,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[2], 6,4,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[3], 8,4,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[11], 10,4,2,1);

    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[10], 4,5,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[0], 6,5,2,1);
    gtk_grid_attach(GTK_GRID(calc.grid), calc.button[16], 8,5,4,1);

    for (size_t i = 0; i < 18; i++)
    {
        g_signal_connect(calc.button[i], "clicked", G_CALLBACK(btn_click), (gpointer)sequence);
    }
    
    gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL(menu_bar));
    gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE);
    gtk_window_present(GTK_WINDOW(window));
    g_object_unref(about_menu_item);
    g_object_unref(quit_menu_item);
}


static void btn_click(GtkWidget *w, gpointer data)
{
    const gchar *text = gtk_button_get_label(GTK_BUTTON(w));
    if(!strcmp(text, "="))
    {
        data = str_replace((char *)data, "+", " + ");
        data = str_replace((char *)data, "-", " - ");
        data = str_replace((char *)data, "*", " * ");
        data = str_replace((char *)data, "/", " / ");
        double res = evaluateExpression((char *)data);
        ((char *)data)[0] = '\0';
        if(isInt(res))
        {
            sprintf((char *)data, "%d ", (int)res);
        }
        else{
            sprintf((char *)data, "%0.4f ", res);
        }
    }
    else if(!strcmp(text, "C"))
    {
        ((char *)data)[0] = '\0';
    }
    else if(!strcmp(text, "<-"))
    {
        ((char *)data)[strlen(((char *)data))-1] = '\0';
    }
    else{
        strcat((char*)data, text);
    }
    gtk_editable_set_text(GTK_EDITABLE(box), (char*)data);
}