#include "stdafx.h"
#include "XPSLib.h"
// Function for adding text to page....
HRESULT
XPSLib::Cpp::XPSApi::WriteText_AddTextToPage(
	__in    IXpsOMObjectFactory   *xpsFactory,
	// The font resource to use for this run
	__in    IXpsOMFontResource    *xpsFont,
	// The font size
	__in    float                 fontEmSize,
	// The solid color brush to use for the font
	__in    IXpsOMSolidColorBrush *xpsBrush,
	// The starting location of this glyph run
	__in    XPS_POINT             *origin,
	// The text to use for this run
	__in    LPCWSTR               unicodeString,
	// The page on which to write this glyph run
	__in IXpsOMPage            *xpsPage) const
{
	HRESULT                       hr = S_OK;
	XPS_POINT                     glyphsOrigin = { origin->x,origin->y };
	IXpsOMGlyphsEditor            *glyphsEditor = NULL;
	IXpsOMGlyphs                  *xpsGlyphs = NULL;
	IXpsOMVisualCollection        *pageVisuals = NULL;

	// Create a new Glyphs object and set its properties.
	hr = xpsFactory->CreateGlyphs(xpsFont, &xpsGlyphs);
	hr = xpsGlyphs->SetOrigin(&glyphsOrigin);
	hr = xpsGlyphs->SetFontRenderingEmSize(fontEmSize);
	hr = xpsGlyphs->SetFillBrushLocal(xpsBrush);

	// Some properties are inter-dependent so they
	//    must be changed by using a GlyphsEditor.
	hr = xpsGlyphs->GetGlyphsEditor(&glyphsEditor);
	hr = glyphsEditor->SetUnicodeString(unicodeString);
	hr = glyphsEditor->ApplyEdits();

	// Add the new Glyphs object to the page
	hr = xpsPage->GetVisuals(&pageVisuals);
	hr = pageVisuals->Append(xpsGlyphs);

	// Release interface pointers.
	if (NULL != xpsGlyphs) xpsGlyphs->Release();
	if (NULL != glyphsEditor) glyphsEditor->Release();
	if (NULL != pageVisuals) pageVisuals->Release();

	return hr;
}
//Function to get the image size and its resolution
HRESULT XPSLib::Cpp::XPSApi::GetImageProperties(
	__in IStream_t	imageStream,
	__out XPS_SIZE &imagesize,
	__out FLOAT &dpiX,
	__out FLOAT &dpiY
) const
{
	HRESULT hr = S_OK;
	IWICImagingFactory_t factory(NULL);
	IWICBitmapDecoder_t  decoder(NULL);

	UINT width = 0, height = 0;
	double dpiXres = 0.0, dpiYres = 0.0;

	UINT count = 0;

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));

	// Create the decoder.
	if (SUCCEEDED(hr))
	{
		hr = factory->CreateDecoderFromStream(imageStream, NULL, WICDecodeMetadataCacheOnDemand, &decoder);
	}
	if (SUCCEEDED(hr))
	{
		hr = decoder->GetFrameCount(&count);
	}
	// Process each frame of the image.
	for (UINT i = 0; i < count && SUCCEEDED(hr); i++)
	{
		IWICBitmapFrameDecode_t frame_decode(NULL);
		IWICBitmapSource_t		bitmapsource(NULL);
		IWICBitmap_t			ppIBitmap(NULL);
		IWICBitmapLock_t		ppILock(NULL);

		UINT cbStride = 0;
		BYTE *pbBuffer = NULL;
		WICPixelFormatGUID pPixelFormat;
		UINT pcbBufferSize = 0;

		// Get and create the image frame.
		if (SUCCEEDED(hr))
		{
			hr = decoder->GetFrame(i, &frame_decode);
		}
		// Get and set the size.
		if (SUCCEEDED(hr))
		{
			hr = frame_decode->GetSize(&width, &height);
			imagesize.width = width;
			imagesize.height = height;
		}
#ifdef TEST
		cout << "Widht and Height: " << width << " " << height << endl;
#endif
		WICRect prclock = { 0, 0, (INT)width, (INT)height };
		if (SUCCEEDED(hr))
		{
			frame_decode->GetResolution(&dpiXres, &dpiYres);
			dpiX = dpiXres;
			dpiY = dpiYres;
		}
	}
	return hr;
}

