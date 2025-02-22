#ifndef TEXT_H_
#define TEXT_H_

#include "UIObject.hpp"
#include "Color.hpp"
#include <string>
#include <utility>

namespace spic {

    /**
     * @brief Enumeration for different text alignments.
     * @spicapi
     */
    enum class Alignment {
        left,
        center,
        right
    };

    /**
     * @brief Class representing a piece of text which can be rendered.
     * @spicapi
     */
    class Text : public UIObject {
    private:
        std::string text;
        std::string font;
        int size;
        Alignment alignment;
        Color color;
    public:
        explicit Text(std::string font, std::string text,
                      const std::vector<std::shared_ptr<Component>> &components = {},
                      const std::string &parentName = "", const std::string &name = "", const std::string &tag = "",
                      Alignment alignment = Alignment::left, const Color &color = Color::black(), bool active = true,
                      int layer = 1, int size = 3, double width = 60, double height = 15);

        void TextString(const std::string &newText);

        [[nodiscard]] const std::string &TextString() const;

        void Font(const std::string &newFont);

        [[nodiscard]] const std::string &Font() const;

        void Size(int newSize);

        [[nodiscard]] int Size() const;

        void AlignmentValue(const spic::Alignment &newAlignment);

        [[nodiscard]] const spic::Alignment &AlignmentValue() const;

        void ColorValue(const spic::Color &newColor);

        [[nodiscard]] const spic::Color &ColorValue() const;
    };

}

#endif // TEXT_H_
