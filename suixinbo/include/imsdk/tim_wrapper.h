#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
#include "tim_msg_c.h"
#include "tim_group_c.h"



namespace TIM_WRAPPER
{
	const uint32_t BUFFER_SIZE = 100;
	inline std::string GetBuffer(void* handle, std::function<uint32_t(void*)> get_sizt, std::function<uint32_t(void *, char*, uint32_t*)> get_buf)
	{
		uint32_t len = get_sizt(handle);
		std::shared_ptr<char> p(new char[len], std::default_delete<char[]>());			
		get_buf(handle, p.get(), &len);
		std::string rt(p.get(), len);
		return std::move(rt);
	};

	namespace MSG
	{
		class TextElem;
		class ImageElem;
		class CustomElem;

		class Elem
		{
		public:
			TIMElemType type() const {return GetElemType(handle_);}
			Elem& SetType(TIMElemType type) {SetElemType(handle_, type); return *this;}
			void Release() {DestroyElem(handle_);}

			TextElem *GetTextElem(){return (TextElem*)(this);}
			ImageElem *GetImageElem(){return (ImageElem*)(this);}
			CustomElem *GetCustomElem(){return (CustomElem*)(this);};

		protected:
			Elem();
		protected:
			TIMMsgElemHandle handle_;
		};

		class TextElem:public Elem
		{
		public:
			TextElem(){};
			void SetContent(const std::string &content)
			{
				::SetContent(handle_, content.c_str());
			}
			const std::string content() const
			{
				return GetBuffer(handle_, 
								[](void* handle){ return GetContentLen(handle);}, 
								[](void *handle, char* buf, uint32_t* len){return GetContent(handle, buf, len);});
			}
		};

		class ImageElem:public Elem
		{


		};
		class Msg
		{
		public:
			Msg():handle_(CreateTIMMessage()){}
			~Msg(){DestroyTIMMessage(handle_);}
			explicit Msg(const Msg& r):handle_(CloneTIMMessage(r.handle_)){}
			explicit Msg(TIMMessageHandle handle):handle_(CloneTIMMessage(handle_)){}

			uint32_t GetElemCount() {return ::GetElemCount(handle_);}
		private:
			TIMMessageHandle handle_;
		};

	}

	namespace GROUP
	{
#if 0

		class CustomInfoElem
		{
		public:
			CustomInfoElem():handle_(CreateGroupCustomInfoElemHandle()){};
			CustomInfoElem(TIMGroupCustomInfoElemHandle handle):handle_(handle){};
			CustomInfoElem(const CustomInfoElem& r) :handle_(CloneGroupCustomInfoElemHandle(r.handle_)){};
		
		public:
			TIMGroupCustomInfoElemHandle GetHandle() const
			{
				return handle_;
			}
			std::string GetKey() 
			{
				return GetBuffer(handle_, 
					[](void* handle){return GetKeyLen4GroupCustomInfoElemHandle(handle);}, 
					[](void* handle, char* buf, uint32_t* len){return GetKey4GroupCustomInfoElemHandle(handle, buf, len);});
			};
			std::string GetValue()
			{
				return GetBuffer(handle_, 
					[](void* handle){return GetValueLen4GroupCustomInfoElemHandle(handle);}, 
					[](void* handle, char* buf, uint32_t* len){return GetValue4GroupCustomInfoElemHandle(handle, buf, len);});
			};
			void SetKey(char* key, uint32_t len)
			{
				return SetKey4GroupCustomInfoElemHandle(handle_, key, len);
			}
			void SetValue(char* value, uint32_t len)
			{
				return SetValue4GroupCustomInfoElemHandle(handle_, value, len);
			}

		private:
			TIMGroupCustomInfoElemHandle handle_;
		};
		class BaseCustomInfo
		{
		public:
			BaseCustomInfo() :handle_(::CreateGroupBaseCustomInfoHandle()){};
			BaseCustomInfo(TIMGroupCustomInfoHandle handle)
			{
				::DestroyGroupBaseCustomInfoHandle(handle_);
				handle_ = handle;
			}
			BaseCustomInfo(BaseCustomInfo& info)
			{
				handle_ = CloneGroupBaseCustomInfoHandle(info.handle_);
			}
			~BaseCustomInfo(){ ::DestroyGroupBaseCustomInfoHandle(handle_); };

