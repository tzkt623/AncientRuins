#pragma once



namespace tezcat
{
	template <int DIMENSION, typename TYPE>
	class Tuple
	{
	public:

		Tuple();
		Tuple(const Tuple& tuple);
		~Tuple();

		inline operator const TYPE* () const;
		inline operator TYPE* ();
		inline const TYPE& operator[] (int i) const;
		inline TYPE& operator[] (int i);

		Tuple& operator= (const Tuple& tuple);

		bool operator== (const Tuple& tuple) const;
		bool operator!= (const Tuple& tuple) const;
		bool operator<  (const Tuple& tuple) const;
		bool operator<= (const Tuple& tuple) const;
		bool operator>  (const Tuple& tuple) const;
		bool operator>= (const Tuple& tuple) const;

	protected:
		TYPE m_Tuple[DIMENSION];
	};

	template <int DIMENSION, typename TYPE>
	Tuple<DIMENSION, TYPE>::Tuple()
	{

	}
	
	template <int DIMENSION, typename TYPE>
	Tuple<DIMENSION, TYPE>::Tuple(const Tuple& tuple)
	{
		for (int i = 0; i < DIMENSION; ++i)
		{
			m_Tuple[i] = tuple.m_Tuple[i];
		}
	}
	
	template <int DIMENSION, typename TYPE>
	Tuple<DIMENSION, TYPE>::~Tuple()
	{
	}
	
	template <int DIMENSION, typename TYPE>
	inline Tuple<DIMENSION, TYPE>::operator const TYPE* () const
	{
		return m_Tuple;
	}
	
	template <int DIMENSION, typename TYPE>
	inline Tuple<DIMENSION, TYPE>::operator TYPE* ()
	{
		return m_Tuple;
	}
	
	template <int DIMENSION, typename TYPE>
	inline const TYPE& Tuple<DIMENSION, TYPE>::operator[] (int i) const
	{
		return m_Tuple[i];
	}
	
	template <int DIMENSION, typename TYPE>
	inline TYPE& Tuple<DIMENSION, TYPE>::operator[] (int i)
	{
		return m_Tuple[i];
	}
	
	template <int DIMENSION, typename TYPE>
	Tuple<DIMENSION, TYPE>& Tuple<DIMENSION, TYPE>::operator= (const Tuple& tuple)
	{
		for (int i = 0; i < DIMENSION; ++i)
		{
			m_Tuple[i] = tuple.m_Tuple[i];
		}
		return *this;
	}
	
	template <int DIMENSION, typename TYPE>
	bool Tuple<DIMENSION, TYPE>::operator== (const Tuple& tuple) const
	{
		for (int i = 0; i < DIMENSION; ++i)
		{
			if (m_Tuple[i] != tuple.m_Tuple[i])
			{
				return false;
			}
		}
		return true;
	}
	
	template <int DIMENSION, typename TYPE>
	bool Tuple<DIMENSION, TYPE>::operator!= (const Tuple& tuple) const
	{
		for (int i = 0; i < DIMENSION; ++i)
		{
			if (m_Tuple[i] != tuple.m_Tuple[i])
			{
				return true;
			}
		}
		return false;
	}
	
	template <int DIMENSION, typename TYPE>
	bool Tuple<DIMENSION, TYPE>::operator< (const Tuple& tuple) const
	{
		for (int i = 0; i < DIMENSION; ++i)
		{
			if (m_Tuple[i] < tuple.m_Tuple[i])
			{
				return true;
			}

			if (m_Tuple[i] > tuple.m_Tuple[i])
			{
				return false;
			}
		}
		return false;
	}
	
	template <int DIMENSION, typename TYPE>
	bool Tuple<DIMENSION, TYPE>::operator<= (const Tuple& tuple) const
	{
		for (int i = 0; i < DIMENSION; ++i)
		{
			if (m_Tuple[i] < tuple.m_Tuple[i])
			{
				return true;
			}

			if (m_Tuple[i] > tuple.m_Tuple[i])
			{
				return false;
			}
		}
		return true;
	}
	
	template <int DIMENSION, typename TYPE>
	bool Tuple<DIMENSION, TYPE>::operator> (const Tuple& tuple) const
	{
		for (int i = 0; i < DIMENSION; ++i)
		{
			if (m_Tuple[i] > tuple.m_Tuple[i])
			{
				return true;
			}

			if (m_Tuple[i] < tuple.m_Tuple[i])
			{
				return false;
			}
		}
		return false;
	}
	
	template <int DIMENSION, typename TYPE>
	bool Tuple<DIMENSION, TYPE>::operator>= (const Tuple& tuple) const
	{
		for (int i = 0; i < DIMENSION; ++i)
		{
			if (m_Tuple[i] > tuple.m_Tuple[i])
			{
				return true;
			}

			if (m_Tuple[i] < tuple.m_Tuple[i])
			{
				return false;
			}
		}
		return true;
	}
}