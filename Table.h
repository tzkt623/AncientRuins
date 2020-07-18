#pragma once

#include "Tupe.h"

namespace tezcat
{
	template <int NUMROWS, int NUMCOLS, typename TYPE>
	class Table
	{
	public:

		Table();
		Table(const Table& table);
		~Table();

		inline operator const TYPE* () const;
		inline operator TYPE* ();
		inline const TYPE* operator[] (int row) const;
		inline TYPE* operator[] (int row);
		inline const TYPE& operator() (int row, int col) const;
		inline TYPE& operator() (int row, int col);

		void setRow(int row, const Tuple<NUMCOLS, TYPE>& tuple);
		Tuple<NUMCOLS, TYPE> getRow(int row) const;
		void setColumn(int col, const Tuple<NUMROWS, TYPE>& tuple);
		Tuple<NUMROWS, TYPE> getColumn(int col) const;

		int begin() { return 0; }
		int end() { return NUMENTRIES; }
		int rows() { return NUMROWS; }
		int cols() { return NUMCOLS; }

		Table& operator = (const Table& table);

		bool operator == (const Table& table) const;
		bool operator != (const Table& table) const;
		bool operator <  (const Table& table) const;
		bool operator <= (const Table& table) const;
		bool operator >  (const Table& table) const;
		bool operator >= (const Table& table) const;

	protected:
		enum { NUMENTRIES = NUMROWS * NUMCOLS };
		TYPE m_Entry[NUMENTRIES];
	};


	template <int NUMROWS, int NUMCOLS, typename TYPE>
	Table<NUMROWS, NUMCOLS, TYPE>::Table()
	{

	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	Table<NUMROWS, NUMCOLS, TYPE>::Table(const Table& table)
	{
		for (int i = 0; i < NUMENTRIES; ++i)
		{
			m_Entry[i] = table.m_Entry[i];
		}
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	Table<NUMROWS, NUMCOLS, TYPE>::~Table()
	{
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	inline Table<NUMROWS, NUMCOLS, TYPE>::operator const TYPE* () const
	{
		return m_Entry;
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	inline Table<NUMROWS, NUMCOLS, TYPE>::operator TYPE* ()
	{
		return m_Entry;
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	inline const TYPE* Table<NUMROWS, NUMCOLS, TYPE>::operator[] (int row) const
	{
		return &m_Entry[NUMCOLS*row];
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	inline TYPE* Table<NUMROWS, NUMCOLS, TYPE>::operator[] (int row)
	{
		return &m_Entry[NUMCOLS*row];
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	inline const TYPE& Table<NUMROWS, NUMCOLS, TYPE>::operator() (int row, int col)
		const
	{
		return m_Entry[col + NUMCOLS*row];
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	inline TYPE& Table<NUMROWS, NUMCOLS, TYPE>::operator() (int row, int col)
	{
		return m_Entry[col + NUMCOLS*row];
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	void Table<NUMROWS, NUMCOLS, TYPE>::setRow(int row, const Tuple<NUMCOLS, TYPE>& tuple)
	{
		for (int c = 0, i = NUMCOLS*row; c < NUMCOLS; ++c, ++i)
		{
			m_Entry[i] = tuple[c];
		}
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	Tuple<NUMCOLS, TYPE> Table<NUMROWS, NUMCOLS, TYPE>::getRow(int row) const
	{
		Tuple<NUMROWS, TYPE> result;
		for (int c = 0, i = NUMCOLS*row; c < NUMCOLS; ++c, ++i)
		{
			result[c] = m_Entry[i];
		}
		return result;
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	void Table<NUMROWS, NUMCOLS, TYPE>::setColumn(int col, const Tuple<NUMROWS, TYPE>& tuple)
	{
		for (int r = 0, i = col; r < NUMROWS; ++r, i += NUMCOLS)
		{
			m_Entry[i] = tuple[r];
		}
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	Tuple<NUMROWS, TYPE> Table<NUMROWS, NUMCOLS, TYPE>::getColumn(int col) const
	{
		Tuple<NUMCOLS, TYPE> result;
		for (int r = 0, i = col; r < NUMROWS; ++r, i += NUMCOLS)
		{
			result[r] = m_Entry[i];
		}
		return result;
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	Table<NUMROWS, NUMCOLS, TYPE>& Table<NUMROWS, NUMCOLS, TYPE>::operator = (const Table& table)
	{
		for (int i = 0; i < NUMENTRIES; i++)
		{
			m_Entry[i] = table.m_Entry[i];
		}
		return *this;
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	bool Table<NUMROWS, NUMCOLS, TYPE>::operator == (const Table& table) const
	{
		for (int i = 0; i < NUMENTRIES; ++i)
		{
			if (m_Entry[i] != table.m_Entry[i])
			{
				return false;
			}
		}
		return true;
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	bool Table<NUMROWS, NUMCOLS, TYPE>::operator != (const Table& table) const
	{
		for (int i = 0; i < NUMENTRIES; ++i)
		{
			if (m_Entry[i] != table.m_Entry[i])
			{
				return true;
			}
		}
		return false;
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	bool Table<NUMROWS, NUMCOLS, TYPE>::operator < (const Table& table) const
	{
		for (int i = 0; i < NUMENTRIES; ++i)
		{
			if (m_Entry[i] < table.m_Entry[i])
			{
				return true;
			}

			if (m_Entry[i] > table.m_Entry[i])
			{
				return false;
			}
		}
		return false;
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	bool Table<NUMROWS, NUMCOLS, TYPE>::operator <= (const Table& table) const
	{
		for (int i = 0; i < NUMENTRIES; ++i)
		{
			if (m_Entry[i] < table.m_Entry[i])
			{
				return true;
			}

			if (m_Entry[i] > table.m_Entry[i])
			{
				return false;
			}
		}
		return true;
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	bool Table<NUMROWS, NUMCOLS, TYPE>::operator > (const Table& table) const
	{
		for (int i = 0; i < NUMENTRIES; ++i)
		{
			if (m_Entry[i] > table.m_Entry[i])
			{
				return true;
			}

			if (m_Entry[i] < table.m_Entry[i])
			{
				return false;
			}
		}
		return false;
	}

	template <int NUMROWS, int NUMCOLS, typename TYPE>
	bool Table<NUMROWS, NUMCOLS, TYPE>::operator >= (const Table& table) const
	{
		for (int i = 0; i < NUMENTRIES; ++i)
		{
			if (m_Entry[i] > table.m_Entry[i])
			{
				return true;
			}

			if (m_Entry[i] < table.m_Entry[i])
			{
				return false;
			}
		}
		return true;
	}
}

