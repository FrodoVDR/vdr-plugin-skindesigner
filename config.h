#ifndef __DESIGNER_CONFIG_H
#define __DESIGNER_CONFIG_H

#include <string>
#include <vector>
#include <map>
#include <vdr/tools.h>
#include <vdr/skins.h>
#include <vdr/plugin.h>
#include "libcore/fontmanager.h"
#include "libcore/imagecache.h"
#include "libcore/recfolderinfo.h"
#include "libcore/skinsetup.h"

#define SCRIPTOUTPUTPATH "/tmp/skindesigner"

class cDesignerConfig {
private:
    cString CheckSlashAtEnd(string path);
    bool epgImagePathSet;
    bool skinPathSet;
    bool logoPathSet;
    cRect osdSize;
    string osdSkin;
    string osdTheme;
    string fontFix;
    string fontOsd;
    string fontSml;
    string osdLanguage;
    cGlobals *tmplGlobals;
    map < string, map < int, string > > pluginMenus;
    map < string, map < int, string > >::iterator plugMenuIt;
    map < string, map < int, string > > pluginViews;
    map < string, map < int, string > >::iterator plugViewIt;
    map < string, multimap< int, pair <int, string> > > pluginSubViews;
    map < string, map< int, map <int, string> > > pluginViewElements;
    map < string, map< int, map <int, string> > > pluginViewGrids;
    map < string, cSkinSetup* > skinSetups;
    map < string, cSkinSetup* >::iterator setupIt;
    vector < pair <string, int> > skinSetupParameters;
public:
    cDesignerConfig();
    ~cDesignerConfig();
    bool SetupParse(const char *Name, const char *Value);
    void SetPathes(void);
    void SetSkinPath(cString path);
    void SetLogoPath(cString path);
    void SetEpgImagePath(cString path);
    void ReadSkins(void);
    void ReadSkinSetup(string skin);
    void InitSkinIterator(void) { skinIterator = skins.begin(); };
    bool GetSkin(string &skin);
    void ClearSkinSetups(void);
    void DebugSkinSetups(void);
    void DebugSkinSetupParameters(void);
    cSkinSetup* GetSkinSetup(string &skin);
    cSkinSetup* GetNextSkinSetup(void);
    cSkinSetupMenu* GetSkinSetupMenu(string &skin, string &menu);
    void InitSetupIterator(void) { setupIt = skinSetups.begin(); };
    void TranslateSetup(void);
    void SetSkinSetupParameters(void);
    void UpdateSkinSetupParameter(string name, int value);
    void SetGlobals(cGlobals *globals) { tmplGlobals = globals; };
    void UpdateGlobals(void);
    void CheckDecimalPoint(void);
    void SetSkin(void);
    bool SkinChanged(void);
    void SetOSDSize(void);
    bool OsdSizeChanged(void);
    void SetOSDFonts(void);
    bool OsdFontsChanged(void);
    void SetOsdLanguage(void) { osdLanguage = Setup.OSDLanguage; };
    bool OsdLanguageChanged(void);
    cString GetSkinRessourcePath(void);
    void AddPluginMenus(string name, map< int, string > menus);
    void AddPluginViews(string name, map< int, string > views, multimap< int, pair <int, string> > subViews, map< int, map <int, string> > viewElements, map< int, map <int, string> > viewGrids);
    void InitPluginMenuIterator(void);
    map <int,string> *GetPluginTemplates(string &name);
    void InitPluginViewIterator(void);
    map <int,string> *GetPluginViews(string &name);
    map <int,string> GetPluginSubViews(string name, int viewID);
    int GetPluginViewElementID(string pluginName, string viewElementName, int viewID);
    int GetPluginViewGridID(string pluginName, string viewGridName, int viewID);
    cString skinPath;
    cString logoPath;
    cString epgImagePath;
    vector<string> skins;
    vector<string>::iterator skinIterator;
    bool replaceDecPoint;
    char decPoint;
    //Setup Parameter
    int numLogosPerSizeInitial;
    int limitLogoCache;
    int numLogosMax;
    int debugImageLoading;
    int rerunAmount;
    int rerunDistance;
    int rerunMaxChannel;
    int blockFlush;
    //TemplateReload on Setup Close
    bool setupCloseDoReload;
};

#ifdef DEFINE_CONFIG
    cDesignerConfig config;
    cFontManager *fontManager = NULL;
    cImageCache *imgCache = NULL;
    cTheme Theme;
    cRecordingsFolderInfo recFolderInfo(Recordings);
#else
    extern cDesignerConfig config;
    extern cFontManager *fontManager;
    extern cImageCache *imgCache;
    extern cTheme Theme;
    extern cRecordingsFolderInfo recFolderInfo;
#endif

#endif //__DESIGNER_CONFIG_H
