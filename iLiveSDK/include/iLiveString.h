#ifndef iLiveString_h_
#define iLiveString_h_

#include <iLiveCommon.h>

namespace ilive
{
	template<typename T>
	class TStringBase
	{
		struct Rep
		{
			T*			getData();
			const T*	getData() const;
			T*			refCopy();
			int			getSize() const;
			void		unRef();
			void		freeMemory();
			Rep*		clone() const;
			static Rep*	Create(int len);

			int			m_length;
			int			m_capacity;
			int			m_references;
		};
	public:
		TStringBase();
		TStringBase(const T* str);
		TStringBase(T ch, int len);
		TStringBase(const T* buf, int len);
		TStringBase(const TStringBase<T>& oth);
		~TStringBase();

		TStringBase<T>&		operator=(const TStringBase<T>& rhs);
		TStringBase<T>&		operator=(const T* rhs);
		TStringBase<T>		operator+(const TStringBase<T>& rhs) const;
		T					operator[](int idx) const;
		
		bool				operator==(const TStringBase<T>& rhs) const;
		bool				operator==(const T* rhs) const;
		bool				operator!=(const TStringBase<T>& rhs) const;
		bool				operator!=(const T* rhs) const;
		bool				operator> (const TStringBase<T>& rhs) const;
		bool				operator>=(const TStringBase<T>& rhs) const;
		bool				operator< (const TStringBase<T>& rhs) const;
		bool				operator<=(const TStringBase<T>& rhs) const;
		TStringBase<T>&		operator+=(const TStringBase<T>& str);
		TStringBase<T>&		operator+=(const T* str);
		TStringBase<T>&		operator+=(T ch);

		int					length() const;
		int					capacity() const;
		void				clear();
		bool				empty() const;
		const T*			c_str() const;
		const T*			data() const; //等效于c_str();
		void				reserve(int size);//将容量capacity设置为至少size
		void				format(const T* format, ...);
		void				vformat(const T* format, va_list argptr);

		void				swap(TStringBase<T>& oth);
		TStringBase<T>		substr(int index, int num = ILIVE_INVALID_INDEX) const;
		TStringBase<T>&		erase(int idx, int len = 1);
		TStringBase<T>&		setchar(int idx, T ch);

		int					find(const TStringBase<T>& str, int nStart = 0) const;
		int					find(const T* sz, int nStart = 0, int len = ILIVE_INVALID_INDEX) const;
		int					find(T ch, int nStart = 0) const;
		int					rfind(const TStringBase<T>& str, int nStart = ILIVE_INVALID_INDEX) const;
		int					rfind(const T* sz, int nStart = ILIVE_INVALID_INDEX,	int len = ILIVE_INVALID_INDEX) const;
		int					rfind(T ch, int nStart = ILIVE_INVALID_INDEX) const;

		TStringBase<T>&		insert(int idx, const TStringBase<T>& str);
		TStringBase<T>&		insert(int idx, const TStringBase<T>& str, int nStart, int len = ILIVE_INVALID_INDEX);
		TStringBase<T>&		insert(int idx, const T* sz);
		TStringBase<T>&		insert(int idx, const T* sz, int len);
		TStringBase<T>&		insert(int idx, T ch, int len = 1);
 
		TStringBase<T>&		replace(int idx, int n, const TStringBase<T>& str);//将idx开始处的n个字符替换为str的内容;
		TStringBase<T>&		replace(int idx, int n, const TStringBase<T>& str, int sidx, int sn);
		TStringBase<T>&		replace(int idx, int n, const T* str);
		TStringBase<T>&		replace(int idx, int n, const T* str, int sidx, int sn);
		TStringBase<T>&		replace(int idx, int n, T ch, int cn);

		TStringBase<T>&		append(const TStringBase<T>& str);
		TStringBase<T>&		append(const TStringBase<T>& str, int idx, int n);
		TStringBase<T>&		append(const T* str);
		TStringBase<T>&		append(const T* str, int idx, int n);
		TStringBase<T>&		append(T ch);
		TStringBase<T>&		append(T ch, int n);

