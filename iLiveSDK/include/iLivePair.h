#ifndef iLivePair_h_
#define iLivePair_h_

#include <iLiveCommon.h>

namespace ilive
{
	template<typename _Ty1, typename _Ty2>
	struct Pair
	{
		Pair(){}
		Pair(const _Ty1& fir, const _Ty2& sec):first(fir),second(sec){}
		Pair(const Pair& oth):first(oth.first),second(oth.second){}
		~Pair(){}
		Pair&  operator= (const Pair& oth){ first = oth.first; second = oth.second; return *this; }
		_Ty1		first;
		_Ty2		second;
	};
}

#endif //iLivePair_h_