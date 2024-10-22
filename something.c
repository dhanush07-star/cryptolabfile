#include <gtk/gtk.h>
#include <stdlib.h>

static void compile_latex(const gchar *filename) {
    gchar *command = g_strdup_printf("pdflatex %s", filename);
    int status = system(command);  // Compile the LaTeX document

    if (status == -1) {
        g_print("Error compiling LaTeX document.\n");
    }

    g_free(command);
}

static void on_save_button_clicked(GtkButton *button, gpointer user_data) {
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(user_data);
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    
    const gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    
    // Create a file chooser dialog to save the file
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save File",
                                                    NULL,
                                                    GTK_FILE_CHOOSER_ACTION_SAVE,
                                                    "_Cancel", GTK_RESPONSE_CANCEL,
                                                    "_Save", GTK_RESPONSE_ACCEPT,
                                                    NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        g_file_set_contents(filename, text, -1, NULL);  // Save the content to the file
        compile_latex(filename);  // Compile the LaTeX file
        g_free(filename);
    }

    gtk_widget_destroy(dialog);  // Destroy the dialog
}

static void on_run_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("Run command would be executed here.\n");
}

static void on_compile_button_clicked(GtkButton *button, gpointer user_data) {
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(user_data);
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    
    const gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    
    // Create a temporary LaTeX file
    gchar *temp_filename = g_strdup_printf("temp.tex");
    g_file_set_contents(temp_filename, text, -1, NULL);  // Save the content to the temporary file
    compile_latex(temp_filename);  // Compile the LaTeX file
    g_free(temp_filename);
}

static void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *textview;
    GtkWidget *save_button;
    GtkWidget *run_button;
    GtkWidget *compile_button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "LaTeX Editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create buttons for actions
    save_button = gtk_button_new_with_label("Save and Compile");
    run_button = gtk_button_new_with_label("Run");
    compile_button = gtk_button_new_with_label("Compile");

    gtk_box_pack_start(GTK_BOX(vbox), save_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), run_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), compile_button, FALSE, FALSE, 0);

    textview = gtk_text_view_new();  // Create a new text view for editing
    gtk_box_pack_start(GTK_BOX(vbox), textview, TRUE, TRUE, 0);

    // Connect button clicks to their respective functions
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_button_clicked), gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview)));
    g_signal_connect(run_button, "clicked", G_CALLBACK(on_run_button_clicked), NULL);
    g_signal_connect(compile_button, "clicked", G_CALLBACK(on_compile_button_clicked), gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview)));

    gtk_widget_show_all(window);  // Show all widgets in the window
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.latexeditor", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);  // Clean up the application

    return status;
}