		int					compare(const TStringBase<T>& oth) const;
		int					compare(const T* oth) const;
		int					compareIgnoreCase(const TStringBase<T>& oth) const;
		int					compareIgnoreCase(const T* oth) const;

		bool				beginwith(const TStringBase<T>& s) const;
		bool				beginwith(const T* s) const;
		bool				endwith(const TStringBase<T>& s) const;
		bool				endwith(const T* s) const;
	
		TStringBase<T>&		tolower();
		TStringBase<T>&		toupper();

		friend bool			operator == (const T* lhs, const TStringBase& rhs)
		{
			return rhs.compare(lhs?lhs:"")==0;
		}

		friend bool			operator != (const T* lhs, const TStringBase& rhs)
		{
			return !(lhs==rhs);
		}

		static TStringBase<T>	Format(const T* format, ...);

	protected:
		explicit		TStringBase(Rep* r);
		Rep&			_getRep() const;
		static Rep&		_GetEmptyStringRep();
	
	protected:
		T*						m_string;
		static unsigned char	ms_emptyStringRep[sizeof(int)+sizeof(int)+sizeof(int)+sizeof(T)];
	};

	typedef TStringBase<char>	String;
	typedef TStringBase<wchar>	WString;

	//------------------------------------------------------------------------
	template<typename T> inline T*
	TStringBase<T>::Rep::getData()
	{
		return reinterpret_cast<T*>( this+1 );
	}

	//------------------------------------------------------------------------
	template<typename T> inline const T*
	TStringBase<T>::Rep::getData() const
	{
		return reinterpret_cast<const T*>( this+1 );
	}

