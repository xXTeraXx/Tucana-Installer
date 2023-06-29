#include <stdio.h>
#include <gtk/gtk.h>
#include <glib.h>

// A struct because g_signal can only pass 1 argument to a connecting function
typedef struct{
  GtkWidget *center_box;
  GtkWidget *dropdown;
  GtkWidget *checkbox;
} box_and_dropdown;

box_and_dropdown args;

void de_image(GtkWidget *dropdown, gpointer data) {
  GtkWidget *image;
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
  GtkWidget *label;
  gtk_widget_set_size_request(box, 500, 281);

  
  // Attach the packing box to the center box
  image = gtk_picture_new_for_filename("/home/rahul/Music/162.jpg");
  gtk_widget_set_margin_end(image, 5);
  gtk_center_box_set_end_widget(args.center_box, box); 
  gtk_picture_set_content_fit(image, GTK_CONTENT_FIT_SCALE_DOWN);
  gtk_box_append(box, image);
  label = gtk_label_new("A simple and elegant desktop");
  gtk_box_append(box, label);
  // Get the selection
  guint selection = gtk_drop_down_get_selected(dropdown);
  // g_print("%d", selection);
  if (selection == 0) {
     // Gnome
     gtk_picture_set_filename(image, "/home/rahul/Music/162.jpg");
  }
  else if (selection == 1) {
  //KDE
  gtk_label_set_label(label, "A windows-like desktop based on qt5");

}
  
}


static void
activate (GtkApplication* app,
          gpointer        user_data)
{
   //Stuff
   //Vars
  GtkWidget *window;
  GtkWidget *center_box_vertical;
  GtkWidget *center_box_horizontal;
  // Another vertical centerbox to prevent the dropdown from moving when the images come in
  GtkWidget *child_center_box_vert;
  GtkWidget *grid;
  GtkWidget *dropdown;
  GtkWidget *image;
  GtkWidget *checkbox = gtk_check_button_new_with_label("Install Tucana Theme");
  char *  desktops[]  = {"Gnome", "KDE", "XFCE", "Cinnamon",  NULL};


  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 600);
  gtk_widget_show (window);
  // Create a grid 
  center_box_horizontal = gtk_center_box_new ();
  center_box_vertical = gtk_center_box_new();
  child_center_box_vert = gtk_center_box_new();
  
  gtk_orientable_set_orientation(GTK_CENTER_BOX (child_center_box_vert), GTK_ORIENTATION_VERTICAL);
  gtk_orientable_set_orientation(GTK_CENTER_BOX (center_box_vertical), GTK_ORIENTATION_VERTICAL);
  
  // Set child
  gtk_window_set_child (window, center_box_vertical);
  gtk_center_box_set_center_widget (center_box_vertical, center_box_horizontal);
  
  grid = gtk_grid_new();
  gtk_widget_set_margin_start(grid, 100);

  // Create widget

  gtk_center_box_set_start_widget (center_box_horizontal, child_center_box_vert);
  gtk_center_box_set_center_widget (child_center_box_vert, grid);
  gtk_center_box_set_end_widget (child_center_box_vert, grid);
  // Hide the checkbox widget at first
  dropdown = gtk_drop_down_new_from_strings(desktops); 
  // Define the struct type for the args
  args.center_box = center_box_horizontal;
  args.dropdown = dropdown;

  g_signal_connect (dropdown, "notify::selected", G_CALLBACK (de_image), NULL);
  gtk_grid_attach (grid, dropdown, 0, 4, 2, 1); 
 

  
  
  
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.tucana.de-chooser", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

