#ifndef iLiveVector_h_
#define iLiveVector_h_

#include <iLiveCommon.h>

namespace ilive
{
	template<typename T, bool NeedConstruct=true, bool NeedDestruct=true>
	class Vector
	{
	public:
		typedef T*			iterator;
		typedef const T*	const_iterator;
		typedef T			value_type;

	public:
		Vector();
		Vector(const Vector<T, NeedConstruct, NeedDestruct>& rhs);
		Vector(int capacity);
		Vector(int size, const T& fillValue);
		Vector(int size, const T& fillValue, int capacity);
		~Vector();

		T&					operator [] (int idx);
		const T&			operator [] (int idx) const;
		Vector<T, NeedConstruct, NeedDestruct>& operator =  (const Vector<T, NeedConstruct, NeedDestruct>& rhs);
		bool				operator == (const Vector<T, NeedConstruct, NeedDestruct>& rhs) const;
		bool				operator != (const Vector<T, NeedConstruct, NeedDestruct>& rhs) const;
		
		T&					at(int idx);
		int					size() const;
		void				resize(int size);
		void				resize(int size, const T& val);
		int					capacity() const;
		void				reserve(int size);

		void				swap(Vector<T, NeedConstruct, NeedDestruct>& rhs);
		void				push_back(const T& rhs);
		void				pop_back();

		bool				empty() const;
		void				clear();
		void				trim();//make the capacity==size
		iterator			find(const T& val);
		const_iterator		find(const T& val) const;

		void				insert(int idx, const T& ele);
 		void				insert(iterator it, const T& ele);
 		void				insert(int idx, const T& ele, int num);
 		void				insert(iterator it, const T& ele, int num);
 		void				insert(int idx, const Vector<T, NeedConstruct, NeedDestruct>& vec);
 		void				insert(iterator it, const Vector<T, NeedConstruct, NeedDestruct>& vec );
 		void				insert(int idx, const T* pArr, int num );
 		void				insert(iterator it, const T* pArr, int num );
		
		void				erase(int idx, int num = 1);
		void				erase(iterator where);
		void				erase(iterator begin, iterator end);

 		iterator			begin();
 		const_iterator		begin() const;
 		iterator			end();
 		const_iterator		end() const;

		T&					front();
		const T&			front() const;
		T&					back();
		const T&			back() const;

		T*					data();
		const T*			data() const;

	protected:
		void				_copy(const Vector<T, NeedConstruct, NeedDestruct>& rhs);
		void				_cleanup();
		void				_realloc(int capacity);
		void				_grow();
		void				_move(int from, int to);

