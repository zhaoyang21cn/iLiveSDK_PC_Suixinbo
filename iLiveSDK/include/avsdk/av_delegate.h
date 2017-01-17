#pragma once

#include <stddef.h>

template<class TInterfaceImpl>
class AVDelegate {
 public:
  template<class THost>
  AVDelegate(THost* host) {
    m_impl = new TInterfaceImpl();
    m_impl->SetHost(host);
  }

  ~AVDelegate() {
    m_impl->SetHost(NULL);
    m_impl->UnhookAll();
    m_impl->Release();
  }

  TInterfaceImpl* operator->() {
    return m_impl;
  }

  operator TInterfaceImpl* () {
    return m_impl;
  }

 private:
  AVDelegate& operator=(const AVDelegate&);
  AVDelegate(const AVDelegate&);
  TInterfaceImpl* m_impl;
};

#define DECLARE_DELEGATE_BEGIN(delegate_class, interface_class) \
  template<class THost> class interface_class##Impl; \
  template<class THost> \
  class delegate_class : public AVDelegate<interface_class##Impl<THost> > { \
   public: \
    delegate_class(THost* host) : AVDelegate<interface_class##Impl<THost> >(host) {} \
  }; \
  template<class THost> \
  class interface_class##Impl : public interface_class { \
   public: \
    interface_class##Impl() { \
      memset((uint8*)&m_host, 0, sizeof(*this) - ((uint8*)&m_host - (uint8*)this)); \
    } \
    ~interface_class##Impl() { UnhookAll(); } \
   public: \
    void SetHost(THost* host) { m_host = host; } \
    void UnhookAll() { \
      THost* host = m_host; \
      memset((uint8*)&m_host, 0, sizeof(*this) - ((uint8*)&m_host - (uint8*)this)); \
      m_host = host; \
    } \
   private: \
    THost* m_host; \
    interface_class##Impl& operator=(const interface_class##Impl&); \
    interface_class##Impl(const interface_class##Impl&);

#define IMPLEMENT_DELEGATE_METHOD(method_name, method_params, param_values) \
   public: \
    typedef void (THost::*PROC_##method_name)method_params; \
    void Hook_##method_name(PROC_##method_name function_pointer) { m_fp##method_name = function_pointer; } \
    void Unhook_##method_name() { m_fp##method_name = NULL; } \
    void (method_name)method_params { \
      if (m_host && m_fp##method_name) ((m_host)->*(m_fp##method_name))param_values; \
    } \
   private: \
    PROC_##method_name m_fp##method_name;

#define DECLARE_DELEGATE_END() };