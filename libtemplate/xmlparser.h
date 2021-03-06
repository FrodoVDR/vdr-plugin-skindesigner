#ifndef __XMLPARSER_H
#define __XMLPARSER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlerror.h>
#include <vdr/plugin.h>

#include "templateview.h"
#include "templateviewlist.h"
#include "templateviewgrid.h"
#include "templateviewtab.h"
#include "../libcore/skinsetup.h"

using namespace std;

// --- cXmlParser -------------------------------------------------------------

class cXmlParser {
private:
    cTemplateView *view;
    cGlobals *globals;
    cSkinSetup *skinSetup;
    xmlParserCtxtPtr ctxt;
    xmlDocPtr doc;
    xmlNodePtr root;
    string GetPath(string xmlFile);
    void ParseSetupMenu(xmlNodePtr node);
    void ParseSetupParameter(xmlNodePtr node);
    void ParseGlobalColors(xmlNodePtr node);
    void InsertColor(string name, string value);
    void ParseGlobalVariables(xmlNodePtr node);
    void InsertVariable(string name, string type, string value);
    void ParseGlobalFonts(xmlNodePtr node);
    void ParseTranslations(xmlNodePtr node);
    bool ParseSubView(xmlNodePtr node);
    void ParseViewElement(const xmlChar * viewElement, xmlNodePtr node, vector<pair<string, string> > &attributes, cTemplateView *subView = NULL);
    void ParseViewList(xmlNodePtr parentNode, cTemplateView *subView = NULL);
    void ParseViewTab(xmlNodePtr parentNode, cTemplateView *subView);
    void ParseGrid(xmlNodePtr node, vector<pair<string, string> > &attributes);
    void ParseFunctionCalls(xmlNodePtr node, cTemplatePixmap *pix);
    void ParseLoopFunctionCalls(xmlNodePtr node, cTemplateLoopFunction *loopFunc);
    bool ParseAttributes(xmlAttrPtr attr, xmlNodePtr node, vector<pair<string, string> > &attribs, bool isViewElement = false);
public:
    cXmlParser(void);
    virtual ~cXmlParser(void);
    bool ReadView(cTemplateView *view, string xmlFile);
    bool ReadPluginView(string plugName, int templateNumber, string templateName);
    bool ReadGlobals(cGlobals *globals, string xmlFile, bool mandatory);
    bool ReadSkinSetup(cSkinSetup *skinSetup, string xmlFile);
    bool ParseView(void);
    bool ParsePluginView(string plugName, int templateNumber);
    bool ParseGlobals(void);
    bool ParseSkinSetup(string skin);
    void DeleteDocument(void);
    static void InitLibXML();
    static void CleanupLibXML();
};

#endif //__XMLPARSER_H
