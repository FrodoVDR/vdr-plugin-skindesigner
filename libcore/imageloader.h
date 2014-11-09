#ifndef __NOPACITY_IMAGELOADER_H
#define __NOPACITY_IMAGELOADER_H

#include <cairo.h>
#include <librsvg/rsvg.h>
#ifndef LIBRSVG_VERSION // Workaround for librsvg < 2.36.2
    #include <librsvg/rsvg-cairo.h>
#endif
#include <jpeglib.h>
#include <setjmp.h>
#include <vdr/osd.h>
#include <vdr/tools.h>

//
// Image importers
//
class cImageImporter {
public:
    cImageImporter() {};
    virtual ~cImageImporter() {};
    virtual bool LoadImage(const char *path) { return false; };
    virtual void DrawToCairo(cairo_t *cr) {};
    virtual void GetImageSize(int &width, int &height) {};
};

// Image importer for PNG
class cImageImporterPNG : public cImageImporter {
public:
    cImageImporterPNG();
    ~cImageImporterPNG();
    bool LoadImage(const char *path);
    void DrawToCairo(cairo_t *cr);
    void GetImageSize(int &width, int &height);
private:
    cairo_surface_t *surface;
};

// Image importer for SVG
class cImageImporterSVG : public cImageImporter {
public:
    cImageImporterSVG();
    ~cImageImporterSVG();
    bool LoadImage(const char *path);
    void DrawToCairo(cairo_t *cr);
    void GetImageSize(int &width, int &height);
private:
    RsvgHandle *handle;
};

// Image importer for JPG

#if BITS_IN_JSAMPLE != 8
    #error libjpeg has to be compiled with 8-bit samples!
#endif

struct my_error_mgr {
    struct jpeg_error_mgr pub; // "public" fields
    jmp_buf setjmp_buffer;     // for return to caller
};

METHODDEF(void)
my_error_exit(j_common_ptr cinfo) {
    // cinfo->err really points to a my_error_mgr struct, so coerce pointer
    my_error_mgr *myerr = (my_error_mgr*) cinfo->err;

    // Always display the message.
    (*cinfo->err->output_message) (cinfo);

    // Return control to the setjmp point
    longjmp(myerr->setjmp_buffer, 1);
}

METHODDEF(void)
my_output_message(j_common_ptr cinfo) {
    char buf[JMSG_LENGTH_MAX];
    cinfo->err->format_message(cinfo, buf);
    dsyslog("skindesigner: libjpeg error: %s", buf);
}

class cImageImporterJPG : public cImageImporter {
public:
    cImageImporterJPG();
    ~cImageImporterJPG();
    bool LoadImage(const char *path);
    void DrawToCairo(cairo_t *cr);
    void GetImageSize(int &width, int &height);
private:
    j_decompress_ptr cinfo;
    FILE *infile;
};



class cImageLoader {
private:
    cImageImporter *importer;
public:
    cImageLoader();
    virtual ~cImageLoader();
    cImage *CreateImage(int width, int height, bool preserveAspect = true);
    bool LoadImage(std::string Path, std::string FileName, std::string Extension);
    bool LoadImage(const char *fullpath);
    void DeterminateChannelLogoSize(int &width, int &height);
};

#endif //__NOPACITY_IMAGELOADER_H
