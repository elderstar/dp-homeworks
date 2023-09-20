#include <string>
#include <iostream>
#include "text_decorator.h"

int main() {
    auto text_block = new ItalicText(new BoldText(new Text()));
    text_block->render("Hello world");

    std::cout << std::endl;

    auto p_text_block = new Paragraph(new Text());
    p_text_block->render("String in Paragraph");

    std::cout << std::endl;

    auto l_text_block = new Link(new Text());
    l_text_block->render("netology.ru", "Netology");
}