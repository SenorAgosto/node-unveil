#include <errno.h>
#include <node.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

namespace openbsd_unveil {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Disable(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	
	if(args.Length() != 0)
	{
		isolate->ThrowException(
			Exception::TypeError(
				String::NewFromUtf8(
					  isolate
					, "Wrong number of arguments"
					, v8::NewStringType::kNormal).ToLocalChecked())
		);
		
		return;
	}
	
	#if defined(__OpenBSD__)
	const int status = unveil(NULL, NULL);
	args.GetReturnValue().Set(status == 0 ? 0 : errno);
	#else
	const int status = -1;
	args.GetReturnValue().Set(ENOTSUP);
	#endif
}

void Unveil(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	if(args.Length() < 2) 
	{
		isolate->ThrowException(
			Exception::TypeError(
				String::NewFromUtf8(
					  isolate
					, "Wrong number of arguments"
					, v8::NewStringType::kNormal).ToLocalChecked()));

		return;
	}
	
	if(!args[0]->IsString()) 
	{
		isolate->ThrowException(
			Exception::TypeError(
				String::NewFromUtf8(
					  isolate
					, "Wrong argument type"
					, v8::NewStringType::kNormal).ToLocalChecked())); 
					
		return;
	}
	
	if(!args[1]->IsString()) 
	{
		isolate->ThrowException(
			Exception::TypeError(
				String::NewFromUtf8(
					  isolate
					, "Wrong argument type"
					, v8::NewStringType::kNormal).ToLocalChecked())); 
					
		return;
	}
	
#if defined(__OpenBSD__)
	const int status = unveil(*String::Utf8Value(isolate, args[0]), *String::Utf8Value(isolate, args[1]));
	args.GetReturnValue().Set(status == 0 ? 0 : errno);
#else
	const int status = -1;
	args.GetReturnValue().Set(ENOTSUP);
#endif
}

void Init(Local<Object> exports) 
{
	NODE_SET_METHOD(exports, "unveil_path", Unveil);
	NODE_SET_METHOD(exports, "disable", Disable);
}

NODE_MODULE(addon, Init)

}
