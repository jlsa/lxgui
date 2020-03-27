#ifndef GUI_SFML_RENDERER_HPP
#define GUI_SFML_RENDERER_HPP

#include "lxgui/impl/gui_sfml_rendertarget.hpp"

#include <lxgui/utils.hpp>
#include <lxgui/gui_manager.hpp>

namespace sf
{
    class RenderWindow;
    class RenderTarget;
}

namespace gui {
namespace sfml
{
    /// SFML implementation of rendering
    class renderer : public gui::renderer_impl
    {
    public :

        /// Constructor.
        explicit renderer(sf::RenderWindow& mWindow);

        /// Destructor.
        ~renderer();

        /// Begins rendering on a particular render target.
        /** \param pTarget The render target (main screen if nullptr)
        */
        void begin(utils::refptr<gui::render_target> pTarget = nullptr) const override;

        /// Ends rendering.
        void end() const override;

        /// Renders a quad.
        /** \param mQuad The quad to render on the current render target
        *   \note This function is meant to be called between begin() and
        *         end() only.
        */
        virtual void render_quad(const quad& mQuad) const override;

        /// Renders a set of quads.
        /** \param mQuad     The base quad to use for rendering (material, blending, ...)
        *   \param lQuadList The list of the quads you want to render
        *   \note This function is meant to be called between begin() and
        *         end() only. It is always more efficient to call this method
        *         than calling render_quad repeatedly, as it allows to batch
        *         count reduction.
        */
        virtual void render_quads(const quad& mQuad, const std::vector<std::array<vertex,4>>& lQuadList) const override;

        /// Creates a new material from a texture file.
        /** \param sFileName The name of the file
        *   \param mFilter   The filtering to apply to the texture
        *   \return The new material
        *   \note Only PNG textures are supported by this implementation (parsed by libpng).
        */
        utils::refptr<gui::material> create_material(const std::string& sFileName,
            material::filter mFilter = material::filter::NONE) const override;

        /// Creates a new material from a plain color.
        /** \param mColor The color to use
        *   \return The new material
        */
        utils::refptr<gui::material> create_material(const color& mColor) const override;

        /// Creates a new material from a render target.
        /** \param pRenderTarget The render target from which to read the pixels
        *   \return The new material
        */
        utils::refptr<gui::material> create_material(utils::refptr<gui::render_target> pRenderTarget) const override;

        /// Creates a new render target.
        /** \param uiWidth  The width of the render target
        *   \param uiHeight The height of the render target
        */
        utils::refptr<gui::render_target> create_render_target(uint uiWidth, uint uiHeight) const override;

        /// Creates a new font.
        /** \param sFontFile The file from which to read the font
        *   \param uiSize    The requested size of the characters (in points)
        *   \note This implementation uses FreeType to load vector fonts and rasterize them.
        *         Bitmap fonts are not yet supported.
        */
        utils::refptr<gui::font> create_font(const std::string& sFontFile, uint uiSize) const override;

    private :

        sf::RenderWindow& mWindow_;

        mutable std::map<std::string, utils::wptr<gui::material>> lTextureList_;
        mutable std::map<std::string, utils::wptr<gui::font>>     lFontList_;

        mutable utils::refptr<gui::sfml::render_target> pCurrentTarget_;
        mutable sf::RenderTarget*                       pCurrentSFMLTarget_;
    };
}
}

#endif
