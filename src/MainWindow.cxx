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

  completion = gtk_entry_completion_new();
  gtk_entry_set_completion (GTK_ENTRY(m_textbox.gobj()), completion);
  gtk_entry_set_placeholder_text(GTK_ENTRY(m_textbox.gobj()), "Search Template");

  completion_model = this->populateCompletion();
  gtk_entry_completion_set_model(completion, completion_model);
  gtk_entry_completion_set_text_column(completion, 0);
  gtk_entry_completion_set_minimum_key_length(completion, 0);

  /* Set window's size */
  Gtk::Window::set_size_request(m_screenw / 3, 32);
  Gtk::Window::move((m_screenw / 2) - (m_screenw / 3) / 2, m_screenh / 2 - 64);
  Gtk::Window::set_skip_taskbar_hint(true);
  
  add(m_textbox);
  m_textbox.show();
  m_textbox.grab_focus();

  // m_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnButtonPressed));
  m_textbox.signal_key_press_event().connect(sigc::mem_fun(*this, &MainWindow::onKeyPress), false);
  signal_draw().connect(sigc::mem_fun(*this, &MainWindow::onDraw));
  signal_screen_changed().connect(sigc::mem_fun(*this, &MainWindow::onScreenChanged));

  onScreenChanged(get_screen());
}

MainWindow::~MainWindow() {

}

GtkTreeModel* MainWindow::populateCompletion() {
  ls_home();
  store = gtk_list_store_new(1, G_TYPE_STRING);
  GtkTreeIter iter;

  tfile_t c = root;
	while (c != nullptr) {
    char tmp[512] = {};
    int i = 0;

    while (c->data[i] != '.') {
      tmp[i] = c->data[i];
      i++;
    }

		gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, COL_NAME, tmp, -1);
		c = c->next;
	}

  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, COL_NAME, "(+) Add new template", -1);

  return GTK_TREE_MODEL(store);
}

bool MainWindow::onKeyPress(GdkEventKey* event) {
  if (strcmp(m_textbox.get_text().c_str(), "(+) Add new template") == 0) {
    // m_formwindow = new FormWindow;
    // m_formwindow->show();
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
  string PATH = (string) HOME;
  
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
