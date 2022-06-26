#include <MainWindow.hpp>
#include <gdk/gdkkeysyms.h>
#include <gdkmm.h>
#include <string.h>

MainWindow::MainWindow() {
  set_border_width(1);

  /* Get screen resolution in Linux, X11. */
  GdkRectangle workarea = {0};
  gdk_monitor_get_workarea(
    gdk_display_get_primary_monitor(gdk_display_get_default()),
    &workarea);

  m_screenw = workarea.width;
  m_screenh = workarea.height;

  /* Disable window's frame */
  Gtk::Window::set_decorated(false);
  Gtk::Window::set_app_paintable(true);

  /* Load Stylesheet (CSS) */
  this->LoadStylesheet();

  /* Initialize completion */
  ActivateCompletion(true);

  /* Set window's size */
  Gtk::Window::set_size_request(m_screenw / 3, 32);
  Gtk::Window::move((m_screenw / 2) - (m_screenw / 3) / 2, m_screenh / 2 - 64);
  Gtk::Window::set_skip_taskbar_hint(true);
  
  add(m_textbox);
  m_textbox.show();
  m_textbox.grab_focus();

  m_textbox.signal_key_press_event().connect(sigc::mem_fun(*this, &MainWindow::onKeyPress), false);
  m_textbox.signal_changed().connect(sigc::mem_fun(*this, &MainWindow::onEntryChanged), false);

  signal_draw().connect(sigc::mem_fun(*this, &MainWindow::onDraw));
  signal_screen_changed().connect(sigc::mem_fun(*this, &MainWindow::onScreenChanged));

  onScreenChanged(get_screen());
}

MainWindow::~MainWindow() {

}

void MainWindow::ActivateCompletion(bool init) {
  m_completion = Gtk::EntryCompletion::create();
  
  if (init) {
    completion_model = this->populateCompletion(true);
  } else {
    completion_model = this->populateCompletion(false);
  }

  m_model = Glib::wrap(completion_model);
  m_completion->set_model(m_model);
  m_completion->set_text_column(1);
  m_completion->set_minimum_key_length(0);
  m_completion->set_popup_completion(true);
  // m_completion->set_match_func(sigc::mem_fun(*this, &MainWindow::on_match));
  
  Gtk::CellRendererPixbuf pixbuf;
  m_completion->pack_start(pixbuf, true);
  m_completion->add_attribute(pixbuf, "icon_name", 0);

  gtk_entry_set_completion(GTK_ENTRY(m_textbox.gobj()), m_completion->gobj());
  gtk_entry_set_placeholder_text(GTK_ENTRY(m_textbox.gobj()), "Search Template");
}

GtkTreeModel* MainWindow::populateCompletion(bool init) {
  int max = get_config_int("max_displayed_item");

  ls_home();
  store = gtk_list_store_new(COL_NUM, G_TYPE_STRING, G_TYPE_STRING);
  GtkTreeIter iter;

  tfile_t c = root;
  string icon_name = "edit-copy";

  size_t iterator = 0;
  while (c != nullptr && iterator < max) {
    char tmp[512] = {};
    int i = 0;

    /* Before extension */
    while (c->data[i] != '.') {
      tmp[i] = c->data[i];
      i++;
    }

		gtk_list_store_append(store, &iter);
    gtk_list_store_set(
      store, &iter,
      COL_ICON, icon_name, 
      COL_NAME, tmp, 
      -1
    );

		c = c->next;
    iterator++;
	}

  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, COL_ICON, icon_name, COL_NAME, "(+) Add new template", -1);

  tfile_clear(&root);
  return GTK_TREE_MODEL(store);
}

bool MainWindow::onKeyPress(GdkEventKey* event) {
  if (event->keyval == GDK_KEY_Return && 
    strcmp(m_textbox.get_text().c_str(), "(+) Add new template") == 0) {
    m_formwindow = new FormWindow;

    m_textbox.set_text("");
    Gtk::Window::hide();
  } else {
    if (event->keyval == GDK_KEY_Return) {
      cstring filecontent = open(strdup(m_textbox.get_text().c_str()));

      GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
      gtk_clipboard_set_text(clipboard, filecontent, -1);
      Gtk::Window::hide();

      /* Reset textbox */
      m_textbox.set_text("");
    } else if (event->keyval == GDK_KEY_Escape) {
      Gtk::Window::hide();
      m_textbox.set_text("");
    }
  }

  return false;
}

void MainWindow::LoadStylesheet() {
  auto css = Gtk::CssProvider::create();
  string PATH = (string) malloc(strlen(get_home_directory()) + 1);
  strcpy(PATH, get_home_directory());

  /* Getting default css */
  strcat(PATH, "/");
  strcat(PATH, CONFIG_PATH);
  strcat(PATH, DEFAULT_CSS);

  if (!css->load_from_path(PATH)) {
    printf("Failed to load css\n");
    exit(1);
  }

  Glib::RefPtr<Gtk::CssProvider> provider = Gtk::CssProvider::create();
	provider->load_from_path(PATH);
	
  /* All context */
	Glib::RefPtr<Gtk::StyleContext> styleContext = Gtk::StyleContext::create();
	Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
	
	styleContext->add_provider_for_screen(screen, provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  /* Specific Context */
  Glib::RefPtr<Gtk::StyleContext> entryContext = m_textbox.get_style_context();

  entryContext->add_class("textbox");

  free(PATH);
}

bool MainWindow::onDraw(const Cairo::RefPtr<Cairo::Context>& ctx) {
  ctx->save();

  ctx->set_source_rgba(0, 0, 0, 0);
  ctx->set_operator(Cairo::OPERATOR_SOURCE);
  ctx->paint();
  ctx->restore();

  return Gtk::Window::on_draw(ctx);
}

void MainWindow::onScreenChanged(const Glib::RefPtr<Gdk::Screen>& previous_screen) {
  auto screen = get_screen();
  auto visual = screen->get_rgba_visual();

  if (!visual) {
    std::cout << "Your screen does not support alpha channels!" << std::endl;
  } else {
    std::cout << "Your screen supports alpha channels!" << std::endl;
    _SUPPORTS_ALPHA = TRUE;
  }

  setVisual(visual);
}

void MainWindow::setVisual(Glib::RefPtr<Gdk::Visual> visual) {
  gtk_widget_set_visual(GTK_WIDGET(gobj()), visual->gobj());
}

void MainWindow::resetCompletion() {
  this->ActivateCompletion(false);
}

bool MainWindow::on_match(const Glib::ustring& key, const Gtk::TreeModel::const_iterator& iter) {
  return true; // Always show
}

void MainWindow::onEntryChanged() {
  if (strcmp(m_textbox.get_text().c_str(), "(+) Add new template") == 0) {
    m_formwindow = new FormWindow;

    m_textbox.set_text("");
    Gtk::Window::hide();
  }
}