HRESULT XPSLib::Cpp::XPSApi::CreateRectanglePath(
	__in  IXpsOMObjectFactory1_t   &xpsFactory,
	__in  const XPS_RECT			*rect,
	__out IXpsOMPath_t           &rectPath
) const
{
	HRESULT hr = S_OK;

	IXpsOMGeometryFigure           *rectFigure;
	IXpsOMGeometry                 *imageRectGeometry;
	IXpsOMGeometryFigureCollection *geomFigureCollection;

	// Define start point and three of the four sides of the rectangle.
	//  The fourth side is implied by setting the path type to CLOSED.
	XPS_POINT            startPoint = { rect->x, rect->y };
	XPS_SEGMENT_TYPE     segmentTypes[3] = {
		XPS_SEGMENT_TYPE_LINE,
		XPS_SEGMENT_TYPE_LINE,
		XPS_SEGMENT_TYPE_LINE
	};
	FLOAT segmentData[6] = {
		rect->x,              rect->y + rect->height,
		rect->x + rect->width,  rect->y + rect->height,
		rect->x + rect->width,  rect->y
	};
	BOOL segmentStrokes[3] = {
		TRUE, TRUE, TRUE
	};

	// Create a closed geometry figure using the three 
	//  segments defined above.

	hr = xpsFactory->CreateGeometryFigure(&startPoint, &rectFigure);
	hr = rectFigure->SetIsClosed(TRUE);
	hr = rectFigure->SetIsFilled(TRUE);
	hr = rectFigure->SetSegments(3, 6,
		segmentTypes, segmentData, segmentStrokes);

	// Create a geometry that consists of the figure created above.
	hr = xpsFactory->CreateGeometry(&imageRectGeometry);
	hr = imageRectGeometry->GetFigures(&geomFigureCollection);
	hr = geomFigureCollection->Append(rectFigure);

	// Create the path that consists of the geometry created above
	//  and return the pointer in the parameter passed in to the function.
	hr = xpsFactory->CreatePath(&rectPath);
	hr = rectPath->SetGeometryLocal(imageRectGeometry);
	return hr;
}

//Saves the file to the given location.....
HRESULT XPSLib::Cpp::XPSApi::SavefiletoLocation(string str) const 
{	
	m_pathcopy = str;
	wstring wide_string = wstring(str.begin(), str.end());
	const wchar_t* wide1 =wide_string.c_str();
	HRESULT hr = S_OK;
	hr= m_xpsPackage->WriteToFile(wide1, NULL, FILE_ATTRIBUTE_NORMAL, FALSE);
	return hr;
}