	//------------------------------------------------------------------------
	template<typename T> inline T*
	TStringBase<T>::Rep::refCopy()
	{
		++m_references;
		return getData();
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::Rep::getSize() const
	{
		return sizeof( Rep ) + sizeof(T) * (m_capacity + 1);
	}

	//------------------------------------------------------------------------
	template<typename T> inline void
	TStringBase<T>::Rep::unRef()
	{
		if( --m_references < 0 )
		{
			if ( this != reinterpret_cast<Rep*>(ms_emptyStringRep) )
			{
				freeMemory();
			}
		}
	}

	//------------------------------------------------------------------------
	template<typename T> inline void
	TStringBase<T>::Rep::freeMemory()
	{
		assert( this != reinterpret_cast<Rep*>(ms_emptyStringRep) );
		iliveFree(this);
	}

	//------------------------------------------------------------------------
	template<typename T> inline typename TStringBase<T>::Rep*
	TStringBase<T>::Rep::clone() const
	{
		Rep* r = reinterpret_cast<Rep*>( iliveMalloc( getSize() ) );
		r->m_length		= m_length;
		r->m_capacity	= m_capacity;
		r->m_references	= 0;
		iliveMemCpy( r->getData(), getData(), m_length+1 );
		return r;
	}

	//------------------------------------------------------------------------
	template<typename T> inline typename TStringBase<T>::Rep*
	TStringBase<T>::Rep::Create(int len)
	{
		unsigned int scapacity = len;
		if(scapacity < ILIVE_MININUM_STRING_CAPACITY)
		{
			scapacity = ILIVE_MININUM_STRING_CAPACITY;
		}
		Rep* r = reinterpret_cast<Rep*>( iliveMalloc( sizeof(Rep)+sizeof(T)*(scapacity+1) ) );
		r->m_length		= len;
		r->m_capacity	= scapacity;
		r->m_references	= 0;
		return r;
	}

	//静态成员变量
	//------------------------------------------------------------------------
	template<typename T> unsigned char TStringBase<T>::ms_emptyStringRep[sizeof(int)+sizeof(int)+sizeof(int)+sizeof(T)] = {0};//静态变量自动初始化为0

	//静态成员函数
	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>
	TStringBase<T>::Format(const T* format, ...)
	{
		TStringBase<T> str;
		va_list argptr;
		va_start(argptr, format);
		str.vformat(format, argptr);
		va_end(argptr);
		return str;
	}

	//------------------------------------------------------------------------
	template<typename T> inline typename TStringBase<T>::Rep&
	TStringBase<T>::_GetEmptyStringRep()
	{
		return *reinterpret_cast<Rep*>(ms_emptyStringRep);
	}

	//普通成员函数
	//------------------------------------------------------------------------
	template<typename T> inline
	TStringBase<T>::TStringBase()
	{
		m_string = _GetEmptyStringRep().refCopy();
	}

	//------------------------------------------------------------------------
	template<typename T> inline
	TStringBase<T>::TStringBase(typename TStringBase<T>::Rep* r)
	:m_string(r->getData())
	{

	}

	//------------------------------------------------------------------------
	template<typename T> inline
	TStringBase<T>::TStringBase( const T* str )
	{
		if( NULL != str && str[0] != 0 )
		{
			int slen = iliveStrLen(str);
			m_string = Rep::Create(slen)->getData();
			iliveMemCpy( m_string, str, slen+1 );
		}
		else
		{
			m_string = _GetEmptyStringRep().refCopy();
		}
	}

	//------------------------------------------------------------------------
	template<typename T> inline
	TStringBase<T>::TStringBase( T ch, int len )
	{
		assert( len >= 0 );
		m_string = Rep::Create(len)->getData();
		iliveMemSet(m_string, ch, len);
		m_string[len] = 0;
	}

	//------------------------------------------------------------------------
	template<typename T> inline
	TStringBase<T>::TStringBase( const T* buf, int len )
	{
		if(buf==NULL || len==0)
		{
			m_string = _GetEmptyStringRep().refCopy();
			return;
		}
		int slen = iliveStrLen(buf);
		if (len<0)
		{
			len = slen;
		}
		assert(len >= 0);
		m_string = Rep::Create(len)->getData();
		iliveMemCpy(m_string, buf, len);
		m_string[len] = 0;
	}

	//------------------------------------------------------------------------
	template<typename T> inline
	TStringBase<T>::TStringBase( const TStringBase<T>& oth )
	{
		m_string = oth._getRep().refCopy();
	}

	//------------------------------------------------------------------------
	template<typename T> inline
	TStringBase<T>::~TStringBase()
	{
		_getRep().unRef();
	}

	//------------------------------------------------------------------------
	template<typename T> inline	TStringBase<T>&
	TStringBase<T>::operator = (const TStringBase<T>& rhs)
	{
		_getRep().unRef();		
		m_string = rhs._getRep().refCopy();
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::operator = (const T* rhs)
	{
		if( rhs != NULL && 0 != *rhs)
		{
			int slen = iliveStrLen(rhs);
			if( _getRep().m_capacity < slen || _getRep().m_references > 0 )
			{
				_getRep().unRef();
				m_string = Rep::Create(slen)->getData();
			}
			iliveMemCpy(m_string, rhs, slen+1);
			_getRep().m_length = slen;
		}
		else
		{
			_getRep().unRef();
			m_string = _GetEmptyStringRep().refCopy();
		}
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>
	TStringBase<T>::operator + (const TStringBase<T>& rhs) const
	{
		int len = length() + rhs.length();
		Rep* r	= Rep::Create(len);
		T* p	= r->getData();
		iliveMemCpy( p, c_str(), length() );
		iliveMemCpy( p+length(), rhs.c_str(), rhs.length()+1 );
		return TStringBase<T>(r);
	}

	//------------------------------------------------------------------------
	template<typename T> inline T
	TStringBase<T>::operator [] (int idx) const
	{
		return m_string[idx];
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::operator == (const TStringBase<T>& rhs) const
	{
		return length()==rhs.length()?compare(rhs)==0:false;
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::operator == (const T* rhs) const
	{
		return compare(rhs?rhs:"") == 0;
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::operator != (const TStringBase<T>& rhs) const
	{
		return !(*this == rhs);
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::operator != (const T* rhs) const
	{
		return !(*this == rhs);
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::operator > (const TStringBase<T>& rhs) const
	{
		return compare(rhs) > 0;
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::operator >= (const TStringBase<T>& rhs) const
	{
		return compare(rhs) >= 0;
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::operator < (const TStringBase<T>& rhs) const
	{
		return compare(rhs) < 0;
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::operator <= (const TStringBase<T>& rhs) const
	{
		return compare(rhs) <= 0;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::operator += (const TStringBase<T>& str)
	{
		return append(str);
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::operator += (const T* str)
	{
		return append(str);
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::operator += (T ch)
	{
		return append(ch, 1);
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::length() const
	{
		return _getRep().m_length;
	}

	template<typename T> int
	TStringBase<T>::capacity() const
	{
		return _getRep().m_capacity;
	}

	//------------------------------------------------------------------------
	template<typename T> inline void
	TStringBase<T>::clear()
	{
		_getRep().unRef();
		m_string = _GetEmptyStringRep().refCopy();
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::empty() const
	{
		return 0 == length();
	}

	//------------------------------------------------------------------------
	template<typename T> inline const T*
	TStringBase<T>::c_str() const
	{
		return m_string;
	}

	//------------------------------------------------------------------------
	template<typename T> inline const T*
	TStringBase<T>::data() const
	{
		return c_str();
	}

	//------------------------------------------------------------------------
	template<typename T> inline	void
	TStringBase<T>::reserve( int size )
	{
		assert( size>=0 );
		if( _getRep().m_capacity >= size && _getRep().m_references <= 0)
		{
			return;
		}
		int len = length();
		Rep* rep = Rep::Create(size);
		iliveMemCpy(rep->getData(), c_str(), len);
		rep->getData()[len] = 0;
		rep->m_length = len;
		_getRep().unRef();
		m_string = rep->getData();
	}

	//------------------------------------------------------------------------
	template<typename T> inline	void
	TStringBase<T>::format(const T* format, ...)
	{
		va_list argptr;
		va_start(argptr, format);
		vformat(format, argptr);
		va_end(argptr);
	}

	//------------------------------------------------------------------------
	template<typename T> inline void
	TStringBase<T>::vformat(const T* format, va_list argptr)
	{
		if( _getRep().m_references > 0 )
		{
			_getRep().unRef();
			m_string = Rep::Create(ILIVE_MININUM_STRING_CAPACITY)->getData();
		}
		while(true)
		{
			int size	= _getRep().m_capacity;
			int nchars	= iliveVsnprintf(m_string, size, format, argptr);
			if( nchars >= 0 && nchars < size )
			{
				_getRep().m_length = nchars;
				break;
			}
			else
			{
				_getRep().unRef();
				m_string	= Rep::Create( size*2 > 256 ? size*2 : 256 )->getData();
			}
		}
	}

	//------------------------------------------------------------------------
	template<typename T> inline void
	TStringBase<T>::swap(TStringBase<T>& oth)
	{
		iliveSwap<T*>(m_string, oth.m_string);
	}

	//------------------------------------------------------------------------
	template<typename T> TStringBase<T>
	TStringBase<T>::substr( int index, int num /*= ILIVE_INVALID_INDEX*/ ) const
	{
		if(num == ILIVE_INVALID_INDEX || num + index > length())
		{
			num = length() - index;
		}
		if( num <= 0 || index >= length() )
		{
			return TStringBase();
		}
		Rep* r	= Rep::Create(num);
		T* p	= r->getData();
		iliveMemCpy(p, m_string+index, num);
		p[num] = 0;
		return TStringBase(r);
	}

	//------------------------------------------------------------------------
	template<typename T> TStringBase<T>&
	TStringBase<T>::erase( int idx, int len/* = 1*/ )
	{
		assert( idx >= 0 && idx <= length() );
		int strLen = length() - idx;
		len = strLen < len ? strLen : len;
		TStringBase<T> strTmp(c_str(), idx);
		strTmp += ( c_str() + idx + len);
		swap(strTmp);
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::setchar(int idx, T ch)
	{
		assert( idx>=0  && idx<length() );
		if(c_str()[idx]==ch)
		{
			return *this;
		}
		if(_getRep().m_references > 0)
		{
			Rep* rep = _getRep().clone();
			_getRep().unRef();
			m_string = rep->getData();
		}
		m_string[idx] = ch;
		if( ch=='\0' )
		{
			_getRep().m_length = idx;
		}
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::find(const TStringBase<T>& str, int nStart/* = 0*/) const
	{
		const int nLen = length();
		const int nLenOther = str.length();
		if ( nLenOther==0 )
		{
			if (nStart>=0 && nStart<=nLen)
			{
				return 0;
			}
			else
			{
				return ILIVE_INVALID_INDEX;
			}
		}
		if ( nLen==0 || nStart<0 || nStart>=nLen)
		{
			return ILIVE_INVALID_INDEX;
		}

		const T* const oth = str.c_str();

		const T* p = (const T*)iliveMemChr(c_str() + nStart, *oth, nLen - nStart);
		if ( !p ) return ILIVE_INVALID_INDEX;

		while ( p - c_str() + nLenOther <= nLen && iliveMemCmp(p, oth, nLenOther) )
		{
			++p;
			p = (const T*)iliveMemChr(p, *oth, nLen - (p - c_str()));
			if ( !p ) return ILIVE_INVALID_INDEX;
		}
		return p - c_str() + nLenOther <= nLen ? p - c_str() : ILIVE_INVALID_INDEX;
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::find(const T* sz, int nStart/* = 0*/, int len/* = ILIVE_INVALID_INDEX*/) const
	{
		if (len == ILIVE_INVALID_INDEX)
		{
			len = iliveStrLen(sz);
		}
		return find( TStringBase<T>(sz, len), nStart );
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::find(T ch, int nStart/* = 0*/) const
	{
		if( nStart < 0 || nStart >= length() )
		{
			return ILIVE_INVALID_INDEX;
		}
		const T *p = (const T*)iliveMemChr(c_str() + nStart, ch, length() - nStart);
		return p == NULL ? ILIVE_INVALID_INDEX : p - c_str();
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::rfind(const TStringBase<T>& str, int nStart/* = ILIVE_INVALID_INDEX*/) const
	{
		if (nStart==ILIVE_INVALID_INDEX)
		{
			nStart = length()-1;
		}
		if (nStart<0 || nStart>=length())
		{
			return ILIVE_INVALID_INDEX;
		}
		if ( length() >= str.length() )
		{
			if ( length() == 0 && str.length() == 0 )
			{
				return 0;
			}
			int top = length() - str.length();//top是开始查找的位置
			if ( top > nStart )
			{
				top = nStart;
			}
			const T* cursor = c_str() + top;
			do
			{
				if ( iliveMemCmp(cursor, str.c_str(), str.length()) == 0 )
				{
					return cursor - c_str();
				}
			} while ( cursor-- > c_str() );
		}
		return ILIVE_INVALID_INDEX;
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::rfind(const T* sz, int nStart/* = ILIVE_INVALID_INDEX*/, int len/* = ILIVE_INVALID_INDEX*/) const
	{
		if (len == ILIVE_INVALID_INDEX)
		{
			len = iliveStrLen(sz);
		}
		return rfind( TStringBase<T>(sz, len), nStart );
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::rfind(T ch, int nStart/* = ILIVE_INVALID_INDEX*/) const
	{
		if (nStart==ILIVE_INVALID_INDEX)
		{
			nStart = length()-1;
		}
		if (nStart<0 || nStart>=length())
		{
			return ILIVE_INVALID_INDEX;
		}
		for ( const T* cursor = c_str() + nStart; cursor >= c_str(); --cursor )
		{
			if ( *cursor == ch )
			{
				return cursor - c_str();
			}
		}
		return ILIVE_INVALID_INDEX;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::insert(int idx, const TStringBase<T>& str)
	{
		return insert(idx, str, 0, str.length());
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::insert(int idx, const TStringBase<T>& str, int nStart, int len/* = ILIVE_INVALID_INDEX*/)
	{
		assert( idx >= 0 && idx <= length() );
		assert( nStart >= 0 && nStart <= str.length() );
		assert( len >= 0 || len == ILIVE_INVALID_INDEX );
		if(len == ILIVE_INVALID_INDEX)
		{
			len = str.length() - nStart;
		}
		if ( len > str.length() - nStart )
		{
			len = str.length() - nStart;
		}
		reserve( length() + len );
		iliveMemMove( m_string + idx + len, m_string + idx, length() - idx );
		iliveMemCpy( m_string + idx, str.m_string+  nStart, len);
		_getRep().m_length = length() + len;
		m_string[length()] = 0;
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::insert(int idx, const T* sz)
	{
		return insert(idx, sz, iliveStrLen(sz));
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::insert(int idx, const T* sz, int len)
	{
		assert( idx >= 0 && idx <= length() );
		assert( sz );
		assert( len <= iliveStrLen(sz) && len >= 0 );
		reserve( length() + len );
		iliveMemMove( m_string + idx + len, m_string + idx, length() - idx );
		iliveMemCpy( m_string + idx, sz, len );
		_getRep().m_length = length() + len;
		m_string[length()] = 0;
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::insert(int idx, T ch, int len/* = 1*/)
	{
		assert( idx >= 0 && idx <= length() );
		assert( len >= 0 );
		reserve( length() + len );
		iliveMemMove( m_string + idx + len, m_string + idx, length()-idx );
		iliveMemSet( m_string + idx, ch, len );
		_getRep().m_length = length() + len;
		m_string[length()] = 0;
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::replace(int idx, int n, const TStringBase<T>& str)
	{
		return replace(idx, n, str.c_str(), 0, str.length());
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::replace(int idx, int n, const TStringBase<T>& str, int sidx, int sn)
	{
		return replace( idx, n, str.c_str(), sidx, sn);
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::replace(int idx, int n, const T* str)
	{
		assert( str );
		assert( idx >= 0 && idx < length() );
		assert( n >= 0 );
		if ( n > length() - idx )
		{
			n = length() - idx;
		}
		int len = iliveStrLen(str);
		TStringBase<T> tmp;
		tmp.reserve( length() - n + len );
		tmp.append( c_str(), 0, idx );
		tmp.append( str, 0, len );
		tmp.append( c_str(), idx + n, length() - idx - n );
		swap(tmp);
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::replace(int idx, int n, const T* str, int sidx, int sn)
	{
		assert( str );
		assert( idx>=0 && idx<length() );
		assert( n >= 0 );
		assert( sidx >= 0 );
		assert( sn >= 0 );
		if ( n > length() - idx )
		{
			n = length() - idx;
		}
		TStringBase<T> tmp;
		tmp.reserve( length() - n + sn );
		tmp.append( c_str(), 0, idx );
		tmp.append( str, sidx, sn );
		tmp.append( c_str(), idx+n, length()-idx-n );
		swap(tmp);
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::replace(int idx, int n, T ch, int cn)
	{
		assert( cn >= 0 );
		assert( idx>=0 && idx<length() );
		assert( n >= 0 );
		if ( n > length() - idx )
		{
			n = length() - idx;
		}
		TStringBase<T> tmp;
		tmp.reserve( length() - n + cn );
		tmp.append( c_str(), 0, idx );
		tmp.append( ch, cn );
		tmp.append( c_str(), idx+n, length()-idx-n );
		swap(tmp);
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::append( const TStringBase<T>& str )
	{
		reserve( length() + str.length() );
		iliveMemCpy( m_string + length(), str.c_str(), str.length()+1 );
		_getRep().m_length = length() + str.length();
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::append(const TStringBase<T>& str, int idx, int n)
	{
		return append(str.c_str(), idx, n);
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::append(const T* str)
	{
		assert(str);
		int len = iliveStrLen(str);
		reserve( length() + len );
		iliveMemCpy(m_string+length(), str, len+1 );
		_getRep().m_length = length() + len;
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::append(const T* str, int idx, int n)
	{
		if(0 == n)
		{
			return *this;
		}
		assert(str);
		int len = iliveStrLen(str);
		assert(idx>=0 && idx<len);
		assert(n >= 0);
		if(n<0 || n+idx>len)
		{
			n = len - idx;
		}
		reserve(length() + n);
		iliveMemCpy(m_string+length(), str+idx, n);
		_getRep().m_length = length() + n;
		m_string[length()] = 0;
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::append(T ch)
	{
		return append(ch, 1);
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::append(T ch, int n)
	{
		assert(n >= 0);
		reserve(length() + n);
		iliveMemSet(m_string+length(), ch, n);
		_getRep().m_length = length() + n;
		m_string[length()] = 0;
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::compare(const TStringBase<T>& oth) const
	{
		return iliveStrCmp(c_str(), oth.c_str());
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::compare(const T* oth) const
	{
		return iliveStrCmp(c_str(), oth);
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::compareIgnoreCase(const TStringBase<T>& oth) const
	{
		return iliveStrIgnoreCaseCmp(c_str(), oth.c_str());
	}

	//------------------------------------------------------------------------
	template<typename T> inline int
	TStringBase<T>::compareIgnoreCase(const T* oth) const
	{
		return iliveStrIgnoreCaseCmp(c_str(), oth);
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::beginwith(const TStringBase<T>& s) const
	{
		return beginwith( s.c_str() );
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::beginwith(const T* s) const
	{
		for(int i=0; s[i]!=0; ++i)
		{
			if( i>=length() || c_str()[i]!=s[i] )
			{
				return false;
			}
		}
		return true;
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::endwith(const TStringBase<T>& s) const
	{
		if( length() < s.length() )
		{
			return false;
		}
		int offset = length() - s.length();
		for(int i=0; i<s.length(); ++i)
		{
			if(c_str()[offset+i] != s[i])
			{
				return false;
			}
		}
		return true;
	}

	//------------------------------------------------------------------------
	template<typename T> inline bool
	TStringBase<T>::endwith(const T* s) const
	{
		assert(s);
		int offset = length() - iliveStrLen(s);
		if(offset<0)
		{
			return false;
		}
		for(int i=0; s[i]!=0; ++i)
		{
			if(c_str()[i+offset] != s[i])
			{
				return false;
			}
		}
		return true;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::tolower()
	{
		if( _getRep().m_references>0 )
		{
			Rep* rep = _getRep().clone();
			_getRep().unRef();
			m_string = rep->getData();
		}
		for(int i=0; i<length(); ++i)
		{
			m_string[i] = iliveToLower(m_string[i]);
		}
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline TStringBase<T>&
	TStringBase<T>::toupper()
	{
		if( _getRep().m_references>0 )
		{
			Rep* rep = _getRep().clone();
			_getRep().unRef();
			m_string = rep->getData();
		}
		for(int i=0; i<length(); ++i)
		{
			m_string[i] = iliveToUpper(m_string[i]);
		}
		return *this;
	}

	//------------------------------------------------------------------------
	template<typename T> inline	typename TStringBase<T>::Rep&
	TStringBase<T>::_getRep() const
	{
		return *( reinterpret_cast<Rep*>(m_string) - 1 );
	}
}

#endif //iLiveString_h_