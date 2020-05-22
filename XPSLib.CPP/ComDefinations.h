#ifndef __ComDefinations_H_INCLUDED__   
#define __ComDefinations_H_INCLUDED__ 

const CHAR* const kxps_document_type[] = { "", "XPS_DOCUMENT_TYPE_UNSPECIFIED", "XPS_DOCUMENT_TYPE_XPS", "XPS_DOCUMENT_TYPE_OPENXPS" };
const CHAR* const kxps_object_type[] = { "", "XPS_OBJECT_TYPE_CANVAS", "XPS_OBJECT_TYPE_GLYPHS", "XPS_OBJECT_TYPE_PATH", "XPS_OBJECT_TYPE_MATRIX_TRANSFORM"
, "XPS_OBJECT_TYPE_GEOMETRY", "XPS_OBJECT_TYPE_SOLID_COLOR_BRUSH", "XPS_OBJECT_TYPE_IMAGE_BRUSH"
, "XPS_OBJECT_TYPE_LINEAR_GRADIENT_BRUSH", "XPS_OBJECT_TYPE_RADIAL_GRADIENT_BRUSH"
, "XPS_OBJECT_TYPE_VISUAL_BRUSH" };

typedef CComPtr<IXpsOMObjectFactory1> IXpsOMObjectFactory1_t;
typedef CComPtr<XpsOMObjectFactory> XpsOMObjectFactory_t;
typedef CComPtr<IXpsOMPackageWriter> IXpsOMPackageWriter_t;
typedef CComPtr<IXpsOMPackage1> IXpsOMPackage1_t;
typedef CComPtr<IXpsOMPackage> IXpsOMPackage_t;

typedef CComPtr<IXpsOMDocumentStructureResource> IXpsOMDocumentStructureResource_t;
typedef CComPtr<IXpsOMSignatureBlockResourceCollection> IXpsOMSignatureBlockResourceCollection_t;
typedef CComPtr<IXpsOMPartUriCollection> IXpsOMPartUriCollection_t;
typedef CComPtr<IXpsOMStoryFragmentsResource> IXpsOMStoryFragmentsResource_t;
typedef CComPtr<IXpsOMCoreProperties> IXpsOMCoreProperties_t;

typedef CComPtr<IXpsOMDocumentSequence> IXpsOMDocumentSequence_t;
typedef CComPtr<IXpsOMPrintTicketResource> IXpsOMPrintTicketResource_t;
typedef CComPtr<IXpsOMDocumentCollection> IXpsOMDocumentCollection_t;
typedef CComPtr<IXpsOMDocument> IXpsOMDocument_t;
typedef CComPtr<IXpsOMPageReferenceCollection> IXpsOMPageReferenceCollection_t;
typedef CComPtr<IXpsOMPageReference> IXpsOMPageReference_t;
typedef CComPtr<IXpsOMPage> IXpsOMPage_t;
typedef CComPtr<IXpsOMVisualCollection> IXpsOMVisualCollection_t;
typedef CComPtr<IXpsOMVisual> IXpsOMVisual_t;

typedef CComPtr<IXpsOMGlyphs> IXpsOMGlyphs_t;
typedef CComPtr<IXpsOMCanvas> IXpsOMCanvas_t;
typedef CComPtr<IXpsOMPath> IXpsOMPath_t;
typedef CComPtr<IXpsOMBrush> IXpsOMBrush_t;
typedef CComPtr<IXpsOMVisualBrush> IXpsOMVisualBrush_t;
typedef CComPtr<IXpsOMImageBrush> IXpsOMImageBrush_t;
typedef CComPtr<IXpsOMImageResource> IXpsOMImageResource_t;
typedef CComPtr<IStream> IStream_t;
typedef CComPtr<IOpcPartUri> IOpcPartUri_t;
typedef CComPtr<IXpsOMMatrixTransform> IXpsOMMatrixTransform_t;
typedef CComPtr<IXpsOMImageBrush> IXpsOMImageBrush_t;

typedef CComPtr<IWICImagingFactory> IWICImagingFactory_t;
typedef CComPtr<IWICBitmapDecoder> IWICBitmapDecoder_t;
typedef CComPtr<IWICBitmapEncoder> IWICBitmapEncoder_t;
typedef CComPtr<IWICBitmapFrameDecode> IWICBitmapFrameDecode_t;
typedef CComPtr<IWICBitmapFrameEncode> IWICBitmapFrameEncode_t;
typedef CComPtr<IWICBitmapSource> IWICBitmapSource_t;
typedef CComPtr<IWICBitmap> IWICBitmap_t;
typedef CComPtr<IWICBitmapLock> IWICBitmapLock_t;

typedef CComPtr<IXpsOMGeometryFigure> IXpsOMGeometryFigure_t;
typedef CComPtr<IXpsOMGeometry> IXpsOMGeometry_t;
typedef CComPtr<IXpsOMGeometryFigureCollection> IXpsOMGeometryFigureCollection_t;

#endif