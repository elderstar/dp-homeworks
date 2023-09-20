#include "text_decorator.h"
#include <string>
#include <iostream>


void Text::render(const std::string& data) const {
    std::cout << data;
}

void ItalicText::render(const std::string& data)  const {
    std::cout << "<i>";
    text_->render(data);
    std::cout << "</i>";
}

void BoldText::render(const std::string& data) const {
    std::cout << "<b>";
    text_->render(data);
    std::cout << "</b>";
}

void Paragraph::render(const std::string& data) const {
    std::cout << "<p>";
    text_->render(data);
    std::cout << "</p>";
}

void Reversed::render(const std::string& data) const {
    std::string new_data = data;
    std::reverse(new_data.begin(), new_data.end());
    text_->render(new_data);
}

void Link::render(const std::string& url, const std::string& data) const {
    std::cout << "<a href=\"" + url + "\">";
    text_->render(data);
    std::cout << "</a>";
}
