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

#include <gullinkambi/maths/vector>

#include <cmath>
#include <algorithm>

namespace gullinkambi
{
	namespace math
	{
		template <int Size, typename Type>
		vector<Size, Type>::vector (void)
		{
			_data      = new Type[Size];
			_allocated = true;
		}

		template <int Size, typename Type>
		vector<Size, Type>::vector (const vector<Size, Type>& from)
		{
			_data      = new Type[Size];
			_allocated = true;

			std::move(&from, &from + Size, _data);
		}

		template <int Size, typename Type>
		vector<Size, Type>::vector (std::initializer_list<Type> list) throw (std::invalid_argument)
		{
			if (list.size() != Size) {
				throw std::invalid_argument("number of arguments doesn't match vector size");
			}

			_data      = new Type[Size];
			_allocated = true;

			int i = 0;
			for (auto value : list) {
				_data[i++] = value;
			}
		}

		template <int Size, typename Type>
		vector<Size, Type>::vector (Type* data)
		{
			_data      = data;
			_allocated = false;
		}

		template <int Size, typename Type>
		vector<Size, Type>::~vector (void)
		{
			if (_allocated) {
				delete _data;
			}
		}

		template <int Size, typename Type>
		vector<Size, Type>&
		vector<Size, Type>::operator = (const Type* data)
		{
			std::move(data, data + Size, _data);

			return *this;
		}
		
		template <int Size, typename Type>
		vector<Size, Type>&
		vector<Size, Type>::operator = (std::initializer_list<Type> list) throw (std::invalid_argument)
		{
			if (list.size() != Size) {
				throw std::invalid_argument("number of arguments doesn't match vector size");
			}

			int i = 0;
			for (auto value : list) {
				_data[i++] = value;
			}

			return *this;
		}

		template <int Size, typename Type>
		Type&
		vector<Size, Type>::operator [] (int index) const
		{
			return _data[index];
		}

		template <int Size, typename Type>
		vector<Size, Type>
		vector<Size, Type>::operator + (const vector<Size, Type>& other)
		{
			vector<Size, Type> result;

			for (int i = 0; i < Size; i++) {
				result[i] = _data[i] + other[i];
			}

			return result;
		}

		template <int Size, typename Type>
		vector<Size, Type>&
		vector<Size, Type>::operator += (const vector<Size, Type>& other)
		{
			for (int i = 0; i < Size; i++) {
				_data[i] += other[i];
			}

			return *this;
		}

		template <int Size, typename Type>
		vector<Size, Type>
		vector<Size, Type>::operator - (const vector<Size, Type>& other)
		{
			vector<Size, Type> result;

			for (int i = 0; i < Size; i++) {
				result[i] = _data[i] - other[i];
			}

			return result;
		}

		template <int Size, typename Type>
		vector<Size, Type>&
		vector<Size, Type>::operator -= (const vector<Size, Type>& other)
		{
			for (int i = 0; i < Size; i++) {
				_data[i] -= other[i];
			}

			return *this;
		}

		template <int Size, typename Type>
		vector<Size, Type>
		vector<Size, Type>::operator % (Type scale)
		{
			vector<Size, Type> result;

			for (int i = 0; i < Size; i++) {
				result[i] = _data[i] * scale;
			}

			return result;
		}

		template <int Size, typename Type>
		vector<Size, Type>&
		vector<Size, Type>::operator %= (Type scale)
		{
			for (int i = 0; i < Size; i++) {
				_data[i] *= scale;
			}

			return *this;
		}

		template <int Size, typename Type>
		vector<Size, Type>
		vector<Size, Type>::operator ! (void)
		{
			return this % (1.0 / ~this);
		}

		template <int Size, typename Type>
		Type
		vector<Size, Type>::operator ~ (void)
		{
			Type result = 0;

			for (int i = 0; i < Size; i++) {
				result += _data[i] * _data[i];
			}

			return sqrt(result);
		}

		template <int Size, typename Type>
		Type
		vector<Size, Type>::operator >> (vector<Size, Type>& other)
		{
			Type result = 0;

			for (int i = 0; i < Size; i++) {
				Type current = _data[i] - other[i];

				result += current * current;
			}

			return sqrt(result);
		}

		template <int Size, typename Type>
		Type*
		vector<Size, Type>::operator & (void) const
		{
			return _data;
		}
	}
}
