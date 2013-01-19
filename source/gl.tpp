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

#include <gullinkambi/utility>
#include <gullinkambi/gl>

#include <map>
#include <string>

namespace gullinkambi
{
	namespace gl
	{
		namespace window
		{
			template <typename Function>
			void
			loop (Function setup)
			{
				setup();
				glutMainLoop();
			}

			namespace callbacks
			{
				extern std::map<std::string, void*> closures;
			}

			template<typename Function>
			void
			callback (std::string name, Function lambda)
			{
				using namespace callbacks;

				if (name == "resize") {
					glutReshapeFunc(callbacks::resize);
				}
				else if (name == "render") {
					glutDisplayFunc(callbacks::render);
				}
				else {
					throw std::invalid_argument("unknown callback");
				}

				if (closures.find(name) != closures.end()) {
					throw std::invalid_argument("the callback already exists");
				}

				closures[name] = new decltype(to_function(lambda))(to_function(lambda));
			}
		}
	}
}