//Creates a blank page and parse the document to get page for future use....
HRESULT XPSLib::Cpp::XPSApi::CreateBlankXPSFile() const
{
	IXpsOMObjectFactory1_t				xpsFactory(NULL);
	HRESULT hr = S_OK;
	hr = CoCreateInstance(
		__uuidof(XpsOMObjectFactory),
		NULL,

		CLSCTX_INPROC_SERVER,
		__uuidof(IXpsOMObjectFactory),
		reinterpret_cast<LPVOID*>(&xpsFactory));

	if (SUCCEEDED(hr))
	{

		HRESULT                         hr = S_OK;
		IOpcPartUri                    *opcPartUri = NULL;
		IXpsOMDocumentSequence_t        xpsFDS(NULL);
		IXpsOMDocumentCollection_t      fixedDocuments(NULL);
		IXpsOMDocument_t                xpsFD(NULL);
		IXpsOMPage_t                    xpsPage(NULL);
		IXpsOMPageReferenceCollection_t pageRefs(NULL);
		IXpsOMPageReference_t           xpsPageRef(NULL);
		FLOAT width = 816.0;
		FLOAT height = 1056.0;
		XPS_SIZE pageSize = { width, height };
		
		// Create the package.
		hr = xpsFactory->CreatePackage1(&static_cast<IXpsOMPackage1*>(m_xpsPackage));
		
		// Create the URI for the fixed document sequence part and then  
		//  create the fixed document sequence
		hr = xpsFactory->CreatePartUri(
			L"/FixedDocumentSequence.fdseq", &opcPartUri);
		hr = xpsFactory->CreateDocumentSequence(opcPartUri, &xpsFDS);
		// Release this URI to reuse the interface pointer.
		if (NULL != opcPartUri) { opcPartUri->Release(); opcPartUri = NULL; }

		// Create the URI for the document part and then create the document.
		hr = xpsFactory->CreatePartUri(
			L"/Documents/1/FixedDocument.fdoc", &opcPartUri);
		hr = xpsFactory->CreateDocument(opcPartUri, &xpsFD);
		// Release this URI to reuse the interface pointer.
		if (NULL != opcPartUri) { opcPartUri->Release(); opcPartUri = NULL; }

		// Create a blank page.
		hr = xpsFactory->CreatePartUri(
			L"/Documents/1/Pages/1.fpage", &opcPartUri);
		hr = xpsFactory->CreatePage(
			&pageSize,                  // Page size
			L"en-US",                   // Page language
			opcPartUri,                 // Page part name 
			&xpsPage);
		// Release this URI to reuse the interface pointer.
		if (NULL != opcPartUri) { opcPartUri->Release(); opcPartUri = NULL; }

		// Create a page reference for the page.
		hr = xpsFactory->CreatePageReference(&pageSize, &xpsPageRef);
		// Create a blank page.
		

		// Add the fixed document sequence to the package.
		hr = m_xpsPackage->SetDocumentSequence(xpsFDS);
	
		// Get the document collection of the fixed document sequence
		//  and then add the document to the collection.
		hr = xpsFDS->GetDocuments(&fixedDocuments);
		hr = fixedDocuments->Append(xpsFD);

		// Get the page reference collection from the document
		//  and add the page reference and blank page.
		hr = xpsFD->GetPageReferences(&pageRefs);
		hr = pageRefs->Append(xpsPageRef);
		hr = xpsPageRef->SetPage(xpsPage);
	}
	// Function to parse the file and get the page for future use
	if (SUCCEEDED(hr))
	{
		IXpsOMDocumentSequence_t         docSeq(NULL);
		IXpsOMDocumentCollection_t       docs(NULL);
		IXpsOMDocument_t                 doc(NULL);
		IXpsOMPageReferenceCollection_t  pages(NULL);
		IXpsOMPageReference_t            pageRef(NULL);
		UINT32  numDocs = 0;
		UINT32  thisDoc = 0;

		UINT32  numPageRefs = 0;
		UINT32  thisPageRef = 0;
		hr = m_xpsPackage->GetDocumentSequence(&docSeq);

		// Get the fixed documents in the fixed document sequence.
		hr = docSeq->GetDocuments(&docs);

		// Walk the collection of documents.
		hr = docs->GetCount(&numDocs);
		thisDoc = 0;
		while (thisDoc < numDocs) {
			hr = docs->GetAt(thisDoc, &doc);

			// Get the doc contents.
			hr = doc->GetPageReferences(&pages);

			// Walk the collection of page references
			hr = pages->GetCount(&numPageRefs);
			thisPageRef = 0;
			while (thisPageRef < numPageRefs) {
				// Get this page reference.
				hr = pages->GetAt(thisPageRef, &pageRef);
				hr = pageRef->GetPage(&static_cast<IXpsOMPage*>(m_page));
				thisPageRef++;
			}
			thisDoc++;
		}
	}

		return hr;
	
}
//Sets the Page size based on the user need.....
HRESULT XPSLib::Cpp::XPSApi::ChangePageSize(float width, float height) const
{
	HRESULT hr = S_OK;
	XPS_SIZE pageSize;
	pageSize = { width,height };
	if (SUCCEEDED(hr)) {
		hr = m_page->SetPageDimensions(&pageSize);
	}
		
	return hr;
}

//Saves the changes made to the document......
HRESULT XPSLib::Cpp::XPSApi::SaveChanges(string str) const
{
	if (m_pathcopy==" ")
	{
		XPSApi::m_pathcopy = str;
		wstring wide_string = wstring(str.begin(), str.end());
		const wchar_t* wide1 = wide_string.c_str();
		HRESULT hr = S_OK;
		hr = m_xpsPackage->WriteToFile(wide1, NULL, FILE_ATTRIBUTE_NORMAL, FALSE);
		return hr;
		
	}

	else
	{
		HRESULT hr = S_OK;
		wstring wide_string = wstring(m_pathcopy.begin(), m_pathcopy.end());
		const wchar_t* wide1 = wide_string.c_str();
		hr = m_xpsPackage->WriteToFile(wide1, NULL, FILE_ATTRIBUTE_NORMAL, FALSE);

		return hr;
		
	}
}

