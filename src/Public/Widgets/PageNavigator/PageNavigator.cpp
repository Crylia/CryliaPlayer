#include "PageNavigator.h"
#include "SelectHandler.hpp"

PageNavigator::PageNavigator(QString text, QString icon, QWidget* parent)
  :m_text(new QLabel(text)), m_icon(new QLabel( )) {

  m_icon->setPixmap(icon);

  setObjectName("PageNavigator");
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  setStyleSheet(R"(
      #PageNavigator{
        border: 4px solid #414141;
        border-radius: 8px;
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

  connect(this, &QPushButton::clicked, [this]( ) {
    SelectHandler* sh = SelectHandler::GetInstance( );

    sh->setSelected(this);
    });

}

void PageNavigator::unselect( ) {
  setStyleSheet(R"(
      #PageNavigator{
        border: 4px solid #414141;
        border-radius: 6px;
        color: #E0E0E0;
      }
    )");
}

void PageNavigator::select( ) {
  setStyleSheet(R"(
      #PageNavigator{
        border: 4px solid #81D4FA;
        border-radius: 6px;
        color: #E0E0E0;
      }
    )");
}
