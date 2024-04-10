#include "NavButton.h"

void NavButton::setupButton( ) {
  QSvgRenderer renderer(iconPath);

  QPixmap pixmap(32, 32);
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);
  renderer.render(&painter, pixmap.rect( ));

  painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
  painter.fillRect(pixmap.rect( ), color);
  painter.end( );

  m_icon->setPixmap(pixmap);

  m_icon->setObjectName("icon");
  m_text->setObjectName("Text");

  setObjectName("NavButton");
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  setStyleSheet(R"(
      #NavButton{
        border: 4px solid #414141;
        border-radius: 6px;
      }
      #Text{
        color: #E0E0E0;
      }
    )");

  setCursor(Qt::PointingHandCursor);

  QFont font = m_text->font( );
  font.setPointSize(16);
  font.setWeight(QFont::Bold);
  m_text->setFont(font);

  QHBoxLayout* layout = new QHBoxLayout(this);
  layout->addWidget(m_icon, 0, Qt::AlignLeft);
  layout->addWidget(m_text, 1, Qt::AlignLeft);
  connect(this, &QPushButton::clicked, [this]( ) {
    emit SelectedChanged(this->page);
    });

  this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

}

NavButton::NavButton(QString text, QString color, QString icon_path, Page* page, QWidget* parent = nullptr) :
  QPushButton(parent),
  m_text(new QLabel(text)),
  m_color(new QString(color)),
  m_icon(new SquareIcon( )),
  page(page),
  iconPath(icon_path),
  color(color) {
  setupButton( );
}

NavButton::~NavButton( ) { }