//Inserts picture in the page.....
HRESULT XPSLib::Cpp::XPSApi::InsertPicture(string imagepath) const
{
	IXpsOMObjectFactory1_t			    xpsFactory(NULL);
	IStream_t							imageStream(NULL);
	IOpcPartUri_t						imagePartUri(NULL);
	IXpsOMImageResource_t				imageResource(NULL);
	IXpsOMPath_t						imageRectPath(NULL);
	IXpsOMImageBrush_t					imageBrush(NULL);
	IXpsOMVisualCollection_t			pageVisuals(NULL);

	wstring imgloc = wstring(imagepath.begin(), imagepath.end());
	const wchar_t* imgpath = imgloc.c_str();
	UINT32  numDocs = 0;
	UINT32  thisDoc = 0;
	UINT32  numPageRefs = 0;
	UINT32  thisPageRef = 0;
	XPS_SIZE pageSize;
	HRESULT hr = S_OK;
	hr = CoCreateInstance(
		__uuidof(XpsOMObjectFactory),
		NULL,

		CLSCTX_INPROC_SERVER,
		__uuidof(IXpsOMObjectFactory),
		reinterpret_cast<LPVOID*>(&xpsFactory));

			hr = m_page->GetPageDimensions(&pageSize);
			float width = (pageSize).width;
			float height = (pageSize).height;

			if (SUCCEEDED(hr)) {
				hr = xpsFactory->CreateReadOnlyStreamOnFile(
					imgpath, &imageStream);
			}

			std::wstring imagefilename = std::wstring(imgpath);

			XPS_IMAGE_TYPE imageType;
			std::wstring fileExtension(imagefilename.substr(imagefilename.find_last_of('.')));
			// Convert all characters to lower case
			std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), tolower);
			// Default value is bitmap encoding
			if (fileExtension.compare(L".jpg") == 0 ||
				fileExtension.compare(L".jpeg") == 0 ||
				fileExtension.compare(L".jpe") == 0 ||
				fileExtension.compare(L".jfif") == 0)
			{
				imageType = XPS_IMAGE_TYPE_JPEG;
			}
			else if (fileExtension.compare(L".tif") == 0 ||
				fileExtension.compare(L".tiff") == 0)
			{
				imageType = XPS_IMAGE_TYPE_TIFF;
			}
			else if (fileExtension.compare(L".png") == 0)
			{
				imageType = XPS_IMAGE_TYPE_PNG;
			}
			else if (fileExtension.compare(L".wdp") == 0)
			{
				imageType = XPS_IMAGE_TYPE_WDP;
			}

			if (SUCCEEDED(hr)) {
				std::wstring outputfilename = L"/Resources/Images/1" + fileExtension;
				hr = xpsFactory->CreatePartUri(outputfilename.c_str(), &imagePartUri);
			}

			if (SUCCEEDED(hr)) {
				hr = xpsFactory->CreateImageResource(
					imageStream,
					imageType,
					imagePartUri,
					&imageResource);
			}
			XPS_SIZE    bmpDim = { 0,0 };//set to image size
			FLOAT        dpiX = 0.0f;
			FLOAT        dpiY = 0.0f;

			if (SUCCEEDED(hr))
			{
				hr =GetImageProperties(imageStream, bmpDim, dpiX, dpiY);
			}
			XPS_RECT    vp = { 0.0f,0.0f,0.0f,0.0f }; // set to image size
			
				float w1 = bmpDim.width;
				float h1 = bmpDim.height;
				vp = { (width - w1) / 2, (height - h1) / 2, w1, h1 };

			 
			XPS_RECT    viewPort = { 0.0,0.0,0.0,0.0 };
			// initialize viewbox values
			XPS_RECT    viewBox = { 0.0,0.0,0.0,0.0 };
			viewBox.width = FLOAT((double)bmpDim.width * 96.0 / (int)dpiX);
			viewBox.height = FLOAT((double)bmpDim.height * 96.0 / (int)dpiY);
			viewPort.x = vp.x;
			viewPort.y = vp.y;
			viewPort.width = vp.width;
			viewPort.height = vp.height;

			// Create the image brush.
			if (SUCCEEDED(hr)) {
				hr = xpsFactory->CreateImageBrush(imageResource, &viewBox, &viewPort, &imageBrush);
			}

			// Create the path that describes the outline of the image on the page.
			//This calls the function defined above
			if (SUCCEEDED(hr)) {
				hr = CreateRectanglePath(xpsFactory, &vp, imageRectPath);
			}

			// Set the accessibility description for the path object as required.
			if (SUCCEEDED(hr)) {
				hr = imageRectPath->SetAccessibilityShortDescription(L"ImagePath");
			}

			// Set the image brush to be the fill brush for this path.

			if (SUCCEEDED(hr)) {
				hr = imageRectPath->SetFillBrushLocal(imageBrush);
			}
		
			if (SUCCEEDED(hr)) {
				 //Get the list of visuals for this page...
				hr = m_page->GetVisuals(&pageVisuals);
				hr = pageVisuals->Append(imageRectPath);
			}

	return hr;
}

