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
#include <gullinkambi/math>
#include <gullinkambi/gl>

namespace gullinkambi
{
	shader_manager::shader::~shader (void)
	{
		if (this->id != 0) {
			gl::program::destroy(this->id);
		}

		delete static_cast<std::function<void()>*>(this->function);
	}

	void
	shader_manager::shader::uniform (std::string name, math::vector<1, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::vector<2, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::vector<3, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::vector<4, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::vector<1, int> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::vector<2, int> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::vector<3, int> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::vector<4, int> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::matrix<2, 2, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::matrix<3, 3, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::matrix<4, 4, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::matrix<2, 3, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::matrix<3, 2, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::matrix<2, 4, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::matrix<4, 2, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::matrix<3, 4, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}

	void
	shader_manager::shader::uniform (std::string name, math::matrix<4, 3, float> data)
	{
		gl::program::uniform::set(gl::program::uniform::location(this->id, name), data);
	}
}
