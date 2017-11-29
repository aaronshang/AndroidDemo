#include "UBDLLLoad.h"

#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h> 
#include <stddef.h>
#endif

UBDllLoad::UBDllLoad()
{
	mHandle = NULL;
}

UBDllLoad::~UBDllLoad()
{
	UnLoad();
	mHandle = NULL;
}

bool UBDllLoad::Load(const char *librarypath){

#ifdef WIN32
	mHandle = (void*)LoadLibraryA(librarypath);
#else
	mHandle = (void*)dlopen(librarypath, RTLD_LAZY | RTLD_GLOBAL);
#endif

	return (mHandle == NULL) ? false : true;
}

void UBDllLoad::UnLoad()
{
#ifdef WIN32
	if (mHandle != NULL)
	{
		FreeLibrary((HINSTANCE)mHandle);
	}
#else
	if (mHandle != NULL)
	{
		dlclose((void*)mHandle);
		mHandle = NULL;
	}
#endif
}

void *UBDllLoad::GetSymbol(const char *symbolname)
{
	if (symbolname == NULL || mHandle == NULL)
	{
		return NULL;
	}

#ifdef WIN32
	return (void *)::GetProcAddress((HINSTANCE)mHandle, symbolname);
#else
	return dlsym((void *)mHandle, symbolname);
#endif
};

void* UBDllLoad::GetHandle(){
    return mHandle;
}