	protected:
		int			m_size;
		int			m_capacity;
		T*			m_pData;
	};

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline
	Vector<T, NeedConstruct, NeedDestruct>::Vector()
	:m_size(0)
	,m_capacity(0)
	,m_pData(NULL)
	{

	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline
	Vector<T, NeedConstruct, NeedDestruct>::Vector(const Vector<T, NeedConstruct, NeedDestruct>& rhs)
	:m_size(0)
	,m_capacity(0)
	,m_pData(NULL)
	{
		_copy(rhs);
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline
	Vector<T, NeedConstruct, NeedDestruct>::Vector(int capacity)
	:m_size(0)
	,m_capacity(capacity)
	,m_pData(NULL)
	{
		assert(capacity >= 0);
		if(m_capacity > 0)
		{
			m_pData = reinterpret_cast<T*>( iliveMalloc( m_capacity * sizeof(T) ) );
		}
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline
	Vector<T, NeedConstruct, NeedDestruct>::Vector(int size, const T& fillValue)
	:m_size(size)
	,m_capacity(size)
	,m_pData(NULL)
	{
		assert(size >= 0);
		if(size > 0)
		{
			m_pData = reinterpret_cast<T*>( iliveMalloc( m_capacity * sizeof(T) ) );
			for( int i = 0; i < m_size; ++i )
			{
				new(m_pData+i) T(fillValue);
			}
		}
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline
	Vector<T, NeedConstruct, NeedDestruct>::Vector(int size, const T& fillValue, int capacity)
	:m_size(size)
	,m_capacity(capacity)
	,m_pData(NULL)
	{
		assert( capacity >= size );
		assert( size >= 0 );
		if(m_capacity >= 0)
		{
			m_pData = reinterpret_cast<T*>( iliveMalloc( m_capacity * sizeof(T) ) );
			for(int i = 0; i < m_size; ++i)
			{
				new(m_pData+i) T(fillValue);
			}
		}
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline
	Vector<T, NeedConstruct, NeedDestruct>::~Vector()
	{
		_cleanup();
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline T&
	Vector<T, NeedConstruct, NeedDestruct>::operator [] (int idx)
	{
		assert(idx>=0 && idx<m_size);
		return m_pData[idx];
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline const T&
	Vector<T, NeedConstruct, NeedDestruct>::operator [] (int idx) const
	{
		assert(idx>=0 && idx<m_size);
		return m_pData[idx];
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline Vector<T, NeedConstruct, NeedDestruct>&
	Vector<T, NeedConstruct, NeedDestruct>::operator = (const Vector<T, NeedConstruct, NeedDestruct>& rhs)
	{
		if(this == &rhs) return *this;
		
		if(m_capacity >= rhs.m_size)
		{
			int i = 0;
			if(NeedConstruct)
			{
				for(; i < rhs.m_size && i < this->m_size; ++i )
				{
					m_pData[i] = rhs.m_pData[i]; //调用=操作符
				}
				for(; i < rhs.m_size; ++i)
				{
					new(m_pData+i) T(rhs.m_pData[i]); //调用拷贝构造
				}
			}
			else
			{
				iliveMemCpy( m_pData, rhs.m_pData, rhs.m_size * sizeof(T) );
				i = rhs.m_size;
			}

			if(NeedDestruct)
			{
				for(; i < m_size; ++i)//本Vector比rhs的size大时，后面多余的元素需要释放掉;
				{
					m_pData[i].~T();
				}
			}
			m_size = rhs.m_size;
		}
		else
		{
			_cleanup();
			_copy(rhs);
		}

		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline bool
	Vector<T, NeedConstruct, NeedDestruct>::operator == (const Vector<T, NeedConstruct, NeedDestruct>& rhs) const
	{
		if(this == &rhs)
		{
			return true;
		}
		if(this->m_size == rhs.m_size)
		{
			for(int i = 0; i < m_size; ++i)
			{
				if( !(m_pData[i] == rhs.m_pData[i]) ) //调用==操作符
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline bool
	Vector<T, NeedConstruct, NeedDestruct>::operator != (const Vector<T, NeedConstruct, NeedDestruct>& rhs) const
	{
		return !( (*this) == rhs );
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline T&
	Vector<T, NeedConstruct, NeedDestruct>::at(int idx)
	{
		assert( idx >= 0 && idx < m_size );
		return m_pData[idx];
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline int
	Vector<T, NeedConstruct, NeedDestruct>::size() const
	{
		return m_size;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::resize(int size)
	{
		resize( size, T() );//调用无参数的构造函数
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::resize(int size, const T& val)
	{
		assert( size >= 0 );
		if( size > m_capacity )
		{
			_realloc( size );
		}

		if(NeedDestruct)
		{
			for(int i=size; i<m_size; ++i)
			{
				m_pData[i].~T();
			}
		}
		if ( NeedConstruct )
		{
			for(int i=m_size; i<size; ++i)
			{
				new(m_pData+i) T(val);
			}
		}
		else
		{
			for(int i=m_size; i<size; ++i)
			{
				iliveMemCpy( m_pData+i, &val, sizeof(T) );
			}
		}

		m_size = size;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline int
	Vector<T, NeedConstruct, NeedDestruct>::capacity() const
	{
		return m_capacity;
	}

	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::reserve(int size)
	{
		if ( size > m_capacity )
		{
			_realloc(size);
		}
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::swap(Vector<T, NeedConstruct, NeedDestruct>& rhs)
	{
		iliveSwap<int>(m_size, rhs.m_size);
		iliveSwap<int>(m_capacity, rhs.m_capacity);
		iliveSwap<T*>(m_pData, rhs.m_pData);
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::push_back(const T& rhs)
	{
		if( m_size >= m_capacity )
		{
			_grow();
		}
		new(m_pData+m_size) T(rhs);
		++m_size;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::pop_back()
	{
		assert( m_size > 0 );
		--m_size;
		if(NeedDestruct)
		{
			m_pData[m_size].~T();
		}
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline bool
	Vector<T, NeedConstruct, NeedDestruct>::empty() const
	{
		return m_size==0;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::clear()
	{
		if( 0 != m_size )
		{
			if( NeedDestruct )
			{
				for(int i=0; i<m_size; ++i)
				{
					m_pData[i].~T();
				}
			}
			m_size = 0;
		}
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::trim()
	{
		if (m_capacity == m_size) return;

		T* pData = reinterpret_cast<T*>( iliveMalloc( m_size * sizeof(T) ) );
		if(NeedConstruct)
		{
			for(int i=0; i<m_size; ++i)
			{
				new(pData+i) T(m_pData[i]);
			}
		}
		else
		{
			iliveMemCpy(pData, m_pData, m_size * sizeof(T) );
		}
		if(NeedDestruct)
		{
			for(int i=0; i<m_size; ++i)
			{
				m_pData[i].~T();
			}
		}
		iliveFree(m_pData);
		iliveSwap(pData, m_pData);
		m_capacity = m_size;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline typename Vector<T, NeedConstruct, NeedDestruct>::iterator
	Vector<T, NeedConstruct, NeedDestruct>::find(const T& val)
	{
		for(int i=0; i<m_size; ++i)
		{
			if (m_pData[i] == val )
			{
				return m_pData+i;
			}
		}
		return m_pData + m_size;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline typename Vector<T, NeedConstruct, NeedDestruct>::const_iterator
	Vector<T, NeedConstruct, NeedDestruct>::find(const T& val) const
	{
		for(int i=0; i<m_size; ++i)
		{
			if (m_pData[i] == val )
			{
				return m_pData+i;
			}
		}
		return m_pData + m_size;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::insert(int idx, const T& ele)
	{
		assert( idx>=0 && idx<=m_size );
		if( m_size >= m_capacity )
		{
			_grow();
		}
		if( idx != m_size )
		{
			_move(idx, idx+1);
		}
		if( NeedConstruct )
		{
			new(m_pData+idx) T(ele);
		}
		else
		{
			iliveMemCpy( m_pData+idx, &ele, sizeof(T) );
		}
		++m_size;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::insert(iterator it, const T& ele)
	{
		int idx = it - m_pData;
		insert(idx, ele);
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::insert(int idx, const T& ele, int num)
	{
		assert( num>0 && idx>=0 && idx<=m_size );
		while( m_size + num > m_capacity )
		{
			_grow();
		}
		if(idx != m_size)
		{
			_move(idx, idx+num);
		}
		if( NeedConstruct )
		{
			for(int i=idx; i<idx+num; ++i)
			{
				new(m_pData+i) T(ele);
			}
		}
		else
		{
			for(int i=idx; i<idx+num; ++i)
			{
				iliveMemCpy( m_pData+i, &ele, sizeof(T) );
			}
		}
		m_size += num;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::insert(iterator it, const T& ele, int num)
	{
		int idx = it - m_pData;
		insert(idx, ele, num);
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::insert(int idx, const Vector<T, NeedConstruct, NeedDestruct>& vec)
	{
		assert( idx>=0 && idx<=m_size );
		while( m_size + vec.size() > m_capacity )
		{
			_grow();
		}
		if(idx != m_size)
		{
			_move( idx, idx+vec.size() );
		}
		if( NeedConstruct )
		{
			for( int i=0; i<vec.size(); ++i )
			{
				new(m_pData+idx+i) T(vec[i]);
			}
		}
		else
		{
			iliveMemCpy( m_pData+idx, arr.m_pData, sizeof(T) * arr.size() );
		}
		m_size += arr.size();
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::insert(iterator it, const Vector<T, NeedConstruct, NeedDestruct>& vec )
	{
		int idx = it - m_pData;
		insert(idx, vec);
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::insert(int idx, const T* pArr, int num )
	{
		assert( num>0 && idx>=0 && idx<=m_size );
		while( m_size+num > m_capacity )
		{
			_grow();
		}
		if( idx != m_size )
		{
			_move(idx, idx+num);
		}
		if( NeedConstruct )
		{
			for( int i=0; i<num; ++i )
			{
				new(m_pData+idx+i) T(pArr[i]);
			}
		}
		else
		{
			iliveMemCpy( m_pData+idx, pArr, sizeof(T) * num );
		}
		m_size += num;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::insert(iterator it, const T* pArr, int num )
	{
		int idx = it - m_pData;
		insert(idx, pArr, num);
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::erase(int idx, int num/* = 1*/)
	{
		assert( num>0 && idx>=0 && idx<=m_size );
		if( idx == m_size )
		{
			return;
		}
		if( idx + num > m_size )
		{
			num = m_size - idx;
		}
		if(NeedDestruct)
		{
			for(int i=0; i<num; ++i)
			{
				m_pData[idx+i].~T();
			}
		}
		_move(idx+num, idx);
		m_size -= num;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::erase(iterator where)
	{
		int idx = where - m_pData;
		erase(idx);
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::erase(iterator begin, iterator end)
	{
		int idx = begin - m_pData;
		int num = end - begin;
		erase(idx, num);
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline typename Vector<T, NeedConstruct, NeedDestruct>::iterator
	Vector<T, NeedConstruct, NeedDestruct>::begin()
	{
		return m_pData;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline typename Vector<T, NeedConstruct, NeedDestruct>::const_iterator
	Vector<T, NeedConstruct, NeedDestruct>::begin() const
	{
		return m_pData;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline typename Vector<T, NeedConstruct, NeedDestruct>::iterator
	Vector<T, NeedConstruct, NeedDestruct>::end()
	{
		return m_pData + m_size;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline typename Vector<T, NeedConstruct, NeedDestruct>::const_iterator
	Vector<T, NeedConstruct, NeedDestruct>::end() const
	{
		return m_pData + m_size;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline T&
	Vector<T, NeedConstruct, NeedDestruct>::front()
	{
		assert( m_size > 0 );
		return *m_pData;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline const T&
	Vector<T, NeedConstruct, NeedDestruct>::front() const
	{
		assert( m_size > 0 );
		return *m_pData;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline T&
	Vector<T, NeedConstruct, NeedDestruct>::back()
	{
		assert( m_size > 0 );
		return m_pData[m_size-1];
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline const T&
	Vector<T, NeedConstruct, NeedDestruct>::back() const
	{
		assert( m_size > 0 );
		return m_pData[m_size-1];
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline T*
	Vector<T, NeedConstruct, NeedDestruct>::data()
	{
		return m_pData;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline const T*
	Vector<T, NeedConstruct, NeedDestruct>::data() const
	{
		return m_pData;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::_copy(const Vector<T, NeedConstruct, NeedDestruct>& rhs)
	{
		assert( 0 == m_size && 0 == m_capacity && NULL == m_pData );
		m_size		= rhs.m_size;
		m_capacity	= rhs.m_size;
		if( m_size > 0 )
		{
			m_pData	= reinterpret_cast<T*>( iliveMalloc(m_size * sizeof(T)) );
			if(NeedConstruct)
			{
				for(int i=0; i<m_size; i++)
				{
					new(m_pData+i) T( rhs.m_pData[i] );//调用T类型的拷贝构造函数
				}
			}
			else
			{
				iliveMemCpy( m_pData, rhs.m_pData, m_size * sizeof(T) );
			}
		}
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::_cleanup()
	{
		if(NeedDestruct)
		{
			for(int i=0; i<m_size; ++i)
			{
				m_pData[i].~T(); //调用析构函数(调试发现,基本类型会跳过此行);
			}
		}
		iliveFree(m_pData);
		m_pData		= NULL;
		m_size		= 0;
		m_capacity	= 0;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::_realloc(int capacity)
	{
		T* pData = reinterpret_cast<T*>( iliveMalloc( capacity * sizeof(T) ) );
		if(NeedConstruct)
		{
			for(int i=0; i<m_size; ++i)
			{
				new(pData+i) T(m_pData[i]);
			}
		}
		else
		{
			iliveMemCpy( pData, m_pData, m_size * sizeof(T) );
		}
		if(NeedDestruct)
		{
			for(int i=0; i<m_size; i++)
			{
				m_pData[i].~T();
			}
		}
		iliveFree(m_pData);
		m_pData		= pData;
		m_capacity	= capacity;
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::_grow()
	{
		int growStep = m_capacity + 3*m_capacity/8 + 32;
		_realloc( growStep + m_capacity );
	}

	//------------------------------------------------------------------------
	template<typename T, bool NeedConstruct, bool NeedDestruct> inline void
	Vector<T, NeedConstruct, NeedDestruct>::_move(int from, int to)
	{
		iliveMemMove( (char*)(m_pData+to), (char*)(m_pData+from), sizeof(T)*(m_size-from) );
	}

}

#endif //iLiveVector_h_