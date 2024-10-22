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
                                                    ("_Cancel"), GTK_RESPONSE_CANCEL,
                                                    ("_Save"), GTK_RESPONSE_ACCEPT,
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
    // Placeholder for running the LaTeX document (if applicable)
    g_print("Run command would be executed here.\n");
}

static void on_compile_button_clicked(GtkButton *button, gpointer user_data) {
    // Placeholder for compiling the LaTeX document
    // Ideally, this could be expanded to compile the currently loaded document
    g_print("Compile command would be executed here.\n");
}

static void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *textview;
    GtkWidget *toolbar;
    GtkWidget *save_button;
    GtkWidget *run_button;
    GtkWidget *compile_button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "LaTeX Editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    toolbar = gtk_toolbar_new();
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    save_button = gtk_tool_button_new(NULL, "Save");
    gtk_tool_button_set_icon_name(save_button, "document-save");
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_button_clicked), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), save_button, -1);

    run_button = gtk_tool_button_new(NULL, "Run");
    gtk_tool_button_set_icon_name(run_button, "execute");
    g_signal_connect(run_button, "clicked", G_CALLBACK(on_run_button_clicked), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), run_button, -1);

    compile_button = gtk_tool_button_new(NULL, "Compile");
    gtk_tool_button_set_icon_name(compile_button, "document-save");
    g_signal_connect(compile_button, "clicked", G_CALLBACK(on_compile_button_clicked), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), compile_button, -1);

    textview = gtk_text_view_new();  // Create a new text view for editing
    gtk_box_pack_start(GTK_BOX(vbox), textview, TRUE, TRUE, 0);

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