// Function for inserting text....
HRESULT XPSLib::Cpp::XPSApi::InsertText(string str,float size,string text) const
{
	HRESULT hr = S_OK;
	IXpsOMObjectFactory1_t			    xpsFactory(NULL);
	hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	hr = CoCreateInstance(
		__uuidof(XpsOMObjectFactory),
		NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IXpsOMObjectFactory),
		reinterpret_cast<LPVOID*>(&xpsFactory));
	if (SUCCEEDED(hr))
	{
		HRESULT                       hr = S_OK;
		GUID                          fontNameGuid;
		WCHAR                         guidString[128] = { 0 };
		WCHAR                         uriString[256] = { 0 };
		IStream_t                     fontStream(NULL);
		IOpcPartUri_t                 fontUri(NULL);
		IXpsOMFontResource_t          fontResource(NULL);
		IXpsOMVisualCollection_t      pageVisuals(NULL);
		IXpsOMVisual_t                canvasVisual(NULL);
		IXpsOMSolidColorBrush         *xpsTextColor = NULL;
		XPS_COLOR                     xpsColorBodyText;
		wstring fontloc = wstring(str.begin(), str.end());
		const wchar_t* fontpath = fontloc.c_str();
		wstring texts = wstring(text.begin(), text.end());
		const wchar_t* content = texts.c_str();
		// Create font stream.
		hr = xpsFactory->CreateReadOnlyStreamOnFile(
			fontpath, &fontStream);
		// Create new obfuscated part name for this resource using a GUID.
		hr = CoCreateGuid(&fontNameGuid);
		hr = StringFromGUID2(
			fontNameGuid,
			guidString,
			ARRAYSIZE(guidString));

		// Create a URI string for this font resource that will place  the font part in the /Resources/Fonts folder of the package.
		wcscpy_s(uriString, ARRAYSIZE(uriString), L"/Resources/Fonts/");

		// Create the part name using the GUID string as the name and 
		//  ".odttf" as the extension GUID string start and ends with 
		//  curly braces so they are removed.
		wcsncat_s(uriString, ARRAYSIZE(uriString),
			guidString + 1, wcslen(guidString) - 2);		
		wcscat_s(uriString, ARRAYSIZE(uriString), L".ttf");

		// Create the font URI interface.
		hr = xpsFactory->CreatePartUri(
			uriString,
			&fontUri);
		// Create the font resource.
		hr = xpsFactory->CreateFontResource(
			fontStream,
			XPS_FONT_EMBEDDING_OBFUSCATED,
			fontUri,
			FALSE,     // isObfSourceStream
			&fontResource);
		
		XPS_POINT startpoints;
		startpoints.x = 200;
		startpoints.y = 300;
		
			// Create the brush to use for the font.
			xpsColorBodyText.colorType = XPS_COLOR_TYPE_SRGB;
			xpsColorBodyText.value.sRGB.alpha = 0xFF;
			xpsColorBodyText.value.sRGB.red = 0x00;
			xpsColorBodyText.value.sRGB.green = 0x00;
			xpsColorBodyText.value.sRGB.blue = 0x00;

			hr = xpsFactory->CreateSolidColorBrush(
				&xpsColorBodyText,
				NULL,
				&xpsTextColor);

			hr = WriteText_AddTextToPage(
				xpsFactory,
				fontResource,
				size,
				xpsTextColor,
				&startpoints,
				content,
				m_page);
			
			
			if (NULL != xpsTextColor) xpsTextColor->Release();
		
	}
	return hr;

}