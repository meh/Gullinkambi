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

#include <gullinkambi/shader_manager>
#include "shader_manager/shader.tpp"

namespace gullinkambi
{
	template <typename Function>
	shader_manager::shader*
	shader_manager::make (std::vector<std::string> attributes,
	                      std::map<std::string, std::string> source,
	                      Function lambda)
	{
		return new shader(attributes, source, lambda);
	}

	template <typename Function>
	shader_manager::shader&
	shader_manager::add (std::string name,
	                     std::vector<std::string> attributes,
	                     std::map<std::string, std::string> source,
	                     Function lambda)
	{
		auto current = make(attributes, source, lambda);

		_shaders[name] = current;

		return *current;
	}

	template <typename ...Args>
	shader_manager::shader&
	shader_manager::use (std::string name, Args... args)
	{
		auto current = _shaders.at(name);

		current->call(args...);

		return *current;
	}
}
