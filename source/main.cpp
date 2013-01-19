/** Copyleft (ɔ) meh. - http://meh.schizofreni.co
 *
 * This file is part of Gullinkambi - https://github.com/meh/Gullinkambi
 *
 * Gullinkambi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Gullinkambi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Gullinkambi. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <libconfig.h++>

#include <gullinkambi/gl>
#include <gullinkambi/math>
#include <gullinkambi/shader_manager>

using namespace libconfig;
using namespace gullinkambi;

int
main (int argc, char* argv[])
{
	Config config;

	try {
		config.readFile("gullinkambi.cfg");
	}
	catch (const FileIOException& e) {
		std::cerr << "could not read configuration file" << std::endl;

		return EXIT_FAILURE;
	}
	catch (const ParseException& e)
	{
		std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine()
		          << " - " << e.getError() << std::endl;

		return EXIT_FAILURE;
	}

	gl::window::create(&argc, argv,
		{ { "size", { 800, 600 } } }, config.lookup("title"));

	gl::extensions::setup();

	shader_manager shaders;
	shaders.add("identity", {"vertex"}, {
		{ "vertex", R"(
			attribute vec4 vertex;

			void
			main (void)
			{
				gl_Position = vertex;
			}
		)" },

		{ "fragment", R"(
			uniform vec4 color;

			void
			main (void)
			{
				gl_FragColor = color;
			}
		)" } },
	[](shader_manager::shader& shader, math::vector<4> color) {
		shader.uniform("color", color);
	});

	shaders.add("flat", {"vertex"}, {
		{ "vertex", R"(
			uniform mat4 matrix;
			attribute vec4 vertex;

			void
			main (void)
			{
				gl_Position = matrix * vertex;
			}
		)" },

		{ "fragment", R"(
			uniform vec4 color;

			void
			main (void)
			{
				gl_FragColor = color;
			}
		)" } },
	[](shader_manager::shader& shader, math::matrix<4, 4> transform, math::vector<4> color) {
		shader.uniform("matrix", transform);
		shader.uniform("color", color);
	});

	gl::window::callback("resize", [&](int width, int height) {
		gl::viewport(width, height);
	});

	gl::window::callback("render", [&]() {
		gl::buffers::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		gl::buffers::swap();
	});

	gl::window::loop([&]() {
		gl::clear::color(0.0, 0.0, 0.0);
	});

	return EXIT_SUCCESS;
}