		public:
			TIMGroupCustomInfoHandle GetHandle(){ return handle_; };
			void SetGroupBaseCustomInfo(std::vector<CustomInfoElem>& elems)
			{
				std::shared_ptr< TIMGroupCustomInfoElemHandle> p(new TIMGroupCustomInfoElemHandle[elems.size()], [](TIMGroupCustomInfoElemHandle* p){delete []p;});
				TIMGroupCustomInfoElemHandle* cur_handle = p.get();
				std::for_each(elems.begin(), elems.end(), [&cur_handle](const CustomInfoElem& elem){
					*cur_handle = elem.GetHandle();
					cur_handle++;
				});
				return ::SetGroupBaseCustomInfo(handle_, p.get(), elems.size());
			};

			std::vector<CustomInfoElem> GetGroupBaseCustomInfo()
			{
				std::vector<CustomInfoElem> rt;
				uint32_t handle_num = ::GetGroupBaseCustomInfoNum(handle_);
				std::shared_ptr<TIMGroupCustomInfoElemHandle> elems(new TIMGroupCustomInfoElemHandle[handle_num], std::default_delete<TIMGroupCustomInfoElemHandle[]>());
				::GetGroupBaseCustomInfo(handle_, elems.get(), &handle_num);
				std::for_each(elems.get(), elems.get() + handle_num, [&rt](const TIMGroupCustomInfoElemHandle elem){rt.push_back(CustomInfoElem(elem));});
				return std::move(rt);
			};
		private:
			TIMGroupCustomInfoHandle handle_;
		};
#endif

		class BaseInfo
		{
		public:
			BaseInfo() :handle_(CreateGroupBaseInfoHandle()){};
			~BaseInfo() {DestroyGroupBaseInfoHandle(handle_);};
			BaseInfo(BaseInfo& r) :handle_(CloneGroupBaseInfoHandle(r.handle_)){}
			BaseInfo(TIMGroupBaseInfoHandle handle) {handle_ = CloneGroupBaseInfoHandle(handle);};

		public:
			std::string GetId()
			{
				char id_buf[BUFFER_SIZE] = {0};uint32_t id_len = BUFFER_SIZE;
				GetGroupBaseInfoID(handle_, id_buf, &id_len);
				std::string rt(id_buf, id_len);
				return std::move(rt);
			}

			std::string GetName()
			{
				char name_buf[BUFFER_SIZE] = {0};uint32_t name_len = BUFFER_SIZE;
				GetGroupBaseInfoName(handle_, name_buf, &name_len);
				std::string rt(name_buf, name_len);
				return std::move(rt);
			}
			
			std::string GetType()
			{
				char type_buf[BUFFER_SIZE] = {0};uint32_t type_len = BUFFER_SIZE;
				GetGroupBaseInfoType(handle_, type_buf, &type_len);
				std::string rt(type_buf, type_len);
				return std::move(rt);
			}

		private:
			TIMGroupBaseInfoHandle handle_;
		};

		inline std::vector<BaseInfo> GenerateBaseInfos(TIMGroupBaseInfoHandle* handles, uint32_t num)
		{
			std::vector<BaseInfo> infos;
			std::for_each(handles, handles + num, [&infos](TIMGroupBaseInfoHandle handle){ infos.push_back(BaseInfo(handle));});
			return std::move(infos);
		}

		class MemberResult
		{
		public:
			MemberResult() :handle_(CreateGroupMemberResultHandle()){};
			MemberResult(TIMGroupMemberResultHandle handle) :handle_(CloneGroupMemberResultHandle(handle)){};
			~MemberResult() {DestroyGroupMemberResultHandle(handle_);}; 
		public:
			TIMGroupMemberResultHandle GetHandle()const {return handle_;}
			std::string GetOpenId() 
			{
				char buf[BUFFER_SIZE] = {0}; uint32_t len = BUFFER_SIZE;
				GetGroupMemberResultID(handle_, buf, &len);
				std::string rt(buf, len);
				return std::move(rt);
			};
			uint32_t GetResult()
			{
				return GetGroupMemberResult(handle_);
			}
			TIM_DECL uint32_t GetGroupMemberResult(TIMGroupMemberResultHandle handle);
		private:
			TIMGroupMemberResultHandle handle_;
		};

		inline std::vector<MemberResult > GenerateMmeberResults(TIMGroupMemberResultHandle* handle, uint32_t num)
		{
			std::vector<MemberResult > rt;
			std::for_each(handle, handle + num, [&rt](TIMGroupMemberResultHandle handle){rt.push_back(MemberResult(handle)); });
			return std::move(rt);
		}

		

	}
}
