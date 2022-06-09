#include <MainWindow.hpp>

MainWindow::MainWindow() {
  set_border_width(1);

  /* Get screen resolution in Linux, X11. */
  Display* display = XOpenDisplay(NULL);
  Screen* screen = DefaultScreenOfDisplay(display);

  m_screenw = screen->width;
  m_screenh = screen->height;

  /* Disable window's frame */
  Gtk::Window::set_decorated(false);

  GtkEntryCompletion *completion;
  GtkTreeModel *completion_model;

  completion = gtk_entry_completion_new();
  gtk_entry_set_completion (GTK_ENTRY(m_textbox.gobj()), completion);

  completion_model = this->populateCompletion();
  gtk_entry_completion_set_model(completion, completion_model);
  
  gtk_entry_completion_set_text_column(completion, 0);

  /* Set window's size */
  Gtk::Window::set_size_request(m_screenw / 3, 32);
  Gtk::Window::move((m_screenw / 2) - (m_screenw / 3) / 2, m_screenh / 2 - 64);
  add(m_textbox);
  m_textbox.show();

  // m_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnButtonPressed));
}

MainWindow::~MainWindow() {

}

GtkTreeModel* MainWindow::populateCompletion() {
  ls_home();
  store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
  GtkTreeIter iter;

  tfile_t c = root;
	while (c != nullptr) {
		gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, COL_NAME, c->data, COL_PATH, c->data, -1);
		c = c->next;
	}

  return GTK_TREE_MODEL(store);
}