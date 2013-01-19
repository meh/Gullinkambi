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

#include <gullinkambi/maths/matrix>

#include <cmath>
#include <algorithm>

namespace gullinkambi
{
	namespace math
	{
		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::matrix (void)
		{
			_data      = new Type[Columns * Rows];
			_allocated = true;

			std::fill(_vectors, _vectors + Rows, nullptr);

			if (Columns == 2 && Rows == 2) {
				_data[0] = 1.0; _data[1] = 0.0;
				_data[2] = 0.0; _data[3] = 1.0;
			}
			else if (Columns == 3 && Rows == 3) {
				_data[0] = 1.0; _data[1] = 0.0; _data[2] = 0.0;
				_data[3] = 0.0; _data[4] = 1.0; _data[5] = 0.0;
				_data[6] = 0.0; _data[7] = 0.0; _data[8] = 1.0;
			}
			else if (Columns == 4 && Rows == 4) {
				_data[0]  = 1.0; _data[1]  = 0.0; _data[2]  = 0.0; _data[3]  = 0.0;
				_data[4]  = 0.0; _data[5]  = 1.0; _data[6]  = 0.0; _data[7]  = 0.0;
				_data[8]  = 0.0; _data[9]  = 0.0; _data[10] = 1.0; _data[11] = 0.0;
				_data[12] = 0.0; _data[13] = 0.0; _data[14] = 0.0; _data[15] = 1.0;
			}
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::matrix (const matrix<Columns, Rows, Type>& from)
		{
			_data      = new Type[Columns * Rows];
			_allocated = true;

			std::fill(_vectors, _vectors + Rows, nullptr);
			std::move(&from, &from + Columns * Rows, _data);
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::matrix (Type* data)
		{
			_data      = data;
			_allocated = false;

			std::fill(_vectors, _vectors + Rows, nullptr);
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::matrix (std::initializer_list<std::initializer_list<Type>> list) throw (std::invalid_argument)
		{
			if (list.size() != Rows) {
				throw std::invalid_argument("number of arguments doesn't match matrix rows");
			}

			_data      = new Type[Columns * Rows];
			_allocated = true;

			std::fill(_vectors, _vectors + Rows, nullptr);

			int i = 0;
			for (auto list : list) {
				if (list.size() != Columns) {
					throw std::invalid_argument("number of arguments doesn't match matrix columns");
				}

				int j = 0;
				for (auto value : list) {
					_data[i * Columns + j] = value;

					j++;
				}

				i++;
			}
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::~matrix (void)
		{
			if (_allocated) {
				delete[] _data;
			}

			for (int i = 0; i < Rows; i++) {
				if (_vectors[i]) {
					delete _vectors[i];
				}
			}
		}

		template <int Columns, int Rows, typename Type>
		vector<Columns, Type>&
		matrix<Columns, Rows, Type>::operator [] (int index)
		{
			if (index < 0 || index >= Rows) {
				throw std::out_of_range("index out of range");
			}

			if (!_vectors[index]) {
				_vectors[index] = new vector<Columns, Type>(_data + (Columns * index));
			}

			return *_vectors[index];
		}

		template <int Columns, int Rows, typename Type>
		Type*
		matrix<Columns, Rows, Type>::operator & (void) const
		{
			return _data;
		}
	}
}
