#include "Poc.h"

PWSTR Poc::LoadFile()
{

	IFileOpenDialog* pFileOpen;
	PWSTR pszFilePath = NULL;

	// Create the FileOpenDialog object.
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
		IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
	if (SUCCEEDED(hr))
	{
		//IShellItem *psiDocuments = NULL;
		//hr = SHCreateItemInKnownFolder(FOLDERID_Documents, 0, NULL, IID_PPV_ARGS(&psiDocuments));

		//if (SUCCEEDED(hr)) {
		//	hr = pFileOpen->SetFolder(psiDocuments);
		//	psiDocuments->Release();
		//}
		// Show the Open dialog box.
		hr = pFileOpen->Show(NULL);

		// Get the file name from the dialog box.
		if (SUCCEEDED(hr))
		{
			IShellItem* pItem;
			hr = pFileOpen->GetResult(&pItem);
			if (SUCCEEDED(hr))
			{
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

				pItem->Release();
			}
		}
		pFileOpen->Release();
	}
	return pszFilePath;
	
}
