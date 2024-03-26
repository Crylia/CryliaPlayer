#include "PageNavigator.h"
#include "SelectHandler.hpp"
#include "../../Tools/SvgToPixmap.hpp"

class SquareIcon : public QLabel {
public:
  QSize sizeHint( ) const override {
    QSize hint = QLabel::sizeHint( );
    int side = qMin(hint.width( ), hint.height( ));
    return QSize(side, side);
  }
};

PageNavigator::PageNavigator(QString text, QString icon, QString color, QWidget* parent)
  :m_text(new QLabel(text)), m_icon(new SquareIcon( )), m_color(color), m_iconPath(icon) {


  QSvgRenderer renderer(icon);

  QPixmap pixmap(32, 32);
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);
  renderer.render(&painter, pixmap.rect( ));

  painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
  painter.fillRect(pixmap.rect( ), color);
  painter.end( );

  m_icon->setPixmap(pixmap);

  m_icon->setObjectName("icon");

  setObjectName("PageNavigator");
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  setStyleSheet(R"(
      #PageNavigator{
        border: 4px solid #414141;
        border-radius: 6px;
        color: #E0E0E0;
      }
    )");

  QFont font = m_text->font( );
  font.setPointSize(16);
  font.setWeight(QFont::Bold);
  m_text->setFont(font);

  QHBoxLayout* layout = new QHBoxLayout(this);
  layout->addWidget(m_icon, 0, Qt::AlignLeft);
  layout->addWidget(m_text, 1, Qt::AlignLeft);

  connect(this, &QPushButton::clicked, [this, parent]( ) {
    SelectHandler* sh = SelectHandler::GetInstance( );

    sh->setSelected(this);
    emit SelectedChanged(this);
    });

  // Little hacky but thats how home is the default
  if (text == "Home") {
    SelectHandler* sh = SelectHandler::GetInstance( );

    sh->setSelected(this);
    emit SelectedChanged(this);
  }
}

void PageNavigator::unselect( ) {
  setStyleSheet(R"(
    #PageNavigator{
      border: 4px solid #414141;
      border-radius: 6px;
    }
  )");
}

void PageNavigator::select( ) {
  setStyleSheet(R"(
    #PageNavigator{
      border: 4px solid )" + m_color + R"(;
      border-radius: 6px;
    }
  )");
}

QString PageNavigator::GetText( ) {
  return m_text->text( );
}
