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

namespace gullinkambi
{
	template <class Function>
	shader_manager::shader::shader (std::vector<std::string> attrs,
	                                std::map<std::string, std::string> source,
	                                Function lambda)
	{
		this->id     = gl::program::make(source);
		this->source = source;

		for (GLuint i = 0; i < attrs.size(); i++) {
			auto& name = attrs[i];

			this->attributes[name] = i;
			gl::program::bind(this->id, i, name);
		}

		auto function = new decltype(to_function(lambda))(to_function(lambda));

		this->signature = &typeid(function);
		this->function  = static_cast<void*>(function);
	}

	template <typename ...Args>
	void
	shader_manager::shader::call (Args... args)
	{
		auto function = static_cast<std::function<void(shader_manager::shader&, Args...)>>(this->function);

		if (typeid(function) == *this->signature) {
			(*function)(*this, args...);
		}
		else {
			throw std::bad_typeid();
		}
	}
}
