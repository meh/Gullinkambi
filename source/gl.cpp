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

#include <gullinkambi/gl>

#include <iostream>

#include <map>
#include <string>
#include <functional>

namespace gullinkambi
{
	namespace gl
	{
		namespace window
		{
			void create (int* argc, char* argv[],
			             std::map<std::string, std::vector<int>> attributes,
			             std::string name) throw (std::invalid_argument)
			{
				glutInit(argc, argv);
				glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

				if (attributes.find("size") != attributes.end()) {
					if (attributes["size"].size() != 2) {
						throw std::invalid_argument("size must have two elements");
					}

					glutInitWindowSize(attributes["size"].at(0), attributes["size"].at(1));
				}

				if (attributes.find("position") != attributes.end()) {
					if (attributes["size"].size() != 2) {
						throw std::invalid_argument("size must have two elements");
					}

					glutInitWindowPosition(attributes["position"].at(0), attributes["position"].at(1));
				}

				glutCreateWindow(name.c_str());
			}

			namespace callbacks
			{
				std::map<std::string, void*> closures;

				template <typename Signature>
				static
				std::function<Signature>&
				closure (std::string name)
				{
					if (closures.find(name) == closures.end()) {
						throw std::invalid_argument("unknown callback");
					}

					return *static_cast<std::function<Signature>*>(closures[name]);
				}

				void
				resize (int width, int height)
				{
					closure<void(int, int)>("resize")(width, height);
				}

				void
				render (void)
				{
					closure<void(void)>("render")();
				}
			}
		}

		namespace extensions
		{
			void
			setup (void) throw (std::runtime_error)
			{
				GLenum err = glewInit();

				if (err != GLEW_OK) {
					throw std::runtime_error((const char*) glewGetErrorString(err));
				}
			}
		}

		void
		viewport (GLsizei width, GLsizei height)
		{
			glViewport(0, 0, width, height);
		}

		void
		viewport (GLint x, GLint y, GLsizei width, GLsizei height)
		{
			glViewport(x, y, width, height);
		}

		namespace clear
		{
			void
			color (GLclampf red, GLclampf green, GLclampf blue)
			{
				glClearColor(red, green, blue, 1.0);
			}

			void
			color (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
			{
				glClearColor(red, green, blue, alpha);
			}
		}

		namespace buffers
		{
			void
			swap (void)
			{
				glutSwapBuffers();
			}

			void
			clear (GLbitfield mask)
			{
				glClear(mask);
			}
		}

		namespace program
		{
			namespace shader
			{
				GLuint
				create (GLenum value)
				{
					return glCreateShader(value);
				}

				void
				destroy (GLuint id)
				{
					glDeleteShader(id);
				}

				GLuint
				load (GLuint id, std::string source)
				{
					GLchar* string[1] = { (GLchar*) source.c_str() };

					glShaderSource(id, 1, (const GLchar**) string, NULL);

					return id;
				}

				GLuint
				compile (GLuint id)
				{
					glCompileShader(id);

					GLint status;
					glGetShaderiv(id, GL_COMPILE_STATUS, &status);
					if (status == GL_FALSE) {
						throw std::runtime_error("shader compilation failed");
					}

					return id;
				}

				GLuint
				make (GLenum value, std::string source)
				{
					GLuint shader = create(value);

					load(shader, source);

					try {
						compile(shader);
					}
					catch (const std::runtime_error& e) {
						destroy(value);

						throw e;
					}

					return shader;
				}
			}

			namespace uniform
			{
				GLint
				location (GLuint program, std::string name)
				{
					return glGetUniformLocation(program, name.c_str());
				}

				void
				set (GLint location, GLfloat a)
				{
					glUniform1f(location, a);
				}

				void
				set (GLint location, GLfloat a, GLfloat b)
				{
					glUniform2f(location, a, b);
				}

				void
				set (GLint location, GLfloat a, GLfloat b, GLfloat c)
				{
					glUniform3f(location, a, b, c);
				}

				void
				set (GLint location, GLfloat a, GLfloat b, GLfloat c, GLfloat d)
				{
					glUniform4f(location, a, b, c, d);
				}

				void
				set (GLint location, GLint a)
				{
					glUniform1i(location, a);
				}

				void
				set (GLint location, GLint a, GLint b)
				{
					glUniform2i(location, a, b);
				}

				void
				set (GLint location, GLint a, GLint b, GLint c)
				{
					glUniform3i(location, a, b, c);
				}

				void
				set (GLint location, GLint a, GLint b, GLint c, GLint d)
				{
					glUniform4i(location, a, b, c, d);
				}

				void
				set (GLint location, math::matrix<2, 2, float> data)
				{
					glUniformMatrix2fv(location, 1, GL_TRUE, &data);
				}

				void
				set (GLint location, math::matrix<3, 3, float> data)
				{
					glUniformMatrix3fv(location, 1, GL_TRUE, &data);
				}

				void
				set (GLint location, math::matrix<4, 4, float> data)
				{
					glUniformMatrix4fv(location, 1, GL_TRUE, &data);
				}

				void
				set (GLint location, math::matrix<2, 3, float> data)
				{
					glUniformMatrix2x3fv(location, 1, GL_TRUE, &data);
				}

				void
				set (GLint location, math::matrix<3, 2, float> data)
				{
					glUniformMatrix3x2fv(location, 1, GL_TRUE, &data);
				}

				void
				set (GLint location, math::matrix<2, 4, float> data)
				{
					glUniformMatrix2x4fv(location, 1, GL_TRUE, &data);
				}

				void
				set (GLint location, math::matrix<4, 2, float> data)
				{
					glUniformMatrix4x2fv(location, 1, GL_TRUE, &data);
				}

				void
				set (GLint location, math::matrix<3, 4, float> data)
				{
					glUniformMatrix3x4fv(location, 1, GL_TRUE, &data);
				}

				void
				set (GLint location, math::matrix<4, 3, float> data)
				{
					glUniformMatrix4x3fv(location, 1, GL_TRUE, &data);
				}
			}

			GLuint
			make (std::map<std::string, std::string> source)
			{
				static std::map<std::string, GLenum> enums = {
					{ "vertex",   GL_VERTEX_SHADER },
					{ "fragment", GL_FRAGMENT_SHADER },
					{ "geometry", GL_GEOMETRY_SHADER },

					{ "tessellation:evaluation", GL_TESS_EVALUATION_SHADER },
					{ "tessellation:control",    GL_TESS_CONTROL_SHADER }
				};

				std::map<std::string, GLuint> id;

				for (auto entry : source) {
					id[entry.first] = shader::make(enums[entry.first], entry.second);
				}

				return make(id);
			}

			GLuint
			make (std::map<std::string, GLuint> id)
			{
				GLuint program = glCreateProgram();

				for (auto entry : id) {
					glAttachShader(program, entry.second);
				}

				glLinkProgram(program);

				for (auto entry : id) {
					shader::destroy(entry.second);
				}

				GLint status;
				glGetProgramiv(program, GL_LINK_STATUS, &status);
				if (status == GL_FALSE) {
					destroy(program);

					throw std::runtime_error("shader linking failed");
				}

				return program;
			}

			void
			destroy (GLuint program)
			{
				glDeleteProgram(program);
			}

			void
			bind (GLuint program, GLuint index, std::string name)
			{
				glBindAttribLocation(program, index, name.c_str());
			}
		}
	}
}
