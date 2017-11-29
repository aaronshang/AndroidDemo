#ifndef UBDLLOAD_HEADER_
#define UBDLLOAD_HEADER_

typedef enum UBDLLError{
    UBDLLSuccess  = 0,
    UBDLLLoadFail,
    UBGetSymbolNameFail
}UBDLLError;

class UBDllLoad
{
public:
	UBDllLoad();
	~UBDllLoad();
public:
	bool Load(const char *librarypath);
	void UnLoad();
public:
    void* GetHandle();
	void *GetSymbol(const char *symbolname);
private:
	void *mHandle;
};

#endif
