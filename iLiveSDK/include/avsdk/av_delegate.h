// 委托类定义
#pragma once

#include <string>
#include "av_ref_count.h"

template<class TInterfaceImpl>
class AVDelegate {
public:
    template<class THost>
    AVDelegate(THost* host) {
        _impl = new TInterfaceImpl();
        _impl->SetHost(host);
    }

    virtual ~AVDelegate() {
        _impl->SetHost(NULL);
        _impl->UnhookAll();
        _impl->Release();
    }

    TInterfaceImpl* operator->() {
        return _impl;
    }

    operator TInterfaceImpl* () {
        return _impl;
    }

private:
    AVDelegate& operator=(const AVDelegate&);
    AVDelegate(const AVDelegate&);
    TInterfaceImpl* _impl;
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
            memset((uint8*)&_host, 0, sizeof(*this) - ((uint8*)&_host - (uint8*)this)); \
        } \
        ~interface_class##Impl() { UnhookAll(); } \
    public: \
        void SetHost(THost* host) { _host = host; } \
        void UnhookAll() { \
            THost* host = _host; \
            memset((uint8*)&_host, 0, sizeof(*this) - ((uint8*)&_host - (uint8*)this)); \
            _host = host; \
        } \
    private: \
        THost* _host; \
        interface_class##Impl& operator=(const interface_class##Impl&); \
        interface_class##Impl(const interface_class##Impl&);

#define IMPLEMENT_DELEGATE_METHOD(method_name, method_params, param_values) \
    public: \
        typedef void (THost::*FuncPtr_##method_name)method_params; \
        void Hook_##method_name(FuncPtr_##method_name function_pointer) { _fp##method_name = function_pointer; } \
        void Unhook_##method_name() { _fp##method_name = NULL; } \
        void (method_name)method_params { \
            if (_host && _fp##method_name) (_host->*_fp##method_name)param_values; \
        } \
    private: \
        FuncPtr_##method_name _fp##method_name;

#define DECLARE_DELEGATE_END() };